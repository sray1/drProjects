// Axis.h : header file
//
#ifndef _AXISOBJECT
#define _AXISOBJECT  

//#include "DrObject.h" 
//////////////////
#define	MAX_PT_AXIS	7
/////////////////////////////////////////////////////////////////////////////
// CAxisObject/////////////////////////////////////////////////////////////////////////////
class CAxis: public CObject
{
public:  
	CAxis();                      // call from serialization only
	DECLARE_SERIAL(CAxis)
public:
// Construction                 
//	CAxis(UINT nLength);
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
	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClienbb\\\\\\RRRbb\\Rzz                                                                                                                                                                                                               |~~ vvRRRWWffffoorr~  |~||~sRRRRR\\fooiifaaxzzriiffdddaRRoooffRoozzxxjEEÿÿÿhh |||{{~{{~|||||{{{|||{{||{{{{zzz{ooRRRRRORRORRRRRRRGRRR==ÿÿÿ///////// Axis
	virtual UINT	GetVertical(){return m_nVertical;};
	virtual void	SetVertical(UINT nVertical){ m_nVertical = nVertical;};   
	virtual UINT	GetVerticalOld(){return m_nVerticalOld;};
	virtual void	SetVerticalOld(UINT nVertical){ m_nVerticalOld = nVertical;};   
	virtual UINT	GetVerticalDefault(){return m_nVerticalDefault;};
	virtual void	SetVerticalDefault(UINT nVertical){ m_nVerticalDefault = nVertical;};   
	virtual UINT	GetPositive(){return m_nPositive;};
	virtual void	SetPositive(UINT nPositive){ m_nPositive = nPositive;};;   
	virtual UINT	GetPositiveOld(){return m_nPositiveOld;};
	virtual void	SetPositiveOld(UINT nPositive){ m_nPositiveOld = nPositive;};;   
	virtual UINT	GetPositiveDefault(){return m_nPositiveDefault;};
	virtual void	SetPositiveDefault(UINT nPositive){ m_nPositiveDefault = nPositive;};;   
	virtual void	GetAxes(UINT* nAxes);
	virtual void	SetAxes(UINT* nAxes);   
	virtual void	GetAxesOld(UINT* nAxes);
	virtual void	SetAxesOld(UINT* nAxes);   
	virtual void	GetAxesDefault(UINT* nAxes);
	virtual void	SetAxesDefault(UINT* nAxes);
	//////////////////////////////////////////////Drawing data
	virtual UINT	GetLength(){return m_nLength;};
	virtual void	SetLength(UINT nLength){ m_nLength = nLength;}; 
	////////////////////////////////////////////// Needs to be consolidated (??????)  
	virtual void 	TransformPoint3to2(double* Coord,double Tran[][3],
									double* dTranCoord);
	virtual void 	GetTranArray(double Tran[][3]);
	virtual void 	SetTranArray(int nTilt,int nRotation);  
	
protected:	
	///////////////////////////////////////////////////// Unit 
	virtual void 	ReadDefaultAxis();
	virtual void	InitializeAxis();
	//////////////////////////
	virtual void 	GoDoIt(CDC* PtrDC,POINT* pt,UINT* nAxes,UINT nViewNumber);
	//////////////////////////////////////////////////////// scroll


protected:
	/////////////////////////////////////////// Axes     
    UINT	m_nAxes[3];
    UINT	m_nVertical;
    UINT	m_nPositive;
    UINT	m_nAxesOld[3];
    UINT	m_nVerticalOld;
    UINT	m_nPositiveOld;
    UINT	m_nAxesDefault[3];
    UINT	m_nVerticalDefault;
    UINT	m_nPositiveDefault; 
    /////////////////////////////////////// drawing
	UINT 	m_nLength;
	UINT	m_nLengthOld;
	UINT	m_nLengthDefault;
	/////////////////////////
	UINT 	m_nWidth;
	UINT 	m_nHeight;
	POINT 	m_pt[MAX_PT_AXIS];
	double 	m_Coord[3][MAX_PT_AXIS];
	double	m_dTran[2][3]; 

public:
	virtual ~CAxis(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CAxis)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#endif
