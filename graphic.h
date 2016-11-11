/**
*   \file graphic.h
*   \author Thiebaud Vannier
*   \brief Moteur graphique
*   \version 1.3
*/
#ifndef __GRAPHIC_HEADER_
#define __GRAPHIC_HEADER_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cstring>
#include <cstdlib>

#pragma GCC diagnostic ignored "-Wwrite-strings"

/** \struct Vec2
*   \brief Vecteur 2 dimension
*
* Peut �galement �tre vue comme un simple point.
*/
typedef struct Vec2
{
    float x;
    float y;

    inline Vec2 operator=(Vec2 a) {
        x=a.x;
        y=a.y;
        return a;
    }

    inline Vec2 operator+(Vec2 a) {
        return {a.x+x,a.y+y};
    }

    inline Vec2 operator+(double a) {
        return {x+(float)a,y+(float)a};
    }

    inline Vec2 operator-(Vec2 a) {
        return {x-a.x,y-a.y};
    }

    inline Vec2 operator-(double a) {
        return {x-(float)a,y-(float)a};
    }

    inline Vec2 operator*(double a) {
        return {x*(float)a,y*(float)a};
    }

    inline Vec2 operator*(Vec2 a) {
        return {x*a.x,y*a.y};
    }

    inline Vec2 operator/(double a) {
        return {x/(float)a,y/(float)a};
    }

    inline Vec2 operator/(Vec2 a) {
        return {x/a.x,y/a.y};
    }

    inline bool operator==(Vec2 a) {
       if (a.x==x && a.y== y)
          return true;
       else
          return false;
    }
}Vec2;

/** \brief permet d'obtenir un vecteur 2D en fonction de x et de y.
 *
 * \param x float
 * \param y float
 * \return Vec2
 *
 */
Vec2 CreateVec2(float x, float y);

/** \brief Calcule la distance entre 2 points.
 *
 * \param point1 Vec2
 * \param point2 Vec2
 * \return float
 *
 */
float Distance(Vec2 point1, Vec2 point2);

/** \struct Color
*   \brief Couleur.
*
* Contient les 4 composantes de couleur de base (rouge, vert, bleu, alpha)
* La variable r pour la composante rouge.
* La variable g pour la composante vert.
* La variable b pour la composante bleu.
* La variable a pour la composante alpha, c'est � dire la transparence.
*/
typedef struct Color
{
    char r, g, b, a;
}Color;
/** \brief Permet d'obtenir une couleur en fonction des 3 composantes de couleur rouge, vert et bleu. Chaque composante est comprise entre 0 et 255.
 *
 * \param red int Rouge
 * \param green int Vert
 * \param blue int Bleu
 * \return Color
 *
 */
Color CreateColor(int red, int green, int blue);

/** \brief Permet d'obtenir une couleur en fonction des 4 composantes de couleur rouge, vert, bleu et alpha. Chaque composante est comprise entre 0 et 255.
 *
 * \param red int Rouge
 * \param green int Vert
 * \param blue int Bleu
 * \param alpha int Transparent
 * \return Color
 *
 */
Color CreateColor(int red, int green, int blue, int alpha);

struct MyImage;

/** \struct Image
*   \brief Contient une image.
*/
typedef struct MyImage* Image;

/** \brief Permet de charger une image en pr�cisant son nom. Peut charger les images aux formats BMP, PNG, GIF et JPEG.
 *
 * \param name char* Le nom de l'image et son chemin d'acc�s. Exemple : "data/img.png"
 * \return Image
 *
 */
Image CreateImage(char *name);

/** \brief Lib�re la m�moire occup�e par une image. Attention une fois lib�r�e, une image ne peut plus �tre utilis�e.
 *
 * \param img Image
 * \return void
 *
 */
void FreeImage(Image img);

/** \brief Applique une position � une image.
 *
 * \param img Image
 * \param pos Vec2 la position � appliquer � l'image.
 * \return void
 *
 */
void ImgSetPosition(Image img, Vec2 pos);

/** \brief Applique une position � une image.
 *
 * \param img Image
 * \param x int La nouvelle coordonn�e en x de l'image
 * \param y int La nouvelle coordonn�e en y de l'image
 * \return void
 *
 */
void ImgSetPosition(Image img, int x, int y);

/** \brief Applique une rotation � une image.
 *
 * \param img Image
 * \param angle float en degr�s.
 * \return void
 *
 */
void ImgSetRotation(Image img, float angle);

/** \brief Applique un zoom � une image.
 * Si scale vaut 1 alors il n'y a pas de zoom.
 * Si scale est sup�rieur � 1 alors l'image sera agrendie.
 * Si scale est inferieur � 1 alors l'image sera rapetiss�e.
 *
 * \param img Image
 * \param scale float
 * \return void
 *
 */
void ImgSetScale(Image img, float scale);

/** \brief Applique un zoom diff�rent en x et en y � une image.
 * Si scale vaut 1 alors il n'y a pas de zoom.
 * Si scale est sup�rieur � 1 alors l'image sera agrendie.
 * Si scale est inferieur � 1 alors l'image sera rapetiss�e.
 *
 * \param img Image
 * \param scaleX float Zoom en X.
 * \param scaleY float Zoom en Y
 * \return void
 *
 */
void ImgSetScale(Image img, float scaleX, float scaleY);

/** \brief Applique un zoom diff�rent en x et en y � une image.
 * Si scale vaut 1 alors il n'y a pas de zoom.
 * Si scale est sup�rieur � 1 alors l'image sera agrendie.
 * Si scale est inferieur � 1 alors l'image sera rapetiss�e.
 *
 * \param img Image
 * \param scale Vec2
 * \return void
 *
 */
void ImgSetScale(Image img, Vec2 scale);

/** \brief Applique une couleur � une image.
 *
 * \param img Image
 * \param color Color
 * \return void
 *
 */
void ImgSetColor(Image img, Color color);

/** \brief R�cup�re la position d'une image.
 *
 * \param img Image
 * \return Vec2 La position de l'image.
 *
 */
Vec2 ImgGetPosition(Image img);

/** \brief R�cup�re la rotation d'une image en degr�.
 *
 * \param img Image
 * \return float Rotation de l'image.
 *
 */
float ImgGetRotation(Image img);

/** \brief R�cup�re le zoom d'une image.
 *
 * \param img Image
 * \return Vec2 Zoom de l'image
 *
 */
Vec2 ImgGetScale(Image img);

/** \brief R�cup�re la couleur d'affichage de l'image.
 *
 * \param img Image
 * \return Color La couleur d'affichage de l'image.
 *
 */
Color ImgGetColor(Image img);

/** \brief R�cup�re la taille d'une image.
 *
 * \param img Image
 * \return Vec2 La taille de l'image.
 *
 */
Vec2 ImgGetSize(Image img);

/** \brief R�cup�re la taille r�el d'une image.
 *
 * \param img Image
 * \return Vec2 La taille de l'image multipli� par son zoom.
 *
 */
Vec2 ImgGetRealSize(Image img);

/** \brief permet de conetre la colision entre 2 image
 *
 * \param img Image
 * \param img2 Image
 * \return bool renvoie true si il y a bien une colision entre les 2 image.
 *
 */
bool ImgGetCollision(Image img, Image img2);

/** \brief permet de conetre la colision entre 2 image (beaucoups plus rapide que ImgGetCollision mais ne prend pas en compte la rotation des image)
 *
 * \param img Image
 * \param img2 Image
 * \return bool renvoie true si il y a bien une colision entre les 2 image.
 *
 */
bool ImgGetCollisionLite(Image img, Image img2);

struct MyText;

/** \struct Text
*   \brief Contient un texte.
*/
typedef struct MyText* Text;

/** \brief Permet de charger un texte.
 *
 * \param text const char*
 * \param color Color La couleur du texte.
 * \param size int La taille du texte.
 * \return Text
 *
 */
Text CreateText(const char* text, Color color, int size);

/** \brief Lib�re la m�moire occup�e par un texte. Attention, une fois lib�r� un texte ne peut plus �tre utilis�.
 *
 * \param text Text
 * \return void
 *
 */
void FreeText(Text text);

/** \brief Change le texte affich� par un Text.
 *
 * \param txt Text
 * \param text const char*
 * \param ... prend comme argument toute les variables a placer dans la chaine (comme dans un printf)
 * \return void
 *
 */
void TextSetText(Text txt, const char* text, ...);

/** \brief Applique une position � un texte.
 *
 * \param txt Text
 * \param position Vec2
 * \return void
 *
 */
void TextSetPosition(Text txt, Vec2 position);

/** \brief Applique une couleur � un texte.
 *
 * \param txt Text
 * \param color Color
 * \return void
 *
 */
void TextSetColor(Text txt, Color color);

/** \brief Change la taille d'un texte.
 *
 * \param txt Text
 * \param size int
 * \return void
 *
 */
void TextSetSize(Text txt, int size);

/** \brief R�cup�re le texte affich� par un Text.
 *
 * \param txt Text
 * \return const char*
 *
 */
const char* TextGetText(Text txt);

/** \brief R�cup�re la position d'un texte.
 *
 * \param txt Text
 * \return Vec2
 *
 */
Vec2 TextGetPosition(Text txt);

/** \brief R�cup�re la couleur d'un texte.
 *
 * \param txt Text
 * \return Color
 *
 */
Color TextGetColor(Text txt);

/** \brief R�cup�re la taille d'un texte.
 *
 * \param txt Text
 * \return int
 *
 */
int TextGetSize(Text txt);

/** \brief Rend un texte modifiable par l'utilisateur ou pas.
 *
 * \param txt Text
 * \param focus bool
 *
 */
void TextSetAlterable(Text txt, bool alterable);

/** \brief Permet de savoir si un texte est modifiable par l'utilisateur.
 *
 * \param txt Text
 * \return bool
 *
 */
bool TextGetAlterable(Text txt);

/** \brief Donne le focus a un Text. Si un Text a le focus alors les touches du clavier permettront de le modifier.
 *
 * \param txt Text
 *
 */
void TextSetFocus(Text txt);

/** \brief Enl�ve le focus des textes.
 *
 * \return void
 *
 */
void TextShootFocus();

/** \brief Permet de savoir si un texte a le focus.
 *
 * \param txt Text
 * \return bool
 *
 */
bool TextGetFocus(Text txt);

/** \brief Cr��e une nouvelle fen�tre.
 *
 * \param width int Largeur de la fen�tre.
 * \param height int Hauteur de la fen�tre.
 * \param name char* Nom de la fen�tre.
 * \return void
 *
 */
void CreateWindow(int width, int height, char* name);

/** \brief R�cup�re la taille de la fen�tre cr��e.
 *
 * \return Vec2
 *
 */
Vec2 WindowGetSize();

/** \brief Cloture l'affichage d'une sc�ne.
 * Pour afficher des choses dans une fen�tre il faut appeler des fonctions Draw puis, une fois que vous avez affich� tout ce dont vous aviez besoin, appelle cette fonction.
 *
 * \return void
 *
 */
void RefreshScreen(bool printFPS = false);

/** \brief Affiche un triangle.
 * Prend en param�tre les 3 points qui d�finissent le triangle ainsi que sa couleur.
 *
 * \param p1 Vec2
 * \param p2 Vec2
 * \param p3 Vec2
 * \param c Color
 * \return void
 *
 */
void DrawTriangles(Vec2 p1, Vec2 p2, Vec2 p3, Color c);

/** \brief Affiche une forma a 4 face.
 * Prend en param�tre les 4 points qui d�finissent la forme ainsi que sa couleur.
 *
 * \param p0 Vec2
 * \param p1 Vec2
 * \param p2 Vec2
 * \param p3 Vec2
 * \param c Color
 * \return void
 *
 */
void DrawRect(Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3, Color c);

/** \brief Affiche une image.
 *
 * \param img Image
 * \return void
 *
 */
void DrawImage(Image img);

/** \brief Affiche un texte.
 *
 * \param txt Text
 * \return void
 *
 */
void DrawText(Text txt);

///void DrawTextArea(TextArea txt);

/** \brief Permet de savoir si une touche du clavier est appuy�e.
 * Peut prendre en parametre toutes les valeurs de cette page : https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkey.html
 *
 * \param key int
 * \return bool Renvoie vrai si la touche est appuy�e.
 *
 */
bool KeyGet(int key);

/** \brief Permet de r�cup�rer un appui sur une touche du clavier.
 * Peut prendre en param�tre toutes les valeurs de cette page : https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkey.html
 *
 * \param key int
 * \return bool Renvoie vrai qu'au moment o� on vient d'appuyer sur la touche.
 *
 */
bool KeyGetOneShot(int key);

/** \brief R�cup�re la position de la souris.
 *
 * \return Vec2
 *
 */
Vec2 MouseGetPosition();

/** \brief Pour savoir si le clic gauche de la souris est appuy�.
 *
 * \return bool
 *
 */
bool MouseGetClickLeft();

/** \brief Permet de r�cup�rer un clic gauche de la souris.
 *
 * \return bool
 *
 */
bool MouseGetClickLeftOneShot();

/** \brief Pour savoir si le clic droit de la souris est appuy�.
 *
 * \return bool
 *
 */
bool MouseGetClickRight();

/** \brief Permet de r�cup�rer un clic droit de la souris.
 *
 * \return bool
 *
 */
bool MouseGetClickRightOneShot();

/** \brief Renvoie le nombre de joystick connect�.
 *
 * \return int
 *
 */
int StickGetNbConnect();

/** \brief Pour obtenir le nom d'un joystick
 *
 * \param numStick int Le Num�ro du joystick (compris entre 0 et GetNbStickConnect() )
 * \return const char*
 *
 */
const char * StickGetName(int numStick);

/** \brief Pour savoir si une touche d'une manette est appuy�e.
 *
 * \param numStick int Le Num�ro du joystick (compris entre 0 et GetNbStickConnect() ).
 * \param numButton int Le num�ro du bouton.
 * \return bool
 *
 */
bool StickGetClick(int numStick, int numButton);

/** \brief Pour un appui sur une touche de la manette.
 *
 * \param numStick int Le Num�ro du joystick (compris entre 0 et GetNbStickConnect() ).
 * \param numButton int Le num�ro du bouton.
 * \return bool
 *
 */
bool StickGetClickOneShot(int numStick, int numButton);

/** \brief Renvoie l'�tat du chapeau d'une manette
 *
 * \param numStick int Le Num�ro du joystick (compris entre 0 et GetNbStickConnect() ).
 * \param numHat int Le num�ro du chapeau.
 * \return int L'�tat du chapeau, c'est � dire une de ces valeurs :
 * SDL_HAT_CENTERED,
 * SDL_HAT_UP,
 * SDL_HAT_RIGHT,
 * SDL_HAT_DOWN,
 * SDL_HAT_LEFT,
 * SDL_HAT_RIGHTUP,
 * SDL_HAT_RIGHTDOWN,
 * SDL_HAT_LEFTUP,
 * SDL_HAT_LEFTDOWN.
 *
 */
int StickGetStateHat(int numStick, int numHat);

/** \brief Permet de recup�rer l'�tat d'un axe
 *
 * \param numStick int
 * \param numAxis int
 * \return float
 *
 */
float StickGetAxis(int numStick, int numAxis);

/** \brief Permet d'obtenir une valeur al�atoire.
 *
 * \param min int
 * \param max int
 * \return int
 *
 */
int Rand(int min, int max);

/** \brief Permet d'obtenir une valeur al�atoire entre 0 et 1
 *
 * \return float
 *
 */
float fRand();

/** \brief permet de conna�tre le nombre de millisecondes �couler depuis le debut du programme
 *
 * \return unsigned int renvoie un nombre de millisecondes
 *
 */
unsigned int Time();


#endif
