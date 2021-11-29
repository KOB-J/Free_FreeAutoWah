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
    baseFrequency_ = 350.0f;
    q_ = 5.0f;
    lfoFrequency_ = 1.1f;
    lfoWidth_ = 1200.0f;
    envelopeWidth_ = 0.0f;
    envelopeAttack_ = 0.005f;
    envelopeDecay_ = 0.025f;

    envelopes_ = 0;
    numEnvelopes_ = 0;
    attackMultiplier_ = 1.0;
    decayMultiplier_ = 0.0;

    inverseSampleRate_ = 1.0 / 44100.0;

    lfoPhase_ = 0.0f;
}

AutoWah::~AutoWah()
{
    delete(envelopes_);
}

void AutoWah::prepare(double sampleRate, int samplesPerBlock)
{
    filterCoefs = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 500.0f, 1.0f);

    filterRight.coefficients = filterCoefs;
    filterLeft.coefficients = filterCoefs;

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 1;

    filterRight.prepare(spec);
    filterLeft.prepare(spec);

    numSamples = samplesPerBlock;
    this->sampleRate = sampleRate;

    inverseSampleRate_ = 1.0 / sampleRate;
    if (envelopeDecay_ == 0.0)
        decayMultiplier_ = 0.0;
    else
        decayMultiplier_ = pow(1.0 / M_E, inverseSampleRate_ / envelopeDecay_);
    if (envelopeAttack_ == 0.0)
        attackMultiplier_ = 0.0;
    else
        attackMultiplier_ = pow(1.0 / M_E, inverseSampleRate_ / envelopeAttack_);
}

void AutoWah::process(juce::AudioBuffer<float>& buffer, float baseFrequency, float q, float lfoFrequency, float lfoWidth, float envelopeWidth, float envelopeAttack, float envelopeDecay)
{
    baseFrequency_ = baseFrequency;
    q_ = q;
    lfoFrequency_ = lfoFrequency;
    lfoWidth_ = lfoWidth;
    envelopeWidth_ = envelopeWidth;
    envelopeAttack_ = envelopeAttack;
    envelopeDecay_ = envelopeDecay;

    const int numInputChannels = buffer.getNumChannels();
    int channel;
    float ph;

     for (channel = 0; channel < numInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        ph = lfoPhase_;

        for (int sample = 0; sample < numSamples; ++sample)
        {
            const float in = channelData[sample];
            float centreFrequency = baseFrequency_;

            if (channel < numEnvelopes_) {   
                if (fabs(in) > envelopes_[channel]) {
                    envelopes_[channel] += (1.0 - attackMultiplier_) * (fabs(in) - (double)envelopes_[channel]);
                }
                else
                    envelopes_[channel] *= decayMultiplier_;
            }

            if (lfoWidth_ > 0.0) {
                centreFrequency += lfoWidth_ * (0.5f + 0.5f * sinf(2.0 * M_PI * ph));
            }
            if (envelopeWidth_ > 0.0 && channel < numEnvelopes_) {
                centreFrequency += envelopeWidth_ * envelopes_[channel];
            }

       /*     if (!proceed.get())
            {*/
                filterCoefs = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, centreFrequency, q);
                proceed = true;
            //}

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

            ph += lfoFrequency_ * inverseSampleRate_;
            if (ph >= 1.0)
                ph -= 1.0;
        }
    }

    lfoPhase_ = ph;
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
        filterCoefs->getMagnitudeForFrequencyArray(frequencies, magnitudes, numSamples, sampleRate);
        proceed = false;
    }
}
