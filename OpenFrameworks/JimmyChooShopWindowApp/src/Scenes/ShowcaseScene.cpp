/*
 *  ShowcaseScene.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 28/07/17.
 *
 */


#include "ShowcaseScene.h"
#include "AppManager.h"

ShowcaseScene::ShowcaseScene(): ofxScene("SHOWCASE"){}

void ShowcaseScene::setup() {
    ofLogNotice("ShowcaseScene::setup");
    
    m_currentColor = ofColor::white;
    m_currentColor.setSaturation(255);
    m_currentColor.setBrightness(255);
    m_currentColor.setHue(0);
}

void ShowcaseScene::update() {
    
    float dt = ofGetLastFrameTime();
    
    float hue = fmod((m_currentColor.getHue() + dt*10),360);
   // ofLogNotice() << "ShowcaseScene::update -> dt" <<  dt;
    //ofLogNotice() << "ShowcaseScene::update -> hue" <<  hue;
    m_currentColor.setHue(hue);
    
    AppManager::getInstance().getSerialManager().onSetColor(m_currentColor);
    AppManager::getInstance().getDmxManager().onSetDmxLightColor(m_currentColor);
    
}

void ShowcaseScene::draw() {
    ofBackground(m_currentColor);
}

void ShowcaseScene::willFadeIn() {
    ofLogNotice("ShowcaseScene::willFadeIn");
    AppManager::getInstance().getDmxManager().onSetDmxLightColor(ofColor::blue);
    AppManager::getInstance().getDmxManager().onSetDmxLightSolid();
    int motorSpeed = 20;
    AppManager::getInstance().getDmxManager().onSetDmxMotorSpeed(motorSpeed);
    AppManager::getInstance().getLayoutManager().setTitle(getName());
    
    //AppManager::getInstance().getSerialManager().onSetColor(ofColor::blue);
}

void ShowcaseScene::willDraw() {
    ofLogNotice("ShowcaseScene::willDraw");
}

void ShowcaseScene::willFadeOut() {
    ofLogNotice("ShowcaseScene::willFadeOut");
}

void ShowcaseScene::willExit() {
    ofLogNotice("ShowcaseScene::willExit");
}
