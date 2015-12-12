#include "Generator.h"


Generator::Generator()
{
}


void Generator::run(const std::vector<float>& fParams, std::vector<kiss_fft_cpx>& fOut, float fSampleFreq)
{
    const float twoPi = 6.28318530717;
    for (unsigned int s = 0; s < fOut.size(); s++)
    {
        fOut[s].r = 0.f;
        fOut[s].i = 0.f;
        for (unsigned int g = 0; g < fParams.size(); g++)
        {
            float freq = (float) (g + 1) * (fmod(g * 3133.5463f, 10.f) + 10.f);
            // phase aléatoire
            float phase = fmod(g * 31337.85307f, twoPi);
            fOut[s].r += fParams[g] * sin(phase + twoPi * freq * s / fSampleFreq);
        }

        
        fOut[s].r /= (float)fParams.size();
    }

    // normalisation
    normalize(fOut);
}


// normalise le son entre [-1, 1]
void Generator::normalize(std::vector<kiss_fft_cpx>& fBuffer)
{
    float _max = 0.f;
    for (unsigned int s = 0; s < fBuffer.size(); s++)
    {
        if (fabs(fBuffer[s].r) > _max)
        {
            _max = fabs(fBuffer[s].r);
        }
    }

    if (_max > 1e-6f)
    {
        for (unsigned int s = 0; s < fBuffer.size(); s++)
        {
            fBuffer[s].r /= _max;
        }
    }
}