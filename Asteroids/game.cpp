/***********************************************************************
 * Source File:
 *    Game: Class for the game
 * Author:
 *    Kyle Stewart
 * Summary:
 *    Description: Contains the implementaiton of the game class
 *    methods.
 ************************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function
#include <limits>
#include <algorithm>

using namespace std;

#define NUM_OF_ROCKS 5
#define GAME_OVER "GAME OVER"
#define VICTORY "VICTORY!!!"

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)
: topLeft(tl), bottomRight(br)
{
   for (int i = 0; i < NUM_OF_ROCKS; i++)
   {
      rocks.push_back(new BigRock);
   }
   
   specialRock = NULL;
   
}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
   // Unalocate the space for specialRock
   if(specialRock != NULL)
   {
      delete specialRock;
   }
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
   // Draw ship if alive
   if (ship.isAlive())
   {
      ship.draw();
   }
   
   // Iterator for rocks
   for (vector <Rock*> :: iterator it = rocks.begin(); it < rocks.end(); ++it)
   {
      if ((*it)->isAlive()) // Draw if alive
         (*it)->draw();
   }
   
   
   // Iterator for each bullet
   for (vector <Bullet*> :: iterator it = bullets.begin(); it < bullets.end(); ++it)
   {
      if ((*it)->isAlive()) // Draw if alive
         (*it)->draw();
   }
   
   if (specialRock != NULL && specialRock->isAlive())
   {
      specialRock->draw();
   }
   
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   if (!gameOver) // If game isn't over
   {
      advanceRocks();   // Advance like normal
      advanceBullets();
      advanceShip();
      
      handleCollisions(); // Handle collisions, break rocks, etc.
      cleanUpZombies();
   }
   else // Else game is over, user lost.
   {
      string message = GAME_OVER;         // Set message,
      const char * c = message.c_str();   // Convert to char
      displayText(*c);                    // Display the text
   }
}

/***************************************
 * GAME :: ADVANCE ROCKS
 * Go through each rock and advance it.
 ***************************************/
void Game :: advanceRocks()
{
   bool noRocks = true;
   // Iterator for all the rocks, if it exists then advance them
   for (vector <Rock*> :: iterator rit = rocks.begin(); rit < rocks.end(); ++rit)
   {
      (*rit)->advance();
      noRocks = false;
   }
   
   if (noRocks) // If no rocks, then all rocks have been destroyed
   {
      string message = VICTORY;   // Therefore, Victory!
      const char * c = message.c_str();
      displayText(*c);            // Pass text to function to display
   }
   
   // SpecialRock, extra feature
   if (specialRock == NULL && !ship.isForceFieldOn())
   {
      specialRock = new SpecialRock;
      ship.setForceFieldLife(FORCE_FIELD_LIFE);
   }
   else
   {
      if (specialRock != NULL && specialRock->isAlive())
      {
         specialRock->advance();
      }
   }
   
}

/***************************************
 * GAME :: ADVANCE BULLETS
 * Go through each bullet and advance it.
 ***************************************/
void Game :: advanceBullets()
{
   // Iterator for all bullets.
   for (vector <Bullet*> :: iterator it = bullets.begin(); it < bullets.end(); ++it)
   {
      if ((*it)->isAlive()) // If alive,
         (*it)->advance();  // then advance
      else
         it = bullets.erase(it); // if it's dead, then erase the item from the vector
   }
}

/***************************************
 * GAME :: ADVANCE SHIP
 * Do what it says, advance the ship.
 ***************************************/
void Game :: advanceShip()
{
   // If the ship is alive, then advance it
   if (ship.isAlive())
      ship.advance();
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between the ship and a rock, then each rock and each bullet.
 **************************************************************************/
void Game :: handleCollisions()
{
   // To be used in case of colission, vector will hold new rocks created
   vector<Rock*> appendRocks;
   
   // Iterator through all the rocks
   // Rit = it iterator for rock
   for (vector <Rock*> :: iterator rit = rocks.begin(); rit < rocks.end(); ++rit)
   {
      // Check contact with ship
      if (getClosestDistance(**rit, ship) <= ((*rit)->getRadius() + ship.getRadius()))
      {
         if (!ship.isForceFieldOn())
         {
            ship.kill(); // kill the ship
            gameOver = true;
         }
      }
      
      // Now check contact with each bullet
      // Bit = it iterator for bullet
      for (vector <Bullet*> :: iterator bit = bullets.begin(); bit < bullets.end(); ++bit)
      {
         // Check the distance between the rock (rit) and bullet (bit)
         if (getClosestDistance(**rit, **bit) <= ((*rit)->getRadius() + (*bit)->getRadius()))
         {
            // Kill and erase the bullet
            (*bit)->kill();
            
            // Contact made, break up rock!
            // In case of two rocks breaking up on same frame, we...
            vector<Rock*> newRocks;             // Create a new vector
            newRocks = (*rit)->breakRock();     // Set new rocks to vector
            appendRocks.insert(appendRocks.end(), newRocks.begin(), newRocks.end());  // Then insert to final vector
            
            // Kill the original rock, then erase it
            (*rit)->kill();
            
         }
         
         if (specialRock != NULL && specialRock->isAlive())
         {
            if (getClosestDistance(*specialRock, **bit) <= (specialRock->getRadius() + (*bit)->getRadius()))
            {
               specialRock->kill();    // Kill specialRock
               ship.setForceFieldOn(true); // Force field activated
            }
         }
      }
   }
   
   // Now that we're done going through each rock, add the newRocks onto the rocks vector
   rocks.insert(rocks.end(), appendRocks.begin(), appendRocks.end());
}

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets out of the list, deallocate bird)
 **************************************************************************/
void Game :: cleanUpZombies()
{
   // Look for dead bullets
   for (vector <Bullet*> :: iterator bit = bullets.begin(); bit < bullets.end(); ++bit)
      if (!(*bit)->isAlive())
      {
         // Delete the bullet
         delete (*bit);
         
         // remove from list
         bit = bullets.erase(bit);
      }
   
   // Look for dead rocks
   for (vector <Rock*> :: iterator rit = rocks.begin(); rit < rocks.end(); ++rit)
   {
      if (!(*rit)->isAlive())
      {
         // Delete the rock
         delete (*rit);
         
         // Remove from list
         rit = rocks.erase(rit);
      }
   }
   
   // check for dead specialRock
   if (specialRock != NULL && !specialRock->isAlive())
   {
      // Delete space allocated
      delete specialRock;
      
      // Assign the pointer to NULL
      specialRock = NULL;
      
   }
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
   // Handle each input
   if (ship.isAlive())
   {
      if (ui.isUp())
      {
         ship.moveUp();
      }
      if (ui.isDown())
      {
         ship.moveDown();
      }
      if (ui.isLeft())
      {
         ship.moveLeft();
      }
      if (ui.isRight())
      {
         ship.moveRight();
      }
      if (ui.isSpace())
      {
         // Add bullet to vector, pass the ship point, velocity, and rotation
         bullets.push_back(new Bullet(ship.getPoint(), ship.getVelocity(), ship.getRotation()));
      }
   }
}

/***************************************
 * GAME :: DISPLAYTEXT
 * Displays input message to screen
 ***************************************/
void Game :: displayText(const char &message)
{
   Point gameOverText(-40,0);
   drawText(gameOverText, &message);
}

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                   obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                   obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}


