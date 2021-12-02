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
        infosLabel.setText(infosViewText, juce::dontSendNotification);
        infosLabel.setColour(juce::Label::textColourId, wahOrange);
        addAndMakeVisible(infosLabel);
    }

    ~InfosViewComponent()
    {
    }

    void paint(juce::Graphics& g) override
    {
    }

    void resized() override 
    {
        infosLabel.setBounds(20, 10, 300, 200);
    }

private:
    juce::Label infosLabel;
};