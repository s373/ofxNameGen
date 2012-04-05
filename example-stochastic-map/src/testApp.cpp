#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(60);
			
	namegen.setup("lob-test.txt");	// read input file
	namegen.setNumLetters(7);		// set num letters
}

//--------------------------------------------------------------
void testApp::update(){
	
	space += ofMap(mouseY, 0, ofGetHeight(), 0., 1e-3);
//	fmodf(space, 1e7);
//	seed = (int)(space * 1e12);
	seed = (int)(space);
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(255);
	ofSetColor(0);

	float prob = ofMap(mouseX, 0, ofGetWidth(), 0., 1e-3);
	int grid = ofGetWidth()*ofGetHeight();
	
	for(int i=0; i<grid; i++){

		int x = i % ofGetWidth();
		int y = i / ofGetHeight();
		int flower = seed + x + y *ofGetWidth();

		
		if(ofRandomuf()<prob){
									
			ofSeedRandom(flower);

			ofEllipse(x, y, 10, 10);
			
			ofDrawBitmapString( namegen.generate() ,  x - 7, y + 15  ) ;			
			
		}
	}
	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}