/*
  ==============================================================================

    CenterComponent.h
    Created: 29 Nov 2021 3:37:57pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Source/PluginProcessor.h"
#include "../Utils/Colors.h"
#include "SubComponents/GraphViewComponent.h"
#include "SubComponents/PresetsViewComponent.h"
#include "SubComponents/InfosViewComponent.h"



class CenterComponent : public juce::Component
{
public:
    CenterComponent(FreeAutoWahAudioProcessor& p);
    ~CenterComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void showGraphView();
    void pressetButtonClicked();
    void infosButtonClicked();

private:
    FreeAutoWahAudioProcessor& audioProcessor;

    GraphViewComponent graphViewComponent; 
    PresetsViewComponent presetsViewComponent;
    InfosViewComponent infosViewComponent;
    int actualView;
};
