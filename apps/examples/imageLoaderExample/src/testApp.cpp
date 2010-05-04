#include "testApp.h"
//--------------------------------------------------------------
int sensorWidth;
bool video = true;

int h[] = {
  -1,-2,-1,
  0,0,0,
  1,2,1,
};

int v[] = {
  1,0,-1,
  2,0,-2,
  1,0,-1
};


void testApp::setup(){	 
  
  cam.setVerbose(true);
  cam.initGrabber(320, 240, false);
  suggestion.allocate(CAM_WIDTH, CAM_HEIGHT, OF_IMAGE_GRAYSCALE);
  drawing.allocate(CAM_WIDTH, CAM_HEIGHT, OF_IMAGE_GRAYSCALE);
  
}

void testApp::update(){
  sensorWidth = drawing.getWidth();
	ofBackground(255,255,255);	
  cam.grabFrame();
  drawing.setFromPixels(cam.getPixels(), 320, 240, OF_IMAGE_COLOR, true);
  if (!video) {
    drawing.loadImage("daimond.jpg");
  }
  drawing.setImageType(OF_IMAGE_GRAYSCALE);
  setCamAngles();
  
  //load best match //TODO
  suggestion.loadImage("daimond.jpg");
  
}



//--------------------------------------------------------------
void testApp::draw(){	
	ofSetColor(255,255,255);
  drawing.draw(0, 0);
  
	ofSetColor(120,180,120);
  drawLines();
  drawCamAngles();
  
	ofSetColor(255,255,255);
  suggestion.draw(CAM_WIDTH, 0);
  
  
  //drawH();
  //drawV();

}

void testApp::drawCamAngles(){
  for (int i = 0; i < CELLS; i++) {
    for (int j = 0; j < CELLS; j++) {
      double a = angle[j][i];
      int x = (j + 0.5)*CAM_WIDTH/CELLS;
      int y = (i + 0.5)*CAM_HEIGHT/CELLS;
      
      ofLine(x - 5 * cos(a), y - 5 * sin(a), x + 5 * cos(a), y + 5 * sin(a));
    }
  }
}


void testApp::drawLines(){
  for (int i = 0; i < CAM_WIDTH; i += CAM_WIDTH/CELLS) {
    ofLine(i, 0, i, CAM_HEIGHT);
  }
  for (int i = 0; i < CAM_HEIGHT; i += CAM_HEIGHT/CELLS) {
    ofLine(0, i, CAM_WIDTH, i);
  }
  ofRect(CAM_WIDTH, 0, CAM_WIDTH, CAM_HEIGHT);
}

void testApp::drawH(){
  for (int i = 0; i < CAM_HEIGHT; i++) {
    for (int j = 0; j < CAM_WIDTH; j++) {
      double p = pixelBufferV[j][i]*200/3.14;
      ofSetColor(p,p,p);
      ofCircle(CAM_WIDTH + j, i, 1);
    }
  }
}

void testApp::drawV(){
  for (int i = 0; i < CAM_HEIGHT; i++) {
    for (int j = 0; j < CAM_WIDTH; j++) {
      double p = pixelBufferV[j][i]*200/3.14;
      ofSetColor(p,p,p);
      ofCircle(2*CAM_WIDTH + j, i, 1);
    }
  }
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	video = !video;
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

//--------------------------------------------------------------


int testApp::pointConvolution(int a1, int a2, int a3, 
                              int a4, int a5, int a6,
                              int a7, int a8, int a9,
                              int b1, int b2, int b3,
                              int b4, int b5, int b6,
                              int b7, int b8, int b9){
  
  int i = a1*b1 + a2*b2 + a3*b3 +
  a4*b4 + a5*b5 + a6*b6 + 
  a7*b7 + a8*b8 + a9*b9; 
  
  return i;
  
}
int p[9];
void testApp::vSobel(){
  
  unsigned char * pixels = drawing.getPixels();
  for (int i = 1; i < CAM_HEIGHT - 1; i++) {
    for (int j = 1; j < CAM_WIDTH - 1; j++) {
      p[0] = pixels[(i-1)*sensorWidth+j-1];
      p[1] = pixels[(i-1)*sensorWidth+j-0];
      p[2] = pixels[(i-1)*sensorWidth+j+1];
      p[3] = pixels[(i-0)*sensorWidth+j-1];
      p[4] = pixels[(i-0)*sensorWidth+j-0];
      p[5] = pixels[(i-0)*sensorWidth+j+1];
      p[6] = pixels[(i+1)*sensorWidth+j-1];
      p[7] = pixels[(i+1)*sensorWidth+j-0];
      p[8] = pixels[(i+1)*sensorWidth+j+1];
      
      pixelBufferV[j][i] = pointConvolution(p[0],p[1],p[2],
                                            p[3],p[4],p[5],
                                            p[6],p[7],p[8],
                                            v[0],v[1],v[2],
                                            v[3],v[4],v[5],
                                            v[6],v[7],v[8])/8.0;
    }
  }
}


void testApp::hSobel(){
  
  unsigned char * pixels = drawing.getPixels();
  for (int i = 1; i < CAM_HEIGHT - 1; i++) {
    for (int j = 1; j < CAM_WIDTH - 1; j++) {
      p[0] = pixels[(i-1)*sensorWidth+j-1];
      p[1] = pixels[(i-1)*sensorWidth+j-0];
      p[2] = pixels[(i-1)*sensorWidth+j+1];
      p[3] = pixels[(i-0)*sensorWidth+j-1];
      p[4] = pixels[(i-0)*sensorWidth+j-0];
      p[5] = pixels[(i-0)*sensorWidth+j+1];
      p[6] = pixels[(i+1)*sensorWidth+j-1];
      p[7] = pixels[(i+1)*sensorWidth+j-0];
      p[8] = pixels[(i+1)*sensorWidth+j+1];
      pixelBufferH[j][i] = pointConvolution(p[0],p[1],p[2],
                                            p[3],p[4],p[5],
                                            p[6],p[7],p[8],
                                            h[0],h[1],h[2],
                                            h[3],h[4],h[5],
                                            h[6],h[7],h[8])/8.0;
    }
  }
}

double testApp::avgImgH(int x1, int y1, int x2, int y2) {
  double total = 0;
  for (int i = y1; i < y2; i++) {
    for (int j = x1; j < x2; j++) {
      total += pixelBufferH[j][i];
    }
  }
  return total/((x2 - x1) * (y2 - y1));
}

double testApp::avgImgV(int x1, int y1, int x2, int y2) {
  double total = 0;
  for (int i = y1; i < y2; i++) {
    for (int j = x1; j < x2; j++) {
      total += pixelBufferV[j][i];
    }
  }
  return total/((x2 - x1) * (y2 - y1));
}

double testApp::calcAngle(int x1, int y1, int x2, int y2) {
  double h = avgImgH(x1, y1, x2, y2);
  double v = avgImgV(x1, y1, x2, y2);
  return atan(h/v);
}

void testApp::setCamAngles(){
  hSobel();
  vSobel();
  for (int i = 0; i < CELLS; i += 1) {
    for (int j = 0; j < CELLS; j+= 1) {
      int x1 = j*CAM_WIDTH/CELLS;
      int y1 = i*CAM_WIDTH/CELLS;
      int x2 = (j+1)*CAM_WIDTH/CELLS;
      int y2 = (i+1)*CAM_WIDTH/CELLS;
      
      angle[j][i] = calcAngle(x1,y1,x2,y2);
    }
  }
}

