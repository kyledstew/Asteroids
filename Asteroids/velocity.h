/***********************************************************************
 * Header File:
 *    Velocity: Class for velocity, used in FlyingObject
 * Author:
 *    Kyle Stewart
 * Summary:
 *    Contains all elements to give each flying object the appropriate 
 *    velocity
 ************************************************************************/

#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{
public:
   /*********************************************
    * CONSTRUCTOR
    * Set up velovity to 0, or input variables
    *********************************************/
   Velocity() : Dx(0), Dy(0) {};
   Velocity(float x, float y) {this->Dx=x; this->Dy=y;}
   
   /*********************************************
    * GETTERS
    * Getter functions for Dx and Dy
    *********************************************/
   float getDx() const     {return Dx;}
   float getDy() const     {return Dy;}
   
   /*********************************************
    * SETTERS
    * Setter functions for Dx and Dy
    *********************************************/
   void setDx(float Dx)    {this->Dx = Dx;}
   void setDy(float Dy)    {this->Dy = Dy;}
   
private:
   float Dx; // Variable for X axis
   float Dy; // Variable for Y axis
   
};


#endif /* velocity_h */
