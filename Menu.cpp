#include "include/Menu.hpp"
#include "include/TextHolder.hpp"
#include <cstring>
menudata::menudata( int index, int x, int y , char arr[32]): ind(index), xPos(x), yPos(y) {
    memcpy(data,arr, 32);
}
menudata::~menudata( ) {

}

Menu::Menu( ){
    mData = std::vector<menudata*>( 0, nullptr);
}
Menu::~Menu( ) { }
void Menu::addData( int x, int y, char arr[32] ) {
    menudata * md = new menudata( mData.size(), x, y , arr );
    mData.push_back(md);
    TextHolder * th = new TextHolder( arr, 24, x, y );
    mElm.push_back(std::make_shared<TextHolder*>(th));
}
void Menu::overrideData( int index, char d[32] ) {
    memcpy(mData[index]->data, d, 32);
}
// update with float data;
void Menu::update( float dt ) const{
    TextHolder * t = *mElm[0];
    t->update( dt );
}
void Menu::drawCurrent( sf::RenderTarget& target, sf::RenderStates states ) const {
    for( auto& d: mData ) {
        TextHolder * t = *mElm[d->ind];
        t->drawCurrent(target, states);
    }
}