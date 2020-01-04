#ifndef	_TXUDLL_
#define	_TXUDLL_

#include <apitx.h>

typedef struct UserDll {
	STR4		name;
	HINSTANCE	hLib;
	TXINIT		pTxInit;
	TXSETARG	pTxSetArg;
	TXGETARG	pTxGetArg;
	TXXFRM		pTxXfrm;
	TXEVAL		pTxEval;
	TXTERM		pTxTerm;
	TXFINI		pTxFini;
	struct UserDll __far *prior;
}	UserDll,__far *pUserDll;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

pUserDll API3D GetUserDll(STR4 name);
void API3D UnloadUserDlls(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif


