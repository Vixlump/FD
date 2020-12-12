#include "ofApp.h"
#include "fdge.rve.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0,0,0,255);
	fdge_rve_setup();
	ofSetWindowShape(rve_x, rve_y);
	switch (rve_fullscreen) {

	case true:
		ofToggleFullscreen();
		break;

	case false:
		break;

	default:
		break;
	}
	rve_x = ofGetWindowWidth();
	rve_y = ofGetWindowHeight();
}

//--------------------------------------------------------------
void ofApp::update(){
	fdge_rve_music();
	fdge_rve_sound();
	fdge_rve_video_start();
	fdge_rve_video_update();
	fdge_rve_case();
	if (rve_scene_change == true) { fdge_rve_changescene(); }
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofPushMatrix();
	ofTranslate(rve_x/2, rve_y/2);
	switch (rve_background_type) {
		case 0:
			//sta_img
			fdge_rve_background_image();
			break;
		case 1:
			//sta_vid
			fdge_rve_background_video();
			break;
		case 2:
			//360_img
			fdge_rve_background_360image();
			break;
		case 3:
			//360_vid
			fdge_rve_background_360video();
			break;
		default:
			//none
			break;
	}
	fdge_rve_imagenvid();
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	x -= ofGetWidth() / 2;
	y -= ofGetHeight() / 2;
	//cout << "x" << x << "y" << y << endl;
	fdge_rve_click_box(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
