#ifndef __MOTOR_HPP_
#define __MOTOR_HPP_



#include "ch.hpp"
#include "hal.h"
#include "gpio.hpp"

class Motor {
public:
	Motor(PWMDriver * driver, uint32_t pwm_index,
	      uint32_t max_neg_freq, uint32_t max_pos_freq, uint32_t channel,
	      gpio_pin_t enable_pin, gpio_pin_t dir_pin) :
		driver(driver), pwm_index(pwm_index), channel(channel),
		max_neg_freq(max_neg_freq), max_pos_freq(max_pos_freq),
		position(0), target_position(0), current_freq(0),
		enable_pin(enable_pin), dir_pin(dir_pin)
	
	{
		dir_pin.clear();
		enable_pin.clear();

		dir_pin.set_mode(gpio_pin_t::MODE_OUTPUT);
		enable_pin.set_mode(gpio_pin_t::MODE_OUTPUT);

		pwmObjectInit(driver);
		pwmStop(driver);
		motors[pwm_index] = this;
		switch(pwm_index){
		case 0:
			cb = tickM1;
			break;
		case 1:
			cb = tickM2;
			break;
		case 2:
			cb = tickM3;
			break;
		case 3:
			cb = tickM4;
			break;
		case 4:
			cb = tickM5;
			break;
		case 5:
			cb = tickM6;
			break;
		case 6:
			cb = tickM7;
			break;
		case 7:
			cb = tickM8;
			break;
		case 8:
			cb = tickM9;
			break;
		default:
			while(1);
		}
		
		config.frequency = clk_freq;
		config.period = clk_freq / initial_freq;
		config.channels[0] = {PWM_OUTPUT_DISABLED, NULL};
		config.channels[1] = {PWM_OUTPUT_DISABLED, NULL};
		config.channels[2] = {PWM_OUTPUT_DISABLED, NULL};
		config.channels[3] = {PWM_OUTPUT_DISABLED, NULL};
		config.cr2 = 0;
		config.dier = 0;
	}

	void setPosition(uint32_t new_pos){
		position = new_pos;
		target_position = new_pos;
	}

	void enable(){
		enable_pin.set();
	}
	
	void goToPos(int32_t new_pos){
		if(new_pos == position)
			return;
		config.frequency = clk_freq;
		config.period = clk_freq / initial_freq;
		config.callback = cb;
		current_freq = initial_freq;
		config.channels[0] = {PWM_OUTPUT_DISABLED, NULL};
		config.channels[1] = {PWM_OUTPUT_DISABLED, NULL};
		config.channels[2] = {PWM_OUTPUT_DISABLED, NULL};
		config.channels[3] = {PWM_OUTPUT_DISABLED, NULL};
		config.channels[channel] = {PWM_OUTPUT_ACTIVE_HIGH, NULL};
		config.cr2 = 0;
		config.dier = 0;

		dir_positive = new_pos > position;
		target_position = new_pos;

		dir_pin.assign(dir_positive);

		ramp_length = (new_pos > position) ?
			((max_pos_freq - initial_freq) / ramp) :
			((max_neg_freq - initial_freq) / ramp);

		pwmStart(driver, &config);
		pwmEnableChannel(driver, channel, 10);
		pwmEnablePeriodicNotificationI(driver);
	}
	
	void goToRel(int32_t rel_pos){
		goToPos(position + rel_pos);
	}
	
private:
	uint32_t channel;
	PWMDriver * const driver;
	PWMConfig config;
	uint32_t pwm_index;
	pwmcallback_t cb;
	
	bool dir_positive;
	float max_neg_freq;
	float max_pos_freq;
	float current_freq;
	int32_t position;
	int32_t target_position;
	
	
	static constexpr float clk_freq = 1000000;
	static constexpr float initial_freq = 100.0;
	static constexpr float ramp = 1.0;

	float ramp_length;
	
	gpio_pin_t enable_pin, dir_pin;
	
	void tick();
	
	static void tickM1(PWMDriver *){
		motors[0]->tick();
	}
	
	static void tickM2(PWMDriver *){
		motors[1]->tick();
	}
	
	static void tickM3(PWMDriver *){
		motors[2]->tick();
	}
	
	static void tickM4(PWMDriver *){
		motors[3]->tick();
	}
	
	static void tickM5(PWMDriver *){
		motors[4]->tick();
	}
	
	static void tickM6(PWMDriver *){
		motors[5]->tick();
	}
	
	static void tickM7(PWMDriver *){
		motors[6]->tick();
	}
	
	static void tickM8(PWMDriver *){
		motors[7]->tick();
	}
	
	static void tickM9(PWMDriver *){
		motors[8]->tick();
	}

	static Motor * motors[9];
};

#endif // __MOTOR_HPP_
