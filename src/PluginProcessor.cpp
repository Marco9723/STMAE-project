/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_dsp/juce_dsp.h>

//==============================================================================
Stmaeproject_pluginAudioProcessor::Stmaeproject_pluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     //#if ! JucePlugin_IsMidiEffect
                     //#if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                     // #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     //#endif
                       ), apvts(*this, nullptr, "Parameters", createParameters()),
                       lowPassFilter(juce::dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.1))
#endif
{
    firstInGainDbParam = apvts.getRawParameterValue("first_input_gain_db");
    secondInGainDbParam = apvts.getRawParameterValue("second_input_gain_db");
 
    //MODELS LOADING
    auto modelFilePath1 = "C:/Users/marco/Desktop/Selected Topics in MAE project/models/distorsion_lstm_32_1_min_input.json";     
    assert(std::filesystem::exists(modelFilePath1));
    std::cout << "Loading model from path: " << modelFilePath1 << std::endl;
    std::ifstream jsonStream1(modelFilePath1, std::ifstream::binary);
    loadModel(jsonStream1, distorsion_lstm_32_1_min_input_FIRST[0]);
    std::ifstream jsonStream2(modelFilePath1, std::ifstream::binary);
    loadModel(jsonStream2, distorsion_lstm_32_1_min_input_FIRST[1]);
    std::ifstream jsonStream3(modelFilePath1, std::ifstream::binary);
    loadModel(jsonStream3, distorsion_lstm_32_1_min_input_SECOND[0]);
    std::ifstream jsonStream4(modelFilePath1, std::ifstream::binary);
    loadModel(jsonStream4, distorsion_lstm_32_1_min_input_SECOND[1]);

    auto modelFilePath2 = "C:/Users/marco/Desktop/Selected Topics in MAE project/models/distorsion_lstm_96_1_min_input.json";  
    assert(std::filesystem::exists(modelFilePath2));
    std::cout << "Loading model from path: " << modelFilePath2 << std::endl;
    std::ifstream jsonStream5(modelFilePath2, std::ifstream::binary);
    loadModel(jsonStream5, distorsion_lstm_96_1_min_input_FIRST[0]);
    std::ifstream jsonStream6(modelFilePath2, std::ifstream::binary);
    loadModel(jsonStream6, distorsion_lstm_96_1_min_input_FIRST[1]);
    std::ifstream jsonStream7(modelFilePath2, std::ifstream::binary);
    loadModel(jsonStream7, distorsion_lstm_96_1_min_input_SECOND[0]);
    std::ifstream jsonStream8(modelFilePath2, std::ifstream::binary);
    loadModel(jsonStream8, distorsion_lstm_96_1_min_input_SECOND[1]);

    auto modelFilePath3 = "C:/Users/marco/Desktop/Selected Topics in MAE project/models/distorsion_lstm_32_3_min_input.json";   
    assert(std::filesystem::exists(modelFilePath3));
    std::cout << "Loading model from path: " << modelFilePath3 << std::endl;
    std::ifstream jsonStream9(modelFilePath3, std::ifstream::binary);
    loadModel(jsonStream9, distorsion_lstm_32_3_min_input_FIRST[0]);
    std::ifstream jsonStream10(modelFilePath3, std::ifstream::binary);
    loadModel(jsonStream10, distorsion_lstm_32_3_min_input_FIRST[1]);
    std::ifstream jsonStream11(modelFilePath3, std::ifstream::binary);
    loadModel(jsonStream11, distorsion_lstm_32_3_min_input_SECOND[0]);
    std::ifstream jsonStream12(modelFilePath3, std::ifstream::binary);
    loadModel(jsonStream12, distorsion_lstm_32_3_min_input_SECOND[1]);

   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto modelFilePath4 = "C:/Users/marco/Desktop/Selected Topics in MAE project/models/ts9_lstm_32_1_min_input.json";     
    assert(std::filesystem::exists(modelFilePath4));
    std::cout << "Loading model from path: " << modelFilePath4 << std::endl;
    std::ifstream jsonStream13(modelFilePath4, std::ifstream::binary);
    loadModel(jsonStream13, ts9_lstm_32_1_min_input_FIRST[0]);
    std::ifstream jsonStream14(modelFilePath4, std::ifstream::binary);
    loadModel(jsonStream14, ts9_lstm_32_1_min_input_FIRST[1]);
    std::ifstream jsonStream15(modelFilePath4, std::ifstream::binary);
    loadModel(jsonStream15, ts9_lstm_32_1_min_input_SECOND[0]);
    std::ifstream jsonStream16(modelFilePath4, std::ifstream::binary);
    loadModel(jsonStream16, ts9_lstm_32_1_min_input_SECOND[1]);

    auto modelFilePath5 = "C:/Users/marco/Desktop/Selected Topics in MAE project/models/ts9_lstm_96_1_min_input.json";   
    assert(std::filesystem::exists(modelFilePath5));
    std::cout << "Loading model from path: " << modelFilePath5 << std::endl;
    std::ifstream jsonStream17(modelFilePath5, std::ifstream::binary);
    loadModel(jsonStream17, ts9_lstm_96_1_min_input_FIRST[0]);
    std::ifstream jsonStream18(modelFilePath5, std::ifstream::binary);
    loadModel(jsonStream18, ts9_lstm_96_1_min_input_FIRST[1]);
    std::ifstream jsonStream19(modelFilePath5, std::ifstream::binary);
    loadModel(jsonStream19, ts9_lstm_96_1_min_input_SECOND[0]);
    std::ifstream jsonStream20(modelFilePath5, std::ifstream::binary);
    loadModel(jsonStream20, ts9_lstm_96_1_min_input_SECOND[1]);

    auto modelFilePath6= "C:/Users/marco/Desktop/Selected Topics in MAE project/models/ts9_lstm_32_3_min_input.json";     
    assert(std::filesystem::exists(modelFilePath6));
    std::cout << "Loading model from path: " << modelFilePath6<< std::endl;
    std::ifstream jsonStream21(modelFilePath6, std::ifstream::binary);
    loadModel(jsonStream21, ts9_lstm_32_3_min_input_FIRST[0]);
    std::ifstream jsonStream22(modelFilePath6, std::ifstream::binary);
    loadModel(jsonStream22, ts9_lstm_32_3_min_input_FIRST[1]);
    std::ifstream jsonStream23(modelFilePath6, std::ifstream::binary);
    loadModel(jsonStream23, ts9_lstm_32_3_min_input_SECOND[0]);
    std::ifstream jsonStream24(modelFilePath6, std::ifstream::binary);
    loadModel(jsonStream24, ts9_lstm_32_3_min_input_SECOND[1]);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto modelFilePath7 = "C:/Users/marco/Desktop/Selected Topics in MAE project/models/reverb_lstm_32_1_min_input.json";   
    assert(std::filesystem::exists(modelFilePath7));
    std::cout << "Loading model from path: " << modelFilePath7 << std::endl;
    std::ifstream jsonStream25(modelFilePath7, std::ifstream::binary);
    loadModel(jsonStream25, reverb_lstm_32_1_min_input_FIRST[0]);
    std::ifstream jsonStream26(modelFilePath7, std::ifstream::binary);
    loadModel(jsonStream26, reverb_lstm_32_1_min_input_FIRST[1]);
    std::ifstream jsonStream27(modelFilePath7, std::ifstream::binary);
    loadModel(jsonStream27, reverb_lstm_32_1_min_input_SECOND[0]);
    std::ifstream jsonStream28(modelFilePath7, std::ifstream::binary);
    loadModel(jsonStream28, reverb_lstm_32_1_min_input_SECOND[1]);

}

Stmaeproject_pluginAudioProcessor::~Stmaeproject_pluginAudioProcessor()
{
}

//==============================================================================
const juce::String Stmaeproject_pluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Stmaeproject_pluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Stmaeproject_pluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Stmaeproject_pluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Stmaeproject_pluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Stmaeproject_pluginAudioProcessor::getNumPrograms()
{
    return 1;   
}

int Stmaeproject_pluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Stmaeproject_pluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Stmaeproject_pluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void Stmaeproject_pluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Stmaeproject_pluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    *dcBlocker.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 35.0f);
    *firstNoiseBlocker.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 2000.0f);
    *secondNoiseBlocker.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 4000.0f);

    juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 }; //IMPORTANTE

    // We need to reset our filters and initialize the filter
    // void prepare (const ProcessSpec &) noexcept
    // It takes as input a ProcessSpec structure, where used sampleRate and samplesPerBlock need to be specified
    lastSampleRate = sampleRate;

    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();

    //INPUT GAINS
    firstInputGain.prepare(spec);                   
    firstInputGain.setRampDurationSeconds(0.05);    

    secondInputGain.prepare(spec);
    secondInputGain.setRampDurationSeconds(0.05);

    //FILTERS
    dcBlocker.prepare(spec);   
    dcBlocker.reset();

    firstNoiseBlocker.prepare(spec);
    firstNoiseBlocker.reset();

    secondNoiseBlocker.prepare(spec);
    secondNoiseBlocker.reset();

    lowPassFilter.prepare(spec);  
    lowPassFilter.reset();

    //MODEL RESET
    distorsion_lstm_32_1_min_input_FIRST[0].reset();
    distorsion_lstm_32_1_min_input_FIRST[1].reset();
    distorsion_lstm_32_1_min_input_SECOND[0].reset();
    distorsion_lstm_32_1_min_input_SECOND[1].reset();

    distorsion_lstm_96_1_min_input_FIRST[0].reset();
    distorsion_lstm_96_1_min_input_FIRST[1].reset();
    distorsion_lstm_96_1_min_input_SECOND[0].reset();
    distorsion_lstm_96_1_min_input_SECOND[1].reset();

    distorsion_lstm_32_3_min_input_FIRST[0].reset();
    distorsion_lstm_32_3_min_input_FIRST[1].reset();
    distorsion_lstm_32_3_min_input_SECOND[0].reset();
    distorsion_lstm_32_3_min_input_SECOND[1].reset();
    ///////////////////////////////////////////////////////////////
    ts9_lstm_32_1_min_input_FIRST[0].reset();
    ts9_lstm_32_1_min_input_FIRST[1].reset();
    ts9_lstm_32_1_min_input_SECOND[0].reset();
    ts9_lstm_32_1_min_input_SECOND[1].reset();

    ts9_lstm_96_1_min_input_FIRST[0].reset();
    ts9_lstm_96_1_min_input_FIRST[1].reset();
    ts9_lstm_96_1_min_input_SECOND[0].reset();
    ts9_lstm_96_1_min_input_SECOND[1].reset();

    ts9_lstm_32_3_min_input_FIRST[0].reset();
    ts9_lstm_32_3_min_input_FIRST[1].reset();
    ts9_lstm_32_3_min_input_SECOND[0].reset();
    ts9_lstm_32_3_min_input_SECOND[1].reset();
    ///////////////////////////////////////////////////////////////
    reverb_lstm_32_1_min_input_FIRST[0].reset();
    reverb_lstm_32_1_min_input_FIRST[1].reset();
    reverb_lstm_32_1_min_input_SECOND[0].reset();
    reverb_lstm_32_1_min_input_SECOND[1].reset();
  

}

void Stmaeproject_pluginAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Stmaeproject_pluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif  <-----------------

    return true;
  #endif
}
#endif

void Stmaeproject_pluginAudioProcessor::loadModel(std::ifstream& jsonStream, ModelType& model)
{
    nlohmann::json modelJson;
    jsonStream >> modelJson;

    auto& lstm = model.get<0>();

    std::string prefix = "lstm.";

    // for LSTM layers, number of hidden  = number of params in a hidden weight set divided by 4
    auto hidden_count = modelJson[prefix + ".weight_ih_l0"].size() / 4;

    RTNeural::torch_helpers::loadLSTM<float>(modelJson, prefix, lstm);  

    auto& dense = model.get<1>();

    RTNeural::torch_helpers::loadDense<float>(modelJson, "dense.", dense);  


}


void Stmaeproject_pluginAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);

    if (selectFirstEffectFunction() == 1 || selectFirstEffectFunction() == 2 || selectFirstEffectFunction() == 3) {
        firstNoiseBlocker.process(context);
        firstInputGain.setGainDecibels(firstInGainDbParam->load() + 35.0f);
        firstInputGain.process(context);
    }

    //FIRST STAGE
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        auto* x = buffer.getWritePointer(channel);  
        if (selectFirstEffectFunction() == 0) {
            for (int n = 0; n < buffer.getNumSamples(); ++n)   
            {
                x[n] = buffer.getSample(channel, n) * firstGain;
            }
        }

        else if (selectFirstEffectFunction() == 1 && selectFirstModelTypeFunction() == 0) {
            for (int n = 0; n < buffer.getNumSamples(); ++n)   
            {
                float input[] = { x[n] };
                x[n] = distorsion_lstm_32_1_min_input_FIRST[channel].forward(input) * firstGain;
            }
        }

        else if (selectFirstEffectFunction() == 2 && selectFirstModelTypeFunction() == 0) {
            for (int n = 0; n < buffer.getNumSamples(); ++n)
            {
                float input[] = { x[n] };
                x[n] = ts9_lstm_32_1_min_input_FIRST[channel].forward(input) * firstGain;
            }
        }

        else if (selectFirstEffectFunction() == 1 && selectFirstModelTypeFunction() == 1) {
            for (int n = 0; n < buffer.getNumSamples(); ++n)  
            {
                float input[] = { x[n] };
                x[n] = distorsion_lstm_96_1_min_input_FIRST[channel].forward(input) * firstGain;
            }
        }

        else if (selectFirstEffectFunction() == 2 && selectFirstModelTypeFunction() == 1) {
            for (int n = 0; n < buffer.getNumSamples(); ++n)  
            {
                float input[] = { x[n] };
                x[n] = ts9_lstm_96_1_min_input_FIRST[channel].forward(input) * firstGain;
            }
        }

        else if (selectFirstEffectFunction() == 1 && selectFirstModelTypeFunction() == 2) {
            for (int n = 0; n < buffer.getNumSamples(); ++n)
            {
                float input[] = { x[n] };
                x[n] = distorsion_lstm_32_3_min_input_FIRST[channel].forward(input) * firstGain;
            }
        }

        else if (selectFirstEffectFunction() == 2 && selectFirstModelTypeFunction() == 2) {
            for (int n = 0; n < buffer.getNumSamples(); ++n)
            {
                float input[] = { x[n] };
                x[n] = ts9_lstm_32_3_min_input_FIRST[channel].forward(input) * firstGain;  
            }
        }

        else if (selectFirstEffectFunction() == 3) {
            for (int n = 0; n < buffer.getNumSamples(); ++n) 
            {
                float input[] = { x[n] };
                x[n] = reverb_lstm_32_1_min_input_FIRST[channel].forward(input) * firstGain;
            }
        }
    }

    //SECOND STAGE
    if (selectSecondEffectFunction() == 1 || selectSecondEffectFunction() == 2 || selectSecondEffectFunction() == 3 || selectSecondEffectFunction() == 4) {
        secondNoiseBlocker.process(context);
        secondInputGain.setGainDecibels(secondInGainDbParam->load() + 35.0f);
        secondInputGain.process(context);
    }

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        auto* x = buffer.getWritePointer(channel); 
        if (selectSecondEffectFunction() == 0) {
            for (int n = 0; n < buffer.getNumSamples(); ++n)  
            {
                x[n] = buffer.getSample(channel, n) * secondGain;
            }
        }

        else if (selectSecondEffectFunction() == 1 && selectSecondModelTypeFunction() == 0) {
            for (int n = 0; n < buffer.getNumSamples(); ++n)   
            {
                float input[] = { x[n] };
                x[n] = distorsion_lstm_32_1_min_input_SECOND[channel].forward(input) * secondGain;
            }
        }

        else if (selectSecondEffectFunction() == 2 && selectSecondModelTypeFunction() == 0) {
            for (int n = 0; n < buffer.getNumSamples(); ++n) 
            {
                float input[] = { x[n] };
                x[n] = ts9_lstm_32_1_min_input_SECOND[channel].forward(input) * secondGain;
            }
        }

        else if (selectSecondEffectFunction() ==1 && selectSecondModelTypeFunction() == 1) {
            for (int n = 0; n < buffer.getNumSamples(); ++n)  
            {
                float input[] = { x[n] };
                x[n] = distorsion_lstm_96_1_min_input_SECOND[channel].forward(input) * secondGain;
            }
        }

        else if (selectSecondEffectFunction() == 2 && selectSecondModelTypeFunction() == 1) {
            for (int n = 0; n < buffer.getNumSamples(); ++n)  
            {
                float input[] = { x[n] };
                x[n] = ts9_lstm_96_1_min_input_SECOND[channel].forward(input) * secondGain;
            }
        }

        else if (selectSecondEffectFunction() == 1 && selectSecondModelTypeFunction() == 2) {
            for (int n = 0; n < buffer.getNumSamples(); ++n)
            {
                float input[] = { x[n] };
                x[n] = distorsion_lstm_32_3_min_input_FIRST[channel].forward(input) * secondGain;
            }
        }

        else if (selectSecondEffectFunction() == 2 && selectSecondModelTypeFunction() == 2) {
            for (int n = 0; n < buffer.getNumSamples(); ++n)
            {
                float input[] = { x[n] };
                x[n] = ts9_lstm_32_3_min_input_FIRST[channel].forward(input) * secondGain;  
            }
        }

        else if (selectSecondEffectFunction() == 3) {
            for (int n = 0; n < buffer.getNumSamples(); ++n)   
            {
                float input[] = { x[n] };
                x[n] = reverb_lstm_32_1_min_input_SECOND[channel].forward(input) * secondGain;
            }
        }
    }
        
  
    //OUTPUT GAIN STAGE
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        auto* x = buffer.getWritePointer(channel); 
        
        for (int n = 0; n < buffer.getNumSamples(); ++n)   
        {
            x[n] = buffer.getSample(channel, n) * rawVolume;
        }
    }


    // we get the parameters from the value tree state
    // since getRawParameters return a pointer we need to use the * to access the value
    float freq = *apvts.getRawParameterValue("FREQ");
    float quality = *apvts.getRawParameterValue("Q");

    dcBlocker.process(context);
    //buffer.applyGain(25.0f);    //IF NECESSARY 

    // we update the filter state
    // static Ptr makeLowPass (double sampleRate, NumericType frequency, NumericType Q)
    *lowPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(lastSampleRate, freq, quality);
    lowPassFilter.process(juce::dsp::ProcessContextReplacing<float>(block));

    ignoreUnused(midiMessages);
}

//==============================================================================
bool Stmaeproject_pluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Stmaeproject_pluginAudioProcessor::createEditor()
{
    return new Stmaeproject_pluginAudioProcessorEditor (*this);
}

//==============================================================================
void Stmaeproject_pluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{

}

void Stmaeproject_pluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

}

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Stmaeproject_pluginAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout Stmaeproject_pluginAudioProcessor::createParameters()
{

    // parameters correspond to a vector of unique pointers to objects of classes RangedAudioParameters
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    
    // AudioParameterFloat (String parameterID, String parameterName, float minValue, float maxValue, float defaultValue)
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("first_input_gain_db", "Gain [dB]", -12.0f, 12.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("second_input_gain_db", "Gain [dB]", -12.0f, 12.0f, 0.0f));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FREQ", "CutOff Frequency", 50.0f, 20000.0f, 10000.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("Q", "Q Factor", 0.1f, 1.0f, 0.5f));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FIRST_MODEL_EFFECT", "FIRST_MODEL_EFFECT", 0.0f, 3.0f, 0.f)); 
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("SECOND_MODEL_EFFECT", "SECOND_MODEL_EFFECT", 0.0f, 3.0f, 0.f));
    
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FIRST_MODEL_TYPE", "FIRST_MODEL_TYPE", 0.0f, 2.0f, 0.f)); 
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("SECOND_MODEL_TYPE", "SECOND_MODEL_TYPE", 0.0f, 2.0f, 0.f)); 
    
                        
    return { parameters.begin(), parameters.end() };
}

int Stmaeproject_pluginAudioProcessor::selectFirstEffectFunction() {
    int modelEffect = (int) *apvts.getRawParameterValue("FIRST_MODEL_EFFECT");
    switch (modelEffect) {
    case 0:
        return 0;
        break;
    case 1:
        return 1;
        break;
    case 2:
        return 2;
        break;
    case 3:
        return 3;
        break;
    default:
        return 0;
        break;
    }
}

int Stmaeproject_pluginAudioProcessor::selectSecondEffectFunction() {
    int modelType = *apvts.getRawParameterValue("SECOND_MODEL_EFFECT");
    switch (modelType) {
    case 0:
        return 0;
        break;
    case 1:
        return 1;
        break;
    case 2:
        return 2;
        break;
    case 3:
        return 3;
        break;
    default:
        return 0;
        break;
    }
} 

int Stmaeproject_pluginAudioProcessor::selectFirstModelTypeFunction() {
    int modelType = *apvts.getRawParameterValue("FIRST_MODEL_TYPE");
    switch (modelType) {
    case 0:
        return 0;
        break;
    case 1:
        return 1;
        break;
    case 2:
        return 2;
        break;
    default:
        return 0;
        break;
    }
}

int Stmaeproject_pluginAudioProcessor::selectSecondModelTypeFunction() {
    int modelType = *apvts.getRawParameterValue("SECOND_MODEL_TYPE");
    switch (modelType) {
    case 0:
        return 0;
        break;
    case 1:
        return 1;
        break;
    case 2:
        return 2;
        break;
    default:
        return 0;
        break;
    }
}
