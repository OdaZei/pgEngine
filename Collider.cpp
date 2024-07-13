#include "include/Collider.hpp"
#include <cstdio>
#include <math.h>
int times   = 0 ;
sf::Vector2f dimDiff   = sf::Vector2f(0,0);

Collider::Collider( ): Transform( v( ), v( )), colliderAxis(sf::VertexArray( sf::Points, 7 )) { 

}
Collider::Collider( v pos, v dim ): Transform(v( pos ), v( dim ))\
    , colliderAxis( sf::VertexArray( sf::Points, 7 ) ){
    v halfDim = v( dim.x , dim.y );
    v A = v(pos.x - halfDim.x, pos.y );
    v B = v(pos.x + halfDim.x , pos.y);
    v C = v(pos.x , pos.y - halfDim.y);
    v D = v(pos.x , pos.y + halfDim.y);
    //v Ix = v(pos.x , pos.y);
    //v Iy = v(pos.x , pos.y );

    
    colliderAxis[0] = v( pos.x, pos.y);
    colliderAxis[1] = A;
    colliderAxis[2] = B;
    colliderAxis[3] = C;
    colliderAxis[4] = D;
    colliderAxis[5].position = v();
    colliderAxis[6].position = v();

}
Collider::~Collider( ) {
    //
}
float Det(float a, float b, float c, float d){
	return a*d - b*c;
}
void Collider::SetVertexAxis( sf::Vector2f pos, sf::Vector2f dim ) {
    v halfDim = v( dim.x , dim.y  );
    colliderAxis[0].position = v( pos.x, pos.y);
    colliderAxis[0].color = sf::Color::White;
    colliderAxis[1].position = v(pos.x - halfDim.x, pos.y );
    colliderAxis[1].color = sf::Color::Green;//Left
    colliderAxis[2].position = v(pos.x + halfDim.x , pos.y);colliderAxis[2].color = sf::Color::Blue;//Right
    colliderAxis[3].position = v(pos.x , pos.y - halfDim.y);colliderAxis[3].color = sf::Color::Red;//Top
    colliderAxis[4].position = v(pos.x , pos.y + halfDim.y);colliderAxis[4].color = sf::Color::White;//Down
    colliderAxis[5].color = sf::Color::Yellow;
    colliderAxis[6].color = sf::Color::Cyan;
}

bool Collider::IntersectionBetweenLines( v A_p1, v A_p2, v B_p1, v B_p2 , float& ixOut, float& iyOut ) {

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

    v pos = get_position();
    v dim = get_dimension();

    v pOther = other.get_position();
    v dOther = other.get_dimension();
    
    v halfDim = v( dim.x , dim.y );
    
    
    
    v A = v(pos.x - halfDim.x, pos.y );
    v B = v(pos.x + halfDim.x , pos.y);
    v C = v(pos.x , pos.y - halfDim.y);
    v D = v(pos.x , pos.y + halfDim.y);
    //printf( "Line section: C:x[ %f ], y:[ %f ], D:x[ %f ], y:[ %f ]\n[", C.x , C.y, D.x, D.y );
    dimDiff = v(halfDim.x, halfDim.y);
    halfDim = v(dOther.x , dOther.y );
     // test pos 0 , 0
    v O = v(pOther.x - halfDim.x, pOther.y); // 
    v P = v(pOther.x + halfDim.x, pOther.y);
    v Q = v(pOther.x , pOther.y - halfDim.y);
    v R = v(pOther.x , pOther.y + halfDim.y);
    dimDiff = v(dim.x + dimDiff.x, dim.y + dimDiff.y);
    
    //printf("%f, %f\n", pOther.x, pOther.y);

    //printf( "Line section: Q:x[ %f ], y:[ %f ], Ry:x[ %f ], y:[ %f ]\n[", Q.x , Q.y, R.x, R.y );
    //printf( "Line section: O:x[ %f ], y:[ %f ], Py:x[ %f ], y:[ %f ]\n[", O.x , O.y, P.x, P.y );

    //X=
    float e , r = 0;
    bool t1 , t2 = false;
    if( (IntersectionBetweenLines( C , D , O, P , e ,r ))){
        if( ( e > O.x && e < P.x ) ){
            colliderAxis[5].position = v(e,r);
            t1 = true;
        }
    }
    e , r = 0;
    if(IntersectionBetweenLines( A , B , Q , R , e ,r )){
        if(  (r > Q.y && r < R.y) ){
            colliderAxis[6].position = v(e, r );
            t2 = true;
        }
    }
    if(t1 && t2 )   return true;
    

    return false;
}
