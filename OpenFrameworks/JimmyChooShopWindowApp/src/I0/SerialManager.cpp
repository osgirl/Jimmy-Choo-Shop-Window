/*
 *  SerialManager.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 27/07/17.
 *
 */

#include "SerialManager.h"
#include "AppManager.h"


SerialManager::SerialManager(): Manager()
{
    //Intentionally left empty
}

SerialManager::~SerialManager()
{
   ofLogNotice() << "SerialManager::destructor";
}


//--------------------------------------------------------------

void SerialManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    this->setupSerial();
    ofLogNotice() <<"SerialManager::initialized" ;
}

void SerialManager::setupSerial()
{
    m_serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = m_serial.getDeviceList();
    
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    int baud = 9600;
    m_serial.setup(0, baud); //open the first device
    
    ofColor color = ofColor::cyan;
}

void SerialManager::update()
{
    //
}
