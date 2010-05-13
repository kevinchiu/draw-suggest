#ifndef MTPAINT
#define MTPAINT

#include <sstream>

#include "ofMain.h"
#include "tuio.h"
#include "tuioCursor.h"
#include "tuioObject.h"


#define WIDTH 1024
#define HEIGHT 768
#define CELLS 2

class MTPaint : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
	
		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
	private:
	
		Tuio tuio;
		map<int,tuioCursor*> prevCursors;
		map<int,tuioObject*> prevObjects;
		bool drawing,suggested;
		double angle[CELLS][CELLS];
		int dirty[CELLS][CELLS];
		double pixelBufferH[WIDTH][HEIGHT];
		double pixelBufferV[WIDTH][HEIGHT];
	
		int pointConvolution(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int b1, int b2, int b3, int b4, int b5, int b6, int b7, int b8, int b9);
		void Sobel();
		double avgImgH(int x1, int y1, int x2, int y2);
		double avgImgV(int x1, int y1, int x2, int y2);
		double calcAngle(int x1, int y1, int x2, int y2);
		void setCamAngles();
	
};

#endif