#ifndef METRICS_H
#define METRICS_H

#ifndef NULL
#define NULL (0)
#endif

struct Metrics
{
   int m_UsedPieceIndicatorX;
   int m_UsedPieceIndicatorY;
};

void CreateMetrics(struct Metrics** ppMetrics);
void FreeMetrics(struct Metrics** ppMetrics);
int GetUsedPieceIndicatorX( struct Metrics* pMetrics );
int GetUsedPieceIndicatorY( struct Metrics* pMetrics );
int GetPieceLeft( struct Metrics* pMetrics, int x, int y );
int GetPieceTop( struct Metrics* pMetrics, int x, int y );
int GetPieceWidth( struct Metrics* pMetrics, int x, int y );
int GetPieceHeight( struct Metrics* pMetrics, int x, int y );

int GetRemainLabelX( struct Metrics* pMetrics );

#endif
