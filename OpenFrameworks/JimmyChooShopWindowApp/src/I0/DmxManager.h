/*
 *  DmxManager.h
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 27/07/17.
 *
 */

#pragma once

#include "ofMain.h"
#include "Manager.h"
#include "ofxDmx.h"
//#include "ofxDmx4All.h"

//========================== class DmxManager =======================================
//==============================================================================
/** \class DmxManager DmxManager.h
 *	\brief class for managing DMX communication
 *	\details It connects to an Enttec USB pro and sends serial-dmx commands
 */


class DmxManager: public Manager
{

public:
    //! Constructor
    DmxManager();

    //! Destructor
    virtual ~DmxManager();

    //! setups DMX
    void setup();

    void update();

    void onSetDmxLightChannel(int& value);
    
    void onSetDmxMotorChannel(int& value);
    
    void onSetDmxMotorSpeed(int& value);
    
    void onSetDmxLightColor(const ofColor& color);
    
    void onSetDmxLightStrobe();
    
    void onSetDmxLightSolid();

private:
    
    void setupDmx();
    
    void exit();
    
private:
    
    ofxDmx m_dmx;
    int m_dmxLightStartChannel;
    int m_dmxMotorStartChannel;

};

