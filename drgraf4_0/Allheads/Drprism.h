// prism.h : header file
//
#ifndef _DRPRISM_H
#define _DRPRISM_H  

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA



//#include "DrObject.h" 
//////////////////
#define	MAX_PT	8
/////////////////////////////////////////////////////////////////////////////
// CPrism  //////////////////////////////////////////////////////////////////
//class CPrism: public CDrObject
class AFX_EXT_CLASS CPrism: public CObject
{
public:
// Construction 
//	CPrism();                
//	DECLARE_SERIAL(CDrLabel); 
	
	CPrism(UINT nLength,UINT nWidth,UINT nHeight);
	
public:
/* 
	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void		DoDrawView(CDC* PtrDC,BOOL bPenChange,POINT ptZoom,int nViewNumber);
	virtual int 		GetObjectType(){return m_nObjectType;};
	virtual int 		GetElemType(){return m_nElemType;};
	virtual UINT 		GetObjectNo(){return m_nObjectNo;}; 
	virtual void		SetObjectType(int nType){ m_nObjectType = nType;};
	virtual void		SetElemType(int nType){ m_nElemType = nType;};
	virtual void		SetObjectNo(UINT nNo){ m_nObjectNo = nNo;}; 
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual void 		FinishObject(CClientDC* pDC,int nViewNumber);
	virtual int 		DealObjectDialog();
	virtual CRect	 	GetBoundingRect() { return m_rectBounding; };
	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
									POINT point,RECT* pRect,int nViewNumber);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	///////////////////////////////////////////////////////////////
*/	
	virtual void	 DrawPrism(CDC* PtrDC,POINT Origin,double Tran[][3]);
	
protected:	
	virtual POINT    TransformPoint3to2(double* Coord,double Tran[][3]);
	virtual void	 GoConnect(CDC* PtrDC,POINT* pt);
protected:
	UINT 	m_nLength;
	UINT 	m_nWidth;
	UINT 	m_nHeight;
	POINT 	m_pt[MAX_PT];
	double 	m_Coord[3][MAX_PT]; 
public:
};


#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
