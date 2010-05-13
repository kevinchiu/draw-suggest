#ifndef TUIO_TAG
#define TUIO_TAG

//--------------------------------------------------------
class tuioTag {
	
	public:
	
		tuioTag(void);
		tuioTag(int _sid, int _tid, float _x, float _y, float _angle, float _xspeed, float _yspeed, float _angularspeed, float _acceleration, float _angularacceleration);
		tuioTag(tuioTag*);
		~tuioTag(void);
		void update(int _tid, float _x, float _y, float _angle, float _xspeed, float _yspeed, float _angularspeed, float _acceleration, float _angularacceleration);
		//sets
		void setId(int _sid);
		void setTagId(int _tid);
		void setX(float _x);
		void setY(float _y);
		void setAngle (float _angle);
		void setXSpeed (float _xspeed);
		void setYSpeed (float _yspeed);
		void setAngularSpeed(float _angularspeed);
		void setAcceleration (float _acceleration);
		void setAngularAcceleration(float _angularacceleration);
		//gets
		int getId();
		int getTagId();
		float getX();
		float getY();
		float getAngle();
		float getXSpeed();
		float getYSpeed();
		float getAngularSpeed();
		float getAcceleration();
		float getAngularAcceleration();
	
	private:
	
		int sid,tid;
		float x,y,angle,xspeed,yspeed,angularspeed,acceleration,angularacceleration;
	
};

#endif