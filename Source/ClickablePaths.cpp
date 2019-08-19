/*
  ==============================================================================

    ClickablePaths.cpp
    Created: 23 Aug 2017 10:06:02am
    Author:  Mike

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ClickablePaths.h"

//==============================================================================
ClickablePaths::ClickablePaths(bool latching, float xTolerance, float yTolerance)
: selectedPath (nullptr)
, overPath     (nullptr)
, lineColour     (Colours::white)
, selectedColour (Colours::red)
, overColour (Colours::blueviolet)
, xTolerance (xTolerance)
, yTolerance (yTolerance)
, latching   (latching)
{ }

ClickablePaths::~ClickablePaths()
{ }

void ClickablePaths::paint (Graphics& g)
{	
	g.setColour (lineColour);

	for (auto& line : lines)
	{
		g.strokePath (line, PathStrokeType (1.0));
	}

	paintSpecialPath (g, selectedPath, selectedColour);
	paintSpecialPath (g, overPath, overColour);
}

void ClickablePaths::mouseMove (const MouseEvent& event)
{
	switchPathAndRepaint (event, &overPath);
}

void ClickablePaths::mouseUp (const MouseEvent& event)
{
	const auto stateChanged = switchPathAndRepaint (event, &selectedPath, latching ? selectedPath : nullptr);
		
	if (stateChanged)
	{
		observers.call (&Listener::selectedStateChanged, *this);
	} 
	else
	{
		if (auto parent = getParentComponent())
			parent->mouseUp (event);
	}
}

int ClickablePaths::getSelectedIndex () const
{
	return selectedPath ? lines.indexOf (*selectedPath) : -1;
}

void ClickablePaths::addListener (Listener* listener)
{
	observers.add (listener);
}

void ClickablePaths::setPaths (juce::Array <Path> paths)
{
	lines = paths;
	selectedPath = nullptr;
	overPath     = nullptr;
}

void ClickablePaths::setSelectedIndex (int idx)
{
	if (idx < 0 || idx >= lines.size())
	{
		selectedPath = nullptr;
		return;
	}

	selectedPath = &lines.getReference (idx);
}

Path* ClickablePaths::findPathUnderMouse (const MouseEvent& event) const
{
	for (auto& line : lines)
	{
		auto bounds = line.getBounds();
		auto target = bounds.transformedBy (AffineTransform().scaled (1.1f, 4.f, bounds.getX(), bounds.getY()));
		if (target.contains (event.position.x, event.position.y))
		{
			return &line;
		}
	}

	return nullptr;
}

bool ClickablePaths::switchPathAndRepaint (const MouseEvent& event, Path** path, Path* defaultValue)
{
	if (!path)
		return false;

	auto newPath = findPathUnderMouse (event);
	 
	/**
	 * Optionally provide a default value
	 * eg. when you want a value to always
	 * stay selected even when the user
	 * clicks outside all targets
	 */
	newPath = newPath ? newPath : defaultValue;

	/**
	 * Only update if the path has changed
	 */
	if (newPath != *path)
	{
		*path = newPath;
		repaint ();
		return true;
	}

	return false;
}

void ClickablePaths::paintSpecialPath (Graphics& g, Path* p, Colour c)
{
	if (p)
	{
		g.setColour (c);
		g.strokePath (*p, PathStrokeType (2.0));
	}
}
