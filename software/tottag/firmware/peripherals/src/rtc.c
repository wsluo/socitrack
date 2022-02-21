// Header inclusions ---------------------------------------------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wredundant-decls"

#include "ble_config.h"
#include "nrfx_atomic.h"
#include "nrfx_rtc.h"
#include "rtc.h"
#include "sd_card.h"

#pragma GCC diagnostic pop

#define NRF_RTC_PRESCALER 2097

// Static RTC state variables ------------------------------------------------------------------------------------------

static const nrfx_rtc_t _rtc_instance = NRFX_RTC_INSTANCE(2);
static nrfx_atomic_u32_t _rtc_sync_time = 0;
static nrfx_atomic_u32_t _rtc_sync_rtc_counter = 0;
static nrfx_atomic_u32_t _rtc_sync_rtc_overflow_counter = 0;
static nrfx_atomic_flag_t _rtc_sync_rtc_overflown = false;

static nrfx_atomic_u32_t _rtc_sync_rtc_counter_raw = 0;

// Private helper functions --------------------------------------------------------------------------------------------

static void rtc_handler(nrfx_rtc_int_type_t int_type) {}
//static uint32_t rtc_to_s(uint32_t ticks) { return ticks / 8; }
static uint32_t rtc_to_s(uint32_t ticks) { return ticks / (32768/(NRF_RTC_PRESCALER+1)); }

// Public RTC functionality --------------------------------------------------------------------------------------------

void rtc_init(void)
{
   // Initialize the RTC instance
   nrfx_rtc_config_t rtc_config = NRFX_RTC_DEFAULT_CONFIG;
   //rtc_config.prescaler = 4095;  // Ticks at 8 Hz; PRESCALER is 12bit register (2^12 - 1 = 4095)
   //rtc_config.prescaler = 2097;
   rtc_config.prescaler = NRF_RTC_PRESCALER;
   nrfx_err_t err_code = nrfx_rtc_init(&_rtc_instance, &rtc_config, rtc_handler);
   APP_ERROR_CHECK(err_code);
   nrfx_rtc_enable(&_rtc_instance);
}

uint32_t rtc_get_current_time(void)
{
   // Get current application time
   uint32_t current_rtc_counter = rtc_to_s(nrfx_rtc_counter_get(&_rtc_instance));
   uint32_t time = _rtc_sync_time + (current_rtc_counter - _rtc_sync_rtc_counter);

   // Check for an RTC overflow
   if (!_rtc_sync_rtc_overflown && (current_rtc_counter < _rtc_sync_rtc_counter))
   {
      log_printf("WARNING: RTC overflow has occurred\n");
      _rtc_sync_rtc_overflown = true;
      ++_rtc_sync_rtc_overflow_counter;
   }
   else if (_rtc_sync_rtc_overflown && (current_rtc_counter > _rtc_sync_rtc_counter))
   {
      log_printf("INFO: RTC overflow flag cleared, ready for next overflow\n");
      _rtc_sync_rtc_overflown = false;
   }

   // Include RTC overflow and return time
   return time + (_rtc_sync_rtc_overflow_counter * rtc_to_s(0x00FFFFFF));
}


uint32_t rtc_get_current_time_raw(void)
{
   // Get current application time
   uint32_t current_rtc_counter_raw = nrfx_rtc_counter_get(&_rtc_instance);
   
   /*
   uint32_t time_raw = _rtc_sync_time + (current_rtc_counter_raw - _rtc_sync_rtc_counter_raw);

   // Check for an RTC overflow
   if (!_rtc_sync_rtc_overflown && (current_rtc_counter_raw < _rtc_sync_rtc_counter_raw))
   {
      log_printf("WARNING: RTC overflow has occurred\n");
      _rtc_sync_rtc_overflown = true;
      ++_rtc_sync_rtc_overflow_counter;
   }
   else if (_rtc_sync_rtc_overflown && (current_rtc_counter_raw > _rtc_sync_rtc_counter))
   {
      log_printf("INFO: RTC overflow flag cleared, ready for next overflow\n");
      _rtc_sync_rtc_overflown = false;
   }

   // Include RTC overflow and return time
   return time_raw + (_rtc_sync_rtc_overflow_counter * rtc_to_s(0x00FFFFFF));*/
   return current_rtc_counter_raw;
}





void rtc_set_current_time(uint32_t epoch)
{
   _rtc_sync_time = epoch;
   _rtc_sync_rtc_counter = rtc_to_s(nrfx_rtc_counter_get(&_rtc_instance));
   _rtc_sync_rtc_counter_raw = nrfx_rtc_counter_get(&_rtc_instance);
   _rtc_sync_rtc_overflow_counter = 0;
   _rtc_sync_rtc_overflown = false;
}
