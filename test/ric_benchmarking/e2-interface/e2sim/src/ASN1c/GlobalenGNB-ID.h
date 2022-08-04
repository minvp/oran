/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2AP-IEs"
 * 	found in "/root/e2ap-v01.00.00.asn"
 * 	`asn1c -fcompound-names -fincludes-quoted -fno-include-deps -findirect-choice -gen-PER -D .`
 */

#ifndef	_GlobalenGNB_ID_H_
#define	_GlobalenGNB_ID_H_


#include "asn_application.h"

/* Including external dependencies */
#include "PLMN-Identity.h"
#include "ENGNB-ID.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* GlobalenGNB-ID */
typedef struct GlobalenGNB_ID {
	PLMN_Identity_t	 pLMN_Identity;
	ENGNB_ID_t	 gNB_ID;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} GlobalenGNB_ID_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_GlobalenGNB_ID;
extern asn_SEQUENCE_specifics_t asn_SPC_GlobalenGNB_ID_specs_1;
extern asn_TYPE_member_t asn_MBR_GlobalenGNB_ID_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _GlobalenGNB_ID_H_ */
#include "asn_internal.h"
