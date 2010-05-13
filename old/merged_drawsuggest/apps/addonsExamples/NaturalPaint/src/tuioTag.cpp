#include "tuioTag.h"

tuioTag::tuioTag(void){
	
}

tuioTag::tuioTag(int _sid, int _tid, float _x, float _y, float _angle, float _xspeed, float _yspeed, float _angularspeed, float _acceleration, float _angularacceleration) {
	
	sid = _sid;
	tid = _tid;
	x = _x;
	y = _y;
	angle = _angle;
	xspeed = _xspeed;
	yspeed = _yspeed;
	angularspeed = _angularspeed;
	acceleration = _acceleration;
	angularacceleration = _angularacceleration;
	
}

tuioTag::tuioTag(tuioTag* tt) {
	
	sid = tt->getId();
	tid = tt->getTagId();
	x = tt->getX();
	y = tt->getY();
	angle = tt->getAngle();
	xspeed = tt->getXSpeed();
	yspeed = tt->getYSpeed();
	angularspeed = tt->getAngularSpeed();
	acceleration = tt->getAcceleration();
	angularacceleration = tt->getAngularAcceleration();
	
}

tuioTag::~tuioTag(void) {
	
}

void tuioTag::update(int _tid, float _x, float _y, float _angle, float _xspeed, float _yspeed, float _angularspeed, float _acceleration, float _angularacceleration) {
	
	tid = _tid;
	x = _x;
	y = _y;
	angle = _angle;
	xspeed = _xspeed;
	yspeed = _yspeed;
	angularspeed = _angularspeed;
	acceleration = _acceleration;
	angularacceleration = _angularacceleration;
	
}

void tuioTag::setId(int _sid){
	sid = _sid;
}

void tuioTag::setTagId(int _tid){
	tid = _tid;
}

void tuioTag::setX(float _x){
	x = _x;
}

void tuioTag::setY(float _y){
	y = _y;
}

void tuioTag::setAngle (float _angle){
	angle = _angle;
}

void tuioTag::setXSpeed (float _xspeed){
	xspeed = _xspeed;
}

void tuioTag::setYSpeed (float _yspeed){
	yspeed = _yspeed;
}

void tuioTag::setAngularSpeed(float _angularspeed){
	angularspeed = _angularspeed;
}

void tuioTag::setAcceleration (float _acceleration){
	acceleration = _acceleration;
}

void tuioTag::setAngularAcceleration(float _angularacceleration){
	angularacceleration = _angularacceleration;
}

int tuioTag::getId(){
	return sid;
}

int tuioTag::getTagId(){
	return tid;
}

float tuioTag::getY(){
	return y;
}

float tuioTag::getX(){
	return x;
}

float tuioTag::getAngle(){
	return angle;
}

float tuioTag::getXSpeed(){
	return xspeed;
}

float tuioTag::getYSpeed(){
	return yspeed;
}

float tuioTag::getAngularSpeed(){
	return angularspeed;
}

float tuioTag::getAcceleration(){
	return acceleration;
}

float tuioTag::getAngularAcceleration(){
	return angularacceleration;
}