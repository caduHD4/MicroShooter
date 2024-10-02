#ifndef object_hpp
#define object_hpp

#include <stdio.h>
#include <iostream>
#include "math-vector.h"
#include "sprite.hpp"

using Vector = Mylib::Math::Vector<float, 2>;
class Object {
protected:
    int life;
    float height;
    float width;
    Vector speed;
    Vector position;
    Sprite* sprite;

public:
    Vector getSpeed() {
        return this->speed;
    }
    void setSpeed(Vector speed) {
        this->speed = speed;
    }
    Vector getPosition() {
        return this->position;
    }
    void setPosition(Vector position) {
        this->position = position;
    }
    int getLife() {
        return this->life;
    }
    void setLife(int life) {
        this->life = life;
    }
    float getWidth() {
        return this->width;
    }
    void setWidth(float width) {
        this->width = width;
    }
    float getHeight() {
        return this->height;
    }
    void setHeight(float height) {
        this->height = height;
    }

    // Método para mover o objeto
    virtual void move(float frameTime) {
        this->position.x += this->speed.x * frameTime;
        this->position.y += this->speed.y * frameTime;
    }

    void moveLeft(float frameTime) {
        this->position.x -= this->speed.x * frameTime;
        sprite->update(frameTime);
    }

    void moveRight(float frameTime) {
        this->position.x += this->speed.x * frameTime;
        sprite->update(frameTime);
    }

    void moveUp(float frameTime) {
        this->position.y -= this->speed.y * frameTime;
        sprite->update(frameTime);
    }

    void moveDown(float frameTime) {
        this->position.y += this->speed.y * frameTime;
        sprite->update(frameTime);
    }

};
#endif