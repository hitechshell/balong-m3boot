#include <osl_common.h>
#include <osl_bio.h>
#include "hi_base.h"
#include "hi_tsensor.h"

#ifdef TSENSOR_NEW
#include <soc_onchiprom.h>
#include <soc_memmap.h>
#else
#include <hi_syssc.h>
#endif

#ifdef TSENSOR_NEW
#define TEMCODE_TO_TEMPERATURE(c) ((c-125)*165/806-40)
#define CODE_DATA_MASK 0x3FF /* bit0~9 is data */
#define CODE_SIGN_MASK 0x400 /* bit11 is signal */
int g_trim_tem = 0;

/*
Compare the programmed efuse values with the ambient temperature
The bit value is 11 bits, with the MSB as the sign bit (1 indicating negative, 0 indicating positive), representing 0.25 C (per bit). The valid numerical values range from [-1023, 1023], corresponding to a temperature range of [-255.75 C, 255.75 C].
*/
int code2temperature(int code)
{
    int temp = 0;

    temp = (code & CODE_DATA_MASK) / 4;

    return (code & CODE_SIGN_MASK) ? -temp : temp;
}

/*
Chip data acquisition interface, note:
(1) The acquisition rate is set to 1.5ms
(2) Please note that if the acquisition rate exceeds 1300 (including 130) 
*/

int chip_tem_get(void)
{
    unsigned main_tem = 0;

    unsigned main_code = 0;

    main_code = readl(HI_TSENSOR_BASE_ADDR + HI_TEMP1_OFFSET);

    main_tem = TEMCODE_TO_TEMPERATURE(main_code);

    return main_tem + g_trim_tem;
}

int get_trim_temp(void)
{
    tOcrShareData *p_share_data = (tOcrShareData *)M3_TCM_SHARE_DATA_ADDR;
    unsigned int efuse_val = 0;
    int tem_from_tsensor = 0;
    int tem_base = 0;
    int ret = 0;

    ret = p_share_data->efuse_read(16, &efuse_val, 1);    
    if(ret)
    {
        return ret;
    }

    tem_from_tsensor = code2temperature(efuse_val & (CODE_SIGN_MASK | CODE_DATA_MASK));
    tem_base = code2temperature((efuse_val >> 11) & (CODE_SIGN_MASK | CODE_DATA_MASK));
    
    g_trim_tem = tem_base - tem_from_tsensor;
    
    return 0;
}

int tsensor_init(void)
{
	/* There are 32 channels in total. The value to be used for each channel. The channel is selected as local. The conversion time is 0.512ms */
    writel(0x60400, HI_TSENSOR_BASE_ADDR + HI_TEMP_CONFIG1_OFFSET); 

    /* 开启去使能后等待 */
    writel(0, HI_TSENSOR_BASE_ADDR + HI_TEMP_WAIT_BYPASS1_OFFSET); 

    /* 去使能后等待时间5us */
    writel(0x1F4, HI_TSENSOR_BASE_ADDR + HI_TEMP_WAIT_TIME1_OFFSET); 

    /* 屏蔽中断temp_mskint/temp_rst */
    writel(0, HI_TSENSOR_BASE_ADDR + HI_TEMP_INT_MSK1_OFFSET);
    writel(0, HI_TSENSOR_BASE_ADDR + HI_TEMP_RST_MSK1_OFFSET);

    /* 开启校准算法，使能tsensor */
    writel(0x1, HI_TSENSOR_BASE_ADDR + HI_TEMP_DET_EN1_OFFSET);

    /* 获取修正温度值 */
    return get_trim_temp();
}



#else
#define TEMCODE_TO_TEMPERATURE(c) (((c)*200-60*255)*10/255)

short trim_array[]={0,8,16,23,31,39,47,55,-8,-16,-23,-31,-39,-47,-55,-62};

/*
int tsensor_init(void)
{
	set_hi_temp_config_sample_num(0x2);		//Set the number of samples for one conversion

	set_hi_temp_config_sample_mode(0x2);	//Set the number of averages for multiple conversions

	set_hi_temp_config_test(0x0);			//Select local temperature sensor

	//set_hi_temp_config_ct_sel(0x01);		//Conversion time is 6.144ms

	set_hi_temp_config_ct_sel(0x0);			//Conversion time is 0.768ms

	set_hi_temp_dis_time_temp_dis_time(0x6); //Set the display time for the temperature sensor

	set_hi_temp_en_temp_en(0x1);		//Enable

	return 0;
}
*/

//the function is reverse engineered (since the source code for set_hi_temp_* is lost)
int tsensor_init(void)
{
	unsigned int *puVar1;
	puVar1 = (unsigned int *)0x9000B018;
	*puVar1 = *puVar1 & 0xfffffc7f | 0x100;
	*puVar1 = *puVar1 & 0xffffff9f | 0x40;
	*puVar1 = *puVar1 & 0xffffffe3;
	*puVar1 = *puVar1 & 0xfffffffc;
	puVar1[-5] = puVar1[-5] & 0xffffff00 | 6;
	puVar1[-6] = puVar1[-6] | 1;
	return 0;
}

/*
Note when chip obtains serial port data:
(1) The default interval for obtaining data is 1.5ms
(2) If the data exceeds 1300 (including 130) bytes, please pay attention to it
*/

/*
int chip_tem_get(void)
{
    int main_tem = 0;
    int trim_tem = 0;
    
    int main_code = 0;
    int trim_code = 0;
	    
    main_code = get_hi_temp_temp();
    trim_code = get_hi_sc_stat86_efuse_tsensor_trim() & ((0x1 << 8) - 1);

    main_tem = TEMCODE_TO_TEMPERATURE(main_code);
    trim_tem = trim_array[trim_code & 0xF];
    
    return (main_tem + trim_tem);

}
*/

int chip_tem_get(void)
{
    int main_tem = 0;
    int trim_tem = 0;
    
    int main_code = 0;
    int trim_code = 0;
	    
    main_code = (unsigned int *)0x9000B028;
    trim_code = (unsigned int *)0x90000758;

    return TEMCODE_TO_TEMPERATURE(main_code) + trim_array[trim_code & 0xF];

}
#endif
