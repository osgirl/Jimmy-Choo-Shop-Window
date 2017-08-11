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
const int InstagramManager::SCENES_TIMER_INTERVAL_MS = 30000;

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
    this->setupTimers();
    
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
    if(m_tags.find(tag)==m_tags.end()) //No tag found with that name
    {
        return false;
    }
    
    string codeString = this->parseJsonTag(result);
    
    if(m_tags[tag]!=codeString){
        m_tags[tag]=codeString;
        
        string hashtagString = this->parseJsonTag(result);
        ofLogNotice() <<"InstagramManager::parseJson -> " << tag << ": "<< m_tags[tag];
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
    
    for (auto& tag : m_tags)
    {
        if(response.status==200 && response.request.name == tag.first)
        {
            //ofLogNotice() <<"InstagramManager::urlResponse -> " << response.request.name << ", " << response.status;
            
            m_newTag = this->checkUpdate(response.data, tag.first);
        }
    }
}


void InstagramManager::urlTimerCompleteHandler( int &args )
{
    m_urlTimer.start(false);
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
        string hastag = '#' + tag.first ;
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


