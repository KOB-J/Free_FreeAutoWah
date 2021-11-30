/*
  ==============================================================================

    RightComponent.h
    Created: 29 Nov 2021 3:38:27pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/Colors.h"
#include "../Utils/Colors.h"
#include "Slider/AutoWahRotarySlider.h"
#include "../Utils/Strings.h"


class RightComponent : public juce::Component
{
public:
    RightComponent();
    ~RightComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    AutoWahRotarySlider* getEnvelopeWidthSlider() { return &envelopeWidthSlider; }
    AutoWahRotarySlider* getEnvelopeAttackSlider() { return &envelopeAttackSlider; }
    AutoWahRotarySlider* getEnvelopeDecaySlider() { return &envelopeDecaySlider; }

private:
    AutoWahRotarySlider envelopeWidthSlider, envelopeAttackSlider, envelopeDecaySlider;
    juce::Label envelopeWidthLabel, envelopeAttackLabel, envelopeDecayLabel, envelopeTitleLabel;

};