#ifdef _TINSPIRE
#include <os.h>
#include <libndls.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <SDL/SDL.h>
#ifndef _TINSPIRE
#include <SDL/SDL_ttf.h>
#endif
#include "Game.h"
#include "Help.h"
#include "MainMenu.h"
#include "Replacements.h"

#define SCREEN_BIT_DEPTH        (16)
#ifdef _TINSPIRE
#define SCREEN_VIDEO_MODE (SDL_SWSURFACE|SDL_FULLSCREEN|SDL_HWPALETTE)
#else
#define SCREEN_VIDEO_MODE (SDL_SWSURFACE|SDL_HWPALETTE)
#endif

#ifdef _WIN32
#include <Windows.h>
int APIENTRY WinMain( HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPSTR lpCmdLine, int nCmdShow )
{
   return main( __argc, __argv );
}
#endif

int main( int argc, char* argv[] )
{
   printf("Initializing SDL.\n");

   /* Initialize the SDL library (starts the event loop) */
   if ( SDL_Init(SDL_INIT_VIDEO ) < 0 )
   {
      fprintf(stderr,
              "Couldn't initialize SDL: %s\n", SDL_GetError());
      exit(1);
   }

   printf("SDL initialized.\n");

   SDL_Surface* pScreen = NULL;
   pScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BIT_DEPTH, SCREEN_VIDEO_MODE);

   if( pScreen == NULL )
   {
      fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BIT_DEPTH, SDL_GetError());
      exit(1);
   }
   else
   {
      /* Hides the cursor */
      SDL_ShowCursor(SDL_DISABLE);
   }

#ifndef _TINSPIRE
   //Initialize SDL_ttf
   if (TTF_Init() == -1)
   {
      exit(1);
   }
#endif

   while(1) {
      int bShowHelp = 0;

      struct MainMenu* pMenu = NULL;
      int bShouldQuit = 0;
      CreateMainMenu(&pMenu, pScreen);
      while(MainMenuLoop(pMenu) != DecisionMade){}
      bShouldQuit = MainMenuShouldQuit(pMenu);
      bShowHelp = MainMenuShowHelp(pMenu);
      FreeMainMenu(&pMenu);

      if( bShouldQuit )
         break;

      if( bShowHelp ) {
         struct Help* pHelp = NULL;
         CreateHelp(&pHelp, pScreen);
         while(HelpLoop(pHelp)){}
         FreeHelp(&pHelp);
         continue;
      }
      else {
         struct Game* pGame = NULL;
         int bShouldQuit = 0;
         CreateGame(&pGame, pScreen);
         while(GameLoop(pGame)){}
         bShouldQuit = GameShouldQuit(pGame);
         FreeGame(&pGame);

         if( bShouldQuit )
            break;
      }
   }

#ifdef _TINSPIRE
   FreeConfig(&pConfig);
#endif

   printf("Quitting SDL.\n");

#ifndef _TINSPIRE
   //Quit SDL_ttf
   TTF_Quit();
#endif

   /* Shutdown all subsystems */
   SDL_Quit();

   printf("Quitting...\n");

   return 0;
}
