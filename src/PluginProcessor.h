/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <RTNeural/RTNeural.h>
//#include <JuceHeader.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_dsp/juce_dsp.h>


using ModelType = RTNeural::ModelT<float, 1, 1, RTNeural::LSTMLayerT<float, 1, 8>, RTNeural::DenseT<float, 8, 1>>;


//==============================================================================
/**
*/
class Stmaeproject_pluginAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    Stmaeproject_pluginAudioProcessor();
    ~Stmaeproject_pluginAudioProcessor() override;  

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void loadModel(std::ifstream& jsonStream, ModelType& model);

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // We are going to use the AudioProcessorValueTreeState class for implementing
    // the communication between Editor and Processor
    juce::AudioProcessorValueTreeState apvts;

    // we need to define a function where we actually associate all parameters and that
    // returns a ParameterLayout
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    //GAIN VARIABLE
    double rawVolume;
    double firstGain;
    double secondGain;

private:

    //INPUT GAINS     
    std::atomic<float>* firstInGainDbParam = nullptr;  
    juce::dsp::Gain<float> firstInputGain;                   

    std::atomic<float>* secondInGainDbParam = nullptr;  
    juce::dsp::Gain<float> secondInputGain;

    //MODELS
    ModelType distorsion_lstm_32_1_min_input_FIRST[2];
    ModelType distorsion_lstm_32_1_min_input_SECOND[2];

    ModelType distorsion_lstm_96_1_min_input_FIRST[2];
    ModelType distorsion_lstm_96_1_min_input_SECOND[2];

    ModelType distorsion_lstm_32_3_min_input_FIRST[2];   
    ModelType distorsion_lstm_32_3_min_input_SECOND[2];

    ModelType ts9_lstm_32_1_min_input_FIRST[2];
    ModelType ts9_lstm_32_1_min_input_SECOND[2];

    ModelType ts9_lstm_96_1_min_input_FIRST[2];
    ModelType ts9_lstm_96_1_min_input_SECOND[2];

    ModelType ts9_lstm_32_3_min_input_FIRST[2];        
    ModelType ts9_lstm_32_3_min_input_SECOND[2];

    ModelType reverb_lstm_32_1_min_input_FIRST[2];
    ModelType reverb_lstm_32_1_min_input_SECOND[2];


    //FUNCTION FOR SELECTING THE MODEL
    int selectFirstEffectFunction();  
    int selectSecondEffectFunction();

    int selectFirstModelTypeFunction();
    int selectSecondModelTypeFunction();

    float lastSampleRate;

    // Adding the DSP filter in the Processor header
    // ProcessorDuplicator is a template that converst mono processor class in a multi-channel version
    // template<typename MonoProcessorType, typename StateType>	
    // we also add a variable lastSampleRate to support later

    juce::dsp::ProcessorDuplicator <juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients <float>> lowPassFilter;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> dcBlocker;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> firstNoiseBlocker;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> secondNoiseBlocker;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Stmaeproject_pluginAudioProcessor)
};
