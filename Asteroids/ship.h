/***********************************************************************
 * Header File:
 *    Ship: Class for ship, derived class of FlyingObject
 * Author:
 *    Kyle Stewart
 * Summary:
 *    Contains all elements for ship, setting unique variables from
 *    FlyingObject
 ************************************************************************/

#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10
#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#include "flyingObject.h"

class Ship : public FlyingObject
{
public:
   /*********************************************
    * CONSTRUCTOR
    * When ship is created, set the SHIP_SIZE
    *********************************************/
   Ship();
   
   /*********************************************
    * Function: getRotation
    * Description: Get rotation, to be used in game.cpp
    *********************************************/
   int getRotation()                   {return rotation;}
   
   /*********************************************
    * Function: isForceFieldOn
    *           setForceFieldOn
                setForceFieldLife
    * Description: Get/Set Forcefield for extra features
    *********************************************/
   bool isForceFieldOn() const         {return forceFieldOn;}
   void setForceFieldOn(bool on)       {forceFieldOn = on;}
   void setForceFieldLife(int life)    {forceFieldLife = life;}
   
   /*********************************************
    * Function: VIRTUAL - draw
    * Description: Draw the Ship
    *********************************************/
   virtual void draw();
   
   /*********************************************
    * Function: VIRTUAL - advance
    * Description: Advance the ship each frame
    * Used to count life of forceField
    *********************************************/
   virtual void advance();
   
   /*********************************************
    * Functions:
    * moveUp - Moves ship the direction the ship is facing
    * moveDown - Moves ship the opposite direction
    * moveRight - Changes the direction of ship to right
    * moveLeft - Changes the direction of ship to left
    *********************************************/
   void moveUp();
   void moveDown();
   void moveRight();
   void moveLeft();
   
private:
   int rotation;   // Which direction the ship is facing
   int forceFieldLife; // Life of force field
   bool forceFieldOn;  // Is it on?
   
   /*********************************************
    * Function: faceOut
    * Description: Return true when to not display
    * force field, signalling end of feature
    *********************************************/
   bool fazeOut();
};

#endif /* ship_h */
