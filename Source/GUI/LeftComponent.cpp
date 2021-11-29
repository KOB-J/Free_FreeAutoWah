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
}
