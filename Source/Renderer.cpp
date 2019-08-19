/*
  ==============================================================================

    Renderer.cpp
    Created: 20 Jun 2017 5:11:20pm
    Author:  Mike

  ==============================================================================
*/

#include "Renderer.h"
#include "Model.h"

Renderer::Renderer (Model& model, ffc::Constants<float>& constants, Colour(*colourFunction)(double)) :
Thread ("RenderThread"),
model (model),
constants (constants),
isDirty (true),
imageReady (false),
image   (nullptr),
colourFunction (colourFunction ? colourFunction : &darkRgba)
{
    for (int i=0; i<1; ++i)
        sources.push_back({&model.makePolar(constants.frequencyHz)});
    
    const float x = 20; // metres
    float y = 10; // metres
    for (auto& source : sources) {
       source.acousticCentre = {x, (y += 0.4)};
    }
    model.addChangeListener(this);
	startThread ();
    startTimer(10);
}

Renderer::~Renderer ()
{
    model.removeChangeListener(this);
	stopThread (250);
}

void Renderer::changeListenerCallback (ChangeBroadcaster* source)
{
    if (&model == source) {
        for (auto saus : sources) {
            saus.polar = &model.makePolar (constants.frequencyHz);
            isDirty = true;
        }
    }
}

void Renderer::paint (Graphics& g)
{
    if (image) {
        g.drawImageAt (*image, 0, 0);
        imageReady = false;
    } else {
        g.fillAll(Colours::black);
    }
}

/**
 * Converts a point in M within a given rectangle to a point in px.
 * 
 * The size in Px will only include positive values, the size in M can go negative.
 */
Point <int> Renderer::getPxFromM (Point <float> m, Rectangle <int> sizePx, Rectangle <float> sizeM)
{
	const auto xPx = static_cast <int> (((m.x - sizeM.getPosition().x) / sizeM.getWidth ()  * sizePx.getWidth ())); 
	auto yPx = static_cast <int> (((m.y - sizeM.getPosition().y) / sizeM.getHeight () * sizePx.getHeight ())); 
	yPx = sizePx.getHeight() - yPx; // invert

	return {xPx, yPx};
}

Point <float> Renderer::getMFromPx (Point <int> px, Rectangle <int> sizePx, Rectangle <float> sizeM)
{
	const auto xM = (px.x / static_cast <float> (sizePx.getWidth ()) * sizeM.getWidth ()) + sizeM.getPosition().x;
		
	const auto yPxInverted = sizePx.getHeight() - px.y; // invert
	const auto yM = (yPxInverted / static_cast <float> (sizePx.getHeight ()) * sizeM.getHeight ()) + sizeM.getPosition().y;

	return {xM, yM};
}

Rectangle <int> 
Renderer::getRectPxFromRectM (Rectangle <float> boundsInM, Rectangle <int> sizePx, Rectangle <float> sizeM)
{
	return {getPxFromM (boundsInM.getTopLeft(), sizePx, sizeM), getPxFromM (boundsInM.getBottomRight(), sizePx, sizeM)};
}

void Renderer::render(std::vector<float> const& splMap)
{
    auto max = FloatVectorOperations::findMaximum(splMap.data(), static_cast<int>(splMap.size()));
    image = new Image (Image::PixelFormat::ARGB, constants.width_px, constants.height_px, true);
    Image::BitmapData bitmap (*image, 0, 0, constants.width_px, constants.height_px, Image::BitmapData::ReadWriteMode::readWrite);
    
    for (long index = 0; index < splMap.size(); ++index) {
        auto y = index / constants.width_px;
        auto x = index % constants.width_px;
        
        bitmap.setPixelColour ((int)x, (int)y, colourFunction (max - splMap[index]));
    }
    
}

void Renderer::run ()
{
    while (!threadShouldExit())
    {
        if (!isDirty) {
            wait(10);
            continue;
        }
        
        ffc::FreeFieldCalculator<float> calc (8, sources, constants);
        ffc::FreeFieldCalculator<float>::Result r (constants.height_px * constants.width_px);
        calc.calculate (r);
        auto spl = ffc::convert_to_spl (r);
        render (spl);
        isDirty = false; imageReady = true;
    }
}

/**
 * Repaint the component here, so the update happens on the correct thread.
 */
void Renderer::timerCallback ()
{
    if (imageReady)
		repaint();
}

Colour Renderer::darkRgba (double val)
{
	if (val < 0.f) val = 0.f;
    uint8 r = 255;
    uint8 g = 255;
    uint8 b = 255;
    uint8 a = 200;

    const auto band1 = 3.0;
    const auto band2 = 6.0;
    const auto band3 = 9.0;
    const auto band4 = 12.0;
    const auto band5 = 20.0;
    const auto band6 = 40.0;

    if (val < band1) 
	{ 
		const auto width = static_cast <double> (band1);
		const auto depth = 255 / width;
        r = 255;
        g = static_cast <uint8> (255 - (val * depth));
        b = 255 - static_cast <uint8> (val * depth);
    } 
	else if (val >= band1 && val < band2)  // red to yellow
	{ 
		const auto width = static_cast <double> (band2 - band1);
		const auto depth = 255 / width;
        r = 255;
        g = static_cast <uint8> ((val - band1) * depth);
        b = 0;
    } 
	else if (val >= band2 && val < band3)  // yellow to green
	{
		const auto width = static_cast <double> (band3 - band2);
		const auto depth = 255 / width;
        b =   0;
        g = 255;
        r = static_cast <uint8> (255 - (val - band2) * depth);
    } 
	else if (val >= band3 && val < band4) // green to light blue
	{ 
		const auto width = static_cast <double> (band4 - band3);
		const auto depth = 255 / width;
        r =   0;
        g = 255;
        b = static_cast <uint8> ((val - band3) * depth);
    } 
	else if (val >= band4 && val < band5)  //light blue to dark blue
	{
		const auto width = static_cast <double> (band5 - band4);
		const auto depth = 255 / width;
        r =   0;
        b = 255;
        g = static_cast <uint8> (255 - (val - band4)*depth);
	} 
	else if (val >= band5 && val < band6) //dark blue fade out
	{ 
		const auto width = static_cast <double> (band6 - band5);
		const auto depth = 190 / width;
        r =   0;
		g =   0;
        b = 255;
        a = static_cast <uint8> (190 - (val - band5) * depth);
    } 
	else if (val >= band6) // black
	{               
        r = 0; g = 0; b = 0; a = 10;
    }

    return Colour (r, g, b, a);
}

Colour Renderer::stretchRgba (double val)
{
	if (val < 0.f) val = 0.f;
    uint8 r = 255;
    uint8 g = 255;
    uint8 b = 255;
    uint8 a = 127;

    auto band1 = 6.0;
    auto band2 = 9.0;
    auto band3 = 12.0;
    auto band4 = 18.0;
    auto band5 = 24.0;

    if (val < band1) // white to red.
	{ 
        r = 255;
        g = static_cast <uint8> (255-(val*20.0));
        b = 255 - static_cast <uint8> (val*20.0);
    } 
	else if (val >= band1 && val < band2) // red to yellow
	{ 
        b = 0;
        r = 255;
        g = (static_cast <uint8> (val-band1)*20);
    } 
	else if (val >= band2 && val < band3) // yellow to green
	{ 
        b = 0;
        g = 255;
        r = static_cast <uint8> (255-(val-band2)*20);
    } 
	else if (val >= band3 && val < band4)  // green to light blue
	{
        r = 0;
        g = 255;
        b = static_cast <uint8> ((val-band3)*20);
    } 
	else if (val >= band4 && val < band5) //light blue to dark blue
	{ 
        r = 0;
        b = 255;
        g = static_cast <uint8> (255-(val-band4)*20);
    } 
	else if (val >= band5) // black
	{               
        r = 0; g = 0; b = 0; a = 255;
    }

    return Colour (r, g, b, a);
}
