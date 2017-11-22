/*
 * Box.h
 *
 *  Created on: Nov 6, 2017
 *      Author: amitp
 */

#ifndef SRC_BOX_H_
#define SRC_BOX_H_
#include <Arduino.h>
class Box{
private:
	int centre;
	int inclination;
	boolean state;
	boolean updateState;
public:
	Box(int centre,int inclination,boolean state);
	void setCentre(int centre);
	void setInclination(int inclination);
	int getCentre();
	int getInclination();
	void setState(boolean state);
	boolean getState();
	void setParams(boolean state,int centre,int inclination);
	boolean waitTillNextUpdate();
	void checkSencor();
};

#endif /* SRC_BOX_H_ */
