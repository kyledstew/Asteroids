/***********************************************************************
 * Source File:
 *    Rock: Base class for all asteroids
 *    BigRock: Class for Big Asteroids
 *    MediumRock: Class for Medium Asteroids
 *    SmallRock: Class for Small Asteroids
 * Author:
 *    Kyle Stewart
 * Summary:
 *    Includes everything for each of the Asteroids
 ************************************************************************/

#include "rocks.h"

/***************************************
 * BIGROCK CONSTRUCTOR
 ***************************************/
BigRock :: BigRock()
{
   // Set the radius
   radius = BIG_ROCK_SIZE;
   
   // Set random point/velocity and variables
   point.setY(random(-200, 200));
   point.setX(random(-200, 200));
   
   // Set random angle, then apply to velocity
   float angle = random(10, 360);
   velocity.setDy(1 * (-cos(M_PI / 180.0 * angle)));
   velocity.setDx(1 * (sin(M_PI / 180.0 * angle)));
}

/*********************************************
 * BIGROCK :: DRAW
 * Draw the BigRock, applying the appropriate spin
 *********************************************/
void BigRock :: draw()
{
   // Apply spin
   spin += BIG_ROCK_SPIN;
   
   // Draw BigRock
   drawLargeAsteroid(point, spin);
   
}

/*********************************************
 * BIGROCK :: BREAK ROCK
 * Break the BigRock, return two MediumRocks
 * and one SmallRock
 *********************************************/
std::vector<Rock*> BigRock :: breakRock() const
{
   // Declare Vector
   std::vector<Rock*> rocks;
   
   // First Medium Rock
   Velocity firstMediumRockVelocity(getDx(), getDy()+1);
   rocks.push_back(new MediumRock(point, firstMediumRockVelocity));
   
   // Second Medium Rock
   Velocity secondMediumRockVelocity(getDx(), getDy()-1);
   rocks.push_back(new MediumRock(point, secondMediumRockVelocity));
   
   // Third, Small Rock
   Velocity thirdSmallRock(getDx()+2, getDy());
   rocks.push_back(new SmallRock(point, thirdSmallRock));
   
   // Return the vector
   return rocks;
}

/***************************************
 * MEDIUMROCK CONSTRUCTOR
 * Recieve point and velocity of BigRock
 ***************************************/
MediumRock :: MediumRock(const Point point, const Velocity velocity)
{
   // Set variables
   this->setPoint(point);
   this->setVelocity(velocity);
   radius = MEDIUM_ROCK_SIZE;
}

/*********************************************
 * MEDIUMROCK :: DRAW
 * Draw the MediumRock, applying the appropriate spin
 *********************************************/
void MediumRock :: draw()
{
   // Apply spin
   spin += MEDIUM_ROCK_SPIN;
   
   // Draw MediumRock
   drawMediumAsteroid(point, spin);
}

/*********************************************
 * MEDIUMROCK :: BREAK ROCK
 * Break the MediumRock, return two SmallRocks
 *********************************************/
std::vector<Rock*> MediumRock :: breakRock() const
{
   // Declare Vector
   std::vector<Rock*> rocks;
   
   // First Small Rock
   Velocity firstSmallRockVelocity(getDx()+3, getDy());
   rocks.push_back(new SmallRock(point, firstSmallRockVelocity));
   
   // Second Small Rock
   Velocity secondSmallRock(getDx()-3, getDy());
   rocks.push_back(new SmallRock(point, secondSmallRock));
   
   return rocks;
}

/***************************************
 * SMALLROCK CONSTRUCTOR
 * Recieve point and velocity of MediumRock
 ***************************************/
SmallRock :: SmallRock(const Point point, const Velocity velocity)
{
   // Set variables
   this->setPoint(point);
   this->setVelocity(velocity);
   radius = SMALL_ROCK_SIZE;
}

/*********************************************
 * SMALLROCK :: DRAW
 * Draw the SmallRock, applying the appropriate spin
 *********************************************/
void SmallRock :: draw()
{
   // Apply spin
   spin += SMALL_ROCK_SPIN;
   
   // Draw SmallRock
   drawSmallAsteroid(point, spin);
}

/*********************************************
 * SMALLROCK :: BREAK ROCK
 * Break the SmallRock, no new rocks to return
 *********************************************/
std::vector<Rock*> SmallRock :: breakRock() const
{
   // Declare Vector
   std::vector<Rock*> rocks;
   
   // No new rocks to return
   return rocks;
}

/***************************************
 * SMALLROCK CONSTRUCTOR
 * Recieve point and velocity of MediumRock
 ***************************************/
SpecialRock :: SpecialRock()
{
   // Set the radius
   radius = SPECIAL_ROCK_SIZE;
   
   // Set random point/velocity and variables
   point.setY(random(-200, 200));
   point.setX(random(-200, 200));
   
   // Set random angle, then apply to velocity
   float angle = random(10, 360);
   velocity.setDy((-cos(M_PI / 180.0 * angle)) * SPECIAL_ROCK_SPEED);
   velocity.setDx((sin(M_PI / 180.0 * angle)) * SPECIAL_ROCK_SPEED);
}

/*********************************************
 * SPECIALROCK :: DRAW
 * Draw the SmallRock, applying the appropriate spin
 *********************************************/
void SpecialRock :: draw()
{
   // Draw SmallRock
   drawSacredBird(point, radius);
}

/*********************************************
 * SPECIALROCK :: BREAKROCK
 * Break the SpecialRock, no new rocks to return
 *********************************************/
std::vector<Rock*> SpecialRock :: breakRock() const
{
   // Declare Vector
   std::vector<Rock*> rocks;
   
   // No new rocks to return
   return rocks;
}
