#ifdef _TINSPIRE
#include <os.h>
#include <libndls.h>
#else
#endif
#include "MainMenu.h"
#include "Replacements.h"
//#include "MenuGraphic.h"

void CreateMainMenu(struct MainMenu** ppMenu/*, int nLevelNum, struct Config* pConfig*/, struct SDL_Surface* pScreen)
{
   *ppMenu = malloc(sizeof(struct MainMenu));
   struct MainMenu* pMenu = (*ppMenu);

   //pMenu->m_pConfig = pConfig;
   pMenu->m_pScreen = pScreen;

   pMenu->m_eChoice = Play;

   //CreateMenuItem(&pMenu->m_Options, 0, "Options", "", Configuration);
   //CreateMenuItem(&pMenu->m_Help, 1, "Help", "", Configuration);

   //UpdateSelectedItems(pMenu);

   //CreateBackground(&(pMenu->m_pBackground), pMenu->m_pScreen, pMenu->m_pConfig, 0);
   pMenu->m_pFont = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 255/*R*/, 0/*G*/, 0/*B*/, 12);

   //CreateStarDrawer( &pMenu->m_pStarDrawer );

#ifdef _TINSPIRE
   pMenu->m_pTitle = nSDL_LoadImage(image_Title);
#endif
}

void FreeMainMenu(struct MainMenu** ppMenu)
{
   struct MainMenu* pMenu = *ppMenu;

   //FreeMenuItem(&pMenu->m_Options);
   //FreeMenuItem(&pMenu->m_Help);
   
   //FreeBackground(&pMenu->m_pBackground);
   FreeFont(pMenu->m_pFont);

   //FreeStarDrawer( &pMenu->m_pStarDrawer );

   //pMenu->m_pConfig = NULL;//Does not own
   pMenu->m_pScreen = NULL;//Does not own

#ifdef _TINSPIRE
   SDL_FreeSurface(pMenu->m_pTitle);
   pMenu->m_pTitle = NULL;
#endif

   free(*ppMenu);
   *ppMenu = NULL;
}

enum MainMenuDecision PollEvents(struct MainMenu* pMenu)
{
   rand();//I don't think we can use the clock to seed the random

   SDL_Event event;
   while( SDL_PollEvent( &event ) )
   {
      switch( event.type )
      {
         case SDL_KEYDOWN:
            printf( "Key press detected\n" );
            switch( event.key.keysym.sym )
            {
               case SDLK_ESCAPE:
                  printf("Hit Escape!n");
                  pMenu->m_eChoice = Quit;
                  return DecisionMade;
                  break;

               /*case SDLK_LEFT:
	       case SDLK_4:
                  if( pMenu->m_eSelection == Levels ) {
                     if( pMenu->m_nCurrentLevel > 0 ) {
                        pMenu->m_nCurrentLevel--;
                        pMenu->m_nLevelNum--;
			UpdateSelectedItems(pMenu);
		     } 
		  }
		  else if( pMenu->m_eSelection == Categories ) {
                     if( pMenu->m_nCurrentCategory > 0 ) {
                        pMenu->m_nCurrentCategory--;
                        pMenu->m_nCurrentLevel = 0;
                        UpdateSelectedItems(pMenu);
                     }
                  }
                  else if( pMenu->m_eSelection == Other && pMenu->m_eChoice == Help ) {
                      pMenu->m_eChoice = Options;
                      UpdateSelectedItems(pMenu);
                  }
                  break;

               case SDLK_RIGHT:
               case SDLK_6:
		  if( pMenu->m_eSelection == Levels ) {
                     if( pMenu->m_nCurrentLevel < 7 ) {
                        pMenu->m_nCurrentLevel++;
                        pMenu->m_nLevelNum++;
			UpdateSelectedItems(pMenu);
                     }
		  }
		  else if( pMenu->m_eSelection == Categories ) {
                     if( pMenu->m_nCurrentCategory < 6 ) {
                        pMenu->m_nCurrentCategory++;
			pMenu->m_nCurrentLevel = 0;
			UpdateSelectedItems(pMenu);
		     }
		  }
		  else if( pMenu->m_eSelection == Other && pMenu->m_eChoice == Options ) {
                      pMenu->m_eChoice = Help;
                      UpdateSelectedItems(pMenu);
                  }
                  break;

	       case SDLK_UP:
               case SDLK_8:
		  if( pMenu->m_eSelection == Levels ) {
                     if( pMenu->m_nCurrentLevel < 4 ) {
                        pMenu->m_eSelection = Categories;
                        UpdateSelectedItems(pMenu);
		     }
		     else {
                        pMenu->m_nCurrentLevel -= 4;
			pMenu->m_nLevelNum -= 4;
			UpdateSelectedItems(pMenu);
		     }
		  }
                  else if( pMenu->m_eSelection == Categories ) {
		  }
		  else if( pMenu->m_eSelection == Other )
                  {
                      pMenu->m_eSelection = Levels;
		      pMenu->m_eChoice = Play;
                      UpdateSelectedItems(pMenu);
                  }
		  break;

	       case SDLK_DOWN:
               case SDLK_2:
		  if( pMenu->m_eSelection == Levels ) {
                     if( pMenu->m_nCurrentLevel < 4 ) {
                        pMenu->m_nCurrentLevel += 4;
			pMenu->m_nLevelNum += 4;
			UpdateSelectedItems(pMenu);
		     }
		     else {
                        pMenu->m_eSelection = Other;
                        pMenu->m_eChoice = Options;
                        UpdateSelectedItems(pMenu);
		     }
                  }
		  else if( pMenu->m_eSelection == Categories ) {
                     pMenu->m_eSelection = Levels;
		     pMenu->m_nLevelNum = pMenu->m_nCurrentCategory * 8 + 1;
		     pMenu->m_nCurrentLevel = 0;
                     FreeLevelMenuItems(pMenu);
                     CreateLevelMenuItems(pMenu);
		     UpdateSelectedItems(pMenu);
                  }
		  break;*/

               case SDLK_SPACE:
               case SDLK_RETURN:
               case SDLK_LCTRL:
                  return DecisionMade;
                  break;

               default:
                  break;
            }
      }
   }

   return NoDecisionMade;
}

void UpdateDisplay(struct MainMenu* pMenu)
{
   DrawText( pMenu->m_pScreen, pMenu->m_pFont, 10, 10, "nChessFill", 255, 0, 255 );

   DrawText( pMenu->m_pScreen, pMenu->m_pFont, 90, 200, "Play", 255, 0, 255 );

#if 0
   SDL_Rect DestRect;
   DestRect.x = 0;
   DestRect.y = 0;
   DestRect.w = SCREEN_WIDTH;
   DestRect.h = SCREEN_HEIGHT;
   SDL_FillRect(pMenu->m_pScreen, &DestRect, SDL_MapRGB(pMenu->m_pScreen->format, 255, 255, 255));
#endif

#ifdef _TINSPIRE
   SDL_Rect rectSrc, rectDst;

   rectSrc.w = 320;
   rectSrc.h = 240;
   rectSrc.x = 0;
   rectSrc.y = 0;

   rectDst.w = 320;
   rectDst.h = 240;
   rectDst.x = 0;
   rectDst.y = 0;

   SDL_BlitSurface(pMenu->m_pTitle, &rectSrc, pMenu->m_pScreen, &rectDst);
#endif

   SDL_UpdateRect(pMenu->m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

enum MainMenuDecision MainMenuLoop(struct MainMenu* pMenu)
{
   if( PollEvents(pMenu) == DecisionMade )
      return DecisionMade;

   UpdateDisplay(pMenu);

   return NoDecisionMade;
}

int MainMenuShouldQuit(struct MainMenu* pMenu)
{
   return pMenu->m_eChoice == Quit;
}

//int MainMenuShowOptions(struct MainMenu* pMenu)
//{
//   return pMenu->m_eChoice == Options;
//}
//
//int MainMenuShowHelp(struct MainMenu* pMenu)
//{
//   return pMenu->m_eChoice == Help;
//}

