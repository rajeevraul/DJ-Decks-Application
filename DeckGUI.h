/*
  ==============================================================================

    DeckGUI.h
    Created: 24 Feb 2023 11:46:45am
    Author:  Rajee

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener, 
                   public FileDragAndDropTarget, 
                   public Timer
{
public:
    DeckGUI(DJAudioPlayer* player, 
           AudioFormatManager & 	formatManagerToUse,
           AudioThumbnailCache & 	cacheToUse );
    ~DeckGUI();

    void paint (Graphics&) override;
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

    bool isInterestedInFileDrag (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override; 

    void timerCallback() override; 

private:

    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton restartButton{ "RESTART" };
    TextButton loadButton{"LOAD"};

    Slider volSlider; 
    Slider speedSlider;
    Slider posSlider;

    Label volLabel;
    Label speedLabel;
    Label posLabel;

    FileChooser fChooser{"Select a file..."};


    WaveformDisplay waveformDisplay;

    DJAudioPlayer* player; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
