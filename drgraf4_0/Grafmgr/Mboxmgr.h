// eboxMgr.h : header file
//
#ifndef _MBOXMGR_H
#define _MBOXMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////////////////////////////
// CMBoxMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMBoxMgr : public CObject
{
// Construction
public:  
	CMBoxMgr();

	DECLARE_SERIAL(CMBoxMgr)


protected: 
public:
// Implementation 

public:

	////////////////////////////////////////////////////////////// 
	virtual BOOL	IsElemBoxActive(){return m_bElemBox;};
	virtual void	SetElemBoxStatus(BOOL bStatus){m_bElemBox = bStatus;};
	virtual int		GetActiveObjectType(){return m_nObjectType;};
	virtual void	SetActiveObjectType(int nObjectType){m_nObjectType = nObjectType;};
	virtual int		GetActiveToolType(){return m_nToolType;};
	virtual void	SetActiveToolType(int nToolType){m_nToolType = nToolType;};
	//////////////////////////////////////////////////////////////
	
protected:

	///////////////////////////////////////// ElemBox
    BOOL		m_bElemBox;
    int			m_nObjectType;
	int			m_nToolType;
	////////////////////////

public:
	virtual ~CMBoxMgr(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
};


#undef AFX_DATA
#define AFX_DATA
////////////////////////////////////////////////////////
#endif
