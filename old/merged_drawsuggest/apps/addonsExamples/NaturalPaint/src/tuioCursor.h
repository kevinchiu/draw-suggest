#ifndef TUIO_CURSOR
#define TUIO_CURSOR

//--------------------------------------------------------
class tuioCursor {
	
	public:
	
		tuioCursor();
		tuioCursor(int _sid, float _x, float _y,float _xspeed,float _yspeed,float acceleration);
		tuioCursor(tuioCursor *);
		~tuioCursor(void);
		void update(float _x, float _y,float _xspeed,float _yspeed,float acceleration);
		//sets
		void setId(int _sid);
		void setX(float _x);
		void setY(float _y);
		void setXSpeed(float _xspeed);
		void setYSpeed(float _yspeed);
		void setAcceleration(float _acceleration);
		//gets
		int getId();
		float getX();
		float getY();
		float getXSpeed();
		float getYSpeed();
		float getAcceleration();
	
	private:
	
		int sid;
		float x,y,xspeed,yspeed,acceleration;
	
	
};

#endif