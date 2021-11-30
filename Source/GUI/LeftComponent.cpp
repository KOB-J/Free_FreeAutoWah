/*
  ==============================================================================

    LeftComponent.cpp
    Created: 29 Nov 2021 3:38:14pm
    Author:  dev

  ==============================================================================
*/

#include "LeftComponent.h"


LeftComponent::LeftComponent()
{
    addAndMakeVisible(lfoFrequencySlider);
    addAndMakeVisible(lfoWidthSlider);

    addAndMakeVisible(lfoFrequencyLabel);
    addAndMakeVisible(lfoWidthLabel);
    addAndMakeVisible(lfoTitleLabel);

    lfoFrequencyLabel.setFont(juce::Font(12.0f, juce::Font::italic));
    lfoFrequencyLabel.setText(lfoFrequency, juce::dontSendNotification);
    lfoWidthLabel.setFont(juce::Font(12.0f, juce::Font::italic));
    lfoWidthLabel.setText(lfoWidth, juce::dontSendNotification);
    lfoTitleLabel.setFont(juce::Font(24.0f, juce::Font::plain));
    lfoTitleLabel.setText(lfoTitle, juce::dontSendNotification);
    lfoTitleLabel.setColour(juce::Label::textColourId, wahOrange);
}

LeftComponent::~LeftComponent()
{
}

void LeftComponent::paint(juce::Graphics& g)
{
    g.setColour(wahLightGrey);
    g.fillRoundedRectangle(0, 0, 100, 240, 10);
}

void LeftComponent::resized()
{
    auto bounds = getLocalBounds();
    auto width = bounds.getWidth();
    auto height = bounds.getHeight();

    lfoFrequencySlider.setBounds(15, 25, 70, 70);
    lfoWidthSlider.setBounds(15, 120, 70, 70);

    lfoFrequencyLabel.setBounds(15, 9, 70, 10);
    lfoWidthLabel.setBounds(15, 104, 70, 10);
    lfoTitleLabel.setBounds(20, 204, 70, 30);

}
