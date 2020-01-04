#include <3dcolor.h>
#include <TXUDLL.h>
#include <string.h>

pUserDll	pUDll = NULL;	// 3d context sensitive?

pUserDll API3D GetUserDll(STR4 name)
{
	pUserDll	tpUDll = pUDll;

	while( tpUDll ) {
		if( tpUDll->name == name )
			return tpUDll;		// already in the stack
		tpUDll = tpUDll->prior;
	}
	if( !tpUDll ) {				// new stack entry needed
		char		dll[] = "TXXXXX.DLL";
		HINSTANCE	hLib;

		_fmemcpy( dll+2, &name, 4 );
		hLib = LoadLibrary( dll );
		if( hLib >= (HINSTANCE)32 ) {
			tpUDll			= (pUserDll)NewPtr( sizeof(UserDll) );
			tpUDll->name	= name;
			tpUDll->hLib	= hLib;
			tpUDll->pTxInit = (TXINIT)GetProcAddress( hLib, "Init" );
			tpUDll->pTxSetArg=(TXSETARG)GetProcAddress( hLib, "SetArg" );
			tpUDll->pTxGetArg=(TXGETARG)GetProcAddress( hLib, "GetArg" );
			tpUDll->pTxXfrm = (TXXFRM)GetProcAddress( hLib, "Xfrm" );
			tpUDll->pTxEval = (TXEVAL)GetProcAddress( hLib, "Eval" );
			tpUDll->pTxTerm = (TXTERM)GetProcAddress( hLib, "Term" );
			tpUDll->pTxFini = (TXFINI)GetProcAddress( hLib, "Fini" );
			tpUDll->prior = pUDll;
			pUDll = tpUDll;
		}
	}
	return tpUDll;
}

void API3D UnloadUserDlls(void)
{
	pUserDll	tpUDll;

	while( pUDll ) {
		if( pUDll->hLib >= (HINSTANCE)32 ) {
			if( pUDll->pTxFini != NULL )
				pUDll->pTxFini();
			FreeLibrary( pUDll->hLib );
		}
		tpUDll = pUDll;
		pUDll = pUDll->prior;
		DisposPtr( (Ptr)tpUDll );
	}
}
