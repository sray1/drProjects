// CZBuffer.h : header file
//
#ifndef _ZBUFFER_H_
#define _ZBUFFER_H_

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CZBuffer
/////////////////////////////////////////////////////////////////////////////
class CZBuffer : public CObject
{
// Construction
public:  
	CZBuffer();
	DECLARE_SERIAL(CZBuffer)
protected: 
public:
// Implementation
public:

	virtual int 	InitZB
						(
						short	left,	//	X minimum value
						short	top,	//	Y minimum value
						short	right,	//	X maximum value
						short	bottom	//	Y maximum value
						);
	virtual void 	TermZB();
/* //16
	virtual double __huge*
				 	GetZdepthBasePointer(){return m_pZdepth;};
	virtual double __huge*
				 	GetZdepthBasePointer(){return m_pZdepth;};
	virtual double __huge* 
					GetZdepthPointer(long x, long y);
*/
	virtual pDOUBLE	GetZdepthBasePointer(){return m_pZdepth;};
	virtual pDOUBLE	GetZdepthPointer(long x, long y);
	////////////////////////////////////////////////////////////
	virtual double 	GetZdepth
						(
						short	x,		//	point's horizontal coordinate
						short	y		//	point's vertical coordinate
						);
	virtual BOOL 	PutZdepth
						(
						short	x,		//	point's horizontal coordinate
						short	y,		//	point's vertical coordinate
						double	v,		//	point's Z depth value
						double	hither,	//	Front Plane
						double	yon		//	Back  Plane
						);

	virtual void 	UnSetZdepth
						(
						short	x,		//	point's horizontal coordinate
						short	y		//	point's vertical coordinate
						);

	virtual long	GetxMn(){return m_xMn;};
	virtual long	GetxMx(){return m_xMx;};
	virtual long	GetyMn(){return m_yMn;};
	virtual long	GetyMx(){return m_yMx;};
	virtual long	GetxRng(){return m_xRng;};
	virtual long	GetyRng(){return m_yRng;};

						
protected:

	/////////////////////////////////////////////////// Memory
/* //16	
	double __huge* 	FixMem(long nOut)
					{
						double __huge* pOut;
					return ((pOut = new double[nOut]) == NULL)? (double __huge*)NULL:pOut;
			};
	
	void 			FreeMem(double __huge* pOut){delete[] pOut;};
*/
	pDOUBLE 		FixMem(long nOut)
					{
						pDOUBLE pOut;
						return ((pOut = new double[nOut]) == NULL)? (pDOUBLE)NULL:pOut;
					};
	
	void 			FreeMem(pDOUBLE pOut){delete[] pOut;};
	/////////////////////////////////////////////////////////

protected:

	double 			m_priorZV;
	///////////////////////////////////////////////////////////
	pDOUBLE			m_pZdepth;		//	Z depth values
	long			m_xMn,
					m_xMx,
					m_yMn, 
					m_yMx;			//	bounds of the Z buffer
	long			m_xRng,
					m_yRng;			//	bounds spans
	CRect			m_ActiveRect;	//	active area of buffer
    /////////////////////

protected: 

public:
	virtual ~CZBuffer(){};
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CZBuffer)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
