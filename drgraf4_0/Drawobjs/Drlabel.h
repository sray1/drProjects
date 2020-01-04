// Label.h : header file
//
#ifndef _DRLABEL_H
#define _DRLABEL_H       

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA



#include "DrObject.h" 
#include "DrNode.h" 
#include "Def_Draw.h" 
//////////////////// 
#define MAX_LABEL_DRAW_PT	1
/////////////////////////////////////////////////////////////////////////////
// CDrLabel    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrLabel: public CDrObject
{
public:
// Construction                 
	CDrLabel();
//////////////////////////////////////
	DECLARE_SERIAL(CDrLabel);
//////////////////////////////////////
	
	
// Operations
public:

	////////////////////////////////////////////////////////////////Begin DrObject OverRides
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void		DoDrawView(CDC* PtrDC,BOOL bPenChange,int nViewNumber);
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	virtual void		InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 		pMATRIX pViewM,pMATRIX pvv3DM,double dzMin,
							double dScale_U,double dScale_V);
	virtual void 		Corner_3Dto2D();
	////////////////////////////////////////// for projection
	virtual int			GetMaxCorners(){return (int)MAX_LABEL_DRAW_PT;}; 
	virtual	void 		GetRawCoords(long* lCoord, int* pnPrecision, int index);
	virtual void		SetProjectedCoords(POINT pt, int index)
						{ 
							m_pt[index] = pt;
						};
	//////////////////////////////////////////////////////////////
	virtual BOOL		IsMoved(){return m_bMoved;};
	virtual void		SetMoved(BOOL  bMoved){m_bMoved = bMoved;};	

	virtual void 		FinishObject(CClientDC* pDC,int nViewNumber);
	virtual BOOL 		IsObjectHit(CClientDC* ptrDC,int nNet,
									POINT point,CRect* pRect,int nViewNumber);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	//////////////////////////////////////////////////////////////////End DrObject OverRides
	virtual	CDrNode*	GetNodePtr(){return m_pDrNode[0];};	// use when new Transformation
	virtual void		SetNodePtr(CDrNode* ptr){m_pDrNode[0] = ptr;};
 	virtual CONTEXTOBJ	GetContextObj(){return m_ContextObj;};
	virtual void		SetContextObj(CONTEXTOBJ c){m_ContextObj = c;};	
 	virtual UINT		GetMeshElemType(){return m_MeshElemType;};
	virtual void		SetMeshElemType(UINT c){m_MeshElemType = c;};	
   ////////////////////////////////////////////////////////////////////// helper
	virtual COLORREF	GetColor(){return m_Color;};
	virtual void		SetColor(COLORREF Color){m_Color = Color;};	
	virtual int			GetViewNum(){return m_nViewNum;};
	virtual void		SetViewNum(int nViewNum){m_nViewNum = nViewNum;};	
	virtual int			GetType(){return m_nType;};
	virtual void		SetType(int nType){m_nType = nType;};	
	virtual CString		GetText(){return m_Text;};
	virtual void		SetText(CString text){m_Text = text;};
	virtual void		SetLogFont(LOGFONT lf){ m_lf = lf;};
	virtual LOGFONT		GetLogFont(){ return m_lf;};
	virtual POINT		GetCorner(int nViewNum);   // screen projected
	virtual void		SetCorner(POINT Corner,int nViewNum);// screen projected
	virtual POINT		GetOtherCorner(){return m_RBCorner;}; // addition for
	virtual void 		SetOtherCorner(POINT Corner)          // other corner
	                    		{m_RBCorner = Corner;};
	virtual int			GetAngle(){return m_nTilt;};
	virtual void		SetAngle(int nAngle){m_nTilt = nAngle;};	
	/////////////////////////////////////////////////////////////
	
// Helper functions
	 
protected:
	
	void 	GoDoIt(CDC* PtrDC,POINT* pt,CString text,BOOL bPenChange,int nViewNumber);
	void 	DrawRotatedString(CDC* pDC, POINT* s, CString str, double angle);
	void 	RotateBitMap(CDC* pdcSrc,CDC* pdcDst,CRect* r,double angle);
			
// Helper functions
protected:
// Attributes
 
	/////////////////////////////////
	BOOL		m_bMoved;
	CDrNode*	m_pDrNode[MAX_LABEL_DRAW_PT];	// use when new Transformation
	POINT		m_RBCorner; //  Add h,v for RightBottom Corner
	int 		m_nType;	// we save coord in node and use here
							// -1 = Node Label(for All Views: default)
							//  0 = 2D ScreenLabel( View-specific)
							//	1 = 3D Label( View-specific)
	CONTEXTOBJ	m_ContextObj;// CO_NODE,CO_FORCE,CO_CURVE etc
	UINT		m_MeshElemType;
	///////////////////////////////////
	COLORREF	m_Color; 
	CString		m_Text;     // Label Card
	int			m_nIndex;   // nodeId index or other based on m_ntype
	int			m_nViewNum;							
	int			m_nRotation;// for rotating text
	int			m_nTilt;
	int 		m_nShift;
	//////////////////////
	LOGFONT		m_lf;
	POINT 		m_pt[4];// for 4 Views:XFormed & Projected Coords

	

public:
	virtual ~CDrLabel(){};
public:
};

#undef AFX_DATA
#define AFX_DATA
/////////////////////////////////////////////
#endif                                       



