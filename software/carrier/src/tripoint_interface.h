#ifndef __TRIPOINT_INTERFACE_H
#define __TRIPOINT_INTERFACE_H

#include "sdk_errors.h"

#define TRIPOINT_ID 0xB01A

#define TRIPOINT_ADDRESS 0x65


#define TRIPOINT_CMD_INFO             0x01
#define TRIPOINT_CMD_CONFIG           0x02
#define TRIPOINT_CMD_READ_INTERRUPT   0x03
#define TRIPOINT_CMD_DO_RANGE         0x04
#define TRIPOINT_CMD_SLEEP            0x05
#define TRIPOINT_CMD_RESUME           0x06
#define TRIPOINT_CMD_SET_LOCATION     0x07
#define TRIPOINT_CMD_READ_CALIBRATION 0x08

// Defines for identifying data sent to host
#define HOST_IFACE_INTERRUPT_RANGES         0x01
#define HOST_IFACE_INTERRUPT_CALIBRATION    0x02

// Ranging errors
#define ONEWAY_TAG_RANGE_MIN (-1000)
// The ANCHOR did not receive matching packets from the first three cycle.
// This prevents us from calculating clock skew, and we have to skip this anchor range.
#define ONEWAY_TAG_RANGE_ERROR_NO_OFFSET 0x80000001
// The anchor did not receive enough packets from the tag, so we don't have
// enough observations (ranges) to actually calculate a range to this anchor.
#define ONEWAY_TAG_RANGE_ERROR_TOO_FEW_RANGES 0x80000002
// Something else went wrong that we don't have pinned down.
#define ONEWAY_TAG_RANGE_ERROR_MISC 0x8000000F

typedef void (*tripoint_interface_data_cb_f)(uint8_t* data, uint32_t len);


ret_code_t tripoint_init (tripoint_interface_data_cb_f cb);
ret_code_t tripoint_hw_init ();
ret_code_t tripoint_get_info (uint16_t* id, uint8_t* version);
ret_code_t tripoint_start_ranging (bool periodic, uint8_t rate);
ret_code_t tripoint_start_anchor (bool is_glossy_master);
ret_code_t tripoint_start_calibration (uint8_t index);
ret_code_t tripoint_get_calibration (uint8_t* calib_buf);
ret_code_t tripoint_sleep ();
ret_code_t tripoint_resume ();

#endif