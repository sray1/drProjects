// CXForm.h : header file
//
#ifndef _XFORM_H_
#define _XFORM_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
#include "Def_View.h"
/////////////////////////////////////////////////////////////////////////////
// CXForm
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CXForm : public CObject
{
// Construction
public:  
	CXForm();
	CXForm(BOOL bParallel); // Overload
	DECLARE_SERIAL(CXForm)

protected: 
public:
// Implementation
public:
 
	virtual void	Reflect(pMATRIX pM,WORLD N,double p);
	virtual void 	Scale(pMATRIX pM,double sx,double sy,double sz,
							XFMODE mode);
	virtual void 	Shear_X(pMATRIX pM,double sy,double sz,XFMODE mode);
	virtual void 	Shear_Y(pMATRIX pM,double sx,double sz,XFMODE mode);
	virtual void 	Shear_Z(pMATRIX pM,double sx,double sy,XFMODE mode);
	virtual void	Rotate_X(pMATRIX pM,double ang,XFMODE mode);
	virtual void 	Rotate_Y(pMATRIX pM,double ang,XFMODE mode);
	virtual void 	Rotate_Z(pMATRIX pM,double ang,XFMODE mode);
	virtual void 	Translate(pMATRIX pM,double dx,double dy,double dz,
							XFMODE mode);
	//////////////////
	virtual void 	RotateAboutLineMATRIX(pMATRIX pM, pWORLD p0,pWORLD p1,
							double dAng,XFMODE mode);
	virtual void	HeadToNewZLocMATRIX(pWORLD pFrom, pWORLD pTo, pMATRIX pM,
							XFMODE mode);
	virtual void	RotateToNewZMATRIX(pWORLD pNewZ, pMATRIX pM,XFMODE mode);
	virtual void	HeadToNewYLocMATRIX(pWORLD pFrom, pWORLD pTo, pMATRIX pM,
							XFMODE mode);
	virtual void	RotateToNewYMATRIX(pWORLD pNewY, pMATRIX pM,XFMODE mode);
	virtual void	HeadToNewXLocMATRIX(pWORLD pFrom, pWORLD pTo, pMATRIX pM,
							XFMODE mode);
	virtual void	RotateToNewXMATRIX(pWORLD pNewX, pMATRIX pM,XFMODE mode);
	//////////////////
	virtual void 	VRCtoWORLDRotationMATRIX(pMATRIX pM,pWORLD pNewZ,
							pWORLD pUp);
	virtual void 	ComposeLocalMATRIX(pMATRIX pMLocal,
							double rx, double ry, double rz,
							double sx,double sy,double sz, 
							double shx,double shy,double shz, 
							double tx,double ty,double tz);
	virtual double 	ComposeViewMATRIX(pMATRIX pNPar,
							WORLD VRP,WORLD VPN,WORLD VUP,
							WORLD CW, WORLD PRP,
							double Front,double Back,
							double width_U,double width_V);
	virtual void 	PerToParCVVMATRIX(pMATRIX pM,double dzMin);
	virtual int 	ALT_ComposeViewMATRIX(pMATRIX pNPar,
							WORLD VRP,WORLD VPN,WORLD VUP,
							WORLD CW, WORLD PRP,
							double Front,double Back,
							double width_U,double width_V);
	virtual void 	SetVOMATRIX(pMATRIX pVOM,WORLD VRP,WORLD VPN,
						    WORLD VUP);
	virtual void 	Par_SetVMMATRIX(pMATRIX pVMM,
							WORLD CW, WORLD PRP,
							double Front, double Back,
							double width_U, double width_V);
	virtual double 	Per_SetVMMATRIX(pMATRIX pVMM,
							WORLD CW, WORLD PRP,
							double Front, double Back,
							double width_U, double width_V);
	virtual void 	ComposeCombineMATRIX(
							pMATRIX pLM,pMATRIX pVM,pMATRIX pCM);
	virtual void 	Transform(pWORLD pt1, pWORLD pt2, pMATRIX pM);
	virtual void 	TransformPerToParCVV(
							double dzMin, pWORLD pPer, pWORLD pPar);
	virtual void 	ComposeWin3DtoScreen3DMATRIX(pMATRIX pM,
							WORLD Vmin, WORLD Vmax);
	virtual void 	Project(pMATRIX pMvv3D,pWORLD ptIn, pWORLD ptOut);
	
	virtual void 	SetParallel(BOOL bState){m_bParallel = bState;};
	virtual BOOL 	GetParallel(){return m_bParallel;};

protected:

	BOOL	m_bParallel;	// if true disables perspective projection
    /////////////////////

protected: 

public:
	virtual ~CXForm(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CXForm)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
