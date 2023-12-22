#include <iostream>
#include <SDL.h>

#include "include/Circle.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CIRCLE_RADIUS = 20;
float dampening = 0.9f; // Dampening factor
float gravity = 0.1f;   // Gravity factor

int main() {
    std::cout << "Enter dampening factor (default 0.9): ";
    std::string dampeningInput;
    std::getline(std::cin, dampeningInput);

    // Use default value if the input is empty
    dampening = dampeningInput.empty() ? 0.9f : std::stof(dampeningInput);

    std::cout << "Enter gravity factor (default 0.1): ";
    std::string gravityInput;
    std::getline(std::cin, gravityInput);

    // Use default value if the input is empty
    gravity = gravityInput.empty() ? 0.1f : std::stof(gravityInput);

    // Check dampening factor is between 0 and 1
    if (dampening < 0 || dampening > 1) {
        std::cerr << "Dampening factor must be between 0 and 1" << std::endl;
        return 1;
    }
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window =
        SDL_CreateWindow("2D Physics Engine", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                         SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Circle circle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CIRCLE_RADIUS, 5, 5);

    bool quit = false;
    bool paused = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    paused = !paused; // Toggle pause state
                } else if (paused) {
                    // If paused, allow the user to change the position
                    // of the circle using arrow keys
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            circle.setPosition(circle.getX(), circle.getY() - 5);
                            break;
                        case SDLK_DOWN:
                            circle.setPosition(circle.getX(), circle.getY() + 5);
                            break;
                        case SDLK_LEFT:
                            circle.setPosition(circle.getX() - 5, circle.getY());
                            break;
                        case SDLK_RIGHT:
                            circle.setPosition(circle.getX() + 5, circle.getY());
                            break;
                    }
                }
            }
        }

        if (!paused) {
            circle.update();
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        circle.render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
