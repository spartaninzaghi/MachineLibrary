/**
 * @file Drawable.h
 * @author Charles Owen
 * @author Mate Narh
 *
 * Abstract base class for drawable elements of our picture.
 */

#ifndef CANADIANEXPERIENCE_DRAWABLE_H
#define CANADIANEXPERIENCE_DRAWABLE_H

#include "AnimChannelAngle.h"

class Actor;
class Timeline;

/**
 * Abstract base class for drawable elements of our picture.
 *
 * A drawable is one part of an actor. Drawable parts can be moved
 * independently.
 */
class Drawable {
private:
    /// The drawable name
    std::wstring mName;

    /// The position of this drawable relative to its parent
    wxPoint mPosition = wxPoint(0, 0);

    /// The rotation of this drawable relative to its parent
    double mRotation = 0;

    /// The actor using this drawable
    Actor *mActor = nullptr;

    /// The parent drawable
    Drawable *mParent = nullptr;

    /// The child drawables
    std::vector<std::shared_ptr<Drawable>> mChildren;

    /// The animation channel for animating the angle of this drawable
    AnimChannelAngle mChannel;

protected:
    Drawable(const std::wstring &name);
    wxPoint RotatePoint(wxPoint point, double angle);


    /// The actual postion in the drawing
    wxPoint mPlacedPosition = wxPoint(0, 0);

    /// The actual rotation in the drawing
    double mPlacedR = 0;

public:
    virtual ~Drawable() {}

    /** Default constructor disabled */
    Drawable() = delete;
    /** Copy constructor disabled */
    Drawable(const Drawable &) = delete;
    /** Assignment operator disabled */
    void operator=(const Drawable &) = delete;

    virtual void SetActor(Actor *actor);

    /**
     * Get the actor for this drawable
     * @return the actor for this drawable
     */
    Actor *GetActor() const { return mActor; }

    /**
     * Draw this drawable
     * @param graphics Graphics object to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    void Place(wxPoint offset, double rotate);

    void AddChild(std::shared_ptr<Drawable> child);

    /**
     * Display the machine selection dialog box
     * @param parent Parent window for the dialog box
     */
    virtual void DoDialog(wxWindow *parent) {}

    /**
     * Save this drawable to an XML node
     * @param node The node we are going to be a child of
     */
    virtual void XmlSave(wxXmlNode* node) {}

    /**
    * Load this drawable from XML
    * @param node XML node to load from
    */
    virtual void XmlLoad(wxXmlNode* node) {}

    /**
     * Set the start time for this drawable
     * @param time The new start time
     */
    virtual void SetStartTime(double time) {}

    /**
     * Get the start time for this drawable
     * @return The start time for this drawable
     */
    virtual double GetStartTime() const { return 0; }

    /**
     * Test to see if we have been clicked on by the mouse
     * @param pos Position to test
     * @return true if clicked on
     */
    virtual bool HitTest(wxPoint pos) = 0;

    /**
     * Is this a movable drawable?
     * @return true if movable
     */
    virtual bool IsMovable() { return false; }

    void Move(wxPoint delta);

    /**
     * Set the drawable position
     * @param pos The new drawable position
     */
    virtual void SetPosition(wxPoint pos) { mPosition = pos; } // virtualized

    /**
     * Get the drawable position
     * @return The drawable position
     */
    virtual wxPoint GetPosition() const { return mPosition; } // virtualized

    /**
     * Set the rotation angle in radians
    * @param r The new rotation angle in radians
     */
    void SetRotation(double r) { mRotation = r; }

    /**
     * Get the rotation angle in radians
     * @return The rotation angle in radians
     */
    double GetRotation() const { return mRotation; }

    /**
     * Get the drawable name
     * @return The drawable name
     */
    std::wstring GetName() const { return mName; }

    /**
     * Set the drawable parent
     * @param parent New parent pointer
     */
    void SetParent(Drawable *parent) { mParent = parent; }

    /**
     * Get the drawable parent
     * @return Parent pointer
     * */
    Drawable *GetParent() { return mParent; }

    virtual void SetTimeline(Timeline *timeline);
    virtual void SetKeyframe();
    virtual void GetKeyframe();

    /**
     * The angle animation channel
     * @return Pointer to animation channel
     */
    AnimChannelAngle *GetAngleChannel() { return &mChannel; }
};

#endif //CANADIANEXPERIENCE_DRAWABLE_H
