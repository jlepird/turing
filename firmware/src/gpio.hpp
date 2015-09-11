#ifndef __GPIO_PIN_H_
#define __GPIO_PIN_H_

#include "ch.hpp"
#include "hal.h"

/*!
 @brief A structure defining a single GPIO pin
 */
struct gpio_pin_t {
	gpio_pin_t(ioportid_t gpio, uint16_t index) :
		gpio(*gpio), index(index), mask(1 << index)
	{}
	
	/*!
	 @brief Read the current value at the pin
	 */
	bool read() const{
		return gpio.IDR & mask;
	}
	
	/*!
	 @brief Toggle the output of the pin
	 */
	void toggle() const{
		if(gpio.ODR & mask){
			gpio.BSRR.H.clear = mask;
		} else {
			gpio.BSRR.H.set = mask;
		}
	}
	
	/*!
	 @brief Assign a boolean value to the pin
	 */
	void assign(bool val) const{
		if(val)
			set();
		else
			clear();
	}
	
	/*!
	 @brief Explicitly set the output to a logical '1'
	 */
	void set() const{
		gpio.BSRR.H.set = mask;
	}
	
	/*!
	 @brief Explicitly set the output to a logical '0'
	 */
	void clear() const{
		gpio.BSRR.H.clear = mask;
	}
	
	typedef enum {
		MODE_INPUT = 0,
		MODE_OUTPUT = 1,
		MODE_ALT = 2,
		MODE_ANALOG = 3
	} gpio_mode_t;
	
	void set_mode(gpio_mode_t mode) const {
		gpio.MODER = (gpio.MODER & ~(3 << (index * 2))) | (mode << (index * 2));
	}
	
	stm32_gpio_t &gpio;
	uint16_t mask;
	uint16_t index;
};

#endif // __GPIO_PIN_H_

