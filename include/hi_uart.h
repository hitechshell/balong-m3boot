#ifndef HI6930_UART_H
#define HI6930_UART_H

/*
 * bsp_uart.h -- balong uart driver header for both linux and vxworks
 *
 * Copyright (C) 2012 Huawei Corporation
 * 
 *
*/
#include "soc_memmap.h"

#define CCORE_SYS_UART_BASE         HI_UART2_REGBASE_ADDR
#define CCORE_SYS_UART_INTID        INT_LVL_UART2

#define UART_USE_FLAG               0x112233
#define AT_UART_USE_FLAG            0x116119

#define PRT_FLAG_EN_MAGIC_M         0x24680136  /* MºËÐÄ°´¼üºê¶¨Òå*/
#define PRT_FLAG_EN_MAGIC_A         0x24680137  /* AºËÐÄ°´¼üºê¶¨Òå*/

#define UART_BALONG_ID              0x000c21c0  /* uart id */
#define UART_BALONG_ID_MASK         0x000fffff 
/*-----------------------OFFSET OF REGISTER------------------------*/
#define	UART_REGOFF_RBR		        0x00		 /* UART data register (R/W) */
#define UART_REGOFF_DLL             0x00         /*UART Divisor Low bits */
#define UART_REGOFF_THR             0x00         /*UART Transmit Holding */

#define UART_REGOFF_DLH             0x04         /*UART Divisor High bits*/
#define UART_REGOFF_IER             0x04         /*Int Enable register */

#define UART_REGOFF_FCR             0x08         /*Fifo Control register(W)*/
#define UART_REGOFF_IIR             0x08         /*Int Status register(R)*/

#define UART_REGOFF_LCR             0x0C         /*UART Line Control register */

#define UART_REGOFF_USR             0x7C         /*UART Status register */

#define UART_REGOFF_LSR             0x14         /*UART Line Status Register*/

#define UART_FIFO_SIZE              16           /* FIFO SIZE*/
#define UART_FIFO_MASK              0x0F
/*-------------------LCR BITS FIELD-----------------------------*/
#define UART_LCR_DLS_MASK           0x03 /* Êý¾Ý³¤¶ÈÑÚÂë*/
#define UART_LCR_DLS_5BITS          0x00 /* Êý¾Ý³¤¶ÈÑ¡Ôñ,5bits */
#define UART_LCR_DLS_6BITS          0x01 /* Êý¾Ý³¤¶ÈÑ¡Ôñ,6bits */
#define UART_LCR_DLS_7BITS          0x02 /* Êý¾Ý³¤¶ÈÑ¡Ôñ,7bits */
#define UART_LCR_DLS_8BITS          0x03 /* Êý¾Ý³¤¶ÈÑ¡Ôñ,8bits */

#define UART_LCR_STOP_2BITS         0x04 /* Í£Ö¹Î»¸öÊý,2bits*/
#define UART_LCR_STOP_1BITS         0x00 /* Í£Ö¹Î»¸öÊý,1bit */
#define UART_LCR_PEN_NONE	        0x00 /* set no parity */

#define UART_LCR_PEN                0x08 /* ÆæÅ¼Ð£ÑéÊ¹ÄÜ*/
#define UART_LCR_EPS                0x10 /* ÆæÅ¼Ð£ÑéÑ¡Ôñ*/
#define UART_LCR_BREAK              0x40 /* ´ò¿ªBREAK ¿ØÖÆ */
#define UART_LCR_DLAB               0x80 /* ´ò¿ªDLL/DHL */

#define UART_LCR_DEFAULTVALUE       0x00 /* LCRÄ¬ÈÏÖµ*/

#define UART_LCR_BC_NORMAL          0x00 /* ÔÝÍ£¿ØÖÆÎ» Õý³£*/
#define UART_LCR_BC_UNNORMAL        0x40 /* ÔÝÍ£¿ØÖÆÎ» ÔÝÍ£*/

/*-------------------IER BITS FIELD-----------------------------*/
#define UART_IER_IRQ_DISABLE	    0x00 /* Disable both FIFOs */
#define UART_IER_LS_IRQ_ENABLE      0x04 /*Line Status Int Enable*/
#define UART_IER_TX_IRQ_ENABLE      0x02 /*Transmitter Int Enable*/
#define UART_IER_RX_IRQ_ENABLE      0x01 /*Receiver Int Enable*/

#define PTIME       (1<<7)

/*-------------------LSR BITS FIELD-----------------------------*/
#define UART_LSR_DR                 0x01 /* Êý¾Ý×¼±¸ºÃ*/
#define UART_LSR_OE                 0x02 /* Òç³ö±êÖ¾*/
#define UART_LSR_PE                 0x04 /* ÆæÅ¼Ð£Ñé´íÎó±êÖ¾*/
#define UART_LSR_FE                 0x08 /* Ö¡´íÎó±êÖ¾*/
#define UART_LSR_BI                 0x10 /* ÖÐ¶ÏÔÝÍ£±êÖ¾*/
#define UART_LSR_THRE               0x20 /* THRÎª¿Õ*/
#define UART_LSR_TEMT               0x40 /* ·¢ËÍ¿Õ±êÖ¾*/
#define UART_LSR_ERR_ANY (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE | UART_LSR_BI)

/*-------------------IIR BITS FIELD-----------------------------*/
#define UART_IIR_REV_STA            0x06 /* ½ÓÊÕÏß×´Ì¬ÖÐ¶Ï   */
#define UART_IIR_REV_VALID          0x04 /* ½ÓÊÕÏßÊý¾ÝÓÐÐ§ */
#define UART_IIR_REV_TIMEOUT        0x0C /* ½ÓÊÕ³¬Ê±    */
#define UART_IIR_THR_EMPTY          0x02 /* transmit hold reg empty */
#define UART_IIR_NO_INTERRUPT       0x01 /* NO interrupt pending */
#define UART_IIR_MODEM_INTERRUPT    0x00 /* FOURTH modem int    */

/*-------------------USR BITS FIELD-----------------------------*/
#define UART_USR_UART_BUSY          0x01 /* UARTÃ¦±êÖ¾   */
#define UART_USR_FIFO_NOT_FULL      0x02 /* ·¢ËÍFIFO²»Âú±êÖ¾   */
#define UART_USR_FIFO_EMP           0x04 /* ·¢ËÍFIFOÎª¿Õ±êÖ¾   */
#define UART_USR_FIFO_NOT_EMP       0x08 /* ½ÓÊÕFIFO·Ç¿Õ±êÖ¾   */
#define UART_USR_FIFO_FULL          0x10 /* ½ÓÊÕFIFOÂú±êÖ¾   */

/*-------------------FCR BITS FIELD-----------------------------*/
#define UART_FCR_FIFO_ENABLE	    0x01 /* Enable both FIFOs */
#define UART_FCR_FIFO_DISABLE	    0x00 /* Disable both FIFOs */
#define UART_FCR_DEF_SET            0xB7 /* Ê¹ÄÜFIFO,¸´Î»½ÓÊÕÓë·¢ËÍFIFO£¬½ÓÊÕ·¢ËÍË®ÏßÎªFIFO-2 */

/******************* uart print macro definition ********************/
#ifndef __ASSEMBLY__
struct uart_info{
	unsigned int uart_base_addr;
	unsigned int uart_intid;
};

extern struct uart_info g_uart_info;

#define AMBA_UART_DR(base)	(*(volatile unsigned int *)((base) + 0x00))
#define AMBA_UART_LCRH(base)	(*(volatile unsigned int *)((base) + 0x2c))
#define AMBA_UART_CR(base)	(*(volatile unsigned int *)((base) + 0x30))
#define AMBA_UART_LSR(base)	(*(volatile unsigned int *)((base) + 0x14))


static inline void my_putc(int c)
{
	while (!(AMBA_UART_LSR(HI_UART0_REGBASE_ADDR) & 0x20));

	AMBA_UART_DR(HI_UART0_REGBASE_ADDR) = c;
}

static inline void print_info(const char *ptr)
{
	char c;

	while ((c = *ptr++) != '\0') {
		if (c == '\n')
			my_putc('\r');
		my_putc(c);
	}
}

#endif
#define print_uart_m3boot(value)\
	ldr r1, =HI_UART0_REGBASE_ADDR;\
	ldr r2, =value;\
	ldr r3, =UART_REGOFF_THR;\
	str r2, [r1,r3]
            
#define uart_init_m3boot \
	ldr r1, =HI_UART0_REGBASE_ADDR;\
	ldr r2, =0x7;\
	ldr r3, =UART_REGOFF_FCR;\
	str r2, [r1, r3];\
	ldr r2, =0x83;\
	ldr r3, =UART_REGOFF_LCR;\
	str r2, [r1, r3];\
	ldr r2, =0x1A;\
	ldr r3, =UART_REGOFF_DLL;\
	str r2, [r1, r3];\
	ldr r2, =0x0;\
	ldr r3, =UART_REGOFF_IER;\
	str r2, [r1, r3];\
	ldr r2, =0x3;\
	ldr r3, =UART_REGOFF_LCR;\
	str r2, [r1, r3];\
	ldr r2, =0x0;\
	ldr r3, =UART_REGOFF_IER;\
	str r2, [r1, r3];\
	bx lr
#endif /* BSP_UART_H */
