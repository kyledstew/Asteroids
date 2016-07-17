  /***********************************************************************
 * Header File:
 *    FlyingObject: Class for bullets
 * Author:
 *    Kyle Stewart
 * Summary:
 *    Base Class for all flying Objects (rocks, ship, bullet)
 ************************************************************************/

#ifndef flyingObject_h
#define flyingObject_h

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

class FlyingObject
{
public:
   
   /*********************************************
    * CONSTRUCTOR
    * Sets FlyingObject to alive
    *********************************************/
   FlyingObject() : alive(true) {}
   
   /*********************************************
    * GETTERS
    * Getter functions for variables used in game.cpp
    *********************************************/
   Point getPoint() const                 {return point;}
   Velocity getVelocity() const           {return velocity;}
   int getRadius() const                  {return radius;}
   float getDx() const                    {return velocity.getDx();}
   float getDy() const                    {return velocity.getDy();}

   /*********************************************
    * SETTERS
    * Setter functions for variables
    *********************************************/
   void setPoint(Point point)             {this->point = point;}
   void setVelocity(Velocity velocity)    {this->velocity = velocity;}
   void setRadius(int radius)             {this->radius = radius;}
   
   /*********************************************
    * Function: kill
    * Description: Set alive to false
    *********************************************/
   void kill()                            {alive = false;}
   
   /*********************************************
    * Function: isAlive
    * Descrition: Return whether FlyingObject is alive or not
    *********************************************/
   bool isAlive() const                   {return alive;}
   
   /*********************************************
    * VIRTUAL FUNCTIONS
    * ADVANCE - Advance FlyingObject
    * DRAW - Pure Virtual, draw FlyingObject
    *********************************************/
   virtual void advance();
   virtual void draw() = 0;
   
protected:
   Point point;            // Point of FlyingObject
   Velocity velocity;      // Velocity of FlyingObject
   bool alive;             // is FlyingObject alive?
   int radius;             // used for wrapping smoothly
   
};

#endif /* flyingObject_h */
