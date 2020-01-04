// CLight.h : header file
//
#ifndef _CLIGHT_H_
#define _CLIGHT_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Rend.h"
//#include "Globals.h"
/////////////////////////////////////////////////////////////////////////////
// CLight
/////////////////////////////////////////////////////////////////////////////
class CLight : public CObject
{
// Construction
public:  
	CLight();
	DECLARE_DYNAMIC(CLight)
protected: 
public:
// Implementation
public:
 
    ///////////////////////////////////////////////////// 
	virtual RGBCOLOR 	LightEffect
							(
							pLTENVIRON 	pL,
							pRENDINFO	pRA,
							pWORLD		pP,	// current transformed 3d point
							pWORLD		pN,	// current normal vector
							BOOL		b_ShadowOn
							);
	virtual int 		NewLightEnvironMent
							(
							pLTENVIRON	pL,		// Light Environ	
							COLORFACTOR R,
							COLORFACTOR G,
							COLORFACTOR B,		// ambient light
							double 		lvl,	// intensity scaling
							int 		nS,		// number of sources
							pLTSOURCE 	ppLS	// pointer to array of sources
							);
//	virtual int 		AugmentLightEnvironment(pRENDINFO pRA,
//												pLTENVIRON pLE);
	virtual void 		FocusLightSource(	pLTSOURCE pLS,
											double x,
											double y,
											double z);
	virtual void 		SetLightSource
							(	
							pLTSOURCE pLS,
							COLORFACTOR R,COLORFACTOR G,COLORFACTOR B,
							double lvl,
							double x,double y,double z
							);
	virtual void 		TransformLightEnviron(pLTENVIRON pL,pMATRIX pXFM);
	virtual double 		LightIntensity
							(
							double		Si,		// specular index
							double		Ks,		// specular reflection coefficient
							double		Kd,		// diffuse reflection coefficient
							pWORLD		pN,		// normal vector
							pWORLD		pC,		// center of reflection
							pLTSOURCE	pLS,	// light source
							double		*pld	// returned light distance
							);


protected:

	 

public:
	virtual ~CLight(){};
//	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CLight)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
