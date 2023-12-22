#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CIRCLE_RADIUS = 20;

class Circle {
public:
    Circle(float x, float y, float radius, float vx, float vy) : x(x), y(y), radius(radius), vx(vx), vy(vy) {
        font = TTF_OpenFont("arial.ttf", 16); // Try to open the specified font
        if (!font) {
            std::cerr << "Error: Unable to load font - " << TTF_GetError() << std::endl;
            std::cerr << "Using default font." << std::endl;

            // Use a default font (e.g., system font)
            font = TTF_OpenFont(nullptr, 16);
            if (!font) {
                std::cerr << "Error: Unable to load default font - " << TTF_GetError() << std::endl;
                // Handle the error, exit, or use a different default font
            }
        }
    }

    ~Circle() {
        TTF_CloseFont(font);
    }

    void update() {
        x += vx;
        y += vy;

        float dampening = 0.9f;

        if (x - radius < 0) {
            x = radius;
            vx = -vx * dampening;
        } else if (x + radius > SCREEN_WIDTH) {
            x = SCREEN_WIDTH - radius;
            vx = -vx * dampening;
        }
        if (y - radius < 0) {
            y = radius;
            vy = -vy * dampening;
        } else if (y + radius > SCREEN_HEIGHT) {
            y = SCREEN_HEIGHT - radius;
            vy = -vy * dampening;
        }
    }

    void render(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        draw_circle(renderer, x, y, radius);

        SDL_Rect textRect;
        textRect.x = SCREEN_WIDTH - 100;
        textRect.y = 10;
        textRect.w = 90;
        textRect.h = 20;

        std::string velocityText = "Vx: " + std::to_string(vx) + " Vy: " + std::to_string(vy);
        render_text(renderer, velocityText.c_str(), textRect);
    }

private:
    float x, y;
    float radius;
    float vx, vy;
    TTF_Font* font;

    void draw_circle(SDL_Renderer* renderer, float x, float y, float radius) const {
        // (Unchanged) Function to draw a circle on the renderer
    }

    void render_text(SDL_Renderer* renderer, const char* text, SDL_Rect rect) const {
        SDL_Surface* surface = nullptr;
        SDL_Texture* texture = nullptr;

        SDL_Color textColor = {255, 255, 255, 255};

        surface = TTF_RenderText_Solid(font, text, textColor);
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_RenderCopy(renderer, texture, NULL, &rect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
};

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        circle.render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();

    return 0;
}
