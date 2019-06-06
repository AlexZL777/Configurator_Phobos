#ifndef _DLMS_PDU_H_
#define _DLMS_PDU_H_

#include <stdint.h>
#include "DLMS_COSEM_objects.h"
#include "DLMS_PDU_buf.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t COSEM_GET_AttributeAccess(PDU_channel *pdu_ch, const COSEM_OBJECT_Attribute *attr);
uint32_t COSEM_OBIS_to_uint(const COSEM_OBJECT *obj);
uint32_t OBIS_ATTR_to_uint(const OBIS * obis, uint8_t attr);
DLMS_UNIT OBIS_to_unit(uint8_t C, uint8_t D);

const COSEM_OBJECT * COSEM_Find_OBJECT(OBIS * obis);
const COSEM_OBJECT_Attribute * COSEM_Find_Attribute(const COSEM_OBJECT * obj, uint8_t attr_index);
const COSEM_OBJECT_Attribute * COSEM_Find_Method(const COSEM_OBJECT * obj, uint8_t method_index);
void COSEM_profile_array_name(DLMS_PDU_BUF * pb, const COSEM_OBJECT * cobj, uint8_t attr);
uint8_t COSEM_obj_to_list_count(const COSEM_OBJECT *obj, PDU_channel *pdu_ch, uint8_t *p_array_count);
uint8_t COSEM_obj_to_list(const COSEM_OBJECT *obj, PDU_channel *pdu_ch, DLMS_PDU_BUF * pb, uint8_t *p_array_count);
void DLMS_PDU_controller(HDLC_BUF *hdlc);

#ifdef __cplusplus
}
#endif

#endif // _DLMS_PDU_H_
