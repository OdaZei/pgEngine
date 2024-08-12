#include "include/Menu.hpp"
#include "include/TextHolder.hpp"
#include <string.h>
menudata::menudata( int index, int x, int y , char arr[32]): ind(index), xPos(x), yPos(y) {
    memcpy(data,arr, 32);
}
menudata::menudata():ind(0), xPos(0), yPos(0) {

}
menudata::~menudata( ) {

}

Menu::Menu( ): UiElement(1, 0, 0){
    mData = std::vector<std::shared_ptr<menudata>>();
    mElm = std::vector<std::shared_ptr<TextHolder>>();
}
Menu::Menu( const UiElement& e): UiElement(e){
} 
Menu::~Menu( ) { }
void Menu::addData( int x, int y, char arr[32] ) {
    menudata md =  menudata( mData.size()-1, x, y , arr );
    mData.push_back(std::make_shared<menudata>(md));
    TextHolder  th =  TextHolder( arr, 12, x, y );
    mElm.push_back(std::make_shared<TextHolder>(th));
}
void Menu::overrideData( int index, char d[32] ) {
    menudata MD = *(mData[dataFSize()-1]);
    strcpy(MD.data, d);
    TextHolder th = *mElm[dataFSize()-1];
    th.updateC(d);    
}
// update with float data;
void Menu::update( float dt ) const{
    for( auto& me: mElm ) {
        TextHolder t = *me;
        t.update( dt );
    }
}
void Menu::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const {
    for( auto& me: mElm ) {
        TextHolder t = *me;
        std::string s = t.getText();
        t.drawCurrent(target, states);
    }
}
int Menu::dataFSize(){
    return mData.size();
}