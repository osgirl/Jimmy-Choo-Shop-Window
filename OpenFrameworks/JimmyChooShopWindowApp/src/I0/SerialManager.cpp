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
   this->onSetColor(ofColor::black);
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
    int portNum = 3;
    
    if(!m_serial.setup(portNum, baud)) //open a device number)
    {
        ofLogNotice() <<"SerialManager::initialized << Could not cpnnect to serial " << deviceList[portNum].getDeviceName();
    }
    
}

void SerialManager::update()
{
    //
}


void SerialManager::onSetColor(const ofColor& color)
{
    unsigned char bytes[4];
    
    bytes[0] = color.r;
    bytes[1] = color.g;
    bytes[2] = color.b;
    bytes[3] = '\n';
    
    m_serial.writeBytes(bytes,sizeof(bytes));

}
