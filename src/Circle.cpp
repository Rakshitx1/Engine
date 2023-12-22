#include <iostream>
#include <SDL.h>

#include "include/Circle.hpp"

void Circle::update() {
    // Update velocity and position
    vx += ax;
    x += vx;
    vy += ay + gravity;
    y += vy;

    // Check for collisions with the bounding box
    if (x - radius < 0) {
        x = radius;
        vx = -vx * dampening; // Reflect velocity on X-axis
    } else if (x + radius > SCREEN_WIDTH) {
        x = SCREEN_WIDTH - radius;
        vx = -vx * dampening; // Reflect velocity on X-axis
    }
    if (y - radius < 0) {
        y = radius;
        vy = -vy * dampening; // Reflect velocity on Y-axis
    } else if (y + radius > SCREEN_HEIGHT) {
        y = SCREEN_HEIGHT - radius;
        vy = -vy * dampening; // Reflect velocity on Y-axis
    }
}

void Circle::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
    draw_circle(renderer, x, y, radius);
}

void Circle::draw_circle(SDL_Renderer* renderer, float x, float y, float radius) const {
    float d = 3 - 2 * radius;
    float xPos = 0;
    float yPos = radius;

    while (yPos >= xPos) {
        SDL_RenderDrawPoint(renderer, x + xPos, y - yPos);
        SDL_RenderDrawPoint(renderer, x - xPos, y - yPos);
        SDL_RenderDrawPoint(renderer, x + xPos, y + yPos);
        SDL_RenderDrawPoint(renderer, x - xPos, y + yPos);
        SDL_RenderDrawPoint(renderer, x + yPos, y - xPos);
        SDL_RenderDrawPoint(renderer, x - yPos, y - xPos);
        SDL_RenderDrawPoint(renderer, x + yPos, y + xPos);
        SDL_RenderDrawPoint(renderer, x - yPos, y + xPos);

        xPos++;

        if (d > 0) {
            yPos--;
            d = d + 4 * (xPos - yPos) + 10;
        } else {
            d = d + 4 * xPos + 6;
        }
    }
}

float Circle::getX() const {
    return x;
}

float Circle::getY() const {
    return y;
}

void Circle::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

