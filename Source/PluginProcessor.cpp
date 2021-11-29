/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FreeAutoWahAudioProcessor::FreeAutoWahAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
    , apvts(*this, &undoManager, "parameters", getParameterLayout())
#endif
{
}

FreeAutoWahAudioProcessor::~FreeAutoWahAudioProcessor()
{
}

//==============================================================================
const juce::String FreeAutoWahAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FreeAutoWahAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FreeAutoWahAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FreeAutoWahAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FreeAutoWahAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FreeAutoWahAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FreeAutoWahAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FreeAutoWahAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FreeAutoWahAudioProcessor::getProgramName (int index)
{
    return {};
}

void FreeAutoWahAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FreeAutoWahAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    autoWah.prepare(sampleRate, samplesPerBlock);
}

void FreeAutoWahAudioProcessor::releaseResources()
{
    autoWah.release();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FreeAutoWahAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FreeAutoWahAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    float baseFrequency = apvts.getRawParameterValue("baseFrequency")->load();
    float q = apvts.getRawParameterValue("q")->load();
    float lfoFrequency = apvts.getRawParameterValue("lfoFrequency")->load();
    float lfoWidth = apvts.getRawParameterValue("lfoWidth")->load();
    float envelopeWidth = apvts.getRawParameterValue("envelopeWidth")->load();
    float envelopeAttack = apvts.getRawParameterValue("envelopeAttack")->load();
    float envelopeDecay = apvts.getRawParameterValue("envelopeDecay")->load();

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    autoWah.process(buffer, baseFrequency, q, lfoFrequency, lfoWidth, envelopeWidth, envelopeAttack, envelopeDecay);
}

//==============================================================================
bool FreeAutoWahAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FreeAutoWahAudioProcessor::createEditor()
{
    return new FreeAutoWahAudioProcessorEditor (*this);
}

//==============================================================================
void FreeAutoWahAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void FreeAutoWahAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessorValueTreeState::ParameterLayout FreeAutoWahAudioProcessor::getParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "baseFrequency",
        "baseFrequency",
        0.0f,
        10000.0f,
        350.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "q",
        "q",
        0.01f,
        10.0f,
        5.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "lfoFrequency",
        "lfoFrequency",
        0.0f,
        10.0f,
        2.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "lfoWidth",
        "lfoWidth",
        0.0f,
        2000.0f,
        1000.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "envelopeWidth",
        "envelopeWidth",
        0.0f,
        4000.0f,
        0.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "envelopeAttack",
        "envelopeAttack",
        //0.000f,
        //0.01f,
        juce::NormalisableRange<float>(0.000f, 0.01f, 0.0001f),
        0.005f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "envelopeDecay",
        "envelopeDecay",
        //0.0f,
        //0.1f,
        juce::NormalisableRange<float>(0.000f, 0.1f, 0.001f),
        0.025f));

    return layout;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FreeAutoWahAudioProcessor();
}
