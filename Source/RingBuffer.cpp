/*
  ==============================================================================

    RingBuffer.cpp
    Created: 16 Dec 2023 10:46:32pm
    Author:  lazlo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RingBuffer.h"

//Constructor

RingBuffer::RingBuffer() : audioBuffer_(), writePosition_(0) {}

//Memberfunktion

void RingBuffer::fillBuffer(int channel, double sampleRate, const int& bufferSize, const int& ringBufferSize, const float* bufferData)
{
    //copy data from main buffer to delay buffer
    if (ringBufferSize > bufferSize + writePosition_)
    {
        audioBuffer_.copyFromWithRamp(channel, writePosition_, bufferData, bufferSize, 0.8, 0.8);
    }
    else {
        const int bufferRemaining = ringBufferSize - writePosition_;

        audioBuffer_.copyFromWithRamp(channel, writePosition_, bufferData, bufferRemaining, 0.8, 0.8);
        audioBuffer_.copyFromWithRamp(channel, 0, bufferData, bufferSize - bufferRemaining, 0.8, 0.8);
    }
}

void RingBuffer::getFromDelayBuffer(juce::AudioBuffer<float>& buffer, int channel, double sampleRate, const int& bufferSize, const int& ringBufferSize, const float* bufferData, const float* ringBufferData)
{
    int delayTime = 500;

    const int readPosition = static_cast<int> (ringBufferSize + writePosition_ - (sampleRate * delayTime / 1000)) % ringBufferSize;

    if (ringBufferSize > bufferSize + readPosition) {
        buffer.copyFrom(channel, 0, ringBufferData + readPosition, bufferSize);
    }
    else {
        const int bufferRemaining = ringBufferSize - readPosition;
        buffer.copyFrom(channel, 0, ringBufferData + readPosition, bufferRemaining);
        buffer.copyFrom(channel, bufferRemaining, ringBufferData, bufferSize - bufferRemaining);
    }
}

void RingBuffer::feedbackDelay(int channel, const float* bufferData, const int bufferSize, const int ringBufferSize)
{
    if (ringBufferSize > bufferSize + writePosition_) {
        audioBuffer_.addFromWithRamp(channel, writePosition_, bufferData, bufferSize, 0.8, 0.8);
    }
    else {
        const int bufferRemaining = ringBufferSize - writePosition_;

        audioBuffer_.addFromWithRamp(channel, bufferRemaining, bufferData, bufferRemaining, 0.8, 0.8);
        audioBuffer_.addFromWithRamp(channel, 0, bufferData, bufferSize - bufferRemaining, 0.8, 0.8);
    }
}