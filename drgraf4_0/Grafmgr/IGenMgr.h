// eboxMgr.h : header file
//
#ifndef _IGENMGR_H
#define _IGENMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////////////////////////////
// CIGenMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CIGenMgr : public CObject
{
// Construction
public:  
	CIGenMgr();

	DECLARE_SERIAL(CIGenMgr)


protected: 
public:
// Implementation 

public:

	////////////////////////////////////////////////////////////// 
	virtual BOOL	IsIGenBoxActive(){return m_bIGenBox;};
	virtual void	SetIGenBoxStatus(BOOL bStatus){m_bIGenBox = bStatus;};
	virtual int		GetActiveObjectType(){return m_nObjectType;};
	virtual void	SetActiveObjectType(int nObjectType){m_nObjectType = nObjectType;};
	virtual int		GetActiveToolType(){return m_nToolType;};
	virtual void	SetActiveToolType(int nToolType){m_nToolType = nToolType;};
	//////////////////////////////////////////////////////////////
	
protected:

	///////////////////////////////////////// IGenBox
    BOOL		m_bIGenBox;
    int			m_nObjectType;
	int			m_nToolType;
	////////////////////////

public:
	virtual ~CIGenMgr(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
};


#undef AFX_DATA
#define AFX_DATA
////////////////////////////////////////////////////////
#endif
