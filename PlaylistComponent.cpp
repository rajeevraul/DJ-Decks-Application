/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 24 Feb 2023 11:46:45am
    Author:  Rajee

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
    trackTitles.push_back("Track 5");
    trackTitles.push_back("Track 6");

    tableComponent.getHeader().addColumn("Track Title", 1 , 400);
    tableComponent.getHeader().addColumn(" ", 2, 200);
    tableComponent.getHeader().addColumn("Length", 3, 400);

    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int PlaylistComponent::getNumRows()
{
    return trackTitles.size();
}
void PlaylistComponent::paintRowBackground(Graphics & g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else {
        g.fillAll(Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell(Graphics & g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected)
{
    g.drawText(trackTitles[rowNumber],
        2, 0,
        width - 4, height, 
        Justification::centredLeft, true);
}

Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
    int columnId,
    bool isRowSelected,
    Component* existingComponentToUpdate)
{
    if (columnId == 2)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton("play");
            String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);

            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button)
{
    int id =std::stoi(button->getComponentID().toStdString());

    DBG("PlaylistComponent::buttonClicked ");
    //std::cout << button->getComponentID << std::endl;
    std::cout << trackTitles[id] << std::endl;
}