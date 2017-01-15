#include "lineAnalysis.h"

LineAnalysis::LineAnalysis() {
	m = 3;
	//line = l;
	// s, t 初期化
	
}

void LineAnalysis::setup(ofPolyline _line) {
	FOR(i, _line.size()) {
		line.addVertex((_line.getVertices()[i].x - 100)/800.0, (-_line.getVertices()[i].y + 900)/800.0);
	}
	cout << line.getVertices()[0] << endl;
	cout << line.getVertices()[line.size()-1] << endl;
}

/*
* 最小二乗法
*/
ofPolyline LineAnalysis::calcLeastSquaresMethod()
{
	// 測定データ
	vector<ofVec2f> pos;
	FOR(i, line.size()) {
		pos.push_back(line.getVertices()[i]);
	}
	int N = line.size();
	double min = INT_MAX;

	const int num = 50;
	const int ARR = num;
	double a[ARR + 1][ARR + 2], s[2 * ARR + 1], t[ARR + 1];

	int MWhenMin = 2;
	for(int M = 2; M < num; M++){
		FOR(i, 2 * M + 1) {
			s[i] = 0;
		}
		FOR(i, M + 1) {
			t[i] = 0;
		}
		// s[], t[] 計算
		FOR(i, N) {
			//cout << pos[i] << endl;
			FOR(j, 2 * M + 1) {
				s[j] += pow(pos[i].x, j);
				//cout << s[j] << endl;
			}
			FOR(j, M + 1) {
				t[j] += pow(pos[i].x, j) * pos[i].y;
				//cout << t[j] << endl;
			}
		}

		// a[][] に s[], t[] 代入
		FOR(i, M + 1) {
			FOR(j, M + 1) {
				a[i][j] = s[i + j];
			}
			a[i][M + 1] = t[i];
		}

		// 掃き出し
		FOR(k, M + 1) {
			p = a[k][k];
			for (int j = k; j <= M + 1; j++) {
				a[k][j] /= p;
			}
			FOR(i, M + 1) {
				if (i != k) {
					d = a[i][k];
					for (int j = k; j <= M + 1; j++) {
						a[i][j] -= d*a[k][j];
					}
				}
			}
		}

		// y 値計算＆結果出力
		vector<float> dist;
		//dist.erase();
		vector<double> vSum;
		double sum = 0;
		FOR(i, M + 1) {
			//cout << "a[" << i << "] = " << a[i][M + 1] << endl;
			FOR(k, N) {
				cout << "Over chech M:" << M << ",a[]:" << a[i][M + 1] << a[i][M + 1] * pow(pos[k].x, i);
				cout << "sum:" << a[i][M + 1] * pow(pos[k].x, i) - pos[k].y << endl;
				sum += abs(a[i][M + 1] * pow(pos[k].x, i) - pos[k].y); //posXiにおけるyの値
				//vSum.push_back()
			}
		}

		double sumDist = sum;
		//cout << sum << endl;
		if (min > sumDist) {
			min = sumDist;
			MWhenMin = M;
		}
	}
	ofPolyline func;
	for (double px = 0; px <= line.getVertices()[line.size() - 1].x; px += 0.01) {
		double py = 0;
		FOR(k, MWhenMin + 1) {
			py += a[k][MWhenMin + 1] * pow(px, k);
		}
		FOR(i, MWhenMin + 1) {
			//cout << "a[" << i << "] = " << a[i][MWhenMin + 1] << endl;
		}
		//cout << "x:" << px << ",y:" << py << endl;
		func.addVertex(px, py);
	}
	cout << "M:" << MWhenMin << endl;
	return func;
}

ofPolyline LineAnalysis::calc() {
	float y = 0;
	float dist = 0;
	float min = INT_MAX;
	float aWhenMin = 0;
	vector<float> bWhenMin;
	//int x = 0;
	FOR(a, m) { //xの個数 例:a=2:x^2+x
		dist = 0;
		FOR(h, a) { //何回ループを回すか、係数が何個必要か
			FOR(b, m) { //xの係数 例:a=1, b=3:3x
				bWhenMin.push_back(b);
				dist = 0;
				FOR(i, line.size()) {
					y = float(b)*pow(line.getVertices()[i].x, a);
					dist += sq(ofVec2f(line.getVertices()[i].x, y), line.getVertices()[i]);
					cout << "y dist:"<< sq(ofVec2f(line.getVertices()[i].x, y), line.getVertices()[i]) <<","<<dist<< endl;
					/*if (i == line.size() - 1 && a == 1) {
						cout << "d:" << pow(line.getVertices()[i].x, a) <<","<< y <<",b:"<<b<< endl;
					}*/
				}
				cout << a << "," << b << "," << dist << endl;
				if (dist < min) {
					min = dist;
					//cout << dist << endl;
					aWhenMin = a;
				}
				/*else {
					bWhenMin.clear();
				}*/
			}
		}
	}
	cout << "a_min:" << aWhenMin << ", b_min:" <<bWhenMin.size()<< endl;
	ofPolyline func;
	y = 0;
	FOR(i, line.size()) {
		FOR(a, aWhenMin + 1) {
			FOR(b, bWhenMin.size() + 1) {
				y += b*pow(line.getVertices()[i].x, a);
			}
		}
		func.addVertex(line.getVertices()[i].x, y);
		//cout << line.getVertices()[i].x << "," << i << endl;
	}
	return func;
}

float LineAnalysis::sq(ofVec2f pos1, ofVec2f pos2) {
	return ofDist(pos1.x, pos1.y, pos2.x, pos2.y);
}

/*
int LineAnalysis::sumSq(int in) {
	//int min = INT_MAX;
	int sum = 0;
	FOR(i, line.size()) {
		//sum += sp(line.getVertices()[i], )
	}
	return sum;
}
*/
