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
}
