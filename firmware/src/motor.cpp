#include "motor.hpp"

Motor * Motor::motors[9] = {0};

void Motor::tick(){
	if(dir_positive){
		position += 1;
		current_freq += ramp;
		if(current_freq > max_pos_freq){
			current_freq = max_pos_freq;
			//return;
		}
		pwmChangePeriodI(driver, clk_freq / current_freq);
		//if(target_position - position < (max_pos_freq - initial_freq) / ramp){
			// almost at end
		//}
	} else {
		position += 1;
		current_freq += ramp;
		position -= 1;
	}
}
//std::map<PWMDriver *, Motor *> Motor::motormap = {
//#if STM32_PWM_USE_TIM1
//	{&PWMD1, (Motor *)nullptr},
//#endif
//#if STM32_PWM_USE_TIM2
//	{&PWMD2, (Motor *)nullptr},
//#endif
//#if STM32_PWM_USE_TIM3
//	{&PWMD3, (Motor *)nullptr},
//#endif
//};
