#include "ofApp.h"
#include <vector>
#include <iostream>
using namespace std;

//--------------------------------------------------------------
void ofApp::setup()
{
    sound.loadSound("beat.wav");       // Loads a sound file (in bin/data/)
    sound.setLoop(true);               // Makes the song loop indefinitely
    sound.setVolume(1);                // Sets the song volume
    ofSetBackgroundColor(256, 256, 256);
    myFont1.load("Metropo.ttf", 30);
    myFont2.load("Carbon.ttf", 30);
    myFont3.load("Gravis.ttf",30);
    myFont4.load("Highup.ttf",30);
     // Sets the Background Color                    // sets the timer to 0
}

//--------------------------------------------------------------
void ofApp::update()
{
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate();               // Updates all sound players
    visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    timer();                       // Updates the iterator every second (nonstop)
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofColor colorOne(255, 187, 187);
    ofColor colorTwo(255, 228, 192);
    ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_LINEAR);
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */

    if (!playing)
    {   
        myFont3.drawString("Press 'P' to play some music!", ofGetWidth() / 2 - 50, ofGetHeight() / 2 );
        // ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth() / 2 - 50, ofGetHeight() / 2);
        ofDrawBitmapString(keystrokes.size(), ofGetWidth() / 2, ofGetHeight() / 2 - 40);
        ofDrawBitmapString(to_string(ofGetFrameNum() % 60), ofGetWidth() / 2, ofGetHeight() / 2 - 25);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    if (mode == '1')
    {
        drawMode1(amplitudes);
    }
    else if (mode == '2')
    {
        drawMode2(amplitudes);
    }
    else if (mode == '3')
    {
        drawMode3(amplitudes);
    }
}
void ofApp::drawMode1(vector<float> amplitudes)
{
    ofFill(); // Drawn Shapes will be filled in with color
              // ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
    if (booleanTimer(5))
    {
        ofSetColor(ofRandom(0, 135), ofRandom(0, 255), ofRandom(0, 255));
    }
    ofDrawRectangle(2, ofGetHeight() - 100, 50, amplitudes[0]);
    // ofSetColor(256);
}
void ofApp::drawMode2(vector<float> amplitudes)
{
    ofSetLineWidth(5); // Sets the line width
    ofNoFill();        // Only the outline of shapes will be drawn
    // ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++)
    {
        if (booleanTimer(5))
        {
            ofSetColor((bands - i) * 32 % 256, ofRandom(0, 255), ofRandom(0, 255));
        } // Color varies between frequencies
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[0] / (i + 1));
    }
}

void ofApp::drawMode3(vector<float> amplitudes)
{
    if (booleanTimer(5))
    {
        ofSetColor(ofRandom(0, 135), ofRandom(0, 255), ofRandom(0, 255));
    } // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Width Visualizer", 0, 15);
    // YOUR CODE HERE
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    // This method is called automatically when any key is pressed

    switch (key)
    {
    case 'p':
        if (playing)
        {
            sound.stop();
        }
        else
        {
            sound.play();
        }
        playing = !playing;
        break;
    case '1':
        mode = '1';
        break;
    case '2':
        mode = '2';
        break;
    case '3':
        mode = '3';
        break;
    case 'r':
        if (recording)
        {
            recording = false;
        }
        else
        {
            recording = true;
        }

    }
    if (recording)
    {
        this->Recorder(key);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

void ofApp::Recorder(int key)
{

    this->keystrokes.push_back(key);
    cout << keystrokes.size() << endl;
}

void ofApp::timer()
{
    if (ofGetFrameNum() % 60 == 0)
    {
        int secondsPassed;
        secondsPassed++;
    }
}

bool ofApp::booleanTimer(int intervalToReturnBool)
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