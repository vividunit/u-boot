/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2020 Rockchip Electronics Co. Ltd.
 * Author: Elaine Zhang <zhangqing@rock-chips.com>
 */

#ifndef _ASM_ARCH_CRU_RK3588_H
#define _ASM_ARCH_CRU_RK3588_H

#define MHz		1000000
#define KHz		1000
#define OSC_HZ		(24 * MHz)

#define CPU_PVTPLL_HZ	(1008 * MHz)
#define LPLL_HZ		(816 * MHz)
#define GPLL_HZ		(1188 * MHz)
#define CPLL_HZ		(1500 * MHz)
#define NPLL_HZ         (850 * MHz)
#define PPLL_HZ		(1100 * MHz)

/* RK3588 pll id */
enum rk3588_pll_id {
	B0PLL,
	B1PLL,
	LPLL,
	CPLL,
	GPLL,
	NPLL,
	V0PLL,
	AUPLL,
	PPLL,
	PLL_COUNT,
};

struct rk3588_clk_info {
	unsigned long id;
	char *name;
	bool is_cru;
};

struct rk3588_clk_priv {
	struct rk3588_cru *cru;
	struct rk3588_grf *grf;
	ulong ppll_hz;
	ulong gpll_hz;
	ulong cpll_hz;
	ulong npll_hz;
	ulong v0pll_hz;
	ulong aupll_hz;
	ulong armclk_hz;
	ulong armclk_enter_hz;
	ulong armclk_init_hz;
	bool sync_kernel;
	bool set_armclk_rate;
};

struct rk3588_pll {
	unsigned int con0;
	unsigned int con1;
	unsigned int con2;
	unsigned int con3;
	unsigned int con4;
	unsigned int reserved0[3];
};

struct rk3588_cru {
	struct rk3588_pll pll[18];
	unsigned int reserved0[16];/* Address Offset: 0x0240 */
	unsigned int mode_con00;/* Address Offset: 0x0280 */
	unsigned int reserved1[31];/* Address Offset: 0x0284 */
	unsigned int clksel_con[178]; /* Address Offset: 0x0300 */
	unsigned int reserved2[142];/* Address Offset: 0x05c8 */
	unsigned int clkgate_con[78];/* Address Offset: 0x0800 */
	unsigned int reserved3[50];/* Address Offset: 0x0938 */
	unsigned int softrst_con[78];/* Address Offset: 0x0400 */
	unsigned int reserved4[50];/* Address Offset: 0x0b38 */
	unsigned int glb_cnt_th;/* Address Offset: 0x0c00 */
	unsigned int glb_rst_st;/* Address Offset: 0x0c04 */
	unsigned int glb_srst_fst;/* Address Offset: 0x0c08 */
	unsigned int glb_srsr_snd; /* Address Offset: 0x0c0c */
	unsigned int glb_rst_con;/* Address Offset: 0x0c10 */
	unsigned int reserved5[4];/* Address Offset: 0x0c14 */
	unsigned int sdio_con[2];/* Address Offset: 0x0c24 */
	unsigned int reserved7;/* Address Offset: 0x0c2c */
	unsigned int sdmmc_con[2];/* Address Offset: 0x0c30 */
	unsigned int reserved8[48562];/* Address Offset: 0x0c38 */
	unsigned int pmuclksel_con[21]; /* Address Offset: 0x0100 */
	unsigned int reserved9[299];/* Address Offset: 0x0c38 */
	unsigned int pmuclkgate_con[9]; /* Address Offset: 0x0100 */
};

check_member(rk3588_cru, mode_con00, 0x280);
check_member(rk3588_cru, pmuclksel_con[1], 0x30304);

struct pll_rate_table {
	unsigned long rate;
	unsigned int m;
	unsigned int p;
	unsigned int s;
	unsigned int k;
};

#define RK3588_PLL_CON(x)		((x) * 0x4)
#define RK3588_MODE_CON			0x280

#define RK3588_PHP_CRU_BASE		0x8000
#define RK3588_PMU_CRU_BASE		0x30000
#define RK3588_BIGCORE0_CRU_BASE	0x50000
#define RK3588_BIGCORE1_CRU_BASE	0x52000
#define RK3588_DSU_CRU_BASE		0x58000

#define RK3588_PLL_CON(x)		((x) * 0x4)
#define RK3588_MODE_CON0		0x280
#define RK3588_CLKSEL_CON(x)		((x) * 0x4 + 0x300)
#define RK3588_CLKGATE_CON(x)		((x) * 0x4 + 0x800)
#define RK3588_SOFTRST_CON(x)		((x) * 0x4 + 0xa00)
#define RK3588_GLB_CNT_TH		0xc00
#define RK3588_GLB_SRST_FST		0xc08
#define RK3588_GLB_SRST_SND		0xc0c
#define RK3588_GLB_RST_CON		0xc10
#define RK3588_GLB_RST_ST		0xc04
#define RK3588_SDIO_CON0		0xC24
#define RK3588_SDIO_CON1		0xC28
#define RK3588_SDMMC_CON0		0xC30
#define RK3588_SDMMC_CON1		0xC34

#define RK3588_PHP_CLKGATE_CON(x)	((x) * 0x4 + RK3588_PHP_CRU_BASE + 0x800)
#define RK3588_PHP_SOFTRST_CON(x)	((x) * 0x4 + RK3588_PHP_CRU_BASE + 0xa00)

#define RK3588_PMU_PLL_CON(x)		((x) * 0x4 + RK3588_PHP_CRU_BASE)
#define RK3588_PMU_CLKSEL_CON(x)	((x) * 0x4 + RK3588_PMU_CRU_BASE + 0x300)
#define RK3588_PMU_CLKGATE_CON(x)	((x) * 0x4 + RK3588_PMU_CRU_BASE + 0x800)
#define RK3588_PMU_SOFTRST_CON(x)	((x) * 0x4 + RK3588_PMU_CRU_BASE + 0xa00)

#define RK3588_B0_PLL_CON(x)		((x) * 0x4 + RK3588_BIGCORE0_CRU_BASE)
#define RK3588_B0_PLL_MODE_CON		(RK3588_BIGCORE0_CRU_BASE + 0x280)
#define RK3588_BIGCORE0_CLKSEL_CON(x)	((x) * 0x4 + RK3588_BIGCORE0_CRU_BASE + 0x300)
#define RK3588_BIGCORE0_CLKGATE_CON(x)	((x) * 0x4 + RK3588_BIGCORE0_CRU_BASE + 0x800)
#define RK3588_BIGCORE0_SOFTRST_CON(x)	((x) * 0x4 + RK3588_BIGCORE0_CRU_BASE + 0xa00)
#define RK3588_B1_PLL_CON(x)		((x) * 0x4 + RK3588_BIGCORE1_CRU_BASE)
#define RK3588_B1_PLL_MODE_CON		(RK3588_BIGCORE1_CRU_BASE + 0x280)
#define RK3588_BIGCORE1_CLKSEL_CON(x)	((x) * 0x4 + RK3588_BIGCORE1_CRU_BASE + 0x300)
#define RK3588_BIGCORE1_CLKGATE_CON(x)	((x) * 0x4 + RK3588_BIGCORE1_CRU_BASE + 0x800)
#define RK3588_BIGCORE1_SOFTRST_CON(x)	((x) * 0x4 + RK3588_BIGCORE1_CRU_BASE + 0xa00)
#define RK3588_LPLL_CON(x)		((x) * 0x4 + RK3588_DSU_CRU_BASE)
#define RK3588_LPLL_MODE_CON		(RK3588_DSU_CRU_BASE + 0x280)
#define RK3588_DSU_CLKSEL_CON(x)	((x) * 0x4 + RK3588_DSU_CRU_BASE + 0x300)
#define RK3588_DSU_CLKGATE_CON(x)	((x) * 0x4 + RK3588_DSU_CRU_BASE + 0x800)
#define RK3588_DSU_SOFTRST_CON(x)	((x) * 0x4 + RK3588_DSU_CRU_BASE + 0xa00)

enum {
	/* CRU_CLK_SEL8_CON */
	ACLK_LOW_TOP_ROOT_SRC_SEL_SHIFT		= 14,
	ACLK_LOW_TOP_ROOT_SRC_SEL_MASK		= 1 << ACLK_LOW_TOP_ROOT_SRC_SEL_SHIFT,
	ACLK_LOW_TOP_ROOT_SRC_SEL_GPLL		= 0,
	ACLK_LOW_TOP_ROOT_SRC_SEL_CPLL,
	ACLK_LOW_TOP_ROOT_DIV_SHIFT		= 9,
	ACLK_LOW_TOP_ROOT_DIV_MASK		= 0x1f << ACLK_LOW_TOP_ROOT_DIV_SHIFT,
	PCLK_TOP_ROOT_SEL_SHIFT			= 7,
	PCLK_TOP_ROOT_SEL_MASK			= 3 << PCLK_TOP_ROOT_SEL_SHIFT,
	PCLK_TOP_ROOT_SEL_100M			= 0,
	PCLK_TOP_ROOT_SEL_50M,
	PCLK_TOP_ROOT_SEL_24M,
	ACLK_TOP_ROOT_SRC_SEL_SHIFT		= 5,
	ACLK_TOP_ROOT_SRC_SEL_MASK		= 3 << ACLK_TOP_ROOT_SRC_SEL_SHIFT,
	ACLK_TOP_ROOT_SRC_SEL_GPLL		= 0,
	ACLK_TOP_ROOT_SRC_SEL_CPLL,
	ACLK_TOP_ROOT_SRC_SEL_AUPLL,
	ACLK_TOP_ROOT_DIV_SHIFT			= 0,
	ACLK_TOP_ROOT_DIV_MASK			= 0x1f << ACLK_TOP_ROOT_DIV_SHIFT,

	/* CRU_CLK_SEL9_CON */
	ACLK_TOP_S400_SEL_SHIFT			= 8,
	ACLK_TOP_S400_SEL_MASK			= 3 << ACLK_TOP_S400_SEL_SHIFT,
	ACLK_TOP_S400_SEL_400M			= 0,
	ACLK_TOP_S400_SEL_200M,
	ACLK_TOP_S200_SEL_SHIFT			= 6,
	ACLK_TOP_S200_SEL_MASK			= 3 << ACLK_TOP_S200_SEL_SHIFT,
	ACLK_TOP_S200_SEL_200M			= 0,
	ACLK_TOP_S200_SEL_100M,

	/* CRU_CLK_SEL38_CON */
	CLK_I2C8_SEL_SHIFT			= 13,
	CLK_I2C8_SEL_MASK			= 1 << CLK_I2C8_SEL_SHIFT,
	CLK_I2C7_SEL_SHIFT			= 12,
	CLK_I2C7_SEL_MASK			= 1 << CLK_I2C7_SEL_SHIFT,
	CLK_I2C6_SEL_SHIFT			= 11,
	CLK_I2C6_SEL_MASK			= 1 << CLK_I2C6_SEL_SHIFT,
	CLK_I2C5_SEL_SHIFT			= 10,
	CLK_I2C5_SEL_MASK			= 1 << CLK_I2C5_SEL_SHIFT,
	CLK_I2C4_SEL_SHIFT			= 9,
	CLK_I2C4_SEL_MASK			= 1 << CLK_I2C4_SEL_SHIFT,
	CLK_I2C3_SEL_SHIFT			= 8,
	CLK_I2C3_SEL_MASK			= 1 << CLK_I2C3_SEL_SHIFT,
	CLK_I2C2_SEL_SHIFT			= 7,
	CLK_I2C2_SEL_MASK			= 1 << CLK_I2C2_SEL_SHIFT,
	CLK_I2C1_SEL_SHIFT			= 6,
	CLK_I2C1_SEL_MASK			= 1 << CLK_I2C1_SEL_SHIFT,
	ACLK_BUS_ROOT_SEL_SHIFT			= 5,
	ACLK_BUS_ROOT_SEL_MASK			= 3 << ACLK_BUS_ROOT_SEL_SHIFT,
	ACLK_BUS_ROOT_SEL_GPLL			= 0,
	ACLK_BUS_ROOT_SEL_CPLL,
	ACLK_BUS_ROOT_DIV_SHIFT			= 0,
	ACLK_BUS_ROOT_DIV_MASK			= 0x1f << ACLK_BUS_ROOT_DIV_SHIFT,

	/* CRU_CLK_SEL40_CON */
	CLK_SARADC_SEL_SHIFT			= 14,
	CLK_SARADC_SEL_MASK			= 0x1 << CLK_SARADC_SEL_SHIFT,
	CLK_SARADC_SEL_GPLL			= 0,
	CLK_SARADC_SEL_24M,
	CLK_SARADC_DIV_SHIFT			= 6,
	CLK_SARADC_DIV_MASK			= 0xff << CLK_SARADC_DIV_SHIFT,

	/* CRU_CLK_SEL41_CON */
	CLK_UART_SRC_SEL_SHIFT			= 14,
	CLK_UART_SRC_SEL_MASK			= 0x1 << CLK_UART_SRC_SEL_SHIFT,
	CLK_UART_SRC_SEL_GPLL			= 0,
	CLK_UART_SRC_SEL_CPLL,
	CLK_UART_SRC_DIV_SHIFT			= 9,
	CLK_UART_SRC_DIV_MASK			= 0x1f << CLK_UART_SRC_DIV_SHIFT,
	CLK_TSADC_SEL_SHIFT			= 8,
	CLK_TSADC_SEL_MASK			= 0x1 << CLK_TSADC_SEL_SHIFT,
	CLK_TSADC_SEL_GPLL			= 0,
	CLK_TSADC_SEL_24M,
	CLK_TSADC_DIV_SHIFT			= 0,
	CLK_TSADC_DIV_MASK			= 0xff << CLK_TSADC_DIV_SHIFT,

	/* CRU_CLK_SEL42_CON */
	CLK_UART_FRAC_NUMERATOR_SHIFT		= 16,
	CLK_UART_FRAC_NUMERATOR_MASK		= 0xffff << 16,
	CLK_UART_FRAC_DENOMINATOR_SHIFT		= 0,
	CLK_UART_FRAC_DENOMINATOR_MASK		= 0xffff,

	/* CRU_CLK_SEL43_CON */
	CLK_UART_SEL_SHIFT			= 0,
	CLK_UART_SEL_MASK			= 0x3 << CLK_UART_SEL_SHIFT,
	CLK_UART_SEL_SRC			= 0,
	CLK_UART_SEL_FRAC,
	CLK_UART_SEL_XIN24M,

	/* CRU_CLK_SEL59_CON */
	CLK_PWM2_SEL_SHIFT			= 14,
	CLK_PWM2_SEL_MASK			= 3 << CLK_PWM2_SEL_SHIFT,
	CLK_PWM1_SEL_SHIFT			= 12,
	CLK_PWM1_SEL_MASK			= 3 << CLK_PWM1_SEL_SHIFT,
	CLK_SPI4_SEL_SHIFT			= 10,
	CLK_SPI4_SEL_MASK			= 3 << CLK_SPI4_SEL_SHIFT,
	CLK_SPI3_SEL_SHIFT			= 8,
	CLK_SPI3_SEL_MASK			= 3 << CLK_SPI3_SEL_SHIFT,
	CLK_SPI2_SEL_SHIFT			= 6,
	CLK_SPI2_SEL_MASK			= 3 << CLK_SPI2_SEL_SHIFT,
	CLK_SPI1_SEL_SHIFT			= 4,
	CLK_SPI1_SEL_MASK			= 3 << CLK_SPI1_SEL_SHIFT,
	CLK_SPI0_SEL_SHIFT			= 2,
	CLK_SPI0_SEL_MASK			= 3 << CLK_SPI0_SEL_SHIFT,
	CLK_SPI_SEL_200M			= 0,
	CLK_SPI_SEL_150M,
	CLK_SPI_SEL_24M,

	/* CRU_CLK_SEL60_CON */
	CLK_PWM3_SEL_SHIFT			= 0,
	CLK_PWM3_SEL_MASK			= 3 << CLK_PWM3_SEL_SHIFT,
	CLK_PWM_SEL_100M			= 0,
	CLK_PWM_SEL_50M,
	CLK_PWM_SEL_24M,

	/* CRU_CLK_SEL62_CON */
	DCLK_DECOM_SEL_SHIFT			= 5,
	DCLK_DECOM_SEL_MASK			= 1 << DCLK_DECOM_SEL_SHIFT,
	DCLK_DECOM_SEL_GPLL			= 0,
	DCLK_DECOM_SEL_SPLL,
	DCLK_DECOM_DIV_SHIFT			= 0,
	DCLK_DECOM_DIV_MASK			= 0x1F << DCLK_DECOM_DIV_SHIFT,

	/* CRU_CLK_SEL77_CON */
	CCLK_EMMC_SEL_SHIFT			= 14,
	CCLK_EMMC_SEL_MASK			= 3 << CCLK_EMMC_SEL_SHIFT,
	CCLK_EMMC_SEL_GPLL			= 0,
	CCLK_EMMC_SEL_CPLL,
	CCLK_EMMC_SEL_24M,
	CCLK_EMMC_DIV_SHIFT			= 8,
	CCLK_EMMC_DIV_MASK			= 0x3f << CCLK_EMMC_DIV_SHIFT,

	/* CRU_CLK_SEL78_CON */
	SCLK_SFC_SEL_SHIFT			= 12,
	SCLK_SFC_SEL_MASK			= 3 << SCLK_SFC_SEL_SHIFT,
	SCLK_SFC_SEL_GPLL			= 0,
	SCLK_SFC_SEL_CPLL,
	SCLK_SFC_SEL_24M,
	SCLK_SFC_DIV_SHIFT			= 6,
	SCLK_SFC_DIV_MASK			= 0x3f << SCLK_SFC_DIV_SHIFT,
	BCLK_EMMC_SEL_SHIFT			= 5,
	BCLK_EMMC_SEL_MASK			= 1 << BCLK_EMMC_SEL_SHIFT,
	BCLK_EMMC_SEL_GPLL			= 0,
	BCLK_EMMC_SEL_CPLL,
	BCLK_EMMC_DIV_SHIFT			= 0,
	BCLK_EMMC_DIV_MASK			= 0x1f << BCLK_EMMC_DIV_SHIFT,

	/* CRU_CLK_SEL81_CON */
	CLK_GMAC1_PTP_SEL_SHIFT			= 13,
	CLK_GMAC1_PTP_SEL_MASK			= 1 << CLK_GMAC1_PTP_SEL_SHIFT,
	CLK_GMAC1_PTP_SEL_CPLL			= 0,
	CLK_GMAC1_PTP_DIV_SHIFT			= 7,
	CLK_GMAC1_PTP_DIV_MASK			= 0x3f << CLK_GMAC1_PTP_DIV_SHIFT,
	CLK_GMAC0_PTP_SEL_SHIFT			= 6,
	CLK_GMAC0_PTP_SEL_MASK			= 1 << CLK_GMAC0_PTP_SEL_SHIFT,
	CLK_GMAC0_PTP_SEL_CPLL			= 0,
	CLK_GMAC0_PTP_DIV_SHIFT			= 0,
	CLK_GMAC0_PTP_DIV_MASK			= 0x3f << CLK_GMAC0_PTP_DIV_SHIFT,

	/* CRU_CLK_SEL83_CON */
	CLK_GMAC_125M_SEL_SHIFT			= 15,
	CLK_GMAC_125M_SEL_MASK			= 1 << CLK_GMAC_125M_SEL_SHIFT,
	CLK_GMAC_125M_SEL_GPLL			= 0,
	CLK_GMAC_125M_SEL_CPLL,
	CLK_GMAC_125M_DIV_SHIFT			= 8,
	CLK_GMAC_125M_DIV_MASK			= 0x7f << CLK_GMAC_125M_DIV_SHIFT,

	/* CRU_CLK_SEL84_CON */
	CLK_GMAC_50M_SEL_SHIFT			= 7,
	CLK_GMAC_50M_SEL_MASK			= 1 << CLK_GMAC_50M_SEL_SHIFT,
	CLK_GMAC_50M_SEL_GPLL			= 0,
	CLK_GMAC_50M_SEL_CPLL,
	CLK_GMAC_50M_DIV_SHIFT			= 0,
	CLK_GMAC_50M_DIV_MASK			= 0x7f << CLK_GMAC_50M_DIV_SHIFT,

	/* CRU_CLK_SEL110_CON */
	HCLK_VOP_ROOT_SEL_SHIFT			= 10,
	HCLK_VOP_ROOT_SEL_MASK			= 3 << HCLK_VOP_ROOT_SEL_SHIFT,
	HCLK_VOP_ROOT_SEL_200M			= 0,
	HCLK_VOP_ROOT_SEL_100M,
	HCLK_VOP_ROOT_SEL_50M,
	HCLK_VOP_ROOT_SEL_24M,
	ACLK_VOP_LOW_ROOT_SEL_SHIFT		= 8,
	ACLK_VOP_LOW_ROOT_SEL_MASK		= 3 << ACLK_VOP_LOW_ROOT_SEL_SHIFT,
	ACLK_VOP_LOW_ROOT_SEL_400M		= 0,
	ACLK_VOP_LOW_ROOT_SEL_200M,
	ACLK_VOP_LOW_ROOT_SEL_100M,
	ACLK_VOP_LOW_ROOT_SEL_24M,
	ACLK_VOP_ROOT_SEL_SHIFT			= 5,
	ACLK_VOP_ROOT_SEL_MASK			= 7 << ACLK_VOP_ROOT_SEL_SHIFT,
	ACLK_VOP_ROOT_SEL_GPLL			= 0,
	ACLK_VOP_ROOT_SEL_CPLL,
	ACLK_VOP_ROOT_SEL_AUPLL,
	ACLK_VOP_ROOT_SEL_NPLL,
	ACLK_VOP_ROOT_SEL_SPLL,
	ACLK_VOP_ROOT_DIV_SHIFT			= 0,
	ACLK_VOP_ROOT_DIV_MASK			= 0x1f << ACLK_VOP_ROOT_DIV_SHIFT,

	/* CRU_CLK_SEL111_CON */
	DCLK1_VOP_SRC_SEL_SHIFT			= 14,
	DCLK1_VOP_SRC_SEL_MASK			= 3 << DCLK1_VOP_SRC_SEL_SHIFT,
	DCLK1_VOP_SRC_DIV_SHIFT			= 9,
	DCLK1_VOP_SRC_DIV_MASK			= 0x1f << DCLK1_VOP_SRC_DIV_SHIFT,
	DCLK0_VOP_SRC_SEL_SHIFT			= 7,
	DCLK0_VOP_SRC_SEL_MASK			= 3 << DCLK0_VOP_SRC_SEL_SHIFT,
	DCLK_VOP_SRC_SEL_GPLL			= 0,
	DCLK_VOP_SRC_SEL_CPLL,
	DCLK_VOP_SRC_SEL_V0PLL,
	DCLK_VOP_SRC_SEL_AUPLL,
	DCLK0_VOP_SRC_DIV_SHIFT			= 0,
	DCLK0_VOP_SRC_DIV_MASK			= 0x7f << DCLK0_VOP_SRC_DIV_SHIFT,

	/* CRU_CLK_SEL112_CON */
	DCLK2_VOP_SEL_SHIFT			= 11,
	DCLK2_VOP_SEL_MASK			= 3 << DCLK2_VOP_SEL_SHIFT,
	DCLK1_VOP_SEL_SHIFT			= 9,
	DCLK1_VOP_SEL_MASK			= 3 << DCLK1_VOP_SEL_SHIFT,
	DCLK0_VOP_SEL_SHIFT			= 7,
	DCLK0_VOP_SEL_MASK			= 3 << DCLK0_VOP_SEL_SHIFT,
	DCLK2_VOP_SRC_SEL_SHIFT			= 5,
	DCLK2_VOP_SRC_SEL_MASK			= 3 << DCLK2_VOP_SRC_SEL_SHIFT,
	DCLK2_VOP_SRC_DIV_SHIFT			= 0,
	DCLK2_VOP_SRC_DIV_MASK			= 0x1f << DCLK2_VOP_SRC_DIV_SHIFT,

	/* CRU_CLK_SEL113_CON */
	DCLK3_VOP_SRC_SEL_SHIFT			= 7,
	DCLK3_VOP_SRC_SEL_MASK			= 3 << DCLK3_VOP_SRC_SEL_SHIFT,
	DCLK3_VOP_SRC_DIV_SHIFT			= 0,
	DCLK3_VOP_SRC_DIV_MASK			= 0x7f << DCLK3_VOP_SRC_DIV_SHIFT,

	/* CRU_CLK_SEL117_CON */
	CLK_AUX16MHZ_1_DIV_SHIFT		= 8,
	CLK_AUX16MHZ_1_DIV_MASK			= 0xff << CLK_AUX16MHZ_1_DIV_SHIFT,
	CLK_AUX16MHZ_0_DIV_SHIFT		= 0,
	CLK_AUX16MHZ_0_DIV_MASK			= 0xff << CLK_AUX16MHZ_0_DIV_SHIFT,

	/* CRU_CLK_SEL165_CON */
	PCLK_CENTER_ROOT_SEL_SHIFT		= 6,
	PCLK_CENTER_ROOT_SEL_MASK		= 3 << PCLK_CENTER_ROOT_SEL_SHIFT,
	PCLK_CENTER_ROOT_SEL_200M		= 0,
	PCLK_CENTER_ROOT_SEL_100M,
	PCLK_CENTER_ROOT_SEL_50M,
	PCLK_CENTER_ROOT_SEL_24M,
	HCLK_CENTER_ROOT_SEL_SHIFT		= 4,
	HCLK_CENTER_ROOT_SEL_MASK		= 3 << HCLK_CENTER_ROOT_SEL_SHIFT,
	HCLK_CENTER_ROOT_SEL_400M		= 0,
	HCLK_CENTER_ROOT_SEL_200M,
	HCLK_CENTER_ROOT_SEL_100M,
	HCLK_CENTER_ROOT_SEL_24M,
	ACLK_CENTER_LOW_ROOT_SEL_SHIFT		= 2,
	ACLK_CENTER_LOW_ROOT_SEL_MASK		= 3 << ACLK_CENTER_LOW_ROOT_SEL_SHIFT,
	ACLK_CENTER_LOW_ROOT_SEL_500M		= 0,
	ACLK_CENTER_LOW_ROOT_SEL_250M,
	ACLK_CENTER_LOW_ROOT_SEL_100M,
	ACLK_CENTER_LOW_ROOT_SEL_24M,
	ACLK_CENTER_ROOT_SEL_SHIFT		= 0,
	ACLK_CENTER_ROOT_SEL_MASK		= 3 << ACLK_CENTER_ROOT_SEL_SHIFT,
	ACLK_CENTER_ROOT_SEL_700M		= 0,
	ACLK_CENTER_ROOT_SEL_400M,
	ACLK_CENTER_ROOT_SEL_200M,
	ACLK_CENTER_ROOT_SEL_24M,

	/* CRU_CLK_SEL172_CON */
	CCLK_SDIO_SRC_SEL_SHIFT			= 8,
	CCLK_SDIO_SRC_SEL_MASK			= 3 << CCLK_SDIO_SRC_SEL_SHIFT,
	CCLK_SDIO_SRC_SEL_GPLL			= 0,
	CCLK_SDIO_SRC_SEL_CPLL,
	CCLK_SDIO_SRC_SEL_24M,
	CCLK_SDIO_SRC_DIV_SHIFT			= 2,
	CCLK_SDIO_SRC_DIV_MASK			= 0x3f << CCLK_SDIO_SRC_DIV_SHIFT,

	/* CRU_CLK_SEL176_CON */
	CLK_PCIE_PHY1_PLL_DIV_SHIFT		= 6,
	CLK_PCIE_PHY1_PLL_DIV_MASK		= 0x3f << CLK_PCIE_PHY1_PLL_DIV_SHIFT,
	CLK_PCIE_PHY0_PLL_DIV_SHIFT		= 0,
	CLK_PCIE_PHY0_PLL_DIV_MASK		= 0x3f << CLK_PCIE_PHY0_PLL_DIV_SHIFT,

	/* CRU_CLK_SEL177_CON */
	CLK_PCIE_PHY2_REF_SEL_SHIFT		= 8,
	CLK_PCIE_PHY2_REF_SEL_MASK		= 1 << CLK_PCIE_PHY2_REF_SEL_SHIFT,
	CLK_PCIE_PHY1_REF_SEL_SHIFT		= 7,
	CLK_PCIE_PHY1_REF_SEL_MASK		= 1 << CLK_PCIE_PHY1_REF_SEL_SHIFT,
	CLK_PCIE_PHY0_REF_SEL_SHIFT		= 6,
	CLK_PCIE_PHY0_REF_SEL_MASK		= 1 << CLK_PCIE_PHY0_REF_SEL_SHIFT,
	CLK_PCIE_PHY_REF_SEL_24M		= 0,
	CLK_PCIE_PHY_REF_SEL_PPLL,
	CLK_PCIE_PHY2_PLL_DIV_SHIFT		= 0,
	CLK_PCIE_PHY2_PLL_DIV_MASK		= 0x3f << CLK_PCIE_PHY2_PLL_DIV_SHIFT,

	/* PMUCRU_CLK_SEL2_CON */
	CLK_PMU1PWM_SEL_SHIFT			= 9,
	CLK_PMU1PWM_SEL_MASK			= 3 << CLK_PMU1PWM_SEL_SHIFT,

	/* PMUCRU_CLK_SEL3_CON */
	CLK_I2C0_SEL_SHIFT			= 6,
	CLK_I2C0_SEL_MASK			= 1 << CLK_I2C0_SEL_SHIFT,
	CLK_I2C_SEL_200M			= 0,
	CLK_I2C_SEL_100M,
};
#endif
