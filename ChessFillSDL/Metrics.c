#ifdef _TINSPIRE
#include <os.h>
#include <libndls.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#include "Metrics.h"

void CreateMetrics(struct Metrics** ppMetrics)
{
   *ppMetrics = malloc(sizeof(struct Metrics));
   struct Metrics* pMetrics = *ppMetrics;
   pMetrics->m_UsedPieceIndicatorX = 40;
   pMetrics->m_UsedPieceIndicatorY = 120;
}

void FreeMetrics(struct Metrics** ppMetrics)
{
   struct Metrics* pMetrics = *ppMetrics;

   free(pMetrics);
   *ppMetrics = NULL;
}

int GetUsedPieceIndicatorX( struct Metrics* pMetrics )
{
   return pMetrics->m_UsedPieceIndicatorX;
}

int GetUsedPieceIndicatorY( struct Metrics* pMetrics )
{
   return pMetrics->m_UsedPieceIndicatorY;
}

int GetPieceLeft( struct Metrics* pMetrics, int x, int y )
{
   return x * 20 + 40;
}

int GetPieceTop( struct Metrics* pMetrics, int x, int y )
{
   return y * 20 + 25;
}

int GetPieceWidth( struct Metrics* pMetrics, int x, int y )
{
   return 20;
}

int GetPieceHeight( struct Metrics* pMetrics, int x, int y )
{
   return 20;
}

int GetRemainLabelX( struct Metrics* pMetrics )
{
   return 40;
}


