#ifndef __MTK_PHY_NEW_H
#define __MTK_PHY_NEW_H

/* include system library */
//#include <linux/gfp.h>
//#include <linux/kernel.h>
//#include <linux/slab.h>
//#include <linux/dmapool.h>
//#include <linux/delay.h>

#define CONFIG_C60802_SUPPORT
#define CONFIG_E60802_SUPPORT
#define CONFIG_U3_PHY_GPIO_SUPPORT

#define REF_CK 24

/* BASE ADDRESS DEFINE, should define this on ASIC */
#define U2_PHY_BASE			0x0
#define U3_PHYA_BASE		0x0
#define U3_PHYA_DA_BASE		0x0
#define U3_PHYD_BASE		0x0
#define U3_PHYD_B2_BASE		0x0
#define SIFSLV_CHIP_BASE	0x0
#define SIFSLV_FM_FEG_BASE	0x0

/* TYPE DEFINE */
typedef unsigned int	PHY_UINT32;
typedef int				PHY_INT32;
typedef	unsigned short	PHY_UINT16;
typedef short			PHY_INT16;
typedef unsigned char	PHY_UINT8;
typedef signed char			PHY_INT8;

typedef PHY_UINT32 PHY_LE32;

/* CONSTANT DEFINE */
#define PHY_FALSE	0
#define PHY_TRUE	1

/* MACRO DEFINE */
#define DRV_WriteReg32(addr,data)       ((*(volatile PHY_UINT32 *)(addr)) = (unsigned long)(data))
#define DRV_Reg32(addr)                 (*(volatile PHY_UINT32 *)(addr))

#define DRV_MDELAY	mdelay
#define DRV_MSLEEP	msleep
#define DRV_UDELAY	udelay
#define DRV_USLEEP	usleep

/* PHY FUNCTION DEFINE */
PHY_INT32 U3PhyWriteReg32(PHY_UINT32 addr, PHY_UINT32 data);
PHY_INT32 U3PhyReadReg32(PHY_UINT32 addr);
PHY_INT32 U3PhyWriteReg8(PHY_UINT32 addr, PHY_UINT8 data);
PHY_INT8 U3PhyReadReg8(PHY_UINT32 addr);

/* PHY GENERAL USAGE FUNC, implemented in mtk-phy.c */
PHY_INT32 U3PhyWriteField8(PHY_INT32 addr, PHY_INT32 offset, PHY_INT32 mask, PHY_INT32 value);
PHY_INT32 U3PhyWriteField32(PHY_INT32 addr, PHY_INT32 offset, PHY_INT32 mask, PHY_INT32 value);
PHY_INT32 U3PhyReadField8(PHY_INT32 addr, PHY_INT32 offset, PHY_INT32 mask);
PHY_INT32 U3PhyReadField32(PHY_INT32 addr, PHY_INT32 offset, PHY_INT32 mask);

struct u3phy_info {
	PHY_INT32 phy_version;
	PHY_INT32 phyd_version_addr;
#ifdef CONFIG_C60802_SUPPORT
	//c60802 regs reference
	struct u2phy_reg_c *u2phy_regs_c;
	struct u3phya_reg_c *u3phya_regs_c;
	struct u3phya_da_reg_c *u3phya_da_regs_c;
	struct u3phyd_reg_c *u3phyd_regs_c;
	struct u3phyd_bank2_reg_c *u3phyd_bank2_regs_c;
	struct sifslv_chip_reg_c *sifslv_chip_regs_c;
	struct sifslv_fm_feg_c *sifslv_fm_regs_c;
#endif
#ifdef CONFIG_D60802_SUPPORT
	//d60802 regs reference
	struct u2phy_reg_d *u2phy_regs_d;
	struct u3phya_reg_d *u3phya_regs_d;
	struct u3phya_da_reg_d *u3phya_da_regs_d;
	struct u3phyd_reg_d *u3phyd_regs_d;
	struct u3phyd_bank2_reg_d *u3phyd_bank2_regs_d;
	struct sifslv_chip_reg_d *sifslv_chip_regs_d;
	struct sifslv_fm_feg_d *sifslv_fm_regs_d;
#endif
#ifdef CONFIG_E60802_SUPPORT
	//e60802 regs reference
	struct u2phy_reg_e *u2phy_regs_e;
	struct u3phya_reg_e *u3phya_regs_e;
	struct u3phya_da_reg_e *u3phya_da_regs_e;
	struct u3phyd_reg_e *u3phyd_regs_e;
	struct u3phyd_bank2_reg_e *u3phyd_bank2_regs_e;
	struct sifslv_chip_reg_e *sifslv_chip_regs_e;	
	struct spllc_reg_e *spllc_regs_e;
	struct sifslv_fm_feg_e *sifslv_fm_regs_e;
#endif
};

struct u3phy_operator {
	PHY_INT32 (*init) (struct u3phy_info *info);
	PHY_INT32 (*change_pipe_phase) (struct u3phy_info *info, PHY_INT32 phy_drv, PHY_INT32 pipe_phase);
//	PHY_INT32 (*eyescan_init) (struct u3phy_info *info);
//	PHY_INT32 (*eyescan) (struct u3phy_info *info, PHY_INT32 x_t1, PHY_INT32 y_t1, PHY_INT32 x_br, PHY_INT32 y_br, PHY_INT32 delta_x, PHY_INT32 delta_y, PHY_INT32 eye_cnt, PHY_INT32 num_cnt, PHY_INT32 PI_cal_en, PHY_INT32 num_ignore_cnt);
	PHY_INT32 (*u2_connect) (struct u3phy_info *info);
	PHY_INT32 (*u2_disconnect) (struct u3phy_info *info);
	PHY_INT32 (*u2_save_current_entry) (struct u3phy_info *info);
	PHY_INT32 (*u2_save_current_recovery) (struct u3phy_info *info);
	PHY_INT32 (*u2_slew_rate_calibration) (struct u3phy_info *info);
};

#ifdef U3_PHY_LIB
#define AUTOEXT
#else
#define AUTOEXT extern
#endif

AUTOEXT struct u3phy_info *u3phy;
AUTOEXT struct u3phy_operator *u3phy_ops;

/*********eye scan required*********/

#define LO_BYTE(x)                   ((PHY_UINT8)((x) & 0xFF))
#define HI_BYTE(x)                   ((PHY_UINT8)(((x) & 0xFF00) >> 8))

typedef enum
{
  SCAN_UP,
  SCAN_DN
} enumScanDir;

struct strucScanRegion
{
  PHY_INT8 bX_tl;
  PHY_INT8 bY_tl;
  PHY_INT8 bX_br;
  PHY_INT8 bY_br;
  PHY_INT8 bDeltaX;
  PHY_INT8 bDeltaY;
};

struct strucTestCycle
{
  PHY_UINT16 wEyeCnt;
  PHY_INT8 bNumOfEyeCnt;
  PHY_INT8 bPICalEn;
  PHY_INT8 bNumOfIgnoreCnt;
};

#define ERRCNT_MAX		128
#define CYCLE_COUNT_MAX	15

/// the map resolution is 128 x 128 pts
#define MAX_X                 127
#define MAX_Y                 127
#define MIN_X                 0
#define MIN_Y                 0

PHY_INT32 eyescan_write_field8(PHY_INT32 addr, PHY_INT32 offset, PHY_INT32 len, PHY_INT32 value);
PHY_INT32 eyescan_read_field8(PHY_INT32 addr, PHY_INT32 offset, PHY_INT32 len);
PHY_INT32 eyescan_write_reg8(PHY_INT32 addr, PHY_INT32 value);
PHY_INT32 eyescan_read_reg8(PHY_INT32 addr);
PHY_INT32 u3phy_init(void);
int _U3Write_Reg(int address, int value);
int _U3Read_Reg(int address);

AUTOEXT struct strucScanRegion           _rEye1;
AUTOEXT struct strucScanRegion           _rEye2;
AUTOEXT struct strucTestCycle            _rTestCycle;
AUTOEXT PHY_INT8                      _bXcurr;
AUTOEXT PHY_INT8                      _bYcurr;
AUTOEXT enumScanDir               _eScanDir;
AUTOEXT PHY_INT8                      _fgXChged;
AUTOEXT PHY_INT8                      _bPIResult;
AUTOEXT PHY_UINT16 pwErrCnt0[CYCLE_COUNT_MAX][ERRCNT_MAX][ERRCNT_MAX];
AUTOEXT PHY_UINT16 pwErrCnt1[CYCLE_COUNT_MAX][ERRCNT_MAX][ERRCNT_MAX];

/***********************************/
#endif

