#pragma once

#include "stdafx.h"
#include "_kiss_fft_guts.h"

class Generator
{
public:
    Generator();

    void run(const std::vector<float>& fParams, std::vector<kiss_fft_cpx>& fOut, float fSampleFreq);

    void normalize(std::vector<kiss_fft_cpx>& fBuffer);

private:

};
