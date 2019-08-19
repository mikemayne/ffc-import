/*
  ==============================================================================

    MainView.h
    Created: 16 Aug 2019 2:04:38pm
    Author:  Michael Mayne

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Renderer.h"
#include "ffc/ffc.h"

struct MainView : Component, TextEditor::InputFilter, TextEditor::Listener, ChangeBroadcaster
{
    MainView (Model &model);
    ~MainView();

    void paint (Graphics&) override;
    void resized() override;
    
    void textEditorReturnKeyPressed (TextEditor&) override;
    
    String filterNewText (TextEditor&, const String& newInput) override;
    
private:
    void setup(TextEditor&);
    void loadData();
    void loadImage(Image &target, ImageComponent &imageView);

    Model &model;
    
    ffc::Constants<float> constants;
    
    Renderer r;
    
    Label labelWidth;
    Label labelHeight;
    Label labelDepth;
    TextEditor editorWidth;
    TextEditor editorHeight;
    TextEditor editorDepth;
    
    ToggleButton buttonMirror;
    TextButton   buttonFindData;
    
    TextButton buttonChangeSideView  {"side view"};
    TextButton buttonChangeFrontView {"front view"};
    
    Image imageSideView;
    ImageComponent sideView;
    
    Image imageFrontView;
    ImageComponent frontView;
    
    float elementWidth;
    float elementHeight;
    float elementDepth;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainView);
};
