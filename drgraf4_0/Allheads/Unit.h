// CUnit.h : header file
//
#ifndef _UNITOBJECT
#define _UNITOBJECT

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h" 
/////////////////////////////////////////////////////////////////////////////
// CUnit
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CUnit : public CDrObject
{
// Construction
public:  
	CUnit();

	DECLARE_SERIAL(CUnit)


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
	///////////////////////////////////////////////////// Unit 
	virtual CString GetUnitName(UINT nNameIndex){return m_UnitNames[nNameIndex];};				  
    virtual UINT 	GetUnitIndex(){return m_nUnitIndex;};
    virtual void 	SetUnitIndex(UINT nindex){m_nUnitIndex = nindex;};
    virtual UINT 	GetUnitIndexOld(){return m_nUnitIndexOld;};
    virtual void 	SetUnitIndexOld(UINT nindex){m_nUnitIndexOld = nindex;};
    virtual UINT 	GetUnitIndexDefault(){return m_nUnitIndexDefault;};
    virtual void 	SetUnitIndexDefault(UINT nindex){m_nUnitIndexDefault = nindex;};
    virtual UINT 	GetUnitNameCount(){return m_nUnitNameCount;};
    virtual void 	SetUnitNameCount(UINT nUnitNameCount){m_nUnitNameCount=nUnitNameCount;};
	////////////////////////
	virtual	void 		ReadDefaultUnit();
	virtual	void 		InitUnit();


	
protected:

	int			m_nElemType;	
	int			m_nObjectType;
	long		m_nObjectNo;
	/////////////////////////////////////////// Units
	CString m_UnitNames[15]; 
	UINT	m_nUnitNameCount;   
    UINT	m_nUnitIndex;
    UINT	m_nUnitIndexOld;
    UINT	m_nUnitIndexDefault; 
protected: 

public:
	virtual ~CUnit(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CUnit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
