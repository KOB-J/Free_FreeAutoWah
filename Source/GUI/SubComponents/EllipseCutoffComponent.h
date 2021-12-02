/*
  ==============================================================================

    EllipseCutoffComponent.h
    Created: 2 Dec 2021 3:43:21pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../Utils/Colors.h"


class EllipseCutoffComponent : public juce::Component
{
public:
    EllipseCutoffComponent()
    {}

    ~EllipseCutoffComponent()
    {}

    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();
        g.setColour(wahAzur);
        g.fillEllipse(bounds);
        g.setColour(wahLightGrey);
        g.drawEllipse(bounds, 4.0f);
    }
};
