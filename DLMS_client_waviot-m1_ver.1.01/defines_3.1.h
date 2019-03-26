#ifndef _DEFINES_HW_3_1_H_
#define _DEFINES_HW_3_1_H_

#define DD_ADE7868A
#define SENSOR_ADC_COVER ( 2000 )
#define SENSOR_ADC_BODY  ( 150 )
#define ADE_GainI (0)
#define ADE_GainU (0)
#define METER_K (1.0 / 500.0)

#define DEV_HW_id       (0x31) // 3-фазы 1-прямое контроль нуля
#define DEV_HW_rev      (0x11)
//#define DEV_SW_rev      (0x35) // 3-фазы
//#define DEV_SW_sub      (0x01)
#define DEV_SW_rev      (0x31) // 3-фазы
#define DEV_SW_sub      (0x30)

#endif // _DEFINES_HW_3_1_H_
