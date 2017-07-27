/*
 *  AudioManager.h
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 27/07/17.
 *
 */


#pragma once

#include "Manager.h"

//========================== class AudioManager ==============================
//============================================================================
/** \class AudioManager AudioManager.h
 *	\brief Class managing the text
 *	\details it renders the current subtitles according to a width, height and position
 */


class AudioManager: public Manager
{
    static const string UNICODE_FONT_PATH; //The Apps unicode font path
    
public:
    
    //! Constructor
    AudioManager();
    
    //! Destructor
    ~AudioManager();
    
    //! Setup the Text Manager
    void setup();
    
    //! Update the Text Manager
    void update();
    
    //! Draw the Text Manager
    void draw();
    
    
private:
        
    void setupSamples();
    
    
private:
    
    ofSoundPlayer  m_soundPlayer;

};



