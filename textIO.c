#include <stdio.h>   //Basic input output functions are defined here
#include <stdbool.h> //This provides basic bool variables
//Note: Each global variables declaration is to use them in all sub-functions
#include <SDL2/SDL.h>       //Main library for window and rendering
#include <string.h>         //string operations
#include <SDL2/SDL_ttf.h>   //main library for rendering fonts
#include <SDL2/SDL_image.h> //image library
const int WIDTH = 1200;
const int HEIGHT = 700; //Width and height of screen
char inpbuffer[1000];   //GLobal variable for words inserted during program
char contents[1000];
char appendWord[1000];
SDL_Window *window = NULL;     //window pointer declaring global so that we can use it in all functoins
SDL_Renderer *renderer = NULL; //pointer to renderer
SDL_Texture *imgTexture = NULL;
SDL_Texture *imgTexture2 = NULL;
TTF_Font *gFont = NULL;
int mXpos, mYpos; //x and y position of mouse
// SDL_Texture *imgTexture=NULL;
bool flag = false;
struct charSize
{
    int height;
    int width;
} character[255];
bool pause = false;
SDL_Texture *NewTexture[255];
SDL_Color textColor = {0, 255, 0}; //SDL color variable
//These are all the required functions for textIO process
bool Initialize(void);                     //It initializes all the required variables and memorry locations like windows and renderer
void Update();                             //maybe required later to udate the screen with dictionary info
void Shutdown(void);                       //it kills all memory and destroys for safe exit of program.Everything initialized in initialize functions is destroyed here
int Display(char *inp, bool searchLayout); //Fuction that takes a string and displays it in screen
void instructions(void);
void createCharacters(void);
void renderSearchbutton(void);
void loadImage(char *imageName);
void renderDisplayLayout(void);
void loadDisplay(char *imageName);
void resultDisplay(void);
void file_read(char *word);
void appendWords(void);
bool mainmenu = false;
int main(int argc, char *argv[])
{
    bool appendMode = false;
    bool meaningMode = false;
    bool resultMode = false;
    atexit(Shutdown); //at exit performs shutdown function
    if (!Initialize())
    {
        exit(1); //safe exit if failed to initialize
    }
    SDL_StartTextInput(); //this enables us to track text entered during runtime
    bool quit = false;    //declaring quit to be false so that if we need to quit we can declare it true
    SDL_Event event;      //an event which represents our entire program
    createCharacters();
    Display("", true); //Passing wlecome string to display hence displaying it on screen
    // SDL_Delay(2000);           //delaying code execution to display welcome message
         //clearing the buffer by copying empty string to it->basically to remove the welcome which we passed earlier
    // instructions();            //THis functions basic instructions user needs to use Dictionary
    while (!quit) //Since quit is false program executes till quit is true->This is the main loop to run program
    {
        if (!appendMode && !meaningMode && !resultMode)
        {
            Display("|", true);
            inpbuffer[strlen(inpbuffer) - 1] = '\0';
        }
        while (SDL_PollEvent(&event)) //this catptures every event hapening during runtime
        {

            switch (event.type) //event.type is any type of event occurance when program is running
            {
            case SDL_QUIT: //if user hits that cross
                quit = true;
                break;
            case SDL_TEXTINPUT: //if users inputs text

                if (appendMode)
                {
                    strcat(appendWord, event.text.text);
                    Display(event.text.text, false);
                }
                else if (meaningMode)
                {
                    strcat(appendWord, event.text.text);
                    Display(event.text.text, false);
                }
                else
                {
                    Display(event.text.text, true); //event.text.text is the buffer where entered text goes so displaying it as it is
                    Display("|", true);
                    inpbuffer[strlen(inpbuffer) - 1] = '\0';
                    break;
                }
            case SDL_KEYDOWN:                               //if any key is pressed
                if (event.key.keysym.sym == SDLK_BACKSPACE) //if key pressed  is backspace
                {
                    if (strlen(inpbuffer) > 0 && !appendMode && !meaningMode) //if there is text in buffer ie length of text is greater than zero
                    {
                        inpbuffer[strlen(inpbuffer) - 1] = '\0'; //setting the second last as \0 because it needs to be erased
                        Display("|", true);                      //add a cursor | to the input buffer
                        inpbuffer[strlen(inpbuffer) - 1] = '\0'; //remove the cursor after displaying it
                    }
                    if (flag)
                    {
                        strcpy(inpbuffer, "");
                        Display("|", true);
                        inpbuffer[strlen(inpbuffer) - 1] = '\0';
                        flag = false;
                    }
                    if (strlen(appendWord) > 0 && (appendMode || meaningMode)) //if there is text in buffer ie length of text is greater than zero
                    {
                        appendWord[strlen(appendWord) - 1] = '\0'; //setting the second last as \0 because it needs to be erased
                        inpbuffer[strlen(inpbuffer) - 1] = '\0';   //remove the cursor after displaying it
                        Display("", false);                        //add a cursor | to the input buffer
                    }
                }
                else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) //condition-if user presses ctrl + c
                {
                    SDL_SetClipboardText(inpbuffer); //copy inpbuffer to clipboard
                }
                else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) //condition - if user presses ctrl+v
                {
                    // Display(SDL_GetClipboardText(),false);
                    strcat(inpbuffer, SDL_GetClipboardText()); //get text from input and appends it to inputbuffer
                    Display("|", true);
                    inpbuffer[strlen(inpbuffer) - 1] = '\0';
                }
                // else if (event.key.keysym.sym == SDLK_ESCAPE)
                // {
                //     quit = true;
                // }
                else if (event.key.keysym.sym == SDLK_RETURN)
                {
                    if (!appendMode && !meaningMode && !resultMode)
                    {
                        resultMode = true;
                        resultDisplay();
                        SDL_StopTextInput();
                    }
                    if (appendMode)
                    {
                        strcat(appendWord, ": ");
                        strcpy(inpbuffer, "");
                        Display("Enter the meaning(press enter after completion):", false);
                        strcpy(inpbuffer, "");
                        appendMode = false;
                        meaningMode = true;
                    }
                    else if (meaningMode)
                    {
                        strcpy(inpbuffer, "");
                        appendWords();
                        meaningMode = false;
                        strcpy(contents, "");
                        Display("", true);
                        SDL_StartTextInput();
                    }
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SDL_StartTextInput();
                    if (resultMode)
                    {
                        resultMode = false;
                        Display("", true);
                    }
                }
                else if (event.key.keysym.sym == SDLK_a && SDL_GetModState() & KMOD_CTRL)
                {
                    appendMode = true;
                    strcpy(inpbuffer, "");
                    Display("Enter the word you want to append to dictionary(press enter after your word completion):", false);
                    strcpy(inpbuffer, "");
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mXpos, &mYpos);
                if (mXpos > 697 && mXpos < 780 && mYpos > 380 && mYpos < 430)
                {
                    resultDisplay();
                    resultMode = true;
                    SDL_StopTextInput();
                }
                if (mXpos > 63 && mXpos < 139 && mYpos > 38 && mYpos < 78)
                {
                    mainmenu = true;
                    quit = true;
                }
                break;
            default:
                break;
            }
        }
    }
    SDL_StopTextInput(); //After the loop is exited text input is stopped
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
    loadImage("media\\searchLayout.png");
    loadDisplay("media\\Display.png");
    return true; //If it fails to initialize even 1 memory adresses it simply returns false
}
void Update()
{
    // SDL_SetRenderDrawColor(renderer,255,255,255,255);
}
void Shutdown(void) //Safe exit functon
{
    for (int i = 0; i < 255; i++)
    {
        SDL_DestroyTexture(NewTexture[i]);
    }

    SDL_DestroyTexture(imgTexture);
    if (renderer)
    {

        SDL_DestroyRenderer(renderer); //Destroys renderer
    }
    if (window)
    {
        SDL_DestroyWindow(window); //Destroys window
    }
    TTF_Quit(); //Exit TTF->True type font and SDL->Simple DirectMedia Layer
    SDL_Quit();
    if (mainmenu)
    {
        system("start mainmenu.exe");
    }
}
void instructions(void) //Basic instructions to use dictionary
{
    Display("Hello there!. To use this Dictionary simply put the words needed to be searched in  the box and press enter.Press ctrl+a to enter append mode.", false);
    strcpy(inpbuffer, ""); //Clearing the buffer cuz we entered shitloads of text before
}
int Display(char *inp, bool searchLayout)
{
    SDL_RenderClear(renderer);
    if (searchLayout)
    {
        renderSearchbutton();
    }
    if (!searchLayout)
    {
        renderDisplayLayout();
    }
    strcat(inpbuffer, inp); //Concatenates previous input with current input
    inp = strcat(inpbuffer, "");
    SDL_Rect dest;
    int i = 0;
    if (!searchLayout)
    {
        i = 0;
        dest.x = 0;
        dest.y = 0;
    }
    if (searchLayout)
    {
        dest.x = 452;
        dest.y = 398;
    }

    if (strlen(inpbuffer) == 0)
    {
        inpbuffer[0] = '|';
        inpbuffer[1] = '\0';
    }
    while (*inp)
    {
        dest.x += i;
        if (dest.x > WIDTH - 100 && !searchLayout)
        {
            dest.y += 20;
            i = 0;
            dest.x = i;
        }
        if (searchLayout && dest.x > 662 && (strlen(inpbuffer) > 1))
        {

            flag = true;
            break;
        }
        dest.w = character[*inp].width;
        dest.h = character[*inp].height;
        SDL_RenderCopy(renderer, NewTexture[(int)*inp], NULL, &dest);
        i = dest.w;
        inp++;
    }
    SDL_RenderPresent(renderer);
    if (inpbuffer[0] == '|')
    {
        strcpy(inpbuffer, "");
    }
    return 0;
}
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
void renderSearchbutton(void)
{
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect image = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
    SDL_RenderCopy(renderer, imgTexture, NULL, &image);
}
void loadImage(char *imageName)
{
    //     SDL_Surface *imgSurface = IMG_Load(imageName);
    //     if (imgSurface == NULL)
    //     {
    //         printf("Failed to open image\n");
    //     }
    //     imgTexture = SDL_CreateTextureFromSurface(renderer, imgSurface);
    // SDL_FreeSurface(imgSurface);
    imgTexture = IMG_LoadTexture(renderer, imageName);
}
void loadDisplay(char *imageName)
{
    // SDL_Surface *imgSurface = IMG_Load(imageName);
    // if (imgSurface == NULL)
    // {
    //     printf("Failed to open image\n");
    // }
    imgTexture2 = IMG_LoadTexture(renderer, imageName);
    // SDL_FreeSurface(imgSurface);
}
void resultDisplay(void)
{
    char searchWord[1000];
    strcpy(searchWord, inpbuffer);
    strcat(searchWord, " is the word you searched. The results are(Press Escape another word):");
    file_read(inpbuffer);
    strcat(searchWord, contents);
    strcpy(inpbuffer, "");
    Display(searchWord, false);
    strcpy(inpbuffer, "");
}

void file_read(char word[500])
{
    FILE *fp;
    word = strlwr(word);
    if ((int)word[0] > 90)
    {
        word[0] = word[0] - 32;
    }
    strcat(word, ":");
    bool found = false;
    fp = fopen("media\\test.txt", "r");
    if (fp == NULL)
    {
        printf("error to open file");
    }
    char str[500];
    while (!found)
    {
        if (fscanf(fp, "%s", &str) != EOF)
        {
            if (strcmp(str, word) == 0)
            {
                found = true;
                fscanf(fp, "%[^\n]", &contents);
            }
        }
        else
        {
            found = true;
            strcpy(contents, "The searched word not found");
        }
    }
    fclose(fp);
}
void renderDisplayLayout(void)
{
    SDL_Rect image = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
    SDL_RenderCopy(renderer, imgTexture2, NULL, &image);
}
void appendWords(void)
{
    FILE *fptr;
    strlwr(appendWord);
    if ((int)appendWord[0] > 95)
    {
        appendWord[0] = appendWord[0] - 32;
    }
    fptr = fopen("media\\test.txt", "a");
    strcat(appendWord, "\n");
    fputs(appendWord, fptr);
    fclose(fptr);
}
