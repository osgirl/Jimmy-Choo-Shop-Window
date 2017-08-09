/*
 *  DiscoScene.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 28/07/17.
 *
 */


#include "DiscoScene.h"
#include "AppManager.h"



DiscoScene::DiscoScene(): ofxScene("DISCO"), m_updateColors(false)
{
}

void DiscoScene::setup() {
    ofLogNotice("DiscoScene::setup");
    this->setupText();
}

void DiscoScene::setupText()
{
    int margin =  LayoutManager::MARGIN;
    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    ofPoint pos = ofPoint(width/2, height/2);
    float w = width - 2*margin;
    float h = height - 2*margin;
    string text = " ";
    //string fontName = "fonts/Arial Unicode.ttf";
    string fontName = "fonts/OpenSansEmoji.ttf";
    float size = 20;
    
    
    m_textVisual.setWidth(w); m_textVisual.setHeight(h);
    m_textVisual.setPosition(pos); m_textVisual.setCentred(true);
    m_textVisual.setLineHeight(1.5);
    m_textVisual.setText(text, fontName, size, ofColor::white);
    
}

void DiscoScene::update()
{
    if(m_updateColors){
        this->updateColors();
    }
    
    this->updateText();
  
}

void DiscoScene::draw() {
    ofBackground(0,0,0);
    m_textVisual.draw();
}

void DiscoScene::willFadeIn() {
     ofLogNotice("DiscoScene::willFadeIn");
     AppManager::getInstance().getAudioManager().playSample("NightFever");
     this->setupDmx();
     this->updateText();
     this->setupColor();
     AppManager::getInstance().getLayoutManager().setTitle(getName());
     AppManager::getInstance().getSerialManager().onSetDisco();
    
}

void DiscoScene::updateText()
{
    auto text = AppManager::getInstance().getInstagramManager().getCurrentString();
    m_textVisual.setText(text);
}


void DiscoScene::willDraw() {
    ofLogNotice("DiscoScene::willDraw");
    AppManager::getInstance().getSerialManager().onSetDisco();
}

void DiscoScene::willFadeOut() {
    ofLogNotice("DiscoScene::willFadeOut");
    AppManager::getInstance().getAudioManager().stopSample();
    m_updateColors = false;
}

void DiscoScene::willExit() {
    ofLogNotice("DiscoScene::willExit");
   
}


void DiscoScene::setupDmx()
{
    m_updateColors = true;
    AppManager::getInstance().getDmxManager().onSetDmxLightStrobe();
    //AppManager::getInstance().getDmxManager().onSetDmxLightSolid();
    int motorSpeed = 127;
    //AppManager::getInstance().getDmxManager().onSetDmxMotorSpeed(motorSpeed);
    AppManager::getInstance().getGuiManager().onSetMotorSpeed(motorSpeed);
}

void DiscoScene::updateColors()
{
    auto animationColor = AppManager::getInstance().getLayoutManager().getAnimationColor();
    
    AppManager::getInstance().getSerialManager().onSetColor(animationColor);
    
//    float strobeProb = sin(ofGetElapsedTimef()*50);
//    if(strobeProb<0){
//        animationColor = ofColor::black;
//    }
//    
//    AppManager::getInstance().getDmxManager().onSetDmxLightColor(animationColor);
    
}

void DiscoScene::setupColor()
{
    ofColor color = ofColor(255,0,255);
    int strobeColor = 182;
    if(ofRandom(1)<0.5){
        color = ofColor(0,0,255);
        strobeColor = 162;
    }
    AppManager::getInstance().getLayoutManager().setAnimationColor(color);
    
    AppManager::getInstance().getDmxManager().onSetDmxLightStrobe();
    AppManager::getInstance().getDmxManager().onSetDmxStrobeColor(strobeColor);
    AppManager::getInstance().getDmxManager().onSetDmxLightStrobe();
    
}


