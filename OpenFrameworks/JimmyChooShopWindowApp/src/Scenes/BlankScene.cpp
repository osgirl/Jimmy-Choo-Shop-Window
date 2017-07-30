/*
 *  BlankScene.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 28/07/17.
 *
 */


#include "BlankScene.h"
#include "AppManager.h"

BlankScene::BlankScene(): ofxScene("BLANK"){}

void BlankScene::setup() {
    ofLogNotice("BlankScene::setup");
}

void BlankScene::update() {
    
}

void BlankScene::draw() {
    ofBackground(0,0,0);
    
}

void BlankScene::willFadeIn() {
    ofLogNotice("BlankScene::willFadeIn");
    AppManager::getInstance().getLayoutManager().setTitle(getName());
}

void BlankScene::willDraw() {
    ofLogNotice("BlankScene::willDraw");
	AppManager::getInstance().getDmxManager().onSetDmxLightColor(ofColor::black);
	AppManager::getInstance().getDmxManager().onSetDmxLightSolid();
	AppManager::getInstance().getSerialManager().onSetColor(ofColor::black);
}

void BlankScene::willFadeOut() {
    ofLogNotice("BlankScene::willFadeOut");
}

void BlankScene::willExit() {
    ofLogNotice("BlankScene::willExit");
}
