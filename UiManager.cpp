#include "include/UiManager.hpp"
#include "include/TextHolder.hpp"

#include "include/filepaths.hpp"

/*
 * 0 - text
 * 1 - menu
 * ...
 */

UiManager::UiManager(): uiCam(nullptr) , elements() {
    elements = std::vector<std::shared_ptr<TextHolder>>();
    TextHolder  tH =  TextHolder("Test...", _DEFAULT_TEXT_SIZE_ , 0, 0);
    elements.clear();
    elements.push_back( std::make_shared<TextHolder>( tH ) );
}
UiManager::UiManager( int xCam, int yCam , int wCam, int hCam ): uiCam(new Camera( xCam, yCam, wCam, hCam,false,0,0,0,0 )), elements() {
    elements = std::vector<std::shared_ptr<TextHolder>>();
    TextHolder  tH =  TextHolder("Test...", _DEFAULT_TEXT_SIZE_ , 0, 0);
    TextHolder  tH2 =  TextHolder("Test...", _DEFAULT_TEXT_SIZE_ , 100, 0);
    elements.clear();
    elements.push_back( std::make_shared<TextHolder>( tH ) );
    elements.push_back( std::make_shared<TextHolder>( tH2 ) );
}
UiManager::~UiManager() { };

int UiManager::addTextElement(const char* st, int x, int y) {
    //base text
    TextHolder  tH =  TextHolder( st,_DEFAULT_TEXT_SIZE_, x, y);
    std::shared_ptr<TextHolder> ptr = std::make_shared<TextHolder>( tH );
    elements.push_back( ptr );
    return elements.size() - 1;
}
int UiManager::addMenu( int x, int y, char arr[32] ) {
    Menu m = Menu();
    m.addData( x, y , arr );
    m.addData( x, y + 20 , arr );
    menu = std::make_shared<Menu>( m );
    return 0;
}
int UiManager::addMenu( std::shared_ptr<Menu> m ){
    menu = m; 
    return elements.size() - 1;
}
UiElement UiManager::popElement( unsigned int index ) {
    TextHolder e = *elements[index];
    elements.erase( elements.begin() + index );
    return e;
}
void UiManager::updateF(unsigned int index, float dt) {
    if(index < elements.size() ){
        std::string s = elements[index]->getText();
        (elements[index])->update(dt);
    }
}
//Updates menu index with 32 chars long string;
void UiManager::updateC(unsigned int index, char arr[32]) {
    (*menu).overrideData(index, arr );
}
void UiManager::updateTC(unsigned int index, char arr[32]){
    if(index < elements.size() ){
        (elements[index])->setText(arr, 12);
    }
}
void UiManager::render(sf::RenderTarget& target, sf::RenderStates states) {
    int o = 0;
    for( auto& e: elements ){
        TextHolder uiO = *e;
        uiO.drawCurrent(target, states );
        o++;
    }
    (*menu).drawCurrent(target, states );
}
sf::View UiManager::getCamera( ) {
    //Camera has to exist default contructor for future use;

    return uiCam->getCamera();
}
