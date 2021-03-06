#ifndef MAINMENU_H
#define MAINMENU_H

#ifdef _TINSPIRE
#include <os.h>
#endif
#include "SDL/SDL.h"
#include "Font.h"

enum MenuChoice
{
   Play,
   Help,
   Quit
};

enum SelectionLocation
{
   Categories,
   Levels,
   Other
};

enum MainMenuDecision
{
   DecisionMade,
   NoDecisionMade
};

struct MainMenu
{
   enum MenuChoice m_eChoice;
   //enum SelectionLocation m_eSelection;
   //int m_nLevelNum;
   //struct MenuItem m_Levels[7];
   //struct MenuItem m_ChoiceLevels[8];
   //struct MenuItem m_Options;
   //struct MenuItem m_Help;
   //int m_nCurrentCategory;
   //int m_nCurrentLevel;
   //struct Background* m_pBackground;
   Font *m_pFont;
   //struct StarDrawer* m_pStarDrawer;
   //struct Config* m_pConfig;//Does not own
   struct SDL_Surface* m_pScreen;//Does not own
   struct SDL_Surface* m_pTitle;
};

void CreateMainMenu(struct MainMenu** ppMenu/*, int nLevelNum, struct Config* pConfig*/, struct SDL_Surface* pScreen);
void FreeMainMenu(struct MainMenu** ppMenu);
enum MainMenuDecision MainMenuLoop(struct MainMenu* pMenu);
int MainMenuShouldQuit(struct MainMenu* pMenu);
int MainMenuShowHelp(struct MainMenu* pMenu);

#endif
