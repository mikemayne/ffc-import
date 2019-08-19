/*
  ==============================================================================

    Element.h
    Created: 14 Aug 2019 4:57:14pm
    Author:  Michael Mayne

  ==============================================================================
*/

#pragma once

#include "ffc/ffc.h"
#include <JuceHeader.h>

struct Element {
    // next step: load data from disk
    Element (ffc::ElementType<float> &type, ffc::ElementState<float> &state) :
    type (type),
    state (state)
    { }
    
private:
    
    ffc::ElementType<float>&  type;
    ffc::ElementState<float>& state;
    Image side;
    Image front;
};
