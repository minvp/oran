/*****************************************************************************
#                                                                            *
# Copyright 2019 AT&T Intellectual Property                                  *
#                                                                            *
# Licensed under the Apache License, Version 2.0 (the "License");            *
# you may not use this file except in compliance with the License.           *
# You may obtain a copy of the License at                                    *
#                                                                            *
#      http://www.apache.org/licenses/LICENSE-2.0                            *
#                                                                            *
# Unless required by applicable law or agreed to in writing, software        *
# distributed under the License is distributed on an "AS IS" BASIS,          *
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   *
# See the License for the specific language governing permissions and        *
# limitations under the License.                                             *
#                                                                            *
******************************************************************************/

/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "X2AP-PDU-Contents"
 * 	found in "../../asnFiles/X2AP-PDU-Contents.asn"
 * 	`asn1c -fcompound-names -fincludes-quoted -fno-include-deps -findirect-choice -gen-PER -no-gen-OER -D.`
 */

#include "E-RABs-AdmittedToBeModified-SgNBModConf-Item.h"

#include "ProtocolExtensionContainer.h"
#include "E-RABs-AdmittedToBeModified-SgNBModConf-Item-SgNBPDCPpresent.h"
#include "E-RABs-AdmittedToBeModified-SgNBModConf-Item-SgNBPDCPnotpresent.h"
static asn_per_constraints_t asn_PER_type_resource_configuration_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  1,  1,  0,  1 }	/* (0..1,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_resource_configuration_4[] = {
	{ ATF_POINTER, 0, offsetof(struct E_RABs_AdmittedToBeModified_SgNBModConf_Item__resource_configuration, choice.sgNBPDCPpresent),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_E_RABs_AdmittedToBeModified_SgNBModConf_Item_SgNBPDCPpresent,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"sgNBPDCPpresent"
		},
	{ ATF_POINTER, 0, offsetof(struct E_RABs_AdmittedToBeModified_SgNBModConf_Item__resource_configuration, choice.sgNBPDCPnotpresent),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_E_RABs_AdmittedToBeModified_SgNBModConf_Item_SgNBPDCPnotpresent,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"sgNBPDCPnotpresent"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_resource_configuration_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* sgNBPDCPpresent */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* sgNBPDCPnotpresent */
};
static asn_CHOICE_specifics_t asn_SPC_resource_configuration_specs_4 = {
	sizeof(struct E_RABs_AdmittedToBeModified_SgNBModConf_Item__resource_configuration),
	offsetof(struct E_RABs_AdmittedToBeModified_SgNBModConf_Item__resource_configuration, _asn_ctx),
	offsetof(struct E_RABs_AdmittedToBeModified_SgNBModConf_Item__resource_configuration, present),
	sizeof(((struct E_RABs_AdmittedToBeModified_SgNBModConf_Item__resource_configuration *)0)->present),
	asn_MAP_resource_configuration_tag2el_4,
	2,	/* Count of tags in the map */
	0, 0,
	2	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_resource_configuration_4 = {
	"resource-configuration",
	"resource-configuration",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ 0, &asn_PER_type_resource_configuration_constr_4, CHOICE_constraint },
	asn_MBR_resource_configuration_4,
	2,	/* Elements count */
	&asn_SPC_resource_configuration_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_E_RABs_AdmittedToBeModified_SgNBModConf_Item_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct E_RABs_AdmittedToBeModified_SgNBModConf_Item, e_RAB_ID),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_E_RAB_ID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"e-RAB-ID"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct E_RABs_AdmittedToBeModified_SgNBModConf_Item, en_DC_ResourceConfiguration),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_EN_DC_ResourceConfiguration,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"en-DC-ResourceConfiguration"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct E_RABs_AdmittedToBeModified_SgNBModConf_Item, resource_configuration),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_resource_configuration_4,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"resource-configuration"
		},
	{ ATF_POINTER, 1, offsetof(struct E_RABs_AdmittedToBeModified_SgNBModConf_Item, iE_Extensions),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ProtocolExtensionContainer_170P75,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"iE-Extensions"
		},
};
static const int asn_MAP_E_RABs_AdmittedToBeModified_SgNBModConf_Item_oms_1[] = { 3 };
static const ber_tlv_tag_t asn_DEF_E_RABs_AdmittedToBeModified_SgNBModConf_Item_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_E_RABs_AdmittedToBeModified_SgNBModConf_Item_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* e-RAB-ID */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* en-DC-ResourceConfiguration */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* resource-configuration */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* iE-Extensions */
};
static asn_SEQUENCE_specifics_t asn_SPC_E_RABs_AdmittedToBeModified_SgNBModConf_Item_specs_1 = {
	sizeof(struct E_RABs_AdmittedToBeModified_SgNBModConf_Item),
	offsetof(struct E_RABs_AdmittedToBeModified_SgNBModConf_Item, _asn_ctx),
	asn_MAP_E_RABs_AdmittedToBeModified_SgNBModConf_Item_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_E_RABs_AdmittedToBeModified_SgNBModConf_Item_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	4,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_E_RABs_AdmittedToBeModified_SgNBModConf_Item = {
	"E-RABs-AdmittedToBeModified-SgNBModConf-Item",
	"E-RABs-AdmittedToBeModified-SgNBModConf-Item",
	&asn_OP_SEQUENCE,
	asn_DEF_E_RABs_AdmittedToBeModified_SgNBModConf_Item_tags_1,
	sizeof(asn_DEF_E_RABs_AdmittedToBeModified_SgNBModConf_Item_tags_1)
		/sizeof(asn_DEF_E_RABs_AdmittedToBeModified_SgNBModConf_Item_tags_1[0]), /* 1 */
	asn_DEF_E_RABs_AdmittedToBeModified_SgNBModConf_Item_tags_1,	/* Same as above */
	sizeof(asn_DEF_E_RABs_AdmittedToBeModified_SgNBModConf_Item_tags_1)
		/sizeof(asn_DEF_E_RABs_AdmittedToBeModified_SgNBModConf_Item_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_E_RABs_AdmittedToBeModified_SgNBModConf_Item_1,
	4,	/* Elements count */
	&asn_SPC_E_RABs_AdmittedToBeModified_SgNBModConf_Item_specs_1	/* Additional specs */
};

