// CPrecision.h : header file
//
#ifndef _PRECISONOBJECT
#define _PRECISONOBJECT

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h" 
/////////////////////////////////////////////////////////////////////////////
// CUnit
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CPrecision : public CDrObject
{
// Construction
public:  
	CPrecision();

	DECLARE_SERIAL(CPrecision)


protected: 
public:
// Implementation
public:

	///////////////////////////////////////////////////// EXPORTS needed for DLL
	virtual void	DoDataView(CDC* PtrDC, int y);
	virtual int 	GetObjectType(){return m_nObjectType;};
	virtual void	SetObjectType(int nType){m_nObjectType = nType;};
	virtual int 	GetElemType(){return m_nElemType;};
	virtual void	SetElemType(int nType){m_nElemType = nType;};
	virtual long 	GetObjectNo(){return m_nObjectNo;}; 
	virtual void	SetObjectNo(long nNo){ m_nObjectNo = nNo;};
	virtual void	Pack_drPipe(CString* pstrCard);
	virtual void 	GetObjectInfo(CDrObject* pObject);
	virtual void 	SetObjectInfo(CDrObject* pObject);
	///////////////////////////////////////////////////// Precision
	virtual UINT	GetPrecision(){return m_nPrecision;};
	virtual void	SetPrecision(UINT nPrecision){ m_nPrecision = nPrecision;};    				
	virtual UINT	GetPrecisionOld(){return m_nPrecisionOld;};
	virtual void	SetPrecisionOld(UINT nPrecision){ m_nPrecisionOld = nPrecision;};    				
	virtual UINT	GetPrecisionDefault(){return m_nPrecisionDefault;};
	virtual void	SetPrecisionDefault(UINT nPrecision){ m_nPrecisionDefault = nPrecision;};    				
	///////////////////////////////////////////////////// World
    virtual LONG 	GetWorldBase(){return m_lWorldBase;};
    virtual void 	SetWorldBase(LONG lWorldBase)
    					{ m_lWorldBase = lWorldBase;};
    virtual LONG 	GetWorldBaseOld(){return m_lWorldBaseOld;};
    virtual void 	SetWorldBaseOld(LONG lWorldBase)
    					{ m_lWorldBaseOld = lWorldBase;};
    virtual LONG 	GetWorldBaseDefault(){return m_lWorldBaseDefault;};
    virtual void 	SetWorldBaseDefault(LONG lWorldBase)
    					{ m_lWorldBaseDefault = lWorldBase;};
	////////////////////////
	virtual	void 	ReadDefaultPrecision();
	virtual	void 	InitPrecision();

	
protected:

	int			m_nElemType;	
	int			m_nObjectType;
	long		m_nObjectNo;
	/////////////////////////////////////////// Precisions
    UINT	m_nPrecision;  
    UINT	m_nPrecisionOld; 
    UINT	m_nPrecisionDefault; 
	/////////////////////////////////////////// World Base
	LONG	m_lWorldBase;    
	LONG	m_lWorldBaseOld;    
	LONG	m_lWorldBaseDefault;    

protected: 

public:
	virtual ~CPrecision(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CPrecision)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
