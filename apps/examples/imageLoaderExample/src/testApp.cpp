#include "testApp.h"

double h[] = {
  -1,-2,-1,
  0,0,0,
  1,2,1
};

double v[] = {
  -1,0,1,
  -2,0,2,
  -1,0,1
};



//--------------------------------------------------------------

int testApp::pointConvolution(int a1, int a2, int a3, 
                     int a4, int a5, int a6,
                     int a7, int a8, int a9,
                     int b1, int b2, int b3,
                     int b4, int b5, int b6,
                     int b7, int b8, int b9){
  return
  a1*b1 +
  a2*b2 +
  a3*b3 +
  a4*b4 +
  a5*b5 +
  a6*b6 +
  a7*b7 +
  a8*b8 +
  a9*b9; 
}

void testApp::setup(){	 
  cam.setVerbose(true);
  cam.initGrabber(640, 480, false);
  suggestion.allocate(IMAGE_WIDTH, IMAGE_HEIGHT, OF_IMAGE_GRAYSCALE);
  drawing.allocate(CAM_WIDTH, CAM_HEIGHT, OF_IMAGE_GRAYSCALE);
  cell.allocate(CAM_WIDTH/CELLS, CAM_HEIGHT/CELLS, OF_IMAGE_GRAYSCALE);
  sobelCell.clone(cell);
  printf("max int: %i", INT_MAX);
}
ofImage testApp::vSobel(ofImage image){
  int iWidth = image.getWidth();
  int iHeight = image.getHeight();
  
  unsigned char * pixels = image.getPixels();
  for (int i = 1; i < iHeight - 1; i++) {
    for (int j = 1; j < iWidth - 1; j++) {
      int p[] = {
        pixels[(i-1)*iWidth+j-1],
        pixels[(i-1)*iWidth+j-0],
        pixels[(i-1)*iWidth+j+1],
        pixels[(i-0)*iWidth+j-1],
        pixels[(i-0)*iWidth+j-0],
        pixels[(i-0)*iWidth+j+1],
        pixels[(i+1)*iWidth+j-1],
        pixels[(i+1)*iWidth+j-0],
        pixels[(i+1)*iWidth+j+1]
      };
      sobelCell.getPixels()[iWidth * i + j] = 
      pointConvolution(p[1],p[2],p[3],
                       p[4],p[5],p[6],
                       p[7],p[8],p[9],
                       v[1],v[2],v[3],
                       v[4],v[5],v[6],
                       v[7],v[8],v[9]);
    }
  }
  return sobelCell;
}


ofImage testApp::hSobel(ofImage image){
  int iWidth = image.getWidth();
  int iHeight = image.getHeight();

  unsigned char * pixels = image.getPixels();
  for (int i = 1; i < iHeight - 1; i++) {
    for (int j = 1; j < iWidth - 1; j++) {
      int p[] = {
        pixels[(i-1)*iWidth+j-1],
        pixels[(i-1)*iWidth+j-0],
        pixels[(i-1)*iWidth+j+1],
        pixels[(i-0)*iWidth+j-1],
        pixels[(i-0)*iWidth+j-0],
        pixels[(i-0)*iWidth+j+1],
        pixels[(i+1)*iWidth+j-1],
        pixels[(i+1)*iWidth+j-0],
        pixels[(i+1)*iWidth+j+1]
      };
      sobelCell.getPixels()[iWidth * i + j] = 
      pointConvolution(p[1],p[2],p[3],
                       p[4],p[5],p[6],
                       p[7],p[8],p[9],
                       h[1],h[2],h[3],
                       h[4],h[5],h[6],
                       h[7],h[8],h[9]);
    }
  }
  return sobelCell;
}

double testApp::sumImg(ofImage img) {
  double total = 0;
  for (int i = 0; i < img.getHeight(); i++) {
    for (int j = 0; j < img.getWidth(); j++) {
      total += img.getPixels()[i * (int)img.getWidth() + j];
    }
  }
  printf("sum $i", total);
  return total/256;
}

double testApp::angleOf(ofImage cell) {
  
  return atan2(sumImg(hSobel(cell)), 1.0);
}

void testApp::setCamAngles(){
  for (int i = 0; i < CELLS; i += 1) {
    for (int j = 0; j < CELLS; j+= 1) {
      cell.grabScreen(i*CAM_WIDTH/CELLS, j*CAM_HEIGHT/CELLS, CAM_WIDTH/CELLS, CAM_HEIGHT/CELLS);
      cell.resize(CAM_WIDTH/CELLS/2, CAM_HEIGHT/CELLS/2);
      angle[j][i] = angleOf(cell);
    }
  }
}
//--------------------------------------------------------------
void testApp::update(){
	ofBackground(255,255,255);	
  cam.grabFrame();
  drawing.setFromPixels(cam.getPixels(), 640, 480, OF_IMAGE_COLOR, true);
  drawing.setImageType(OF_IMAGE_GRAYSCALE);
  setCamAngles();
}

void testApp::drawCamAngles(){
  for (int i = 0; i < CELLS; i++) {
    for (int j = 0; j < CELLS; j++) {
      double a = angle[j][i];
      int x = (j + 0.5)*CAM_WIDTH/CELLS;
      int y = (i + 0.5)*CAM_HEIGHT/CELLS;
      
      ofLine(x, y, x + 10 * cos(a), y + 10 * sin(a));
    }
  }
}
void testApp::drawLines(){
  ofSetColor(255,255,255);
  for (int i = 0; i < CAM_WIDTH; i += CAM_WIDTH/CELLS) {
    ofLine(i, 0, i, CAM_HEIGHT);
  }
  for (int i = 0; i < CAM_HEIGHT; i += CAM_HEIGHT/CELLS) {
    ofLine(0, i, CAM_WIDTH, i);
  }
  ofRect(CAM_WIDTH, 0, CAM_WIDTH, CAM_HEIGHT);
}

//--------------------------------------------------------------
void testApp::draw(){	
	ofSetColor(0xFFFFFF);
  drawing.draw(0, 0);
  drawLines();
  drawCamAngles();
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
  
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
  
}
