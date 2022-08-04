/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-Bouncer-IEs"
 *      found in "/home/ubuntu/ASN-Defns/e2sm-Bouncer-v002.asn"
 * 	`asn1c -fno-include-deps -fcompound-names -findirect-choice -gen-PER -no-gen-OER`
 */

#ifndef	_E2SM_Bouncer_ControlMessage_H_
#define	_E2SM_Bouncer_ControlMessage_H_


#include <asn_application.h>

/* Including external dependencies */
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum E2SM_Bouncer_ControlMessage_PR {
	E2SM_Bouncer_ControlMessage_PR_NOTHING,	/* No components present */
	E2SM_Bouncer_ControlMessage_PR_controlMessage_Format1
	/* Extensions may appear below */
	
} E2SM_Bouncer_ControlMessage_PR;

/* Forward declarations */
struct E2SM_Bouncer_ControlMessage_Format1;

/* E2SM-Bouncer-ControlMessage */
typedef struct E2SM_Bouncer_ControlMessage {
	E2SM_Bouncer_ControlMessage_PR present;
	union E2SM_Bouncer_ControlMessage_u {
		struct E2SM_Bouncer_ControlMessage_Format1	*controlMessage_Format1;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} E2SM_Bouncer_ControlMessage_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_E2SM_Bouncer_ControlMessage;

#ifdef __cplusplus
}
#endif

#endif	/* _E2SM_Bouncer_ControlMessage_H_ */
#include <asn_internal.h>
