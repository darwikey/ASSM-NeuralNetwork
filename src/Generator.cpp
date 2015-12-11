#include "Generator.h"


Generator::Generator()
{
}


void Generator::run(const std::vector<float>& fParams, std::vector<float>& fOut, float fSampleFreq)
{
    for (unsigned int s = 0; s < fOut.size(); s++)
    {
        fOut[s] = 0.f;
        for (unsigned int g = 0; g < fParams.size(); g++)
        {
            float freq = (float)(g + 1) * 10.f;
            fOut[s] += fParams[g] * sin(2.f * 3.14159f * freq * s / fSampleFreq);
        }

        // normalisation
        fOut[s] /= (float)fParams.size();
    }

}