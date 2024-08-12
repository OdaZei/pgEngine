#include "include/WindowManager.hpp"

#include "include/Utils.hpp"

#include "include/Grid.hpp"

static const int SCREEN_HEIGHT = 9*64;
static const int SCREEN_WIDTH = 16*64;
static const int BITSPERPIXEL = 2;
static const char* SCREEN_TITLE = "0XD3F0";

WindowManager::WindowManager():  windowWidth(SCREEN_WIDTH)\
, windowHeight(SCREEN_HEIGHT), bitsPerPixel(BITSPERPIXEL) \
, title(SCREEN_TITLE), windowExists(false), window(nullptr)\
, videoMode(nullptr){
	this->videoMode = new sf::VideoMode(this->windowWidth, this->windowHeight, bitsPerPixel);
	
	if(!this->videoMode)	printError(0, "WindowManager");
	else{
		this->window = new sf::RenderWindow(*this->videoMode, this->title);
		if(!this->window)	printError( 0 , "WindowManager" );
		else windowExists = true;
	}

}
WindowManager::~WindowManager( ){ 
	delete window;
	delete videoMode;
}
sf::RenderWindow* WindowManager::getRenderWindow( ) {
	if(!windowExists) printError( 0, "getRenderWindow");
	return this->window;
}
bool WindowManager::windowPoll(sf::Event* e){
	return this->window->pollEvent(*e);
}
void WindowManager::Clear(){
	this->window->clear();
}
void WindowManager::windowDisplay( ){
	this->window->display();
}
void WindowManager::windowClose(){
	if(this->windowExists)
		this->window->close();
	//Null pointer, window does not exist yet
}
bool WindowManager::isOpened(){
	return this->windowExists && this->window->isOpen();
}
void WindowManager::setView(sf::View view) {
	window->setView( view );
}