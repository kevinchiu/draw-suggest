#include "tuio.h"

void Tuio::init(){
	
	receiver.setup( PORT );
	
}

void Tuio::getMessages(){
	
	cursors = receiver.getCursors();
	
}