/*
 *  DiscoScene.h
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 28/07/17.
 *
 */

#pragma once


#include "ofxScene.h"
#include "TextVisual.h"


class DiscoScene : public ofxScene {

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
    
private:
    
    void setupText();
    
    void updateText();
    
    void setupDmx();
    
    void updateColors();
    
    void setupColor();
    
      
private:
    
    TextVisual         m_textVisual;
    bool               m_updateColors;

};

