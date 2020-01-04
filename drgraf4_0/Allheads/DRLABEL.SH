// Label.h : header file
//
#ifndef _LABEL_H
#define _LABEL_H       


#include "DrObject.h" 
#include "DrNode.h" 
//////////////////// 
#define MAX_LABEL_DRAW_PT	1
/////////////////////////////////////////////////////////////////////////////
// CDrLabel    ///////////////////////////////////////////////////////////////
class CDrLabel: public CDrObject
{
public:
// Construction                 
	CDrLabel();
	DECLARE_SERIAL(CDrLabel);
	
	
// Operations
public:

	////////////////////////////////////////////////////////////////Begin DrObject OverRides
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual int 		GetLevelType(){return m_nLevelType;};
	virtual void		SetLevelType(int nType){ m_nLevelType = nType;};
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void		DoDrawView(CDC* PtrDC,BOOL bPenChange,int nViewNumber);
	virtual CString		GetObjectID(){return m_ObjectID;}; 
	virtual void		SetObjectID(CString strID){ m_ObjectID = strID;}; 
	virtual long 		GetObjectNo(){return m_nObjectNo;}; 
	virtual void		SetObjectNo(long nNo){ m_nObjectNo = nNo;};
	virtual int 		GetObjectType(){return m_nObjectType;};
	virtual void		SetObjectType(int nType){ m_nObjectType = nType;};
	virtual int 		GetElemType(){return m_nElemType;};
	virtual void		SetElemType(int nType){ m_nElemType = nType;};
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
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
	virtual CRect	 	GetBoundingRect() { return m_rectBounding; };

	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
									POINT point,RECT* pRect,int nViewNumber);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	//////////////////////////////////////////////////////////////////End DrObject OverRides
	virtual	CDrNode*	GetNodePtr(){return m_pDrNode[0];};	// use when new Transformation
	virtual void		SetNodePtr(CDrNode* ptr){m_pDrNode[0] = ptr;};
	/////////////////////////////////////////////////						
	virtual UINT		GetLayer(){return m_nLayer;};
	virtual void		SetLayer(UINT nLayer){m_nLayer = nLayer;};
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
	virtual BOOL		IsGenerated(){return m_bGenerated;};
	virtual void		SetGenerated(BOOL bGen){m_bGenerated = bGen;};
	virtual int			GetLevel(){return m_nLevel;};
	virtual void		SetLevel(int nLevel){m_nLevel = nLevel;};
	
// Helper functions
	 
protected:
	
	void 	GoDoIt(CDC* PtrDC,POINT* pt,CString text,BOOL bPenChange,int nViewNumber);
	void 	DrawRotatedString(CDC* pDC, POINT* s, CString str, double angle);
	void 	RotateBitMap(CDC* pdcSrc,CDC* pdcDst,CRect* r,double angle);
			
// Helper functions
protected:
// Attributes
 
	int			m_nLevelType;
	int			m_nObjectType;
	int			m_nElemType;	
	long		m_nObjectNo;
    /////////////////////////////////
	CString		m_ObjectID;
	/////////////////////////////////
	/////////////////////////////////
	BOOL		m_bMoved;
	CDrNode*	m_pDrNode[MAX_LABEL_DRAW_PT];	// use when new Transformation
	POINT		m_RBCorner; //  Add h,v for RightBottom Corner
	int 		m_nType;	// we save coord in node and use here
							// -1 = Node Label(for All Views: default)
							//  0 = 2D ScreenLabel( View-specific)
							//	1 = 3D Label( View-specific)
	///////////////////////////////////
	CRect       m_rectBounding; // smallest rect that surrounds 
								// Pipe Ends measured in MM_LOENGLISH units
								// (0.01 inches, with Y-axis inverted)
	UINT		m_nLayer;
	///////////////////////////////////
	COLORREF	m_Color; 
	CString		m_Text;     // Label Card
	int			m_nIndex;   // nodeId index or other based on m_ntype
	int			m_nViewNum;							
	int			m_nRotation;// for rotating text
	int			m_nTilt;
	int 		m_nShift;
	
	LOGFONT		m_lf;
	POINT 		m_pt[4];// for 4 Views:XFormed & Projected Coords
	///////////////////////////////////
	BOOL		m_bGenerated;			// generated by Curve or Patch
	int			m_nLevel;				// Hierarchy Level

	

public:
	virtual ~CDrLabel(){};
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrLabel)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
/////////////////////////////////////////////
#endif                                       



