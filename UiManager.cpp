#include "include/UiManager.hpp"
#include "include/TextHolder.hpp"
#include "include/Menu.hpp"
#include "include/filepaths.hpp"

/*
 * 0 - text
 * 1 - menu
 * ...
 */

UiManager::UiManager(): uiCam(nullptr) , elements() {
    elements = std::vector<std::shared_ptr<UiElement*>>();
    TextHolder * tH = new TextHolder("Test...", _DEFAULT_TEXT_SIZE_ , 0, 0);
    elements.clear();
    elements.push_back( std::make_shared<UiElement*>( tH ) );
}
UiManager::UiManager( int xCam, int yCam , int wCam, int hCam ): uiCam(new Camera( xCam, yCam, wCam, hCam )), elements() {
    elements = std::vector<std::shared_ptr<UiElement*>>();
    TextHolder * tH = new TextHolder("Test...", _DEFAULT_TEXT_SIZE_ , 0, 0);
    elements.clear();
    elements.push_back( std::make_shared<UiElement*>( tH ) );
}
UiManager::~UiManager() { };

int UiManager::addTextElement(const char* st, int x, int y) {
    //base text
    TextHolder * tH = new TextHolder( st,_DEFAULT_TEXT_SIZE_, x, y);
    std::shared_ptr<UiElement*> ptr = std::make_shared<UiElement*>( tH );
    elements.push_back( ptr );
    return elements.size() - 1;
}
int UiManager::addMenu( int x, int y ) {
    Menu * menu = new Menu();
    
    char arr[32] =  { "TestString" };
    menu->addData( x, y, arr);
    char arr2[32] = "TestString 2" ;
    menu->addData( x, y + 20, arr2);
    std::shared_ptr<UiElement*> ptr = std::make_shared<UiElement*>( menu );
    elements.push_back( ptr );
    return elements.size() - 1;
}
UiElement* UiManager::popElement( unsigned int index ) {
    UiElement * e = *elements[index];
    elements.erase( elements.begin() + index );
    return e;
}
void UiManager::update(unsigned int index, float dt) {
    UiElement * e = *elements[index];
    e->update(dt);
}
void UiManager::update(unsigned int index, char arr[32]) {
    UiElement * e = *elements[index];
    e->update(1);
}
void UiManager::render(sf::RenderTarget& target, sf::RenderStates states) {
    for( auto& e: elements ){
        UiElement * uiO = *e;
        uiO->drawCurrent(target, states );
    }
}
sf::View UiManager::getCamera( ) {
    //Camera has to exist default contructur for future use;

    return uiCam->getCamera();
}
