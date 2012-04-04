#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(60);
			
	namegen.setup("lob-test.txt");	// read input file
	namegen.setNumLetters(3);		// set num letters
	namegen.post();					// watch the frequency table 
}

//--------------------------------------------------------------
void testApp::update(){
	if(ofGetFrameNum()% (int)ofMap(mouseX,0,ofGetWidth(), 2, 60) == 0){
		namegen.generate();			// generate new word from table
		namegen.setNumLetters((int)ofRandom(5,20));
		namegen.addWords(namegen.getWord()); // recursive add
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(0);
	ofSetColor(255);
	ofDrawBitmapString(namegen.getWord(), ofGetWidth()/2.12, 20);
	
	
	// draw frequency table
	glColor4f(0.7,0.9,0,1);
	string msg; char tstr[8];
	int * table = namegen.getFrequencyTablePtr();
	for( int j = 0; j<namegen.alphabet; j++){
		sprintf(tstr, "%02d ",j);
		msg += tstr;
		for(int i = 0; i < namegen.alphabet; i++){
			sprintf(tstr, " %02d ",table[i+j*namegen.alphabet]);
			msg += tstr;
		}
		msg += "\n";
	}
	
	ofDrawBitmapString(msg, 12,41);
	
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