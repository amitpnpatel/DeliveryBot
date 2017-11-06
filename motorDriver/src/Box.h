/*
 * Box.h
 *
 *  Created on: Nov 6, 2017
 *      Author: amitp
 */

#ifndef SRC_BOX_H_
#define SRC_BOX_H_
class Box{
private:
	int centre;
	int inclination;
public:
	Box(int centre,int inclination);
	void setCentre(int centre);
	void setInclination(int inclination);
	int getCentre();
	int getInclination();
};




#endif /* SRC_BOX_H_ */
