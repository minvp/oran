/*
# ==================================================================================
# Copyright (c) 2020 HCL Technologies Limited.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==================================================================================
*/

#include "xapp.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include<string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using jsonn = nlohmann::json;
#define BUFFER_SIZE 1024
extern std::vector<std::string>SubscriptionIds;
 Xapp::Xapp(XappSettings &config, XappRmr &rmr){

	  rmr_ref = &rmr;
	  config_ref = &config;
	  xapp_mutex = NULL;
	  subhandler_ref = NULL;
	  return;
  }

Xapp::~Xapp(void){

	//Joining the threads
	int threadcnt = xapp_rcv_thread.size();
		for(int i=0; i<threadcnt; i++){
			if(xapp_rcv_thread[i].joinable())
				xapp_rcv_thread[i].join();
	}
	xapp_rcv_thread.clear();

	if(xapp_mutex!=NULL){
		xapp_mutex->~mutex();
		delete xapp_mutex;
	}
};

//Stop the xapp. Note- To be run only from unit test scripts.
void Xapp::stop(void){
  // Get the mutex lock
	std::lock_guard<std::mutex> guard(*xapp_mutex);
	rmr_ref->set_listen(false);
	rmr_ref->~XappRmr();

	//Detaching the threads....not sure if this is the right way to stop the receiver threads.
	//Hence function should be called only in Unit Tests
	int threadcnt = xapp_rcv_thread.size();
	for(int i=0; i<threadcnt; i++){
		xapp_rcv_thread[i].detach();
	}
	sleep(10);
}

void Xapp::startup(SubscriptionHandler &sub_ref) {

	subhandler_ref = &sub_ref;
	set_rnib_gnblist();

	sleep(70);

	//send subscriptions.
	startup_subscribe_requests();

	//read A1 policies
	//startup_get_policies();
	return;
}
void Xapp::Run(){
	rmr_ref->set_listen(true);
	if(xapp_mutex == NULL){
		xapp_mutex = new std::mutex();
	}
	std::lock_guard<std::mutex> guard(*xapp_mutex);

	for(int j=0; j < _callbacks.size(); j++){
		std::thread th_recv([&](){ rmr_ref->xapp_rmr_receive(std::move(_callbacks[j]), rmr_ref);});
		xapp_rcv_thread.push_back(std::move(th_recv));
	}

	return;
}

//Starting a seperate single receiver
void Xapp::start_xapp_receiver(XappMsgHandler& mp_handler){
	//start a receiver thread. Can be multiple receiver threads for more than 1 listening port.
	rmr_ref->set_listen(true);
	if(xapp_mutex == NULL){
		xapp_mutex = new std::mutex();
	}

	mdclog_write(MDCLOG_INFO,"Receiver Thread file= %s, line=%d",__FILE__,__LINE__);
	std::lock_guard<std::mutex> guard(*xapp_mutex);
	std::thread th_recv([&](){ rmr_ref->xapp_rmr_receive(std::move(mp_handler), rmr_ref);});
	xapp_rcv_thread.push_back(std::move(th_recv));
	return;
}

void Xapp::shutdown(){
	
        sleep(70);
        //send subscriptions delete.
        shutdown_subscribe_deletes();
        return;
}

void Xapp::shutdown_subscribe_deletes(void )
{

	bool res;
   	size_t data_size = ASN_BUFF_MAX_SIZE;
   	unsigned char	data[data_size];
   	//unsigned char meid[RMR_MAX_MEID];
	char meid[RMR_MAX_MEID];
   	std::string xapp_id = config_ref->operator [](XappSettings::SettingName::XAPP_ID);

   	mdclog_write(MDCLOG_INFO,"Preparing to send subscription Delete in file= %s, line=%d",__FILE__,__LINE__);

   	auto gnblist = get_rnib_gnblist();

   	int sz = gnblist.size();
	 mdclog_write(MDCLOG_INFO,"GNBList size : %d", sz);

   	if(sz <= 0)
		mdclog_write(MDCLOG_INFO,"Subscriptions Delete cannot be sent as GNBList in RNIB is NULL");

   	for(int i = 0; i<sz; i++)
   	{
	 	sleep(15);
	 	//give the message to subscription handler, along with the transmitter.
	 	strcpy((char*)meid,gnblist[i].c_str());
		mdclog_write(MDCLOG_INFO,"sending %d subscription delete request out of : %d",i+1, sz);
	     	mdclog_write(MDCLOG_INFO,"sending subscription delete to ,meid = %s", meid);
		
		if (SubscriptionIds.size()>0)
		{
		auto delJson = pplx::create_task([i,meid]() {
		utility::string_t port = U("8088");
                utility::string_t address = U("http://service-ricplt-submgr-http.ricplt.svc.cluster.local:");
                address.append(port);
                address.append(U("/ric/v1/subscriptions/"));
		address.append( utility::string_t(SubscriptionIds.back()));
				SubscriptionIds.pop_back();
                uri_builder uri(address);
                auto addr = uri.to_uri().to_string();
                http_client client(addr);
                ucout << utility::string_t(U("making requests at: ")) << addr <<std::endl;
                return client.request(methods::DEL);

                 
                        })

                        // Get the response.
                                .then([](http_response response) {
                                // Check the status code.
                                if (response.status_code() != 204) {
                                        throw std::runtime_error("Returned " + std::to_string(response.status_code()));
                                }

                                // Convert the response body to JSON object.
                                	std::wcout << "Deleted: " << std::boolalpha << (response.status_code() == 204) << std::endl;
                                        });

                                // serailize the user details.
                      

                                        try {
                                                delJson.wait();
                                        }
                                        catch (const std::exception& e) {
                                                printf("Error exception:%s\n", e.what());
                                        }
										
		}
		
		else{
		 mdclog_write(MDCLOG_ERR,"Subscription delete cannot send in file= %s, line=%d for MEID %s as no valid subIDS",__FILE__,__LINE__, meid);
		}

		/*


	 	subscription_helper  din;
	 	subscription_helper  dout;

         	subscription_delete sub_del;
         	subscription_delete sub_recv;

 
		unsigned char buf[BUFFER_SIZE];
	 	size_t buf_size = BUFFER_SIZE;
	 	bool res;


	 	//Random Data  for request
	 	int request_id = 1;
	 	int function_id = 1;

	 	din.set_request(request_id);
	 	din.set_function_id(function_id);

         	res = sub_del.encode_e2ap_subscription(&buf[0], &buf_size, din);

	 	mdclog_write(MDCLOG_INFO,"Sending subscription delete  in file= %s, line=%d for MEID %s",__FILE__,__LINE__, meid);

	 	xapp_rmr_header rmr_header; 
 	 	rmr_header.message_type = RIC_SUB_DEL_REQ;
 	 	rmr_header.payload_length = buf_size; //data_size

	 	strcpy((char*)rmr_header.meid,gnblist[i].c_str());
	 	auto transmitter = std::bind(&XappRmr::xapp_rmr_send,rmr_ref, &rmr_header, (void*)buf); //(void*)data)
		if (subhandler_ref)
		{
			mdclog_write(MDCLOG_INFO,"subhandler_ref is valid pointer");
		}
		else
		{
		 	mdclog_write(MDCLOG_INFO,"subhandler_ref is invalid pointer");
		}
         	int result = subhandler_ref->manage_subscription_delete_request(gnblist[i], transmitter);

       	 	if(result==SUBSCR_SUCCESS)
		{

     	      		mdclog_write(MDCLOG_INFO,"Subscription Delete SUCCESSFUL in file= %s, line=%d for MEID %s",__FILE__,__LINE__, meid);
          	}
          	else 
		{
		 	mdclog_write(MDCLOG_ERR,"Subscription Delete FAILED in file= %s, line=%d for MEID %s",__FILE__,__LINE__, meid);
              	}
		*/
	}
}

void Xapp::startup_subscribe_requests(void ){
   bool res;
   size_t data_size = ASN_BUFF_MAX_SIZE;
   unsigned char	data[data_size];
   char meid[RMR_MAX_MEID];
   std::string xapp_id = config_ref->operator [](XappSettings::SettingName::XAPP_ID);
   //int a =std::stoi(xapp_id);
   mdclog_write(MDCLOG_INFO,"Preparing to send subscription in file= %s, line=%d",__FILE__,__LINE__);

   auto gnblist = get_rnib_gnblist();

   int sz = gnblist.size();
	mdclog_write(MDCLOG_INFO,"GNBList size : %d", sz);
   if(sz <= 0)
	   mdclog_write(MDCLOG_INFO,"Subscriptions cannot be sent as GNBList in RNIB is NULL");

   for(int i = 0; i<sz; i++)
   {
	 sleep(15);
	 strcpy((char*)meid,gnblist[i].c_str());
        mdclog_write(MDCLOG_INFO,"sending %d subscription request out of : %d",i+1, sz);

	 //mdclog_write(MDCLOG_INFO,"GNBList,gnblist[i] = %s and ith val = %d", gnblist[i], i);
	 mdclog_write(MDCLOG_INFO,"sending subscription to ,meid = %s", meid);

auto postJson = pplx::create_task([meid,xapp_id]() {


                jsonn jsonObject;
                 jsonObject =
    {



        {"SubscriptionId",""},
        {"ClientEndpoint",{{"Host","service-ricxapp-bouncer-xapp-http.ricxapp"},{"HTTPPort",8080},{"RMRPort",4560}}},
        {"Meid",meid},
        {"RANFunctionID",0},
        {"SubscriptionDetails",
                {
                        {
                            {"XappEventInstanceId",12345},{"EventTriggers",{0}},
                            {"ActionToBeSetupList",
                                    {
                                        {
                                                {"ActionID",1},{"ActionType","report"},{"ActionDefinition",{0}},{"SubsequentAction",{{"SubsequentActionType","continue"},{"TimeToWait","zero"}}}
                                        }
                                    }
                            }
                        }
                }
        }

    };
                        std::cout <<jsonObject.dump(4) << "\n";
                        utility::stringstream_t s;
                        s << jsonObject.dump().c_str();
                        web::json::value ret = json::value::parse(s);
                       // std::wcout << ret.serialize().c_str() << std::endl;
                utility::string_t port = U("8088");
                 utility::string_t address = U("http://service-ricplt-submgr-http.ricplt.svc.cluster.local:");
                  address.append(port);
                  address.append(U("/ric/v1/subscriptions"));
                uri_builder uri(address);
                auto addr = uri.to_uri().to_string();
                http_client client(addr);
                //std::cout<<uri::validate(addr)<<" validation \n";
                ucout << utility::string_t(U("making requests at: ")) << addr << "\n";
                return client.request(methods::POST,U("/"),ret.serialize(),U("application/json"));
                        })

                        // Get the response.
                                .then([](http_response response) {
                                // Check the status code.
                                if (response.status_code() != 201) {
                                        throw std::runtime_error("Returned " + std::to_string(response.status_code()));
                                }

                                // Convert the response body to JSON object.
                                return response.extract_json();
                                        })

                                // serailize the user details.
                                                .then([](json::value jsonObject) {
						std::cout<<"\nRecieved REST subscription response\n";
                                                std::wcout << jsonObject.serialize().c_str() << "\n";
						std::string tmp;
						tmp=jsonObject[U("SubscriptionId")].as_string();
						SubscriptionIds.push_back(tmp);

                                                        });

                                        try {
                                                postJson.wait();
                                        }
                                        catch (const std::exception& e) {
                                                printf("Error exception:%s\n", e.what());
                                        }

	
	/*
	 //give the message to subscription handler, along with the transmitter.
	 strcpy((char*)meid,gnblist[i].c_str());

         mdclog_write(MDCLOG_INFO,"GNBList size : %d", sz);
	mdclog_write(MDCLOG_INFO,"sending %d subscription request out of : %d",i+1, sz);
	 subscription_helper  din;
	 subscription_helper  dout;

	 subscription_request sub_req;
	 subscription_request sub_recv;

	 unsigned char buf[BUFFER_SIZE];
	 size_t buf_size = BUFFER_SIZE;
	 bool res;


	 //Random Data  for request
	 int request_id = 1;
	 int function_id = 0;
	 std::string event_def = "01";

	 din.set_request(request_id);
	 din.set_function_id(function_id);
	 din.set_event_def(event_def.c_str(), event_def.length());

	 std::string act_def = "01";

	 din.add_action(1,0,(void*)act_def.c_str(), act_def.length(), 0);

	 res = sub_req.encode_e2ap_subscription(&buf[0], &buf_size, din);

	 //mdclog_write(MDCLOG_INFO,"GNBList = %s and ith val = %d", gnblist[i], i);

	 mdclog_write(MDCLOG_INFO,"Sending subscription in file= %s, line=%d for MEID %s",__FILE__,__LINE__, meid);
	 
	 xapp_rmr_header rmr_header;
 	 rmr_header.message_type = RIC_SUB_REQ;
 	 rmr_header.payload_length = buf_size; //data_size

	 strcpy((char*)rmr_header.meid,gnblist[i].c_str());

	 auto transmitter = std::bind(&XappRmr::xapp_rmr_send,rmr_ref, &rmr_header, (void*)buf); //(void*)data);
         
         int result = subhandler_ref->manage_subscription_request(gnblist[i], transmitter);
         
       	 if(result==SUBSCR_SUCCESS){

     	      mdclog_write(MDCLOG_INFO,"Subscription SUCCESSFUL in file= %s, line=%d for MEID %s",__FILE__,__LINE__, meid);
          }
          else {
		 mdclog_write(MDCLOG_ERR,"Subscription FAILED in file= %s, line=%d for MEID %s",__FILE__,__LINE__, meid);
              }
	    */  
	}
   std::cout<<"\n SubscriptionIds vector size= "<<SubscriptionIds.size()<<"\n"; 
}

void Xapp::startup_get_policies(void){

    int policy_id = BOUNCER_POLICY_ID;

    std::string policy_query = "{\"policy_type_id\":" + std::to_string(policy_id) + "}";
    unsigned char * message = (unsigned char *)calloc(policy_query.length(), sizeof(unsigned char));
    memcpy(message, policy_query.c_str(),  policy_query.length());
    xapp_rmr_header header;
    header.payload_length = policy_query.length();
    header.message_type = A1_POLICY_QUERY;
    mdclog_write(MDCLOG_INFO, "Sending request for policy id %d\n", policy_id);
    rmr_ref->xapp_rmr_send(&header, (void *)message);
    free(message);

}

void Xapp::set_rnib_gnblist(void) {

	   openSdl();

	   void *result = getListGnbIds();
	   if(strlen((char*)result) < 1){
		    mdclog_write(MDCLOG_ERR, "ERROR: no data from getListGnbIds\n");
	        return;
	    }

	    mdclog_write(MDCLOG_INFO, "GNB List in R-NIB %s\n", (char*)result);


	    Document doc;
	    ParseResult parseJson = doc.Parse<kParseStopWhenDoneFlag>((char*)result);
	    if (!parseJson) {
	    	std::cerr << "JSON parse error: %s (%u)", GetParseErrorFunc(parseJson.Code());
	    	return;
	    }

	    if(!doc.HasMember("gnb_list")){
	    	mdclog_write(MDCLOG_INFO, "JSON Has No GNB List Object");
	    	return;
	    }
	    assert(doc.HasMember("gnb_list"));

	    const Value& gnblist = doc["gnb_list"];
	    if (gnblist.IsNull())
	      return;

	    if(!gnblist.IsArray()){
	    	mdclog_write(MDCLOG_INFO, "GNB List is not an array");
	    	return;
	    }


	   	assert(gnblist.IsArray());
	    for (SizeType i = 0; i < gnblist.Size(); i++) // Uses SizeType instead of size_t
	    {
	    	assert(gnblist[i].IsObject());
	    	const Value& gnbobj = gnblist[i];
	    	assert(gnbobj.HasMember("inventory_name"));
	    	assert(gnbobj["inventory_name"].IsString());
	    	std::string name = gnbobj["inventory_name"].GetString();
	    	rnib_gnblist.push_back(name);

	    }
	    closeSdl();
	    return;

}

