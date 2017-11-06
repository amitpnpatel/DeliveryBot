/*
 * Box.cpp
 *
 *  Created on: Nov 6, 2017
 *      Author: amitp
 */
#include "Box.h"
Box::Box(int centre,int inclination){
	this->centre=centre;
	this->inclination=inclination;
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
