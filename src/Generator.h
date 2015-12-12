#pragma once

#include "stdafx.h"
#include "_kiss_fft_guts.h"

struct GeneratorEntity
{
    float freq = 0.f;
    float phase = 0.f;
    float(*function)(float) = nullptr;
};

class Generator
{
public:
    Generator();

    void run(const std::vector<float>& fParams, std::vector<kiss_fft_cpx>& fOut, float fSampleFreq);

    void normalize(std::vector<kiss_fft_cpx>& fBuffer);

private:
    static float generator0(float fValue);
    static float generator1(float fValue);
    static float generator2(float fValue);
    static float generator3(float fValue);
    static float generator4(float fValue);

    std::vector<GeneratorEntity> mGenerators;
};
