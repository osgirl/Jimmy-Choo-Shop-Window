/*
 *  InstagramManager.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 29/07/17.
 *
 */

#include "InstagramManager.h"
#include "AppManager.h"


const int InstagramManager::TIMER_INTERVAL_MS = 2000;

InstagramManager::InstagramManager(): Manager(), m_currentString(""), m_newTag(false)
{
    //Intentionally left empty
}

InstagramManager::~InstagramManager()
{
   ofLogNotice() << "InstagramManager::destructor";
   ofUnregisterURLNotification(this);
}


//--------------------------------------------------------------

void InstagramManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    this->setupTags();
    this->setupTimer();
    
    ofRegisterURLNotification(this);
    
    ofLogNotice() <<"InstagramManager::initialized" ;
}

void InstagramManager::setupTags()
{
    auto& tags = AppManager::getInstance().getSettingsManager().getTags();
    for(auto& tag: tags)
    {
        m_tags[tag] = "";
        ofLogNotice() <<"InstagramManager::setupTags -> Added tag: " << tag;
    }
}

void InstagramManager::setupTimer()
{
    m_timer.setup( TIMER_INTERVAL_MS );
    
    m_timer.start( false ) ;
    ofAddListener( m_timer.TIMER_COMPLETE , this, &InstagramManager::timerCompleteHandler ) ;
}

void InstagramManager::update()
{
    m_timer.update();
    if(m_newTag){
        m_newTag = false;
        AppManager::getInstance().getGuiManager().onSceneChange("DISCO");
    }
}


bool InstagramManager::checkUpdate(const string& result, const string& tag)
{
    if(m_tags.find(tag)==m_tags.end()) //No tag found with that name
    {
        return false;
    }
    
    string hashtagString = this->parseJson(result);
    
    if(m_tags[tag]!=hashtagString){
        m_tags[tag]=hashtagString;
        ofLogNotice() <<"InstagramManager::parseJson -> " << tag << ": "<< m_tags[tag];
        if(this->checkAllTags(result)){
            m_currentString = m_tags[tag];
            return true;
        }
        
    }
    
     return false;
    
    // cout << json["tag"]["media"]["nodes"][0]["caption"].asString() <<endl;
}

string InstagramManager::parseJson(const string& result)
{
    m_json.parse(result);
    return m_json["tag"]["media"]["nodes"][0]["caption"].asString();
}

void InstagramManager::urlResponse(ofHttpResponse & response)
{
    //ofLogNotice() <<"InstagramManager::urlResponse -> " << response.request.name << ", " << response.status;
    
    for (auto& tag : m_tags)
    {
        if(response.status==200 && response.request.name == tag.first)
        {
            //ofLogNotice() <<"InstagramManager::urlResponse -> " << response.request.name << ", " << response.status;
            
            m_newTag = this->checkUpdate(response.data, tag.first);
        }
    }
}


void InstagramManager::timerCompleteHandler( int &args )
{
    m_timer.start(false);
    //cout<<"TIMER COMPLETED"<<endl;
    string start = "https://www.instagram.com/explore/tags/" ;
    string end = "/?__a=1" ;
    
    for (auto& tag : m_tags) {
        string url = start + tag.first + end;
        ofLoadURLAsync(url,tag.first);
        break; //Just use the first tag as reference
        //ofLogNotice() <<"InstagramManager::loadurl -> " << url;
    }
}


bool InstagramManager::checkAllTags(const string& result)
{
    bool allTagsAreInResult = true;
   
    for (auto& tag : m_tags)
    {
        string hastag = '#' + tag.first ;
        if(!ofIsStringInString(result, hastag))
        {
            ofLogNotice() <<"InstagramManager::checkAllTags -> hashtag not found: " << hastag;
            allTagsAreInResult = false;
            break;
        }
    }
    
    return allTagsAreInResult;
}


