/*
 *  dataSmoother.cpp
 *  moviePlayerExample
 *
 *  Created by William Hooke on 10/12/2011.
 *  Copyright 2011 Wieden + Kennedy. All rights reserved.
 *
 */

#include "ofMain.h"
#include "testApp.h"
#include "dataSmoother.h"
#include "ofxXmlSettings.h"


void dataSmoother::drawGui() {
	ofPushMatrix();
		ofTranslate(600, 600);
		ofSetColor(0);
		ofDrawBitmapString("press l to toggle shape lock: " + ofToString(shapeLocked) ,0,0);
		ofDrawBitmapString("point 1 smoothing (1 / q) : " + ofToString(pt1SmoothVal),0,20);
		ofDrawBitmapString("point 2 smoothing (2 / w) : " + ofToString(pt2SmoothVal),0,40);
		ofDrawBitmapString("point 3 smoothing (3 / e) : " + ofToString(pt3SmoothVal),0,60);
		ofDrawBitmapString("hit 'r' to reset",0,80);
		ofDrawBitmapString("hit 'x' to save new xml files",0,100);
	ofPopMatrix();
}


void dataSmoother::loadXML() {
	
	//ofDirectory choirFaceDir;
	//vector<ofFile> faceDataFiles;
	
	string filename = "xml/orig/boy 6 - row 1.xml";
	origXml.loadFile(filename);
	origXml.pushTag("CHOIRFACE");
	totalFrames = origXml.getNumTags("FRAME");
	printf("total frame tags found %i", totalFrames);
	
	//vector<frameTriangle> origFrameTris;
//	Pt1x[totalFrames];
//	Pt1y[totalFrames];
//	
//	Pt2x[totalFrames];
//	Pt2y[totalFrames];
//	
//	Pt3x[totalFrames];
//	Pt3y[totalFrames];
//	
//	FrameNum[totalFrames];	
	
	// load all the frame coords into a vector
	
	for (int i = 0; i < totalFrames; ++i) {
		origXml.pushTag("FRAME", i);
		
		Pt1x[i] = (origXml.getValue("POINT1:X", 0.0f)) - 472; //
		printf("point 1x: %f \n", origXml.getValue("POINT1:X", 0.0f)); //
		Pt1y[i] = (origXml.getValue("POINT1:Y", 0.0f)) - 192; //
		printf("point 1y: %f \n", origXml.getValue("POINT1:Y", 0.0f)); //
		
		Pt2x[i] = (origXml.getValue("POINT2:X", 0.0f)) - 472; //
		printf("point 2x: %f \n", origXml.getValue("POINT2:X", 0.0f)); //
		Pt2y[i] = (origXml.getValue("POINT2:Y", 0.0f)) - 192; //
		printf("point 2y: %f \n", origXml.getValue("POINT2:Y", 0.0f)); //
		
		Pt3x[i] = (origXml.getValue("POINT3:X", 0.0f)) - 472; //
		printf("point 3x: %f \n", origXml.getValue("POINT3:X", 0.0f)); //
		Pt3y[i] = (origXml.getValue("POINT3:Y", 0.0f)) - 192; //
		printf("point 3y: %f \n", origXml.getValue("POINT3:Y", 0.0f)); //Pt3y[i] = origXml.getValue("POINT3:Y", 0);
		
		//FrameNum[i] = i;
				
		//origFrameTris.push_back(curPt1x, curPt1y, curPt2x, curPt2y, curPt3x, curPt3y, curFrameNum);
		origXml.popTag();
	}
	
	//printf("xml loaded in %i %f", FrameNum[10], Pt1x[10]);
	
	printf("triangle x1: %f y1: %f x2: %f y2: %f x3: %f y3: %f", Pt1x[0], Pt1y[0], Pt2y[0], Pt2y[0], Pt3x[0], Pt3y[0]);

	//then make a copy of the vector. we will smooth the values in the copy, using the original as for reference
	
	/*
	string filename = "myfile.xml";
	ofxXmlSettings xml;
	xml.loadFile(fileName);
	interactionLevel = (int)xml.getAttribute(ofToString("CHOIRFACE"), ofToString("interactionLevel"), 0, 0);
	xml.pushTag("CHOIRFACE");
	for (int i = 0; i < xml.getNumTags("FRAME"); ++i)
	{
		xml.pushTag("FRAME", i);
		ofVec2f pt1(xml.getValue("POINT1:X", 0) + CROP_SHIFT.x, xml.getValue("POINT1:Y", 0) + CROP_SHIFT.y);
		ofVec2f pt2(xml.getValue("POINT2:X", 0) + CROP_SHIFT.x, xml.getValue("POINT2:Y", 0) + CROP_SHIFT.y);
		ofVec2f pt3(xml.getValue("POINT3:X", 0) + CROP_SHIFT.x, xml.getValue("POINT3:Y", 0) + CROP_SHIFT.y);
		frames.push_back(Frame(pt1, pt2, pt3));
		xml.popTag();
	}
	*/
}

void dataSmoother::drawTriangles(int curFrame) {
	// draw the triangles if data loaded
	//ofPushMatrix();
	
	//curFrame = fingerMovie.getCurrentFrame();
		
	ofSetColor(255,0,0);
	ofNoFill();
	ofRect(200, 200, 100, 100);
	ofLine(10, 30, 150, 60); //ofLine(frames[frameNum].p1, frames[frameNum].p2);
	
	//ofTriangle( Pt1x[curFrame], Pt1y[curFrame], Pt2y[curFrame], Pt2y[curFrame], Pt3x[curFrame], Pt3y[curFrame]);
	
	ofEnableSmoothing();
	
	ofLine(Pt1x[curFrame], Pt1y[curFrame], Pt2y[curFrame], Pt2y[curFrame]);
	ofLine(Pt2y[curFrame], Pt2y[curFrame], Pt3x[curFrame], Pt3y[curFrame]);
	ofLine(Pt3x[curFrame], Pt3y[curFrame], Pt1x[curFrame], Pt1y[curFrame]);
	
	ofDisableSmoothing();
	//printf("triangle x1:%f y1:%f x2:%f y2:%f x3:%f y3:%f", Pt1x[curFrame], Pt1y[curFrame], Pt2y[curFrame], Pt2y[curFrame], Pt3x[curFrame], Pt3y[curFrame]);
	
	//ofLine(frames[frameNum].p2, frames[frameNum].p3);
	//ofLine(frames[frameNum].p3, frames[frameNum].p1);
	//ofPopMatrix();
}

void dataSmoother::updateValues() {
	// if the slider value has changed, smooth values
	// slider values vary number of mean average sample values either side the frame for smoothing.
}

void dataSmoother::saveXML() {
	// once happy with the smoothing, write out 25 new xml files in a new folder
}