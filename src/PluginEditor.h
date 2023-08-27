/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

//#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

//==============================================================================
/**
*/
class Stmaeproject_pluginAudioProcessorEditor : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    Stmaeproject_pluginAudioProcessorEditor(Stmaeproject_pluginAudioProcessor&);
    ~Stmaeproject_pluginAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Stmaeproject_pluginAudioProcessor& audioProcessor;

    //MASTER GAIN
    juce::Slider sliderGain;
    juce::Label sliderGainLabel;

    //STAGE GAINS
    juce::Slider firstStageGain;
    juce::Label firstStageLabel;
    juce::Slider secondStageGain;
    juce::Label secondStageLabel;

    //Q FACTOR LPF
    juce::Slider qualitySlider;
    juce::Label qualityLabel;

    //LPF
    juce::Slider frequencySlider;
    juce::Label frequencyLabel;

    //MODEL EFFECT SELECTORS
    juce::ComboBox selectFirstModelBox;
    juce::ComboBox selectSecondModelBox;

    //MODEL TYPE SELECTORS
    juce::ComboBox selectFirstModelTypeBox;
    juce::ComboBox selectSecondModelTypeBox;

    //IMAGES
    juce::Image image1;
    juce::ImageComponent imageComponent1;

    juce::Image image2;
    juce::ImageComponent imageComponent2;


    //ATTACHMENTS
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> qualitySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> frequencySliderAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> selectFirstModelBoxAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> selectSecondModelBoxAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> selectFirstModelTypeBoxAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> selectSecondModelTypeBoxAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Stmaeproject_pluginAudioProcessorEditor)
};
