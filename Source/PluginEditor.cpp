/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FreeAutoWahAudioProcessorEditor::FreeAutoWahAudioProcessorEditor (FreeAutoWahAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (600, 300);

    addAndMakeVisible(centerComponent);
    addAndMakeVisible(headerComponent);
    addAndMakeVisible(leftComponent);
    addAndMakeVisible(rightComponent);

}

FreeAutoWahAudioProcessorEditor::~FreeAutoWahAudioProcessorEditor()
{
}

//==============================================================================
void FreeAutoWahAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (wahDarkGrey);  
}

void FreeAutoWahAudioProcessorEditor::resized()
{
    auto bounds = getBounds();
    bounds.removeFromLeft(5);
    bounds.removeFromRight(5);
    bounds.removeFromTop(5);

    auto headerBounds = bounds.removeFromTop(40);
    headerComponent.setBounds(headerBounds);

    bounds.removeFromTop(10);

    auto leftBounds = bounds.removeFromLeft(100);
    leftComponent.setBounds(leftBounds);

    auto rightBounds = bounds.removeFromRight(100);
    rightComponent.setBounds(rightBounds);

    bounds.removeFromLeft(5);

    auto centerBounds = bounds.removeFromLeft(380);
    centerComponent.setBounds(centerBounds);
}
