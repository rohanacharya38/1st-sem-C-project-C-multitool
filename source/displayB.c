// const int WIDTH = 600;
// const int HEIGHT = 400;
void DisplayB(char *inp, int X, int Y)
{
    SDL_Rect dest;
    dest.x = 300+X;
    dest.y = 150+Y;
    int i=0;
    while (*inp)
    {
        dest.x+=i;
        dest.w = character[*inp].width;
        dest.h = character[*inp].height;
        i=dest.w;
        SDL_RenderCopy(renderer, NewTexture[(int)*inp], NULL, &dest);
        inp++;
    }
}

// void sortArray(data element[])
// {
//     data temp;
//     for (int i = 0; i < 5; i++)
//     {
//         for (int j = 0; j < 5; j++)
//         {
//             if (element[j].score < element[j + 1].score)
//             {
//                 temp = element[j];
//                 element[j] = element[j + 1];
//                 element[j + 1] = temp;
//             }
//         }
//     }
// }
// void highScoreDisplay(void)
// {
//     char scorebuf[500];
//     char Totalscore[500];
//     getScore_withname();
//     SDL_RenderClear(renderer);
//     DisplayB("High Scores Table", (600 / 2) - 100, 0);
//     for (int i = 0; i < 5; i++)
//     {
//         sprintf(scorebuf, "%10s", highestScore[i].name);
//         DisplayB(scorebuf, 600 / 2 - 200, 40 + i * 40);
//         sprintf(Totalscore,"%10d",highestScore[i].score);
//         DisplayB(Totalscore,600,40 + i * 40);
//     }
//     SDL_RenderPresent(renderer);
//     scoreMode = true;
//     menumode = false;
// }
// void writeScore()
// {
//     getScore_withname();
//     sortArray(highestScore);
//     FILE *fp;
//     fp = fopen("../media/highScore", "wb");
//     highestScore[4].score = rohan.score;
//     strcpy(highestScore[4].name, rohan.name);
//     fwrite(highestScore, sizeof(highestScore), 1, fp);
//     fclose(fp);
//     rohan.score = 0;
//     strcpy(rohan.name, "");
// }
// void getScore_withname(void)
// {
//     data player[5];
//     int k = 0;
//     FILE *fp;
//     fp = fopen("../media/highScore", "rb");
//     if (fp == NULL)
//     {
//         printf("file not present in directory->creating it");
//         fp = fopen("../media/highScore", "wb");
//         for (int i = 0; i < 5; i++)
//         {
//             strcpy(player[i].name, " ");
//             player[i].score = 0;
//         }
//         fwrite(&player, sizeof(player), 1, fp);
//         fclose(fp);
//         fp = fopen("../media/highScore", "rb");
//     }
//     fread(highestScore, sizeof(highestScore), 1, fp);
//     sortArray(highestScore);
//     fclose(fp);
// }
// void writeScore_withname(int points)
// {
//     bool newHigh = false;
//     getScore_withname();
//     for (int i = 0; i < 5; i++)
//     {
//         if ((highestScore[i].score) < points)
//         {
//             newHigh = true;
//         }
//     }
//     if (newHigh)
//     {
//         appendName = true;
//         shouldCheck = false;
//         curScore = points;
//     }
// }
