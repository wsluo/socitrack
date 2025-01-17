// Datasheet: https://www.st.com/resource/en/datasheet/lis3mdl.pdf
#ifndef __MAGNETOMETER_HEADER_H
#define __MAGNETOMETER_HEADER_H

// Header inclusions ---------------------------------------------------------------------------------------------------

#include "ble_config.h"


// LIS3MDL register definitions ----------------------------------------------------------------------------------------
/*
#define LIS3MDL_I2C_ADD_L               0x39U
#define LIS3MDL_I2C_ADD_H               0x3DU
#define LIS3MDL_ID                      0x3DU
#define LIS3MDL_WHO_AM_I                0x0FU

#define LIS3MDL_CTRL_REG1               0x20U
#define LIS3MDL_CTRL_REG2               0x21U
#define LIS3MDL_CTRL_REG3               0x22U
#define LIS3MDL_CTRL_REG4               0x23U
#define LIS3MDL_CTRL_REG5               0x24U
#define LIS3MDL_STATUS_REG              0x27U

#define LIS3MDL_OUT_X_L                 0x28U
#define LIS3MDL_OUT_X_H                 0x29U
#define LIS3MDL_OUT_Y_L                 0x2AU
#define LIS3MDL_OUT_Y_H                 0x2BU
#define LIS3MDL_OUT_Z_L                 0x2CU
#define LIS3MDL_OUT_Z_H                 0x2DU
#define LIS3MDL_TEMP_OUT_L              0x2EU
#define LIS3MDL_TEMP_OUT_H              0x2FU
#define LIS3MDL_INT_CFG                 0x30U
#define LIS3MDL_INT_SRC                 0x31U
#define LIS3MDL_INT_THS_L               0x32U
#define LIS3MDL_INT_THS_H               0x33U

#define LIS2DW12_WHO_AM_I               0x0F
#define LIS2DW12_CTRL1                  0x20
#define LIS2DW12_CTRL2                  0x21
#define LIS2DW12_CTRL3                  0x22
#define LIS2DW12_CTRL4_INT1             0x23
#define LIS2DW12_CTRL5_INT2             0x24
#define LIS2DW12_CTRL6                  0x25
#define LIS2DW12_CTRL7                  0x3F
#define LIS2DW12_STATUS                 0x27
#define LIS2DW12_OUT_X_L                0x28
#define LIS2DW12_FIFO_CTRL              0x2E
#define LIS2DW12_WAKE_UP_THS            0x34
#define LIS2DW12_WAKE_UP_DUR            0x35

#define LIS2DW12_SPI_READ               0x80
#define LIS2DW12_SPI_WRITE              0x7F


// LIS3MDL enums and structs -------------------------------------------------------------------------------------------

typedef nrfx_err_t (*write_reg_ptr)(uint8_t, uint8_t *, uint16_t);
typedef nrfx_err_t (*read_reg_ptr)(uint8_t, uint8_t *, uint16_t);

typedef enum
{
   LIS3MDL_LP_Hz625      = 0x00,
   LIS3MDL_LP_1kHz       = 0x01,
   LIS3MDL_MP_560Hz      = 0x11,
   LIS3MDL_HP_300Hz      = 0x21,
   LIS3MDL_UHP_155Hz     = 0x31,

   LIS3MDL_LP_1Hz25      = 0x02,
   LIS3MDL_LP_2Hz5       = 0x04,
   LIS3MDL_LP_5Hz        = 0x06,
   LIS3MDL_LP_10Hz       = 0x08,
   LIS3MDL_LP_20Hz       = 0x0A,
   LIS3MDL_LP_40Hz       = 0x0C,
   LIS3MDL_LP_80Hz       = 0x0E,

   LIS3MDL_MP_1Hz25      = 0x12,
   LIS3MDL_MP_2Hz5       = 0x14,
   LIS3MDL_MP_5Hz        = 0x16,
   LIS3MDL_MP_10Hz       = 0x18,
   LIS3MDL_MP_20Hz       = 0x1A,
   LIS3MDL_MP_40Hz       = 0x1C,
   LIS3MDL_MP_80Hz       = 0x1E,

   LIS3MDL_HP_1Hz25      = 0x22,
   LIS3MDL_HP_2Hz5       = 0x24,
   LIS3MDL_HP_5Hz        = 0x26,
   LIS3MDL_HP_10Hz       = 0x28,
   LIS3MDL_HP_20Hz       = 0x2A,
   LIS3MDL_HP_40Hz       = 0x2C,
   LIS3MDL_HP_80Hz       = 0x2E,

   LIS3MDL_UHP_1Hz25     = 0x32,
   LIS3MDL_UHP_2Hz5      = 0x34,
   LIS3MDL_UHP_5Hz       = 0x36,
   LIS3MDL_UHP_10Hz      = 0x38,
   LIS3MDL_UHP_20Hz      = 0x3A,
   LIS3MDL_UHP_40Hz      = 0x3C,
   LIS3MDL_UHP_80Hz      = 0x3E,
} lis3mdl_om_t;

typedef enum
{
   LIS3MDL_4_GAUSS   = 0,
   LIS3MDL_8_GAUSS   = 1,
   LIS3MDL_12_GAUSS  = 2,
   LIS3MDL_16_GAUSS  = 3,
} lis3mdl_fs_t;

typedef enum
{
   LIS3MDL_CONTINUOUS_MODE  = 0,
   LIS3MDL_SINGLE_TRIGGER   = 1,
   LIS3MDL_POWER_DOWN       = 2,
} lis3mdl_md_t;

typedef enum
{
   LIS3MDL_LSB_AT_LOW_ADD  = 0,
   LIS3MDL_MSB_AT_LOW_ADD  = 1,
} lis3mdl_ble_t;

typedef enum {
   LIS3MDL_INT_PULSED   = 0,
   LIS3MDL_INT_LATCHED  = 1,
} lis3mdl_lir_t;

typedef enum {
   LIS3MDL_ACTIVE_HIGH  = 0,
   LIS3MDL_ACTIVE_LOW   = 1,
} lis3mdl_iea_t;

typedef enum {
   LIS3MDL_SPI_4_WIRE   = 0,
   LIS3MDL_SPI_3_WIRE   = 1,
} lis3mdl_sim_t;

typedef struct
{
   uint8_t bit0 :1;
   uint8_t bit1 :1;
   uint8_t bit2 :1;
   uint8_t bit3 :1;
   uint8_t bit4 :1;
   uint8_t bit5 :1;
   uint8_t bit6 :1;
   uint8_t bit7 :1;
} bitwise_t;

typedef struct
{
   uint8_t address;
   uint8_t data;
} ucf_line_t;

typedef struct
{
   uint8_t st              : 1;
   uint8_t om              : 6; // om + do + fast_odr -> om
   uint8_t temp_en         : 1;
} lis3mdl_ctrl_reg1_t;

typedef struct
{
   uint8_t not_used_01     : 2;
   uint8_t soft_rst        : 1;
   uint8_t reboot          : 1;
   uint8_t not_used_02     : 1;
   uint8_t fs              : 2;
   uint8_t not_used_03     : 1;
} lis3mdl_ctrl_reg2_t;

typedef struct
{
   uint8_t md              : 2;
   uint8_t sim             : 1;
   uint8_t not_used_01     : 2;
   uint8_t lp              : 1;
   uint8_t not_used_02     : 2;
} lis3mdl_ctrl_reg3_t;

typedef struct
{
   uint8_t not_used_01     : 1;
   uint8_t ble             : 1;
   uint8_t omz             : 2;
   uint8_t not_used_02     : 4;
} lis3mdl_ctrl_reg4_t;

typedef struct
{
   uint8_t not_used_01     : 6;
   uint8_t bdu             : 1;
   uint8_t fast_read       : 1;
} lis3mdl_ctrl_reg5_t;

typedef struct
{
   uint8_t xda             : 1;
   uint8_t yda             : 1;
   uint8_t zda             : 1;
   uint8_t zyxda           : 1;
   uint8_t _xor            : 1;
   uint8_t yor             : 1;
   uint8_t zor             : 1;
   uint8_t zyxor           : 1;
} lis3mdl_status_reg_t;

typedef struct
{
   uint8_t ien             : 1;
   uint8_t lir             : 1;
   uint8_t iea             : 1;
   uint8_t not_used_01     : 2;
   uint8_t zien            : 1;
   uint8_t yien            : 1;
   uint8_t xien            : 1;
} lis3mdl_int_cfg_t;

typedef struct
{
   uint8_t int_            : 1;
   uint8_t mroi            : 1;
   uint8_t nth_z           : 1;
   uint8_t nth_y           : 1;
   uint8_t nth_x           : 1;
   uint8_t pth_z           : 1;
   uint8_t pth_y           : 1;
   uint8_t pth_x           : 1;
} lis3mdl_int_src_t;

typedef union
{
   lis3mdl_ctrl_reg1_t      ctrl_reg1;
   lis3mdl_ctrl_reg2_t      ctrl_reg2;
   lis3mdl_ctrl_reg3_t      ctrl_reg3;
   lis3mdl_ctrl_reg4_t      ctrl_reg4;
   lis3mdl_ctrl_reg5_t      ctrl_reg5;
   lis3mdl_status_reg_t     status_reg;
   lis3mdl_int_cfg_t        int_cfg;
   lis3mdl_int_src_t        int_src;
   bitwise_t                bitwise;
   uint8_t                  byte;
} lis3mdl_reg_t;


// LIS3MDL driver functions --------------------------------------------------------------------------------------------

float lis3mdl_from_fs4_to_gauss(int16_t lsb);
float lis3mdl_from_fs8_to_gauss(int16_t lsb);
float lis3mdl_from_fs12_to_gauss(int16_t lsb);
float lis3mdl_from_fs16_to_gauss(int16_t lsb);
float lis3mdl_from_lsb_to_celsius(int16_t lsb);

nrfx_err_t lis3mdl_data_rate_set(lis3mdl_om_t val);
nrfx_err_t lis3mdl_data_rate_get(lis3mdl_om_t *val);
nrfx_err_t lis3mdl_temperature_meas_set(uint8_t val);
nrfx_err_t lis3mdl_temperature_meas_get(uint8_t *val);
nrfx_err_t lis3mdl_full_scale_set(lis3mdl_fs_t val);
nrfx_err_t lis3mdl_full_scale_get(lis3mdl_fs_t *val);
nrfx_err_t lis3mdl_operating_mode_set(lis3mdl_md_t val);
nrfx_err_t lis3mdl_operating_mode_get(lis3mdl_md_t *val);
nrfx_err_t lis3mdl_fast_low_power_set(uint8_t val);
nrfx_err_t lis3mdl_fast_low_power_get(uint8_t *val);
nrfx_err_t lis3mdl_block_data_update_set(uint8_t val);
nrfx_err_t lis3mdl_block_data_update_get(uint8_t *val);
nrfx_err_t lis3mdl_high_part_cycle_set(uint8_t val);
nrfx_err_t lis3mdl_high_part_cycle_get(uint8_t *val);
nrfx_err_t lis3mdl_mag_data_ready_get(uint8_t *val);
nrfx_err_t lis3mdl_mag_data_ovr_get(uint8_t *val);
nrfx_err_t lis3mdl_magnetic_raw_get(int16_t *val);
nrfx_err_t lis3mdl_temperature_raw_get(int16_t *val);
nrfx_err_t lis3mdl_device_id_get(uint8_t *buff);
nrfx_err_t lis3mdl_self_test_set(uint8_t val);
nrfx_err_t lis3mdl_self_test_get(uint8_t *val);
nrfx_err_t lis3mdl_reset_set(uint8_t val);
nrfx_err_t lis3mdl_reset_get(uint8_t *val);
nrfx_err_t lis3mdl_boot_set(uint8_t val);
nrfx_err_t lis3mdl_boot_get(uint8_t *val);
nrfx_err_t lis3mdl_data_format_set(lis3mdl_ble_t val);
nrfx_err_t lis3mdl_data_format_get(lis3mdl_ble_t *val);
nrfx_err_t lis3mdl_status_get(lis3mdl_status_reg_t *val);
nrfx_err_t lis3mdl_int_config_set(lis3mdl_int_cfg_t *val);
nrfx_err_t lis3mdl_int_config_get(lis3mdl_int_cfg_t *val);
nrfx_err_t lis3mdl_int_generation_set(uint8_t val);
nrfx_err_t lis3mdl_int_generation_get(uint8_t *val);
nrfx_err_t lis3mdl_int_notification_mode_set(lis3mdl_lir_t val);
nrfx_err_t lis3mdl_int_notification_mode_get(lis3mdl_lir_t *val);
nrfx_err_t lis3mdl_int_polarity_set(lis3mdl_iea_t val);
nrfx_err_t lis3mdl_int_polarity_get(lis3mdl_iea_t *val);
nrfx_err_t lis3mdl_int_on_z_ax_set(uint8_t val);
nrfx_err_t lis3mdl_int_on_z_ax_get(uint8_t *val);
nrfx_err_t lis3mdl_int_on_y_ax_set(uint8_t val);
nrfx_err_t lis3mdl_int_on_y_ax_get(uint8_t *val);
nrfx_err_t lis3mdl_int_on_x_ax_set(uint8_t val);
nrfx_err_t lis3mdl_int_on_x_ax_get(uint8_t *val);
nrfx_err_t lis3mdl_int_source_get(lis3mdl_int_src_t *val);
nrfx_err_t lis3mdl_interrupt_event_flag_get(uint8_t *val);
nrfx_err_t lis3mdl_int_mag_over_range_flag_get(uint8_t *val);
nrfx_err_t lis3mdl_int_neg_z_flag_get(uint8_t *val);
nrfx_err_t lis3mdl_int_neg_y_flag_get(uint8_t *val);
nrfx_err_t lis3mdl_int_neg_x_flag_get(uint8_t *val);
nrfx_err_t lis3mdl_int_pos_z_flag_get(uint8_t *val);
nrfx_err_t lis3mdl_int_pos_y_flag_get(uint8_t *val);
nrfx_err_t lis3mdl_int_pos_x_flag_get(uint8_t *val);
nrfx_err_t lis3mdl_int_threshold_set(uint16_t val);
nrfx_err_t lis3mdl_int_threshold_get(uint16_t *val);
nrfx_err_t lis3mdl_spi_mode_set(lis3mdl_sim_t val);
nrfx_err_t lis3mdl_spi_mode_get(lis3mdl_sim_t *val);

void lis3mdl_set_read_reg_function(read_reg_ptr read_reg_function);
void lis3mdl_set_write_reg_function(write_reg_ptr write_reg_function);*/

#endif // #ifndef __MAGNETOMETER_HEADER_H
