/*
  ==============================================================================

    LineArrayControlUI.h
    Created: 23 Aug 2017 12:48:40pm
    Author:  Mike

  ==============================================================================
*/

#ifndef LINEARRAYCONTROLUI_H_INCLUDED
#define LINEARRAYCONTROLUI_H_INCLUDED

#include <JuceHeader.h>
#include "ClickablePaths.h"

//==============================================================================
/*
*/
struct ControlView : Component, ClickablePaths::Listener
{
    explicit ControlView (const std::vector <float>& splayAngles);
    virtual ~ControlView ();

    void paint (Graphics&) override;
//    void resized () override;

//    void mouseUp (const MouseEvent& event) override;
//    void selectedStateChanged (ClickablePaths&) override;
//    void hide ();
    
    void selectedStateChanged (ClickablePaths&) override;
private:
	void drawElementImages (Graphics &g);
//    void drawAimPaths (Graphics &g);
//
//    bool noPathsSelected () const;
//    int  getElementIndex    (const MouseEvent&) const;
//    void selectSplayAngle (ClickablePaths &) const;
//    void selectElement (int index);
//
//    void generateSplayPaths ();
//    void generateAimPaths ();
//
//    int selectedIndex;
//    LineArray& lineArray;
//    Model&     model;
//    const Array <float>& splayAngles;
//    Array <Rectangle <float>> elementBounds;
//
//    Array <float> cumulativeAngles;
//    Array <Path> splayPaths;
//    Array <Path> aimPaths;
//
//    ScopedPointer <ClickableSegments> splayAngleSelector;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlView);
};


#endif  // LINEARRAYCONTROLUI_H_INCLUDED
