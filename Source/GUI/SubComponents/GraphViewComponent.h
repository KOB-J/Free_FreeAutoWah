/*
  ==============================================================================

    GraphViewComponent.h
    Created: 1 Dec 2021 4:47:23pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Source/PluginProcessor.h"
#include "../../Utils/Colors.h"
#include "../../Utils/Strings.h"
#include "EllipseCutoffComponent.h"


class GraphViewComponent 
    : public juce::Component
    , public juce::Timer
    , public juce::MouseListener
{
public:
    GraphViewComponent(FreeAutoWahAudioProcessor& p);
    ~GraphViewComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void timerCallback() override;

    void mouseDrag(const juce::MouseEvent& event) { moveButton(); }
    void mouseDown(const juce::MouseEvent& event) { moveButton(); }

private:
    FreeAutoWahAudioProcessor& audioProcessor;

    int numSamples;
    double* frequencies;
    double* magnitudes;
    EllipseCutoffComponent button;

    int buttonX, buttonY;
    juce::Label graphLabel;

    void moveButton();

    juce::String getGraphViewLabelText();
};
