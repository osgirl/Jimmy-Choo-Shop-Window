/*
 *  DiscoScene.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 28/07/17.
 *
 */


#include "DiscoScene.h"
#include "RectangleVisual.h"

DiscoScene::DiscoScene(): ofxScene("DISCO"){}

void DiscoScene::setup() {
    ofLogNotice("DiscoScene::setup");
}

void DiscoScene::update() {
    
}

void DiscoScene::draw() {
    ofBackground(255,0,0);
    ofColor(255);
    ofDrawRectangle(0, 0, 400, 400);
    
}

void DiscoScene::willFadeIn() {
     ofLogNotice("DiscoScene::willFadeIn");
}

void DiscoScene::willDraw() {
    ofLogNotice("DiscoScene::willDraw");
}

void DiscoScene::willFadeOut() {
    ofLogNotice("DiscoScene::willFadeOut");
}

void DiscoScene::willExit() {
    ofLogNotice("DiscoScene::willExit");
}
