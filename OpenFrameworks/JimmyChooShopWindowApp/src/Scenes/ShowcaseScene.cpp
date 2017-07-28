/*
 *  ShowcaseScene.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 28/07/17.
 *
 */


#include "ShowcaseScene.h"
#include "RectangleVisual.h"

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
