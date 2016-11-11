#ifndef __LABYRINTHE__H_
#define __LABYRINTHE__H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

enum EDirection {
    EDir_None = 0,
    EDir_Up,
    EDir_Down,
    EDir_Left,
    EDir_Right,
};

enum ECase {
    ECase_None = 0,
    ECase_Wall,
    ECase_Start,
    ECase_End,
    ECase_Nop,
    ECase_Way
};

typedef struct Labyrinthe
{
    int *lab = NULL;
    int sizeX, sizeY;
    int sizeWay, endX, endY;

    ECase GetCase(int x, int y)
    {
        if (lab && x>=0 && x<sizeX && y>=0 && y<sizeY)
            return (ECase)lab[y*sizeX+x];
        return ECase_Wall;
    }
    //init la case a c
    void SetCase(int x, int y, ECase c)
    {
        if (lab && x>=0 && x<sizeX && y>=0 && y<sizeY)
            lab[y*sizeX+x] = (int)c;
    }

    EDirection LabDirection(int startX, int startY)
    {
        //on compte le nombre de direction que l'on peut prendre
        bool up, down, left, right;
        int nbDir = 0;
        if (startX < sizeX-1 && startY < sizeY-2 && startX > 0 &&
            GetCase(startX,startY+1) == ECase_Wall &&
            GetCase(startX,startY+2) == ECase_Wall &&
            GetCase(startX+1,startY+1) == ECase_Wall &&
            GetCase(startX-1,startY+1) == ECase_Wall)
        {
            up = true;
            nbDir++;
        }
        else
            up = false;

        if (startX < sizeX-1 && startY > 1 && startX > 0 &&
            GetCase(startX,startY-1) == ECase_Wall &&
            GetCase(startX,startY-2) == ECase_Wall &&
            GetCase(startX+1,startY-1) == ECase_Wall &&
            GetCase(startX-1,startY-1) == ECase_Wall)
        {
            down = true;
            nbDir++;
        }
        else
            down = false;

        if (startY < sizeY-1 && startX > 1 && startY > 0 &&
            GetCase(startX-1,startY) == ECase_Wall &&
            GetCase(startX-2,startY) == ECase_Wall &&
            GetCase(startX-1,startY+1) == ECase_Wall &&
            GetCase(startX-1,startY-1) == ECase_Wall)
        {
            left = true;
            nbDir++;
        }
        else
            left = false;

        if (startY < sizeY-1 && startX < sizeX-2 && startY > 0 &&
            GetCase(startX+1,startY) == ECase_Wall &&
            GetCase(startX+2,startY) == ECase_Wall &&
            GetCase(startX+1,startY+1) == ECase_Wall &&
            GetCase(startX+1,startY-1) == ECase_Wall)
        {
            right = true;
            nbDir++;
        }
        else
            right = false;
        //si on ne peut prendre aucune direction fin de la fonction
        if (!nbDir)
            return EDir_None;
        //on prend un direction aléatoirement
        int dir = rand()%nbDir;
        if (up && !dir)
            return EDir_Up;
        else if(up)
            dir--;

        if (down && !dir)
            return EDir_Down;
        else if(down)
            dir--;

        if (left && !dir)
            return EDir_Left;
        else if(left)
            dir--;

        if (right)
            return EDir_Right;
        else
            return EDir_None;
    }

    void Mined(int startX, int startY, int sizeStart)
    {
        if (sizeStart>sizeWay)
        {
            sizeWay = sizeStart;
            endX = startX;
            endY = startY;
        }
        while(true)
        {
            //on choisi une direction
            EDirection dir = LabDirection(startX, startY);
            //si on ne peut prendre aucune direction alors stop
            if (!dir)
                return;
            //on creuse la direction
            int posX = startX;
            int posY = startY;
            if(dir == EDir_Up)
                posY++;
            if(dir == EDir_Down)
                posY--;
            if(dir == EDir_Left)
                posX--;
            if(dir == EDir_Right)
                posX++;
            SetCase(posX, posY, ECase_None);
            //on demande a la case qu'on vien de creuser de creuser a sont tour
            Mined(posX, posY, sizeStart+1);
        }
    }

    void Print()
    {
        for(int j=sizeY-1; j>=0; j--)
        {
            for(int i=0; i<sizeX; i++)
            {
                if (GetCase(i, j))
                    printf("%c", (char)219);
                else
                    printf(" ");
            }
            printf("\n");
        }
    }

    void Init(int _sizeX, int _sizeY, int _startX=1, int _startY=1)
    {
        //si on avez déjà de la mémoire alouer on la libère
        if (lab)
            free(lab);
        //on crée notre tableau de int qui contien notre labyrinthe
        sizeX = _sizeX;
        sizeY = _sizeY;
        lab = (int*)malloc(sizeof(int)*sizeX*sizeY);
        //init de l'aléa
        srand(time(NULL));
        //on initialise toute les case a mur
        for(int j=0; j<sizeX*sizeY; j++)
            lab[j] = (int)ECase_Wall;
        SetCase(_startX, _startY, ECase_Start);
        endX = _startX;
        endY = _startY;
        sizeWay = 0;
        //on commence a creuser
        Mined(_startX, _startY, 0);
        SetCase(endX, endY, ECase_End);
    }

    ~Labyrinthe()
    {
        free(lab);
        lab = NULL;
    }

}Labyrinthe;
#endif
