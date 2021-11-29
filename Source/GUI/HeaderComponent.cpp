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
    g.fillAll(wahLightGrey);
}

void HeaderComponent::resized()
{
}
