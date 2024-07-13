#pragma once
#include <cstddef>  // size_t

class SimplexNoise {
public:
    // 1D Perlin simplex noise
    static float noise(float x);
    // 2D Perlin simplex noise
    static float noise(float x, float y);

    float fractal(size_t octaves, float x) const;
    float fractal(size_t octaves, float x, float y) const;
    explicit SimplexNoise(float frequency,
                          float amplitude,
                          float lacunarity,
                          float persistence) :
        mFrequency(frequency),
        mAmplitude(amplitude),
        mLacunarity(lacunarity),
        mPersistence(persistence) {
    }

private:
    
    float mFrequency;
    float mAmplitude;
    float mLacunarity;
    float mPersistence;
};

