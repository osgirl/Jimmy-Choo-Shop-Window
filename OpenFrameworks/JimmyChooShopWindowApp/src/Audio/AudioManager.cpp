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




AudioManager::AudioManager(): Manager(), m_currentPath("")
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
    m_soundPlayer.setVolume(1.0);
    
     m_videoSamples = AppManager::getInstance().getSettingsManager().getVideoResourcesPath();
    
    

    
    #ifdef TARGET_RASPBERRY_PI
        ofxOMXPlayerSettings settings;
        //settings.videoPath = path;
        settings.useHDMIForAudio = true;	//default true
        settings.enableTexture = true;		//default true
        settings.enableLooping = true;		//default true
        settings.enableAudio = true;		//default true, save resources by disabling
    
        //so either pass in the settings
        m_omxPlayer.setup(settings);
    #endif
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
#ifdef TARGET_RASPBERRY_PI
    
        if(m_videoSamples.find(name)==m_videoSamples.end()){
            ofLogNotice() <<"AudioManager::playSample -> No sample named:  " << name ;
            return false;
        }
    
        string path =  ofToDataPath(m_videoSamples[name],true);
    
        if(m_currentPath == path){
            m_omxPlayer.restartMovie();
        }
        else{
             m_omxPlayer.loadMovie(path);
             m_currentPath = path;
        }
    
        //so either pass in the settings
    
        m_omxPlayer.setPaused(false);
    
       return true;
    
#else

    if(m_sampleNames.find(name)==m_sampleNames.end()){
        ofLogNotice() <<"AudioManager::playSample -> No sample named:  " << name ;
        return false;
    }
    
    string path = m_sampleNames[name];
    
    if(!m_soundPlayer.load(path)){
        ofLogNotice() <<"AudioManager::playSample -> No sample found under path:  " << path ;
        return false;
    }
    
    m_soundPlayer.setLoop(true); //Sound will loop
    m_soundPlayer.play();
    return true;
    
#endif
    
    
}

void AudioManager::stopSample()
{
    #ifdef TARGET_RASPBERRY_PI
        m_omxPlayer.setPaused(true);
    #else
    
         m_soundPlayer.stop();
    
    #endif
}



