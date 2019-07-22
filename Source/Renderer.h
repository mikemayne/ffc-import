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
#include <ffc.h>

using juce::Graphics;
struct LineArray;
struct SplMeter;


struct Renderer : Component, juce::Thread, juce::Timer
{
	explicit Renderer (Colour(*colourFunction)(double) = &Renderer::darkRgba);
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
private:
    ffc::Constants<float> constants;
    std::vector<ffc::Source<float>> sources;
    ffc::Polar<float> p;
    
	bool isDirty;
	double renderStartTime;
	ScopedPointer <juce::Image> image;
	int splMeterWidth;

	Colour (*colourFunction)(double);
};


#endif  // RENDERER_H_INCLUDED
