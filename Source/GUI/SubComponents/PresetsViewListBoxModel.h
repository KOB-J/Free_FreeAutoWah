/*
  ==============================================================================

    PresetsViewListBoxModel.h
    Created: 6 Dec 2021 2:32:40pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Source/PluginProcessor.h"


class PresetsViewListBoxModel : public juce::ListBoxModel
{
public:
    PresetsViewListBoxModel(FreeAutoWahAudioProcessor& p, juce::ListBox& l)
        : audioProcessor(p)
        , listBox(l)
    {
    }

    int getNumRows() override
    {
        return getList().size();
    }

    void paintListBoxItem(int rowNumber, juce::Graphics& g,
        int width, int height, bool rowIsSelected) override
    {
        if (rowIsSelected)
            g.fillAll(juce::Colours::lightblue);

        g.setColour(juce::LookAndFeel::getDefaultLookAndFeel().findColour(juce::Label::textColourId));
        g.setFont((float)height * 0.7f);
        g.drawText(getList()[rowNumber],
            5, 0, width, height,
            juce::Justification::centredLeft, true);
    }

    juce::var getDragSourceDescription(const juce::SparseSet<int>& selectedRows) override
    {
        juce::StringArray rows;

        for (int i = 0; i < selectedRows.size(); ++i)
            rows.add(juce::String(selectedRows[i] + 1));

        return rows.joinIntoString(", ");
    }

    juce::StringArray getList()
    {
        juce::String filePath = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getFullPathName();
        juce::StringArray list;

        juce::File file = juce::File(filePath);

        auto results = file.findChildFiles(juce::File::findFiles, false, "*.xml");

        DBG("result size: " << results.size());
        DBG("file path: " << filePath);


        for (auto result : results)
        {
            DBG("file name: " << result.getFileName());
            list.add(result.getFileName());
        }

        return list;

    }

    void selectedRowsChanged(int lastRowSelected) override
    {
        juce::String fileName = getList()[lastRowSelected];
        juce::String filePath = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getFullPathName() + "/" + fileName;
        juce::File file = juce::File(filePath);
        std::unique_ptr<juce::XmlElement> xmlState;

        auto apvts = audioProcessor.getApvts();

        xmlState = juce::XmlDocument::parse(file);

        if (xmlState.get() != nullptr)
            if (xmlState->hasTagName(apvts->state.getType()))
                apvts->replaceState(juce::ValueTree::fromXml(*xmlState));
    }

    void deleteKeyPressed(int lastRowSelected) override
    {
        juce::String fileName = getList()[lastRowSelected];
        juce::String filePath = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getFullPathName() + "/" + fileName;
        juce::File file = juce::File(filePath);

        if (file.exists()) {
            file.deleteFile();
            listBox.updateContent();
        }
    }

    void saveToFile(int lastRowSelected)
    {
        juce::String fileName = getList()[lastRowSelected];
        juce::String filePath = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getFullPathName() + "/" + fileName;
        juce::File file = juce::File(filePath);
        std::unique_ptr<juce::XmlElement> xmlState;

        auto apvts = audioProcessor.getApvts();
        auto state = apvts->copyState();
        std::unique_ptr<juce::XmlElement> xml(state.createXml());

        DBG("xml: " << xml.get()->toString());

        xmlState = state.createXml();

        if (!file.exists()) {
            file.create();
        }
        else {
            file.deleteFile();
        }


        xml.get()->writeTo(file, {});

        DBG("file: " << file.getFileName());
    }

    void saveToFile(juce::String fileName)
    {
        juce::String filePath = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getFullPathName() + "/" + fileName + ".xml";
        juce::File file = juce::File(filePath);
        std::unique_ptr<juce::XmlElement> xmlState;

        auto apvts = audioProcessor.getApvts();
        auto state = apvts->copyState();
        std::unique_ptr<juce::XmlElement> xml(state.createXml());

        DBG("xml: " << xml.get()->toString());

        xmlState = state.createXml();

        if (!file.exists()) {
            file.create();
        }
        else {
            file.deleteFile();
        }


        xml.get()->writeTo(file, {});

        DBG("file: " << file.getFileName());
    }

private:
    FreeAutoWahAudioProcessor& audioProcessor;
    juce::ListBox& listBox;
};
