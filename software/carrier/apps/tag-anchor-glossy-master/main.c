/*

UWB Localization Tag used as an Anchor

*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define DEVICE_NAME "tottaganc"

#include "nordic_common.h"
#include "nrf.h"
#include "nrf_sdm.h"
#include "nrf_delay.h"
#include "ble.h"
#include "ble_db_discovery.h"
#include "softdevice_handler.h"
#include "app_util.h"
#include "app_error.h"
#include "ble_advdata_parser.h"
#include "ble_conn_params.h"
#include "ble_hci.h"
#include "nrf_gpio.h"
#include "pstorage.h"
// #include "device_manager.h"
#include "app_trace.h"
#include "ble_hrs_c.h"
#include "ble_bas_c.h"
#include "app_util.h"
#include "app_timer.h"
#include "simple_ble.h"
#include "simple_adv.h"

#include "led.h"
#include "boards.h"

#include "ble_config.h"
#include "module_interface.h"
#include "SEGGER_RTT.h"

static app_timer_id_t  test_timer;

bool module_inited = false;

// Copy address from flash
uint8_t _ble_address[6];

// Intervals for advertising and connections
static simple_ble_config_t ble_config = {
    // c0:98:e5:45:xx:xx
    .platform_id       = 0x45,              // used as 4th octect in device BLE address
    .device_id         = DEVICE_ID_DEFAULT,
    .adv_name          = DEVICE_NAME,       // used in advertisements if there is room
    .adv_interval      = MSEC_TO_UNITS(1000, UNIT_0_625_MS),
    .min_conn_interval = MSEC_TO_UNITS(500, UNIT_1_25_MS),
    .max_conn_interval = MSEC_TO_UNITS(1000, UNIT_1_25_MS),
};

void moduleData(uint8_t* data, uint32_t len) {
}

static void timer_handler (void* p_context) {
    uint32_t err_code;

    if (!module_inited) {
        err_code = module_init(moduleData);
        if (err_code == NRF_SUCCESS) {
            module_inited = true;
            module_start_anchor(true);
        }
    }
}

/*******************************************************************************
 *   INIT FUNCTIONS
 ******************************************************************************/

void initialize_app_timers(void) {
    APP_TIMER_INIT(TRITAG_TIMER_PRESCALER, TRITAG_MAX_TIMERS, TRITAG_OP_QUEUE_SIZE, false);
}

static void timers_init(void) {
    uint32_t err_code;

    err_code = app_timer_create(&test_timer,
                                APP_TIMER_MODE_REPEATED,
                                timer_handler);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_start(test_timer, UPDATE_RATE, NULL);
    APP_ERROR_CHECK(err_code);
}

int main(void) {
    uint32_t err_code;

    // Initialization
    led_init(LED_0);
    debug_msg("\r\n----------------------------------------------\r\n");
    debug_msg("Initializing nRF...\r\n");

    // Get stored address
    memcpy(_ble_address, (uint8_t*) BLE_FLASH_ADDRESS, 6);
    // And use it to setup the BLE
    ble_config.device_id = (uint16_t)( (uint16_t)_ble_address[1] << (uint8_t)8) | _ble_address[0];

    // Setup BLE
    simple_ble_init(&ble_config);

    // Advertise because why not
    simple_adv_only_name();

    // Need a timer to make sure we have inited the module
    timers_init();

    err_code = module_hw_init();
    APP_ERROR_CHECK(err_code);

    err_code = module_init(moduleData);
    if (err_code == NRF_SUCCESS) {
        module_inited = true;
        debug_msg("Finished initialization\r\n");
    }
    else {
        debug_msg("ERROR: Failed initialization!\r\n");
    }

    // Make this node an anchor
    if (module_inited) {
        module_start_anchor(true);
        debug_msg("Started as a master anchor...\r\n");
    }

    // Signal end of initialization
    led_on(LED_0);

    while (1) {
        power_manage();
    }
}
