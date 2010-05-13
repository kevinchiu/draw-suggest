#ifndef TUIO
#define TUIO

#include <map>

#include "ofxOsc.h"
#include "tuioCursor.h"
#include "tuioObject.h"
#include "tuioTag.h"

// listen on port 3333
#define PORT 3333
#define NUM_MSG_STRINGS 20


//--------------------------------------------------------
class Tuio {
	
	public:
	
		map<int,tuioCursor*>		cursors;
		map<int,tuioObject*>		objects;
		map<int,tuioTag*>			tags;
	
		void init();
		void getMessages();
	
	private:
	
		ofxOscReceiver			receiver;
		int						current_msg_string;
	
};

#endif
