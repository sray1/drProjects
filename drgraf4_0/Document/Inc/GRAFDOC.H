// grafdoc.h : header file
//
/////////////////////////////////////////////////////////////////////////////
#ifndef GRAF_DOC
#define GRAF_DOC 

#include "drgradoc.h"

/////////////////////////////////////////////////////////////////////////////
// CGrafDoc document

class CGrafDoc : public CDrGrafDoc
{
	DECLARE_SERIAL(CGrafDoc)
protected:
	CGrafDoc();			// protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	///////////////////////////////////////////////////// Label
	CObList*	GetLabelList(){return &m_LabelList;};
	int			GetLabelCount(){return m_LabelList.GetCount();};
	///////////////////////////////////////////////////// Pen
	CPen*       GetCurrentPen() { return &m_PenCur; };
	void 		ReplacePen();
	UINT		GetStyleIndex() { return m_nPenStyleIndex; };
	int			GetStyle() { return m_nPenStyle; };
	void		SetStyle(int nStyle) { m_nPenStyle = nStyle; };
	int			GetWidth() { return m_nPenWidth; };
	void		SetWidth(int nWidth) { m_nPenWidth = nWidth; };
	COLORREF	GetColor() { return m_nPenColor; };
 	void		SetWidth(COLORREF nColor) { m_nPenColor = nColor; };
	CString 	GetPenStyleName(UINT nNameIndex)
					{return m_PenStyleNames[nNameIndex];};				  
    UINT 		GetPenStyleIndex(){return m_nPenStyleIndex;};
    UINT 		GetPenStyleNameCount(){return m_nPenStyleNameCount;};
    void 		SetPenStyleNameCount(UINT nPenStyleNameCount)
    				{m_nPenStyleNameCount=nPenStyleNameCount;};
    UINT		GetPenStyleConstants(UINT nIndex)
    				{return m_nPenStyleConstants[nIndex];};				
	///////////////////////////////////////////////////// FreeHand
	CObList*	GetFreeHandList(){return &m_FreeHandList;};
	int			GetFreeHandCount(){return m_FreeHandList.GetCount();};
	int			GetSearchNet(){return m_nSearchNet;};
	void		SetSearchNet(int nNet){ m_nSearchNet = nNet;};
	CDrFreeHand*	GetFreeHandCurrent(){return m_pFreeHandCur;};
	void		SetFreeHandCurrent(CDrFreeHand* pFreeHand){ m_pFreeHandCur = pFreeHand;};
	///////////////////////////////////////////////////                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                SetTranArray(m_dTran);
			};
	UINT	GetRotation(){return m_nRotation;};
	void	SetRotation(UINT nRotation)
			{
				m_nRotation = nRotation;
				SetTranArray(m_dTran);
			};
	///////////////////////////////////////////////////// Transformation
	void 	GetTranArray(double Tran[][3]);
	void 	SetTranArray(double Tran[][3]);
	void	GetAxesDefault(UINT* nAxes);
	void	SetAxesDefault(UINT* nAxes);
	void 	GetTranDefaultArray(double Tran[][3]);
	void 	SetTranDefaultArray(double Tran[][3]);
protected:
// Implementation
protected:
	virtual ~CGrafDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
	virtual	BOOL OnNewDocument();
//.			void ReadDefaults();
//			void Initialize();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGrafDoc)
	afx_msg void OnDrawAxis();
	afx_msg void OnDrawEyeposition();
	afx_msg void OnDrawLayer();
	afx_msg void OnOptionsPenchange();
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////
#endif

