#ifndef TYPES_HPP
#define TYPES_HPP

struct Color {
    int r, g, b, a;
};

struct Vector {
    float x, y;

    Vector() : x(0), y(0) {}
    Vector(float x, float y) : x(x), y(y) {}

    Vector operator+(const Vector& other) const {
        return { x + other.x, y + other.y };
    }

    Vector operator-(const Vector& other) const {
        return { x - other.x, y - other.y };
    }

    Vector& operator+=(const Vector& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector& operator-=(const Vector& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};

struct Rect {
    Vector position;
    int width, height;

    Rect() : position(), width(0), height(0) {}
    Rect(Vector position, int width, int height) 
        : position(position), width(width), height(height) {}
};

#endif // TYPES_HPP
