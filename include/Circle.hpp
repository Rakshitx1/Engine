#pragma once

#include <SDL.h>

class Circle {
public:
    Circle(float x, float y, float radius, float vx, float vy);

    void update();

    void render(SDL_Renderer* renderer) const;

    // Function to draw a circle on the renderer
    void draw_circle(SDL_Renderer* renderer, float x, float y, float radius) const;

    // Getter functions for x and y positions
    float getX() const;

    float getY() const ;

    // Function to set the position of the circle
    void setPosition(float newX, float newY);

private:
    float x, y;            // Circle center coordinates
    float radius;
    float vx, vy;          // Velocity components
};
