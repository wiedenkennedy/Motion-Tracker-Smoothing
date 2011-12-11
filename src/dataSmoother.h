/*
 *  dataSmoother.h
 *  moviePlayerExample
 *
 *  Created by William Hooke on 10/12/2011.
 *  Copyright 2011 Wieden + Kennedy. All rights reserved.
 *
 */

#ifndef _DATA_SMOOTHER
#define _DATA_SMOOTHER

#pragma once

#include "ofMain.h"
#include "testApp.h"
#include "ofxXmlSettings.h"

class frameTriangle {
	public:
		float pt1x;
		float pt1y;
		
		float pt2x;
		float pt2y;
		
		float pt3x;
		float pt3y;
		
		int frameNum;
	private:
		// private stuff
};

class dataSmoother {
	public:
		
		float pt1SmoothVal;
		float pt2SmoothVal;
		float pt3SmoothVal;	
		bool shapeLocked;
		
		ofxXmlSettings origXml;
	
		int totalFrames;
	
		float Pt1x[866];
		float Pt1y[866];
		
		float Pt2x[866];
		float Pt2y[866];
		
		float Pt3x[866];
		float Pt3y[866];
		
		int FrameNum[866];
		
	
		//vector<frameTriangle> origFrameTris;
		//vector<frameTriangle> smoothFrameTris;
		
		int curFrame;
	
		void drawGui();
		void loadXML();
		void drawTriangles(int curFrame);
		void updateValues();
		void saveXML();
		
	private:
		//private stuff
};


#endif
	