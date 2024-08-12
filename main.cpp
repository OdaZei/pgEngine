#include "include/StartServicesState.hpp"

#include "include/EventManager.hpp"

int main(int argc, char **argv){
	StartServicesState* ssState_ = new StartServicesState(); 
	sf::Clock Clock;
	while( ssState_->isWindowOpen() ) {
		ssState_->handleEvents();
		sf::Time ElapsedTime = Clock.getElapsedTime();
		Clock.restart();
		ssState_->update(ElapsedTime.asSeconds());
		ssState_->render();
	}
	return 0;
}