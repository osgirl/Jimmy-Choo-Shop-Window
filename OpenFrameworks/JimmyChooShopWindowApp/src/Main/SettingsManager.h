/*
 *  SettingsManager.h
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 27/07/17.
 *
 */


#pragma once

#include "Manager.h"

//========================== class SettingsManager ==============================
//============================================================================
/** \class SettingsManager SettingsManager.h
 *	\brief Class managing the whole settings of the application
 *	\details it reads from an xml settings file and provides access to the information
 */

typedef             map<string,string>               ResourcesPathMap;       ///< defines a map of path attached to the resources name
typedef             vector< string >                 ResourcesVector;             ///< Defines a vector of resource names

class SettingsManager: public Manager
{
    
public:
    
    static const string APPLICATION_SETTINGS_FILE_NAME;
    
    //! Destructor
    ~SettingsManager();
    
    //! Constructor
    SettingsManager();
    
    //! Compares two transition objects
    void setup();
    
    const ResourcesPathMap& getTextureResourcesPath() const {return m_texturesPath;}
    
    const ResourcesPathMap& getSvgResourcesPath() const {return m_svgResourcesPath;}
    
    const ResourcesPathMap& getVideoResourcesPath() const {return m_videoResourcesPath;}
    
    const ResourcesPathMap& getAudioResourcesPath() const {return m_audioResourcesPath;}
    
    const ResourcesVector& getTags() const {return m_tags;}
    
    ofColor getColor(const string& colorName);
    
    float getAppWidth() const {return m_appWidth;}
    
    float getAppHeight() const {return m_appHeight;}
    
    string getIpAddress() const {return m_ipAddress;}
    
    int getOscPortSend() const {return m_portOscSend;}
    
    int getOscPortReceive() const {return m_portOscReceive;}
    
    string getSyphonName() const {return m_syphonName;}
    
    string getMidiName() const {return m_midiName;}
    
    int getDmxPort() const {return m_dmxPort;}
    
    int getSerialPort() const {return m_serialPort;}
    
    int getPlaybackTime() const {return m_playbackTimeMs;}
    
    int getRequestTime() const {return m_requestTimeMs;}
    
private:
    
    //! Loads the settings file
    bool loadSettingsFile();
    
    //! Loads all the settings
    void loadAllSettings();
    
    //! Sets all the debug properties
    void setDebugProperties();
    
    //! Sets all the network properties
    void setNetworkProperties();
    
    //! Sets all the window properties
    void setWindowProperties();
    
    //! Loads all the app settings
    void loadAppSettings();
    
    //! Loads all the app colors
    void loadColors();
    
    //! Loads all the textures settings
    void loadTextureSettings();
    
    //! Loads all the svg images settings
    void loadSvgSettings();
    
    //! Loads all the video  settings
    void loadVideoSettings();
    
    //! Loads all the audio  settings
    void loadAudioSettings();
    
    //! Loads all the tag  settings
    void loadTagSettings();
    
    //! Loads all the serial  settings
    void loadSerialSettings();
    
private:
    
    typedef             map< string, ofPtr<ofColor> >    ColorMap;              ///< Defines a map of colors attached to a name
    
    
    ofXml		            m_xml;          ///< instance of the xml parser
    ResourcesPathMap        m_texturesPath;         ///< stores the texture paths
    ResourcesPathMap        m_svgResourcesPath;     ///< stores the svg paths
    ResourcesPathMap        m_videoResourcesPath;   ///< stores the video paths
    ResourcesPathMap        m_audioResourcesPath;   ///< stores the audio paths
    ColorMap                m_colors;               ///< stores all the application's colors
    ResourcesVector         m_tags;                 ///< stroes all the tags
    float                   m_appWidth;             ///< stores the applications width
    float                   m_appHeight;            ///< stores the applications height
    int                     m_portOscSend;          ///< stores the OSC port used for the OSC Sending communications
    int                     m_portOscReceive;       ///< stores the OSC port used for the OSC Receiving communications
    string                  m_ipAddress;            ///< stores the Ip Address used for the Network communications
    string                  m_syphonName;           ///<stores the name of the syphon pipe name
    string                  m_midiName;             ///<stores the name of the midi device
    bool                    m_autoSerial;           ///< stores whether the serial port has to be search automatically or not
    int                     m_serialPort;           ///< stores the settings serial port
    int                     m_dmxPort;              ///< stores the settings dmx port
    int                     m_playbackTimeMs;       ///< stores the playback time of the song
    int                     m_requestTimeMs;        ///< stores the request time between checking new instagram feeds
    
};


