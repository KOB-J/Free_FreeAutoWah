/*
  ==============================================================================

    AutoWah.cpp
    Created: 29 Nov 2021 10:14:45am
    Author:  dev

  ==============================================================================
*/

#include "AutoWah.h"

AutoWah::AutoWah()
{
    baseFrequency = 350.0f;
    q = 5.0f;
    lfoFrequency = 1.1f;
    lfoWidth = 1200.0f;
    envelopeWidth = 0.0f;
    envelopeAttack = 0.005f;
    envelopeDecay = 0.025f;

    envelopes = 0;
    numEnvelopes = 0;
    attackMultiplier = 1.0;
    decayMultiplier = 0.0;

    inverseSampleRate = 1.0 / 44100.0;

    lfoPhase = 0.0f;

    numSamples = 0;
    sampleRate = 44100.0;
}

AutoWah::~AutoWah()
{
    delete(envelopes);
}

void AutoWah::prepare(double sampleRate, int samplesPerBlock)
{
    filterCoefs = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 500.0f, 1.0f);
    filterCoefsForGUI = filterCoefs;

    filterRight.coefficients = filterCoefs;
    filterLeft.coefficients = filterCoefs;

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 1;

    filterRight.prepare(spec);
    filterLeft.prepare(spec);

    numSamples = samplesPerBlock;
    this->sampleRate = sampleRate;

    inverseSampleRate = 1.0 / sampleRate;
    if (envelopeDecay == 0.0)
        decayMultiplier = 0.0;
    else
        decayMultiplier = pow(1.0 / M_E, inverseSampleRate / envelopeDecay);
    if (envelopeAttack == 0.0)
        attackMultiplier = 0.0;
    else
        attackMultiplier = pow(1.0 / M_E, inverseSampleRate / envelopeAttack);
}

void AutoWah::process(juce::AudioBuffer<float>& buffer, juce::AudioProcessorValueTreeState& apvts)
{
    jassert(numSamples != 0);
    
    baseFrequency = apvts.getRawParameterValue("baseFrequency")->load();
    q = apvts.getRawParameterValue("q")->load();
    lfoFrequency = apvts.getRawParameterValue("lfoFrequency")->load();
    lfoWidth = apvts.getRawParameterValue("lfoWidth")->load();
    envelopeWidth = apvts.getRawParameterValue("envelopeWidth")->load();
    envelopeAttack = apvts.getRawParameterValue("envelopeAttack")->load();
    envelopeDecay = apvts.getRawParameterValue("envelopeDecay")->load();

    const int numInputChannels = buffer.getNumChannels();
    int channel;
    float phase;

     for (channel = 0; channel < numInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        phase = lfoPhase;

        for (int sample = 0; sample < numSamples; ++sample)
        {
            const float in = channelData[sample];
            float centreFrequency = baseFrequency;

            if (channel < numEnvelopes) {   
                if (fabs(in) > envelopes[channel]) {
                    envelopes[channel] += (1.0 - attackMultiplier) * (fabs(in) - (double)envelopes[channel]);
                }
                else
                    envelopes[channel] *= decayMultiplier;
            }

            if (lfoWidth > 0.0) {
                centreFrequency += lfoWidth * (0.5f + 0.5f * sinf(2.0 * M_PI * phase));
            }

            if (envelopeWidth > 0.0 && channel < numEnvelopes) {
                centreFrequency += envelopeWidth * envelopes[channel];
            }

            filterCoefs = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, centreFrequency, q);

            if (!proceed.get())
            {
                filterCoefsForGUI = filterCoefs;
                proceed = true;
            }

            switch (channel)
            {
                case 0:
                    filterLeft.coefficients = filterCoefs;
                    channelData[sample] = filterLeft.processSample(in);
                    break;

                case 1:
                    filterRight.coefficients = filterCoefs;
                    channelData[sample] = filterRight.processSample(in);
                    break;

                default:
                    break;
            }

            phase += lfoFrequency * inverseSampleRate;
            if (phase >= 1.0)
                phase -= 1.0;
        }
    }

    lfoPhase = phase;
}

void AutoWah::release()
{
    filterRight.reset();
    filterLeft.reset();
}

void AutoWah::getFilterMagnitudeArray(double* frequencies, double* magnitudes)
{
    if (proceed.get())
    {
        filterCoefsForGUI->getMagnitudeForFrequencyArray(frequencies, magnitudes, numSamples, sampleRate);
        proceed = false;
    }
}
