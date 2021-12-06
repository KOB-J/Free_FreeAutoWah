/*
  ==============================================================================

    PresetsViewComponent.h
    Created: 1 Dec 2021 4:47:40pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Source/PluginProcessor.h"
#include "../../Utils/Colors.h"
#include "../../Utils/Strings.h"
#include "PresetsViewListBoxModel.h"


class PresetsViewComponent : public juce::Component
{
public:
    PresetsViewComponent(FreeAutoWahAudioProcessor& p)
        : audioProcessor(p)
        , presetsViewListBoxModel(p, listBox)
        , listBox("presets", &presetsViewListBoxModel)
    {
        newButton.setButtonText(newPresetButtonText);
        newButton.setColour(juce::TextButton::textColourOffId, wahAzur);
        newButton.setColour(juce::TextButton::buttonColourId, wahBlack);

        saveButton.setButtonText(savePresetButtonText);
        saveButton.setColour(juce::TextButton::textColourOffId, wahAzur);
        saveButton.setColour(juce::TextButton::buttonColourId, wahBlack);

        newButton.onClick = [this] {newPreset(); };
        saveButton.onClick = [this] {savePreset(); };

        addAndMakeVisible(newButton);
        addAndMakeVisible(saveButton);
        addAndMakeVisible(newLabel);

        newLabel.setEditable(true);
        newLabel.setColour(juce::Label::backgroundColourId, wahDarkGrey);
        newLabel.setColour(juce::Label::outlineColourId, wahMidGrey);

        addAndMakeVisible(listBox);
        listBox.setColour(juce::ListBox::backgroundColourId, wahDarkGrey);
    }

    ~PresetsViewComponent()
    {
    }

    void resized() override
    {
        newLabel.setBounds(getWidth() - 170, 10, 160, 30);
        newButton.setBounds(getWidth() - 90, 40, 80, 40);
        saveButton.setBounds(getWidth() - 90, 120, 80, 40);
        listBox.setBounds(10, 10, getWidth() - 200, getHeight() - 20);
    }

    void newPreset()
    {
        if (newLabel.getText() != "")
        {
            presetsViewListBoxModel.saveToFile(newLabel.getText());
            listBox.updateContent();
            newLabel.setText("", juce::dontSendNotification);
        }
    }

    void savePreset()
    {
        presetsViewListBoxModel.saveToFile(listBox.getSelectedRow());
    }

private:
    FreeAutoWahAudioProcessor& audioProcessor;
    juce::TextButton newButton, saveButton;
    juce::Label newLabel;
    juce::ListBox listBox;
    PresetsViewListBoxModel presetsViewListBoxModel;
};