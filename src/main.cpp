#include <iostream>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CIRCLE_RADIUS = 20;

class Circle {
public:
    Circle(int x, int y, int radius, int vx, int vy) : x(x), y(y), radius(radius), vx(vx), vy(vy) {}

    void update() {
        x += vx;
        y += vy;

        // Check for collisions with the bounding box
        if (x - radius < 0 || x + radius > SCREEN_WIDTH) {
            vx = -vx; // Reflect velocity on X-axis
        }
        if (y - radius < 0 || y + radius > SCREEN_HEIGHT) {
            vy = -vy; // Reflect velocity on Y-axis
        }
    }

    void render(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
        draw_circle(renderer, x, y, radius);
    }

private:
    int x, y; // Circle center coordinates
    int radius;
    int vx, vy; // Velocity components

    // Function to draw a circle on the renderer
    void draw_circle(SDL_Renderer* renderer, int x, int y, int radius) const {
        int d = 3 - 2 * radius;
        int xPos = 0;
        int yPos = radius;

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
};

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("2D Physics Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Circle circle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CIRCLE_RADIUS, 5, 5);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        circle.update();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set the clear color to black
        SDL_RenderClear(renderer); // Clear the renderer

        circle.render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Add a small delay to control the frame rate
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
