#include "ofxOscReceiver.h"

#ifndef TARGET_WIN32
#include <pthread.h>
#endif
#include <iostream>
#include <assert.h>

ofxOscReceiver::ofxOscReceiver() {
	
	listen_socket = NULL;

}

void ofxOscReceiver::setup( int listen_port ) {
	
	if ( listen_socket ) shutdown();
	
	#ifdef TARGET_WIN32
	mutex = CreateMutexA( NULL, FALSE, NULL );
	busyCursors = CreateMutexA( NULL, FALSE, NULL );
	busyObjects = CreateMutexA( NULL, FALSE, NULL );
	busyTags = CreateMutexA( NULL, FALSE, NULL );
	#else
	pthread_mutex_init( &mutex, NULL );
	pthread_mutex_init( &busyCursors, NULL );
	pthread_mutex_init( &busyObjects, NULL );
	pthread_mutex_init( &busyTags, NULL );
	#endif
	
	socketHasShutdown = false;
	listen_socket = new UdpListeningReceiveSocket( IpEndpointName( IpEndpointName::ANY_ADDRESS, listen_port ), this );

	#ifdef TARGET_WIN32
	thread	= CreateThread(NULL, 0, &ofxOscReceiver::startThread, (void*)this, 0, NULL);
	#else
	pthread_create( &thread, NULL, &ofxOscReceiver::startThread, (void*)this );
	#endif

}

void ofxOscReceiver::shutdown() {
	
	if ( listen_socket ) {
		listen_socket->AsynchronousBreak();
		while (!socketHasShutdown) {
			#ifdef TARGET_WIN32
			Sleep(1);
			#else
			usleep(100);
			#endif
		}
		grabMutex(mutex);
		delete listen_socket;
		listen_socket = NULL;
		
	}
	
}

ofxOscReceiver::~ofxOscReceiver() {
	
	shutdown();

}

#ifdef TARGET_WIN32
DWORD WINAPI
#else
void*
#endif
		ofxOscReceiver::startThread( void* receiverInstance ) {
			
	ofxOscReceiver* instance = (ofxOscReceiver*)receiverInstance;
	instance->listen_socket->Run();
	instance->socketHasShutdown = true;
	#ifdef TARGET_WIN32
	return 0;
    #else
	return NULL;
    #endif
			
}

void ofxOscReceiver::ProcessMessage( const osc::ReceivedMessage &m, const IpEndpointName& remoteEndpoint ) {
	
	try{
		if( strcmp( m.AddressPattern(), "/tuio/2Dcur" ) == 0 ){
			osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
			string type = (arg++)->AsString();
			if (type.compare("set") == 0) {
				//parse message
				int id = (arg++)->AsInt32();
				float x = (arg++)->AsFloat();
				float y = (arg++)->AsFloat();
				float xspeed = (arg++)->AsFloat();
				float yspeed = (arg++)->AsFloat();
				float acceleration = (arg++)->AsFloat();
				//add-update cursor
				grabMutex(busyCursors);
				if(cursors.count(id) != 0) cursors[id]->update(x,y,xspeed,yspeed,acceleration);
				else cursors.insert( pair<int,tuioCursor*>(id,new tuioCursor(id,x,y,xspeed,yspeed,acceleration)) );
				releaseMutex(busyCursors);
			} else if (type.compare("alive") == 0){
				map<int,tuioCursor*> stay;
				while ( arg != m.ArgumentsEnd() ) {
					int id = (arg++)->AsInt32();
					grabMutex(busyCursors);
					if (cursors.count(id) != 0) stay.insert( pair<int,tuioCursor*>(id,cursors[id]) );
					releaseMutex(busyCursors);
				}
				grabMutex(busyCursors);
				cursors = stay;
				releaseMutex(busyCursors);
			}
		}else if( strcmp( m.AddressPattern(), "/tuio/2Dblb" ) == 0 ){
			osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
			string type = (arg++)->AsString();
			if (type.compare("set") == 0) {
				//parse message
				int id = (arg++)->AsInt32();
				float x = (arg++)->AsFloat();
				float y = (arg++)->AsFloat();
				float angle = (arg++)->AsFloat();
				float width = (arg++)->AsFloat();
				float height = (arg++)->AsFloat();
				float area = (arg++)->AsFloat();
				float xspeed = (arg++)->AsFloat();
				float yspeed = (arg++)->AsFloat();
				float angularspeed = (arg++)->AsFloat();
				float acceleration = (arg++)->AsFloat();
				float angularacceleration = (arg++)->AsFloat();
				//add-update object
				grabMutex(busyObjects);
				if(objects.count(id) != 0) objects[id]->update(x,y,angle,width,height,area,xspeed,yspeed,angularspeed,acceleration,angularacceleration);
				else objects.insert( pair<int,tuioObject*>(id,new tuioObject(id,x,y,angle,width,height,area,xspeed,yspeed,angularspeed,acceleration,angularacceleration)) );	
				releaseMutex(busyObjects);	
			}else if (type.compare("alive") == 0){
				map<int,tuioObject*> stay;
				while ( arg != m.ArgumentsEnd() ) {
					int id = (arg++)->AsInt32();
					grabMutex(busyObjects);
					if (objects.count(id) != 0) stay.insert( pair<int,tuioObject*>(id,objects[id]) );
					releaseMutex(busyObjects);
				}
				grabMutex(busyObjects);
				objects = stay;
				releaseMutex(busyObjects);
			}
		}else if( strcmp( m.AddressPattern(), "/tuio/2Dobj" ) == 0 ){
			osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
			string type = (arg++)->AsString();
			if (type.compare("set") == 0) {
				//parse message
				int id = (arg++)->AsInt32();
				int fid = (arg++)->AsInt32();
				float x = (arg++)->AsFloat();
				float y = (arg++)->AsFloat();
				float angle = (arg++)->AsFloat();
				float xspeed = (arg++)->AsFloat();
				float yspeed = (arg++)->AsFloat();
				float angularspeed = (arg++)->AsFloat();
				float acceleration = (arg++)->AsFloat();
				float angularacceleration = (arg++)->AsFloat();
				//add-update tag
				grabMutex(busyTags);
				if(tags.count(id) != 0) tags[id]->update(fid,x,y,angle,xspeed,yspeed,angularspeed,acceleration,angularacceleration);
				else tags.insert( pair<int,tuioTag*>(id,new tuioTag(id,fid,x,y,angle,xspeed,yspeed,angularspeed,acceleration,angularacceleration)) );
				releaseMutex(busyTags);				
			}else if (type.compare("alive") == 0){
				map<int,tuioTag*> stay;
				while ( arg != m.ArgumentsEnd() ) {
					int id = (arg++)->AsInt32();
					grabMutex(busyTags);
					if (tags.count(id) != 0) stay.insert( pair<int,tuioTag*>(id,tags[id]) );
					releaseMutex(busyTags);
				}
				grabMutex(busyTags);
				tags = stay;
				releaseMutex(busyTags);
			}
		}
	}catch( osc::Exception& e ){
		printf("error while parsing message\n");
	}
	
}

#ifdef TARGET_WIN32
void ofxOscReceiver::grabMutex(HANDLE m) {
	WaitForSingleObject( m, INFINITE );
}

void ofxOscReceiver::releaseMutex(HANDLE m) {
	ReleaseMutex( m );
}
#else
void ofxOscReceiver::grabMutex(pthread_mutex_t m) {
	pthread_mutex_lock( &m );	
}

void ofxOscReceiver::releaseMutex(pthread_mutex_t m) {
	pthread_mutex_unlock( &m );
}
#endif

map<int,tuioCursor*> ofxOscReceiver::getCursors(){
	
	map<int,tuioCursor*> currentCursors;
	map<int,tuioCursor*>::reverse_iterator rit;
	
	grabMutex(busyCursors);
	for ( rit = cursors.rbegin() ; rit != cursors.rend(); rit++ ) {
		tuioCursor* aux = rit->second; 
		currentCursors.insert( pair<int,tuioCursor*>(aux->getId(),aux) );
	}
	releaseMutex(busyCursors);
	
	return currentCursors;
	
}

map<int,tuioObject*> ofxOscReceiver::getObjects(){
	
	map<int,tuioObject*> currentObjects;
	map<int,tuioObject*>::reverse_iterator rit;
	
	grabMutex(busyObjects);
	for ( rit = objects.rbegin() ; rit != objects.rend(); rit++ ) {
		tuioObject* aux = rit->second; 
		currentObjects.insert( pair<int,tuioObject*>(aux->getId(),aux) );
	}
	releaseMutex(busyObjects);
	
	return currentObjects;
	
}

map<int,tuioTag*> ofxOscReceiver::getTags(){
	
	map<int,tuioTag*> currentTags;
	map<int,tuioTag*>::reverse_iterator rit;
	
	//LOCK TAGS
	grabMutex(busyTags);
	for ( rit = tags.rbegin() ; rit != tags.rend(); rit++ ) {
		tuioTag* aux = rit->second; 
		currentTags.insert( pair<int,tuioTag*>(aux->getId(),aux) );
	}
	releaseMutex(busyTags);
	
	return currentTags;
	
}