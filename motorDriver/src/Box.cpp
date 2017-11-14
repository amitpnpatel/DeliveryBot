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
}
void Box::setCentre(int centre){
	this->centre=centre;
}
void Box::setInclination(int inclination){
	this->inclination=inclination;
}
int Box::getCentre(){
	return centre;
}
int Box::getInclination(){
	return inclination;
}
void Box::setState(boolean state){
	this->state=state;
}
boolean Box::getState(){
	return state;
}
