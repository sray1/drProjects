/*****************************************************************************
 *
 *	File:		ZBuffer.cpp
 *
 *	Purpose:	Implements a depth buffer for hidden surface removal uses.
 *
 *****************************************************************************
 */
#include "stdafx.h"

#include "ZBuffer.h"
/////////////////////////////////////////////////////////////////////////////
// CZBuffer

IMPLEMENT_SERIAL(CZBuffer,CObject,1)
/*
BEGIN_MESSAGE_MAP(CZBuffer,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CZBuffer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
CZBuffer::CZBuffer()
{
} 

////////////////////////////////
/**********************************************************************************
 *
 *	Function:	InitZB
 *
 *	Purpose:	Initializes a Z buffer.  Storage for the ZBuffer record is assumed
 *				to be supplied by the caller.  The left, top, right and bottom
 *				parameters define the coordinate space within which the Z depths
 *				will be recorded.  Points outside these limits will be considered
 *				to be excluded from the image.  The Z depth array is initialized
 *				to -1.0( Back Clipping Plane).
 *
 **********************************************************************************
 */
int CZBuffer::InitZB
	(
		short		left,	//	X minimum value
		short		top,	//	Y minimum value
		short		right,	//	X maximum value
		short		bottom	//	Y maximum value
	)
{
	pDOUBLE			pb;
	pDOUBLE			pl;
	long			n;
	double			v = -1.0;		// back clipping plane	
    ////////////////////////////
	m_priorZV 	= v;
	m_xMn 		= left;
	m_xMx 		= right;
	m_yMn 		= top;
	m_yMx 		= bottom;
	m_xRng 		= right - left + 1;
	m_yRng 		= bottom - top + 1;
	n 			= m_xRng * m_yRng;
    //////////////////////////// alloc memory
	m_pZdepth = NULL;
    if(!(m_pZdepth = FixMem(n)) )
    	return -1;
    //////////////////
	m_ActiveRect.SetRect(left, top, right, bottom );
	pb = m_pZdepth;
	pl = m_pZdepth + n;
	while( pl-- > pb )
		*pl = v;
	////////////
	return 0;	
}

/**********************************************************************************
 *
 *	Function:	TermZB
 *
 *	Purpose:	Releases the memory area occupied by a ZBuffers depth array.
 *
 **********************************************************************************
 */
void CZBuffer::TermZB()
{
	if( m_pZdepth ) 
	{
		FreeMem( m_pZdepth );
		m_pZdepth = NULL;
	}
}

pDOUBLE CZBuffer::GetZdepthPointer(long x, long y)
{
	if(		(x >= m_xMn) && (x <= m_xMx)
		&&	(y >= m_yMn) && (y <= m_yMx) ) 
		return m_pZdepth + (y - m_yMn) * m_xRng + (x - m_xMn);
	else
		return NULL;
}			
/**********************************************************************************
 *
 *	Function:	GetZdepth
 *
 *	Purpose:	Determines the Z depth corresponding to a point in the Z buffer.
 *
 *	Returns:	-2. if the specified point lies outside of the ZBuffer bounds;
 *				Z depth at the specified point otherwise.
 *
 **********************************************************************************
 */
double CZBuffer::GetZdepth
	(
		short		x,		//	point's horizontal coordinate
		short		y		//	point's vertical coordinate
	)
{

	if	(	(x < (short)m_xMn)
		||	(x > (short)m_xMx)
		||	(y < (short)m_yMn)
		||	(y > (short)m_yMx)
		)
		return -2.0; // Beyond Yon
	return *(m_pZdepth + ( (y - m_yMn)*m_xRng + (x - m_xMn) ) );
}


/**********************************************************************************
 *
 *	Function:	PutZdepth
 *
 *	Purpose:	Attempts to record a ZBuffer's depth array the Z depth of a point.
 *				A comparison is made to determine of the Z depth supplied is less
 *				than or equal to the Z depth currently recorded at the point's
 *				coordinates.  If so, the new Z depth is stored.  Points which lie
 *				outside of ZBuffer's bounds box are clipped (not recorded).  The Z
 *
 *	Returns:	true if a new Z depth is recorded; false otherwise.
 *
 **********************************************************************************
 */
BOOL CZBuffer::PutZdepth
	(
		short		x,		//	point's horizontal coordinate
		short		y,		//	point's vertical coordinate
		double		v,		//	point's Z depth value
		double		hither,	//	Front Plane
		double		yon		//	Back  Plane
	)
{
	register
		pDOUBLE	pB;

	if	(	(x < (short)m_xMn)
		||	(x > (short)m_xMx)
		||	(y < (short)m_yMn)
		||	(y > (short)m_yMx)
		||	(v > hither)		//Recall Canonical View Volume
		||	(v < yon )			// z:[0,-1]
		)
		return FALSE;
        /////////////
	pB = m_pZdepth + ((y-m_yMn)*m_xRng+(x-m_xMn));
	if(v<*pB)			// behind the current depth
		return FALSE;
	/////////////////	// replace		
	m_priorZV = *pB;
	*pB=v;
	///////////
	return TRUE;
}

/**********************************************************************************
 *
 *	Function:	UnSetZdepth
 *
 *	Purpose:	Undoes the action of SetZB
 *
 **********************************************************************************
 */
void CZBuffer::UnSetZdepth
	(
		short		x,		//	point's horizontal coordinate
		short		y		//	point's vertical coordinate
	)
{

	if	(	(x < (short)m_xMn)
		||	(x > (short)m_xMx)
		||	(y < (short)m_yMn)
		||	(y > (short)m_yMx)
		)
		return;

	*(m_pZdepth + ((y-m_yMn)*m_xRng+(x-m_xMn))) = m_priorZV;
	m_priorZV	= -1.0;
}

void CZBuffer::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
//	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" ZBuffer:    Storing\n");	// TODO: add storing code here
	}
	else
	{
		TRACE(" ZBuffer:    Loading\n");	// TODO: add loading code here
	}
		
}
///////////////////////////// end of module ////////////////


