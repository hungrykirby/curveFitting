#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowShape(1000, 1000);
	moveFlag = false;
	posX = posY = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(255);
	ofSetColor(0);
	ofSetLineWidth(5);
	ofDrawRectangle(50, 850, 100, 100);
	ofDrawRectangle(850, 50, 100, 100);
	ofNoFill();
	ofDrawRectangle(100, 100, 800, 800);
	ofFill();
	if (moveFlag) {
		ofSetColor(20, 50, 80);
		ofDrawCircle(posX, posY, 20);
	}
	ofSetColor(200, 200, 100);
	//line.begin();
	for (int i = 0; i < pos.size(); i++) {
		
	}
	//line.end();
	//ofNoFill();
	ofSetLineWidth(5);
	line.draw();
	if (newLine.size() > 0) {
		ofSetColor(200, 100, 100);
		newLine.draw();
		ofDrawBitmapString("order of a expected polynomial : " + ofToString(lA._M), 20, 20);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if ('0' <= key && key <= '9') {
		lA.setM(key - '0');
	}
	else {
		line.clear();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	posX = x;
	posY = y;
	if (x > 900 && moveFlag) {
		line.addVertex(900, 100);
		moveFlag = false;
		line = line.getResampledByCount(100);
		lA.setup(line);
		try {
			_newLine = lA.calcLeastSquaresMethod();
		}
		catch (const bad_typeid e) {
			cerr << e.what();
		}
		for(int i = 0; i < _newLine.size(); i++){
			newLine.addVertex(_newLine.getVertices()[i].x*lA.rate + 100, -_newLine.getVertices()[i].y*lA.rate + 900);
		}
		//cout << newLine.getVertices()[0] << endl;
	}
	if (moveFlag) {
		pos.push_back(ofVec2f(x, y));
		line.addVertex(ofVec2f(x, y));
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	line.clear();
	newLine.clear();
	if (ofDist(x, y, 100, 900) < 50) {
		moveFlag = true;
		posX = 100;  posY = 900;
		pos.push_back(ofVec2f(100, 900));
		line.addVertex(100, 900);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (x > 900) {
		moveFlag = false;
	}
	pos.clear();
	//line.clear();
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
