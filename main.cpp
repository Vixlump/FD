#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include "ofMain.h"
#include "ofApp.h"


//========================================================================
int main(){

	ofSetupOpenGL(500, 500, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
