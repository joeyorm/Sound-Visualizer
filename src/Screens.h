#pragma once

#include "ofMain.h"
#include "AudioVisualizer.h"
#include <vector>
#include <iostream>
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

public:
	Screens()
	{
		screenWidth = ofGetWidth();
		screenHeight = ofGetHeight();
		width = screenWidth;
		height = screenHeight;
		xPos = 0;
		yPos = 0;
		toggler = false;
	}

	// setters
	void setScreenStartPos(float x, float y)
	{
		xPos = x;
		yPos = y;
	}
	void setScreenWidth(float width) { screenWidth = this->width; }
	void setScreenHeight(float height) { screenHeight = this->height; }
	void setScreenBackGround(float r, float g, float b) { ofSetBackgroundColor(ofColor::fromHsb(r, g, b)); }
	void enable() { toggler = true; }
	void disable() { toggler = false; }

	// Getters
	float getScreenWidth() { return screenWidth; }
	float getScreenHeight() { return screenHeight; }
	float getScreenStartPosX() { return xPos; }
	float getScreenStartPosY() { return yPos; }

	void screenDisplay()
	{
		if (this->toggler)
		{
			ofDrawRectangle(getScreenStartPosX(), getScreenStartPosY(), getScreenWidth(), getScreenHeight());
		}
	}
};