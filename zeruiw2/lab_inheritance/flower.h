/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 */

#ifndef FLOWER_H_
#define FLOWER_H_

#include "shape.h"

class Flower : public Drawable
{
public:
    Shape* stem;
    Shape* pistil; // center piece of flower
    Shape* leaf;
    void clear();
    void drawPetals(PNG* canvas, const Vector2& center, int x, int y) const;

    Flower(const Vector2& center);
    void draw(PNG* canvas) const ;

    virtual ~Flower();
};

#endif // FLOWER_H_
