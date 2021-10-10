#include "variables.c"
#include "textIO.c"
#include "calculator.c"
#include "BrickBreaker.c"
#include <stdio.h>   //Basic input output functions are defined here
#include <stdbool.h> //This provides basic bool variables
//Note: Each global variables declaration is to use them in all sub-functions
#include <SDL2/SDL.h>       //Main library for window and rendering
#include <string.h>         //string operations
#include <SDL2/SDL_ttf.h>   //main library for rendering fonts
#include <SDL2/SDL_image.h> //image library

int main(int argc, char *argv[])
{
    if (!Initialize())
    {
        exit(1); //safe exit if failed to initialize
    }
    bool quit = false; //declaring quit to be false so that if we need to quit we can declare it true
    SDL_Event event;   //an event which represents our entire program
    lastTick = SDL_GetTicks();
    while (!quit) //Since quit is false program executes till quit is true->This is the main loop to run program
    {
        SDL_StartTextInput();
        textinput=false;         //this enables us to track text entered during runtime
        while (SDL_PollEvent(&event)) //this catptures every event hapening during runtime
        {
            if (menu)
            {
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, menuTexture, NULL, &image);
                SDL_GetMouseState(&mXpos, &mYpos);
                SDL_RenderPresent(renderer);
            }
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (menu)
                {
                    if (mYpos > 301 && mYpos < 562)
                    {
                        if (mXpos > 230 && mXpos < 502)
                        {
                            menu = false;
                            dict = true;
                        }
                        if (mXpos > 518 && mXpos < 784)
                        {
                            menu = false;
                            brickG = true;
                            ball = MakeBall(BALL_SIZE);
                            player1 = MakePlayers();
                            player2 = MakePlayers();
                            // MakeBricks();
                        }
                        if (mXpos > 801 && mXpos < 1066)
                        {
                            menu = false;
                            calci = true;
                            DisplayCalc("");
                        }
                    }
                }
                break;
            case SDL_TEXTINPUT:
                    textinput=true;
                break;
                break;
            }
        }
        if (!menu)
        {
            if (dict)
            {
                dictionary(&event);
            }
            else if (calci)
            {

                calculator(&event);
            }

            else if (brickG)
            {
                BrickBreak(&event);
            }
        }
        SDL_StopTextInput();
    }

    return 0;
}

bool Initialize(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) //Video initialization
    {
        fprintf(stderr, "Failed to initialize SDL:%s\n", SDL_GetError()); //if there is error in video initialization it prints failed to initialize to stderr
        return false;
    }
    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN); //Creating a window with width height and title parameters note that position of window is not defined
    if (!window)
    {
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Initializing a renderer in the creating window which render objects there
    if (!renderer)
    {
        return false;
    }
    if (TTF_Init() == -1)
    {
        return false;
    }
    menuTexture = IMG_LoadTexture(renderer, "media/mainmenu.png");
    searchTexture = IMG_LoadTexture(renderer, "media/searchLayout.png");
    displayTexture = IMG_LoadTexture(renderer, "media/Display.png");
    calciTexture = IMG_LoadTexture(renderer, "media/calci.png");
    createCharacters();
    return true; //If it fails to initialize even 1 memory adresses it simply returns false
}
