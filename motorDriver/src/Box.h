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
	boolean onMarker;
public:
	Box(int centre,int inclination,boolean state,boolean onMark);
	void setCentre(int centre);
	void setInclination(int inclination);
	int getCentre();
	int getInclination();
	void setState(boolean state);
	boolean getState();
	void setOnMarker(boolean state);
	boolean isOnMarker();
	void setParams(boolean state,int centre,int inclination,boolean onMark);
	boolean waitTillNextUpdate();
	void checkSensor();
};

#endif /* SRC_BOX_H_ */
