// Vuport.h : interface of the CVuport class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef VUPORT_H
#define VUPORT_H
 
#include "grafobj.h"  
#include "globals.h"  
 
class CVuport : public CGrafObject 
{

protected: // create from serialization only
	CVuport();
	DECLARE_DYNCREATE(CVuport)

// Attributes
public: 

protected:                  

    POINT	m_VuportMouseLoc;
    POINT3	m_VuportAnchorLoc;
    POINT	m_VuportOrigin;
    POINT	m_Vup         ÀÀÀ   ÿ  ÿ   ÿÿ ÿ   ÿ ÿ ÿÿ  ÿÿÿ           wwwwwwwwwwpwwwwwwwwwwpppp DHp DHp p  Dxp    Dxp   Hp   Dxp  DtGp  GDp GDp DtGpDDxpppÿÿÿÿÿÿÿÿÿÿp          BM~      v   (                                                     ÀÀÀ   ÿ  ÿ   ÿÿ ÿ   ÿ ÿ ÿÿ  ÿÿÿ           wwwwwwwwwwpwwwwwwwwwwpp  pwp  xed:
	//{{AFX_MSG(CVuport)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif
