#pragma once

#include "ofMain.h"
#include "AudioVisualizer.h"
#include <vector>
#include <iostream>
using namespace std;

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void timer();

	void drawMode1(vector<float> amplitudes);
	void drawMode2(vector<float> amplitudes);
	void drawMode3(vector<float> amplitudes);
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void Recorder(int key);

	bool booleanTimer(int intervalToReturnBool);

private:
	ofSoundPlayer sound;
	AudioVisualizer visualizer;

	bool recording = false;
	bool playing = false;
	char mode = '1';
	vector<int> keystrokes;
};
