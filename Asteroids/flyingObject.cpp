/***********************************************************************
 * Source File:
 *    FlyingObject: Class for bullets
 * Author:
 *    Kyle Stewart
 * Summary:
 *    Base Class for all flying Objects (rocks, ship, bullet)
 ************************************************************************/

#include "flyingObject.h"

/***************************************
 * FLYINGOBJECT :: ADVANCE
 * Advance each object, wrapping objects
 ***************************************/
void FlyingObject::advance()
{
   // Let velocity takes it's toll
   point.setX(point.getX() + velocity.getDx());
   point.setY(point.getY() + velocity.getDy());
   
   // Wrap objects, taking the object's radius into effect
   if (point.getX() < (-200-radius))
   {
      point.setX(200 + radius);
   }
   if (point.getX() > 200+radius)
   {
      point.setX(-200-radius);
   }
   if (point.getY() < -200-radius)
   {
      point.setY(200+radius);
   }
   if (point.getY() > 200+radius)
   {
      point.setY(-200-radius);
   }
}
