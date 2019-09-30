#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
using std::string;
using std::vector;

#include "InfoSurface.h"
#include "ButtonMenu.h"

/*
+-----+----------+-----+
|     |          |     |
| LP  | TextArea | RP  | 
|     |          |     |
|-----+----------+-----|
| ??  | Options  |  X  | 
+-----+----------+-----+
*/


#ifndef CHARACTERDIALOG_H
#define CHARACTERDIALOG_H


//Character dialog class
class CharacterDialog
{
private:
	SDL_Texture *dialog;
	SDL_Texture *left_portrait, *right_portrait;
	InfoSurface *text_area;
	ButtonMenu  *buttons;
	SDL_Rect    pos;
	int start,end;
	//OptionsMenu *options;
	
public:
	//Technically I only need to pass portraits and the actual text.
	CharacterDialog(SDL_Texture *left_portrait, SDL_Texture *right_portrait,SDL_Rect pos,TTF_Font *font);
	CharacterDialog(SDL_Texture *left_portrait, SDL_Texture *right_portrait,SDL_Rect pos,InfoSurface *text_area);
	void Draw(SDL_Texture *screen);
	void HandleEvents(SDL_Event *event);
	void ScrollUp();
	void ScrollDown();
};


#endif
