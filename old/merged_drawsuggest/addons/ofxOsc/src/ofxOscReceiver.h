#ifndef _ofxOscRECEIVER_H
#define _ofxOscRECEIVER_H

#include <deque>
#include "ofMain.h"
#ifdef TARGET_WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

#include "OscTypes.h"
#include "OscPacketListener.h"
#include "UdpSocket.h"

#include "tuioCursor.h"
#include "tuioObject.h"
#include "tuioTag.h"

class ofxOscReceiver : public osc::OscPacketListener {
	
	public:
	
		ofxOscReceiver();
		~ofxOscReceiver();

		void setup( int listen_port );
		map<int,tuioCursor*> getCursors();
		map<int,tuioObject*> getObjects();
		map<int,tuioTag*> getTags();

	protected:
	
		virtual void ProcessMessage( const osc::ReceivedMessage &m, const IpEndpointName& remoteEndpoint );

	private:
		
		map<int,tuioCursor*> cursors;
		map<int,tuioObject*> objects;
		map<int,tuioTag*> tags;
		UdpListeningReceiveSocket* listen_socket;
		bool socketHasShutdown;
		#ifdef TARGET_WIN32
		HANDLE thread;
		HANDLE mutex;
		HANDLE busyCursors;
		HANDLE busyObjects;
		HANDLE busyTags;
		#else
		pthread_t thread;
		pthread_mutex_t mutex;
		pthread_mutex_t busyCursors;
		pthread_mutex_t busyObjects;
		pthread_mutex_t busyTags;
		#endif
	
		void shutdown();
		#ifdef TARGET_WIN32
		static DWORD WINAPI startThread( void* ofxOscReceiverInstance );
		void grabMutex(HANDLE m);
		void releaseMutex(HANDLE m);
		#else
		static void* startThread( void* ofxOscReceiverInstance );
		void grabMutex(pthread_mutex_t m);
		void releaseMutex(pthread_mutex_t m);
		#endif

};

#endif
