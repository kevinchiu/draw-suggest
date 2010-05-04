#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#define IMAGE_WIDTH 500
#define IMAGE_HEIGHT 500
#define CAM_WIDTH 480
#define CAM_HEIGHT 480
#define CELLS 5

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
  ofImage cell;
  ofImage sobelCell;
  ofVideoGrabber cam;
  
  double angle[CELLS][CELLS];
  
  void drawLines();
  void setCamAngles();
  void drawCamAngles();
  double angleOf(ofImage image);
  double sumImg(ofImage image);
  ofImage hSobel(ofImage image);
  ofImage vSobel(ofImage image);
  int pointConvolution(int a1, int a2, int a3, 
                       int a4, int a5, int a6,
                       int a7, int a8, int a9,
                       int b1, int b2, int b3,
                       int b4, int b5, int b6,
                       int b7, int b8, int b9);

};

#endif	

