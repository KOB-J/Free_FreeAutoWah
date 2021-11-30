/*
  ==============================================================================

    HeaderComponent.cpp
    Created: 29 Nov 2021 3:37:12pm
    Author:  dev

  ==============================================================================
*/

#include "HeaderComponent.h"

HeaderComponent::HeaderComponent()
{
    addAndMakeVisible(headerTitleLabel);
    headerTitleLabel.setText(headerTitle, juce::dontSendNotification);
    headerTitleLabel.setFont(juce::Font(36.0, juce::Font::bold));
    headerTitleLabel.setColour(juce::Label::textColourId, wahOrange);

    addAndMakeVisible(presetButton);
    presetButton.setButtonText(headerPreset);
    presetButton.setColour(juce::TextButton::buttonColourId, wahBlack);
    presetButton.setColour(juce::TextButton::textColourOffId, wahAzur);

    addAndMakeVisible(undoButton);
    undoButton.setButtonText(headerUndo);
    undoButton.setColour(juce::TextButton::buttonColourId, wahAzur);
    undoButton.setColour(juce::TextButton::textColourOffId, wahBlack);

    addAndMakeVisible(redoButton);
    redoButton.setButtonText(headerRedo);
    redoButton.setColour(juce::TextButton::buttonColourId, wahAzur);
    redoButton.setColour(juce::TextButton::textColourOffId, wahBlack);

    addAndMakeVisible(infosButton);
    infosButton.setButtonText(headerInfos);
    infosButton.setColour(juce::TextButton::buttonColourId, wahOrange);
    infosButton.setColour(juce::TextButton::textColourOffId, wahBlack);
}

HeaderComponent::~HeaderComponent()
{
}

void HeaderComponent::paint(juce::Graphics& g)
{
    g.setColour(wahLightGrey);
    g.fillRoundedRectangle(0, 0, 590, 40, 10);
}

void HeaderComponent::resized()
{
    headerTitleLabel.setBounds(17, 5, 140, 25);
    presetButton.setBounds(200, 5, 160, 30);
    undoButton.setBounds(400, 5, 65, 22);
    redoButton.setBounds(465, 5, 65, 22);
    infosButton.setBounds(550, 5, 28, 28);

}
