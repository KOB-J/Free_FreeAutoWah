/*
  ==============================================================================

    AutoWah.h
    Created: 29 Nov 2021 10:14:45am
    Author:  dev

  ==============================================================================
*/

#pragma once

#define _USE_MATH_DEFINES
#include <JuceHeader.h>

class AutoWah
{
public:
    AutoWah();
    ~AutoWah();

    void prepare(double sampleRate, int samplesPerBlock);

    void process(juce::AudioBuffer<float>& buffer
        , float baseFrequency
        , float q
        , float lfoFrequency
        , float lfoWidth
        , float envelopeWidth
        , float envelopeAttack
        , float envelopeDecay);

    void release();

    void getFilterMagnitudeArray(double* frequencies, double* magnitudes);

    size_t getNumSamples() { return numSamples; }

private:

    juce::dsp::IIR::Filter<float> filterRight, filterLeft;
    juce::dsp::IIR::Coefficients<float>::Ptr filterCoefs;

    size_t numSamples;
    double sampleRate;

    juce::dsp::ProcessSpec spec;
    juce::Atomic<bool> proceed;

    /*********/

    float baseFrequency_, q_;
    float lfoFrequency_, lfoWidth_;
    float envelopeWidth_, envelopeAttack_, envelopeDecay_;
    float lfoPhase_;   

    double* envelopes_; 
    int numEnvelopes_;

    double attackMultiplier_, decayMultiplier_;

    double inverseSampleRate_;

};
