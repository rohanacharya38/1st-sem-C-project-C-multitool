#include <ctype.h>
#define pi 3.141592654
const int WIDTH = 1200;
const int HEIGHT = 700; //Width and height of screen
char inpbuffer[1000];   //GLobal variable for words inserted during program
char input[1000];
SDL_Window *window = NULL;     //window pointer declaring global so that we can use it in all functoins
SDL_Renderer *renderer = NULL; //pointer to renderer
SDL_Texture *imgTexture = NULL;
SDL_Texture *imgTexture2 = NULL;
TTF_Font *gFont = NULL;
int mXpos, mYpos; //x and y position of mouse
// SDL_Texture *imgTexture=NULL;
bool flag = false;
bool point = false;
bool graphingMode = false;

int behindPoint = 0;
SDL_Rect image = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
struct charSize
{
    int height;
    int width;
} character[255];
bool pause = false;
//number operations
double x[20];
int operandCount = 0;
int placeValue = 0;
double inputNumber;
char operator= '0';
double opResult = 0;
bool prevRes = false;
bool mainmenu = false;
int no = 0; //no of operator used
//
SDL_Texture *NewTexture[255];
SDL_Color textColor = {0, 255, 0}; //SDL color variable

//These are all the required functions for textIO process
bool Initialize(void);   //It initializes all the required variables and memorry locations like windows and renderer
void Update();           //maybe required later to udate the screen with dictionary info
void Shutdown(void);     //it kills all memory and destroys for safe exit of program.Everything initialized in initialize functions is destroyed here
void Display(char *inp); //Fuction that takes a string and displays it in screen
void createCharacters(void);
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
    createCharacters();

    imgTexture = IMG_LoadTexture(renderer, "media\\calci.png");

    // loadImage("searchLayout.png");
    // loadDisplay("Display.png");
    return true; //If it fails to initialize even 1 memory adresses it simply returns false
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

void Display(char *inp)
{

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, imgTexture, NULL, &image);
    if (!imgTexture)
    {
        printf("failed to load image");
    }
    //Concatenates previous input with current input
    if (prevRes && !atoi(inp))
    {
        strcat(inpbuffer, "Ans");
        prevRes = false;
    }
    else if (prevRes)
    {
        for (int i = 0; i < 19; i++)
        {
            x[i] = 0;
        }
    }
    if ((atoi(inp) >= 0 || atoi(inp) < 0) && !point)
    {
        behindPoint = 0;
        x[operandCount] = atof(inp) + x[operandCount] * 10;
    }
    else if (inp[0] == ')')
    {
    }
    else if (point)
    {
        if (behindPoint == 0)
        {
            behindPoint++;
        }
        else if (behindPoint > 0)
        {
            x[operandCount] += atof(inp) * pow(10, -behindPoint);
            behindPoint++;
        }
    }
    // else
    // {
    //     point = false;
    //     operandCount++;
    //     behindPoint = 0;
    // }
    strcat(inpbuffer, inp);
    inp = strcat(inpbuffer, "");
    SDL_Rect dest;
    int i = 0;
    dest.x = 0;
    dest.y = 0;
    while (*inp)
    {
        dest.x += i;
        dest.w = character[*inp].width;
        dest.h = character[*inp].height;
        SDL_RenderCopy(renderer, NewTexture[(int)*inp], NULL, &dest);
        i = dest.w;
        inp++;
    }
    SDL_RenderPresent(renderer);
    prevRes = false;
}
void createCharacters(void)
{
    gFont = TTF_OpenFont("media\\Lobster-Regular.ttf", 30); //SDL font pointer
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
void result(float result)
{
    sprintf(input, "=%f", result);
    char *inp = input;

    SDL_Rect dest;
    int i = 0;
    dest.x = 0;
    dest.y = 60;
    while (*inp)
    {
        dest.x += i;
        dest.w = character[*inp].width;
        dest.h = character[*inp].height;
        SDL_RenderCopy(renderer, NewTexture[(int)*inp], NULL, &dest);
        i = dest.w;
        inp++;
    }
    SDL_RenderPresent(renderer);
    operandCount = 0;
    placeValue = 0;
    for (int i = 0; i < 20; i++)
    {
        x[i] = 0;
    }
    x[0] = result;
    operator= '0';
    prevRes = true;
    strcpy(inpbuffer, "");
}

float mod(float x, float y)
{
    int temp;
    float result;
    temp = x / y;
    result = x - temp * y;
    return (result);
}
long int fact(float n)
{
    float x = n;
    if (x - abs((int)x) != 0)
    {
        return 0;
    }

    long int result;
    if (n == 0)
    {
        return (1);
    }
    else
    {
        return (n * fact(n - 1));
    }
}
float radian(float x)
{
    float result;
    result = x * (pi / 180);
    return result;
}
float degree(float x)
{
    float result;
    result = x * (180 / pi);
    return result;
}
float sine(float x)
{
    int i;
    float result = 0;
    float term;
    float an;
    int temp;
    int t;
    an = (mod(x, 180) * 3.141592) / 180;
    temp = x / 180;
    for (i = 1; i <= 15; i++)
    {
        term = pow(-1, i + 1) * pow(an, (2 * i) - 1) / fact((2 * i) - 1);
        result += term;
    }
    if (temp % 2 == 0)
    {
        return (result);
    }
    else
    {
        return (result * -1);
    }
}
float cosine(float x)
{
    float result;
    result = pow(1 - pow(sine(x), 2), 0.5);
    return (result);
}
float tangent(float x)
{
    float result;
    result = sine(x) / cosine(x);
    return (result);
}
float sinhyp(float x)
{
    float result;
    result = (pow(2.71828, x) - pow(2.71828, x * -1)) / 2;
    return (result);
}
float coshyp(float x)
{
    float result;
    result = (pow(2.71828, x) + pow(2.71828, x * -1)) / 2;
    return (result);
}
float tanhyp(float x)
{
    float result;
    result = sinhyp(x) / coshyp(x);
    return (result);
}
void Update(void)
{
    if (graphingMode && operator!= '0')
    {
        createGraph();
        graphingMode = false;
    }
}

void createGraph(void)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_SetWindowTitle(window, "Graph");
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int y = 0;
    int yTemp = 0;
    int resetX;
    for ( int x = 0; x < WIDTH; x++)
    {
        resetX=x;
        switch (operator)
        {
        case 's':
            y = (HEIGHT / 2) + (HEIGHT / 2) * sin(2 * 3.1415 * (x / (double)WIDTH));
            break;
        case 'c':
            y = (HEIGHT / 2) + (HEIGHT / 2) * cos(2 * 3.1415 * (x / (double)WIDTH));
            break;
        case 'l':
            y = pow(2.718281828, (10 * x) / (double)(WIDTH));
            yTemp=x;
            x=WIDTH/2+y;
            y=HEIGHT-yTemp;
            // SDL_RenderDrawLine(renderer, x, y, x - 1, yTemp);
            break;
        case 'S':
            //inverse sin
            yTemp=x;
            x = (HEIGHT / 2) + (HEIGHT / 2) * sin(2 * 3.1415 * (y / (double)WIDTH));
            y=HEIGHT-yTemp;
            break;
        case 'd':
            //inverse cos
            break;

        case 'j':
            //hyp cos
            y=HEIGHT/2+cosh(10*x/WIDTH);
            x=WIDTH-x;
            break;
        case 'h':
            //hypsin
            if(x<WIDTH/2)
            {
            y = (HEIGHT/2 ) - sinh( 10*x / (double)(WIDTH));
            x=WIDTH/2+x;
            }
            else if(x>=WIDTH/2)
            {
            x=WIDTH-x;
            y =  HEIGHT/2-sinh( 10*(x-WIDTH/2) / (double)(WIDTH));

            }
            break;
        case 'e':
            y = (HEIGHT / 2) - pow(2.718281828, (10 * x) / (double)(WIDTH));
            SDL_RenderDrawLine(renderer, x, y, x - 1, yTemp);
            yTemp = y;
            break;
        case 'T':
            //hyptan
            break;
        case 't':
            y = (HEIGHT / 2) + (HEIGHT / 2) * tan(2 * 3.1415 * (x / (double)WIDTH));
            break;
        case 'L':
            //log
            y = (HEIGHT / 2) -  log(10*(x +1));
            SDL_RenderDrawLine(renderer, x, y, x - 1, yTemp);
            yTemp = y;
            break;
        case 'C':
            //inverse cos
            break;
        default:
            break;
        }
        SDL_RenderDrawPoint(renderer, x, y);
        x=resetX;
    }
    SDL_RenderDrawLine(renderer, WIDTH / 2, 0, WIDTH / 2, HEIGHT);
    SDL_RenderDrawLine(renderer, 0, HEIGHT / 2, WIDTH, HEIGHT / 2);
    SDL_RenderPresent(renderer);
}
