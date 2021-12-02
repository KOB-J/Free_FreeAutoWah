/*
  ==============================================================================

    GraphViewComponent.h
    Created: 1 Dec 2021 4:47:23pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Source/PluginProcessor.h"
#include "../../Utils/Colors.h"
#include "../../Utils/Strings.h"


class GraphViewComponent 
    : public juce::Component
    , public juce::Timer
    , public juce::MouseListener
{
public:
    GraphViewComponent(FreeAutoWahAudioProcessor& p)
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
    }

    ~GraphViewComponent()
    {
        delete(frequencies);
        delete(magnitudes);
    }

    void paint(juce::Graphics& g) override
    {
        g.setColour(juce::Colours::white);
        auto bounds = getLocalBounds();
        juce::Path path;

        for (size_t i = 0; i < numSamples; i++)
        {
            path.lineTo(i, getHeight() - (getHeight() / 2.0 * magnitudes[i]));
        }
        g.strokePath(path, juce::PathStrokeType(juce::PathStrokeType::beveled));    
    }

    void resized() override
    {
        button.setBounds(buttonX, buttonY, 50, 50);
    }

    void timerCallback() override
    {
        audioProcessor.getFilterMagnitudeArray(frequencies, magnitudes);
        repaint();
    }

    void mouseDrag(const juce::MouseEvent& event) { moveButton(); }
    void mouseDown(const juce::MouseEvent& event) { moveButton(); }

private:
    FreeAutoWahAudioProcessor& audioProcessor;

    int numSamples;
    double* frequencies;
    double* magnitudes;
    juce::TextButton button;
    int buttonX, buttonY;

    void moveButton()
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
            auto yValue = 1.0f / getHeight() * buttonY;
                          
            audioProcessor.getApvts()->getParameter(juce::StringRef("baseFrequency"))->setValueNotifyingHost(xValue);
            audioProcessor.getApvts()->getParameter(juce::StringRef("q"))->setValueNotifyingHost(yValue);            
        }
    }
};
