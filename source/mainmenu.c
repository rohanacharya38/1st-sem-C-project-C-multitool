#include "variables.c"
#include "textIO.c"
#include "calculator.c"
#include "BrickBreaker.c"
#include <stdio.h>   //Basic input output functions are defined here
#include <stdbool.h> //This provides basic bool variables
//Note: Each global variables declaration is to use them in all sub-functions
#include <SDL.h>       //Main library for window and rendering
#include <string.h>    //string operations
#include <SDL_ttf.h>   //main library for rendering fonts
#include <SDL_image.h> //image library

int main(int argc, char *argv[])
{
    if (!Initialize())
    {
        exit(1); //safe exit if failed to initialize
    }
    bool quit = false; //declaring quit to be false so that if we need to quit we can declare it true
    SDL_Event event;   //an event which represents our entire program
    while (!quit)      //Since quit is false program executes till quit is true->This is the main loop to run program
    {

        textinput = false;
        while (SDL_PollEvent(&event)) //this catptures every event hapening during runtime
        {
            if (menu)
            {
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, menuTexture, NULL, &image);
                SDL_RenderPresent(renderer);
            }
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_TEXTINPUT:
                textinput = true;
            case SDL_MOUSEBUTTONDOWN:
                if (menu)
                {
                    SDL_GetMouseState(&mXpos, &mYpos);
                    printf("X:%d,Y:%d\n", mXpos, mYpos);
                    if (mYpos > 297 && mYpos < 563)
                    {
                        if (mXpos > 211 && mXpos < 464)
                        {
                            menu = false;
                            dict = true;
                            Display("", true);
                        }
                        if (mXpos > 474 && mXpos < 723)
                        {
                            menu = false;
                            brickG = true;
                            ball = MakeBall(BALL_SIZE);
                            player1 = MakePlayers();
                            player2 = MakePlayers();
                            // MakeBricks();
                        }
                        if (mXpos > 734 && mXpos < 990)
                        {
                            menu = false;
                            calci = true;
                            DisplayCalc("");
                        }
                    }
                }
                break;
            default:
                break;
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
            }
        }
        if (!menu)
        {
            if (brickG)
                BrickBreak(&event);
        }
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
    menuTexture = IMG_LoadTexture(renderer, "../media/mainmenu.png");
    searchTexture = IMG_LoadTexture(renderer, "../media/searchLayout.png");
    displayTexture = IMG_LoadTexture(renderer, "../media/Display.png");
    calciTexture = IMG_LoadTexture(renderer, "../media/calci.png");
    createCharacters();
    return true; //If it fails to initialize even 1 memory adresses it simply returns false
}
