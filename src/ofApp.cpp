#include "ofApp.h"
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowTitle("Sound Visualizer");
    sound.loadSound(playlist[0]); // Loads a sound file (in bin/data/)
    sound.setLoop(true);          // Makes the song loop indefinitely

    currentVol = 0.5;                  // The current volume
    sound.setVolume(currentVol * 100); // Sets the song volume

    ofSetBackgroundColor(256, 256, 256);
    myFont1.load("texreg.ttf", 15);    // Loads the text fonts
    myFont2.load("textbold.ttf", 30);  // Loads the text fonts
    myFont3.load("textbold.ttf", 15);  // Loads the text fonts
    myFont4.load("textbold.ttf", 100); // Loads the text fonts
    myFont5.load("textbold.ttf", 22);

    imageBg.load("ultraviolet.jpg");    // Loads the images
    pauseButton.load("pauseButton.png"); // Loads the images
    playButton.load("playButtton.png");  // Loads the images
    ImgRecording.load("rec.png");
    ImgReplay.load("replay.png");
}

//--------------------------------------------------------------
void ofApp::update()
{

    ofSoundUpdate();             // Updates all sound players
    sound.setVolume(currentVol); // updates the volume

    if (time > 0 && startFinish) // allows the fade Animation of Welcome
    {
        time -= 1;
    }
    if (fade)
    {
        fader -= 1;
    }

    if (not ampStop) // stops the visualizer
    {
        visualizer.updateAmplitudes();
    }

    if (ofGetFrameNum() % (60) == 0) // A timer that makes the variable go back to
    {
        this->secPass++;
        if (secPass % 60 == 0)
        {
            secPass = 0;
        }
    }

    if (booleanTimer(4)) // wait for 4 seconds and then go ahead and update the variable time, so that it can start fading
    {
        startFinish = true;
    }

    if (booleanTimer(4) && not pause)
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
        if (nextOne < playlist.size())
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
        if (nextBackground < backgroundImages.size())
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

    if (wrongPress)
    {
        fade = true;
        ofSetColor(175, 0, 0, fader);
        string donotpress = "Can't press this button right now";
        myFont2.drawString(donotpress, ofGetWidth() / 2 - myFont2.stringWidth(donotpress) / 2, ofGetHeight() / 4 - myFont2.stringHeight(donotpress) / 4);
        if (booleanTimer(2))
        {
            wrongPress = false;
            fade = false;
            fader = 255;
        }
    }

    if (!playing)
    {
        ofEnableAlphaBlending();
        ofSetColor(247, 247, 247);
        pauseButton.draw(ofGetWidth() / 2 - floor(pauseButton.getWidth() / 2), ofGetHeight() / 2 - floor(pauseButton.getHeight() / 2));
        pauseButton.resize(100, 100);
        ofDisableAlphaBlending();
    }

    ofSetColor(0, 0, 0);
    string currentMusic = playlist[nextOne];

    currentMusic = currentMusic.erase(currentMusic.rfind("."), currentMusic.length() - currentMusic.rfind("."));
    currentMusic = remSpecificChar(currentMusic, '_', " ");
    ofSetColor(248,248,248);
    myFont5.drawString(currentMusic, n, 75 + l); // will draw current music

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

    if (recording) // will draw REC when user presses r and recording
    {
        if (secPass % 2 == 0) // every 2 seconds , modulo 1 is equal to no blinking, modulo 2 blinks
        {
            ofEnableAlphaBlending();
            ofSetColor(255, 255, 255);
            ImgRecording.resize(75, 75);
            ImgRecording.draw(floor(ofGetWidth() - ImgRecording.getWidth() - 10), floor(20));
            ofDisableAlphaBlending();
        }
    }
    
    if (replay){ // will draw simple image when replay is enabled
        
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 255);
        ImgReplay.resize(75, 75);
        ImgReplay.draw(floor(ofGetWidth() - ImgRecording.getWidth() - 10), floor(20));
        ofDisableAlphaBlending();
    

    }

    // Menu Screen (Just a bunch of text)
    ofSetColor(0, 0, 0, 200);
    menu.screenDisplay();
    ofSetColor(255, 255, 255);
    menu.screenTextTittle("MENU", ofGetWidth(), ofGetHeight(), 2, 5);
    // BUTTONS
    menu.screenTextTittle1("BUTTONS", ofGetWidth(), ofGetHeight() / 3, 4, 1); // FIXME:
    menu.screenTextReg("Volume Increment: =", ofGetWidth() / 4, 270);
    menu.screenTextReg("Volume Decrement: -", ofGetWidth() / 4, 300); // FIXME:
    menu.screenTextReg("Background Forward: b", ofGetWidth() / 4, 330);
    menu.screenTextReg("Background Previous: B", ofGetWidth() / 4, 360);
    menu.screenTextReg("Next Song: n", ofGetWidth() / 4, 390);
    menu.screenTextReg("Previous Song: N", ofGetWidth() / 4, 420);
    menu.screenTextReg("Visualizer Increment: +", ofGetWidth() / 4, 450);
    menu.screenTextReg("Visualizer Decrement: _", ofGetWidth() / 4, 480);
    menu.screenTextReg("Menu Toggle: m", ofGetWidth() / 4, 510);
    menu.screenTextReg("Replay Recorded Keys: t", ofGetWidth() / 4, 540);
    menu.screenTextReg("Record Keys: r", ofGetWidth() / 4, 570);
    menu.screenTextReg("Cancel Replay: c", ofGetWidth() / 4, 600);
    menu.screenTextReg("Pause Song / Unpause Song : p", ofGetWidth() / 4, 630);
    menu.screenTextReg("Pause Visualizer: a", ofGetWidth() / 4, 660);
    // SPECS
    menu.screenTextTittle1("SPECS", ofGetWidth() - ofGetWidth() / 4, ofGetHeight() / 3, 1, 1);
    menu.screenTextReg("Volume: " + to_string(currentVol).erase(to_string(currentVol).length() - 5, -5), ofGetWidth() - ofGetWidth() / 3, 270);
    menu.screenTextReg("Recording: " + to_string(recording), ofGetWidth() - ofGetWidth() / 3, 300);
    menu.screenTextReg("Recorded Keys: " + to_string(keystrokes.size()), ofGetWidth() - ofGetWidth() / 3, 330);
    menu.screenTextReg("Replay: " + to_string(replay), ofGetWidth() - ofGetWidth() / 3, 360);
    menu.screenTextReg("Paused: " + to_string(playing), ofGetWidth() - ofGetWidth() / 3, 390);
    menu.screenTextReg("Frames Per Second: " + to_string(ofGetFrameNum() % 60), ofGetWidth() - ofGetWidth() / 3, 420);
    menu.screenTextReg("X: " + to_string(ofGetMouseX()) + ", Y: " + to_string(ofGetMouseY()), ofGetWidth() - ofGetWidth() / 3, 450);
    menu.screenTextReg("Multiplier: "+ to_string(visualMultiplier), ofGetWidth() - ofGetWidth() / 3, 480);

    // welcomeScreen
    welcomeScreen.toggle();
    welcomeScreen.background(0, 0, 0, time);
    welcomeScreen.screenDisplay();
    ofSetColor(255, 255, 255, time);
    welcomeScreen.screenTextTittle("WELCOME", ofGetWidth(), ofGetHeight(), 2, 2);
    welcomeScreen.screenTextTittle1("Press 'm' For More Info On Keys", ofGetWidth(), ofGetHeight() - ofGetHeight() / 4, 2, 1);
    welcomeScreen.toggle();
}
void ofApp::drawMode1(vector<float> amplitudes)
{
    ofFill();
    ofSetColor(248, 248, 248);
    myFont5.drawString("Rectangle Height Visualizer", n, 25 + l);

    for (int i = 0; i < ofGetWidth(); i += ofGetWidth() / 64)
    {
        ofSetColor(randomInt1, randomInt2, randomInt3);
        ofDrawRectangle(i, ofGetHeight(), 32, amplitudes[iter] * visualMultiplier);

        iter++;
        if (iter == 64)
        {
            iter = 0;
        }
    }
}
void ofApp::drawMode2(vector<float> amplitudes)
{
    ofSetColor(248, 248, 248);
    ofSetLineWidth(10);
    ofNoFill();
    myFont5.drawString("Circle Radius Visualizer", n, 25 + l);
    int bands = amplitudes.size();
    for (int j = 0; j < bands; j++)
    {
        int i;
        i = ofRandom(0, 3);
        ofSetColor((bands - i) * 32 % 256, randomInt1, randomInt2);
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, (amplitudes[0] * visualMultiplier) / (i + 1));
    }
}

void ofApp::drawMode3(vector<float> amplitudes)
{
    ofFill();
    ofSetColor(248, 248, 248);
    myFont5.drawString("Rectangle Width Visualizer", n, 25 + l);
    ofSetColor(randomInt1, randomInt2, randomInt3);
    for (int i = 0; i < ofGetHeight(); i += ofGetHeight() / 64)
    {
        ofDrawRectangle(ofGetWidth(), i, amplitudes[iter2] * visualMultiplier, 32);
        iter2++;
        if (iter2 == 64)
        {
            iter2 = 0;
        }
    }
}

void ofApp::drawMode4(vector<float> amplitudes) // cube
{
    myFont5.drawString("Cube Visualizer", n, 25 + l);
    ofEnableDepthTest();
    newBox.setPosition(0, 0, 0);
    newBox.set(abs(amplitudes[0] * visualMultiplier), abs(amplitudes[0] * visualMultiplier), abs(amplitudes[0] * visualMultiplier));
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

    if (recording && key != 'r' && key != 't')
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
        else
        {
            wrongPress = !wrongPress;
        }
        break;
    }
    switch (keyVal)
    {
    case 'p': // Play the visualizer//FIXME:
        if (playing)
        {

            playing = false;
            pause = true; // Play
            ampStop = false;
        }
        else
        {
            pause = false;
            ampStop = false;
            playing = true;
            
        }
        sound.setPaused(pause);
        break;
    case 't': // replay the recording
        if (not cancel && not recording && keystrokes.size() > k)
        {
            replay = true;
        }
        else
        {
            wrongPress = !wrongPress;
        }
        break;
    case '-': // lower volume
        if (currentVol > 0.1)
        {
            currentVol -= 0.1;
        }
        else
        {
            wrongPress = !wrongPress;
        }
        break;
    case '=': // volume up
        if (currentVol < 0.9)
        {
            currentVol += 0.1;
        }
        else
        {
            wrongPress = !wrongPress;
        }
        break;
    case '+': // vizualizer increment
        if (visualMultiplier < 100)
        {
            visualMultiplier += 1;
        }
        else
        {
            wrongPress = !wrongPress;
        }
        break;
    case '_': // visualizer decrement
        if (visualMultiplier > 0)
        {
            visualMultiplier -= 1;
        }
        else
        {
            wrongPress = !wrongPress;
        }
        break;
    case 'r': // record
        recording = !recording;
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
        break;
    case 'n': // toggle next Music songs
        nPressed = true;
        break;
    case 'N': // toggle previous Music songs
        NPressed = true;
        break;
    case 'a': // toggle Amplitudes stop//FIXME:
        if (playing)
        {
            playing = false;
            pause = true;
            ampStop = true;
        }
        else if (not playing)
        {
            playing = true;
            pause = false;
            ampStop = false;
        }
        sound.setPaused(pause);
  

        break;
    case 'm': // toggle menu on or off
        menu.toggle();
        break;
    case 'b': // toggle nextBackground
        bPressed = true;
        break;
    case 'B': // toggle previous background
        BPressed = true;
        break;
    case '7':
        nPressed = true;
        nextOne = 0 - 1; // my wife
        break;
    case '8':
        nPressed = true;
        nextOne = 1 - 1; // beat
        break;
    case '9':
        nPressed = true;
        nextOne = 2 - 1; // way less
        break;
    case '0':
        nPressed = true;
        nextOne = 3 - 1; // believer
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

    if (dragInfo.files.size() > 0 && !count(playlist.begin(), playlist.end(), dragInfo.files[0]))
    {

        playlist.push_back(dragInfo.files[0]);
        dragInfo.files.clear();
    }
}
