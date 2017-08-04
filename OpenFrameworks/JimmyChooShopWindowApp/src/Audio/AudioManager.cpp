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


AudioManager::AudioManager(): Manager()
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
}


void AudioManager::draw()
{
    
}

bool AudioManager::playSample(string name)
{
//    if(m_sampleNames.find(name)==m_sampleNames.end()){
//        ofLogNotice() <<"AudioManager::playSample -> No sample named:  " << name ;
//        return false;
//    }
//    
//    string path = m_sampleNames[name];
//    
//    if(!m_soundPlayer.load(path)){
//        ofLogNotice() <<"AudioManager::playSample -> No sample found under path:  " << path ;
//        return false;
//    }
//    
//    m_soundPlayer.play();
//    return true;
//    
    
    
    if(m_videoSamples.find(name)==m_videoSamples.end()){
        ofLogNotice() <<"AudioManager::playSample -> No sample named:  " << name ;
        return false;
    }
    
    string path =  ofToDataPath(m_videoSamples[name],true);
    
    string videoPath = ofToDataPath("../../../video/Timecoded_Big_bunny_1.mov", true);
    
    //Somewhat like ofFboSettings we may have a lot of options so this is the current model
    ofxOMXPlayerSettings settings;
    settings.videoPath = path;
    settings.useHDMIForAudio = true;	//default true
    settings.enableTexture = true;		//default true
    settings.enableLooping = true;		//default true
    settings.enableAudio = true;		//default true, save resources by disabling
    
    //so either pass in the settings
    m_omxPlayer.setup(settings);
    
    return true;
}

void AudioManager::stopSample()
{
   // m_soundPlayer.stop();
    m_omxPlayer.close();
}



