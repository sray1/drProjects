/*****************************************************************************
 *	File:		AntiAlias.h
 *
 *	(C) 1991 Mark M. Owen. All rights reserved.
 *****************************************************************************
 */
#ifndef	_AntiAlias_
#define	_AntiAlias_

#include <OSINTF.h>

/*
 *	Convolution weight factors corresponding to
 *	a 3x3 matrix derived from a cubic spline
 *	surface, as follows:
 *
 *			W3 W2 W3
 *			W2 W1 W2
 *			W3 W2 W3
 */
#define	W1		0.444444444444444F		/*	16/36	*/
#define	W2		0.111111111111111F		/*	 4/36	*/
#define	W3		0.027777777777778F		/*	 1/36	*/

#define	MAXPIXQ		10L	/* pixel queue size */

typedef struct {
	int			x,y;
	RGBColor	rgb;
}
	pixQitem, __far *pPixQitem;

typedef struct {
	int			oldest;
	pixQitem	pixQ[MAXPIXQ];

}	pixelQ, __far *pPixelQ;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


void	API3D	GetCPixel		(int x,int y,pRGBColor rgb);
void	API3D	SetCPixel		(int x,int y,pRGBColor rgb);

void	API3D	SetPixQ			(pPixelQ thePixQ);
void	API3D	SetDefPixQ		(void);
pPixelQ	API3D	NewPixQ			(void);
void	API3D	DisposePixQ		(pPixelQ thePixQ);
void	API3D	DisposeDefPixQ	(void);
Boolean	API3D	InPixQ			(int x,int y,pRGBColor rgb);
void	API3D	QueuePixel		(int x,int y,pRGBColor rgb);
void	API3D	GetQueuePixel	(int x,int y,pRGBColor rgb);
void	API3D	SetQueuePixel	(int x,int y,pRGBColor rgb);

void	API3D	ConvoluteColorPixel(int x,int y,float w1,float w2,float w3,pRGBColor rgb);
void	API3D	ConvolutionColor(int X,int Y,float w1,float w2,float w3,pRGBColor rgb);
void	API3D 	ConvoluteColor	(pRect r);

unsigned short API3D Convolution(int X,int Y);
void	API3D 	Convolute		(pRect r);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif	_AntiAlias_
