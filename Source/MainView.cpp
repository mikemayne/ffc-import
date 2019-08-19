/*
  ==============================================================================

    MainView.cpp
    Created: 16 Aug 2019 2:04:38pm
    Author:  Michael Mayne

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainView.h"
#include "Model.h"

//==============================================================================
MainView::MainView(Model& model) :
model (model),
constants {1000.f, 0.05f, 343.f, 1024, 1024, {0.f, 0.f}},
r {model, constants},
elementWidth(1.f),
elementHeight(0.3f),
elementDepth(0.5f)
{
    labelWidth .setText ("Width (m)",  dontSendNotification);
    labelHeight.setText ("Height (m)", dontSendNotification);
    labelDepth .setText ("Depth (m)",  dontSendNotification);
    
    editorWidth .setText (String (elementWidth,  1));
    editorHeight.setText (String (elementHeight, 1));
    editorDepth .setText (String (elementDepth,  1));
    setup (editorWidth);
    setup (editorHeight);
    setup (editorDepth);
    
    addAndMakeVisible (r);
    addAndMakeVisible (labelWidth);
    addAndMakeVisible (labelHeight);
    addAndMakeVisible (labelDepth);
    
    addAndMakeVisible (buttonChangeSideView);
    addAndMakeVisible (sideView);
    
    addAndMakeVisible (buttonChangeFrontView);
    addAndMakeVisible (frontView);
    
    addAndMakeVisible (buttonMirror);
    addAndMakeVisible (buttonFindData);
    
    buttonFindData.setButtonText("data...");
    buttonFindData.onClick = std::bind(&MainView::loadData, this);
    
    buttonMirror.onClick = [&]() {
      model.setShouldMirrorPolar(buttonMirror.getToggleState());
    };
    
    buttonChangeSideView .onClick = std::bind(&MainView::loadImage, this, std::ref(imageSideView),  std::ref(sideView));
    buttonChangeFrontView.onClick = std::bind(&MainView::loadImage, this, std::ref(imageFrontView), std::ref(frontView));
    
    setOpaque(true);
    setSize(constants.width_px + 150, constants.height_px);
}

void MainView::setup(TextEditor& editor)
{
    editor.setInputFilter (this, false);
    editor.addListener (this);
    addAndMakeVisible(editor);
}

MainView::~MainView()
{ }

void MainView::loadData()
{
    FileChooser file("Select directory containing data");
    if (!file.browseForDirectory())
        return;
    
    model.setShouldMirrorPolar(buttonMirror.getToggleState());
    model.setPolarData(frd::import_polardata<float> (file.getResult().getFullPathName().toStdString()));
    
    DBG("Loaded " << file.getResult().getFullPathName());
}

void MainView::loadImage(Image &image, ImageComponent &imageView)
{
    FileChooser file ("Select image", File(), "*.png, *.jpg");
    if (!file.browseForFileToOpen())
        return;
    
    image = ImageFileFormat::loadFrom (file.getResult());
    imageView.setImage (image);
}

void MainView::textEditorReturnKeyPressed(TextEditor& editor)
{
    String::CharPointerType charPtr = editor.getText().getCharPointer();

    if (&editorWidth == &editor)
    {
        elementWidth = float(CharacterFunctions::readDoubleValue(charPtr));
    }
    else if (&editorHeight == &editor)
    {
        elementHeight = float(CharacterFunctions::readDoubleValue(charPtr));
    }
    else if (&editorDepth == &editor)
    {
        elementDepth = float(CharacterFunctions::readDoubleValue(charPtr));
    }
    DBG("width : " << elementWidth << " height: " << elementHeight << " depth: " << elementDepth);
}

String MainView::filterNewText (TextEditor&, const String& newInput)
{
    if (!newInput.containsOnly("0123456789."))
    {
        return String("");
    }
    
    return newInput;
}

void MainView::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId)); // clear the background
}

void MainView::resized()
{
    auto b = getLocalBounds();
    auto controlPane = b.removeFromLeft(150).reduced(5);
    
    r.setBounds(b);
    auto padding = 5;
    
    auto widthPane  = controlPane.removeFromTop(30);
    auto heightPane = controlPane.removeFromTop(30);
    auto depthPane  = controlPane.removeFromTop(30);
    controlPane.removeFromTop(padding);
    
    auto findDataPane  = controlPane.removeFromTop(30);
    auto sideViewPane  = controlPane.removeFromTop(180);
    auto frontViewPane = controlPane.removeFromTop(180);
    
    labelWidth .setBounds (widthPane.removeFromLeft(widthPane.getWidth() * 0.5));
    editorWidth.setBounds (widthPane);
    
    labelHeight .setBounds (heightPane.removeFromLeft(heightPane.getWidth() * 0.5));
    editorHeight.setBounds (heightPane);
    
    labelDepth .setBounds (depthPane.removeFromLeft(depthPane.getWidth() * 0.5));
    editorDepth.setBounds (depthPane);
    
    buttonMirror  .setBounds (findDataPane.removeFromLeft(20));
    buttonFindData.setBounds (findDataPane.removeFromRight(50));
    
    sideViewPane.removeFromTop(10);
    buttonChangeSideView.setBounds(sideViewPane.removeFromTop(30).removeFromRight(50));
    sideView.setBounds(sideViewPane);
    
    frontViewPane.removeFromTop(10);
    buttonChangeFrontView.setBounds(frontViewPane.removeFromTop(30).removeFromRight(50));
    frontView.setBounds(frontViewPane);
}
