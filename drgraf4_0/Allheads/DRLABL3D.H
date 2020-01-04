// Label.h : header file
//
#ifndef _LABEL_H
#define _LABEL_H       


#include "globals.h" 
#include "DrObject.h" 
//////////////////// 
#define MAX_LABEL_DRAW_PT	1
/////////////////////////////////////////////////////////////////////////////
// CDrLabel3D    ///////////////////////////////////////////////////////////////
class CDrLabel3D: public CDrObject
{
public:
// Construction                 
	CDrLabel3D();
	DECLARE_SERIAL(CDrLabel3D);
	
	
// Operations
public:

	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void 		DoDrawView(CDC* PtrDC,BOOL bPenChange,int nViewNumber);
	virtual int 		GetObjectType(){return m_nObjectType;};
	virtual int 		GetElemType(){return m_nElemType;};
	virtual UINT 		GetObjectNo(){return m_nObjectNo;}; 
	virtual void		SetObjectType(int nType){ m_nObjectType = nType;};
	virtual void		SetElemType(int nType){ m_nElemType = nType;};
	virtual void		SetObjectNo(UINT nNo){ m_nObjectNo = nNo;}; 
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();

	virtual void 		FinishObject(CClientDC* pDC,int nViewNumber);
	virtual CRect	 	GetBoundingRect() { return m_rectBounding; };

	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
									POINT point,RECT* pRect,int nViewNumber);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	///////////////////////////////////////////////////////////////
	virtual UINT		GetLayer(){return m_nLayer;};
	virtual void		SetLayer(UINT nLayer){m_nLayer = nLayer;};
    ////////////////////////////////////////////////////////////////////// helper
	virtual COLORREF	GetColor(){return m_Color;};
	virtual void		SetColor(COLORREF Color)
						{
							m_Color = Color;
						};	
	virtual int			GetViewNum(){return m_nViewNum;};
	virtual void		SetViewNum(int nViewNum)
						{
							m_nViewNum = nViewNum;
						};	
	virtual int			GetType(){return m_nType;};
	virtual void		SetType(int nType)
						{
							m_nType = nType;
						};	
	virtual CString		GetText(){return m_Text;};
	virtual void		SetText(CString text)
						{
							m_Text = text;
						};
	virtual void		SetLogFont(LOGFONT lf){ m_lf = lf;};
	virtual LOGFONT		GetLogFont(){ return m_lf;};
	
	virtual int			GetPrecision(){return m_nPrecision;};
	virtual void		SetPrecision(int nPrec)
						{
							m_nPrecision = nPrec;
						};	
	virtual LPOINT3		GetCorner(){return m_Corner;};
  	virtual void		SetCorner(LPOINT3 Corner)               
  							{
  								m_Corner.x = Corner.x;
  								m_Corner.y = Corner.y;
  								m_Corner.z = Corner.z;
  							};
//	virtual POINT		GetCorner(int nType,int nViewNum);
//	virtual void		SetCorner(int nType,POINT Corner,int nViewNum);
//	virtual POINT		GetOtherCorner(){return m_RBCorner;}; // addition for
//	virtual void 		SetOtherCorner(POINT Corner);         // other corner 

// Helper functions
	 
protected:
	
	void 		GoDoIt(CDC* PtrDC,POINT* pt,CString text,BOOL bPenChange);
			
// Helper functions
protected:
// Attributes
 
	int			m_nObjectType;
	int			m_nElemType;	
	UINT		m_nObjectNo;
	//////////////////////////////
	CRect       m_rectBounding; // smallest rect that surrounds 
								// Pipe Ends measured in MM_LOENGLISH units
								// (0.01 inches, with Y-axis inverted)
	UINT		m_nLayer;
	///////////////////////////////////
	COLORREF	m_Color; 
	CString		m_Text;     // Label Card
	LPOINT3		m_Corner;   // x,y,z location of TopLeft Corner
	int			m_nPrecision;   
/*
	POINT3		m_RBCorner; //  Add x,y,z for RightBottom Corner
	LPOINT		m_Corner;   // x,y location of TopLeft Corner 
	POINT		m_Corner23; // x,y location of TopLeft Corner
	POINT		m_Corner31; // x,y location of TopLeft Corner
	LPOINT		m_CornerIso;// x,y location of TopLeft Corner
	POINT		m_RBCorner; //  Add x,y for RightBottom Corner
*/	
	int			m_nIndex;   // nodeId index or other based on m_ntype
	int 		m_nType;	// we save coord in node and use here
							// -1 = Node Label(for All Views: default)
							//  0 = Label
	int			m_nViewNum;							
	int			m_nRotation;// for rotating text
	int			m_nTilt;
	int 		m_nShift;
	
	LOGFONT		m_lf;
	POINT 		m_pt[MAX_LABEL_DRAW_PT];
    ////////////////////////////////////

	

public:
	virtual ~CDrLabel3D(){};
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrLabel3D)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
/////////////////////////////////////////////
#endif                                       



