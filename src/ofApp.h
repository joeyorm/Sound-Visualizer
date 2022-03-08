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
	void drawMode4(vector<float> amplitudes);
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
	


	bool booleanTimer(int intervalToReturnBool);
	bool helpButtons = false;
	bool cancel = false;
	bool replay = false;
	bool nextMusic = false;

	float randomInt1;
	float randomInt2;
	float randomInt3;
	int secondsPassed;
	double currentVol;

	int iter = 0;
	int iter2 = 0;
	int k = 0;
	int nextOne = 0;
	int keyVal;
	
	ofTrueTypeFont myFont1;
	ofTrueTypeFont myFont2;
	ofTrueTypeFont myFont3;
	
	string currentMusic;
	string pressP;
	string keyStrokeRecord;
	string FPS;

	ofBoxPrimitive newBox;
	ofEasyCam cam;
	

	vector<string> playlist = {"beat.wav", "geesebeat.wav", "pigeon-coo.wav", "rock-song.wav"};

	ofLight light;



private:
	ofSoundPlayer sound;
	AudioVisualizer visualizer;

	bool recording = false;
	bool playing = false;
	char mode = '1';
	vector<int> keystrokes;
	
};
