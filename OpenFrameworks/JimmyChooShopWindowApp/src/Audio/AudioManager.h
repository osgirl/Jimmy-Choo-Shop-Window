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

#ifdef TARGET_RASPBERRY_PI
    #include "ofxOMXPlayer.h"
#endif


//========================== class AudioManager ==============================
//============================================================================
/** \class AudioManager AudioManager.h
 *	\brief Class managing the audio
 *	\details it loads the samples and gives the methods to play them
 */


class AudioManager: public Manager
{
    static const string UNICODE_FONT_PATH; //The Apps unicode font path
    
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
    
private:
    
    ResourcesPathMap    m_sampleNames;
    ResourcesPathMap    m_videoSamples;
    ofSoundPlayer       m_soundPlayer;
    ofVideoPlayer       m_videoPlayer;
    string              m_currentPath;
    
#ifdef TARGET_RASPBERRY_PI
    ofxOMXPlayer m_omxPlayer;
#endif

};



