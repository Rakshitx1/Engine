#include <iostream>
#include <SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CIRCLE_RADIUS = 20;
float dampening = 0.9f; // Dampening factor
float gravity = 0.1f;   // Gravity factor

class Circle {
public:
    Circle(float x, float y, float radius, float vx, float vy)
        : x(x), y(y), radius(radius), vx(vx), vy(vy), selected(false) {}

    void update() {
        if (selected) {
            // If the circle is selected, update its position based on the mouse
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            x = static_cast<float>(mouseX);
            y = static_cast<float>(mouseY);
        } else {
            x += vx;
            vy += gravity;
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
    }

    void render(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
        draw_circle(renderer, x, y, radius);
    }

    void select() {
        selected = true;
    }

    void unselect() {
        selected = false;
    }

    // Function to draw a circle on the renderer
    void draw_circle(SDL_Renderer* renderer, float x, float y, float radius) const {
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

    // Getter functions for x and y positions
    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    // Function to check if the circle is selected
    bool isSelected() const {
        return selected;
    }

private:
    float x, y;            // Circle center coordinates
    float radius;
    float vx, vy;          // Velocity components
    bool selected;         // Flag to indicate if the circle is selected
};

int main() {
    std::cout << "Enter dampening factor (e, default 0.9): ";
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
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    if (!circle.isSelected()) {
                        circle.select(); // Select the circle on spacebar press
                    } else {
                        circle.unselect(); // Unselect the circle on spacebar press
                    }
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                // Left-click to toggle the selection of the circle
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                float circleX = circle.getX();
                float circleY = circle.getY();
                if (mouseX >= circleX - CIRCLE_RADIUS && mouseX <= circleX + CIRCLE_RADIUS &&
                    mouseY >= circleY - CIRCLE_RADIUS && mouseY <= circleY + CIRCLE_RADIUS) {
                    if (!circle.isSelected()) {
                        circle.select();
                    } else {
                        circle.unselect();
                    }
                }
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

    return 0;
}
