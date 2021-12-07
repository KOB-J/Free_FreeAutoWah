/*
  ==============================================================================

    CenterComponent.cpp
    Created: 29 Nov 2021 3:37:57pm
    Author:  dev

  ==============================================================================
*/

#include "CenterComponent.h"


CenterComponent::CenterComponent(FreeAutoWahAudioProcessor& p)
    : audioProcessor(p)
    , graphViewComponent(p)
    , presetsViewComponent(p)
{
    addAndMakeVisible(graphViewComponent);
    actualView = 1;
}

CenterComponent::~CenterComponent()
{
}

void CenterComponent::paint(juce::Graphics& g)
{
    g.setColour(wahLightGrey);
    g.drawRoundedRectangle(0, 0, 380, 240, 10, 1);
}

void CenterComponent::resized()
{
    graphViewComponent.setBounds(0, 0, getWidth(), getHeight());
    presetsViewComponent.setBounds(0, 0, getWidth(), getHeight());
    infosViewComponent.setBounds(0, 0, getWidth(), getHeight());
}

void CenterComponent::showGraphView()
{
}

void CenterComponent::pressetButtonClicked()
{
    DBG("pressetButtonClicked , actualView= "<<actualView);
    switch (actualView)
    {
    case 1:
        removeChildComponent(&graphViewComponent);
        addAndMakeVisible(presetsViewComponent);
        actualView = 2;
        break;

    case 2:
        removeChildComponent(&presetsViewComponent);
        addAndMakeVisible(graphViewComponent);
        actualView = 1;
        break;

    case 3:
        removeChildComponent(&infosViewComponent);
        addAndMakeVisible(presetsViewComponent);
        actualView = 2;
        break;

    default:
        break;
    }
}

void CenterComponent::infosButtonClicked()
{
    DBG("infosButtonClicked , actualView= " << actualView);
    switch (actualView)
    {
    case 1:
        removeChildComponent(&graphViewComponent);
        addAndMakeVisible(infosViewComponent);
        actualView = 3;
        break;

    case 2:
        removeChildComponent(&presetsViewComponent);
        addAndMakeVisible(infosViewComponent);
        actualView = 3;
        break;

    case 3:
        removeChildComponent(&infosViewComponent);
        addAndMakeVisible(graphViewComponent);
        actualView = 1;
        break;

    default:
        break;
    }
}
