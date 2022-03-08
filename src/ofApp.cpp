#include "ofApp.h"
#include <vector>
#include <iostream>
using namespace std;

//--------------------------------------------------------------
void ofApp::setup()
{

    sound.loadSound(playlist[nextOne]); // Loads a sound file (in bin/data/)
    sound.setLoop(true);                // Makes the song loop indefinitely
    currentVol = 0.5;
    sound.setVolume(currentVol); // Sets the song volume
    ofSetBackgroundColor(256, 256, 256);
    myFont1.load("Lato-Regular.ttf", 15);
    myFont2.load("Gravis.ttf", 30);
    myFont3.load("Lato-Regular.ttf", 25);
    pressP = "Press 'P' to play some music!";
}

//--------------------------------------------------------------
void ofApp::update()
{
    ofSetBackgroundColor(256, 256, 256); // Sets the Background Color
    ofSoundUpdate();                     // Updates all sound players
    sound.setVolume(currentVol);
    timer(); // counts seconds passed since start

    if (not ampStop)
    {                                  // Sets volume when user presses "-" or "="
        visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    }

    if (booleanTimer(3))
    {
        randomInt1 = ofRandom(0, 255);
        randomInt2 = ofRandom(0, 255);
        randomInt3 = ofRandom(0, 255);
    }

    if (booleanTimer(2) && replay && not cancel) //(RECORDER)
    {
        keyPressed(keystrokes[k]);
        k++;
        if (k > keystrokes.size())
        {
            k = 0;
            keystrokes.clear();
            replay = false;
        }
    }

    if (nextMusic) //(bool nextMusic) is changed to true every time n is pressed
    {
        nextOne++;
        if (nextOne < playlist.size()) // if the iterator (nextOne) is less than the size of the playlist then do
        {
            sound.loadSound(playlist[nextOne]); // use the iterator (nextOne) to pick a song from the Vector
            playing = true;                     // play the visualizer
            sound.play();                       // start the sound
            sound.setLoop(true);                // loop the sound
        }
        else // if the iterator (nextOne) is greater than the size of the playlist then do
        {
            nextOne = -1; // set iterator back to 0
        }
        nextMusic = false; // always set the bool to false so that we are not changing songs wildly
    }
    for (int side = 0; side < 6; side++)
    {
        newBox.setSideColor(side, ofColor::fromHsb(137, 15, 13));
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofColor colorOne(255, 187, 187);
    ofColor colorTwo(255, 228, 192);
    ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_LINEAR);

    ofSetColor(0, 0, 0);
    string currentMusic = playlist[nextOne];
    myFont2.drawString(currentMusic, 0, 75); // will draw current music

    if (recording) // will draw REC when user presses r and recording
    {
        if (secondsPassed % 2) // every 2 seconds
        {
            ofSetColor(155, 0, 0); // red
            myFont2.drawString("REC", 0, 125);
        }
    }

    if (!playing)
    {
        ofSetColor(0, 0, 0);
        myFont2.drawString(pressP, ofGetWidth() / 2 - myFont2.stringWidth(pressP) / 2, ofGetHeight() / 2 - myFont2.stringHeight(pressP) / 2);
        ofSetColor(randomInt1, randomInt2, randomInt3);
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
    else if (mode == '4')
    {
        drawMode4(amplitudes);
    }

    if (helpButtons) // rectangle that contains info such as FPS, buttons etc
    {
        ofSetColor(0, 0, 0);
        ofFill();
        ofDrawRectRounded(250, 220, 500, 300, 50);
        ofSetColor(255, 255, 255);
        myFont1.drawString("NRK: " + to_string(keystrokes.size()), 300, 340);
        myFont1.drawString("FPS: " + to_string(ofGetFrameNum() % 60), 300, 300);
        myFont1.drawString("Volume down: '-'", 300, 380);
        myFont1.drawString("Volume up: '='", 300, 420);
        myFont1.drawString("Volume: " + to_string(currentVol), 500, 300);
        myFont1.drawString("X: " + to_string(ofGetMouseX()) + ", Y: " + to_string(ofGetMouseY()), 300, 460);
        myFont2.drawString("Help", 450, 265);
        ofSetColor(randomInt1, randomInt2, randomInt3);
    }
}
void ofApp::drawMode1(vector<float> amplitudes)
{
    ofFill();
    ofSetColor(0, 0, 0);
    myFont1.drawString("Rectangle Height Visualizer", 0, 25);

    ofSetColor(randomInt1, randomInt2, randomInt3);
    for (int i = 0; i < ofGetWidth(); i += ofGetWidth() / 64)
    {
        ofDrawRectangle(i, ofGetHeight(), 32, amplitudes[iter]);
        iter++;
        if (iter == 64)
        {
            iter = 0;
        }
    }
}
void ofApp::drawMode2(vector<float> amplitudes)
{
    ofSetColor(0, 0, 0);
    ofSetLineWidth(5); // Sets the line width
    ofNoFill();        // Only the outline of shapes will be drawn
    myFont1.drawString("Circle Radius Visualizer", 0, 25);

    int bands = amplitudes.size();
    for (int j = 0; j < bands; j++)
    {
        int i;
        i = ofRandom(0, 3);
        ofSetColor((bands - i) * 32 % 256, randomInt1, randomInt2);
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[0] / (i + 1));
    }
}

void ofApp::drawMode3(vector<float> amplitudes)
{
    ofFill();
    ofSetColor(0, 0, 0);
    myFont1.drawString("Rectangle Width Visualizer", 0, 25);

    ofSetColor(randomInt1, randomInt2, randomInt3);
    for (int i = 0; i < ofGetHeight(); i += ofGetHeight() / 64)
    {
        ofDrawRectangle(ofGetWidth(), i, amplitudes[iter2], 32);
        iter2++;
        if (iter2 == 64)
        {
            iter2 = 0;
        }
    }
}

void ofApp::drawMode4(vector<float> amplitudes)
{
    ofEnableDepthTest();
    ofSetBackgroundColor(0, 0, 0);
    newBox.setPosition(0, 0, 0);
    newBox.set(100, abs(2 * amplitudes[0] / 4) + 50, 100);
    light.setPosition(0, 100, -30);
    light.enable();

    if (booleanTimer(3))
    {
        for (int side = 0; side < 6; side++)
        {
            newBox.setSideColor(side, ofColor::fromHsb(ofRandom(255), 255, 255));
        }
    }

    cam.begin();
    newBox.draw();
    cam.end();
    light.disable();
    ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

    if (replay && key != 'c')
    {
        keyVal = keystrokes[k];
    }

    else
    {
        keyVal = key;
    }

    if (recording && key != 'r')
    {
        this->keystrokes.push_back(key);
    }

    switch (key)
    {
    case 'c': // cancel recording
        if (replay)
        {
            cancel = !cancel;
            replay = false;
            keystrokes.clear();
        }
        break;
    }
    switch (keyVal)
    {
    case 'p': // Play the visualizer
        if (playing)
        {
            playing = !playing;
            sound.stop();
        }
        else
        {
            playing = !playing;
            sound.play();
        }
        break;
    case 't': // replay the recording //FIXME:
        if (not cancel && not recording && keystrokes.size() > k)
        {
            replay = true;
        }
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
    case '4':
        mode = '4';
    case '-': // lower volume
        if (currentVol > -0.1)
        {
            currentVol -= 0.1;
        }
        break;
    case '=': // volume up
        if (currentVol < 0.9)
        {
            currentVol += 0.1;
        }
        break;
    case 'r': // record //FIXME:
        recording = !recording;
        break;
    case 'h': // draw help
        if (helpButtons)
        {
            helpButtons = false;
        }
        else
        {
            helpButtons = true;
        }
        break;

    case 'n': // toggle nextMusic
        nextMusic = true;
        break;
    case 'a': // toggle Amplitudes stop
        ampStop = !ampStop;
        break;
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

void ofApp::timer() // counts time passed
{
    if (ofGetFrameNum() % 60 == 0)
    {
        secondsPassed++;
    }
}

bool ofApp::booleanTimer(int intervalToReturnBool) // becomes true every n seconds for one frame
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
