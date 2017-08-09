/*
 *  InstagramManager.h
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 29/07/17.
 *
 */

#pragma once

#include "ofMain.h"
#include "Manager.h"
#include "ofxSimpleTimer.h"
#include "ofxJSON.h"

//========================== class InstagramManager =======================================
//==============================================================================
/** \class InstagramManager InstagramManager.h
 *	\brief class for managing the Instagram feeds
 *	\details It frequently checks for certain instagram hashtags
 */


class InstagramManager: public Manager
{
    
    static const int URL_TIMER_INTERVAL_MS;
    static const int SCENES_TIMER_INTERVAL_MS;

public:
    //! Constructor
    InstagramManager();

    //! Destructor
    virtual ~InstagramManager();

    //! setups DMX
    void setup();

    void update();
    
    void urlResponse(ofHttpResponse & response);
    
    void urlTimerCompleteHandler( int &args ) ;
    
    void scenesTimerCompleteHandler( int &args ) ;
    
    const string& getCurrentString() const {return m_currentString;}


private:
    
    void setupTimers();
    
    void setupTags();
    
    void updateTimers();
    
    bool checkUpdate(const string& result, const string& tag);
    
    string parseJson(const string& result);
    
    bool checkAllTags(const string& result);
    
    void resetDiscoScene();
    
private:
    
    
    typedef            map<string,string> TagMap; ///< Defines a map of current feeds related to a tag
    
    TagMap             m_tags;
    ofxSimpleTimer     m_urlTimer;
    ofxSimpleTimer     m_scenesTimer;
    ofxJSONElement     m_json;
    string             m_currentString;
    bool               m_newTag;

};

