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
    
}

void ShowcaseScene::draw() {
    ofBackground(0,255,0);
    
}

void ShowcaseScene::willFadeIn() {
    ofLogNotice("ShowcaseScene::willFadeIn");
    AppManager::getInstance().getDmxManager().onSetDmxLightColor(ofColor::blue);
    AppManager::getInstance().getDmxManager().onSetDmxLightSolid();
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
