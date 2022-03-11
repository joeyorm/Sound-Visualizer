# PA1: Openframeworks Audiovisualizer
The objective for this first project is to complete this audiovisualizer with the help of OpenFrameworks!

# What it can do out of the box
After compiling and running the project for the first time, you should be able to do a couple of things:

- Using the "P" key, you should be able to play music from "beat.wav" 
- Using different number keys, you can visualize the music in different ways:
    - 1: Rectangle Height Visualizer
    - 2: Circle Radius Visualizer
    - 3: Rectangle Width Visualizer (to be implemented)
    - 4: Custom Visualizer (to be implemented)

# Classes
This project contains two classes that should be of your concern: ofApp and AudioVisualizer.

## ofApp
This is the class that brings most things together. Here, you will find the code that causes the audio to play and pause. It is also to where the visualization happens. Here, you can observe how the code to change between modes works, and how the song is actually played. 

## AudioVisualizer
The AudioVisualizer class provides us with the data needed to do the visualization. Using some of the tools OpenFrameworks provides us and math, we can obtain information such as the amplitude of the sound. 

## Music Keys
- 'n' will move forward towards the next song in the vector playlist which contains strings of all names of the songs.
- 'N' will move backwards throught the list of songs onto the previous one.
- '7' will play the first song.
- '8' will play the second song.
- '9' will play the third song.
- '0' will play the fourth song.
- 'm' will toggle the menu on
- Dragging and dropping .wav files onto the window will add them to the playlist. Scroll to them using 'n'!

## Contributors
- Joey Ortega Mandia - joey.ortega@upr.edu
- Angel Feliciano Portalatin - angel.feliciano21@upr.edu

## Disclaimer
- None of the images inside the app are owned by the authors of this project unless specified otherwise.
- This code can be used as long as no ownership of this code is falsely claimed by someone else. (Plagiarism)
