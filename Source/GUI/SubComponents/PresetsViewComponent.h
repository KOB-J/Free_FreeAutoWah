/*
  ==============================================================================

    PresetsViewComponent.h
    Created: 1 Dec 2021 4:47:40pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Source/PluginProcessor.h"
#include "../../Utils/Colors.h"
#include "../../Utils/Strings.h"


class PresetsViewComponent : public juce::Component
{
public:
    PresetsViewComponent(FreeAutoWahAudioProcessor& p)
        : audioProcessor(p)
    {
    }

    ~PresetsViewComponent()
    {
    }

    void paint(juce::Graphics& g) override
    {
        g.setColour(juce::Colours::white);
        auto bounds = getLocalBounds();
        g.drawText("PresetsViewComponent", bounds, juce::Justification::centred);
    }

    void resized() override{}

private:
    FreeAutoWahAudioProcessor& audioProcessor;

};