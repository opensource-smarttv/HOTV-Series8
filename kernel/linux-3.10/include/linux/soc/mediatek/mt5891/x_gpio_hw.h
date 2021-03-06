/*
 * linux/arch/arm/mach-mt53xx/include/mach/x_gpio_hw.h
 *
 * Cobra GPIO defines
 *
 * Copyright (c) 2006-2012 MediaTek Inc.
 * $Author: wei.zhou $
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 *
 */

#ifndef __X_GPIO_HW_H__
#define __X_GPIO_HW_H__

#define TOTAL_NORMAL_GPIO_NUM   (NORMAL_GPIO_NUM)
#define NORMAL_GPIO_NUM         167
#define MAX_GPIO_NUM            (409)

#define TOTAL_OPCTRL_NUM        67
#define TOTAL_PDWNC_GPIO_INT_NUM 44
#define TOTAL_PDWNC_GPIO_NUM	TOTAL_OPCTRL_NUM

#define TOTAL_GPIO_NUM          (OPCTRL0 + TOTAL_OPCTRL_NUM)//(NORMAL_GPIO_NUM + 8 + TOTAL_OPCTRL_NUM)
#define TOTAL_GPIO_IDX          ((NORMAL_GPIO_NUM + 31) >> 5)
#define GPIO_INDEX_MASK         ((1 << 5) - 1)
#define GPIO_TO_INDEX(gpio)     (((UINT32)(gpio)) >> 5)
#define GPIO_SUPPORT_INT_NUM	147// GPIO0~GPIO146
#define GPIO_EDGE_INTR_NUM      GPIO_SUPPORT_INT_NUM
#define TOTAL_EDGE_IDX          ((GPIO_EDGE_INTR_NUM + 31) >> 5)
#define EDGE_INDEX_MASK         ((1 << 5) - 1)

#define ADC2GPIO_CH_ID_MAX	7///5
#define ADC2GPIO_CH_ID_MIN	1///2

#define SERVO_GPIO1             (230)
#define SERVO_GPIO0             (SERVO_GPIO1 - 1)//not real gpio, just for judge ather sevoad_gpio function

#define MAX_PDWNC_INT_ID			32	 // Maximum value of PDWNC interrupt id
//#define MAX_PDWNC_INT_ID_2			38	 // Maximum value of PDWNC interrupt id

#define _PINT(v)		(1U << (v))


#define GPIO_IN_REG(idx)                __ckgen_readl(CKGEN_GPIOIN0+(4*(idx)))
#define GPIO_OUT_REG(idx)               __ckgen_readl(CKGEN_GPIOOUT0+(4*(idx)))
#define GPIO_OUT_WRITE(idx,val)         __ckgen_writel((CKGEN_GPIOOUT0+(4*(idx))), (val))
#define GPIO_EN_REG(idx)                __ckgen_readl(CKGEN_GPIOEN0+(4*(idx)))
#define GPIO_EN_WRITE(idx,val)          __ckgen_writel((CKGEN_GPIOEN0+(4*(idx))), (val))
#define GPIO_RISE_REG(num)			    (~ GPIO_ED2INTEN_REG(num)) & (~ GPIO_LEVINTEN_REG(num))	 & (GPIO_ENTPOL_REG(num)) &  (GPIO_EXTINTEN_REG(num))// 				(~u4IO32Read4B(REG_GPIO_ED2INTEN)) & (~u4IO32Read4B(REG_GPIO_LEVINTEN)) & u4IO32Read4B(REG_GPIO_ENTPOL) & u4IO32Read4B(REG_GPIO_EXTINTEN)
#define GPIO_FALL_REG(num)			    (~ GPIO_ED2INTEN_REG(num)) & (~ GPIO_LEVINTEN_REG(num))	 & (~ GPIO_ENTPOL_REG(num)) &  (GPIO_EXTINTEN_REG(num))						//	(~u4IO32Read4B(REG_GPIO_ED2INTEN)) & (~u4IO32Read4B(REG_GPIO_LEVINTEN)) & (~u4IO32Read4B(REG_GPIO_ENTPOL)) & u4IO32Read4B(REG_GPIO_EXTINTEN)

#define _GPIO_ED2INTEN_REG(X) 		((X==0)?CKGEN_ED2INTEN0:((X==1)?CKGEN_ED2INTEN1:((X==2)?CKGEN_ED2INTEN2:((X==3)?CKGEN_ED2INTEN3:CKGEN_ED2INTEN4))))
#define GPIO_ED2INTEN_REG(num) 		__ckgen_readl(_GPIO_ED2INTEN_REG(GPIO_TO_INDEX(num)))
#define _GPIO_LEVINTEN_REG(X) 		((X==0)?CKGEN_LEVINTEN0:((X==1)?CKGEN_LEVINTEN1:((X==2)?CKGEN_LEVINTEN2:((X==3)?CKGEN_LEVINTEN3:CKGEN_LEVINTEN4))))
#define GPIO_LEVINTEN_REG(num) 		__ckgen_readl(_GPIO_LEVINTEN_REG(GPIO_TO_INDEX(num)))
#define _GPIO_ENTPOL_REG(X) 		((X==0)?CKGEN_ENTPOL0:((X==1)?CKGEN_ENTPOL1:((X==2)?CKGEN_ENTPOL2:((X==3)?CKGEN_ENTPOL3:CKGEN_ENTPOL4))))
#define GPIO_ENTPOL_REG(num) 		__ckgen_readl(_GPIO_ENTPOL_REG(GPIO_TO_INDEX(num)))
#define _GPIO_EXTINTEN_REG(X)		((X==0)?CKGEN_EXTINTEN0:((X==1)?CKGEN_EXTINTEN1:((X==2)?CKGEN_EXTINTEN2:((X==3)?CKGEN_EXTINTEN3:CKGEN_EXTINTEN4))))
#define GPIO_EXTINTEN_REG(num)		__ckgen_readl(_GPIO_EXTINTEN_REG(GPIO_TO_INDEX(num)))
#define _GPIO_EXTINT_REG(X)			((X==0)?CKGEN_EXTINT0:((X==1)?CKGEN_EXTINT1:((X==2)?CKGEN_EXTINT2:((X==3)?CKGEN_EXTINT3:CKGEN_EXTINT4))))

#define GPIO_INTR_RISE_REG(gpio)   	(GPIO_RISE_REG(gpio) & (1U << (gpio & EDGE_INDEX_MASK)))
#define GPIO_INTR_REG(gpio)         (GPIO_EXTINTEN_REG(gpio) & (1U << (gpio & GPIO_INDEX_MASK)))
#define GPIO_INTR_FALL_REG(gpio)    (GPIO_FALL_REG(gpio) & (1U << (gpio & EDGE_INDEX_MASK)))
#define GPIO_INTR_CLR(gpio)         __ckgen_writel(_GPIO_EXTINTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_EXTINTEN_REG(gpio) & (~(1U << (gpio & EDGE_INDEX_MASK))))
#define GPIO_INTR_FALL_SET(gpio)    \
    __ckgen_writel(_GPIO_ED2INTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_ED2INTEN_REG(gpio) & (~(1U << (gpio & EDGE_INDEX_MASK)))); \
    __ckgen_writel(_GPIO_LEVINTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_LEVINTEN_REG(gpio) & (~(1U << (gpio & EDGE_INDEX_MASK)))); \
    __ckgen_writel(_GPIO_ENTPOL_REG(GPIO_TO_INDEX(gpio)), GPIO_ENTPOL_REG(gpio) & (~(1U << (gpio & EDGE_INDEX_MASK)))); \
    __ckgen_writel(_GPIO_EXTINTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_EXTINTEN_REG(gpio) | (1U << (gpio & EDGE_INDEX_MASK)));
#define GPIO_INTR_RISE_SET(gpio)    \
    __ckgen_writel(_GPIO_ED2INTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_ED2INTEN_REG(gpio) & (~(1U << (gpio & EDGE_INDEX_MASK)))); \
    __ckgen_writel(_GPIO_LEVINTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_LEVINTEN_REG(gpio) & (~(1U << (gpio & EDGE_INDEX_MASK)))); \
    __ckgen_writel(_GPIO_ENTPOL_REG(GPIO_TO_INDEX(gpio)), GPIO_ENTPOL_REG(gpio) | (1U << (gpio & EDGE_INDEX_MASK)));    \
    __ckgen_writel(_GPIO_EXTINTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_EXTINTEN_REG(gpio) | (1U << (gpio & EDGE_INDEX_MASK)));
#define GPIO_INTR_BOTH_EDGE_SET(gpio)    \
    __ckgen_writel(_GPIO_ED2INTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_ED2INTEN_REG(gpio) | (1U << (gpio & EDGE_INDEX_MASK)));    \
    __ckgen_writel(_GPIO_LEVINTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_LEVINTEN_REG(gpio) | (1U << (gpio & EDGE_INDEX_MASK)));    \
    __ckgen_writel(_GPIO_ENTPOL_REG(GPIO_TO_INDEX(gpio)), GPIO_ENTPOL_REG(gpio) | (1U << (gpio & EDGE_INDEX_MASK)));    \
    __ckgen_writel(_GPIO_EXTINTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_EXTINTEN_REG(gpio) | (1U << (gpio & EDGE_INDEX_MASK)));
#define GPIO_INTR_LEVEL_LOW_SET(gpio)    \
    __ckgen_writel(_GPIO_ED2INTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_ED2INTEN_REG(gpio) & (~(1U << (gpio & EDGE_INDEX_MASK)))); \
    __ckgen_writel(_GPIO_LEVINTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_LEVINTEN_REG(gpio) | (1U << (gpio & EDGE_INDEX_MASK))); \
    __ckgen_writel(_GPIO_ENTPOL_REG(GPIO_TO_INDEX(gpio)), GPIO_ENTPOL_REG(gpio) & (~(1U << (gpio & EDGE_INDEX_MASK)))); \
    __ckgen_writel(_GPIO_EXTINTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_EXTINTEN_REG(gpio) | (1U << (gpio & EDGE_INDEX_MASK)));
#define GPIO_INTR_LEVEL_HIGH_SET(gpio)    \
    __ckgen_writel(_GPIO_ED2INTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_ED2INTEN_REG(gpio) & (~(1U << (gpio & EDGE_INDEX_MASK)))); \
    __ckgen_writel(_GPIO_LEVINTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_LEVINTEN_REG(gpio) | (1U << (gpio & EDGE_INDEX_MASK))); \
    __ckgen_writel(_GPIO_ENTPOL_REG(GPIO_TO_INDEX(gpio)), GPIO_ENTPOL_REG(gpio) | (1U << (gpio & EDGE_INDEX_MASK)));    \
    __ckgen_writel(_GPIO_EXTINTEN_REG(GPIO_TO_INDEX(gpio)), GPIO_EXTINTEN_REG(gpio) | (1U << (gpio & EDGE_INDEX_MASK)));



#define PDWNC_GPIO_IN_REG(idx)                __pdwnc_readl(PDWNC_GPIOIN0+(4*(idx)))

#define IO_CKGEN_BASE (0)
//#define IO_CKGEN_BASE  (pCkgenIoMap)
#define CKGEN_GPIOEN0 (IO_CKGEN_BASE + 0x720)
    #define FLD_GPIO_EN0 Fld(32,0,AC_FULLDW)//[31:0]

#define CKGEN_GPIOOUT0 (IO_CKGEN_BASE + 0x700)
    #define FLD_GPIO_OUT0 Fld(32,0,AC_FULLDW)//[31:0]

#define CKGEN_GPIOIN0 (IO_CKGEN_BASE + 0x740)
    #define FLD_GPIO_IN0 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_ED2INTEN0 (IO_CKGEN_BASE + 0x760)
    #define FLD_ED2INTEN0 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_ED2INTEN1 (IO_CKGEN_BASE + 0x764)
    #define FLD_ED2INTEN1 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_ED2INTEN2 (IO_CKGEN_BASE + 0x768)
    #define FLD_ED2INTEN2 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_ED2INTEN3 (IO_CKGEN_BASE + 0x79C)
    #define FLD_ED2INTEN3 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_ED2INTEN4 (IO_CKGEN_BASE + 0x7A0)
    #define FLD_ED2INTEN4 Fld(19,0,AC_MSKDW)//[18:0]    
#define CKGEN_LEVINTEN0 (IO_CKGEN_BASE + 0x76C)
    #define FLD_LEVINTEN0 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_LEVINTEN1 (IO_CKGEN_BASE + 0x770)
    #define FLD_LEVINTEN1 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_LEVINTEN2 (IO_CKGEN_BASE + 0x774)
    #define FLD_LEVINTEN2 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_LEVINTEN3 (IO_CKGEN_BASE + 0x7A4)
    #define FLD_LEVINTEN3 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_LEVINTEN4 (IO_CKGEN_BASE + 0x7A8)
    #define FLD_LEVINTEN4 Fld(19,0,AC_MSKDW)//[18:0]
#define CKGEN_ENTPOL0 (IO_CKGEN_BASE + 0x778)
    #define FLD_INTPOL0 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_ENTPOL1 (IO_CKGEN_BASE + 0x77C)
    #define FLD_INTPOL1 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_ENTPOL2 (IO_CKGEN_BASE + 0x780)
    #define FLD_INTPOL2 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_ENTPOL3 (IO_CKGEN_BASE + 0x7AC)
    #define FLD_INTPOL3 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_ENTPOL4 (IO_CKGEN_BASE + 0x7B0)
    #define FLD_INTPOL4 Fld(19,0,AC_MSKDW)//[18:0]
#define CKGEN_EXTINTEN0 (IO_CKGEN_BASE + 0x784)
    #define FLD_INTEN0 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_EXTINTEN1 (IO_CKGEN_BASE + 0x788)
    #define FLD_INTEN1 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_EXTINTEN2 (IO_CKGEN_BASE + 0x78C)
    #define FLD_INTEN2 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_EXTINTEN3 (IO_CKGEN_BASE + 0x7B4)
    #define FLD_INTEN3 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_EXTINTEN4 (IO_CKGEN_BASE + 0x7B8)
    #define FLD_INTEN4 Fld(19,0,AC_MSKDW)//[18:0]
#define CKGEN_EXTINT0 (IO_CKGEN_BASE + 0x790)
    #define FLD_EXTINT0 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_EXTINT1 (IO_CKGEN_BASE + 0x794)
    #define FLD_EXTINT1 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_EXTINT2 (IO_CKGEN_BASE + 0x798)
    #define FLD_EXTINT2 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_EXTINT3 (IO_CKGEN_BASE + 0x7BC)
    #define FLD_EXTINT3 Fld(32,0,AC_FULLDW)//[31:0]
#define CKGEN_EXTINT4 (IO_CKGEN_BASE + 0x7C0)
    #define FLD_EXTINT4 Fld(19,0,AC_MSKDW)//[18:0]



//PDWNC GPIO related
#define IO_PDWNC_BASE 	(0)
#define PDWNC_INTSTA 	(IO_PDWNC_BASE + 0x040)
#define PDWNC_ARM_INTEN (IO_PDWNC_BASE+0x044)
#define PDWNC_INTCLR 	(IO_PDWNC_BASE+0x048)
#define PDWNC_ARM_INTEN_0 (IO_PDWNC_BASE + 0x064)
#define PDWNC_ARM_INTEN_1 (IO_PDWNC_BASE + 0x068)
#define PDWNC_EXT_INTCLR_0 (IO_PDWNC_BASE + 0x06C)
#define PDWNC_EXT_INTCLR_1 (IO_PDWNC_BASE + 0x070)
#define PDWNC_GPIOOUT0 	(IO_PDWNC_BASE + 0x640)
#define PDWNC_GPIOOUT1 	(IO_PDWNC_BASE + 0x644)
#define PDWNC_GPIOOUT2 	(IO_PDWNC_BASE + 0x648)
#define PDWNC_GPIOEN0 	(IO_PDWNC_BASE + 0x64C)
#define PDWNC_GPIOEN1 	(IO_PDWNC_BASE + 0x650)
#define PDWNC_GPIOEN2 	(IO_PDWNC_BASE + 0x654)
#define PDWNC_GPIOIN0 	(IO_PDWNC_BASE + 0x658)
#define PDWNC_GPIOIN1 	(IO_PDWNC_BASE + 0x65C)
#define PDWNC_GPIOIN2 	(IO_PDWNC_BASE + 0x660)
#define PDWNC_EXINT2ED0 (IO_PDWNC_BASE + 0x66C)
#define PDWNC_EXINTLEV0 (IO_PDWNC_BASE + 0x670)
#define PDWNC_EXINTPOL0 (IO_PDWNC_BASE + 0x674)
#define PDWNC_EXINT2ED1 (IO_PDWNC_BASE + 0x678)
#define PDWNC_EXINTLEV1 (IO_PDWNC_BASE + 0x67C)
#define PDWNC_EXINTPOL1 (IO_PDWNC_BASE + 0x680)
#define PDWNC_SRVCFG1 	(IO_PDWNC_BASE + 0x304)
#define PDWNC_SRVCST 	(IO_PDWNC_BASE + 0x390)
#define PDWNC_ADOUT0 	(IO_PDWNC_BASE + 0x394)


#define PDWNC_ADIN0 (400)
#define PDWNC_TOTAL_SERVOADC_NUM    (10)  //Oryx ServoADC channel 0 ~ 9
#define PDWNC_SRVCH_EN_CH(x)      	(1 << (x))

#endif /* __X_GPIO_HW_H__ */
