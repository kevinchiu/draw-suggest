#include "MTPaint.h"

//--------------------------------------------------------------
void MTPaint::setup(){
	
	tuio.init();
	
	//openFrameworks setup
    ofSetFrameRate(60);
    ofSetColor(0, 0, 0);
    ofEnableSmoothing();
    ofSetBackgroundAuto(false);
    ofBackground(255, 255, 255);
	ofSetWindowTitle("Natural Paint");
	
	suggested = true;
	drawing = false;
	
}

//--------------------------------------------------------------
void MTPaint::update(){
	
	tuio.getMessages();
	
	if(!drawing && !suggested){
		setCamAngles();
		suggested = true;
		cout << "----------------\n";
		for (int i = 0; i < CELLS; i++) for (int j = 0; j < CELLS; j++){
			double a = angle[j][i];
			cout << j << "|" << i << ": " << a << "\n";
		}
	}
	
}


//--------------------------------------------------------------
void MTPaint::draw(){
	
	drawing = false;
	
	//Drawing Cursors
    ofSetColor(0,0,0);
    ofSetLineWidth(10);
	map<int,tuioCursor*> currentCursors;
	map<int,tuioCursor*>::reverse_iterator rit;
	for ( rit = tuio.cursors.rbegin() ; rit != tuio.cursors.rend(); rit++ ) {
		drawing = true;
		suggested = false;
		tuioCursor* aux = rit->second; 
		if(prevCursors.count(aux->getId()) != 0) ofLine(prevCursors[aux->getId()]->getX()*ofGetWidth(),prevCursors[aux->getId()]->getY()*ofGetHeight(),aux->getX()*ofGetWidth(),aux->getY()*ofGetHeight());
		ofEllipse(aux->getX()*ofGetWidth(), aux->getY()*ofGetHeight(), 10.0, 10.0);
		currentCursors.insert ( pair<int,tuioCursor*>(aux->getId(), new tuioCursor(aux)) );
		
//		//update dirty cells
//		float x = aux->getX();
//		float y = aux->getY();
//		
//		int cell_x = CELLS * x;
//		int cell_y = CELLS * y;
//		
//		dirty[cell_x][cell_y] = 1;
		

		
		
	}
	prevCursors = currentCursors;
	
    //Erasing Objects
    ofSetColor(255,255,255);
	map<int,tuioObject*> currentObjects;
	map<int,tuioObject*>::reverse_iterator rit2;
	for( rit2 = tuio.objects.rbegin() ; rit2 != tuio.objects.rend() ; rit2++ ) {
		drawing = true;
		suggested = false;
		tuioObject* aux = rit2->second;
		if(prevObjects.count(aux->getId()) != 0) ofLine(prevObjects[aux->getId()]->getX()*ofGetWidth(),prevObjects[aux->getId()]->getY()*ofGetHeight(),aux->getX()*ofGetWidth(),aux->getY()*ofGetHeight());
		ofEllipse(aux->getX()*ofGetWidth(), aux->getY()*ofGetHeight(), max(aux->getWidth(),aux->getHeight())*ofGetWidth(), max(aux->getWidth(),aux->getHeight())*ofGetWidth());
		currentObjects.insert( pair<int,tuioObject*>(aux->getId(), new tuioObject(aux)) );
		
		
	}
	prevObjects = currentObjects;
	
	//update dirty cells
	
	ofImage screen;
	int w = ofGetWidth();
	int h = ofGetHeight();
	screen.grabScreen(0, 0, w, h);
	unsigned char * pix = screen.getPixels();
	cout << "---\n";
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			
		}
	}
	screen.draw(0, 0);
	
}

//--------------------------------------------------------------
void MTPaint::keyPressed  (int key){
	
	ofImage screen;
	string filename;
	std::stringstream out;
	
	switch (key) {
        case 'B':
            ofBackground(255, 255, 255);
            break;
        case 'b':
            ofBackground(255, 255, 255);
            break;
		case 's':
			screen.grabScreen(0,0,ofGetWidth(),ofGetHeight());
			filename = "img";
			out << ofGetHours() << ofGetMinutes() << ofGetSeconds();
			filename.append(out.str());
			filename.append(".png");
			screen.saveImage(filename);
			break;
		case 'S':
			screen.grabScreen(0,0,ofGetWidth(),ofGetHeight());
			filename = "img";
			out << ofGetHours() << ofGetMinutes() << ofGetSeconds();
			filename.append(out.str());
			filename.append(".png");
			screen.saveImage(filename);
			break;
    }
	
}

//--------------------------------------------------------------
void MTPaint::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void MTPaint::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void MTPaint::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void MTPaint::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void MTPaint::windowResized(int w, int h){
	
}

int MTPaint::pointConvolution(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int b1, int b2, int b3, int b4, int b5, int b6, int b7, int b8, int b9){
	
	return a1*b1 + a2*b2 + a3*b3 + a4*b4 + a5*b5 + a6*b6 + a7*b7 + a8*b8 + a9*b9; 
	
}

void MTPaint::Sobel(){
	
	int p[9];
	int h[] = {-1,-2,-1,0,0,0,1,2,1};
	int v[] = {1,0,-1,2,0,-2,1,0,-1};
	
	ofImage screen;
	screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	unsigned char * pix = screen.getPixels();
	for (int i = 1; i < ofGetHeight() - 1; i++) {
		for (int j = 1; j < ofGetWidth() - 1; j++) {
			p[0] = pix[(i-1)*ofGetWidth()+j-1];
			p[1] = pix[(i-1)*ofGetWidth()+j-0];
			p[2] = pix[(i-1)*ofGetWidth()+j+1];
			p[3] = pix[(i-0)*ofGetWidth()+j-1];
			p[4] = pix[(i-0)*ofGetWidth()+j-0];
			p[5] = pix[(i-0)*ofGetWidth()+j+1];
			p[6] = pix[(i+1)*ofGetWidth()+j-1];
			p[7] = pix[(i+1)*ofGetWidth()+j-0];
			p[8] = pix[(i+1)*ofGetWidth()+j+1];
			//cout << pointConvolution(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],h[0],h[1],h[2],h[3],h[4],h[5],h[6],h[7],h[8])/8.0 << "-";
			pixelBufferH[j][i] = pointConvolution(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],h[0],h[1],h[2],h[3],h[4],h[5],h[6],h[7],h[8])/8.0;
			pixelBufferV[j][i] = pointConvolution(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8])/8.0;
		}
		//cout << "\n";
	}
	
}

double MTPaint::avgImgH(int x1, int y1, int x2, int y2) {
	
	double total = 0;
	
	for (int i = y1; i < y2; i++) for (int j = x1; j < x2; j++) total += pixelBufferH[j][i];
	
	cout << "avgImgH: " << total/((x2 - x1) * (y2 - y1)) << "\n";
	
	return total/((x2 - x1) * (y2 - y1));
	
}

double MTPaint::avgImgV(int x1, int y1, int x2, int y2) {
	
	double total = 0;
	
	for (int i = y1; i < y2; i++) for (int j = x1; j < x2; j++) total += pixelBufferV[j][i];
	
	cout << "avgImgV: " << total/((x2 - x1) * (y2 - y1)) << "\n";
	
	return total/((x2 - x1) * (y2 - y1));
	
}

double MTPaint::calcAngle(int x1, int y1, int x2, int y2) {
	
	double toReturn = atan(avgImgH(x1, y1, x2, y2)/avgImgV(x1, y1, x2, y2));
	if (toReturn != toReturn) {
		//this is NaN
		cout << "nan is caught\n";
		toReturn = 0;
	}
	cout << "calcAngle: " << toReturn << "\n"; 
	return toReturn;

}

void MTPaint::setCamAngles(){
	
	Sobel();
	for (int i = 0; i < CELLS; i++) for (int j = 0; j < CELLS; j++) {
		double thisAngle = calcAngle(j*ofGetWidth()/CELLS,i*ofGetWidth()/CELLS,(j+1)*ofGetWidth()/CELLS,(i+1)*ofGetWidth()/CELLS);
		angle[j][i] = thisAngle;
	}
	
}