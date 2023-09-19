/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 24 Feb 2023 11:46:45am
    Author:  Rajee

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager & 	formatManagerToUse,
                                 AudioThumbnailCache & 	cacheToUse) :
                                 audioThumb(1000, formatManagerToUse, cacheToUse), 
                                 fileLoaded(false), 
                                 position(0)
                          
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

  audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint(Graphics& g)
{
    g.fillAll(Colours::black); 

    g.setColour(Colours::darkolivegreen.withAlpha(0.5f));
    g.drawRect(getLocalBounds(), 3);

    if (fileLoaded)
    {
        auto bounds = getLocalBounds();
        auto gradient = ColourGradient(Colours::red, bounds.getCentreX(), 0.5f,
                        Colours::green, bounds.getCentreX(), bounds.getHeight(), true);
        g.setGradientFill(gradient);
        audioThumb.drawChannel(g, getLocalBounds(), 0, audioThumb.getTotalLength(), 0.1f, 0.5f);
    }
    else
    {
        g.setColour(Colours::cyan.brighter());
        g.setFont(20.0f);
        g.drawText("File not loaded...", getLocalBounds(),
            Justification::centred, true);
    }
    g.setColour(Colours::lime.withAlpha(0.5f));
    g.fillRect(position * getWidth(), 0, getWidth() / 20, getHeight());
}


void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(URL audioURL)
{
  audioThumb.clear();
  fileLoaded  = audioThumb.setSource(new URLInputSource(audioURL));
  if (fileLoaded)
  {
    std::cout << "wfd: loaded! " << std::endl;
    repaint();
  }
  else {
    std::cout << "wfd: not loaded! " << std::endl;
  }

}

void WaveformDisplay::changeListenerCallback (ChangeBroadcaster *source)
{
    std::cout << "wfd: change received! " << std::endl;

    repaint();

}

void WaveformDisplay::setPositionRelative(double pos)
{
  if (pos != position)
  {
    position = pos;
    repaint();
  }

  
}




