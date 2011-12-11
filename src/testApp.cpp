#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
	
	xmlSmoother.pt1SmoothVal = 0.0;
	xmlSmoother.pt2SmoothVal = 0.0;
	xmlSmoother.pt2SmoothVal = 0.0;
	xmlSmoother.shapeLocked = false;
	
	xmlSmoother.loadXML();
	
	frameByframe = false;

	fingerMovie.loadMovie("movies/choir-1080p-3.mov");
	fingerMovie.play();
		
}

//--------------------------------------------------------------
void testApp::update(){
    fingerMovie.idleMovie();
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(255);

    fingerMovie.draw(0,0, 1024, 576);
    ofSetColor(0);

	// draw some stats
	ofPushMatrix();
		ofTranslate(20, 600);
		ofSetColor(0);
		ofDrawBitmapString("press f to change",0,0);
		if(frameByframe) ofSetColor(133);
		ofDrawBitmapString("mouse speed position",0,20);
		if(!frameByframe) ofSetColor(133); else ofSetColor(0);
		ofDrawBitmapString("keys <- -> frame by frame " ,190,20);
		ofSetColor(0);

		ofDrawBitmapString("frame: " + ofToString(fingerMovie.getCurrentFrame()) + "/"+ofToString(fingerMovie.getTotalNumFrames()),0,60);
		ofDrawBitmapString("duration: " + ofToString(fingerMovie.getPosition()*fingerMovie.getDuration(),2) + "/"+ofToString(fingerMovie.getDuration(),2),0,80);
		ofDrawBitmapString("speed: " + ofToString(fingerMovie.getSpeed(),2),0,100);

		if(fingerMovie.getIsMovieDone()){
			ofSetHexColor(0xFF0000);
			ofDrawBitmapString("end of movie",0,120);
		}
	ofPopMatrix();
	
	xmlSmoother.drawGui();
	xmlSmoother.drawTriangles(fingerMovie.getCurrentFrame());
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    switch(key){
        case 'f':
            frameByframe=!frameByframe;
            fingerMovie.setPaused(frameByframe);
        break;
        case OF_KEY_LEFT:
            fingerMovie.previousFrame();
        break;
        case OF_KEY_RIGHT:
            fingerMovie.nextFrame();
        break;
        case '0':
            fingerMovie.firstFrame();
        break;
		
			
		// XML Smoothing keys	
		case '1':
			xmlSmoother.pt1SmoothVal += 0.01f;
			break;
		case 'q':
			if ( xmlSmoother.pt1SmoothVal < 0.02f ) {
				xmlSmoother.pt1SmoothVal = 0.0f;
			} else {
				xmlSmoother.pt1SmoothVal -= 0.01f;
			}
			break;
		case '2':
			xmlSmoother.pt2SmoothVal += 0.01f;
			break;
		case 'w':
			if ( xmlSmoother.pt2SmoothVal < 0.02f ) {
				xmlSmoother.pt2SmoothVal = 0.0f;
			} else {
				xmlSmoother.pt2SmoothVal -= 0.01f;
			}
			break;
		case '3':
			xmlSmoother.pt3SmoothVal += 0.01f;
			break;
		case 'e':
			if ( xmlSmoother.pt3SmoothVal < 0.02f ) {
				xmlSmoother.pt3SmoothVal = 0.0f;
			} else {
				xmlSmoother.pt3SmoothVal -= 0.01f;
			}
			break;
		case 'l':
			// lock shape size;
			xmlSmoother.shapeLocked =! xmlSmoother.shapeLocked;
			break;
		case 'r':
			//reset the values to the original
			// loadXml(); ??
			break;
		case 'x':
			// save out new XML
			break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	/*
	if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        float speed = (2 * pct - 1) * 5.0f;
        fingerMovie.setSpeed(speed);
	}
	*/
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        fingerMovie.setPosition(pct);
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(!frameByframe){
        fingerMovie.setPaused(true);
	}
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if(!frameByframe){
        fingerMovie.setPaused(false);
	}
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
