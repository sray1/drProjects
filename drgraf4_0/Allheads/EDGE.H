// Patch.h : header file
//
#ifndef _EDGE_H
#define _EDGE_H       

#include "DrObject.h"

#include "DListMgr.h"
/////////////////////////////////////////////////////////////////////////////
// CDrEdge    ///////////////////////////////////////////////////////////////
class CDrEdge: public CDrObject
{
public:
// Construction                 
	CDrEdge();
	DECLARE_SERIAL(CDrEdge);
	
	
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
	virtual UINT 		GetObjectNo(){return m_nObjectNo;}; 
	virtual void		SetObjectType(int nType){ m_nObjectType = nType;};
	virtual void		SetElemType(int nType){ m_nElemType = nType;};
	virtual void		SetObjectNo(UINT nNo){ m_nObjectNo = nNo;}; 
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	////////////////////////////////////////// for projection
	virtual int			GetMaxCorners(){return (int)MAX_NODES_VOLUME;};
	virtual	void 		GetRawCoords(long* lCoord, int* pnPrecision, int index);
	virtual void		SetProjectedCoords(POINT pt, int index)
						{ 
							m_pt[index] = pt;
						};
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
    virtual	CDListMgr*	GetPolyList(){return &m_PolyList;};
	//////////////////////////////////////////////////////////////////////						
	virtual	int 		AppendToObject(CDListMgr* pPolyList, CDListMgr* pNodeList);
	virtual	int 		SetObjectTransform(pMatrix xF);
	virtual	int 		CatObjectTransform(pMatrix xF);
	virtual	int 		GetObjectTransform(pMatrix xF);
	virtual	int 		SetObjectRAttribs(pRendAttr pRA);
	virtual	int 		GetObject3DBounds(LPOINT3* pMin, LPOINT3* pMax);
	 
protected:
	
	void 		GoDoIt(CDC* PtrDC,POINT* pt,BOOL bPenChange);
			
// Helper functions
protected:
// Attributes
 
	int			m_nObjectType;
	int			m_nElemType;	
	UINT		m_nObjectNo;
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
	CDListMgr	m_PolyList;        // DrObject
	Matrix		m_instanceXf;
	RendAttr	m_raOptions;
	BOOL		m_bInstanced;
    ///////////////////////////////// 
	POINT 		m_pt[MAX_NODES_VOLUME];           // SCREEN Coords.of Corners of 3DBoundVolume

public:
	virtual ~CDrEdge(){};
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrEdge)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
/////////////////////////////////////////////
#endif                                       



