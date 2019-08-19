/*
  ==============================================================================

    ClickableLines.h
    Created: 23 Aug 2017 10:06:02am
    Author:  Mike

  ==============================================================================
*/

#ifndef CLICKABLELINES_H_INCLUDED
#define CLICKABLELINES_H_INCLUDED

#include <JuceHeader.h>

//==============================================================================
/*
*/
struct ClickablePaths : Component
{
    struct Listener
    {
        virtual ~Listener() = default;
        virtual void selectedStateChanged (ClickablePaths&) = 0;
    };
    explicit ClickablePaths (bool latching = true, float xTolerance = 1.1, float yTolerance = 4.0);
    virtual ~ClickablePaths ();

    void paint (Graphics&) override;
	void mouseMove (const MouseEvent&) override;
	void mouseUp   (const MouseEvent&) override;

	int getSelectedIndex () const;
	void setSelectedIndex (int);

	void addListener     (Listener*);
	void setPaths        (Array <Path> lines);

protected:

	/**
	 * Returns the path under the mouse pointer, or nullptr.
	 * 
	 * Override to implement different collision detection
	 * methods.
	 */
	virtual Path* findPathUnderMouse (const MouseEvent&) const;

	Array <Path> lines;

private:
	/**
	 * Switch the over or selected path
	 * 
	 * Provide a default value if you want to keep a line latched on.
	 * 
	 * Returns true if the state of the line has changed, false otherwise.
	 */
	bool switchPathAndRepaint (const MouseEvent&, Path** pathToSwitch, Path* defaultValue = nullptr);
	static void paintSpecialPath (Graphics&, Path*, Colour);
	
	Path *selectedPath;
	Path *overPath;

	Colour lineColour;
	Colour selectedColour;
	Colour overColour;

	float xTolerance;
	float yTolerance;
	bool latching;

	ListenerList <Listener> observers;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClickablePaths)
};


#endif  // CLICKABLELINES_H_INCLUDED
