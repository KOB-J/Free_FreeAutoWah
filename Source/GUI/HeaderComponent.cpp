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
}
