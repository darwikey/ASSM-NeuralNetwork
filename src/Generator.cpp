#include "Generator.h"

static const float pi = 3.14159265358f;
static const float twoPi = 6.28318530717f;

Generator::Generator()
{
    for (int i = 0; i < GENERATOR_SIZE; i++)
    {
        GeneratorEntity g;
        // frequence et phase au hasard
        g.freq = (float) (i + 1) * random(10.f, 20.f);
        g.phase = random(0.f, twoPi);

        // choisi une fonction au hasard
        switch (random(0, 6))
        {
        default:
        case 0:
            g.function = &Generator::generator0;
            break;

        case 1:
            g.function = &Generator::generator1;
            break;

        case 2:
            g.function = &Generator::generator2;
            break;

        case 3:
            g.function = &Generator::generator3;
            break;

        case 4:
            g.function = &Generator::generator4;
            break;
        }

        mGenerators.push_back(g);
    }
}


void Generator::run(const std::vector<float>& fParams, std::vector<kiss_fft_cpx>& fOut, float fSampleFreq)
{
   
    for (unsigned int s = 0; s < fOut.size(); s++)
    {
        fOut[s].r = 0.f;
        fOut[s].i = 0.f;
        // évalue chaque generateur
        for (unsigned int g = 0; g < fParams.size(); g++)
        {
            fOut[s].r += fParams[g] * mGenerators[g].function(mGenerators[g].phase + twoPi * mGenerators[g].freq * s / fSampleFreq);
        }
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


// sinus
float Generator::generator0(float fValue)
{
    return sin(fValue);
}

// sinus cubique
float Generator::generator1(float fValue)
{
    float a = sin(fValue);
    return a * a * a;
}

// dent de scie
float Generator::generator2(float fValue)
{
    return fmod(fValue, twoPi) / pi - 1.0f;
}


//triangle
float Generator::generator3(float fValue)
{
    return abs(fmod(fValue, twoPi) / (pi / 2.f) - 2.0f) - 1.f;
}

// sinus écrêté
float Generator::generator4(float fValue)
{
    float a = sin(fValue);
    if (a > 0.9f)
        a = 0.9f;
    if (a < -0.9f)
        a = -0.9f;
    return a;
}