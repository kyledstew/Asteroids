/***********************************************************************
 * Source File:
 *    Ship: Class for ship, derived class of FlyingObject
 * Author:
 *    Kyle Stewart
 * Summary:
 *    Contains all elements for ship, setting unique variables from
 *    FlyingObject
 ************************************************************************/

#include "ship.h"

/*********************************************
 * SHIP CONSTRUCTOR
 * Set characteristics of ship
 *********************************************/
Ship :: Ship()
{
   setRadius(SHIP_SIZE); // Set radius
   
   // For extra features, set properties for the Force Field
   forceFieldOn = false;
   
   rotation = 0;
}

/*********************************************
 * SHIP :: DRAW
 * Draw the Ship, and forceField if on
 *********************************************/
void Ship :: draw()
{
   drawShip(point, rotation);
   if (isForceFieldOn()) // Check for Force Field
   {
      if (!fazeOut()) // If it isn't time to faze out..
         drawCircle(point, 15);
   }
}

/*********************************************
 * SHIP :: MOVEUP
 * Moves ship the direction it is facing
 *********************************************/
void Ship :: moveUp()
{
   // Move the ship up
   point.setX(point.getX() - (sin(M_PI / 180.0 * rotation)));
   point.setY(point.getY() - (-cos(M_PI / 180.0 * rotation)));
   
   // Change the velocity
   velocity.setDx(velocity.getDx() - (sin(M_PI / 180.0 * rotation)) * THRUST_AMOUNT);
   velocity.setDy(velocity.getDy() - (-cos(M_PI / 180.0 * rotation)) * THRUST_AMOUNT);
   
}

/*********************************************
 * SHIP :: MOVEDOWN
 * Moves ship the opposite direction it is facing
 *********************************************/
void Ship :: moveDown()
{
   // Move the ship down
   point.setX(point.getX() + (sin(M_PI / 180.0 * rotation)));
   point.setY(point.getY() + (-cos(M_PI / 180.0 * rotation)));
   
   // Change the velocity
   velocity.setDx(velocity.getDx() + (sin(M_PI / 180.0 * rotation)) * THRUST_AMOUNT);
   velocity.setDy(velocity.getDy() + (-cos(M_PI / 180.0 * rotation)) * THRUST_AMOUNT);
}

/*********************************************
 * SHIP :: MOVERIGHT
 * Changes the direction of ship to right
 *********************************************/
void Ship :: moveRight()
{
   // Change rotation to the right
   rotation -= ROTATE_AMOUNT;
   
   // Draw ship with the new rotation
   drawShip(point, rotation);
   
}

/*********************************************
 * SHIP :: MOVELEFT
 * Changes the direction of ship to left
 *********************************************/
void Ship :: moveLeft()
{
   // Change rotation to the left
   rotation += ROTATE_AMOUNT;
   
   // Draw ship with the new rotation
   drawShip(point, rotation);
}

/*********************************************
 * SHIP :: FAZEOUT 
 * return true when to not display
 * force field, signalling end of feature
 *********************************************/
bool Ship :: fazeOut()
{
   if ((forceFieldLife <= 100 && forceFieldLife >= 95)
       || (forceFieldLife <= 50 && forceFieldLife >= 45)
       || (forceFieldLife <= 25 && forceFieldLife >= 21)
       || (forceFieldLife <= 15 && forceFieldLife >= 12)
       || (forceFieldLife <= 9 && forceFieldLife >= 6)
       || (forceFieldLife <= 4 && forceFieldLife >= 2))
      return true; // Time to start fading
   else
      return false;
}

/*********************************************
 * SHIP :: ADVANCE
 * Advance the bullet each frame
 *********************************************/
void Ship :: advance()
{
   if (isAlive()) // If alive,
   {
      FlyingObject :: advance(); // advance
      
      if (isForceFieldOn()) // if force field is on
         forceFieldLife--;  // decrease it's life
      
      if (forceFieldLife == 0) // if reaches zero
         setForceFieldOn(false); // turn it off
   }
  
}



