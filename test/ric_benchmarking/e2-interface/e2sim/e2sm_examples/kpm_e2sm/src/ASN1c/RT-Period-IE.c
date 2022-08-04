/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "E2SM-KPM-IEs"
 * 	found in "/home/rshacham/e2sm-kpm-v01.02.asn"
 * 	`asn1c -fcompound-names`
 */

#include "RT-Period-IE.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_RT_Period_IE_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_RT_Period_IE_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  5,  5,  0,  19 }	/* (0..19,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_RT_Period_IE_value2enum_1[] = {
	{ 0,	4,	"ms10" },
	{ 1,	4,	"ms20" },
	{ 2,	4,	"ms32" },
	{ 3,	4,	"ms40" },
	{ 4,	4,	"ms60" },
	{ 5,	4,	"ms64" },
	{ 6,	4,	"ms70" },
	{ 7,	4,	"ms80" },
	{ 8,	5,	"ms128" },
	{ 9,	5,	"ms160" },
	{ 10,	5,	"ms256" },
	{ 11,	5,	"ms320" },
	{ 12,	5,	"ms512" },
	{ 13,	5,	"ms640" },
	{ 14,	6,	"ms1024" },
	{ 15,	6,	"ms1280" },
	{ 16,	6,	"ms2048" },
	{ 17,	6,	"ms2560" },
	{ 18,	6,	"ms5120" },
	{ 19,	7,	"ms10240" }
	/* This list is extensible */
};
static const unsigned int asn_MAP_RT_Period_IE_enum2value_1[] = {
	0,	/* ms10(0) */
	14,	/* ms1024(14) */
	19,	/* ms10240(19) */
	8,	/* ms128(8) */
	15,	/* ms1280(15) */
	9,	/* ms160(9) */
	1,	/* ms20(1) */
	16,	/* ms2048(16) */
	10,	/* ms256(10) */
	17,	/* ms2560(17) */
	2,	/* ms32(2) */
	11,	/* ms320(11) */
	3,	/* ms40(3) */
	12,	/* ms512(12) */
	18,	/* ms5120(18) */
	4,	/* ms60(4) */
	5,	/* ms64(5) */
	13,	/* ms640(13) */
	6,	/* ms70(6) */
	7	/* ms80(7) */
	/* This list is extensible */
};
const asn_INTEGER_specifics_t asn_SPC_RT_Period_IE_specs_1 = {
	asn_MAP_RT_Period_IE_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_RT_Period_IE_enum2value_1,	/* N => "tag"; sorted by N */
	20,	/* Number of elements in the maps */
	21,	/* Extensions before this member */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_RT_Period_IE_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_RT_Period_IE = {
	"RT-Period-IE",
	"RT-Period-IE",
	&asn_OP_NativeEnumerated,
	asn_DEF_RT_Period_IE_tags_1,
	sizeof(asn_DEF_RT_Period_IE_tags_1)
		/sizeof(asn_DEF_RT_Period_IE_tags_1[0]), /* 1 */
	asn_DEF_RT_Period_IE_tags_1,	/* Same as above */
	sizeof(asn_DEF_RT_Period_IE_tags_1)
		/sizeof(asn_DEF_RT_Period_IE_tags_1[0]), /* 1 */
	{ &asn_OER_type_RT_Period_IE_constr_1, &asn_PER_type_RT_Period_IE_constr_1, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_RT_Period_IE_specs_1	/* Additional specs */
};

