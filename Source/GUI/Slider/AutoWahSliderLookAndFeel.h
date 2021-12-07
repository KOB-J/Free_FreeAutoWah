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

        auto maxVal = slider.getMaximum();
        auto val = slider.getValue();
        

        DBG("slider max value: " << maxVal);

        if (maxVal == 2000 || maxVal == 4000)
        {
            auto modVal = slider.getTextFromValue(val);
            auto intVal = modVal.getIntValue();
            modVal = (juce::String)intVal;
            g.drawFittedText(modVal, width * 0.21, height * 0.49, width * 0.6, height * 0.02, juce::Justification::centred, 1);

        }       
        else if (maxVal == 0.01f)
        {
            auto val2 = val * 1000.00;
            auto modVal = (juce::String)val2;
            DBG("modVal: " << modVal<<" val: "<<(juce::String)val);
            g.drawFittedText(modVal, width * 0.21, height * 0.49, width * 0.6, height * 0.02, juce::Justification::centred, 1);
        }
        else if (maxVal == 0.1f)
        {
            auto val2 = val * 1000.00;
            auto modVal = (juce::String)val2;
            DBG("modVal: " << modVal << " val: " << (juce::String)val);
            g.drawFittedText(modVal, width * 0.21, height * 0.49, width * 0.6, height * 0.02, juce::Justification::centred, 1);
        }
        else
        {
            g.drawFittedText(slider.getTextFromValue(val), width * 0.21, height * 0.49, width * 0.6, height * 0.02, juce::Justification::centred, 1);
        }
    



        

    }

private:

};