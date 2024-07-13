#include "include/DiamondGenerator.hpp"
#include <math.h>
DiamondGenerator::DiamondGenerator( ) {
    for ( int i = 0; i < chunkDim; i++ )
        for ( int j = 0; j < chunkDim; j++)
            chunk[i][j] = rand()%2;
    int h = chunkDim - 1;
    float s = 1.0;
    while( h > 1 ){
        step_diamond_square( h, s );
        h /= 2;
        s *= hrs;
    }
}
float DiamondGenerator::getFixedStepValue( int xC, int yC, int stepD, float offs[4][2]) {
    float r, k = 0.f;
    for( int i = 0 ; i < 4; i++ ){
        int p = xC + offs[i][0] * stepD;
        int q = yC + offs[i][1] * stepD;
        if( (p >= 0 && p < chunkDim) && (q >= 0 && q < chunkDim ) ){
            r += chunk[p][q];
            k += 1.0;
        }
    }
    return r/k;

}
void DiamondGenerator::step_diamond_square( int h, float s ) {
    int v = static_cast<int>(h / 2);
    
    //offs
    float D[4][2] = { {-1,-1},{-1,1}, {1,1}, {1,-1} };
    float S[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };

    for( int i = v; i < chunkDim; i+=h ){
        for( int j = v; j < chunkDim; j+=h ){
            chunk[i][j] = getFixedStepValue(i, j, v, D);
        }
    }
    for( int i = v; i < chunkDim; i+=h ){
        for( int j = 0; j < chunkDim; j+=h )
            chunk[i][j] = getFixedStepValue(i, j, v,S);
    }
    for( int i = 0; i < chunkDim; i+=h ){
        for( int j = v; j < chunkDim; j+=h )
            chunk[i][j] = getFixedStepValue(i, j, v,S);
    }   
}
float DiamondGenerator::getChunkValue( int i, int j) {
    return chunk[i][j];
}