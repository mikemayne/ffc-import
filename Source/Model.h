/*
  ==============================================================================

    Model.h
    Created: 18 Aug 2019 3:54:09pm
    Author:  Michael Mayne

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ffc/ffc.h"
//#include "ffc/frd/frd.h"
#include <algorithm>

struct Model : ChangeBroadcaster
{
    Model() :
    p (makePointSource())
    { }
    
    void setPolarData(frd::PolarData<float> newPolarData)
    {
        polarData = newPolarData;
        sendChangeMessage();
    }
    
    ffc::Polar<float> const& makePolar(float freq)
    {
        if (polarData.size() > 0) {
            p = mirror ? ffc::make_mirrored_polar(polarData, freq) : ffc::make_polar(polarData, freq);
        }
        
        return p;
    }
    
    ffc::Polar<float> makePointSource()
    {
        ffc::Polar<float> p(72);
        std::fill(p.begin(), p.end(), std::make_pair(98.f, 0.f));
        return p;
    }
    
    void setShouldMirrorPolar(bool shouldMirrorData)
    {
        mirror = shouldMirrorData;
        sendChangeMessage();
    }
    
private:
    bool mirror = false;
    frd::PolarData<float> polarData;
    ffc::Polar<float> p;
};
