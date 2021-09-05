
#include <stdio.h>   //Basic input output functions are defined here
#include <stdbool.h> //This provides basic bool variables
//Note: Each global variables declaration is to use them in all sub-functions
#include <SDL2/SDL.h>       //Main library for window and rendering
#include <string.h>         //string operations
#include <SDL2/SDL_ttf.h>   //main library for rendering fonts
#include <SDL2/SDL_image.h> //image library
const int WIDTH = 1300;
const int HEIGHT = 700;            //Width and height of screen
                                   //GLobal variable for words inserted during program
SDL_Window *window = NULL;         //window pointer declaring global so that we can use it in all functoins
SDL_Renderer *renderer = NULL;     //pointer to renderer
SDL_Color textColor = {255, 0, 0}; //SDL color variable
SDL_Texture *imgTexture = NULL;
bool dictionary = false;
bool brick = false;
bool calculator = false;
//These are all the required functions for textIO process
bool Initialize(void); //It initializes all the required variables and memorry locations like windows and renderer
void Update();         //maybe required later to udate the screen with dictionary info
void Shutdown(void);   //it kills all memory and destroys for safe exit of program.Everything initialized in initialize functions is destroyed here
void renderMenu(void);
void loadImage(char *imageName);
void exitFunc(void);
int main(int argc, char *argv[])
{

    int mXpos, mYpos;
    dictionary = false;
    atexit(Shutdown); //at exit performs shutdown function
    if (!Initialize())
    {
        exit(1); //safe exit if failed to initialize
    }
    bool quit = false; //declaring quit to be false so that if we need to quit we can declare it true
    SDL_Event event;   //an event which represents our entire program
    renderMenu();

    while (!quit) //Since quit is false program executes till quit is true->This is the main loop to run program
    {
        // if(SDL_GetWindowFlags(window) & SDL_WINDOW_MAXIMIZED==1)
        // {
        //     renderMenu();
        //     SDL_RenderPresent(renderer);
        // }
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event)) //this catptures every event hapening during runtime
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mXpos, &mYpos);
                if (mYpos > 301 && mYpos < 562)
                {
                    if (mXpos >= 230 && mXpos <= 502)
                    {
                        dictionary = true;
                        quit = true;
                    }
                    if (mXpos >= 518 && mXpos <= 784)
                    {

                        brick = true;
                        quit = true;
                    }

                    if (mXpos >= 801 && mXpos <= 1066)
                    {
                        calculator = true;
                        quit = true;
                    }
                }
                break;
            default:
                break;
            }
        }
    }
    exit(1);
    SDL_Quit(); //This is the quit function of SDL
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
    loadImage("media\\mainmenu.png");
    SDL_Surface *icon = IMG_Load("media\\mainmenu.png");
    if (!icon)
    {
        printf("failed to load icon\n");
    }
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    return true; //If it fails to initialize even 1 memory adresses it simply returns false
}
void Update()
{
}
void Shutdown(void) //Safe exit functon
{
    if (imgTexture)
    {
        SDL_DestroyTexture(imgTexture);
    }
    if (renderer)
    {
        SDL_DestroyRenderer(renderer); //Destroys renderer
    }
    if (window)
    {
        SDL_DestroyWindow(window); //Destroys window
    }
    exitFunc();
    TTF_Quit(); //Exit TTF->True type font and SDL->Simple DirectMedia Layer
    SDL_Quit();

    
}
void loadImage(char *imageName)
{
    SDL_Surface *imgSurface = IMG_Load(imageName);
    if (imgSurface == NULL)
    {
        printf("Failed to open image %s\n", imageName);
    }
    imgTexture = SDL_CreateTextureFromSurface(renderer, imgSurface);
    SDL_FreeSurface(imgSurface);
}
void renderMenu(void)
{
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect image = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
    SDL_RenderCopy(renderer, imgTexture, NULL, &image);
}
void exitFunc(void)
{
    if (dictionary)
    {
        system("start Dictionary");
        
    }
    if (brick)
    {
        system("start BrickBreaker");
    }
    else if (calculator)
    {
        system("start calculator");
    }
}