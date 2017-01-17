#pragma once
#include<ofMain.h>

//#define M 15      // —\‘ª‹Èü‚ÌŸ”
#define FOR(a, b) for(int a = 0; a < b; a++)

class LineAnalysis {
public:
	LineAnalysis();
	ofPolyline line;
	ofPolyline calc();
	void setup(ofPolyline _line);
	void setM(int key);
	ofPolyline calcLeastSquaresMethod();
	ofPolyline lSM(vector<int> in); //Least-square method
	float sq(ofVec2f pos1, ofVec2f pos2); //ofDist to int
	float rate;
	int _M;

private:
	int m; // how many times for loop
	
	double p, d;
};