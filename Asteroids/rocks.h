/***********************************************************************
 * Header File:
 *    Rock: Base class for all asteroids
 *    BigRock: Class for Big Asteroids
 *    MediumRock: Class for Medium Asteroids
 *    SmallRock: Class for Small Asteroids
 * Author:
 *    Kyle Stewart
 * Summary:
 *    Includes everything for each of the Asteroids
 ************************************************************************/

#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#define SPECIAL_ROCK_SIZE 5
#define SPECIAL_ROCK_SPEED 4

#include <vector>

#include "flyingObject.h"
#include "uiDraw.h"

//   Rock
class Rock : public FlyingObject
{
public:
   /*********************************************
    * CONSTRUCTOR
    *********************************************/
   Rock() : spin(0) {}
   
   /*********************************************
    * Function: VIRTUAL - draw
    * Description: Draw the Rock
    *********************************************/
   virtual void draw() {}
   
   /*********************************************
    * Function: VIRTUAL - breakRock
    * Description: Break the rock, return array with debri rocks
    *********************************************/
   virtual std::vector<Rock*> breakRock() const = 0;
   
protected:
   int spin; // Spin of the rock

};

//   BigRock
class BigRock : public Rock
{
public:
   /*********************************************
    * CONSTRUCTOR
    * Sets BigRock to the appropriate characteristics
    *********************************************/
   BigRock();
   
   /*********************************************
    * Function: VIRTUAL - draw 
    * Description: Draw the BigRock
    *********************************************/
   virtual void draw();
   
   /*********************************************
    * Function: VIRTUAL - breakRock
    * Description: Break the BigRock, return two 
    * MediumRocks and one SmallRock
    *********************************************/
   virtual std::vector<Rock*> breakRock() const;
};

//   MediumRock
class MediumRock : public Rock
{
public:
   /*********************************************
    * CONSTRUCTOR
    * Sets BigRock to the appropriate characteristics
    * from BigRock
    *********************************************/
   MediumRock(const Point point, const Velocity velocity);
   
   /*********************************************
    * Function: VIRTUAL - draw
    * Description: Draw the MediumRock
    *********************************************/
   virtual void draw();

   /*********************************************
    * Function: VIRTUAL - breakRock
    * Description: Break the MediumRock, return two SmallRocks
    *********************************************/
   virtual std::vector<Rock*> breakRock() const;
};

//   SmallRock
class SmallRock : public Rock
{
public:
   /*********************************************
    * CONSTRUCTOR
    * Sets BigRock to the appropriate characteristics
    * from MediumRock
    *********************************************/
   SmallRock(const Point point, const Velocity velocity);
   
   /*********************************************
    * Function: VIRTUAL - draw
    * Description: Draw the MediumRock
    *********************************************/
   virtual void draw();
   
   /*********************************************
    * Function: VIRTUAL - breakRock
    * Description: Break the SmallRock, but return 
    * nothing - no debri!
    *********************************************/
   virtual std::vector<Rock*> breakRock() const;
};

//   SpecialRock
class SpecialRock : public Rock
{
public:
   /*********************************************
    * CONSTRUCTOR
    * Sets Characteristics of SpecialRock;
    *********************************************/
   SpecialRock();
   
   /*********************************************
    * Function: VIRTUAL - Draw 
    * Description: Draw the SpecialRock
    *********************************************/
   virtual void draw();
   
   /*********************************************
    * Function: VIRTUAL - breakRock
    * Description: Break the SpecialRock, but 
    * return nothing - no debri!
    *********************************************/
   virtual std::vector<Rock*> breakRock() const;
};

#endif /* rocks_h */
