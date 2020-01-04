#ifndef _OFFSCREENBUFFER_
#define	_OFFSCREENBUFFER_

#include <3d.h>

#define	OS_PENARG(style,width,color)	(DWORD)((style)<<28)|(DWORD)(((width)&&0x0F)<<24)|(DWORD)((color)&0x00FFFFFF)

enum OS_ACTION { OS_INIT, OS_USE, OS_ERASE, OS_PEN, OS_DRAW, OS_DISPOSE, OS_INIT24 };

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

HPALETTE API3D OffscreenBuffer(enum OS_ACTION action,DWORD arg);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _OFFSCREENBUFFER_

