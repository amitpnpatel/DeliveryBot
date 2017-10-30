/*
 * WheelMotor.h
 *
 *  Created on: Jun 23, 2017
 *      Author: amitp
 */

#ifndef SRC_WHEELMOTOR_H_
#define SRC_WHEELMOTOR_H_
#include <Arduino.h>
#define FIXED_STEP 1;
#define CONTINOUS_STEP 2;
#define SINGLE_STEP 3;
class WheelMotor {
private:
    volatile uint8_t *motorPort;
    volatile uint16_t *timeCompareRegister;
	int startStepTime = 400; //micro sec
	int numberOfStepsInRevolution = 200; //number of step in swing
	int currentStepNumber = 0;   // current step count for swing
	int mode = SINGLE_STEP;
public:
	volatile boolean motorState = false; //state "true" for active beat, "false" for motor spleep
	WheelMotor();
	WheelMotor(volatile uint8_t *_beaterPort, volatile uint8_t *portAddressDDR,
			  volatile uint16_t *_timeCompareRegister);
	boolean stop();
	boolean start();
	void moveStep();
	void reset();
	void sleep();
	void wakeUp();
	void powerUp();
	void powerDown();
	void setForwordDirection();
	void setReverseDirection();
	void tick();
	void setStepCount(int step);
	int getStepCount();
	void setStepSpeed(int stepTime);
};

#endif /* SRC_WHEELMOTOR_H_ */
