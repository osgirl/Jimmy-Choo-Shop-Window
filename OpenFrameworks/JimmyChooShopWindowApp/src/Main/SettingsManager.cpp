/*
 *  SettingsManager.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 27/07/17.
 *
 */

#include "ofMain.h"

#include "SettingsManager.h"


const string SettingsManager::APPLICATION_SETTINGS_FILE_NAME = "xmls/ApplicationSettings.xml";


SettingsManager::SettingsManager(): Manager(), m_appHeight(0.0), m_appWidth(0.0), m_dmxPort(-1), m_serialPort(-1), m_playbackTimeMs(3000), m_requestTimeMs(1000)
{
    //Intentionally left empty
}


SettingsManager::~SettingsManager()
{
    ofLogNotice() <<"SettingsManager::Destructor" ;
}


void SettingsManager::setup()
{
    if(m_initialized)
        return;
    
    ofLogNotice() <<"SettingsManager::initialized" ;
    
    Manager::setup();
    
    if(this->loadSettingsFile()){
        this->loadAllSettings();
    }
}

void SettingsManager::loadAllSettings()
{
    this->setWindowProperties();
    this->setDebugProperties();
    this->setNetworkProperties();
    this->loadSerialSettings();
    this->loadAppSettings();
    this->loadTextureSettings();
    this->loadSvgSettings();
    this->loadVideoSettings();
    this->loadAudioSettings();
    this->loadColors();
    this->loadTagSettings();
}

bool SettingsManager::loadSettingsFile()
{
    if(!m_xml.load(APPLICATION_SETTINGS_FILE_NAME)){
        ofLogNotice() <<"SettingsManager::loadSettingsFile-> unable to load file: " << APPLICATION_SETTINGS_FILE_NAME ;
        return false;
    }
    
    ofLogNotice() <<"SettingsManager::loadSettingsFile->  successfully loaded " << APPLICATION_SETTINGS_FILE_NAME ;
    return true;
}

void SettingsManager::setDebugProperties()
{
    m_xml.setTo("//");
    
    string ofPath = "//of_settings/debug";
    if(m_xml.exists(ofPath)) {
        m_xml.setTo(ofPath);
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes = m_xml.getAttributes();
        
        bool showCursor = ofToBool(attributes["showCursor"]);
        if(showCursor){
            ofShowCursor();
        }
        else{
            ofHideCursor();
        }
        
        bool setVerbose = ofToBool(attributes["setVerbose"]);
        if(setVerbose){
            ofSetLogLevel(OF_LOG_VERBOSE);
        }
        else{
            ofSetLogLevel(OF_LOG_NOTICE);
        }
        
        bool logToFile = ofToBool(attributes["logToFile"]);
        if(logToFile){
            ofLogToFile("logs/consoleLog.txt", false);
        }
       
        
        ofLogNotice() <<"SettingsManager::setDebugProperties->  successfully loaded the OF general settings" ;
        return;
    }
    
    ofLogNotice() <<"SettingsManager::setOFProperties->  path not found: " << ofPath ;
}

void SettingsManager::setWindowProperties()
{
    m_xml.setTo("//");
    
    string windowPath = "//of_settings/window";
    if(m_xml.exists(windowPath)) {
        m_xml.setTo(windowPath);
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes = m_xml.getAttributes();
        string title = attributes["title"];
        m_appWidth = ofToInt(attributes["width"]);
        m_appHeight= ofToInt(attributes["height"]);
        
        //m_appWidth = ofGetScreenWidth();
        //m_appHeight = ofGetScreenHeight();
        
        int x = ofToInt(attributes["x"]);
        int y = ofToInt(attributes["y"]);
        bool fullscreen = ofToBool(attributes["fullscreen"]);
        
        //ofSetFullscreen(fullscreen);
        //ofSetWindowShape(ofGetScreenWidth(),ofGetScreenHeight());
  
//        if(!fullscreen){
//            ofSetWindowPosition(x,y);
//        }
        ofSetWindowTitle(title);
        
        ofLogNotice() <<"SettingsManager::setWindowProperties->  successfully loaded the window settings" ;
        ofLogNotice() <<"SettingsManager::setWindowProperties->  title = "<< title<<", width = " << m_appWidth <<", height = "
        <<m_appHeight <<", x = "<<x<<", y = "<<y;
        return;
    }
    
    ofLogNotice() <<"SettingsManager::setWindowProperties->  path not found: " << windowPath ;
}
void SettingsManager::setNetworkProperties()
{
    m_xml.setTo("//");
    
    string networkPath = "//of_settings/network";
    if(m_xml.exists(networkPath)) {
        m_xml.setTo(networkPath);
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes = m_xml.getAttributes();
        
        m_portOscSend  = ofToInt(attributes["portOscSend"]);
        m_portOscReceive  = ofToInt(attributes["portOscReceive"]);
        m_ipAddress  = ofToString(attributes["ipAddress"]);
        m_syphonName = ofToString(attributes["syphon"]);
        m_midiName = ofToString(attributes["midi_name"]);
        
        ofLogNotice() <<"SettingsManager::setNetworkProperties->  successfully loaded the network settings" ;
        return;
    }
    
    ofLogNotice() <<"SettingsManager::setNetworkProperties->  path not found: " << networkPath ;
}


void SettingsManager::loadSerialSettings()
{
    m_xml.setTo("//");
    
    string path = "//of_settings/serial";
    if(m_xml.exists(path)) {
        m_xml.setTo(path);
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes = m_xml.getAttributes();
        
        bool autoSerial = ofToBool(attributes["auto"]);
        
        if(autoSerial){
             ofLogNotice() <<"SettingsManager::loadSerialSettings->  serial will be automatically selected" ;
            m_dmxPort = -1;
            m_serialPort = -1;
        }
        else{
            m_serialPort = ofToInt(attributes["serialPort"]);
            m_dmxPort = ofToInt(attributes["dmxPort"]);
            
            ofLogNotice() <<"SettingsManager::loadSerialSettings->  serial port = " << m_serialPort << ", dmx port = " << m_dmxPort;
        }
        
        ofLogNotice() <<"SettingsManager::loadSerialSettings->  successfully loaded the serial settings" ;
        return;
    }
    
    ofLogNotice() <<"SettingsManager::loadSerialSettings->  path not found: " << path ;
}

void SettingsManager::loadAppSettings()
{
    m_xml.setTo("//");
    
    string path = "//of_settings/app";
    if(m_xml.exists(path)) {
        m_xml.setTo(path);
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes = m_xml.getAttributes();
        
        m_requestTimeMs = ofToInt(attributes["request_time_ms"]);
        m_playbackTimeMs = ofToInt(attributes["playback_time_ms"]);
        
        ofLogNotice() <<"SettingsManager::loadAppSettings->  request time = " << m_requestTimeMs << "ms, playback time = " << m_playbackTimeMs <<"ms";
        ofLogNotice() <<"SettingsManager::loadAppSettings->  successfully loaded the app settings" ;
        return;
    }
    
    ofLogNotice() <<"SettingsManager::loadAppSettings->  path not found: " << path ;
}

void SettingsManager::loadColors()
{
    m_xml.setTo("//");
    
    string colorsSettingsPath = "//colors";
    if(m_xml.exists(colorsSettingsPath)) {
        
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes;
        
        colorsSettingsPath = "//colors/color[0]";
        m_xml.setTo(colorsSettingsPath);
        do {
            
            attributes = m_xml.getAttributes();
            
            int r = ofToInt(attributes["r"]);
            int g = ofToInt(attributes["g"]);
            int b = ofToInt(attributes["b"]);
            int a = ofToInt(attributes["a"]);
            
            ofPtr<ofColor> color = ofPtr<ofColor> (new ofColor(r,g,b,a));
            m_colors[attributes["name"]] = color;
            
            
            ofLogNotice() <<"SettingsManager::loadColors->  color = " << attributes["name"] <<", r = " << r
            <<", g = "<< g << ", b = " << b << ", a = " << a ;
        }
        while(m_xml.setToSibling()); // go to the next node
        
        
        ofLogNotice() <<"SettingsManager::loadColors->  successfully loaded the applications colors" ;
        return;
    }
    
    ofLogNotice() <<"SettingsManager::loadColors->  path not found: " << colorsSettingsPath ;
}

void SettingsManager::loadTextureSettings()
{
    m_xml.setTo("//");
    
    string resourcesPath = "//textures";
    if(m_xml.exists(resourcesPath)) {
        
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes;
        
        resourcesPath = "//textures/texture[0]";
        m_xml.setTo(resourcesPath);
        do {
            
            attributes = m_xml.getAttributes();
            m_texturesPath[attributes["name"]] = attributes["path"];
            
            ofLogNotice() <<"SettingsManager::loadTextureSettings->  texture = " << attributes["name"]
            <<", path = "<< attributes["path"] ;
        }
        while(m_xml.setToSibling()); // go to the next texture
        
        
        ofLogNotice() <<"SettingsManager::loadTextureSettings->  successfully loaded the resource settings" ;
        return;
    }
    
    ofLogNotice() <<"SettingsManager::loadTextureSettings->  path not found: " << resourcesPath ;
}

ofColor SettingsManager::getColor(const string& colorName)
{
    ofColor color;
    if(m_colors.find(colorName)!= m_colors.end()){
        color.setHex(m_colors[colorName]->getHex());
    }
    
    return color;
}


void SettingsManager::loadSvgSettings()
{
    m_xml.setTo("//");
    
    string svgPath = "//svgs";
    if(m_xml.exists(svgPath)) {
        
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes;
        
        svgPath = "//svgs/svg[0]";
        m_xml.setTo(svgPath);
        do {
            
            attributes = m_xml.getAttributes();
            m_svgResourcesPath[attributes["name"]] = attributes["path"];
            
            ofLogNotice() <<"SettingsManager::loadSvgSettings->  svg = " << attributes["name"]
            <<", path = "<< attributes["path"] ;
        }
        while(m_xml.setToSibling()); // go to the next svg
        
        
        ofLogNotice() <<"SettingsManager::loadSvgSettings->  successfully loaded the resource settings" ;
        return;
    }
    
    ofLogNotice() <<"SettingsManager::loadSvgSettings->  path not found: " << svgPath ;
}

void SettingsManager::loadVideoSettings()
{
    m_xml.setTo("//");
    
    string path = "//videos";
    if(m_xml.exists(path)) {
        
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes;
        
        path = "//videos/video[0]";
        m_xml.setTo(path);
        do {
            
            attributes = m_xml.getAttributes();
            m_videoResourcesPath[attributes["name"]] = attributes["path"];
            
            ofLogNotice() <<"SettingsManager::loadVideoSettings->  video = " << attributes["name"]
            <<", path = "<< attributes["path"] ;
        }
        while(m_xml.setToSibling()); // go to the next svg
        
        
        ofLogNotice() <<"SettingsManager::loadSvgSettings->  successfully loaded the video settings" ;
        return;
    }
    
    ofLogNotice() <<"SettingsManager::loadSvgSettings->  path not found: " << path ;
}



void SettingsManager::loadAudioSettings()
{
    m_xml.setTo("//");
    
    string path = "//audio";
    if(m_xml.exists(path)) {
        
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes;
        
        path = "//audio/sample[0]";
        m_xml.setTo(path);
        do {
            
            attributes = m_xml.getAttributes();
            m_audioResourcesPath[attributes["name"]] = attributes["path"];
            
            ofLogNotice() <<"SettingsManager::loadAudioSettings->  sample = " << attributes["name"]
            <<", path = "<< attributes["path"] ;
        }
        while(m_xml.setToSibling()); // go to the next svg
        
        
        ofLogNotice() <<"SettingsManager::loadAudioSettings->  successfully loaded the audio settings" ;
        return;
    }
    
    ofLogNotice() <<"SettingsManager::loadAudioSettings->  path not found: " << path ;
}

void SettingsManager::loadTagSettings()
{
    m_xml.setTo("//");
    
    string path = "//tags";
    if(m_xml.exists(path)) {
        
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes;
        
        path = "//tags/tag[0]";
        m_xml.setTo(path);
        do {
            
            attributes = m_xml.getAttributes();
            m_tags.push_back(attributes["name"]);
            
            ofLogNotice() <<"SettingsManager::loadTagSettings->  tag = " << attributes["name"];
        }
        while(m_xml.setToSibling()); // go to the next svg
        
        
        ofLogNotice() <<"SettingsManager::loadTagSettings->  successfully loaded the tag settings" ;
        return;
    }
    
    ofLogNotice() <<"SettingsManager::loadTagSettings->  path not found: " << path ;
}





