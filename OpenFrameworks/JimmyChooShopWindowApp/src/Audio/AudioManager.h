/*
 *  AudioManager.h
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 27/07/17.
 *
 */


#pragma once

#include "Manager.h"
#include "SettingsManager.h"
#include "BasicVisual.h"


//========================== class AudioManager ==============================
//============================================================================
/** \class AudioManager AudioManager.h
 *	\brief Class managing the audio
 *	\details it loads the samples and gives the methods to play them
 */


class AudioManager: public Manager
{
    static const float    FADE_TIME_S; //< Fade time in seconds
    
public:
    
    //! Constructor
    AudioManager();
    
    //! Destructor
    ~AudioManager();
    
    //! Setup the Audio Manager
    void setup();
    
    //! Update the Audio Manager
    void update();
    
    //! Draw the Audio Manager
    void draw();
    
    bool playSample(string name);
    
    void stopSample();
    
    
private:
        
    void setupSamples();
    
    void loadSample();
    
private:
    
    ResourcesPathMap    m_sampleNames;
    ResourcesPathMap    m_videoSamples;
    ofSoundPlayer       m_soundPlayer;
    string              m_currentPath;
    ofPtr<BasicVisual>  m_audioVolume;

};



