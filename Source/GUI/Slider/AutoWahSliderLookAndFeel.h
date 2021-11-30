/*
  ==============================================================================

    AutoWahSliderLookAndFeel.h
    Created: 30 Nov 2021 12:54:42pm
    Author:  dev

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>
#include "../Source/Utils/Colors.h"


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
        auto bounds = slider.getLocalBounds().toFloat().withSizeKeepingCentre(width, height);
        auto twoPi = juce::MathConstants<float>::twoPi;

        juce::Path path;
        juce::Path outline;

        outline.addPieSegment(bounds,
            rotaryStartAngle + (twoPi - 0.5f),
            rotaryStartAngle,
            0.5f);

        g.setColour(wahAzur);
        g.strokePath(outline, juce::PathStrokeType(0.5f));

        path.addPieSegment(bounds,
            rotaryStartAngle + ((twoPi - 0.5f) * sliderPosProportional),
            rotaryStartAngle,
            0.5f);

        g.fillPath(path);

        g.setColour(wahMidGrey);
        g.fillEllipse(width * 0.15f, height * 0.15f, width * 0.7f, height * 0.7f);

        g.setColour(wahWhite);
        g.drawFittedText(slider.getTextFromValue(slider.getValue()), width * 0.25, height * 0.5, width * 0.6, height * 0.02, juce::Justification::centred, 1);
    }



private:

};