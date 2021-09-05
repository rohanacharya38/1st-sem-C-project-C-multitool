const int WIDTH = 600;
const int HEIGHT = 400;
const int BALL_SIZE = 10;
int roundno = 1;
int moveCursorPosition;
bool scoreMode = false;
bool appendName = false;
bool shouldCheck = true;
int curScore = 0;
void call(void);
unsigned int count[20] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
typedef struct player_data
{
    char name[40];
    int score;
} data;
data rohan;
data highestScore[5];
typedef struct Ball
{
    float x;
    float y;
    float xSpeed;
    float ySpeed;
    int size;
} Ball;
typedef struct Player
{
    int score;
    float xPosition;

} Player;
typedef struct Bricks
{
    float xPositon;
    float yPosition;
    int size;
} Bricks;
Bricks brick[20];
Ball ball;
Player player1;
Player player2;
const int PLAYER_WIDTH = 15;
const int PLAYER_HEIGHT = 85;
const int PLAYER_MARGIN = 5;
const int BRICK_WIDTH = 60;
const int BRICK_HEIGHT = 10;
float SPEED = 130;
float PLAYER_MOVE_SPEED = 150.0f;
bool served;
bool menumode = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Mix_Chunk *collision = NULL;
Mix_Music *bgMusic = NULL;
SDL_Texture *NewTexture[255];
struct charSize
{
    int height;
    int width;
} character[255];
bool Initialize(void);
void Shutdown(void);
void Update(float);
Ball MakeBall(int size);
void UpdateBall(Ball *ball, float elapsed);
void RenderBall(const Ball *);
Player MakePlayers(void);
void UpdatePlayers(float elapsed);
void RenderPlayers(void);
void UpdateScore(int player, int points);
// void MakeBricks(void);
void UpdateBricks(void);
void RestartGame(void);
void loadAudio(void);
void sortArray(data *element);
void writeScore(void);
void getScore_withname(void);
void writeScore_withname(int points);
bool updateScoreMode = false;
// void RenderBricks(void);
SDL_Color textColor = {255, 255, 255};
bool mainmenu;
void Display(char *inp, int X, int Y)
{
    SDL_Rect dest;
    dest.x = X;
    dest.y = Y;
    int i = 0;
    while (*inp)
    {
        dest.x += i;
        dest.w = character[*inp].width;
        dest.h = character[*inp].height;
        SDL_RenderCopy(renderer, NewTexture[(int)*inp], NULL, &dest);
        i = dest.w;
        inp++;
    }
}
void createCharacters(void)
{
    TTF_Font *gFont;
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

void sortArray(data element[])
{
    data temp;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (element[j].score < element[j + 1].score)
            {
                temp = element[j];
                element[j] = element[j + 1];
                element[j + 1] = temp;
            }
        }
    }
}
void highScoreDisplay(void)
{
    char scorebuf[500];
    char Totalscore[500];
    getScore_withname();
    SDL_RenderClear(renderer);
    Display("High Scores Table", (WIDTH / 2) - 100, 0);
    for (int i = 0; i < 5; i++)
    {
        sprintf(scorebuf, "%10s", highestScore[i].name);
        Display(scorebuf, WIDTH / 2 - 200, 40 + i * 40);
        sprintf(Totalscore,"%10d",highestScore[i].score);
        Display(Totalscore,WIDTH-200,40 + i * 40);
    }
    SDL_RenderPresent(renderer);
    scoreMode = true;
    menumode = false;
}
void writeScore()
{
    getScore_withname();
    sortArray(highestScore);
    FILE *fp;
    fp = fopen("highScore", "wb");
    highestScore[4].score = rohan.score;
    strcpy(highestScore[4].name, rohan.name);
    fwrite(highestScore, sizeof(highestScore), 1, fp);
    fclose(fp);
    rohan.score = 0;
    strcpy(rohan.name, "");
}
void getScore_withname(void)
{
    data player[5];
    int k = 0;
    FILE *fp;
    fp = fopen("highScore", "rb");
    if (fp == NULL)
    {
        printf("file not present in directory->creating it");
        fp = fopen("highScore", "wb");
        for (int i = 0; i < 5; i++)
        {
            strcpy(player[i].name, " ");
            player[i].score = 0;
        }
        fwrite(&player, sizeof(player), 1, fp);
        fclose(fp);
        fp = fopen("highScore", "rb");
    }
    fread(highestScore, sizeof(highestScore), 1, fp);
    sortArray(highestScore);
    fclose(fp);
}
void writeScore_withname(int points)
{
    bool newHigh = false;
    getScore_withname();
    for (int i = 0; i < 5; i++)
    {
        if ((highestScore[i].score) < points)
        {
            newHigh = true;
        }
    }
    if (newHigh)
    {
        appendName = true;
        shouldCheck = false;
        curScore = points;
    }
}
