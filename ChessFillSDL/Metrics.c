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
   pMetrics->m_UsedPieceIndicatorY = 120;
}

void FreeMetrics(struct Metrics** ppMetrics)
{
   struct Metrics* pMetrics = *ppMetrics;

   free(pMetrics);
   *ppMetrics = NULL;
}

int GetUsedPieceIndicatorY( struct Metrics* pMetrics )
{
   return pMetrics->m_UsedPieceIndicatorY;
}

