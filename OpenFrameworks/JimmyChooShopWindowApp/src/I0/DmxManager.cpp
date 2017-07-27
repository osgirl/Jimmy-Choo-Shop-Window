/*
 *  DmxManager.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 27/07/17.
 *
 */

#include "DmxManager.h"
#include "AppManager.h"


DmxManager::DmxManager(): Manager()
{
    //Intentionally left empty
}

DmxManager::~DmxManager()
{
   ofLogNotice() << "DmxManager::destructor";
}


//--------------------------------------------------------------

void DmxManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    this->setupDmx();
    ofLogNotice() <<"DmxManager::initialized" ;
}

void DmxManager::setupDmx()
{
    m_dmx.connect("/dev/tty.usbserial-EN198035"); // use the name
}

void DmxManager::update()
{
    m_dmx.update();
}
