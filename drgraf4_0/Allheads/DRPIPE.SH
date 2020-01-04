// Pipe.h : header file
//
#ifndef _DRPIPE_H
#define _DRPIPE_H       

#include "DrObject.h" 
#include "DrNode.h" 
#include "crextern.h"           // card structures
//////////////////////////////
#define	MAX_NODES_PIPE		2
#define MAX_PIPE_DRAW_PT	2
#define MAX_PIPE_DRAW_PT2	4
/////////////////////////////////////////////////////////////////////////////
// CDrPipe    ///////////////////////////////////////////////////////////////
class CDrPipe: public CDrObject
{
public:
// Construction                 
	CDrPipe();
	DECLARE_SERIAL(CDrPipe);
	
	
// Operations
public:

	//////////////////////////////////////////////// Card/Data
	virtual void		Pack_drPipe(CString* pstrCard);
	virtual PIPECARD*	Parse_drPipe(CString* pstrCard)
						{return (PIPECARD*)NULL;};                    //  TOBE DONE
	virtual PIPECARD*	GetPipeCard(){return &m_PipeCard;};
	virtual int			GetCardNo(){return m_nCardNo;};
	virtual void		SetCardNo(int nCardNo){m_nCardNo = nCardNo;}; 
	////////////////////////////////////////////////
	// overrides of virtuals in CDrObject;
	virtual int 		GetLevelType(){return m_nLevelType;};
	virtual void		SetLevelType(int nType){ m_nLevelType = nType;};
	virtual void		DoDataView(CDC* PtrDC, int y);
	virtual void 		DoDrawView(CDC* PtrDC,BOOL bPenChange);
	virtual CString		GetObjectID(){return m_ObjectID;}; 
	virtual void		SetObjectID(CString strID){ m_ObjectID = strID;}; 
	virtual long 		GetObjectNo(){return m_nObjectNo;}; 
	virtual void		SetObjectNo(long nNo){ m_nObjectNo = nNo;};
	virtual int 		GetObjectType(){return m_nObjectType;};
	virtual void		SetObjectType(int nType){ m_nObjectType = nType;};
	virtual int 		GetElemType(){return m_nElemType;};
	virtual void		SetElemType(int nType){ m_nElemType = nType;};
	virtual void		SetObjectInfo(CDrObject* pObject);
	virtual void 		GetObjectInfo(CDrObject* pObject);
	virtual int 		DealObjectDialog();
	////////////////////////////////////////// for projection
	virtual int			GetMaxCorners(){return (int)MAX_NODES_PIPE;};
/*
	virtual	void 		GetRawCoords(long* lCoord, int* pnPrecision, int index);
	virtual void		SetProjectedCoords(POINT pt, int index)
						{ 
							m_pt[index] = pt;
						};
*/						
	//////////////////////////////////////////////////////////////
	virtual	void 		TransformObjectToWorld(pMATRIX pLM,BOOL bYes);
	virtual	void 		TransformObjectToView(pMATRIX pViewM);
	virtual	BOOL 		RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType);
	virtual	void 		ProjectObject
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
	virtual	void 		FinishObject();
	virtual CRect	 	GetBoundingRect() { return m_rectBounding; };

	virtual BOOL 		IsObjectHit(CDrObject* pObject,CClientDC* ptrDC,int nNet,
									POINT point,RECT* pRect);
	virtual BOOL 		IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo);

	virtual void		Serialize(CArchive& ar);	
	////////////////////////////////////////////////
	virtual void        GetPenInfo(UINT nWidth,COLORREF crColor,UINT nStyle)
						{	nWidth  =	m_nPenWidth;
					 	 	crColor =	m_crPenColor;
					  		nStyle  =	m_nPenStyle;
				  		};	
	virtual void        SetPenInfo(UINT nWidth,COLORREF crColor,UINT nStyle)
						{	m_nPenWidth  = nWidth;
					 		m_crPenColor = crColor;
					 		m_nPenStyle  = nStyle;
						};
	virtual UINT		GetLayer(){return m_nLayer;};
	virtual void		SetLayer(UINT nLayer){m_nLayer = nLayer;};
	///////////////////////////////////////////////////////////////
	virtual CDListMgr*	GetNodeList(){return &m_NodeList;};
    ////////////////////////////////////////////////////////////////////// helper
	virtual	POINT 		GetCenter(){return m_nCenter;};
	virtual	void		SetCenter(POINT ptCenter){m_nCenter = ptCenter;};
	/////////////////////////////////////////////////////////////////
	virtual BOOL		IsGenerated(){return m_bGenerated;};
	virtual void		SetGenerated(BOOL bGen){m_bGenerated = bGen;};
	/////////////////////////////////////////////////////////////
	virtual int			GetLevel(){return m_nLevel;};
	virtual void		SetLevel(int nLevel){m_nLevel = nLevel;};
	 
protected:
	
			void 		TransformToWorldPos(pMATRIX pLM,BOOL bYes);
			void 		TransformToEyePos(pMATRIX pViewM);
			void 		ProjectToScreenPos
							(pMATRIX pvv3DM,double dScale_U,double dScale_V);
			void 		Calc_ScreenRectFromCNodes();
			void 		GoDoIt(CDC* PtrDC,BOOL bPenChange);
			
			
// Helper functions
protected:
// Attributes
 
	int			m_nLevelType;
	int			m_nObjectType;
	int			m_nElemType;	
	long		m_nObjectNo;
    /////////////////////////////////
	CString		m_ObjectID;
	/////////////////////////////////
	///////////////////////////////// Render
	CDListMgr	m_NodeList;
	//////////////////////////////
	CRect       m_rectBounding; // smallest rect that surrounds 
								// Pipe Ends measured in MM_LOENGLISH units
								// (0.01 inches, with Y-axis inverted)
    //////////////////////////////
	UINT        m_nPenWidth;    // pen width for Pipe
	COLORREF	m_crPenColor;
	UINT		m_nPenStyle;
	/////////////////////////////////
	PIPECARD	m_PipeCard;
	int			m_nCardNo;
	////////////////////////////// 
	UINT		m_nLayer;
	POINT 		m_nCenter; 
	/////////////////////////////////// 
	BOOL		m_bGenerated;			// generated by Curve or Patch
	///////////////////////////////////
	int			m_nLevel;				// Hierarchy Level

public:
	virtual ~CDrPipe(){};
public:
/*
	// Generated message map functions
	//{{AFX_MSG(CDrPipe)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
/////////////////////////////////////////////
#endif                                       



