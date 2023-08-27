/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_dsp/juce_dsp.h>
//==============================================================================
Stmaeproject_pluginAudioProcessorEditor::Stmaeproject_pluginAudioProcessorEditor (Stmaeproject_pluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    //EDITOR'S SIZE
    setSize (430, 770);


    //LOADING IMAGES
    image1 = juce::ImageFileFormat::loadFrom(juce::File::File("C:/Users/marco/Desktop/Selected Topics in MAE project/images/silhouette.png"));
    if (image1.isValid()){
        imageComponent1.setImage(image1);
    addAndMakeVisible(&imageComponent1);
    }

    image2 = juce::ImageFileFormat::loadFrom(juce::File::File("C:/Users/marco/Desktop/Selected Topics in MAE project/images/logo.png"));
    if (image2.isValid()) {
        imageComponent2.setImage(image2);
        addAndMakeVisible(&imageComponent2);
    }

    //EDITING BACKGROUND, SLIDERS AND BOXES
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::darkred);
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::red);
    getLookAndFeel().setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::grey);
    getLookAndFeel().setColour(juce::ComboBox::backgroundColourId, juce::Colours::grey);
    getLookAndFeel().setColour(juce::ComboBox::arrowColourId, juce::Colours::darkred);
    getLookAndFeel().setColour(juce::ComboBox::outlineColourId, juce::Colours::grey);
    getLookAndFeel().setColour(juce::ComboBox::textColourId, juce::Colours::darkred);


    //MASTER GAIN
    sliderGain.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    sliderGain.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    sliderGain.setRange(-12.0, 12.0);
    sliderGain.setValue(1.0);
    sliderGain.addListener(this);
    addAndMakeVisible(sliderGain);
    sliderGainLabel.setText("Gain", juce::dontSendNotification);
    addAndMakeVisible(sliderGainLabel);

    //STAGE GAINS
    firstStageGain.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    firstStageGain.setTextBoxStyle(juce::Slider::TextBoxRight, true, 30, 25);
    firstStageGain.setRange(-12.0, 12.0);
    firstStageGain.setValue(1.0);
    firstStageGain.addListener(this);
    addAndMakeVisible(firstStageGain);

    secondStageGain.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    secondStageGain.setTextBoxStyle(juce::Slider::TextBoxRight, true, 30, 25);
    secondStageGain.setRange(-12.0, 12.0);
    secondStageGain.setValue(1.0);
    secondStageGain.addListener(this);
    addAndMakeVisible(secondStageGain);

    //Q FACTOR LPF
    qualitySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    qualitySlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 25);
    qualitySlider.setRange(0.0, 1.0, 0.1);
    addAndMakeVisible(qualitySlider);
    qualityLabel.setText("Q",juce::dontSendNotification);
    addAndMakeVisible(qualityLabel);

    //LPF
    frequencySlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    frequencySlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 25);
    frequencySlider.setRange(50.0, 20000.0, 100.0);
    addAndMakeVisible(frequencySlider);
    frequencyLabel.setText("Frequency", juce::dontSendNotification);
    addAndMakeVisible(frequencyLabel);

    //FIRST MODEL EFFECT SELECTOR
    selectFirstModelBox.addItem("Bypass", 1);
    selectFirstModelBox.addItem("Distorsion", 2);
    selectFirstModelBox.addItem("Overdrive", 3);
    selectFirstModelBox.addItem("Reverb", 4);
    selectFirstModelBox.setSelectedId(1); 
    addAndMakeVisible(selectFirstModelBox);
    firstStageLabel.setText("First stage:", juce::dontSendNotification);
    addAndMakeVisible(firstStageLabel);

    //SECOND MODEL EFFECT SELECTOR
    selectSecondModelBox.addItem("Bypass", 1);
    selectSecondModelBox.addItem("Distorsion", 2);
    selectSecondModelBox.addItem("Overdrive", 3);
    selectSecondModelBox.addItem("Reverb", 4);
    selectSecondModelBox.setSelectedId(1);
    addAndMakeVisible(selectSecondModelBox);
    secondStageLabel.setText("Second stage:", juce::dontSendNotification);
    addAndMakeVisible(secondStageLabel);

    //FIRST MODEL TYPE SELECTOR
    selectFirstModelTypeBox.addItem("LSTM, HS=32, 1:00 MIN INPUT", 1);
    selectFirstModelTypeBox.addItem("LSTM, HS=96, 1:00 MIN INPUT", 2);
    selectFirstModelTypeBox.addItem("LSTM, HS=32, 3:30 MIN INPUT", 3);
    selectFirstModelTypeBox.setSelectedId(1);
    addAndMakeVisible(selectFirstModelTypeBox);

    //SECOND MODEL TYPE SELECTOR
    selectSecondModelTypeBox.addItem("LSTM, HS=32, 1:00 MIN INPUT", 1);
    selectSecondModelTypeBox.addItem("LSTM, HS=96, 1:00 MIN INPUT", 2);
    selectSecondModelTypeBox.addItem("LSTM, HS=32, 3:30 MIN INPUT", 3);
    selectSecondModelTypeBox.setSelectedId(1);
    addAndMakeVisible(selectSecondModelTypeBox);


    // We need to instantiate our attachments and linking the value tree state and the sliders
    // Since they are unique pointers we need to use the make_unique template
    // SliderAttachment (AudioProcessorValueTreeState &stateToUse, const String &parameterID, Slider &slider)
    frequencySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FREQ", frequencySlider);
    qualitySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Q", qualitySlider);

    selectFirstModelBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "FIRST_MODEL_EFFECT", selectFirstModelBox);
    selectSecondModelBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "SECOND_MODEL_EFFECT", selectSecondModelBox);
   
    selectFirstModelTypeBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "FIRST_MODEL_TYPE", selectFirstModelTypeBox);
    selectSecondModelTypeBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "SECOND_MODEL_TYPE", selectSecondModelTypeBox);
   
   
}

Stmaeproject_pluginAudioProcessorEditor::~Stmaeproject_pluginAudioProcessorEditor()
{
}

//==============================================================================
void Stmaeproject_pluginAudioProcessorEditor::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::darkred);
    g.fillRect(30, 20, 370, 700);
    g.drawRoundedRectangle(20, 20, 390, 730, 10, 30);

}

void Stmaeproject_pluginAudioProcessorEditor::resized()
{
    
    imageComponent1.setBounds(-290, 10, 1000, 760);
    imageComponent2.setBounds(40, 290, 350, 175);

    //MASTER GAIN
    sliderGain.setBounds(33, 40, 170, 170);
    sliderGainLabel.setBounds(100, 210, 130, 20);

    //LPF
    frequencySlider.setBounds(148, 140, 130, 130);
    frequencyLabel.setBounds(170, 270, 130, 20);

    //Q FACTOR LPF
    qualitySlider.setBounds(227, 40, 170, 170);
    qualityLabel.setBounds(300, 210, 130, 20);

    //STAGE GAINS
    firstStageGain.setBounds(300, 510, 80, 80);
    firstStageLabel.setBounds(50, 510, 100, 20);

    secondStageGain.setBounds(300, 600, 80, 80);
    secondStageLabel.setBounds(50, 600, 100, 20);

    //MODEL EFFECT SELECTORS
    selectFirstModelBox.setBounds(50, 540, 100, 20);
    selectSecondModelBox.setBounds(50, 630, 100, 20);

    //MODEL TYPE SELECTORS
    selectFirstModelTypeBox.setBounds(160, 540, 140, 20);
    selectSecondModelTypeBox.setBounds(160, 630, 140, 20);

}

void Stmaeproject_pluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    //GAIN IMPLEMENTATION
    if (slider == &sliderGain)
    {
        audioProcessor.rawVolume = pow(10, sliderGain.getValue() / 20);  
    }

    if (slider == &firstStageGain)
    {
        audioProcessor.firstGain = pow(10, firstStageGain.getValue() / 20);  
    }

    if (slider == &secondStageGain)
    {
        audioProcessor.secondGain = pow(10, secondStageGain.getValue() / 20);  
    }
}

