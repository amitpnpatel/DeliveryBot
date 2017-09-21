/*
 * Cart.h
 *
 *  Created on: Jun 26, 2017
 *      Author: amitp
 */

#ifndef SRC_CART_H_
#define SRC_CART_H_
#include <Arduino.h>
#include <WheelMotor.h>
class Cart{
private:
	WheelMotor leftWheel;
	WheelMotor rightWheel;
	int wheelRadius;
	int width;
public:
	Cart(WheelMotor left,WheelMotor right, int wheelRadius,int width);
	boolean moveForward(long distance);
	boolean moveReverse(long distance);
	boolean rotateRight(long angle);
	boolean rotateLeft(long angle);
	boolean powerUpWheels();
	boolean powerDownWheels();
};



#endif /* SRC_CART_H_ */
