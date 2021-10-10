#include <stdio.h>   //Basic input output functions are defined here
#include <stdbool.h> //This provides basic bool variables
//Note: Each global variables declaration is to use them in all sub-functions
#include <SDL2/SDL.h>       //Main library for window and rendering
#include <string.h>         //string operations
#include <SDL2/SDL_ttf.h>   //main library for rendering fonts
#include <SDL2/SDL_image.h> //image library
char inpbuffer[1000];       //GLobal variable for words inserted during program
char contents[1000];
char appendWord[1000];
SDL_Window *window = NULL;         //window pointer declaring global so that we can use it in all functoins
SDL_Renderer *renderer = NULL;     //pointer to renderer
SDL_Color textColor = {255, 0, 0}; //SDL color variable
SDL_Texture *searchTexture = NULL;
const int WIDTH = 1200;
const int HEIGHT = 700; //Width and height of screen
SDL_Texture *displayTexture = NULL,*menuTexture=NULL;
TTF_Font *gFont = NULL;
int mXpos, mYpos; //x and y position of mouse
bool appendMode = false,resultMode = false,meaningMode = false,flag = false,pause=false,point=false,graphingMode=false;
bool menu = true,calci=false,brick=false,dict=false;
struct charSize
{
    int height;
    int width;
} character[255];
SDL_Texture *NewTexture[255];
SDL_Rect image = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
  SDL_Texture  *calciTexture =NULL;
  #define pi 3.141592654
char input[1000];
int behindPoint = 0;
//number operations
double x[20];
int operandCount = 0;
int placeValue = 0;
double inputNumber;
char operator= '0';
double opResult = 0;
bool prevRes = false;
bool right = false;
bool equalPress;
int no = 0; //no of operator used
void Update();         //maybe required later to udate the screen with dictionary info
void Shutdown(void);   //it kills all memory and destroys for safe exit of program.Everything initialized in initialize functions is destroyed here
void renderMenu(void);
bool Initialize(void);                     //It initializes all the required variables and memorry locations like windows and renderer
int Display(char *inp, bool searchLayout); //Fuction that takes a string and displays it in screen
void instructions(void);
void createCharacters(void);
void renderSearchbutton(void);
void renderDisplayLayout(SDL_Texture *Text);
void resultDisplay(void);
void file_read(char *word);
void appendWords(void);
bool Initialize(void); //It initializes all the required variables and memorry locations like windows and renderer

void createCharacters(void)
{
    gFont = TTF_OpenFont("media\\Lobster-Regular.ttf", 24); //SDL font pointer
    SDL_Surface *CharacterMap[255];
    for (int i = 0; i < 255; i++)
    {
        char str[2] = {(char)i, '\0'};
        CharacterMap[i] = TTF_RenderText_Blended_Wrapped(gFont, str, textColor, WIDTH - 50);
        NewTexture[i] = SDL_CreateTextureFromSurface(renderer, CharacterMap[i]);
        character[i].height = CharacterMap[i] ? CharacterMap[i]->h : 0;
        character[i].width = CharacterMap[i] ? CharacterMap[i]->w : 0;
        SDL_FreeSurface(CharacterMap[i]);
    }
    TTF_CloseFont(gFont);
}
void DisplayCalc(char *inp); //Fuction that takes a string and displays it in screen
void result(float);
long int fact(float n);
float radian(float x);
float degree(float x);
float sine(float x);
float cosine(float x);
float tangent(float x);
float sinhyp(float x);
float coshyp(float x);
float tanhyp(float x);
void createGraph(void);