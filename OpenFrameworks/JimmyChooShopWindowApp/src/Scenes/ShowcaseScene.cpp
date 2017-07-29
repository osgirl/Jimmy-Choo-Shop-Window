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
}

void ShowcaseScene::update() {
    this->updateColors();
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

void ShowcaseScene::setupDmx() {
    AppManager::getInstance().getDmxManager().onSetDmxLightSolid();
    int motorSpeed = 20;
    AppManager::getInstance().getDmxManager().onSetDmxMotorSpeed(motorSpeed);
    
}

void ShowcaseScene::updateColors()
{
    auto animationColor = AppManager::getInstance().getLayoutManager().getAnimationColor();
    
    AppManager::getInstance().getDmxManager().onSetDmxLightColor(animationColor);
    AppManager::getInstance().getSerialManager().onSetColor(animationColor);
   
}
