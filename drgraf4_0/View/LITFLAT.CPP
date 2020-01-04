typedef struct scanseg {
	short		x[2];
	double		z[2];
}
	SCANSEG, __far *pSCANSEG;

//////////////////////////////////////////////////////////////////
// 	Following Routines are used for LitFlat Z-Buffer Rendering	//
//			SCANSEG structure is much more simplified          //
//////////////////////////////////////////////////////////////////
int CLitFlat::RenderPolygon_LF(DrObject* pPoly, COLORREF c)
{
	register short	y,i = nS;
    pWORLD			pp = P;
	pSCANSEG		pss;
	CPen			PenCur;
	CPen*			pPenCur = &pPenCur;
	CPen*			pPenOld;
    //////////////////////////
	if( !pPoly )
		return 0;
    ////////////////////////////////////////////////////// Z-Buffer Clip
	if(ClippedByZBuffer(pPoly)
		return 0;
	/////////////////////////////////////////////////////// Build EdgeList.
	BuildEdgeList(pPoly);
    //////////////////////////
	pPenCur->CreatePen( PS_SOLID, 1, c );
	pPenOld = pDC->SelectObject( *pPenCur );
	////////////////////////////////// Draw the scan lines
	b_Interrupted = RenderScanLines(pDC);
	//////////////////////////////////
    pDC->SelectObject( *pPenOld );
    DeleteObject( *pPenCur );
    //////////
    return 0;
    
}
void CLitFlat::RenderSpan_LF
				(
					CClientDC* pDC,
					short y,
					pSCANSEG pss
				)
{
	register short 	x,xMx;
	short			Ix1,Ix2,xs,xe,ox;
	double			z,dz;
	long _huge	*pB;
	BOOL			spanopen = FALSE;
    ////////////////////////////////////////////////////
	Ix1 = pss->x[0];
	Ix2 = pss->x[1];
	if( Ix1 == Ix2 )
		return;
	if( Ix1 > m_pZB->GetxMx() || Ix2 < m_pZB->GetxMn() )	// out of window
															// bounds 
		return;
    ////////////////////////////////////////////// Increments 
    // Later change into Integer Arithmatic( p 144:WATT)       todo
    /////////////////////////////////////////////////////
	z	= pss->z[0];
	x	= Max( Ix1, (short)m_pZB->GetxMn() );// forcing -x to zero here
	dz	= ( pss->z[1] - z )/(Ix2-Ix1);
	ox = x - Ix1;
	if( ox )
		z	+= dz*ox;
	xMx	= Min( Ix2, (short)m_pZB->GetxMx() );
	//////////////////////////////////
	while( x < xMx ) 
	{
		/////////////////////////////////////////////////// Update Z-Buffer
		if( m_pZB->PutZdepthValue(x,y,z,m_dHither,m_dYon) ) 
		{
			xe = x;
			if( !spanopen ) 
			{
				spanopen = TRUE;
				xs = x;
			}
		}
		else
		if( spanopen ) {
			spanopen = FALSE;
			if( xe==xs ) 
			{
				LightUpPixel(pDC, xs, y, C);
			}
			else 
			{
				LightUpScanSpan(pDC, xs, ++xe, y);
			}
		}
		x++;
		pB++;
		z += dz;
	}
	if( spanopen ) {
		spanopen = FALSE;
		if( xe==xs ) 
		{
			LightUpPixel(pDC, xs, y, C);
		}
		else 
		{
			LightUpScanSpan(pDC, xs, ++xe, y);
		}
	}
}
/////////////////////////////// end of module /////////////////

