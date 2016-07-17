/***********************************************************************
 * Source File:
 *    Bullet: Class for bullets
 * Author:
 *    Kyle Stewart
 * Summary:
 *    Includes eveything for the bullet class
 ************************************************************************/

#include "bullet.h"

#include <cmath> // used for sin, cos, and M_PI

/***************************************
 * BULLET CONSTRUCTOR
 * Set characteristics of Bullet
 *  INPUT   point: Where does it originate from?
 *          velocity: How fast should it move?
 *          rotation: What direction should it take?
 ***************************************/
Bullet :: Bullet(const Point point, const Velocity velocity,const int rotation)
{
   life = BULLET_LIFE;              // Each bullet lives for 40 frames
   setRadius(1);                    // Used in wrapping, radius is only 1
   setPoint(point);                 // Set the point
   
   // Set the velocity/direction
   this->velocity.setDx(velocity.getDx() - (sin(M_PI / 180.0 * rotation)) * BULLET_SPEED);
   this->velocity.setDy(velocity.getDy() - (-cos(M_PI / 180.0 * rotation)) * BULLET_SPEED);
}

/*********************************************
 * BULLET :: ADVANCE
 * Advance the bullet to the next position
 * for each time it advances, descrease the life
 *********************************************/
void Bullet :: advance()
{
   if (isAlive())                // If alive,
   {
      FlyingObject :: advance(); // advance a frame
      life--;                    // then decrease the life
   }
   
   if (life == 0)                // If no more life, kill the bullet
      kill();
}