/*
 * WheelMotor.h
 *
 *  Created on: Jun 23, 2017
 *      Author: amitp
 */

#ifndef SRC_WHEELMOTOR_H_
#define SRC_WHEELMOTOR_H_
#include <Arduino.h>
class WheelMotor {
private:
    volatile uint8_t *motorPort;
	int startStepTime = 400; //micro sec
	int numberOfStepsInRevolution = 200; //number of step in swing
	int currentStepNumber = 0;   // current step count for swing
public:
	boolean motorState = false; //state "true" for active beat, "false" for motor spleep
	WheelMotor();
	WheelMotor(volatile uint8_t *_beaterPort, volatile uint8_t *portAddressDDR);
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
};

#endif /* SRC_WHEELMOTOR_H_ */
