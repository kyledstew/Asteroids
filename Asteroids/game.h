/***********************************************************************
 * Header File:
 *    Game: Class for the game
 * Author:
 *    Kyle Stewart
 * Summary:
 *    Description: Contains the implementaiton of the game class
 *    methods.
 ************************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>

#include "uiInteract.h"
#include "flyingObject.h"
#include "rocks.h"
#include "ship.h"
#include "bullet.h"

#define FORCE_FIELD_LIFE 300 // Used for ship

class Game
{
public:
   /*********************************************
    * CONSTRUCTOR
    * Initializes the game
    *********************************************/
   Game(Point tl, Point br);
   
   /*********************************************
    * DESTRUCTOR
    * Erases elements of the game
    *********************************************/
   ~Game();
   
   /*********************************************
    * Function: handleInput
    * Description: Takes actions according to whatever
    *  keys the user has pressed.
    *********************************************/
   void handleInput(const Interface & ui);
   
   /*********************************************
    * Function: advance
    * Description: Move everything forward one
    *  step in time.
    *********************************************/
   void advance();
   
   /*********************************************
    * Function: draw
    * Description: draws everything for the game.
    *********************************************/
   void draw(const Interface & ui);


private:
   Point topLeft;
   Point bottomRight;
   std::vector<Rock*> rocks;              // vector for rocks
   std::vector<Bullet*> bullets;          // vector for bullets
   Ship ship;                             // Ship!
   
   // EXTRA ELEMENTS
   bool gameOver;
   SpecialRock *specialRock;
   
   /*********************************************
    * Function: handleCollisions
    * Description: handles collisions between
    * FlyingObjects
    *********************************************/
   void handleCollisions();
   
   /*********************************************
    * Function: advance____
    * Description: calls advance functions for each
    * FlyingObjects
    *********************************************/
   void advanceBullets();
   void advanceRocks();
   void advanceShip();
   
   /*********************************************
    * Function: getClosestDistance
    * Description: calculates distance between two
    * FlyingObjects, returns as float
    *********************************************/
   float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;
   
   /****************************************
    * Function: cleanUpZombies
    * Description: Remove any dead objects 
    *    Take bullets/rocks out of the list, deallocate specialRock
    ****************************************/
   void cleanUpZombies();
   
   /***************************************
    * Function: displayText
    * Description: Displays input message to screen
    ***************************************/
   void displayText(const char &message);
   
};


#endif /* GAME_H */
