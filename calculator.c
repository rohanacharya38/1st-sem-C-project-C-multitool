#include <stdio.h>   //Basic input output functions are defined here
#include <stdbool.h> //This provides basic bool variables
//Note: Each global variables declaration is to use them in all sub-functions
#include <SDL2/SDL.h>       //Main library for window and rendering
#include <string.h>         //string operations
#include <SDL2/SDL_ttf.h>   //main library for rendering fonts
#include <SDL2/SDL_image.h> //image library
#include <math.h>
#include "calci.c"
#define pi 3.141592654
void operatorFunc(void);
int main(int argc, char *argv[])
{
    bool right = false;
    bool equalPress;
    atexit(Shutdown); //at exit performs shutdown function
    if (!Initialize())
    {
        exit(1); //safe exit if failed to initialize
    }
    bool quit = false; //declaring quit to be false so that if we need to quit we can declare it true
    SDL_Event event;   //an event which represents our entire program
    Display("");
    while (!quit) //Since quit is false program executes till quit is true->This is the main loop to run program
    {
        Update();
        while (SDL_PollEvent(&event)) //this catptures every event hapening during runtime
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mXpos, &mYpos);
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    right = true;
                }
                if (mXpos > 91 && mXpos < 365 && mYpos > 298 && mYpos < 344)
                {
                    operatorFunc();
                    if (right)
                    {
                        placeValue = 0;
                        operandCount++;
                        Display("sin^-1(");
                        operator= 'S';
                        break;
                    }
                    else
                    {
                        placeValue = 0;
                        operandCount++;
                        Display("sin(");
                        operator= 's';
                    }
                }
                else if (mXpos > 87 && mXpos < 361 && mYpos > 181 && mYpos < 224)
                {
                    operatorFunc();
                    if (right)
                    {
                        placeValue = 0;
                        operandCount++;
                        Display("degree(");
                        operator= 'd';
                    }
                    else
                    {
                        placeValue = 0;
                        operandCount++;
                        Display("radian(");
                        operator= 'r';
                    }
                }
                else if (mXpos > 459 && mXpos < 733 && mYpos > 181 && mYpos < 224)
                {
                    operatorFunc();
                    placeValue = 0;
                    operandCount++;
                    Display("!");
                    operator= '!';
                    break;
                }
                else if (mXpos > 840 && mXpos < 1109 && mYpos > 178 && mYpos < 224)
                {
                    operatorFunc();
                    placeValue = 0;
                    operandCount++;
                    Display("\%");
                    operator= '%';
                    break;
                }
                else if (mXpos > 456 && mXpos < 739 && mYpos > 299 && mYpos < 344)
                {
                    operatorFunc();
                    if (right)
                    {
                        placeValue = 0;
                        operandCount++;
                        Display("cos^-1(");
                        operator= 'C';
                    }
                    else
                    {
                        placeValue = 0;
                        operandCount++;
                        Display("cos(");
                        operator= 'c';
                    }
                    break;
                }
                else if (mXpos > 832 && mXpos < 1116 && mYpos > 296 && mYpos < 343)
                {
                    operatorFunc();
                    if (right)
                    {
                        placeValue = 0;
                        operandCount++;
                        Display("tanh(");
                        operator= 'T';
                    }
                    else
                    {
                        placeValue = 0;
                        operandCount++;
                        Display("tan(");
                        operator= 't';
                        break;
                    }
                }
                else if (mXpos > 836 && mXpos < 1107 && mYpos > 421 && mYpos < 464)
                {
                    operatorFunc();
                    if (right)
                    {
                        placeValue = 0;
                        operandCount++;
                        Display("ln(");
                        operator= 'L';
                    }
                    else
                    {
                        placeValue = 0;
                        operandCount++;
                        Display("log(");
                        operator= 'l';
                        break;
                    }
                    break;
                }
                else if (mXpos > 89 && mXpos < 359 && mYpos > 418 && mYpos < 465)
                {
                    operatorFunc();
                    placeValue = 0;
                    operandCount++;
                    Display("throotof(");
                    operator= 'q';
                    break;
                }
                else if (mXpos > 359 && mXpos < 725 && mYpos > 421 && mYpos < 464)
                {
                    operatorFunc();
                    if (right)
                    {
                        placeValue = 0;
                        operandCount++;
                        Display("cosh(");
                        operator= 'j';
                    }
                    else
                    {
                        placeValue = 0;
                        operandCount++;
                        Display("sinh(");
                        operator= 'h';
                        break;
                    }
                }
                else if (mXpos > 161 && mXpos < 290 && mYpos > 542 && mYpos < 599)
                {
                    operatorFunc();
                    placeValue = 0;
                    operandCount++;
                    Display("^(");
                    operator= '^';
                    break;
                }
                else if (mXpos > 451 && mXpos < 726 && mYpos > 549 && mYpos < 593)
                {
                    operatorFunc();
                    placeValue = 0;
                    operandCount++;
                    Display("e^(");
                    operator= 'e';
                    break;
                }
                else if (mXpos > 908 && mXpos < 1043 && mYpos > 543 && mYpos < 599)
                {
                    equalPress = true;
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_g && SDL_GetModState() & KMOD_CTRL)
                {
                    graphingMode = true;
                }

                // {
                //     switch (operator)
                //     {
                //     case 's':
                //         operandCount++;
                //         x[operandCount] = sin(radian(x[operandCount - 1])) / 10;
                //         printf("%d\n", x[operandCount]);
                //         Display(")");
                //         printf("%d\n", atoi("sin"));
                //         operator= '0';
                //         break;

                //     default:
                //         break;
                //     }
                //     break;
                // }
                switch (event.key.keysym.sym)
                {
                case SDLK_RETURN:
                    equalPress = true;
                    break;
                case SDLK_ESCAPE:
                    if (!graphingMode)
                    {
                        mainmenu = true;
                        quit = true;
                    }
                case SDLK_SPACE:
                if (graphingMode)
                    {

                        operandCount = 0;
                        operator= '0';
                        strcpy(inpbuffer, "");
                        strcpy(input, "");
                        inputNumber = 0;
                        point = false;
                        // memcpy(x,0,sizeof(x));
                        x[0] = 0;
                        x[1] = 0;
                        x[2] = 0;
                        x[3] = 0;
                        prevRes = false;
                        Display("");
                    }
                    break;
                case SDLK_0:
                    Display("0");
                    break;
                case SDLK_KP_0:
                    Display("0");
                    break;
                case SDLK_1:
                    Display("1");
                    placeValue++;
                    break;
                case SDLK_KP_1:
                    Display("1");
                    placeValue++;
                    break;
                case SDLK_2:
                    Display("2");
                    placeValue++;
                    break;
                case SDLK_KP_2:
                    Display("2");
                    placeValue++;
                    break;
                case SDLK_3:
                    Display("3");
                    placeValue++;
                    break;
                case SDLK_KP_3:
                    Display("3");
                    placeValue++;
                    break;
                case SDLK_4:
                    Display("4");
                    placeValue++;
                    break;
                case SDLK_KP_4:
                    Display("4");
                    placeValue++;
                    break;
                case SDLK_5:
                    Display("5");
                    placeValue++;
                    break;
                case SDLK_KP_5:
                    Display("5");
                    placeValue++;
                    break;
                case SDLK_6:
                    Display("6");
                    placeValue++;
                    break;
                case SDLK_KP_6:
                    Display("6");
                    placeValue++;
                    break;
                case SDLK_7:
                    Display("7");
                    placeValue++;
                    break;
                case SDLK_KP_7:
                    Display("7");
                    placeValue++;
                    break;
                case SDLK_8:
                    Display("8");
                    placeValue++;
                    break;
                case SDLK_KP_8:
                    Display("8");
                    placeValue++;
                    break;
                case SDLK_9:
                    Display("9");
                    placeValue++;
                    break;
                case SDLK_KP_9:
                    Display("9");
                    placeValue++;
                    break;
                case SDLK_KP_PERIOD:
                    point = true;
                    Display(".");
                    placeValue++;
                    break;
                case SDLK_KP_PLUS:
                    operatorFunc();
                    placeValue = 0;
                    operandCount++;
                    point = false;
                    Display("+");
                    operator= '+';
                    break;
                case SDLK_KP_MULTIPLY:
                    operatorFunc();
                    placeValue = 0;
                    operandCount++;
                    point = false;
                    Display("*");
                    operator= '*';
                    break;
                case SDLK_KP_DIVIDE:
                    operatorFunc();
                    placeValue = 0;
                    operandCount++;
                    point = false;
                    Display("/");
                    operator= '/';
                    break;
                case SDLK_KP_MINUS:
                    operatorFunc();
                    placeValue = 0;
                    operandCount++;
                    point = false;
                    Display("-");
                    operator= '-';
                    break;
                case SDLK_s:
                    operatorFunc();
                    placeValue = 0;
                    operandCount++;
                    point = false;
                    Display("sin(");
                    operator= 's';
                    break;
                case SDLK_c:
                    operatorFunc();
                    placeValue = 0;
                    operandCount++;
                    point = false;
                    Display("cos(");
                    operator= 'c';
                    break;
                case SDLK_l:
                    operatorFunc();
                    placeValue = 0;
                    operandCount++;
                    point = false;
                    Display("log(");
                    operator= 'l';
                    break;
                case SDLK_BACKSPACE:
                    operandCount = 0;
                    operator= '0';
                    strcpy(inpbuffer, "");
                    strcpy(input, "");
                    inputNumber = 0;
                    point = false;
                    // memcpy(x,0,sizeof(x));
                    x[0] = 0;
                    x[1] = 0;
                    x[2] = 0;
                    x[3] = 0;
                    prevRes = false;
                    Display("");
                    break;
                default:
                    break;
                }
            default:
                break;
            }
            if (equalPress)
            {
                switch (operator)
                {
                case '+':
                    opResult = x[operandCount] + x[operandCount - 1];
                    result(opResult);
                    break;
                case '*':
                    opResult = x[operandCount] * x[operandCount - 1];
                    result(opResult);
                    break;
                case '/':
                    opResult = x[operandCount - 1] / x[operandCount];
                    result(opResult);
                    break;
                case '-':
                    opResult = x[operandCount - 1] - x[operandCount];
                    result(opResult);
                    break;
                case 's':
                    opResult = sine(x[operandCount]);
                    if (x[operandCount - 1] > 0)
                    {
                        opResult = x[operandCount - 1] * sine(x[operandCount]);
                    }
                    result(opResult);
                    break;
                case 'c':
                    opResult = cosine(x[operandCount]);
                    if (x[operandCount - 1] > 0)
                    {
                        opResult = x[operandCount - 1] * cosine(x[operandCount]);
                    }
                    result(opResult);
                    break;
                case 'l':
                    opResult = (float)log10(x[operandCount]) * 1;
                    if (x[operandCount - 1] > 0)
                    {
                        opResult = x[operandCount - 1] * opResult;
                    }
                    result(opResult);
                    operator= '0';
                    break;
                case 'S':
                    opResult = degree(asin(x[operandCount]));
                    if (x[operandCount - 1] > 0)
                    {
                        opResult = x[operandCount - 1] * degree(asin(x[operandCount]));
                    }
                    result(opResult);
                    break;
                case 'd':
                    opResult = degree(x[operandCount]);
                    if (x[operandCount - 1] > 0)
                    {
                        opResult = x[operandCount - 1] * opResult;
                    }
                    result(opResult);
                    break;
                case 'r':
                    opResult = radian(x[operandCount]);
                    if (x[operandCount - 1] > 0)
                    {
                        opResult = x[operandCount - 1] * opResult;
                    }
                    result(opResult);
                    break;
                case '!':
                    opResult = fact((int)(x[operandCount - 1]));
                    x[operandCount] = 1;
                    result(opResult);
                    break;
                case '%':
                    opResult = fmod(x[operandCount - 1], x[operandCount]);

                    result(opResult);
                    break;
                case 'q':
                    opResult = pow(x[operandCount], 1 / x[operandCount - 1]);
                    result(opResult);
                    break;
                case 'j':
                    opResult = coshyp(x[operandCount]);
                    if (x[operandCount - 1] > 0)
                    {
                        opResult = x[operandCount - 1] * opResult;
                    }
                    result(opResult);
                    break;
                case 'h':
                    opResult = sinhyp(x[operandCount]);
                    if (x[operandCount - 1] > 0)
                    {
                        opResult = x[operandCount - 1] * opResult;
                    }
                    result(opResult);
                    break;
                case '^':
                    opResult = pow(x[operandCount - 1], x[operandCount]);
                    result(opResult);
                    break;
                case 'e':
                    opResult = pow(2.718281828459, x[operandCount]);
                    if (x[operandCount - 1] > 0)
                    {
                        opResult = x[operandCount - 1] * opResult;
                    }
                    result(opResult);
                    break;
                case 'T':
                    opResult = tanhyp(x[operandCount]);
                    if (x[operandCount - 1] > 0)
                    {
                        opResult = x[operandCount - 1] * opResult;
                    }
                    result(opResult);
                    break;
                case 't':
                    opResult = tangent(x[operandCount]);
                    if (x[operandCount - 1] > 0)
                    {
                        opResult = x[operandCount - 1] * opResult;
                    }
                    result(opResult);
                    break;
                case 'L':
                    opResult = log(x[operandCount]);
                    if (x[operandCount - 1] > 0)
                    {
                        opResult = x[operandCount - 1] * opResult;
                    }
                    result(opResult);
                    break;
                case 'C':
                    opResult = degree(acos(x[operandCount]));
                    if (x[operandCount - 1] > 0)
                    {
                        opResult = x[operandCount - 1] * opResult;
                    }
                    result(opResult);
                    break;
                default:
                    break;
                }
            }
        }
        equalPress = false;
        right = false;
    }
    exit(1);
    SDL_Quit(); //This is the quit function of SDL
    return 0;
}
void operatorFunc(void)
{
    point = false;
    switch (operator)
    {
    case '+':
        x[operandCount] = (x[operandCount] + x[operandCount - 1]) * 10;
        break;
    case '-':
        x[operandCount] = (x[operandCount] - x[operandCount - 1]) * 10;
        break;
    case '*':
        x[operandCount] = (x[operandCount] * x[operandCount - 1]) * 10;
        break;
    case '/':

        x[operandCount] = (x[operandCount] / x[operandCount - 1]) * 10;
        break;
    case 's':
        x[operandCount] = sine(x[operandCount]);
        if (x[operandCount - 1] > 0)
        {
            x[operandCount] *= x[operandCount - 1];
        }
        Display(")");
        break;
    case 'c':
        x[operandCount] = cosine(x[operandCount]);
        if (x[operandCount - 1] > 0)
        {
            x[operandCount] *= x[operandCount - 1];
        }
        Display(")");
        break;
    case 'l':
        x[operandCount] = (float)log10(x[operandCount]) * 1;
        if (x[operandCount - 1] > 0)
        {
            x[operandCount] *= x[operandCount - 1];
        }
        Display(")");
        break;
    case 'S':
        x[operandCount] = degree(asin(x[operandCount]));
        if (x[operandCount - 1] > 0)
        {
            x[operandCount] *= x[operandCount - 1];
        }
        Display(")");
        break;
    case 'd':
        x[operandCount] = degree(x[operandCount]);
        if (x[operandCount - 1] > 0)
        {
            x[operandCount] *= x[operandCount - 1];
        }
        Display(")");
        break;
    case 'r':
        x[operandCount] = radian(x[operandCount]);
        if (x[operandCount - 1] > 0)
        {
            x[operandCount] *= x[operandCount - 1];
        }
        Display(")");
        break;
    case '!':
        x[operandCount] = fact((int)(x[operandCount - 1]));
        x[operandCount] = 1;
        break;
    case '%':
        x[operandCount] = fmod(x[operandCount - 1], x[operandCount]);
        break;
    case 'q':
        x[operandCount] = pow(x[operandCount], 1 / x[operandCount - 1]);
        Display(")");
        break;
    case 'j':
        x[operandCount] = coshyp(x[operandCount]);
        if (x[operandCount - 1] > 0)
        {
            x[operandCount] *= x[operandCount - 1];
        }
        Display(")");
        break;
    case 'h':
        x[operandCount] = sinhyp(x[operandCount]);
        if (x[operandCount - 1] > 0)
        {
            x[operandCount] *= x[operandCount - 1];
        }
        Display(")");
        break;
    case '^':
        x[operandCount] = pow(x[operandCount - 1], x[operandCount]);
        Display(")");
        break;
    case 'e':
        opResult = pow(2.718281828459, x[operandCount]);
        if (x[operandCount - 1] > 0)
        {
            opResult *= x[operandCount - 1];
        }
        Display(")");
        break;
    case 'T':
        x[operandCount] = tanhyp(x[operandCount]);
        if (x[operandCount - 1] > 0)
        {
            x[operandCount] *= x[operandCount - 1];
        }
        Display(")");
        break;
    case 't':
        x[operandCount] = tangent(x[operandCount]);
        if (x[operandCount - 1] > 0)
        {
            x[operandCount] *= x[operandCount - 1];
        }
        Display(")");
        break;
    case 'L':
        x[operandCount] = log(x[operandCount]);
        if (x[operandCount - 1] > 0)
        {
            x[operandCount] *= x[operandCount - 1];
        }
        Display(")");
        break;
    case 'C':
        x[operandCount] = degree(acos(x[operandCount]));
        if (x[operandCount - 1] > 0)
        {
            x[operandCount] *= x[operandCount - 1];
        }
        Display(")");
        break;
    default:
        break;
    }
    if (operator!= '0')
    {
        x[operandCount] /= 10;
    }
}
