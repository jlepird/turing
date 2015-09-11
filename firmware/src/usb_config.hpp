#ifndef __USB_CONFIG_HPP_
#define __USB_CONFIG_HPP_

#include "ch.hpp"
#include "hal.h"


void usb_cdc_init();
size_t usb_cdc_read(uint8_t * dest, size_t n, systime_t time);
void usb_cdc_write(uint8_t const * buf, uint32_t len);
BaseSequentialStream * usb_cdc_stream();

#endif // __USB_CONFIG_HPP_
