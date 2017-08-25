/*
 *  InstagramManager.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 29/07/17.
 *
 */

#include "InstagramManager.h"
#include "AppManager.h"


const int InstagramManager::URL_TIMER_INTERVAL_MS = 1000;
const int InstagramManager::SCENES_TIMER_INTERVAL_MS = 3000;

InstagramManager::InstagramManager(): Manager(), m_currentString(""), m_newTag(false), m_firstTag(true), m_currentCode("")
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
    this->setupTimers();
    
    ofRegisterURLNotification(this);
    
    ofLogNotice() <<"InstagramManager::initialized" ;
}

void InstagramManager::setupTags()
{
    m_tags = AppManager::getInstance().getSettingsManager().getTags();
}

void InstagramManager::setupTimers()
{
    m_urlTimer.setup( URL_TIMER_INTERVAL_MS );
    
    m_urlTimer.start( false ) ;
    ofAddListener( m_urlTimer.TIMER_COMPLETE , this, &InstagramManager::urlTimerCompleteHandler ) ;
    
    
    m_scenesTimer.setup( SCENES_TIMER_INTERVAL_MS );
    
    m_scenesTimer.start( false ) ;
    ofAddListener( m_scenesTimer.TIMER_COMPLETE , this, &InstagramManager::scenesTimerCompleteHandler ) ;
}

void InstagramManager::update()
{
    this->updateTimers();
   
    if(m_newTag){
        m_newTag = false;
        this->resetDiscoScene();
    }
}


void InstagramManager::updateTimers()
{
    m_urlTimer.update();
    m_scenesTimer.update();
}

void InstagramManager::resetDiscoScene()
{
    AppManager::getInstance().getGuiManager().onSceneChange("DISCO");
    AppManager::getInstance().getSceneManager().changeScene("DISCO");
    ofLogNotice() <<"InstagramManager::resetDiscoScenes" ;
    m_scenesTimer.start(false, true);
}



bool InstagramManager::checkUpdate(const string& result, const string& tag)
{
   
    if ( std::find(m_tags.begin(), m_tags.end(), tag) == m_tags.end() )
    {
        return false;
    }
    
    
    string codeString = this->parseJsonCode(result);
    
    
    if(m_currentCode!=codeString){
        m_currentCode=codeString;
        
        string hashtagString = this->parseJsonTag(result);
        ofLogNotice() <<"InstagramManager::parseJson -> " << tag << ": "<< m_currentCode;
        if(this->checkAllTags(hashtagString)){
            m_currentString = hashtagString;
            return true;
        }
        
    }
    
     return false;
    
    // cout << json["tag"]["media"]["nodes"][0]["caption"].asString() <<endl;
}

string InstagramManager::parseJsonTag(const string& result)
{
    m_json.parse(result);
    return m_json["tag"]["media"]["nodes"][0]["caption"].asString();
}

string InstagramManager::parseJsonCode(const string& result)
{
    m_json.parse(result);
    return m_json["tag"]["media"]["nodes"][0]["code"].asString();
}


void InstagramManager::urlResponse(ofHttpResponse & response)
{
    //ofLogNotice() <<"InstagramManager::urlResponse -> " << response.request.name << ", " << response.status;
    
    if(m_tags.empty()){
        return;
    }

    if(response.status==200 && response.request.name == m_tags.front())
    {
//        ofLogNotice() <<"InstagramManager::urlResponse -> " << response.request.name << ", " << response.status;
        
        m_newTag = this->checkUpdate(response.data, m_tags.front());
    }
}


void InstagramManager::urlTimerCompleteHandler( int &args )
{
    m_urlTimer.start(false);
  //  cout<<"TIMER COMPLETED"<<endl;
    string start = "https://www.instagram.com/explore/tags/" ;
    string end = "/?__a=1" ;
    
    if(m_tags.empty()){
        return;
    }
    
    string url = start + m_tags.front() + end;
    ofLoadURLAsync(url, m_tags.front());
}


void InstagramManager::scenesTimerCompleteHandler( int &args )
{
    //ofLogNotice("InstagramManager::scenesTimerCompleteHandler -> Timer completed");
    AppManager::getInstance().getGuiManager().onSceneChange("SHOWCASE");
    AppManager::getInstance().getSceneManager().changeScene("SHOWCASE");
}

bool InstagramManager::checkAllTags(const string& result)
{
    bool allTagsAreInResult = true;
    
    for (auto& tag : m_tags)
    {
        string hastag = '#' + tag ;
        if(!ofIsStringInString(result, hastag))
        {
            ofLogNotice() <<"InstagramManager::checkAllTags -> hashtag not found: " << hastag;
            allTagsAreInResult = false;
            return false;
        }
		else {
			ofLogNotice() << "InstagramManager::checkAllTags -> hashtag found!!!: " << hastag;
		}
    }
    
    return allTagsAreInResult;
}


