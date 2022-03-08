#ifndef METRICS_H
#define METRICS_H

#ifndef NULL
#define NULL (0)
#endif

struct Metrics
{
   int m_UsedPieceIndicatorY;
};

void CreateMetrics(struct Metrics** ppMetrics);
void FreeMetrics(struct Metrics** ppMetrics);
int GetUsedPieceIndicatorY( struct Metrics* pMetrics );

#endif
