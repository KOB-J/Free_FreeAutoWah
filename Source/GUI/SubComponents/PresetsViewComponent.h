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
        saveButton.setButtonText(savePresetButtonText);

        newButton.onClick = [this] {newPreset(); };
        saveButton.onClick = [this] {savePreset(); };

        addAndMakeVisible(newButton);
        addAndMakeVisible(saveButton);
        addAndMakeVisible(newLabel);

        newLabel.setEditable(true);
        newLabel.setColour(juce::Label::outlineColourId, juce::Colours::beige);

        addAndMakeVisible(listBox);
    }

    ~PresetsViewComponent()
    {
    }

    void resized() override
    {
        newButton.setBounds(0, 0, 80, 40);
        newLabel.setBounds(0, 45, 80, 40);
        saveButton.setBounds(90, 0, 80, 40);
        listBox.setBounds(200, 50, 150, 150);
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