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

    //addAndMakeVisible(centerComponent);
    addAndMakeVisible(headerComponent);
    //addAndMakeVisible(leftComponent);
    //addAndMakeVisible(rightComponent);

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

}
