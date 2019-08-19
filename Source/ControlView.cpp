/*
  ==============================================================================

    LineArrayControlUI.cpp
    Created: 23 Aug 2017 12:48:40pm
    Author:  Mike

  ==============================================================================
*/

#include "ControlView.h"
#include "ffc/ffc.h"
#include "Element.h"

//==============================================================================
//LineArrayControlUI::LineArrayControlUI (LineArray &lineArray, Model &model, const Array <float>& splayAngles)
//: selectedIndex (-1)
//, lineArray (lineArray)
//, model     (model)
//, splayAngles (splayAngles)
//{
//    addAndMakeVisible (splayAngleSelector = new ClickableSegments);
//    addMouseListener (splayAngleSelector, false);
//    splayAngleSelector->addListener (this);
//
//    generateAimPaths ();
//}

void ControlView::paint (Graphics& g)
{
    drawElementImages (g);
//    drawAimPaths (g);
}
//
//void LineArrayControlUI::resized ()
//{
//    splayAngleSelector->setBounds (getLocalBounds());
//}

//void LineArrayControlUI::mouseUp (const MouseEvent& event)
//{
//    const auto newIndex = getElementIndex (event);
//    selectElement (newIndex);
//}
//
//void LineArrayControlUI::selectedStateChanged (ClickablePaths& paths)
//{
//    if (&paths == splayAngleSelector)
//    {
//        selectSplayAngle (paths);
//    }
//}

//bool LineArrayControlUI::noPathsSelected () const 
//{
//    return selectedIndex <= -1;
//}
//
//void LineArrayControlUI::hide ()
//{
//    selectedIndex = -1;
//    splayAngleSelector->setPaths (Array <Path>());
//    resized ();
//}
//
//AffineTransform transformForElement(ElementView &view)
//{
//    auto image = view.side; // add new class with JUCE dependency that contains image etc
//    auto element = view.element;
//    // can we remove all this calculation and just use the elements hangpoints etc?
//    // they can be calculated by the library
//    const auto imageBounds     = Rectangle <int>    {0, 0, image.getWidth(), image.getHeight()}.toFloat();
//    const auto targetBoundsInM = Rectangle <double> {element.hangPoint.x - element->getDepth(),
//        element->hangPoint.y - (element.splayInverted ? element->getHeight() : 0.0),
//        element->getDepth(), element->getHeight()};
//    
//    //        auto targetBoundsInM = Rectangle <double> {model.arrayX () + model.isFlown() ? element->bottomPoint.x : element->hangPoint.x,
//    //                                                   model.arrayY () + model.isFlown() ? element->bottomPoint.y : element->hangPoint.y,
//    //                                                   element->getDepth(), element->getHeight()};
//    //
//    auto targetBounds = Renderer::getRectPxFromRectM (targetBoundsInM, getLocalBounds (), model.sizeInM ()).toFloat();
//    
//    currentAngle += static_cast <float> (element.splayAngle);
//    
//    auto transform = juce::RectanglePlacement().getTransformToFit (imageBounds, targetBounds);
//    const auto rotationPoint = model.isFlown() ? targetBounds.getTopRight() : targetBounds.getBottomRight();
//    
//    transform = transform.rotated (juce::degreesToRadians (currentAngle), rotationPoint.x, rotationPoint.y);
//}

void ControlView::drawElementImages (Graphics& g)
{
//    g.setColour (Colours::black);
//
//       elementBounds.clearQuick();
//    cumulativeAngles.clearQuick();
//
//    auto currentAngle = static_cast <float> (lineArray.getModel().splayAngle (-1));
//    cumulativeAngles.add (currentAngle);
//
//    for (auto i=0; i < lineArray.internal->elements.size(); ++i)
//    {
//
//        
//           elementBounds.add (targetBounds);
//        cumulativeAngles.add (currentAngle);
//        
//        g.setOpacity (i == selectedIndex ? 1.f : 0.5f);
//        g.drawImageTransformed (image, transform);
//    }
//    generateAimPaths ();
}
//
//void LineArrayControlUI::drawAimPaths (Graphics& g)
//{
//    g.setColour (Colours::white.withAlpha (0.8f));
//
//    for (auto& line : aimPaths)
//    {
//        g.strokePath (line, PathStrokeType (0.5f));
//    }
//}
//
//int LineArrayControlUI::getElementIndex (const MouseEvent& event) const
//{
//    for (auto i = 0; i < elementBounds.size(); ++i)
//    {
//        auto element = elementBounds [i];
//        if (element.contains (event.position.x, event.position.y))
//            return i;
//    }
//    return -1;
//}
//
//void LineArrayControlUI::selectSplayAngle (ClickablePaths& paths) const
//{
//    if (selectedIndex < 0 || selectedIndex >= lineArray.internal->elements.size())
//            return;
//
//        const auto selectedPath = paths.getSelectedIndex();
//    
//        if (selectedPath < 0 || selectedPath >= splayAngles.size())
//            return;
//
//        const auto splay = splayAngles [selectedPath];
//        model.setSplayAngle (selectedIndex, splay);
//        lineArray.internal->recalc();
//}
//
//void LineArrayControlUI::selectElement (int newIndex)
//{
//    if (newIndex != selectedIndex)
//    {
//        selectedIndex = newIndex;
//        DBG ("LineArrayControlUI::mouseUp selectedIndex " << selectedIndex);
//        generateAimPaths ();
//        generateSplayPaths ();
//        resized ();
//    }
//}
//
//static Path getSplayPath (Point <float> startPoint, float angle, float endX)
//{
//    const auto endPoint = Point <float> {endX, startPoint.y + (endX - startPoint.x) * tan (degreesToRadians (angle))};
//
//    Path p;
//    p.startNewSubPath (startPoint.x, startPoint.y);
//    p.lineTo (endPoint);
//    return p;
//}
//
//void LineArrayControlUI::generateSplayPaths ()
//{
//    splayPaths.clearQuick();
//
//    if (noPathsSelected ())
//    {
//        hide ();
//        return;
//    }
//
//    if (selectedIndex >= lineArray.internal->elements.size())
//        return;
//
//    auto pt = lineArray.internal->elements [selectedIndex]->acousticCentre;
//    pt.x += model.arrayX ();
//    pt.y += model.arrayY ();
//
//    auto startPt = Renderer::getPxFromM (pt, getLocalBounds(), model.sizeInM());
//    const auto endX = getLocalBounds().getRight() - 20.f;
//
//    for (auto angle : splayAngles)
//    {
//        angle = model.isFlown() ? angle : -angle;
//        splayPaths.add (getSplayPath (startPt.toFloat(), angle + cumulativeAngles [selectedIndex], endX));
//    }
//
//    splayAngleSelector->setPaths (splayPaths);
//
//    const auto splay = lineArray.internal->elements [selectedIndex]->getSplayAngle();
//    splayAngleSelector->setSelectedIndex (splayAngles.indexOf (static_cast <float> (model.isFlown() ? splay : -splay)));
//}
//
//void LineArrayControlUI::generateAimPaths ()
//{
//    aimPaths.clearQuick ();
//
//    for (auto i = 0; i < lineArray.internal->elements.size(); ++i)
//    {
//        if (i == selectedIndex)
//            continue;
//
//        const auto element = lineArray.internal->elements [i];
//        auto pt = element->acousticCentre;
//        pt.x += model.arrayX ();
//        pt.y += model.arrayY ();
//
//        auto startPt = Renderer::getPxFromM (pt, getLocalBounds(), model.sizeInM());
//        const auto endX = getLocalBounds().getRight() - 20.f;
//        auto angle = static_cast <float> (element->getSplayAngle());
//        angle = model.isFlown() ? angle : -angle;
//
//        aimPaths.add (getSplayPath (startPt.toFloat(), angle + cumulativeAngles [i], endX));
//    }
//}
//
