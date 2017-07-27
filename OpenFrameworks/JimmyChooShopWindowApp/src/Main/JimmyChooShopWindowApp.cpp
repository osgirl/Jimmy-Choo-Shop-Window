/*
 *  JimmyChooShopWindowApp.cpp
 *  Jimmy Choo Shop Window
 *
 *  Created by Imanol Gomez on 27/07/17.
 *
 */


#include "AppManager.h"

#include "JimmyChooShopWindowApp.h"

//--------------------------------------------------------------
void JimmyChooShopWindowApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void JimmyChooShopWindowApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void JimmyChooShopWindowApp::draw(){
    AppManager::getInstance().draw();
}

void JimmyChooShopWindowApp::exit()
{
    ofLogNotice() <<"JimmyChooShopWindowApp::exit";
    AppManager::getInstance().exit();
}

//--------------------------------------------------------------
void JimmyChooShopWindowApp::keyPressed(int key){

}

//--------------------------------------------------------------
void JimmyChooShopWindowApp::keyReleased(int key){

}

//--------------------------------------------------------------
void JimmyChooShopWindowApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void JimmyChooShopWindowApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void JimmyChooShopWindowApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void JimmyChooShopWindowApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void JimmyChooShopWindowApp::windowResized(int w, int h)
{
    AppManager::getInstance().getLayoutManager().windowResized(w,h);
}

//--------------------------------------------------------------
void JimmyChooShopWindowApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void JimmyChooShopWindowApp::dragEvent(ofDragInfo dragInfo)
{
}
