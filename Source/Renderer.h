/*
  ==============================================================================

    Renderer.h
    Created: 20 Jun 2017 5:11:20pm
    Author:  Mike

  ==============================================================================
*/

#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <JuceHeader.h>
#include "ffc/ffc.h"
#include "ControlView.h"
#include "Element.h"

using juce::Graphics;
struct LineArray;
struct SplMeter;
struct Model;

struct Renderer : Component, Thread, Timer, ChangeListener
{
    explicit Renderer (Model& model, ffc::Constants<float>& constants, Colour(*colourFunction)(double) = &Renderer::darkRgba);
	virtual ~Renderer ();

	void paint   (Graphics& g) override;
	void run () override;
    
    static Point <int> getPxFromM (Point <float> m, Rectangle <int> sizePx, Rectangle <float> sizeM);
    static Point <float> getMFromPx (Point <int> px, Rectangle <int> sizePx, Rectangle <float> sizeM);

	static Rectangle <int> getRectPxFromRectM (Rectangle <float> boundsInM, Rectangle <int> sizePx, Rectangle <float> sizeM);

	static Colour darkRgba    (double val);
	static Colour stretchRgba (double val);

    void render(std::vector<float> const& splMap);
    
    void timerCallback() override;
    void changeListenerCallback (ChangeBroadcaster* source) override;
    
private:
    Model& model;
    ffc::Constants<float>& constants;
    
    std::vector<ffc::SoundSource<float>> sources;
    OwnedArray<Element> elements;
    
	bool isDirty;
    bool imageReady;
    ScopedPointer <juce::Image> image;

	Colour (*colourFunction)(double);
//    ControlView control;
};


#endif  // RENDERER_H_INCLUDED
