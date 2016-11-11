#include "graphic.h"
#include "Labyrinthe.h"

int main(int argc, char *argv[])
{
    FILE* fichier = NULL;
    fichier = fopen("data/Size.txt","r");
    int sizeX=0;
    int sizeY=0;
    fscanf(fichier,"%d",&sizeX);
    fscanf(fichier,"%d",&sizeY);
    CreateWindow(sizeX, sizeY, "Labyrinthe");
    Labyrinthe lab;
    int taille = 30;  //A changer si on veut changer la taille du labyrinthe
    sizeX=sizeX/taille;
    sizeY=sizeY/taille;
    lab.Init(sizeX,sizeY,1,1);

    int x=1;
    int y=1;


    while (!KeyGet(SDLK_ESCAPE) && !StickGetClick(0, 7))
    {
        for (int i=0;i<=sizeX;i++)
        {
            for(int j=0;j<=sizeY;j++)
            {
                Vec2 p0=CreateVec2(i*taille,j*taille);
                Vec2 p1=CreateVec2(p0.x+taille,p0.y);
                Vec2 p2=CreateVec2(p0.x+taille,p0.y+taille);
                Vec2 p3=CreateVec2(p0.x,p0.y+taille);
                if (lab.GetCase(i,j)==ECase_Wall)
                {
                    DrawRect(p0,p1,p2,p3,CreateColor(200,0,0));
                }
                if (lab.GetCase(i,j)==ECase_Way)
                {
                    DrawRect(p0,p1,p2,p3,CreateColor(255,255,255));
                }
                if (lab.GetCase(i,j)==ECase_Start)
                {
                    DrawRect(p0,p1,p2,p3,CreateColor(0,250,0));
                }
                if (lab.GetCase(i,j)==ECase_End)
                {
                    DrawRect(p0,p1,p2,p3,CreateColor(250,250,0));
                }
            }
        }


        if(lab.GetCase(x,y)!=ECase_End)
        {
            if(lab.GetCase(x-1,y)==0 || lab.GetCase(x+1,y)==0 || lab.GetCase(x,y-1)==0 || lab.GetCase(x,y+1)==0 || lab.GetCase(x-1,y)==ECase_End || lab.GetCase(x+1,y)==ECase_End || lab.GetCase(x,y-1)==ECase_End || lab.GetCase(x,y+1)==ECase_End)
            {
                lab.SetCase(x,y,ECase_Way);
                if(lab.GetCase(x+1,y)==ECase_None)
                    x+=1;
                else if(lab.GetCase(x-1,y)==ECase_None)
                    x-=1;
                else if(lab.GetCase(x,y+1)==ECase_None)
                    y+=1;
                else if(lab.GetCase(x,y-1)==ECase_None)
                    y-=1;
            }
            else if (lab.GetCase(x-1,y)!=0 && lab.GetCase(x+1,y)!=0 && lab.GetCase(x,y-1)!=0 && lab.GetCase(x,y+1)!=0)
            {
                lab.SetCase(x,y,ECase_Nop);
                if(lab.GetCase(x-1,y)==ECase_Way)
                    x-=1;
                else if(lab.GetCase(x+1,y)==ECase_Way)
                    x+=1;
                else if(lab.GetCase(x,y+1)==ECase_Way)
                    y+=1;
                else if(lab.GetCase(x,y-1)==ECase_Way)
                    y-=1;
                }
        }

        RefreshScreen();
    }

    return 0;
}
