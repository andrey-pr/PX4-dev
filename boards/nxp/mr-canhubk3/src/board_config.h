/****************************************************************************
 * boards/arm/s32k3xx/mr-canhubk3/src/board_config.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/* Copyright 2022 NXP */

#pragma once

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <px4_platform_common/px4_config.h>

#include <nuttx/config.h>
#include <nuttx/compiler.h>

#include <stdint.h>

__BEGIN_DECLS

#include "hardware/s32k344_pinmux.h"
#include "s32k3xx_periphclocks.h"
#include "s32k3xx_pin.h"
#include <arch/board/board.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/

#define HRT_TIMER              1  /* FIXME */

/* MR-CANHUBK3 GPIOs ********************************************************/

/* LEDs.  The MR-CANHUBK3 has one RGB LED:
 *
 *   RedLED    PTE14  (FXIO D7 / EMIOS0 CH19)
 *   GreenLED  PTA27  (FXIO D5 / EMIOS1 CH10 / EMIOS2 CH10)
 *   BlueLED   PTE12  (FXIO D8 / EMIOS1 CH5)
 *
 * An output of '0' illuminates the LED.
 */

#define GPIO_LED_R     (PIN_EMIOS0_CH19_4)
#define GPIO_LED_G     (PIN_EMIOS1_CH10_1)
#define GPIO_LED_B     (PIN_EMIOS1_CH5_3)

/* Buttons.  The MR-CANHUBK3 supports two buttons:
 *
 *   SW1  PTD15  (EIRQ31)
 *   SW2  PTA25  (EIRQ5 / WKPU34)
 */

#define GPIO_SW1       (PIN_EIRQ31_2 | PIN_INT_BOTH)  /* PTD15 */
#define GPIO_SW2       (PIN_EIRQ5_2  | PIN_INT_BOTH)  /* PTA25 */

/*
 * I2C busses
 */
#define PX4_I2C_BUS_ONBOARD_HZ      400000
#define PX4_I2C_BUS_EXPANSION_HZ      400000

#define PX4_I2C_BUS_MTD	1

#define BOARD_NUMBER_I2C_BUSES  2

/* Count of peripheral clock user configurations */

#define NUM_OF_PERIPHERAL_CLOCKS_0 28

/* Timer I/O PWM and capture */

#define DIRECT_PWM_OUTPUT_CHANNELS  8

#define RC_SERIAL_PORT          "/dev/ttyS5"
#define RC_SERIAL_SINGLEWIRE
#define RC_SERIAL_INVERT_RX_ONLY

#define BOARD_ENABLE_CONSOLE_BUFFER

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__

/* User peripheral configuration structure 0 */

extern const struct peripheral_clock_config_s g_peripheral_clockconfig0[NUM_OF_PERIPHERAL_CLOCKS_0];

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/


/************************************************************************************
 * Name: s32k3xx_spidev_initialize
 *
 * Description:
 *   Called to configure SPI chip select GPIO pins for the NXP MR-CANHUB board.
 *
 ************************************************************************************/

void s32k3xx_spidev_initialize(void);

/************************************************************************************
 * Name: s32k3xx_spi_bus_initialize
 *
 * Description:
 *   Called to configure SPI Buses.
 *
 ************************************************************************************/

int  s32k3xx_spi_bus_initialize(void);


/****************************************************************************
 * Name: s32k3xx_bringup
 *
 * Description:
 *   Perform architecture-specific initialization
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=y :
 *     Called from board_late_initialize().
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=y && CONFIG_BOARDCTL=y :
 *     Called from the NSH library
 *
 ****************************************************************************/

int s32k3xx_bringup(void);

/****************************************************************************
 * Name: s32k3xx_i2cdev_initialize
 *
 * Description:
 *   Initialize I2C driver and register /dev/i2cN devices.
 *
 ****************************************************************************/

int s32k3xx_i2cdev_initialize(void);

/****************************************************************************
 * Name: s32k3xx_spidev_initialize
 *
 * Description:
 *   Configure chip select pins, initialize the SPI driver and register
 *   /dev/spiN devices.
 *
 ****************************************************************************/

void s32k3xx_spidev_initialize(void);

/****************************************************************************
 * Name: s32k3xx_tja1153_initialize
 *
 * Description:
 *   Initialize a TJA1153 CAN PHY connected to a FlexCAN peripheral (0-5)
 *
 ****************************************************************************/

int s32k3xx_tja1153_initialize(int bus);

/****************************************************************************
 * Name: s32k3xx_selftest
 *
 * Description:
 *   Runs basic routines to verify that all board components are up and
 *   running.  Results are send to the syslog, it is recommended to
 *   enable all output levels (error, warning and info).
 *
 ****************************************************************************/

void s32k3xx_selftest(void);

extern void board_peripheral_reset(int ms);

#include <px4_platform_common/board_common.h>

#endif /* __ASSEMBLY__ */

__END_DECLS
