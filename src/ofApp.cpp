#include "ofApp.h"
#include <vector>
#include <iostream>
using namespace std;

//--------------------------------------------------------------
void ofApp::setup()
{
    sound.loadSound(playlist[0]); // Loads a sound file (in bin/data/)
    sound.setLoop(true);          // Makes the song loop indefinitely

    currentVol = 0.5;                  // The current volume
    sound.setVolume(currentVol * 100); // Sets the song volume

    ofSetBackgroundColor(256, 256, 256);
    myFont1.load("texreg.ttf", 15);    // Loads the text fonts
    myFont2.load("textbold.ttf", 30);  // Loads the text fonts
    myFont3.load("textbold.ttf", 15);  // Loads the text fonts
    myFont4.load("textbold.ttf", 100); // Loads the text fonts

    imageBg.load("KeepitSimple.png");    // Loads the images
    pauseButton.load("pauseButton.png"); // Loads the images
    playButton.load("playButtton.png");  // Loads the images
}

//--------------------------------------------------------------
void ofApp::update()
{
    ofSoundUpdate();             // Updates all sound players
    sound.setVolume(currentVol); // updates the volume

    if (time > 0 && startFinish)
    {
        time -= 1;
    }

    if (not ampStop) // stops the visualizer if a is pressed causing the bool to be false,
    {
        visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    }

    if (booleanTimer(4)) // wait for 4 seconds and then go ahead and update the variable time, so that it can start fading
    {
        startFinish = true;
    }

    if (booleanTimer(4))
    {
        randomInt1 = ofRandom(0, 255);
        randomInt2 = ofRandom(0, 255);
        randomInt3 = ofRandom(0, 255);
    }

    if (booleanTimer(2) && replay && not cancel) // Allows replay
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

    // MUSIC CHANGER FORWARD
    if (nPressed)
    {
        nextOne++;
        if (nextOne < playlist.size() - 1)
        {
            sound.loadSound(playlist[nextOne]);
            playing = true;
            sound.play();
            sound.setLoop(true);
        }
        else
        {
            nextOne = 0;
            sound.loadSound(playlist[nextOne]);
            playing = true;
            sound.play();
            sound.setLoop(true);
        }

        nPressed = false;
    }

    // MUSIC CHANGER BACKWARDS
    if (NPressed)
    {
        nextOne--;
        if (nextOne >= 0)
        {
            sound.loadSound(playlist[nextOne]);
            playing = true;
            sound.play();
            sound.setLoop(true);
        }
        else
        {
            nextOne = playlist.size() - 1;
            sound.loadSound(playlist[nextOne]);
            playing = true;
            sound.play();
            sound.setLoop(true);
        }

        NPressed = false;
    }


    // BACKGROUND CHANGER FORWARD
    if (bPressed)
    {
        nextBackground++;
        if (nextBackground < backgroundImages.size() - 1)
        {
            imageBg.load(backgroundImages[nextBackground]);
        }
        else
        {
            nextBackground = 0;
            imageBg.load(backgroundImages[nextBackground]);
        }
        bPressed = false;
    }

    // BACKGROUND CHANGER BACKWARDS
    if (BPressed)
    {
        nextBackground--;
        if (nextBackground >= 0)
        {
            imageBg.load(backgroundImages[nextBackground]);
        }
        else
        {
            nextBackground = backgroundImages.size() - 1;
            imageBg.load(backgroundImages[nextBackground]);
        }
        BPressed = false;
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{

    ofSetColor(247, 247, 247);
    imageBg.draw(ofGetWidth() / 2 - imageBg.getWidth() / 2, ofGetHeight() / 2 - imageBg.getHeight() / 2);
    imageBg.resize(ofGetWidth(), ofGetHeight());

    if (!playing)
    {
        ofEnableAlphaBlending();
        ofSetColor(247, 247, 247);
        pauseButton.draw(ofGetWidth() / 2 - floor(pauseButton.getWidth() / 2), ofGetHeight() / 2 - floor(pauseButton.getHeight() / 2));
        pauseButton.resize(100, 100);
        // myFont2.drawString(pressP, ofGetWidth() / 2 - myFont2.stringWidth(pressP) / 2, ofGetHeight() / 2 - myFont2.stringHeight(pressP) / 2);
        ofDisableAlphaBlending();
    }

    // if (playing)
    // {

    //     ofEnableAlphaBlending();
    //     ofSetColor(247, 247, 247);
    //     playButton.draw(ofGetWidth() / 2 - floor(playButton.getWidth() / 2), ofGetHeight() / 2 - floor(playButton.getHeight() / 2));
    //     playButton.resize(100, 100);
    //     ofDisableAlphaBlending();
    // }

    ofSetColor(0, 0, 0);                                                          // FIXME:
    string currentMusic = playlist[nextOne];                                      // draw m
    myFont3.drawString(currentMusic.erase(currentMusic.length() - 4, -4), 0, 75); // will draw current music

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
        myFont1.drawString("Volume: " + to_string(currentVol).erase(to_string(currentVol).length() - 5, -5), 500, 300);
        myFont1.drawString("X: " + to_string(ofGetMouseX()) + ", Y: " + to_string(ofGetMouseY()), 300, 460);
        myFont2.drawString("HELP", ofGetWidth() / 2 - myFont2.stringWidth("HELP"), 265);
        ofSetColor(randomInt1, randomInt2, randomInt3);
    }

    if (recording) // will draw REC when user presses r and recording
    {
        if (secPass % 2 == 0) // every 2 seconds , modulo 1 is equal to no blinking, modulo 2 blinks
        {
            ofEnableAlphaBlending();
            ofSetColor(255, 255, 255);
            ImgRecording.draw(floor(10), floor(125));
            ImgRecording.resize(100, 100);
            myFont3.drawString("REC", 0, 125);
            ofDisableAlphaBlending();
        }
    }

    menu.background(0, 0, 0, 200);
    menu.screenDisplay(); // FIXME: //Animation?? y = ofNoise(ofGetElapsedTime())
    

    ofEnableAlphaBlending();
    welcomeScreen.toggle();
    welcomeScreen.background(0, 0, 0, time);
    welcomeScreen.screenDisplay();

    ofSetColor(248, 248, 248, time);
    myFont4.drawString("WELCOME", ofGetWidth() / 2 - myFont4.stringWidth("WELCOME") / 2, ofGetHeight() / 2 - myFont4.stringHeight("WELCOME") / 2);
    welcomeScreen.toggle();

    menu.screenDisplay();
    ofDisableAlphaBlending();
}
void ofApp::drawMode1(vector<float> amplitudes)
{
    ofFill();
    ofSetColor(0, 0, 0);
    myFont3.drawString("Rectangle Height Visualizer", 0, 25);

    for (int i = 0; i < ofGetWidth(); i += ofGetWidth() / 64)
    {
        int multiplier;
        // if (32 < iter){ //this here allows us to choose the range we want to multiply
        //     multiplier = amplitudes[iter] * 300 * visualizerMultiplier; // this here multiplies the visualizer
        // }
        // else{
        //     multiplier = amplitudes[iter];
        // }
        multiplier = amplitudes[iter];
        ofSetColor(randomInt1, randomInt2, randomInt3);
        ofDrawRectangle(i, ofGetHeight(), 32, multiplier);

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
    ofSetLineWidth(10); // Sets the line width
    ofNoFill();         // Only the outline of shapes will be drawn
    myFont3.drawString("Circle Radius Visualizer", 0, 25);

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
    myFont3.drawString("Rectangle Width Visualizer", 0, 25);

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
    // ofSetBackgroundColor(0, 0, 0);
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
        if (currentVol > 0.1)
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

    
    case 'n': // toggle next Music songs
        nPressed = true;
        break;
    case 'N':
        NPressed = true;
        break;

    case 'a': // toggle Amplitudes stop
        ampStop = !ampStop;
        break;
    case 'm': // toggle menu on or off
        menu.toggle();
        break;

    case 'b':
        bPressed = true;
        break;
    case 'B':
        BPressed = true;
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
