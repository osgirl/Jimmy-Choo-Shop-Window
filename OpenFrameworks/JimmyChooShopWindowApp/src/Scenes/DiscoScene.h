/*
 *  DiscoScene.h
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 28/07/17.
 *
 */

#pragma once


#include "ofxScene.h"
#include "ofxSimpleTimer.h"
#include "TextVisual.h"


class DiscoScene : public ofxScene {

    static const int TIMER_DURATION_MS;
    
public:

    //! Constructor
    DiscoScene();
    
    //! Set up the scene
    void setup();

    //! Update the scene
    void update();

    //! Draw the scene
    void draw();
    
    //! Called when fading in
    void willFadeIn();

    //! Called when to start drawing
    void willDraw();

    //! Called fading out
    void willFadeOut();

    //! Called when exit
    void willExit();
    
    void timerCompleteHandler( int &args ) ;
    
private:
    
    void setupTimer();
    
    void setupText();
    
    void updateText();
    
private:
    
    ofxSimpleTimer     m_timer;
    TextVisual         m_textVisual;

};

