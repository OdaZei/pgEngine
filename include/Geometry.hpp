#pragma once

#include <math.h>
#include <SFML/System/Vector2.hpp>


//Point -> ( x , y ) , operators +, - , == , += -=, != 
class point{
	public:
		point(): x(0.f), y(0.f) {};
		point(int a, int b): x(static_cast< float_t >(a)), y(static_cast< float_t >(b)){};
		point(float a, float b): x(a), y(b) {};
		point(point* p): x(p->x), y(p->y){};
		~point(){};
		
		point operator+(const point& p){
			y = x + p.x;
			y = y + p.y;
			return *this;
		};
		point operator-(const point& p){
			x = x - p.x;
			y = y - p.y;
			return *this; 
		};
		point& operator=(const point& p){
			x = p.x;
			y = p.y;
			return *this;
		};
		bool operator==(const point& p){
			if( y == p.y && x == p.x)	return true;
			return false;
		};
		sf::Vector2<float> point2Vect2f(){
			return sf::Vector2<float>(x, y);
		};
		float_t x;
		float_t y; 
};
