#pragma once
#include <SFML/Window/Event.hpp>
class EventManager{
	public:
		EventManager();
		bool getEventExit( sf::Event::EventType eT);
		sf::Event* event;
};