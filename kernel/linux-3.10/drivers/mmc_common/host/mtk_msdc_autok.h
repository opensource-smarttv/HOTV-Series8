#ifndef _MTK_MSDC_AUTOK_H_
#define _MTK_MSDC_AUTOK_H_

#include <linux/kernel.h>
#include <mtk_msdc.h>
#include <mtk_msdc_dbg.h>

/**********************************************************
* Feature  Control Defination                             *
**********************************************************/
#define AUTOK_OFFLINE_TUNE_TX_ENABLE 0
#define AUTOK_OFFLINE_TUNE_ENABLE 0
#define HS400_OFFLINE_TUNE_ENABLE 0
#define HS200_OFFLINE_TUNE_ENABLE 0
#define HS400_DSCLK_NEED_TUNING   1
#define AUTOK_PARAM_DUMP_ENABLE   0
#define HS400_DDLSEL_SEPARATE_TUNING 1
#define HS400_KERNEL_REDUCE_DS_TUNE_TIME  1

#define E_RESULT_PASS     (0)
#define E_RESULT_CMD_TMO  (1<<0)
#define E_RESULT_RSP_CRC  (1<<1)
#define E_RESULT_DAT_CRC  (1<<2)
#define E_RESULT_DAT_TMO  (1<<3)
#define E_RESULT_W_CRC    (1<<4)
#define E_RESULT_ERR      (1<<5)
#define E_RESULT_START    (1<<6)
#define E_RESULT_PW_SMALL (1<<7)
#define E_RESULT_KEEP_OLD (1<<8)
#define E_RESULT_CMP_ERR  (1<<9)
#define E_RESULT_FATAL_ERR  (1<<10)

#define E_RESULT_MAX

#ifndef NULL
#define NULL                0
#endif
#ifndef TRUE
#define TRUE                (0 == 0)
#endif
#ifndef FALSE
#define FALSE               (0 != 0)
#endif

#define AUTOK_DBG_OFF                             0
#define AUTOK_DBG_ERROR                           1
#define AUTOK_DBG_RES                             2
#define AUTOK_DBG_WARN                            3
#define AUTOK_DBG_TRACE                           4
#define AUTOK_DBG_LOUD                            5

extern unsigned int autok_debug_level;

#define AUTOK_DBGPRINT(_level, _fmt ...)   \
({                                         \
	if (autok_debug_level >= _level) { \
		pr_err(_fmt);              \
	}                                  \
})

#define AUTOK_RAWPRINT(_fmt ...)           \
({                                         \
	pr_err(_fmt);                      \
})

enum AUTOK_PARAM {
	/* command response sample selection (MSDC_SMPL_RISING, MSDC_SMPL_FALLING) */
	CMD_EDGE,

	/* read data sample selection (MSDC_SMPL_RISING, MSDC_SMPL_FALLING) */
	RDATA_EDGE,

	/* read data async fifo out edge select */
	RD_FIFO_EDGE,

	/* write data crc status async fifo out edge select */
	WD_FIFO_EDGE,

	/* [Data Tune]CMD Pad RX Delay Line1 Control. This register is used to
	   fine-tune CMD pad macro respose latch timing. Total 32 stages[Data Tune] */
	CMD_RD_D_DLY1,

	/* [Data Tune]CMD Pad RX Delay Line1 Sel-> delay cell1 enable */
	CMD_RD_D_DLY1_SEL,

	/* [Data Tune]CMD Pad RX Delay Line2 Control. This register is used to
	   fine-tune CMD pad macro respose latch timing. Total 32 stages[Data Tune] */
	CMD_RD_D_DLY2,

	/* [Data Tune]CMD Pad RX Delay Line1 Sel-> delay cell2 enable */
	CMD_RD_D_DLY2_SEL,

	/* [Data Tune]DAT Pad RX Delay Line1 Control (for MSDC RD), Total 32 stages [Data Tune] */
	DAT_RD_D_DLY1,

	/* [Data Tune]DAT Pad RX Delay Line1 Sel-> delay cell1 enable */
	DAT_RD_D_DLY1_SEL,

	/* [Data Tune]DAT Pad RX Delay Line2 Control (for MSDC RD), Total 32 stages [Data Tune] */
	DAT_RD_D_DLY2,

	/* [Data Tune]DAT Pad RX Delay Line2 Sel-> delay cell2 enable */
	DAT_RD_D_DLY2_SEL,

#if HS400_DDLSEL_SEPARATE_TUNING
	DAT_RD_D_DDL_SEL,               /* [Data Tune]DAT Pad RX Delay Line1 separate tuning enable*/
	DAT_RD_D0_DLY1,                  /* [Data Tune]DAT0 Pad RX Delay Line1 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D1_DLY1,                  /* [Data Tune]DAT1 Pad RX Delay Line1 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D2_DLY1,                  /* [Data Tune]DAT2 Pad RX Delay Line1 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D3_DLY1,                  /* [Data Tune]DAT3 Pad RX Delay Line1 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D4_DLY1,                  /* [Data Tune]DAT4 Pad RX Delay Line1 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D5_DLY1,                  /* [Data Tune]DAT5 Pad RX Delay Line1 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D6_DLY1,                  /* [Data Tune]DAT6 Pad RX Delay Line1 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D7_DLY1,                  /* [Data Tune]DAT7 Pad RX Delay Line1 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D0_DLY2,                  /* [Data Tune]DAT0 Pad RX Delay Line2 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D1_DLY2,                  /* [Data Tune]DAT1 Pad RX Delay Line2 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D2_DLY2,                  /* [Data Tune]DAT2 Pad RX Delay Line2 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D3_DLY2,                  /* [Data Tune]DAT3 Pad RX Delay Line2 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D4_DLY2,                  /* [Data Tune]DAT4 Pad RX Delay Line2 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D5_DLY2,                  /* [Data Tune]DAT5 Pad RX Delay Line2 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D6_DLY2,                  /* [Data Tune]DAT6 Pad RX Delay Line2 Control (for MSDC RD), Total 32 stages [Data Tune]*/
	DAT_RD_D7_DLY2,                  /* [Data Tune]DAT7 Pad RX Delay Line2 Control (for MSDC RD), Total 32 stages [Data Tune]*/
#endif

	/* Internal MSDC clock phase selection. Total 8 stages, each stage can delay 1 clock period of msdc_src_ck */
	INT_DAT_LATCH_CK,

	/* DS Pad Z clk delay count, range: 0~63, Z dly1(0~31)+Z dly2(0~31) */
	EMMC50_DS_Z_DLY1,

	/* DS Pad Z clk del sel: [dly2_sel:dly1_sel] -> [0,1]: dly1 enable [1,2]:dl2 & dly1 enable ,else :no dly enable, */
	EMMC50_DS_Z_DLY1_SEL,

	/* DS Pad Z clk delay count, range: 0~63, Z dly1(0~31)+Z dly2(0~31) */
	EMMC50_DS_Z_DLY2,

	/* DS Pad Z clk del sel: [dly2_sel:dly1_sel] -> [0,1]: dly1 enable [1,2]:dl2 & dly1 enable ,else :no dly enable, */
	EMMC50_DS_Z_DLY2_SEL,

	/* DS Pad Z_DLY clk delay count, range: 0~31 */
	EMMC50_DS_ZDLY_DLY,
	TUNING_PARAM_COUNT,

	/* Data line rising/falling latch  fine tune selection in read transaction.
	   1'b0: All data line share one value indicated by MSDC_IOCON.R_D_SMPL.
	   1'b1: Each data line has its own  selection value indicated by Data line (x): MSDC_IOCON.R_D(x)_SMPL */
	READ_DATA_SMPL_SEL,

	/* Data line rising/falling latch  fine tune selection in write transaction.
	   1'b0: All data line share one value indicated by MSDC_IOCON.W_D_SMPL.
	   1'b1: Each data line has its own selection value indicated by Data line (x): MSDC_IOCON.W_D(x)_SMPL */
	WRITE_DATA_SMPL_SEL,

	/* Data line delay line fine tune selection. 1'b0: All data line share one delay
	   selection value indicated by PAD_TUNE.PAD_DAT_RD_RXDLY. 1'b1: Each data line has its
	   own delay selection value indicated by Data line (x): DAT_RD_DLY(x).DAT0_RD_DLY */
	DATA_DLYLINE_SEL,

	/* [Data Tune]CMD & DATA Pin tune Data Selection[Data Tune Sel] */
	MSDC_DAT_TUNE_SEL,

	/* [Async_FIFO Mode Sel For Write Path] */
	MSDC_WCRC_ASYNC_FIFO_SEL,

	/* [Async_FIFO Mode Sel For CMD Path] */
	MSDC_RESP_ASYNC_FIFO_SEL,

	/* Write Path Mux for emmc50 function & emmc45 function , Only emmc50 design valid,[1-eMMC50, 0-eMMC45] */
	EMMC50_WDATA_MUX_EN,

	/* CMD Path Mux for emmc50 function & emmc45 function , Only emmc50 design valid,[1-eMMC50, 0-eMMC45] */
	EMMC50_CMD_MUX_EN,

	/* write data crc status async fifo output edge select */
	EMMC50_WDATA_EDGE,

	/* CKBUF in CKGEN Delay Selection. Total 32 stages */
	CKGEN_MSDC_DLY_SEL,

	/* CMD response turn around period. The turn around cycle = CMD_RSP_TA_CNTR + 2,
	   Only for USH104 mode, this register should be set to 0 in non-UHS104 mode */
	CMD_RSP_TA_CNTR,

	/* Write data and CRC status turn around period. The turn around cycle = WRDAT_CRCS_TA_CNTR + 2,
	   Only for USH104 mode,  this register should be set to 0 in non-UHS104 mode */
	WRDAT_CRCS_TA_CNTR,

	/* CLK Pad TX Delay Control. This register is used to add delay to CLK phase. Total 32 stages */
	PAD_CLK_TXDLY,
	TOTAL_PARAM_COUNT
};

#endif  /* _MTK_MSDC_AUTOK_H_ */

