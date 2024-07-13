#include "include/EventManager.hpp"

EventManager::EventManager(): event(nullptr) {
	this->event = new sf::Event();
};
bool EventManager::getEventExit( sf::Event::EventType eT){
	return event->type == eT;
}