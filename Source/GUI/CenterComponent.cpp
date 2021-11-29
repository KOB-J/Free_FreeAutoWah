/*
  ==============================================================================

    CenterComponent.cpp
    Created: 29 Nov 2021 3:37:57pm
    Author:  dev

  ==============================================================================
*/

#include "CenterComponent.h"

CenterComponent::CenterComponent()
{
}

CenterComponent::~CenterComponent()
{
}

void CenterComponent::paint(juce::Graphics& g)
{
    //g.fillAll(wahDarkGrey);
    //auto bounds = getBounds().toFloat();
    g.setColour(wahLightGrey);
    g.drawRoundedRectangle(0, 0, 380, 240, 10, 1);
    //g.fillRect(0, 0, 380, 240);

}

void CenterComponent::resized()
{
}
