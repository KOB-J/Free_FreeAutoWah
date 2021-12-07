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
        , juce::AudioProcessorValueTreeState& apvts);

    void release();

    void getFilterMagnitudeArray(double* frequencies, double* magnitudes);

    size_t getNumSamples() { return numSamples; }

private:
    juce::dsp::IIR::Filter<float> filterRight, filterLeft;
    juce::dsp::IIR::Coefficients<float>::Ptr filterCoefs, filterCoefsForGUI;

    size_t numSamples;
    double sampleRate;

    juce::dsp::ProcessSpec spec;
    juce::Atomic<bool> proceed;

    float baseFrequency, q;
    float lfoFrequency, lfoWidth;
    float envelopeWidth, envelopeAttack, envelopeDecay;
    float lfoPhase;   

    double* envelopes; 
    int numEnvelopes;

    double attackMultiplier, decayMultiplier;

    double inverseSampleRate;
};
