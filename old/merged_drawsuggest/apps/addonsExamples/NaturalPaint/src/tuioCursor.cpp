#include "tuioCursor.h"

tuioCursor::tuioCursor(void){
	sid = -1;
	x = -1;
	y = -1;
}

tuioCursor::tuioCursor(int _sid, float _x, float _y,float _xspeed,float _yspeed,float _acceleration){
	
	sid = _sid;
	x = _x;
	y = _y;
	xspeed = _xspeed;
	yspeed = _yspeed;
	acceleration = _acceleration;

}

tuioCursor::tuioCursor(tuioCursor* tc){
	
	sid = tc->getId();
	x = tc->getX();
	y = tc->getY();
	xspeed = tc->getXSpeed();
	yspeed = tc->getYSpeed();
	acceleration = tc->getAcceleration();
	
}

tuioCursor::~tuioCursor(void){
	
}

void tuioCursor::update(float _x, float _y,float _xspeed,float _yspeed,float _acceleration){

	x = _x;
	y = _y;
	xspeed = _xspeed;
	yspeed = _yspeed;
	acceleration = _acceleration;

}

void tuioCursor::setId(int _sid){
	sid = _sid;
}

void tuioCursor::setX(float _x){
	x = _x;
}

void tuioCursor::setY(float _y){
	y = _y;
}

void tuioCursor::setXSpeed(float _xspeed){
	xspeed = _xspeed;
}

void tuioCursor::setYSpeed(float _yspeed){
	yspeed = _yspeed;
}

void tuioCursor::setAcceleration(float _acceleration){
	acceleration = _acceleration;
}

int tuioCursor::getId(){
	return sid;
}

float tuioCursor::getY(){
	return y;
}

float tuioCursor::getX(){
	return x;
}

float tuioCursor::getXSpeed(){
	return xspeed;
}

float tuioCursor::getYSpeed(){
	return yspeed;
}

float tuioCursor::getAcceleration(){
	return acceleration;
}