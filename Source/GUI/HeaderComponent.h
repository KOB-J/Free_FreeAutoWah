/*
  ==============================================================================

    HeaderComponent.h
    Created: 29 Nov 2021 3:37:12pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/Colors.h"
#include "../Utils/Strings.h"


class HeaderComponent : public juce::Component
{
public:
    HeaderComponent();
    ~HeaderComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::Label headerTitleLabel;
    juce::TextButton presetButton, undoButton, redoButton, infosButton;
};