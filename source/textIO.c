#include <stdio.h>   //Basic input output functions are defined here
#include <stdbool.h> //This provides basic bool variables
//Note: Each global variables declaration is to use them in all sub-functions
#include <SDL2/SDL.h>       //Main library for window and rendering
#include <string.h>         //string operations
#include <SDL2/SDL_ttf.h>   //main library for rendering fonts
#include <SDL2/SDL_image.h> //image library

int dictionary(SDL_Event *event)
{
        if (!appendMode && !meaningMode && !resultMode)
        {
            Display("|", true);
            inpbuffer[strlen(inpbuffer) - 1] = '\0';
        }
        switch (event->type) //event.type is any type of event occurance when program is running
        {
        case SDL_TEXTINPUT: //if users inputs text
           
            if (appendMode)
            {
                strcat(appendWord, event->text.text);
                Display(event->text.text, false);
            }
            else if (meaningMode)
            {
                strcat(appendWord, event->text.text);
                Display(event->text.text, false);
            }
            else
            {
                Display(event->text.text, true); //event.text.text is the buffer where entered text goes so displaying it as it is
                Display("|", true);
                inpbuffer[strlen(inpbuffer) - 1] = '\0';
                break;
            }
           
        case SDL_KEYDOWN:                                //if any key is pressed
            if (event->key.keysym.sym == SDLK_BACKSPACE) //if key pressed  is backspace
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
            else if (event->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) //condition-if user presses ctrl + c
            {
                SDL_SetClipboardText(inpbuffer); //copy inpbuffer to clipboard
            }
            else if (event->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) //condition - if user presses ctrl+v
            {
                // Display(SDL_GetClipboardText(),false);
                strcat(inpbuffer, SDL_GetClipboardText()); //get text from input and appends it to inputbuffer
                Display("|", true);
                inpbuffer[strlen(inpbuffer) - 1] = '\0';
            }
            else if (event->key.keysym.sym == SDLK_RETURN)
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
            else if (event->key.keysym.sym == SDLK_ESCAPE)
            {
                SDL_StartTextInput();
                if (resultMode)
                {
                    resultMode = false;
                    Display("", true);
                }
            }
            else if (event->key.keysym.sym == SDLK_a && SDL_GetModState() & KMOD_CTRL)
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
            if (mXpos > 63 && mXpos < 139 && mYpos > 38 && mYpos < 78)//home button
            {
                menu=true;
                dict=false;
            }
            break;
        default:
            break;
    }
    return 0;
}

int Display(char *inp, bool searchLayout)
{
    SDL_RenderClear(renderer);
    if (searchLayout)
    {
    SDL_RenderCopy(renderer, searchTexture, NULL, &image);
    }
    if (!searchLayout)
    {
        renderDisplayLayout(displayTexture);
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
    fp = fopen("..\\..\\media\\test.txt", "r");
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
inline void renderDisplayLayout(SDL_Texture *Text)
{
    SDL_Rect image = {.x = 0, .y = 0, .w = WIDTH, .h = HEIGHT};
    SDL_RenderCopy(renderer, Text, NULL, &image);
}
void appendWords(void)
{
    FILE *fptr;
    strlwr(appendWord);
    if ((int)appendWord[0] > 95)
    {
        appendWord[0] = appendWord[0] - 32;
    }
    fptr = fopen("..\\..\\media\\test.txt", "a");
    strcat(appendWord, "\n");
    fputs(appendWord, fptr);
    fclose(fptr);
}
