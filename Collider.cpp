#include "include/Collider.hpp"
#include <cstdio>
#include <math.h>
int times   = 0 ;
sf::Vector2f dimDiff   = sf::Vector2f(0,0);

Collider::Collider( ): colliderAxis(sf::VertexArray( sf::Points, 7 )) { 

}
Collider::Collider( sf::Vector2f pos, sf::Vector2f dim ): colliderAxis( sf::VertexArray( sf::Points, 7 ) ){
    sf::Vector2f halfDim = sf::Vector2f( dim.x/2 , dim.y/2 );
    sf::Vector2f A = sf::Vector2f(pos.x - halfDim.x, pos.y );
    sf::Vector2f B = sf::Vector2f(pos.x + halfDim.x , pos.y);
    sf::Vector2f C = sf::Vector2f(pos.x , pos.y - halfDim.y);
    sf::Vector2f D = sf::Vector2f(pos.x , pos.y + halfDim.y);
    //v Ix = v(pos.x , pos.y);
    //v Iy = v(pos.x , pos.y );

    
    colliderAxis[0] = sf::Vector2f( pos.x, pos.y);
    colliderAxis[1] = A;
    colliderAxis[2] = B;
    colliderAxis[3] = C;
    colliderAxis[4] = D;
    colliderAxis[5].position = sf::Vector2f();
    colliderAxis[6].position = sf::Vector2f();

}
Collider::~Collider( ) {
    //
}
float Det(float a, float b, float c, float d){
	return a*d - b*c;
}
void Collider::SetVertexAxis( sf::Vector2f pos, sf::Vector2f dim ) {
    sf::Vector2f halfDim = sf::Vector2f( dim.x/2 , dim.y/2  );
    colliderAxis[0].position = sf::Vector2f( pos.x, pos.y);colliderAxis[0].color = sf::Color::White;
    colliderAxis[1].position = sf::Vector2f(pos.x - halfDim.x, pos.y );colliderAxis[1].color = sf::Color::Green;//Left
    colliderAxis[2].position = sf::Vector2f(pos.x + halfDim.x , pos.y);colliderAxis[2].color = sf::Color::Blue;//Right
    colliderAxis[3].position = sf::Vector2f(pos.x , pos.y - halfDim.y);colliderAxis[3].color = sf::Color::Red;//Top
    colliderAxis[4].position = sf::Vector2f(pos.x , pos.y + halfDim.y);colliderAxis[4].color = sf::Color::White;//Down
    colliderAxis[5].color = sf::Color::Yellow;
    colliderAxis[6].color = sf::Color::Cyan;
}

bool Collider::IntersectionBetweenLines( sf::Vector2f A_p1, sf::Vector2f A_p2, sf::Vector2f B_p1, sf::Vector2f B_p2 , float& ixOut, float& iyOut ) {

    float detL1 = Det(A_p1.x, A_p1.y, A_p2.x, A_p2.y);
	float detL2 = Det(B_p1.x, B_p1.y, B_p2.x, B_p2.y);

	float x1mx2 = A_p1.x - A_p2.x;
	float x3mx4 = B_p1.x - B_p2.x;
	float y1my2 = A_p1.y - A_p2.y;
	float y3my4 = B_p1.y - B_p2.y;

	float denom = Det(x1mx2, y1my2, x3mx4, y3my4);
	if(denom == 0.0)
		return false;

	float xnom = Det(detL1, x1mx2, detL2, x3mx4);
	float ynom = Det(detL1, y1my2, detL2, y3my4);

	ixOut = xnom / denom;
	iyOut = ynom / denom;

	if(!isfinite(ixOut) || !isfinite(iyOut)) // Probably a numerical issue
		return false;

    return true; //All OK
}

bool Collider::CheckCollision(Collider& other) {

    sf::Vector2f pos = colliderAxis[0].position;
    sf::Vector2f dim = sf::Vector2f(colliderAxis[2].position.x - colliderAxis[0].position.x, colliderAxis[4].position.y - colliderAxis[0].position.y);

    sf::Vector2f pOther = other.colliderAxis[0].position;
    sf::Vector2f dOther = sf::Vector2f(other.colliderAxis[2].position.x - other.colliderAxis[0].position.x, other.colliderAxis[4].position.y - other.colliderAxis[0].position.y);
    
    sf::Vector2f halfDim = sf::Vector2f( dim.x/2 , dim.y/2 );
    
    
    
    sf::Vector2f A = sf::Vector2f(pos.x - halfDim.x, pos.y );
    sf::Vector2f B = sf::Vector2f(pos.x + halfDim.x , pos.y);
    sf::Vector2f C = sf::Vector2f(pos.x , pos.y - halfDim.y);
    sf::Vector2f D = sf::Vector2f(pos.x , pos.y + halfDim.y);
    printf( "Line section: C:x[ %f ], y:[ %f ], D:x[ %f ], y:[ %f ]\n[", C.x , C.y, D.x, D.y );
    dimDiff = sf::Vector2f(halfDim.x, halfDim.y);
    halfDim = sf::Vector2f(dOther.x/2, dOther.y/2 );
     // test pos 0 , 0
    sf::Vector2f O = sf::Vector2f(pOther.x - halfDim.x, pOther.y); // 
    sf::Vector2f P = sf::Vector2f(pOther.x + halfDim.x, pOther.y);
    sf::Vector2f Q = sf::Vector2f(pOther.x , pOther.y - halfDim.y);
    sf::Vector2f R = sf::Vector2f(pOther.x , pOther.y + halfDim.y);
    dimDiff = sf::Vector2f(dim.x + dimDiff.x, dim.y + dimDiff.y);

    float e , r = 0;
    bool t1 , t2 = false;
    if( (IntersectionBetweenLines( C , D , O, P , e ,r ))){
        if( ( e > O.x && e < P.x  ) ){
            colliderAxis[5].position = sf::Vector2f(e,r);
            t1 = true;
        }
    }
    e , r = 0;
    if(IntersectionBetweenLines( A , B , Q , R , e ,r )){
        if(  (r > Q.y && r < R.y) ){
            colliderAxis[6].position = sf::Vector2f(e, r );
            t2 = true;
        }
    }
    if(t1 && t2 )   return true;
    

    return false;
}
