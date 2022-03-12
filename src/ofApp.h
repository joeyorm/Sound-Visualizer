#pragma once

#include "ofMain.h"
#include "AudioVisualizer.h"
#include <vector>
#include <iostream>
#include "Screens.h"
#include <bits/stdc++.h>
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


	bool helpButtons = false;
	bool cancel = false;
	bool replay = false;


	bool ampStop = false;
	bool startFinish = false;

	bool bPressed = false;
	bool BPressed = false;
	bool nPressed = false;
	bool NPressed = false;
	bool mousepressed = false;
	bool wrongPress = false;
	bool fade = true;
	bool pause = false;

	float randomInt1;
	float randomInt2;
	float randomInt3;
	
	int secondsPassed = 0;
	int visualMultiplier = 1;
	double currentVol;

	int iter = 0;
	int iter2 = 0;
	int fader = 255; 
	int k = 0;
	int n = 5;
	int l = 20;
	int nextOne = 0;
	int nextBackground = 0;
	int keyVal;
	int secPass = 0;
	int visualizerMultiplier = 1;
	int file_index = -1;
	float time = 255;

	ofTrueTypeFont myFont1;
	ofTrueTypeFont myFont2;
	ofTrueTypeFont myFont3;
	ofTrueTypeFont myFont4;
	ofTrueTypeFont myFont5;

	string currentMusic;
	string pressP;
	string keyStrokeRecord;
	string FPS;

	ofBoxPrimitive newBox;
	ofEasyCam cam;

	vector<string> playlist = {"My_Wife_2_Dogs.wav","beat.wav", "Way_Less_Sad.wav", "Believer.wav","high_hopes.wav","Truman.mp3","kissy_kissy.mp3", "I_Got_3.mp3", "Head_In_The_Clouds.mp3", "Sunroof.mp3", "Hands_On_You.mp3", "BACK_AND_FORTH.mp3"};
	vector<string> backgroundImages = {"ultraviolet.jpg","KeepitSimple.png","LetsStartAgain.png", "NeverForgetWhereYouStarted.png"};
	ofLight light;

	Screens menu;
	Screens welcomeScreen;

	ofImage imageBg;
	ofImage pauseButton;
	ofImage playButton;
	ofImage ImgRecording;
	ofImage ImgReplay;


bool booleanTimer(int intervalToReturnBool) // becomes true every n seconds for one frame
	{
		if (ofGetFrameNum() % (60 * intervalToReturnBool) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

string remSpecificChar(string text, char toRemove, string toReplace)
{
    string newString = "";

    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] == toRemove)
        {
            newString += toReplace;
        }
        else
        {
            newString += text[i];
        }
    }
    return newString;
}
private:
	ofSoundPlayer sound;
	AudioVisualizer visualizer;

	bool recording = false;
	bool playing = false;
	char mode = '1';
	vector<int> keystrokes;
};


