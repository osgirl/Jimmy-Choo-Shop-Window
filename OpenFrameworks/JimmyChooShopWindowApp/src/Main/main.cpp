#include "ofMain.h"
#include "JimmyChooShopWindowApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new JimmyChooShopWindowApp());

}


/*
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	ofSetupOpenGL(1280, 720, OF_WINDOW);

	HWND hwnd = ofGetWin32Window();
	//HICON hMyIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MAIN_ICON));
	//SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hMyIcon);

	ofRunApp(new JimmyChooShopWindowApp());

}*/
