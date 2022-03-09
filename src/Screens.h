#pragma once

#include "ofMain.h"
#include "AudioVisualizer.h"
#include <vector>
#include <iostream>
#include "ofEvents.h"
#include "ofAppRunner.h"
#include "ofAppBaseWindow.h"
#include "ofLog.h"
using namespace std;

class Screens
{

private:
	float screenWidth;
	float screenHeight;
	float width;
	float height;
	float xPos;
	float yPos;
	float leftDownCorner;
	float leftUpCorner;
	float rightDownCorner;
	float rightupCorner;
	bool toggler;
	ofTrueTypeFont font1;
	ofTrueTypeFont font2;
	ofTrueTypeFont font3;

public:
	Screens()
	{
		screenWidth = ofGetScreenWidth();
		screenHeight = ofGetScreenHeight();
		width = screenWidth;
		height = screenHeight;
		xPos = 0;
		yPos = 0;
		toggler = false;

		font1.load("texreg.ttf", 15);
		font2.load("textbold.ttf", 30);
		font3.load("textbold.ttf", 15);
	}

	// setters
	void setScreenStartPos(float x, float y)
	{
		this->xPos = x;
		this->yPos = y;
	}
	void setScreenWidth(float width) { screenWidth = this->width; }
	void setScreenHeight(float height) { screenHeight = this->height; }
	void toggle() { toggler = !toggler; }

	// Getters
	float getScreenWidth() { return this->screenWidth; }
	float getScreenHeight() { return this->screenHeight; }
	float getScreenStartPosX() { return this->xPos; }
	float getScreenStartPosY() { return this->yPos; }

	// functions
	void screenDisplay() // makes the screen appear on the screen if toggler is true (innitially set to false) to activate use .toggle()
	{
		if (this->toggler)
		{
			ofFill();
			ofDrawRectangle(getScreenStartPosX(), getScreenStartPosY(), getScreenWidth(), getScreenHeight());
		}
	}
	void screenTextfont1(string text, int xPos, int yPos) // creates a draw text
	{
		if (this->toggler)
		{
			font1.drawString(text, xPos, yPos);
		}
	}
	void background(float r, float g, float b) // sets background of screen without opacity
	{
		if (this->toggler)
		{
			ofSetColor(ofColor::fromHsb(r, g, b));
		}
	}
	void background(float r, float g, float b, float z) // sets background of the screen but with opacity
	{
		if (this->toggler)
		{
			ofEnableAlphaBlending();
			ofSetColor(ofColor::fromHsb(r, g, b, z));
		}
	}
};

class Button
{
private:
	int xPosB;
	int yPosB;
	int width;
	int height;
	bool pressedButton;
	bool toggler;
	int r;
	int b;
	int g;

public:
	Button()
	{
		xPosB = ofGetWidth() / 2;
		yPosB = ofGetHeight() / 2;
		width = 300;
		height = 150;
		pressedButton = false;
		toggler = false;
		r = 3;
		b = 3;
		g = 3;
	}

	// setters
	void setPosition(int x, int y, int width, int height) // sets the position of the button on the screen
	{
		this->xPosB = x;
		this->yPosB = y;
		this->width = width;
		this->height = height;
	}
	void setPosition(int x, int y) // a predetermined button that needs just position, great for quick implementation
	{
		this->xPosB = x;
		this->yPosB = y;
		this->width = width;
		this->height = height;
	}

	void toggle() { toggler = !toggler; } // toggle true or false (set to false initially so calling it will change to true the first time around)

	void setButtonColor(int r, int g, int b, int a) // sets background color of button
	{
		if (this->toggler)
		{
			ofSetColor(ofColor::fromHsb(this->r, this->g, this->b));
		}
	}

	void setButtonSizeLarge()
	{
		this->width = 300;
		this->height = 300;
	}

	// getters
	int getXpos() { return this->xPosB; }
	int getYpos() { return this->yPosB; }
	int getWidth() { return this->width; }
	int getHeight() { return this->height; }
	bool getPressedEvent() { return this->pressedButton; }

	// functions
	void buttonDisplay()
	{
		if (toggler)
		{
			ofDrawRectangle(this->xPosB, this->yPosB, this->width, this->height);
		}
	}

	bool buttonPress(int button) //FIXME: //the idea is to make this class detect mouse buttons when pressed.
	{
		if (toggler && ofGetMouseX() > this->xPosB && ofGetMouseY() > this->yPosB && ofGetMouseX() < this->width && ofGetMouseY() < this->height && button == '0')
		{
			pressedButton = true;
			return pressedButton;
		}
		else{ 
			pressedButton = false;
			return pressedButton;
		}
	}
	void buttonToggle() { pressedButton = !pressedButton; }
};