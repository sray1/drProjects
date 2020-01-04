#ifndef	_MATOBJ_H_
#define	_MATOBJ_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "3DMath.h"
#include "Def_Type.h"
#include "Def_CuPS.h"	//041397
#include "Def_IGen.h" // 	XFORMTYPE moved to IGen.h from CuPS.h
/////////////////////////////////////////////////////////////////////////////
// CMatObj
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMatObj : public CObject
{
// Construction
public:  
	CMatObj();
//////////////////////////////////////
	DECLARE_DYNAMIC(CMatObj)
//////////////////////////////////////
public:

	virtual pMATRIX	GetMatrix(){return &m_LM;};
	virtual void 	SetMatrix(pMATRIX pM)
					{
						C3DMath Math3D;
						Math3D.BlockCopy((HUGEBLK)pM, (HUGEBLK)&m_LM, (HUGESIZE)sizeof(MATRIX) );
					}
	///////////////////////////////////////////////////
	virtual CURVELATCH	GetCurveLatch(){return m_CuLatch;};
	virtual void	SetCurveLatch(CURVELATCH id){m_CuLatch = id;};
	virtual BOOL	IsInstanced_Prof(){return m_bInstanced;};
	virtual void	SetInstanced_Prof(BOOL bi){m_bInstanced = bi;};
	//////////////////////////////////////////////////////////
	virtual CString	GetFromID(){return m_FromID;};
	virtual void 	SetFromID(CString st){m_FromID = st;};
	virtual WORLD	GetFromPt(){return m_wFrom;};
	virtual void 	SetFromPt(WORLD st){m_wFrom = st;};
	virtual CString	GetToID(){return m_ToID;};
	virtual void 	SetToID(CString st){m_ToID = st;};
	virtual WORLD	GetToPt(){return m_wTo;};
	virtual void 	SetToPt(WORLD st){m_wTo = st;};
	////////////////////////////////////////////////////////// Grab Node or Coord
	virtual CString	GetRotPtID(){return m_RotPtID;};
	virtual void 	SetRotPtID(CString st){m_RotPtID = st;};
	virtual WORLD	GetRotPt(){return m_wRotPt;};
	virtual void 	SetRotPt(WORLD st){m_wRotPt = st;};
	////////////////////////////////////////////////////////// Translation
	virtual BOOL	IsCoordIn(){return m_bCoordIn;};
	virtual void	SetCoordIn(BOOL bi){m_bCoordIn = bi;};
	virtual CString	GetTranPtID(){return m_TranPtID;};		// Translate To
	virtual void 	SetTranPtID(CString st){m_TranPtID = st;};
	virtual WORLD	GetTranslation(){return m_Translation;};
	virtual void 	SetTranslation(WORLD st){m_Translation = st;};
	////////////////////////////////////////////////////////// Rotation
	virtual BOOL	IsAngleIn(){return m_bAngleIn;};
	virtual void	SetAngleIn(BOOL bi){m_bAngleIn = bi;};
	virtual BOOL	IsDirCos(){return m_bDirCos;};
	virtual void	SetDirCos(BOOL bi){m_bDirCos = bi;};
	virtual WORLD	GetDirCosDirect(){return m_wDir;};
	virtual void 	SetDirCosDirect(WORLD st){m_wDir = st;};
	virtual WORLD	GetRotation(){return m_Rotation;};
	virtual void 	SetRotation(WORLD st){m_Rotation = st;};
	////////////////////////////////////////////////////////// Scale
	virtual WORLD	GetScale(){return m_Scale;};
	virtual void 	SetScale(WORLD st){m_Scale = st;};
	////////////////////////////////////////////////////////// Shear
	virtual WORLD	GetShear(){return m_Shear;};
	virtual void 	SetShear(WORLD st){m_Shear = st;};
	//////////////////////////////////////////////////////////
	virtual BOOL	IsNoRot(){return m_bNoRot;};
	virtual void	SetNoRot(BOOL bi){m_bNoRot = bi;};
	virtual BOOL	IsNoTran(){return m_bNoTran;};
	virtual void	SetNoTran(BOOL bi){m_bNoTran = bi;};
	virtual BOOL	IsNoScale(){return m_bNoScale;};
	virtual void	SetNoScale(BOOL bi){m_bNoScale = bi;};
	virtual BOOL	IsNoShear(){return m_bNoShear;};
	virtual void	SetNoShear(BOOL bi){m_bNoShear = bi;};
	////////////////////////////////////////////////////////// XFormType
	virtual XFORMTYPE	GetXformType(){return m_XfType;};
	virtual void	SetXformType(XFORMTYPE id){m_XfType = id;};
	virtual SPAWNTYPE	GetSpawnType(){return m_SpnType;};
	virtual void	SetSpawnType(SPAWNTYPE id){m_SpnType = id;};
	virtual UINT	GetCreOp(){return m_CreOp;};	
	virtual void	SetCreOp(UINT id){m_CreOp = id;};

	

protected:

	/////////////////////// These needed for editing later so save in MatObj
	CURVELATCH	m_CuLatch;
	BOOL		m_bInstanced;	// Needed for Profiling (Different from that in DrCurve)
	MATRIX		m_LM;			// Identity Matrix if m_bInstanced = FALSE
	CString		m_FromID;		// Rot Axis
	WORLD		m_wFrom;
	CString		m_ToID;
	WORLD		m_wTo;
	CString		m_TranPtID;		// Only for the Ist Curve (Profiling)
	////////////////////////////////////////////////////////// Brab Node or Coord
	CString		m_RotPtID;		// Center of Xformation
	WORLD		m_wRotPt;		// if No Node  but coords only
	///////////////////////////
	BOOL		m_bCoordIn;
	WORLD		m_Translation;
	///////////////////////////
	BOOL		m_bAngleIn;
	BOOL		m_bDirCos;
	WORLD		m_wDir;
	WORLD		m_Rotation;
	///////////////////////////
	WORLD		m_Scale;
	WORLD		m_Shear;
	///////////////////////////
	BOOL		m_bNoRot;
	BOOL		m_bNoScale;
	BOOL		m_bNoShear;
	BOOL		m_bNoTran;
	///////////////////////////
	XFORMTYPE	m_XfType;		// Direct, Symm etc
	SPAWNTYPE	m_SpnType;		// Symm_N,Symm_3 etc
	UINT		m_CreOp;	// Translate,Rotate etc
	
public:
	virtual ~CMatObj(){};
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _MATOBJ_H_
