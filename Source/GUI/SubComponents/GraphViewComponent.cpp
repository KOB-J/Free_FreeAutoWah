/*
  ==============================================================================

    GraphViewComponent.cpp
    Created: 2 Dec 2021 3:33:22pm
    Author:  dev

  ==============================================================================
*/

#include "GraphViewComponent.h"


GraphViewComponent::GraphViewComponent(FreeAutoWahAudioProcessor& p)
    : audioProcessor(p)
{
    numSamples = audioProcessor.getNumSamples();
    frequencies = new double[numSamples];
    magnitudes = new double[numSamples];
    setSize(numSamples, 300);

    for (size_t i = 0; i < numSamples; i++)
    {
        frequencies[i] = 20.0 * std::pow(2.0, i / (numSamples / 10.0));// max value is 1024
        magnitudes[i] = 0.0;
    }

    startTimerHz(240);

    addAndMakeVisible(button);

    addMouseListener(this, false);

    buttonX = 100;
    buttonY = 100;

    addAndMakeVisible(graphLabel);
    graphLabel.setText(getGraphViewLabelText(), juce::dontSendNotification);
    graphLabel.setColour(juce::Label::textColourId, wahWhite);
    //graphLabel.setColour(juce::Label::outlineColourId, wahWhite);
    graphLabel.setFont(juce::Font(12.0f, juce::Font::bold));
}

GraphViewComponent::~GraphViewComponent()
{
    delete(frequencies);
    delete(magnitudes);
}

void GraphViewComponent::paint(juce::Graphics& g) 
{
    g.setColour(wahOrange);
    auto bounds = getLocalBounds();
    //juce::Path strokedCurve;

    for (size_t i = 0; i < numSamples; i++)
    {
        auto mappedMagnitude = magnitudes[i] / 10.0;
        auto mag = getHeight() - (getHeight() * mappedMagnitude); 
        //strokedCurve.lineTo(i, mag);


        g.drawLine(i, mag, i, getHeight(), 4.0f);
    }
    
    //g.setColour(wahLightGrey);
    //g.strokePath(strokedCurve, juce::PathStrokeType(juce::PathStrokeType::beveled)); 
}

void GraphViewComponent::resized()
{
    button.setBounds(buttonX, buttonY, 30, 30);
    graphLabel.setBounds(10, getHeight() - 70, 120, 50);
}

void GraphViewComponent::timerCallback() 
{
        audioProcessor.getFilterMagnitudeArray(frequencies, magnitudes);
        graphLabel.setText(getGraphViewLabelText(), juce::dontSendNotification);
        repaint();
}

void GraphViewComponent::moveButton()
{
    auto cursorPosition = getMouseXYRelative();
    buttonX = cursorPosition.getX();
    buttonY = cursorPosition.getY();

    if (buttonX >= 0 && buttonX <= 380
        && buttonY >= 0 && buttonY <= 245)
    {
        resized();
        repaint();

        auto xValue = 1.0f / getWidth() * buttonX;
        auto yValue = 1.0f / getHeight() * (getHeight() - buttonY);

        audioProcessor.getApvts()->getParameter(juce::StringRef("baseFrequency"))->setValueNotifyingHost(xValue);
        audioProcessor.getApvts()->getParameter(juce::StringRef("q"))->setValueNotifyingHost(yValue);
    }
}

juce::String GraphViewComponent::getGraphViewLabelText()
{
    juce::String str;
    str << graphViewCutOffText << audioProcessor.getApvts()->getParameter(juce::StringRef("baseFrequency"))->getCurrentValueAsText() << " Hz \n";
    str << graphViewQText << audioProcessor.getApvts()->getParameter(juce::StringRef("q"))->getCurrentValueAsText();
    return str;
}
