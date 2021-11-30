/*
  ==============================================================================

    RightComponent.cpp
    Created: 29 Nov 2021 3:38:27pm
    Author:  dev

  ==============================================================================
*/

#include "RightComponent.h"

RightComponent::RightComponent()
{
    addAndMakeVisible(envelopeWidthSlider);
    addAndMakeVisible(envelopeAttackSlider);
    addAndMakeVisible(envelopeDecaySlider);

    addAndMakeVisible(envelopeWidthLabel);
    addAndMakeVisible(envelopeAttackLabel);
    addAndMakeVisible(envelopeDecayLabel);
    addAndMakeVisible(envelopeTitleLabel);

    envelopeWidthLabel.setFont(juce::Font(12.0f, juce::Font::italic));
    envelopeWidthLabel.setText(envelopeWidth, juce::dontSendNotification);
    envelopeAttackLabel.setFont(juce::Font(12.0f, juce::Font::italic));
    envelopeAttackLabel.setText(envelopeAttack, juce::dontSendNotification);
    envelopeDecayLabel.setFont(juce::Font(12.0f, juce::Font::italic));
    envelopeDecayLabel.setText(envelopeDecay, juce::dontSendNotification);

    envelopeTitleLabel.setFont(juce::Font(22.0f, juce::Font::plain));
    envelopeTitleLabel.setText(envelopeTitle, juce::dontSendNotification);
    envelopeTitleLabel.setColour(juce::Label::textColourId, wahOrange);
}

RightComponent::~RightComponent()
{
}

void RightComponent::paint(juce::Graphics& g)
{
    g.setColour(wahLightGrey);
    g.fillRoundedRectangle(0, 0, 100, 240, 10);
}

void RightComponent::resized()
{
    auto bounds = getLocalBounds();
    auto width = bounds.getWidth();
    auto height = bounds.getHeight();

    envelopeWidthSlider.setBounds(25, 20, 50, 50);
    envelopeAttackSlider.setBounds(25, 90, 50, 50);
    envelopeDecaySlider.setBounds(25, 160, 50, 50);

    envelopeWidthLabel.setBounds(25, 4, 70, 10);
    envelopeAttackLabel.setBounds(25, 74, 70, 10);
    envelopeDecayLabel.setBounds(25, 144, 70, 10);
    envelopeTitleLabel.setBounds(15, 215, 70, 20);

}
