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

InstagramManager::InstagramManager(): Manager(), m_currentString("")
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
    
    this->setupTimer();
    ofRegisterURLNotification(this);
    
    ofLogNotice() <<"InstagramManager::initialized" ;
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
}


void InstagramManager::parseJson(const string& result){
    
    m_json.parse(result);
    
    string hashtagString =  m_json["tag"]["media"]["nodes"][0]["caption"].asString();
    
    if(m_currentString!=hashtagString){
        m_currentString=hashtagString;
        ofLogNotice() <<"InstagramManager::parseJson -> " << m_currentString;
    }
    
    
    // cout << json["tag"]["media"]["nodes"][0]["caption"].asString() <<endl;
}

void InstagramManager::urlResponse(ofHttpResponse & response){
    if(response.status==200 && response.request.name == "hashtag"){
        //cout << response.data << endl;
        this->parseJson(response.data );
    }else{
        cout << response.status << " " << response.error << endl;
    }
}


void InstagramManager::timerCompleteHandler( int &args )
{
    m_timer.start(false);
    //cout<<"TIMER COMPLETED"<<endl;
    ofLoadURLAsync("https://www.instagram.com/explore/tags/onelove/?__a=1","hashtag");
}

