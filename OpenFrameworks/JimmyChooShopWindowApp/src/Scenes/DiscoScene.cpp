/*
 *  DiscoScene.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 28/07/17.
 *
 */


#include "DiscoScene.h"
#include "AppManager.h"


const int DiscoScene::TIMER_DURATION_MS = 36000;

DiscoScene::DiscoScene(): ofxScene("DISCO"){}

void DiscoScene::setup() {
    ofLogNotice("DiscoScene::setup");
    this->setupTimer();
}

void DiscoScene::setupTimer()
{
    m_timer.setup( TIMER_DURATION_MS );
    ofAddListener( m_timer.TIMER_COMPLETE , this, &DiscoScene::timerCompleteHandler ) ;
    
}

void DiscoScene::update()
{
    m_timer.update();
}

void DiscoScene::draw() {
    ofBackground(255,0,0);
}

void DiscoScene::willFadeIn() {
     ofLogNotice("DiscoScene::willFadeIn");
     AppManager::getInstance().getAudioManager().playSample("NightFeverShort");
     AppManager::getInstance().getDmxManager().onSetDmxLightStrobe();
     int motorSpeed = 127;
     AppManager::getInstance().getDmxManager().onSetDmxMotorSpeed(motorSpeed);
     AppManager::getInstance().getSerialManager().onSetColor(ofColor::pink);
     m_timer.start(false);
}

void DiscoScene::willDraw() {
    ofLogNotice("DiscoScene::willDraw");
}

void DiscoScene::willFadeOut() {
    ofLogNotice("DiscoScene::willFadeOut");
    AppManager::getInstance().getAudioManager().stopSample();
}

void DiscoScene::willExit() {
    ofLogNotice("DiscoScene::willExit");
   
}

void DiscoScene::timerCompleteHandler( int &args )
{
    ofLogNotice("DiscoScene::timerCompleteHandler -> Timer completed");
    AppManager::getInstance().getGuiManager().onSceneChange("SHOWCASE");

}

