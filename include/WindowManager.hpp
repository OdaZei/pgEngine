#pragma once

#include "SFML/Graphics.hpp"
#include "Object.hpp"
#include "Camera.hpp"

class WindowManager{
	public:
		//empty WM constructor
		WindowManager();
		~WindowManager();
		
		sf::RenderWindow* getRenderWindow();

		bool windowPoll(sf::Event* e);
		void windowDisplay(  );
		void Clear();
		void windowClose();
		bool isOpened();
		void setView(sf::View);
	private:
		int windowWidth;
		int windowHeight;
		int bitsPerPixel;
		
		const char* title;
		
		bool windowExists;
		
		sf::RenderWindow *window;
		sf::VideoMode	 *videoMode;
};
