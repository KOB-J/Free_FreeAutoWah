/*
  ==============================================================================

    AutoWahSliderLookAndFeel.h
    Created: 30 Nov 2021 12:54:42pm
    Author:  dev

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>


class AutoWahSliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    AutoWahSliderLookAndFeel()
    {

    }

    ~AutoWahSliderLookAndFeel()
    {

    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
    {
        auto blue = juce::Colour::fromFloatRGBA(0.43f, 0.83f, 1.0f, 1.0f);

        auto bounds = slider.getLocalBounds().toFloat().withSizeKeepingCentre(100.0f, 100.0f);
        auto twoPi = juce::MathConstants<float>::twoPi;

        juce::Path path;
        juce::Path outline;

        outline.addPieSegment(bounds,
            rotaryStartAngle + (twoPi - 0.5f),
            rotaryStartAngle,
            0.5f);

        g.setColour(blue);
        g.strokePath(outline, juce::PathStrokeType(1.5f));

        path.addPieSegment(bounds,
            rotaryStartAngle + ((twoPi - 0.5f) * sliderPosProportional),
            rotaryStartAngle,
            0.5f);

        g.fillPath(path);

        g.setColour(juce::Colours::grey);
        g.fillEllipse(width * 0.15f, height * 0.15f, width * 0.7f, height * 0.7f);

        g.setColour(juce::Colours::white);
        g.drawText(slider.getTextFromValue(slider.getValue()), 30, 45, 40, 10, juce::Justification::centred);
    }



private:

};