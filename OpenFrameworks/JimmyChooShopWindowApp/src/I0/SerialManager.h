/*
 *  SerialManager.h
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 27/07/17.
 *
 */

#pragma once

#include "ofMain.h"
#include "Manager.h"
#include "ofxDmx.h"

//========================== class SerialManager =======================================
//==============================================================================
/** \class SerialManager SerialManager.h
 *	\brief class for managing Serial communication
 *	\details It connects the Teensy board to communicate color changes on the neon leds.
 */


class SerialManager: public Manager
{

    static const int BAUD_RATE;
    
public:
    //! Constructor
    SerialManager();

    //! Destructor
    virtual ~SerialManager();

    //! setups DMX
    void setup();

    void update();
    
    void onSetColor(const ofColor& color);
    
private:
    
    void setupSerial();
    
    bool checkConnection(int portNum);
    
    bool sendPin();
    
    bool receivedOk();
    
private:
    
     ofSerial	m_serial;

};

