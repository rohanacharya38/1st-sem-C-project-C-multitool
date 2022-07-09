#include "displayB.c" // const int WIDTH = 600;const int WIDTH = 1200;
// const int HEIGHT = 700; //Width and height of screen
// const int HEIGHT = 400;
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <time.h>
#include <math.h>
#include <SDL_ttf.h>
int stoi(char str[])
{
    return (int)str[0];
}
int BrickBreak(SDL_Event *event)
{
    const Uint8 *kState = SDL_GetKeyboardState(NULL);
    if (kState[SDL_SCANCODE_F] && !menumode && !scoreMode && !appendName)
    {
        UpdateScore(2, 0);
    }
    if (kState[SDL_SCANCODE_ESCAPE] && !scoreMode && !appendName)
    {
        menu = true;
    }
    {
        if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_RETURN)
        {
            // if (appendName)
            // {
            //     appendName = false;
            //     menumode = true;
            //     rohan.score = player2.score;
            //     player2.score = 0;
            //     moveCursorPosition = 0;
            //     writeScore();
            //     RestartGame();
            // }
            if (scoreMode)
            {
                scoreMode = false;
            }
            else if (menumode)
            {
                menumode = false;
            }
        }
        //  if (event->type == SDL_TEXTINPUT && appendName &&textinput)
        // {

        //     char str[]= {event->text.text[0],'\0'};
        //     DisplayB(str, moveCursorPosition, 60);
        //     strcat(rohan.name, str);
        //     moveCursorPosition+=character[stoi(str)].width;
        //     SDL_RenderPresent(renderer);
        // }
        //  if (menumode)
        // {
        //     if (event->type == SDL_MOUSEBUTTONDOWN && menumode)
        //     {
        //         SDL_GetMouseState(&mXpos, &mYpos);
        //         if (mXpos > 505 && mXpos < 610 && mYpos > 307 && mYpos < 321) //coordinates of new game
        //         {
        //             menumode = false;
        //         }
        //         // else if (mXpos >506  && mXpos < 633 && mYpos > 356 && mYpos < 370) //coordinates of high scores
        //         // {
        //         //     highScoreDisplay();
        //         // }
        //     }
        // }
    }
    if (!menumode && !scoreMode && !appendName)
    {
        updateB(0.025);
    }

    return 0;
}

void updateB(float elapsed)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 300, 150, 300, 550);
    SDL_RenderDrawLine(renderer, 900, 150, 900, 550);
    SDL_RenderDrawLine(renderer, 300, 150, 900, 150);
    SDL_RenderDrawLine(renderer, 300, 550, 900, 550);
    UpdateBall(&ball, elapsed);
    char score_buffer[100] = "";
    sprintf(score_buffer, "SCORE::%d", player1.score);
    DisplayB(score_buffer, -200, -50);
    if (!menumode && !appendName)
    {
        RenderBall(&ball);

        UpdatePlayers(elapsed);
        RenderPlayers();

        UpdateBricks();

        SDL_RenderPresent(renderer);
    }
}

bool CoinFlip(void)
{
    return rand() % 2 == 1 ? true : false;
}
Ball MakeBall(int size)
{
    Ball ball = {
        .x = 600,
        .y = 550 - PLAYER_WIDTH,
        .size = size,
        .xSpeed = SPEED * (CoinFlip() ? 1 : -1),
        .ySpeed = SPEED * (CoinFlip() ? 1 : -1),
    };
    return ball;
}
void RenderBall(const Ball *ball)
{
    int size = ball->size;
    int halfSize = size / 2;

    SDL_Rect rect =
        {
            .x = ball->x - halfSize,
            .y = ball->y - halfSize,
            .w = size,
            .h = size,
        };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}
void UpdateBall(Ball *ball, float elapsed)
{
    if (!served)
    {
        ball->x = 600;
        ball->y = 550 - PLAYER_WIDTH - PLAYER_MARGIN;
        player2.xPosition = WIDTH / 2 - PLAYER_HEIGHT / 4 - PLAYER_MARGIN;
        ball->xSpeed = SPEED;
        ball->ySpeed = SPEED;
        return;
    }
    ball->x += ball->xSpeed * elapsed;
    ball->y += ball->ySpeed * elapsed;
    if (ball->x < 300 + BALL_SIZE)
    {
        ball->xSpeed = +fabs(ball->xSpeed);
    }
    if (ball->x > 900 - BALL_SIZE / 2)
    {
        ball->xSpeed = -fabs(ball->xSpeed);
    }
    if (ball->y < 150 + BALL_SIZE)
    {
        ball->ySpeed = fabs(ball->ySpeed);
    }
    if (ball->y > 560 - BALL_SIZE / 2)
    {
        RestartGame();
        // ball->ySpeed=-fabs(ball->ySpeed);
    }
}
Player MakePlayers(void)
{
    Player player = {
        .xPosition = WIDTH / 2 - PLAYER_HEIGHT / 4 - PLAYER_MARGIN,
    };
    return player;
}
void UpdatePlayers(float elapsed)
{
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    if (keyboardState[SDL_SCANCODE_SPACE])
    {
        served = true;
    }
    if (keyboardState[SDL_SCANCODE_LEFT])
    {
        player2.xPosition -= PLAYER_MOVE_SPEED * elapsed;
    }
    if (keyboardState[SDL_SCANCODE_RIGHT])
    {
        player2.xPosition += PLAYER_MOVE_SPEED * elapsed;
    }
    if (player2.xPosition < PLAYER_WIDTH / 2 + 300)
    {
        player2.xPosition = PLAYER_WIDTH / 2 + 300;
    }
    if (player2.xPosition > 900 - 80)
    {
        player2.xPosition = 900 - 80;
    }
    // check if  ball rect overlaps with either player rect
    SDL_Rect ballRect = {
        .x = ball.x - ball.size / 2,
        .y = ball.y - ball.size / 2,
        .w = ball.size,
        .h = ball.size,
    };
    SDL_Rect player2Rect = {
        .x = (int)(player2.xPosition) - PLAYER_WIDTH / 2,
        .y = 550 - PLAYER_WIDTH,
        .w = PLAYER_HEIGHT,
        .h = PLAYER_WIDTH,
    };
    if (SDL_HasIntersection(&ballRect, &player2Rect))
    {
        ball.ySpeed = -fabs(ball.ySpeed); // ball goes left
    }
}
void RenderPlayers(void)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect player2Rect = {
        .x = (int)(player2.xPosition) - PLAYER_WIDTH / 2,
        .y = 550 - PLAYER_WIDTH,
        .w = PLAYER_HEIGHT,
        .h = PLAYER_WIDTH,
    };
    SDL_RenderFillRect(renderer, &player2Rect);
}
void UpdateScore(int player, int points)
{
    updateScoreMode = true;
    served = false;
    roundno++;
    for (int i = 0; i < 20; i++)
    {
        count[i] = roundno + 1;
    }
    PLAYER_MOVE_SPEED *= 1.3;
    SPEED += 30;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    DisplayB("Congratulations!You Leveled Up", (WIDTH / 2) - 200, HEIGHT / 2 - 30);
    char lvlupshow[50];
    sprintf(lvlupshow, "Score=%d", player2.score);
    DisplayB(lvlupshow, WIDTH / 2 - 100, HEIGHT / 2);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
}

void UpdateBricks(void)
{

    static float sum = 0;
    bool render = false;
    int k, l, m = 255;
    // check if  ball rect overlaps with either player rect
    SDL_Rect ballRect = {
        .x = ball.x - ball.size / 2,
        .y = ball.y - ball.size / 2,
        .w = ball.size,
        .h = ball.size,
    };
    SDL_Rect bricks[20];
    for (int i = 0; i < 5; i++)
    {
        bricks[i].h = BRICK_HEIGHT;
        bricks[i].w = BRICK_WIDTH;
        bricks[i].x = 300 + 50 + 100 * i;
        bricks[i].y = 50 + 150;
    }
    for (int i = 5; i < 10; i++)
    {
        bricks[i].h = BRICK_HEIGHT;
        bricks[i].w = BRICK_WIDTH;
        bricks[i].x = 300 + 50 + 100 * (i - 5);
        bricks[i].y = 150 + 100;
    }
    for (int i = 10; i < 15; i++)
    {
        bricks[i].h = BRICK_HEIGHT;
        bricks[i].w = BRICK_WIDTH;
        bricks[i].x = 300 + 50 + 100 * (i - 10);
        bricks[i].y = 150 + 150;
    }

    for (int j = 15; j < 20; j++)
    {
        bricks[j].h = BRICK_HEIGHT;
        bricks[j].w = BRICK_WIDTH;
        bricks[j].x = 300 + 50 + 100 * (j - 15);
        bricks[j].y = 150 + 200;
    }

    for (int i = 0; i < 20; i++)
    {
        if (count[i] != 0 && count > 0)
        {
            render = true;
        }
        if (count[i] <= 0)
        {
            render = false;
        }
        while (render)
        {
            if (SDL_HasIntersection(&ballRect, &bricks[i]))
            {
                player2.score += 50;
                player1.score += 50;
                count[i]--;
                if (ball.ySpeed > 0)
                {
                    ball.ySpeed = -fabs(ball.ySpeed);
                }
                else
                {
                    ball.ySpeed = fabs(ball.ySpeed);
                }
            }
            break;
        }
        while (render)
        {
            k = i >= 5 && i < 10 ? -255 : 0;
            l = i >= 10 && i < 15 ? -255 : 0;
            m = i >= 10 ? -255 : 0;
            SDL_SetRenderDrawColor(renderer, 255 + k, 255 + l, 255 + m, 255);
            SDL_RenderFillRect(renderer, &bricks[i]);
            break;
        }
        if (count[i] < 0)
        {
            count[i] = 0;
        }
    }

    if (count[1] == 0 && count[2] == 0 && count[3] == 0 && count[4] == 0 && count[5] == 0 && count[6] == 0 && count[7] == 0 && count[8] == 0 && count[9] == 0 && count[0] == 0 &&
        count[10] == 0 && count[12] == 0 && count[13] == 0 && count[14] == 0 && count[15] == 0 && count[16] == 0 && count[17] == 0 && count[18] == 0 && count[19] == 0 && count[11] == 0)
    {
        UpdateScore(2, 100);
    }
}

void RestartGame(void)
{
    // menumode = true;
    // if (shouldCheck)
    // {
    //     writeScore_withname(player2.score);
    // }

    char scoreBuf[50];
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // SDL_RenderClear(renderer);
    // SDL_RenderPresent(renderer);
    // SDL_RenderClear(renderer);
 
    // DisplayB("New Game", 600 / 2 - 100, (400 / 2) - 50);
    // DisplayB("High Scores", 600 / 2 - 100, (400 / 2));
    served = false;
    player2.score = 0;
    player1.score = 0;
    roundno = 1;
    for (int i = 0; i < 20; i++)
    {
        count[i] = 1;
    }
    PLAYER_MOVE_SPEED = 150.0f;
    SPEED = 140;
    SDL_RenderPresent(renderer);
    // else if (appendName)
    // {
    //     DisplayB("New high score!congratulations", 0, 0);
    //     DisplayB("Please Enter your name for records", 0, 30);
    // }
}
