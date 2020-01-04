#include <WIN_TRIM.h>
#include <3dextrn.h>
#include <3dcontxt.h>
#include <backref.h>
#include <3dcolor.h>
#include <txudll.h>

// from antia
#define	MAXPIXQ		10L	/* pixel queue size */
typedef struct {
	int			x,y;
	RGBColor	rgb;
}
	pixQitem,*pPixQitem;

typedef struct {
	int			oldest;
	pixQitem	pixQ[MAXPIXQ];

}	pixelQ,*pPixelQ;

// from CLUTS
typedef struct tACRPALENTRY {
	struct tACRPALENTRY _far *prior;
	COLORREF		c;
	long			n;
}	ACRPALENTRY, _far *pACRPALENTRY;


// from render
typedef Handle hPGN;
typedef struct polyList {
	hPGN					ph;
	struct polyList	_huge	*prior;

}	polyList, _huge *pPolyList;

// local
typedef struct TCONTEXT3D {
	struct TCONTEXT3D _far	*prior;
	HANDLE				hOwner;
	HDC 				hdcCurrent;
	Point3d				penLoc;
	Fixed				hither,
						yon,
						zoom;
	Matrix				xFormInstance,
						xFormViewer,
						xFormCombined;
	Fixed				centerX,
						centerY;
	Boolean				parallel;
	int					subdivisions;
	pPixelQ				pixQ,
						defPixQ;
	short				interruptsEnabled;
	WORD				wMFmin,
						wMFmax;
	short				nPolys;
	pPolyList			pPL;
	Boolean				shadows,
						antiAliasing;
	pBackRef			pbr;
	BOOL				genBackRefs;
	BOOL				accretingPalettes;
	long				nAPE;
	pACRPALENTRY		pAPE;
	Boolean				bContour;
	HPALETTE			cthContour;
	WORD				colorsContour;
	Fixed				intContour,
						hvyContour,
						rngContour,
						baseContour;
	pUserDll			pUDll;
}
	CONTEXT3D, _far *PCONTEXT3D;

extern	short				interruptsEnabled;	// osintf
extern	WORD				wMFmin,				// osintf
							wMFmax;				// osintf

extern	int					subdivisions;		// 3dmt2pch
extern	pBackRef			pbr;				// backref
extern	BOOL				genBackRefs,		// backref
							accretingPalettes;	// cluts
extern	long				nAPE;				// cluts
extern	pACRPALENTRY		pAPE;				// cluts
extern	Boolean				bContour;			// contours
extern	HPALETTE			cthContour;			// contours
extern	WORD				colorsContour;		// contours
extern	Fixed				intContour,			// contours
							hvyContour,			// contours
							rngContour,			// contours
							baseContour;		// contours
extern	pPixelQ				pixQ,				// antai
							defPixQ;			// antia
extern	short				nPolys;				// render
extern	pPolyList			pPL;				// render
extern	Boolean				shadows,			// render
							antiAliasing;		// render

extern	pUserDll			pUDll;				// txudll

static PCONTEXT3D pContext3d	= NULL;			// context stack top
static PCONTEXT3D pCurrent3d	= NULL;			// active context

static short	WindowsVersion	(void);
static void		Init3dContext	(void);
static void		Save3dContext	(PCONTEXT3D pc);
static void		Restore3dContext(PCONTEXT3D pc);

short WindowsVersion(void)
{
	DWORD dwVersion = GetVersion();	// 3.1 = 0x030A

	return	LOWORD(dwVersion);
}

void Purge3dContexts(void)
{
	while( pContext3d!=NULL ) {
		PCONTEXT3D pc = pContext3d;
		pContext3d = pc->prior;
		DisposPtr( (Ptr)pc );
	}
	pCurrent3d = NULL;
}

int API3D Purge3dContext(void)
{
	PCONTEXT3D		pc, pcAbove;
	HANDLE			hOwner = (HANDLE)GetCurrentTask();

	pc = pContext3d;
	while( pc!=NULL ) {
		if( pc->hOwner == hOwner )
			break;
		pcAbove = pc;
		pc = pc->prior;
	}
	if( pc==NULL )
		return 0;
	if( pc == pContext3d )
		pContext3d = pc->prior;
	else // relink entry above this to this prior
		pcAbove->prior = pc->prior;
	if( pc == pCurrent3d )
		pCurrent3d = NULL;
	DisposPtr( (Ptr)pc );
	return 1;
}

HANDLE 	Get3dContext(void)
{
	PCONTEXT3D		pc = pContext3d;
	HANDLE			hOwner = (HANDLE)GetCurrentTask();

	if( pCurrent3d!=NULL )
		if( pCurrent3d->hOwner == hOwner )
			return hOwner; // same caller
	while( pc!=NULL ) {
		if( pc->hOwner == hOwner )
			break;
		pc = pc->prior;
	}
	if( pCurrent3d!=NULL )
		Save3dContext( pCurrent3d );

	if( pc==NULL ) {
		pc = (PCONTEXT3D)NewPtr( sizeof(CONTEXT3D) );
		if( pc==NULL )
			return NULL;
		pc->prior	= pContext3d;
		pc->hOwner	= hOwner;
		pContext3d	= pc;
		Init3dContext();
		Save3dContext( pc );
	}
	else
		Restore3dContext( pc );
	pCurrent3d = pc;
	return hOwner;
}

void	Init3dContext(void)
{
	hdcCurrent		= NULL;
	penLoc.x		= penLoc.y = penLoc.z = 0;
	hither			= f_hither;
	yon				= f_yon;
	zoom			= f_1;
	xFormInstance	= Identity;
	xFormViewer		= Identity;
	xFormCombined	= Identity;
	centerX			= f_0;
	centerY			= f_0;
	parallel		= false;
	subdivisions	= 1;
	pixQ			= NULL;
	defPixQ			= NULL;
	interruptsEnabled= STDINTERRRUPT;
	wMFmin			= WM_LBUTTONDOWN;
	wMFmax			= WM_MOUSELAST;
	nPolys			= 0;
	pPL				= NULL;
	shadows			= false;
	antiAliasing	= false;
	pbr				= NULL;
	genBackRefs		= FALSE;
	accretingPalettes	= FALSE;
	nAPE			= 0;
	pAPE			= NULL;
	bContour		= FALSE;
	cthContour		= NULL;
	colorsContour	= 0;
	intContour		= f_0;
	hvyContour		= f_0;
	rngContour		= f_0;
	baseContour		= f_0;
	pUDll			= NULL;
}

void	Save3dContext(PCONTEXT3D pc)
{
	pc->hdcCurrent		= hdcCurrent;
	pc->penLoc			= penLoc;
	pc->hither			= hither;
	pc->yon				= yon;
	pc->zoom			= zoom;
	pc->xFormInstance	= xFormInstance;
	pc->xFormViewer		= xFormViewer;
	pc->xFormCombined	= xFormCombined;
	pc->centerX			= centerX;
	pc->centerY			= centerY;
	pc->parallel		= parallel;
	pc->subdivisions	= subdivisions;
	pc->pixQ			= pixQ;
	pc->defPixQ			= defPixQ;
	pc->interruptsEnabled= interruptsEnabled;
	pc->wMFmin			= wMFmin;
	pc->wMFmax			= wMFmax;
	pc->nPolys			= nPolys;
	pc->pPL				= pPL;
	pc->shadows			= shadows;
	pc->antiAliasing	= antiAliasing;
	pc->pbr				= pbr;
	pc->genBackRefs		= genBackRefs;
	pc->accretingPalettes	= accretingPalettes;
	pc->nAPE			= nAPE;
	pc->pAPE			= pAPE;
	pc->bContour		= bContour;
	pc->cthContour		= cthContour;
	pc->colorsContour	= colorsContour;
	pc->intContour		= intContour;
	pc->hvyContour		= hvyContour;
	pc->rngContour		= rngContour;
	pc->baseContour		= baseContour;
	pc->pUDll			= pUDll;
}

void	Restore3dContext(PCONTEXT3D pc)
{
	hdcCurrent		= pc->hdcCurrent;
	penLoc			= pc->penLoc;
	hither			= pc->hither;
	yon				= pc->yon;
	zoom			= pc->zoom;
	xFormInstance	= pc->xFormInstance;
	xFormViewer		= pc->xFormViewer;
	xFormCombined	= pc->xFormCombined;
	centerX			= pc->centerX;
	centerY			= pc->centerY;
	parallel		= pc->parallel;
	subdivisions	= pc->subdivisions;
	pixQ			= pc->pixQ;
	defPixQ			= pc->defPixQ;
	interruptsEnabled= pc->interruptsEnabled;
	wMFmin			= pc->wMFmin;
	wMFmax			= pc->wMFmax;
	nPolys			= pc->nPolys;
	pPL				= pc->pPL;
	shadows			= pc->shadows;
	antiAliasing	= pc->antiAliasing;
	pbr				= pc->pbr;
	genBackRefs		= pc->genBackRefs;
	accretingPalettes	= pc->accretingPalettes;
	nAPE			= pc->nAPE;
	pAPE			= pc->pAPE;
	bContour		= pc->bContour;
	cthContour		= pc->cthContour;
	colorsContour	= pc->colorsContour;
	intContour		= pc->intContour;
	hvyContour		= pc->hvyContour;
	rngContour		= pc->rngContour;
	baseContour		= pc->baseContour;
	pUDll			= pc->pUDll;
}

