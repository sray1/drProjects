#ifndef _DEF_DRAW_H
#define _DEF_DRAW_H 
//////////////////////////////////////////// Objects
#define LASTNUMBER_USED		2010		// alreadyAssigned
#define LABEL				2001        // that can use EDIT & MOVE
#define FREEHAND			2002
#define RECT_FILL			2003
#define RECT_HOLLOW			2004
#define RRECT_FILL			2005
#define RRECT_HOLLOW		2006
#define CIRCLE_FILL			2007
#define CIRCLE_HOLLOW		2008
#define LINE				2009 
#define AXIS				2010
//////////////////////////////// 
#define GRID				2101		// button
///////////////////////////////// used in Label and NodeDlg/InLabDlg
#define LABEL_NODE			-1
#define LABEL_SCREEN		0
//////////////////////////////////
enum CONTEXTOBJ
	{
		CO_NODE,
        CO_CURVE,	
        CO_PATCH,	
        CO_SOLID,	
        CO_RIGID,	
        CO_LIN_SPR,	
        CO_LIN_SNU,	
        CO_FORCE,	
        CO_DISPLACE,	
        CO_PRESSURE,
        CO_THERMAL,	
        CO_LUMPWT
	};
/////////////////////////////////
#endif
