/*
 *  SerialManager.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 27/07/17.
 *
 */

#include "SerialManager.h"
#include "AppManager.h"

const int SerialManager::BAUD_RATE = 115200;


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

    
    for(auto device: deviceList)
    {
        if(this->checkConnection(device.getDeviceID())) //open a device number
        {
            ofLogNotice() <<"SerialManager::setupSerial << Arduino connected to port " << device.getDeviceName();
            break;
        }
    }
    
//    if(!m_serial.setup(0, BAUD_RATE)) //open a device number)
//    {
//        ofLogNotice() <<"SerialManager::initialized << Could not cpnnect to serial " << deviceList[0].getDeviceName();
//    }
//    
}

bool SerialManager::checkConnection(int portNum)
{
    if(m_serial.setup(portNum, BAUD_RATE)) //open a device number
    {
        this->sendPin();
        ofSleepMillis(50);
        if(this->receivedOk()){
            ofLogNotice() <<"SerialManager::checkConnection << Arduino connected to " << portNum;
            return true;
        }
    }
    
    ofLogNotice() <<"SerialManager::checkConnection << Arduino is not connected ";
    //m_serial.setup(0, BAUD_RATE);
    return false;
    
}

bool SerialManager::sendPin()
{
    unsigned char byte = '?';
    m_serial.writeByte(byte);
}

bool SerialManager::receivedOk()
{
    ofLogNotice() <<"SerialManager::checkConnection << Serial Available: " << m_serial.available();

    
    if ( m_serial.available() == 0 )
    {
        return false;
    }
    
    /// // we want to read 2 bytes
    int bytesRequired = 2;
    unsigned char bytes[bytesRequired];
    int bytesRemaining = bytesRequired;
    // loop until we've read everything
    while ( bytesRemaining > 0 ){
        // check for data
        if ( m_serial.available() > 0 ){
            // try to read - note offset into the bytes[] array, this is so
            // that we don't overwrite the bytes we already have
            int bytesArrayOffset = bytesRequired - bytesRemaining;
            int result = m_serial.readBytes( &bytes[bytesArrayOffset], bytesRemaining );
            
                // check for error code
                if ( result == OF_SERIAL_ERROR ){
                    // something bad happened
                    ofLog( OF_LOG_ERROR, "unrecoverable error reading from serial" );
                    break;
                }
                else if ( result == OF_SERIAL_NO_DATA ){
                    // nothing was read, try again
                }
                else {
                    // we read some data!
                    bytesRemaining -= result;
                }
            }
    }
    
    if(bytes[0] == 'O' && bytes[1] == 'K'){
        ofLogNotice() <<"SerialManager::receivedOk << Arduino sent OK ";
        return true;
    }
    
    return false;
}

void SerialManager::update()
{
    //
}


void SerialManager::onSetColor(const ofColor& color)
{
    unsigned char bytes[5];
    
    bytes[0] = 'c';
    bytes[1] = color.r;
    bytes[2] = color.g;
    bytes[3] = color.b;
    bytes[4] = '\n';
    
    m_serial.writeBytes(bytes,sizeof(bytes));

}


void SerialManager::onSetDisco()
{
    m_serial.writeByte('d');
}

void SerialManager::onSetShowcase()
{
    m_serial.writeByte('s');
}
