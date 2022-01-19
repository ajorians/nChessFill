#ifdef _TINSPIRE
#include <os.h>
#include <libndls.h>
#endif
#include "Game.h"
#include "Replacements.h"
//#include "YouWinGraphic.h"

void CreateGame(struct Game** ppGame/*, struct Config* pConfig*/, struct SDL_Surface* pScreen)
{
   *ppGame = malloc(sizeof(struct Game));
   struct Game* pGame = *ppGame;
   ChessFillLibCreate(&(pGame->m_Chess));
   //pGame->m_pConfig = pConfig;
   //pGame->m_bWon = IsCrossGameOver(pGame->m_Cross);

#ifdef _TINSPIRE
   pGame->m_pYouWinGraphic = nSDL_LoadImage(image_YouWin);
   SDL_SetColorKey(pGame->m_pYouWinGraphic, SDL_SRCCOLORKEY, SDL_MapRGB(pGame->m_pYouWinGraphic->format, 255, 255, 255));
#endif

   pGame->m_pScreen = pScreen;
   //CreateBackground(&(pGame->m_pBackground), pGame->m_pScreen, pGame->m_pConfig, 1);
   //pGame->m_pMetrics = NULL;
   //CreateMetrics(&pGame->m_pMetrics, pGame->m_Cross);

   //pGame->m_pSelector = NULL;
   //CreateSelector(&pGame->m_pSelector, pGame->m_pScreen, pGame->m_pConfig, pGame->m_pMetrics, pGame->m_Cross);

   pGame->m_bShouldQuit = 0;

   pGame->m_pFont = LoadFont("ARIAL.TTF", NSDL_FONT_THIN, 255/*R*/, 0/*G*/, 0/*B*/, 12);
   pGame->m_nX = 0;
   pGame->m_nY = 0;
}

void FreeGame(struct Game** ppGame)
{
   struct Game* pGame = *ppGame;

#ifdef _TINSPIRE
   SDL_FreeSurface(pGame->m_pYouWinGraphic);
#endif
   //FreeSelector(&pGame->m_pSelector);
   //FreeBackground(&pGame->m_pBackground);
   //FreeMetrics(&pGame->m_pMetrics);

   //pGame->m_pConfig = NULL;//Does not own
   pGame->m_pScreen = NULL;//Does not own

   FreeFont(pGame->m_pFont);

   free(pGame);
   *ppGame = NULL;
}

void DrawBoard(struct Game* pGame)
{
   SDL_Rect rectDst;
   rectDst.w = SCREEN_WIDTH;
   rectDst.h = SCREEN_HEIGHT;
   rectDst.x = 0;
   rectDst.y = 0;

   SDL_FillRect(pGame->m_pScreen, &rectDst, SDL_MapRGB(pGame->m_pScreen->format, 255, 255, 255));

   //DrawBackground(pGame->m_pBackground);
#if 1
   for ( int x = 0; x < 4; x++ )
   {
      for ( int y = 0; y < 4; y++ )
      {
         enum PieceType piece = GetPieceAt( pGame->m_Chess, x, y );
         //if ( piece == Empty )
         //   continue;

         char buffer[2];
         switch ( piece )
         {
            case Empty:
               strcpy( buffer, "X" );
               break;
            case Pawn:
               strcpy( buffer, "P" );
               break;
            case Rook:
               strcpy( buffer, "R" );
               break;
            case Knight:
               strcpy( buffer, "k" );
               break;
            case Bishop:
               strcpy( buffer, "B" );
               break;
            case Queen:
               strcpy( buffer, "Q" );
               break;
            case King:
               strcpy( buffer, "K" );
               break;
         }
         

         DrawText( pGame->m_pScreen, pGame->m_pFont, x * 20, y * 20, buffer, 0, 0, 255 );
      }
   }

   DrawText( pGame->m_pScreen, pGame->m_pFont, pGame->m_nX * 20, pGame->m_nY * 20, "Z", 255, 0, 255 );

   //Draw selector
   //DrawSelector(pGame->m_pSelector);
   
   /*if( pGame->m_bWon == 1 ) {
      SDL_Rect rectYouWin;
      rectYouWin.x = (SCREEN_WIDTH - pGame->m_pYouWinGraphic->w)/2;
      rectYouWin.y = (SCREEN_HEIGHT - pGame->m_pYouWinGraphic->h)/2;
      rectYouWin.w = pGame->m_pYouWinGraphic->w;
      rectYouWin.h = pGame->m_pYouWinGraphic->h;
      SDL_BlitSurface(pGame->m_pYouWinGraphic, NULL, pGame->m_pScreen, &rectYouWin);
   }*/
#endif
   
   SDL_UpdateRect(pGame->m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

int GamePollEvents(struct Game* pGame)
{
   SDL_Event event;
   while( SDL_PollEvent( &event ) ) {
      switch( event.type ) {
         case SDL_KEYDOWN:
            switch( event.key.keysym.sym) {
              case SDLK_ESCAPE:
                  return 0;
                  break;

               case SDLK_UP:
               case SDLK_8:
		  if( pGame->m_bWon != 1 ) {
           if ( pGame->m_nY > 0 )
           {
              pGame->m_nY--;
           }
                     //Move(pGame->m_pSelector, Up);
		  }
                  break;

	       case SDLK_DOWN:
               case SDLK_2:
		  if( pGame->m_bWon != 1 ) {
           if ( pGame->m_nY < 3 )
           {
              pGame->m_nY++;
           }
                     //Move(pGame->m_pSelector, Down);
		  }
                  break;

               case SDLK_LEFT:
               case SDLK_4:
		  if( pGame->m_bWon != 1 ) {
           if ( pGame->m_nX > 0 )
           {
              pGame->m_nX--;
           }
                     //Move(pGame->m_pSelector, Left);
		  }
                  break;

               case SDLK_RIGHT:
               case SDLK_6:
		  if( pGame->m_bWon != 1 ) {
           if ( pGame->m_nX < 3 )
           {
              pGame->m_nX++;
           }
                     //Move(pGame->m_pSelector, Right);
		  }
                  break;

               case SDLK_RETURN:
               case SDLK_LCTRL:
               case SDLK_RCTRL:
		  if( pGame->m_bWon != 1 ) {
           PlaceNextPieceAt( pGame->m_Chess, pGame->m_nX, pGame->m_nY );
                     //ToggleCrossCellValue(pGame->m_Cross, GetCurrentX(pGame->m_pSelector), GetCurrentY(pGame->m_pSelector));

		     //pGame->m_bWon = IsCrossGameOver(pGame->m_Cross);
		  }
                  break;

               default:
                  break;
            }
          default:
             break;
      }
   }
   return 1;
}

int GameLoop(struct Game* pGame)
{
   if( GamePollEvents(pGame) == 0 )
      return 0;

   DrawBoard(pGame);

   SDL_Delay(30);

   return 1;
}

int GameShouldQuit(struct Game* pGame)
{
   return pGame->m_bShouldQuit;
}

