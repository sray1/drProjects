// CScaleFactor.h : header file
//
#ifndef _SCALEFACTOROBJECT
#define _SCALEFACTOROBJECT

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h" 
/////////////////////////////////////////////////////////////////////////////
// CScaleFactor
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CScaleFactor : public CDrObject
{
// Construction
public:  
	CScaleFactor();

	DECLARE_SERIAL(CScaleFactor)


protected: 
public:
// Implementation
public:

	///////////////////////////////////////////////////// EXPORTS needed for DLL
	virtual void	DoDataView(CDC* PtrDC, int y);
	virtual int 	GetObjectType(){return m_nObjectType;};
	virtual void 	SetObjectType(int nType){m_nObjectType = nType;};
	virtual int 	GetElemType(){return m_nElemType;};
	virtual void	SetElemType(int nType){m_nElemType = nType;};
	virtual long 	GetObjectNo(){return m_nObjectNo;}; 
	virtual void	SetObjectNo(long nNo){ m_nObjectNo = nNo;};
	virtual void	Pack_drPipe(CString* pstrCard);
	virtual void 	GetObjectInfo(CDrObject* pObject);
	virtual void 	SetObjectInfo(CDrObject* pObject);
	///////////////////////////////////////////////////// ScaleFactor
	virtual double	GetScaleFactor(){return m_dScaleFactor;};
	virtual void	SetScaleFactor(double dScaleFactor){ m_dScaleFactor = dScaleFactor;};    				
	virtual double	GetScaleFactorOld(){return m_dScaleFactorOld;};
	virtual void	SetScaleFactorOld(double dScaleFactor){ m_dScaleFactorOld = dScaleFactor;};    				
	virtual double	GetScaleFactorDefault(){return m_dScaleFactorDefault;};
	virtual void	SetScaleFactorDefault(double dScaleFactor)
								{ m_dScaleFactorDefault = dScaleFactor;};    				
	/////////////////////////////////////////
	virtual	void 	ReadDefaultScaleFactor();
	virtual	void 	InitScaleFactor();

		
	
protected:

	int			m_nElemType;	
	int			m_nObjectType;
	long		m_nObjectNo;
	/////////////////////////////////////////// ScaleFactor
    double	m_dScaleFactor;
    double	m_dScaleFactorOld;
    double	m_dScaleFactorDefault;  

protected: 

public:
	virtual ~CScaleFactor(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CScaleFactor)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
