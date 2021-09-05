#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "displayB.c"
int main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL));
    atexit(Shutdown);
    if (!Initialize())
    {
        exit(1);
    }
    bool quit = false;
    int mXpos, mYpos;
    SDL_Event event;
    Uint32 lastTick = SDL_GetTicks();
    loadAudio();
    while (!quit)
    {
        const Uint8 *kState = SDL_GetKeyboardState(NULL);
        if (kState[SDL_SCANCODE_F] && !menumode && !scoreMode && !appendName)
        {
            UpdateScore(2, 0);
        }
        if (kState[SDL_SCANCODE_ESCAPE] &&!scoreMode && !appendName)
        {
            mainmenu = true;
            quit = true;
        }
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
            {
                if (appendName)
                {
                    appendName = false;
                    menumode = true;
                    rohan.score = player2.score;
                    player2.score = 0;
                    moveCursorPosition = 0;
                    writeScore();
                    RestartGame();
                }
                else if (scoreMode)
                {
                    scoreMode = false;
                }
                else if (menumode)
                {
                    menumode = false;
                }
            }
            if (event.type == SDL_TEXTINPUT && appendName)
            {
                Display(event.text.text, moveCursorPosition, 60);
                strcat(rohan.name, event.text.text);
                moveCursorPosition += 20;
                SDL_RenderPresent(renderer);
            }
            else if (menumode)
            {
                if (event.type == SDL_MOUSEBUTTONDOWN && menumode)
                {
                    SDL_GetMouseState(&mXpos, &mYpos);
                    if (mXpos > 203 && mXpos < 341 && mYpos > 165 && mYpos < 180) //coordinates of new game
                    {
                        menumode = false;
                    }
                    else if (mXpos > 203 && mXpos < 364 && mYpos > 210 && mYpos < 230) //coordinates of high scores
                    {
                        highScoreDisplay();
                    }

                }
            }
        }
        Uint32 curTick = SDL_GetTicks();
        Uint32 diff = curTick - lastTick;
        float elapsed = diff / 1000.0f;
        if (!menumode && !scoreMode && !appendName)
        {
            Update(elapsed);
        }
        lastTick = curTick;
    }
    SDL_Quit();
    return 0;
}
bool Initialize(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("Failed to initialize SDL:%s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Rohan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_SetWindowTitle(window, "Brick-Breaker");

    if (!window)
    {
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        return false;
    }
    if (TTF_Init() == -1)
    {
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("Error opening SDL_MIXER Error:%s\n", Mix_GetError());
    }
    createCharacters();
    ball = MakeBall(BALL_SIZE);
    player1 = MakePlayers();
    player2 = MakePlayers();
    // MakeBricks();
    return true;
}
void Update(float elapsed)
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    UpdateBall(&ball, elapsed);
    if (!menumode && !appendName)
    {
        RenderBall(&ball);

        UpdatePlayers(elapsed);
        RenderPlayers();

        UpdateBricks();

        SDL_RenderPresent(renderer);
    }
}
void Shutdown(void)
{
    if (renderer)
    {

        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }

    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    if (mainmenu)
    {
        system("start mainmenu.exe");
    }
}
bool CoinFlip(void)
{
    return rand() % 2 == 1 ? true : false;
}
Ball MakeBall(int size)
{
    Ball ball = {
        .x = WIDTH / 2,
        .y = HEIGHT - PLAYER_WIDTH,
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
        ball->x = WIDTH / 2;
        ball->y = HEIGHT - PLAYER_WIDTH - PLAYER_MARGIN;
        player2.xPosition = WIDTH / 2 - PLAYER_HEIGHT / 4 - PLAYER_MARGIN;
        const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
        ball->xSpeed = SPEED;
        ball->ySpeed = SPEED;
        return;
    }
    ball->x += ball->xSpeed * elapsed;
    ball->y += ball->ySpeed * elapsed;
    if (ball->x < BALL_SIZE / 2)
    {
        ball->xSpeed = +fabs(ball->xSpeed);
    }
    if (ball->x > WIDTH - BALL_SIZE)
    {
        ball->xSpeed = -fabs(ball->xSpeed);
    }
    if (ball->y < BALL_SIZE / 2)
    {
        ball->ySpeed = fabs(ball->ySpeed);
    }
    if (ball->y > HEIGHT - BALL_SIZE)
    {
        RestartGame();
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
    if (player2.xPosition < PLAYER_WIDTH / 2)
    {
        player2.xPosition = PLAYER_WIDTH / 2;
    }
    if (player2.xPosition > WIDTH - 80)
    {
        player2.xPosition = WIDTH - 80;
    }
    //check if  ball rect overlaps with either player rect
    SDL_Rect ballRect = {
        .x = ball.x - ball.size / 2,
        .y = ball.y - ball.size / 2,
        .w = ball.size,
        .h = ball.size,
    };
    SDL_Rect player2Rect = {
        .x = (int)(player2.xPosition) - PLAYER_WIDTH / 2,
        .y = HEIGHT - PLAYER_WIDTH,
        .w = PLAYER_HEIGHT,
        .h = PLAYER_WIDTH,
    };
    if (SDL_HasIntersection(&ballRect, &player2Rect))
    {
        ball.ySpeed = -fabs(ball.ySpeed); //ball goes left
    }
}
void RenderPlayers(void)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect player2Rect = {
        .x = (int)(player2.xPosition) - PLAYER_WIDTH / 2,
        .y = HEIGHT - PLAYER_WIDTH,
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
    SPEED *= 1.2;
    char *pointsTable = "Level %d";
    int len = snprintf(NULL, 0, pointsTable, roundno);
    char buf[len + 1];
    snprintf(buf, len + 1, pointsTable, roundno);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetWindowTitle(window, buf);
    Display("Congratulations!You Leveled Up", (WIDTH / 2) - 200, HEIGHT / 2 - 30);
    char lvlupshow[50];
    sprintf(lvlupshow, "Score=%d", player2.score);
    Display(lvlupshow, WIDTH / 2 - 100, HEIGHT / 2);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
}

void UpdateBricks(void)
{

    static float sum = 0;
    bool render = false;
    int k, l, m = 255;
    //check if  ball rect overlaps with either player rect
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
        bricks[i].x = 50 + 100 * i;
        bricks[i].y = 50;
    }
    for (int i = 5; i < 10; i++)
    {
        bricks[i].h = BRICK_HEIGHT;
        bricks[i].w = BRICK_WIDTH;
        bricks[i].x = 50 + 100 * (i - 5);
        bricks[i].y = 100;
    }
    for (int i = 10; i < 15; i++)
    {
        bricks[i].h = BRICK_HEIGHT;
        bricks[i].w = BRICK_WIDTH;
        bricks[i].x = 50 + 100 * (i - 10);
        bricks[i].y = 150;
    }

    for (int j = 15; j < 20; j++)
    {
        bricks[j].h = BRICK_HEIGHT;
        bricks[j].w = BRICK_WIDTH;
        bricks[j].x = 50 + 100 * (j - 15);
        bricks[j].y = 200;
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
                Mix_PlayChannel(-1, collision, 0);
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
    menumode = true;
    SDL_SetWindowTitle(window, "Brick-Breaker");
    if (shouldCheck)
    {
        writeScore_withname(player2.score);
    }
    char scoreBuf[50];
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // SDL_RenderPresent(renderer);
    // SDL_RenderClear(renderer);
    if (!appendName)
    {

        sprintf(scoreBuf, "Score:%d", player1.score);
        Display(scoreBuf, WIDTH / 2 - 100, 50);
        Display("GAME OVER!", WIDTH / 2 - 100, 0);
        Display("New Game", WIDTH / 2 - 100, (HEIGHT / 2) - 50);
        Display("High Scores", WIDTH / 2 - 100, (HEIGHT / 2));
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
        shouldCheck = true;
    }
    else if (appendName)
    {
        Display("New high score!congratulations", 0, 0);
        Display("Please Enter your name for records", 0, 30);
    }
    SDL_RenderPresent(renderer);
}

void loadAudio(void)
{
    collision = Mix_LoadWAV("media\\1.wav");
    if (collision == NULL)
    {
        printf("failed to open collisioin file\n");
    }
    else
    {
        printf("Succesfully Opened collision\n");
    }
    bgMusic = Mix_LoadMUS(".wav");
    if (collision == NULL)
    {
        printf("failed to open bgMusic file\n");
    }
}