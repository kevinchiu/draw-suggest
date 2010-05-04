#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#define CAM_WIDTH 240
#define CAM_HEIGHT 240
#define CELLS 8

class testApp : public ofBaseApp{
	
public:
  
  void setup();
  void update();
  void draw();
  
  void keyPressed  (int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  
  ofImage drawing;
  ofImage suggestion;
  ofVideoGrabber cam;
  
  double angle[CELLS][CELLS];
  double pixelBufferH[CAM_WIDTH][CAM_HEIGHT];
  double pixelBufferV[CAM_WIDTH][CAM_HEIGHT];
  void drawLines();
  void setCamAngles();
  void drawCamAngles();
  void calcResult();
  double calcAngle(int x1, int x2, int y1, int y2);
  double avgImgV(int x1, int y1, int x2, int y2);
  double avgImgH(int x1, int y1, int x2, int y2);
  void hSobel();
  void vSobel();
  void drawH();
  void drawV();
  int pointConvolution(int a1, int a2, int a3, 
                       int a4, int a5, int a6,
                       int a7, int a8, int a9,
                       int b1, int b2, int b3,
                       int b4, int b5, int b6,
                       int b7, int b8, int b9);
  
  
  
};

#endif	

