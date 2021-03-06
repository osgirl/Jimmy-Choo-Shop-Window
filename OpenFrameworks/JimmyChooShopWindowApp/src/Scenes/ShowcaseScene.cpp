/*
 *  ShowcaseScene.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 28/07/17.
 *
 */


#include "ShowcaseScene.h"
#include "AppManager.h"

ShowcaseScene::ShowcaseScene(): ofxScene("SHOWCASE"), m_updateColors(false)
{
}

void ShowcaseScene::setup() {
    //ofLogNotice("ShowcaseScene::setup");
}

void ShowcaseScene::update() {
    
    if(m_updateColors){
        this->updateColors();
    }
    
}

void ShowcaseScene::draw() {
    auto animationColor = AppManager::getInstance().getLayoutManager().getAnimationColor();
    ofBackground(animationColor);
}

void ShowcaseScene::willFadeIn() {
    ofLogNotice("ShowcaseScene::willFadeIn");
   
    this->setupDmx();
    
    AppManager::getInstance().getLayoutManager().setTitle(getName());
    
    AppManager::getInstance().getSerialManager().onSetSolid();
    ofColor color = ofColor(255,0,255);
    AppManager::getInstance().getLayoutManager().setAnimationColor(color);
}

void ShowcaseScene::willDraw() {
    ofLogNotice("ShowcaseScene::willDraw");
}

void ShowcaseScene::willFadeOut() {
    ofLogNotice("ShowcaseScene::willFadeOut");
    m_updateColors = false;
}

void ShowcaseScene::willExit() {
    ofLogNotice("ShowcaseScene::willExit");
}

void ShowcaseScene::setupDmx() {
    m_updateColors = true;
    AppManager::getInstance().getDmxManager().onSetDmxLightSolid();
    int value = 255;
    AppManager::getInstance().getDmxManager().onSetDmxLightWhite(value);
    int motorSpeed = 20;
    //AppManager::getInstance().getDmxManager().onSetDmxMotorSpeed(motorSpeed);
    AppManager::getInstance().getGuiManager().onSetMotorSpeed(motorSpeed);
    
}

void ShowcaseScene::updateColors()
{
    auto animationColor = AppManager::getInstance().getLayoutManager().getAnimationColor();
   // int brightness = animationColor.getBrightness();
    
    //ofLogNotice() << "ShowcaseScene::updateColors: brightness -> " <<brightness;
    
    //AppManager::getInstance().getDmxManager().onSetDmxLightColor(animationColor);
    //AppManager::getInstance().getDmxManager().onSetDmxLightWhite(brightness);
    AppManager::getInstance().getSerialManager().onSetColor(animationColor);
   
}
