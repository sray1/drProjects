// Elembox.h : header file
// 
#ifndef _MESHBOX_H
#define _MESHBOX_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA
#include "MeshBar.h"   //access to CMeshBar
#include "TriBox.h"   //access to CCTriBox
#include "QuadBox.h"   //access to CQuadBox
#include "HexBox.h"   //access to CHexBox
#include "PenBox.h"   //access to CHexBox
#include "TetBox.h"   //access to CHexBox
/////////////////////////////////////////////////////////////////////////////
// CMeshBox window

class CMeshBox : public CWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CMeshBox();
	virtual ~CMeshBox(); 


	DECLARE_DYNAMIC(CMeshBox);



    UINT			GetWidth();
    UINT			GetHeight();
	int  			GetActiveTool();         // move,edit etc
	int  			GetActiveElemObject();   // object type
    /////////////////////////////////////////////////////////// Children,Popup etc
//	BOOL 			Create(CMDIFrameWnd* pParentWnd,CRect rect);
	BOOL 			Create(CWnd* pParentWnd,CRect rect);
    /////////////////////////////////// helper
	BOOL 			CreateElemBar();
	CMeshBar*		GetElemBar(){return &m_wndElemBar;};
	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();      				 // set eBoxMgr members
	///////////////////////////////////////////////////////////
	int 			GetToolNum(int index);
	void 			FillToolNumArray();
    ///////////////////////////////////////////////////////////////////
	void 			SetActiveTool(int nTool){m_nActiveTool = nTool;};
	void 			SetActiveElemObject(int nObject){m_nActiveElemObject = nObject;};
    void			SetWidth(UINT nWidth){m_nWidth = nWidth;};
    void			SetHeight(UINT nHeight){m_nHeight = nHeight;};
	int				GetElemBarButtCount(){return m_nElemBarButtCount;};
	////////////////////////////////////////////////////////////// TriBoxes
    CTriBox* 		GetTriBox(){return &m_wndTriBox;};
    CSize			GetSizeTriBox(){return m_szTriBox;};
    void			SetSizeTriBox(CSize szBox){m_szTriBox = szBox;};
	////////////////////////////////////////////////////////////// QuadBoxes
    CQuadBox* 		GetQuadBox(){return &m_wndQuadBox;};
    CSize			GetSizeQuadBox(){return m_szQuadBox;};
    void			SetSizeQuadBox(CSize szBox){m_szQuadBox = szBox;};
	////////////////////////////////////////////////////////////// HexBoxes
    CHexBox* 		GetHexBox(){return &m_wndHexBox;};
    CSize			GetSizeHexBox(){return m_szHexBox;};
    void			SetSizeHexBox(CSize szBox){m_szHexBox = szBox;};
	////////////////////////////////////////////////////////////// PenBoxes
    CPenBox* 		GetPenBox(){return &m_wndPenBox;};
    CSize			GetSizePenBox(){return m_szPenBox;};
    void			SetSizePenBox(CSize szBox){m_szPenBox = szBox;};
	////////////////////////////////////////////////////////////// TetBoxes
    CTetBox* 		GetTetBox(){return &m_wndTetBox;};
    CSize			GetSizeTetBox(){return m_szTetBox;};
    void			SetSizeTetBox(CSize szBox){m_szTetBox = szBox;};



// Operations
public:
	BOOL 			IsEditMoveTool(UINT nID);

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CMeshBar	m_wndElemBar; 
	///////////////////////////////////
    UINT    	m_nElemBarColMax;
    UINT		m_nElemBarRowMax;
	int 		m_nActiveTool;         // tool(edit or move)
	int			m_nActiveElemObject;   // other objects
	int			m_nElemBarButtCount;
	int			m_nToolNumArray[100];
	UINT		m_elembox[100];
    /////////////////////////////////
    UINT		m_nWidth;
    UINT		m_nHeight;
	//////////////////////////////// TriBox
	CTriBox		m_wndTriBox;
	CSize		m_szTriBox;
	//////////////////////////////// QuadBox
	CQuadBox	m_wndQuadBox;
	CSize		m_szQuadBox;
	//////////////////////////////// HexBox
	CHexBox		m_wndHexBox;
	CSize		m_szHexBox;
	//////////////////////////////// PenBox
	CPenBox		m_wndPenBox;
	CSize		m_szPenBox;
	//////////////////////////////// TetBox
	CTetBox		m_wndTetBox;
	CSize		m_szTetBox;
    //////////////////////

	
	// Generated message map functions
protected:

	//{{AFX_MSG(CMeshBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif

