#ifndef bullet_hpp
#define bullet_hpp

#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "object.hpp"

class Bullet : public Object {
public:
    Bullet(Vector position);
};

#endif
