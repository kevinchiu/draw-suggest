#ifndef TUIO_OBJECT
#define TUIO_OBJECT

//--------------------------------------------------------
class tuioObject {
	
	public:
	
		tuioObject(void);
		tuioObject(int _sid, float _x, float _y, float _angle, float _width, float _height, float _area, float _xspeed, float _yspeed, float _angularspeed, float _acceleration, float _angularacceleration);
		tuioObject(tuioObject*);
		~tuioObject(void);
		void update(float _x, float _y, float _angle, float _width, float _height, float _area, float _xspeed, float _yspeed, float _angularspeed, float _acceleration, float _angularacceleration);
		//sets
		void setId(int _sid);
		void setX(float _x);
		void setY(float _y);
		void setAngle(float _angle);
		void setWidth(float _width);
		void setHeight(float _height);
		void setArea(float _area);
		void setXSpeed(float _xspeed);
		void setYSpeed(float _yspeed);
		void setAngularSpeed(float _angularspeed);
		void setAcceleration(float _acceleration);
		void setAngularAcceleration(float _angularacceleration);
		//gets
		int getId();
		float getX();
		float getY();
		float getAngle();
		float getWidth();
		float getHeight();
		float getArea();
		float getXSpeed();
		float getYSpeed();
		float getAngularSpeed();
		float getAcceleration();
		float getAngularAcceleration();
	
	private:
	
		int sid;
		float x,y,angle,width,height,area,xspeed,yspeed,angularspeed,acceleration,angularacceleration;
	
};

#endif