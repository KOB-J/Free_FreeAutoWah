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


class GraphViewComponent : public juce::Component
{
public:
    GraphViewComponent(FreeAutoWahAudioProcessor& p)
        : audioProcessor(p)
    {
        DBG("GraphViewComponent");
    }

    ~GraphViewComponent()
    {

    }

    void paint(juce::Graphics& g) override
    {
        g.setColour(juce::Colours::white);
        auto bounds = getLocalBounds();
        g.drawText("GraphViewComponent", bounds, juce::Justification::centred);
    }

    void resized() override{}

private:
    FreeAutoWahAudioProcessor& audioProcessor;

};
