#pragma once

static const int chunkDim = 256; 
static const float hrs    = 0.6; 
class DiamondGenerator{
    public:
        DiamondGenerator();
        float getFixedStepValue( int, int, int, float offs[4][2]);
        void step_diamond_square(int, float);
        float getChunkValue(int i, int j);
    private:
        float chunk[chunkDim][chunkDim];
};