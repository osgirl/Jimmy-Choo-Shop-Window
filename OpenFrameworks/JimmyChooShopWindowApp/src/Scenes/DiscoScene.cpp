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

DiscoScene::DiscoScene(): ofxScene("DISCO"), m_updateColors(false)
{
}

void DiscoScene::setup() {
    ofLogNotice("DiscoScene::setup");
    this->setupTimer();
    this->setupText();
}

void DiscoScene::setupTimer()
{
    m_timer.setup( TIMER_DURATION_MS );
    ofAddListener( m_timer.TIMER_COMPLETE , this, &DiscoScene::timerCompleteHandler ) ;
    
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
    m_timer.update();
    if(m_updateColors){
        this->updateColors();
    }
  
}

void DiscoScene::draw() {
    ofBackground(0,0,0);
    m_textVisual.draw();
}

void DiscoScene::willFadeIn() {
     ofLogNotice("DiscoScene::willFadeIn");
     AppManager::getInstance().getAudioManager().playSample("NightFever");
     this->setupDmx();
     m_timer.start(false);
     this->updateText();
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
    m_timer.stop();
}

void DiscoScene::willExit() {
    ofLogNotice("DiscoScene::willExit");
   
}

void DiscoScene::timerCompleteHandler( int &args )
{
    ofLogNotice("DiscoScene::timerCompleteHandler -> Timer completed");
    AppManager::getInstance().getGuiManager().onSceneChange("SHOWCASE");
}

void DiscoScene::setupDmx()
{
    m_updateColors = true;
    AppManager::getInstance().getDmxManager().onSetDmxLightStrobe();
    int motorSpeed = 127;
    //AppManager::getInstance().getDmxManager().onSetDmxMotorSpeed(motorSpeed);
    AppManager::getInstance().getGuiManager().onSetMotorSpeed(motorSpeed);
}

void DiscoScene::updateColors()
{
    auto animationColor = AppManager::getInstance().getLayoutManager().getAnimationColor();
    
    AppManager::getInstance().getSerialManager().onSetColor(animationColor);
    
}


