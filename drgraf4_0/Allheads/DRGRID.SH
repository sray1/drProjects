// FreeHand.h : header file
//
#ifndef _FREEHAND_H
#define _FREEHAND_H       

#include "DrObject.h" 
/////////////////////////////////////////////////////////////////////////////
// CDrFreeHand    ///////////////////////////////////////////////////////////////
class CDrFreeHand: public CDrObject
{
public:
// Construction                 
	CDrFreeHand();
	DECLARE_SERIAL(CDrFreeHand);
	
	
// Operations
public:

	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void		DoDrawView(CDC* PtrDC,BOOL bPenChange,int nViewNumber);
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	////////////////////////////////////////// for projection
//	virtual int			GetMaxCorners(){return (int)m_pointArray.GetSize();};
//	virtual	void 		GetRawCoords(long* lCoord, int nPrecision, int index); 
	virtual void		SetProjectedCoords(POINT pt, int index) // for Move Only
						{                                       // drag by the
							m_pt[0] = pt;                   	// Ist Point
						};                                      // = 0 at Creation
	//////////////////////////////////////////////////////////////
	virtual BOOL		IsMoved(){return m_bMoved;};
	virtual void		SetMoved(BOOL  bMoved){m_bMoved = bMoved;};	

	virtual void 		FinishObject(int nViewNumber);
	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
									POINT point,RECT* pRect,int nViewNumber);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
    ////////////////////////////////////////////////////////////////////// FrreHand
	virtual int			GetFreeHandNum(){return m_nFHNumber;};
	virtual void		SetFreeHandNum(int nNum){m_nFHNumber = nNum;};	
	virtual int			GetViewN     ��   � 6 2      J� VF�  �   9        ��   � 6 2      J� BF�  �   =        ��   � 6 2      J� rF�  �   _        ��   � 6 2      J� 2 O
�  �   g        ��   � 6 2      J� �O
�  �   i        ��   � 6 2      J� r
O
�  �   k        ��   � 6 2      J� ^O
�  �   m        ��   � 6 2      J� �	O
�  �   o        ��   � 6 2      J� 2
F�  �   q        ��   � 6 2      ber;		// FreeHand Number
	CDWordArray m_pointArray;   	// series of connected points
    int			m_nViewNum; 
    ////////////////////////////////// Starting point move difference
    POINT       m_pt[1];            // set to 0 in the beginning
	///////////////////////////////////

public:
	virtual ~CDrFreeHand(){};
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrFreeHand)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
/////////////////////////////////////////////
#endif                                       



