// FreeHand.h : header file
//
#ifndef _FREEHAND_H
#define _FREEHAND_H       

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h" 
/////////////////////////////////////////////////////////////////////////////
// CDrFreeHand    ///////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrFreeHand: public CDrObject
{
public:
// Construction                 
	CDrFreeHand();
//////////////////////////////////////
	DECLARE_SERIAL(CDrFreeHand);
//////////////////////////////////////
	
	
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
	virtual void		InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 		pMATRIX pViewM,pMATRIX pvv3DM,double dzMin,
							double dScale_U,double dScale_V);
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
	virtual int			GetViewNum(){return m_nViewNum;};
	virtual void		SetViewNum(int nViewNum){m_nViewNum = nViewNum;};	
	virtual void 		AddPoint(CPoint pt);
	/////////////////////////////////////////////////////////////
	 
protected:
	
	void 		GoDoIt(CDC* PtrDC,POINT pt,int nSequence,int nViewNumber);
	CPoint		GetPoint(int i) const { return CPoint(m_pointArray[i]); }
			
// Helper functions
protected:
// Attributes
 
	//////////////////////////////
	BOOL		m_bMoved;
	/////////////////////////////////// 
	UINT		m_nFHNumber;		// FreeHand Number
	CDWordArray m_pointArray;   	// series of connected points
    int			m_nViewNum; 
    ////////////////////////////////// Starting point move difference
    POINT       m_pt[1];            // set to 0 in the beginning
	///////////////////////////////////

public:
	virtual ~CDrFreeHand(){};
public:
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif



