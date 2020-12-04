#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <string>

// EMSCRIPTEN WASM

#include <emscripten.h>

// FREETYPE2

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include FT_OUTLINE_H

// SDL2

#include <SDL.h>
#include <SDL_image.h>

#include "Color.h"
#include "Render.h"
#include "Image.h"
#include "Shape.h"
#include "Text.h"
#include "Cell.h"


// Memory
SDL_Window* window;
SDL_Surface* target;
Image* bg;
Image* grid;
Image* numbers;
Image* GUIbutton;
FT_Library ftLib;
FT_Face ftFace;
Text* title;
Text* footer;
Text* GUItext_create_new_game;
Text* GUItext_reset;
Text* GUItext_undo;
Text* GUItext_redo;
Text* GUItext_solution;
Cell board[9][9];


/*
    Function Prototypes
*/
void Init();
void DeInit();
void Input();
void Update();
void Draw();
void gameLoop();

/// Functions
void gameLoop() {
    Input();
    Update();
    Draw();
}

int main(int argc, char* argv[]) {
    Init();
    emscripten_set_main_loop(gameLoop, 0, 1); 	// Start game loop
    DeInit();

    return 0;
}

void Init() {
    // Init
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Sudoku", 1920 / 2 - 933 / 2, 1080 / 2 - 700 / 2, 933, 700, 0);

    // Setup
    target = SDL_GetWindowSurface(window);

    // Load PNG assets
    bg = new Image("assets/bg.png");
    if (!bg) {
        std::cerr << "Failed to load background image." << std::endl;
    }
    //grid = new Image("assets/lg_grid.png");
    grid = new Image("assets/images/Grid.png");
    if (!grid) {
        std::cerr << "Failed to load grid image." << std::endl;
    }
    numbers = new Image("assets/test_numbers.png");
    if (!grid) {
        std::cerr << "Failed to load image." << std::endl;
    }
    

    // Create main GUI Text objects
    title = new Text("SUDOKU", "assets/arial.ttf", 64, Color(255, 255, 255));

    /*
        Create GUI buttons (rectangles and text)
        (Need to rewrite using transparent PNG images with text overlay)
    */

    //std::cout << "Creating button: create new game" << std::endl;
    const Color button_color = Color(63, 71, 68, 255);
    GUIbutton = new Image("assets/images/Button.png");
    GUItext_create_new_game = new Text("Create New Game", "assets/arial.ttf", 26, Color(255, 255, 255));
    GUItext_reset = new Text("Reset", "assets/arial.ttf", 26, Color(255, 255, 255));
    GUItext_undo = new Text("Undo", "assets/arial.ttf", 26, Color(255, 255, 255));
    GUItext_redo = new Text("Redo", "assets/arial.ttf", 26, Color(255, 255, 255));
    GUItext_solution = new Text("Solution", "assets/arial.ttf", 26, Color(255, 255, 255));

    /*
        Create Sudoku grid
    */
    /*
    unsigned short origin_x = 8;
    unsigned short origin_y = 79;
    unsigned short cell_x = 2;
    unsigned short cell_y = 2;
    unsigned short boardGivenNumbers[81] = { 5, 3, 0, 0, 7, 0, 0, 0, 0, 6, 0, 0, 1, 9, 5, 0, 0, 0, 0, 9, 8, 0, 0, 0, 0, 6, 0, 8, 0, 0, 0, 6, 0, 0, 0, 3, 4, 0, 0, 8, 0, 3, 0, 0, 1, 7, 0, 0, 0, 2, 0, 0, 06, 0, 6, 0, 0, 0, 0, 2, 8, 0, 0, 0, 0, 4, 1, 9, 0, 0, 5, 0, 0, 0, 0, 8, 0, 0, 7, 9 };
    unsigned short boardSolution[81] = { 5, 3, 4, 6, 7, 8, 9, 1, 2, 6, 7, 2, 1, 9, 5, 3, 4, 8, 1, 9, 8, 3, 4, 2, 5, 6, 7, 8, 5, 9, 7, 6, 1, 4, 2, 3, 4, 2, 6, 8, 5, 3, 7, 9, 1, 7, 1, 3, 9, 2, 4, 8, 5, 6, 9, 6, 1, 5, 3, 7, 2, 8, 4, 2, 8, 7, 4, 1, 9, 6, 3, 5, 3, 4, 5, 2, 8, 6, 1, 7, 9 };
    // Grid loop
    int h = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            
            board[i][j].setCoordinates(cell_x + origin_x, cell_y + origin_y);
            board[i][j].setValue(boardSolution[h]);
            board[i][j].setActive(true);
            if (boardGivenNumbers[h] != 0) {
                board[i][j].setGiven(true);
            }
            h++;
            if (cell_x == 132 || cell_x == 330) {
                cell_x += 68;
            }
            else {
                cell_x += 65;
            }
        }
        if (cell_x == 132 || cell_x == 330) {
            cell_x += 68;
        }
        else {
            cell_x += 65;
        }
    }
    std::cout << "Init completed." << std::endl;
    */
}

void DeInit() {
    // DeInit
    delete bg;
    delete grid;
    delete numbers;
    delete title;
    //delete footer;
    delete GUIbutton;
    delete GUItext_create_new_game;
    delete GUItext_reset;
    delete GUItext_undo;
    delete GUItext_redo;
    delete GUItext_solution;

    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Input() {
    
    //SDL_Event e;
    //while (SDL_PollEvent(&e)) {
    //    switch (e.type) {
    //    case SDL_QUIT:
    //        running = false;
    //        break;
    //    }
    //}
}

void Update() {
    // game logic goes here
}

void Draw() {
    // White background
    SDL_FillRect(target, nullptr, SDL_MapRGBA(target->format, 0, 0, 0, 255));

    // Draw background image
    bg->Stage(target, 0, 0);

    // Draw transparent grid image on top of background
    grid->Stage(target, 8, 79);
    numbers->Stage(target, 8, 79);

    //Draw "Sudoku" title
    title->Stage(target, 138, 67);

    // Draw Buttons: Create new game
    GUIbutton->Stage(target, 632, 80);
    GUItext_create_new_game->Stage(target, 647, 117);
    // Draw Buttons: Reset
    GUIbutton->Stage(target, 632, 160);
    GUItext_reset->Stage(target, 726, 197);
    // Draw Buttons: Undo
    GUIbutton->Stage(target, 632, 240);
    GUItext_undo->Stage(target, 731, 277);
    // Draw Buttons: Redo
    GUIbutton->Stage(target, 632, 320);
    GUItext_redo->Stage(target, 731, 357);
    // Draw Buttons: Solution
    GUIbutton->Stage(target, 632, 400);
    GUItext_solution->Stage(target, 717, 437);

    /********************************************** 
     * If "Create new game" is clicked on, display
     * game difficulty buttons
     *********************************************/

    /**********************************************
     * Else: display game grid
     *********************************************
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j].Draw();
        }
    }
    */
    SDL_UpdateWindowSurface(window);
    SDL_Delay(10);
}