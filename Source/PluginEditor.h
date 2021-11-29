/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/CenterComponent.h"
#include "GUI/HeaderComponent.h"
#include "GUI/LeftComponent.h"
#include "GUI/RightComponent.h"
#include "Utils/Colors.h"


//==============================================================================
/**
*/
class FreeAutoWahAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FreeAutoWahAudioProcessorEditor (FreeAutoWahAudioProcessor&);
    ~FreeAutoWahAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    FreeAutoWahAudioProcessor& audioProcessor;

    CenterComponent centerComponent;
    HeaderComponent headerComponent;
    LeftComponent leftComponent;
    RightComponent rightComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreeAutoWahAudioProcessorEditor)
};
