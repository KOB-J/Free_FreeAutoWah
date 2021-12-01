/*
  ==============================================================================

    InfosViewComponent.h
    Created: 1 Dec 2021 4:46:33pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Source/PluginProcessor.h"
#include "../../Utils/Colors.h"
#include "../../Utils/Strings.h"


class InfosViewComponent : public juce::Component
{
public:
    InfosViewComponent()
    {
        DBG("InfosViewComponent");

    }

    ~InfosViewComponent()
    {

    }

    void paint(juce::Graphics& g) override
    {
        g.setColour(juce::Colours::white);
        auto bounds = getLocalBounds();
        g.drawText("InfosViewComponent", bounds, juce::Justification::centred);
    }

    void resized() override {}

private:

};