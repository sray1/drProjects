// Obj3D.h : header file
//
#ifndef _OBJ3D_H_
#define _OBJ3D_H_       

#include "DrObject.h"
#include "DListMgr.h"
#pragma warning( disable : 4200 )
//#include "3d.h"
//#include <3dhrchy.h>               // Render Attribs.
#include "3dcolor.h"
/////////////////////////////////////////////////////////////////////////////
#define MAX_NODES_OBJ3D	2
// CDrObj3D    ///////////////////////////////////////////////////////////////
class CDrObj3D: public CDrObject
{
public:
// Construction                 
	CDrObj3D();
	DECLARE_SERIAL(CDrObj3D);
	
	
// Operations
public:

	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void 		DoDrawView(CDC* PtrDC,BOOL bPenChange);
	virtual CString		GetObjectID(){return m_ObjectID;}; 
	virtual void		SetObjectID(CString strID){ m_ObjectID = strID;}; 
	virtual int 		GetObjectType(){return m_nObjectType;};
	virtual int 		GetElemType(){return m_nElemType;};
	virtual long 		GetObjectNo(){return m_nObjectNo;}; 
	virtual void		SetObjectNo(long nNo){ m_nObjectNo = nNo;};
	virtual void		SetObjectType(int nType){ m_nObjectType = nType;};
	virtual void		SetElemType(int nType){ m_nElemType = nType;};
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	////////////////////////////////////////// for projection
	virtual int			GetMaxCorners(){return (int)MAX_NODES_OBJ3D;};
	virtual	void 		GetRawCoords(long* lCoord, int index);
	virtual void		SetProjectedCoords(POINT pt, int index)
						{ 
							m_pt[index] = pt;
						};
	////////////////////////////////////////////////////////////////////////////////////////						
	// we are dealing with only max & min values(2 pts with 6 values);
	// after transform/projection actual pts(8 corners) will reduce to TopLeft & RightBottom
	// but MaxMin are mixed; so, needs to be compared and rearranged & put in right place
	// This should be done immediately after SetProjectCoords by calling following function
	// from
	// UpdateObject() of DrawView for smart painting						
	virtual void		RearrangeProjectedCoords();// put max/min in right place;					
	//////////////////////////////////////////////
	virtual	void 		FinishObject();
	virtual CRect	 	GetBoundingRect() { return m_rectBounding; };

	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
									POINT point,RECT* pRect);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	////////////////////////////////////////////////
	virtual void        GetPenInfo(UINT nWidth,COLORREF crColor,UINT nStyle)
						{	nWidth  =	m_nPenWidth;
					 	 	crColor =	m_crPenColor;
					  		nStyle  =	m_nPenStyle;
				  		};	
	virtual void        SetPenInfo(UINT nWidth,COLORREF crColor,UINT nStyle)
						{	m_nPenWidth  = nWidth;
					 		m_crPenColor = crColor;
					 		m_nPenStyle  = nStyle;
						};
	////////////////////////////////////////////////
	virtual UINT		GetLayer(){return m_nLayer;};
	virtual void		SetLayer(UINT nLayer){m_nLayer = nLayer;};
    ////////////////////////////////////////////////////////////////////// helper
    virtual	CDListMgr*	GetNodeList(){return &m_NodeList;};
    virtual	CDListMgr*	GetPatchList(){return &m_PatchList;};
	//////////////////////////////////////////////////////////////////////						
	virtual	int 		AppendToObject(CDListMgr* pPatchList, CDListMgr* pNodeList);
	virtual	int 		SetObjectTransform(pMATRIX xF);
	virtual	int 		CatObjectTransform(pMATRIX xF);
	virtual	int 		GetObjectTransform(pMATRIX xF);
	virtual	int 		SetObjectRAttribs(pRendAttr pRA);
	virtual	int 		GetObject3DBounds();				//ConvexHull of CNodes
	 

protected:
	
	void 		GoDoIt(CDC* PtrDC,POINT* pt,BOOL bPenChange);
			
// Helper functions
protected:
// Attributes
 
	int			m_nObjectType;
	int			m_nElemType;	
	long		m_nObjectNo;
	//////////////////////////////
	UINT		m_nLayer;
	CRect       m_rectBounding; // smallest rect that surrounds 
								// Pipe Ends measured in MM_LOENGLISH units
								// (0.01 inches, with Y-axis inverted)
    //////////////////////////////
	UINT        m_nPenWidth;    // pen width for Pipe
	COLORREF	m_crPenColor;
	UINT		m_nPenStyle;
    /////////////////////////////////
	CString		m_ObjectID;
	/////////////////////////////////
	CDListMgr	m_NodeList;        // DrObject
	CDListMgr	m_PatchList;       // DrObject
	MATRIX		m_instanceXf;
	RendAttr	m_raOptions;
	BOOL		m_bInstanced;
    ////////////////////////////////////////////////////////////////////////////////
    LPOINT3		m_ptMinMax[2];			// Raw Bounding Coords mixed as Min & Max 
	POINT 		m_pt[MAX_NODES_OBJ3D];	// SCREEN Coords.of Corners of 3DBoundVolume
    ////////////////////////////////////////////////////////////////////////////////
    

public:
	virtual ~CDrObj3D(){};
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrObj3D)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
/////////////////////////////////////////////
#endif                                       



