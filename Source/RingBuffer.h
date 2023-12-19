/*
  ==============================================================================

    RingBuffer.h
    Created: 16 Dec 2023 10:46:32pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct RingBuffer {
    //Memberfunction
    juce::AudioBuffer<float> audioBuffer_;
    int writePosition_;

    //Constructor
    RingBuffer();

    //Memberfunction
    void fillBuffer(int channel, double sampleRate, const int& bufferSize, const int& ringBufferSize, const float* bufferData);
    void getFromDelayBuffer(juce::AudioBuffer<float>& buffer, int channel, double sampleRate, const int& bufferSize, const int& ringBufferSize, const float* bufferData, const float* ringBufferData);
    void feedbackDelay(int channel, const float* bufferData, const int bufferSize, const int ringBufferSize);
};