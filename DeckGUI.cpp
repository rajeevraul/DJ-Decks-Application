/*
  ==============================================================================

    DeckGUI.cpp
    Created: 24 Feb 2023 11:46:45am
    Author:  Rajee

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, 
                AudioFormatManager & 	formatManagerToUse,
                AudioThumbnailCache & 	cacheToUse
           ) : player(_player), 
               waveformDisplay(formatManagerToUse, cacheToUse)
{
    // Displaying the GUI components
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(restartButton);
    addAndMakeVisible(loadButton);   
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(waveformDisplay);

    // Customising components
    volSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    speedSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    posSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    volSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    posSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);

    // Listeners for components
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    // Setting fixed ranges for components
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 5.0);
    posSlider.setRange(0.0, 1.0);

    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("", getLocalBounds(),
                Justification::centred, true); 
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 8; 
    double rotaryH = 3 * rowH;
    double rotaryW = getWidth() / 3;
    double controlsW = getWidth() / 4;

    playButton.setBounds(5, 5, controlsW, rowH);
    restartButton.setBounds(getWidth() / 2 - controlsW / 2, 5, controlsW, rowH);
    stopButton.setBounds(getWidth() - controlsW - 5, 5, controlsW, rowH);

    volSlider.setBounds(5, 30 + rowH, rotaryW, rotaryH);
    speedSlider.setBounds(10 + rotaryW, 30 + rowH, rotaryW, rotaryH);
    posSlider.setBounds(15 + 2 * rotaryW, 30 + rowH, rotaryW, rotaryH);
    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);
    loadButton.setBounds(0, rowH * 7, getWidth(), rowH);

    volLabel.setText("Volume", NotificationType::dontSendNotification);
    volLabel.attachToComponent(&volSlider, false);

    speedLabel.setText("Speed", NotificationType::dontSendNotification);
    speedLabel.attachToComponent(&speedSlider, false);

    posLabel.setText("Position", NotificationType::dontSendNotification);
    posLabel.attachToComponent(&posSlider, false);
}


void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
     if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();

    }
     if (button == &restartButton)
     {
         std::cout << "Restart button was clicked " << std::endl;
         player->setPosition(0.0);

     }
     if (button == &loadButton)
     {
        auto fileChooserFlags = 
        FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            player->loadURL(URL{chooser.getResult()});
            waveformDisplay.loadURL(URL{chooser.getResult()}); 
        });
     }
}

void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
    
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
    player->loadURL(URL{File{files[0]}});
  }
}

void DeckGUI::timerCallback()
{
    //std::cout << "DeckGUI::timerCallback" << std::endl;
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}


    

