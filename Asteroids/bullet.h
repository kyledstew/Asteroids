/***********************************************************************
 * Header File:
 *    Bullet: Class for bullets
 * Author:
 *    Kyle Stewart
 * Summary:
 *    Includes eveything for the bullet class
 ************************************************************************/

#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "uiDraw.h"
#include "flyingObject.h"

class Bullet : public FlyingObject
{
public:
   /*********************************************
    * CONSTRUCTOR
    * Sets Bullet to input variables from ship
    *********************************************/
   Bullet(const Point point, const Velocity velocity, const int Rotation);
   
   /*********************************************
    * Function: draw
    * Description: Draw the bullet on the screen
    *********************************************/
   virtual void draw()
   {
      if (isAlive())  // Why not check again
         drawDot(getPoint());
   }
   
   /*********************************************
    * Function: advance
    * Description: Advance the bullet each frame
    *********************************************/
   virtual void advance();
   
private:
   int life;   // private variable to hold life of bullet
   
};



#endif /* bullet_h */
