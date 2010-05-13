#include "tuioObject.h"

tuioObject::tuioObject(void){
	
}

tuioObject::tuioObject(int _sid, float _x, float _y, float _angle, float _width, float _height, float _area, float _xspeed, float _yspeed, float _angularspeed, float _acceleration, float _angularacceleration){
	
	sid = _sid;
	x = _x;
	y = _y;
	angle = _angle;
	width = _width;
	height = _height;
	area = _area;
	xspeed = _xspeed;
	yspeed = _yspeed;
	angularspeed = _angularspeed;
	acceleration = _acceleration;
	angularacceleration = _angularacceleration;
	
}

tuioObject::tuioObject(tuioObject* to){
	
	sid = to->getId();
	x = to->getX();
	y = to->getY();
	angle = to->getAngle();
	width = to->getWidth();
	height = to->getHeight();
	area = to->getArea();
	xspeed = to->getXSpeed();
	yspeed = to->getYSpeed();
	angularspeed = to->getAngularSpeed();
	acceleration = to->getAcceleration();
	angularacceleration = to->getAngularAcceleration();
	
}

tuioObject::~tuioObject(void){
	
}

void tuioObject::update(float _x, float _y, float _angle, float _width, float _height, float _area, float _xspeed, float _yspeed, float _angularspeed, float _acceleration, float _angularacceleration){
	
	x = _x;
	y = _y;
	angle = _angle;
	width = _width;
	height = _height;
	area = _area;
	xspeed = _xspeed;
	yspeed = _yspeed;
	angularspeed = _angularspeed;
	acceleration = _acceleration;
	angularacceleration = _angularacceleration;
	
}

void tuioObject::setId(int _sid){
	sid = _sid;
}

void tuioObject::setX(float _x){
	x = _x;
}

void tuioObject::setY(float _y){
	y = _y;
}

void tuioObject::setAngle(float _angle){
	angle = _angle;
}

void tuioObject::setWidth(float _width){
	width = _width;
}

void tuioObject::setHeight(float _height){
	height = _height;
}

void tuioObject::setArea(float _area){
	area = _area;
}

void tuioObject::setXSpeed(float _xspeed){
	xspeed = _xspeed;
}

void tuioObject::setYSpeed(float _yspeed){
	yspeed = _yspeed;
}

void tuioObject::setAngularSpeed(float _angularspeed){
	angularspeed = _angularspeed;
}

void tuioObject::setAcceleration(float _acceleration){
	acceleration = _acceleration;
}

void tuioObject::setAngularAcceleration(float _angularacceleration){
	angularacceleration = _angularacceleration;
}

int tuioObject::getId(){
	return sid;
}

float tuioObject::getX(){
	return x;
}

float tuioObject::getY(){
	return y;
}

float tuioObject::getAngle(){
	return angle;
}

float tuioObject::getWidth(){
	return width;
}

float tuioObject::getHeight(){
	return height;
}

float tuioObject::getArea(){
	return area;
}

float tuioObject::getXSpeed(){
	return xspeed;
}	

float tuioObject::getYSpeed(){
	return yspeed;
}

float tuioObject::getAngularSpeed(){
	return angularspeed;
}

float tuioObject::getAcceleration(){
	return acceleration;
}

float tuioObject::getAngularAcceleration(){
	return angularacceleration;
}
