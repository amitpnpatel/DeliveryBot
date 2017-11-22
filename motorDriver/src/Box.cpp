/*
 * Box.cpp
 *
 *  Created on: Nov 6, 2017
 *      Author: amitp
 */
#include "Box.h"
Box::Box(int centre,int inclination,boolean state){
	this->centre=centre;
	this->inclination=inclination;
	this->state=state;
	this->updateState=false;
}
void Box::setCentre(int centre){
	this->centre=centre;
}
void Box::setInclination(int inclination){
	this->inclination=inclination;
}
int Box::getCentre(){
	checkSencor();
	return centre;
}
int Box::getInclination(){
	checkSencor();
	return inclination;
}
void Box::setState(boolean state){
	this->state=state;
}
boolean Box::getState(){
	checkSencor();
	return state;
}
void Box::setParams(boolean state,int centre,int inclination){
	setState(state);
	setCentre(centre);
	setInclination(inclination);
	this->updateState=true;
}
boolean Box::waitTillNextUpdate(){
	this->updateState=false;
	int counter=0;
	while(!updateState){
		if(counter>100){
			return false;
		}
		counter++;
		delay(10);
		checkSencor();
	}
	return true;
}
char readNextCharacterFromSerial1() {
	while (Serial1.available() == 0) {
	}
	return (char) Serial1.read();
}
byte readNextByteFromSerial1() {
	while (Serial1.available() == 0) {
	}
	return Serial1.read();
}
void Box::checkSencor(){
	while (Serial1.available()) {
	char inChar = readNextCharacterFromSerial1();
	if (inChar == 'S') {
		inChar = readNextCharacterFromSerial1();
		if (inChar == 'L') {
			inChar = readNextCharacterFromSerial1();
			if (inChar == 'C') {
				boolean state = readNextByteFromSerial1();
				int centre = readNextByteFromSerial1();
				int inclination = readNextByteFromSerial1();
				inChar = readNextCharacterFromSerial1();
				if (inChar == 'E') {
					setParams(state,centre,inclination - 50);
				}

			}

		}
	}
}
}
