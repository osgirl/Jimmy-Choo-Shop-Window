/*
 *  AudioManager.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 27/07/17.
 *
 */



#include "ofMain.h"

#include "AudioManager.h"
#include "AppManager.h"




AudioManager::AudioManager(): Manager(), m_currentPath(""), m_soundPlayer(NULL)
{
    //Intentionally left empty
}


AudioManager::~AudioManager()
{
    ofLogNotice() <<"AudioManager::Destructor" ;
}

void AudioManager::setup()
{
    if(m_initialized)
        return;
    
    
    Manager::setup();
    
    this->setupSamples();
   
    ofLogNotice() <<"AudioManager::initialized" ;
    
}

void AudioManager::setupSamples()
{
    m_sampleNames = AppManager::getInstance().getSettingsManager().getAudioResourcesPath();
    
    m_videoSamples = AppManager::getInstance().getSettingsManager().getVideoResourcesPath();
    
}



void AudioManager::update()
{
    // update the sound playing system:
    //ofSoundUpdate();
    
    //m_videoPlayer.update();

}


void AudioManager::draw()
{
    
}

bool AudioManager::playSample(string name)
{
    
    if(m_sampleNames.find(name)==m_sampleNames.end()){
        ofLogNotice() <<"AudioManager::playSample -> No sample named:  " << name ;
        return false;
    }
    
    string path = m_sampleNames[name];
    
    if(!m_soundPlayer){
        m_soundPlayer = new ofSoundPlayer();
    }
    if(!m_soundPlayer->load(path)){
            ofLogNotice() <<"AudioManager::playSample -> No sample found under path:  " << path ;
            return false;
    }
    
    
    m_soundPlayer->setLoop(true); //Sound will loop
    m_soundPlayer->play();
    return true;
}

void AudioManager::stopSample()
{
    
    if(m_soundPlayer){
        m_soundPlayer->stop();
        delete m_soundPlayer;
        m_soundPlayer = NULL;
    }
}



