// XForm.cpp : implementation of the CXForm class
//

#include "stdafx.h"
#include <math.h>                  

#include "Def_Type.h"
#include "3DMath.h"
///////////////////
//#include "3d.h"
//#include "camera.h"
///////////////////
//#include "3Dextern.h"
//#include "3Ddefine.h"

#include "XForm.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CXForm

//IMPLEMENT_SERIAL(CXForm,CDrObject,1)
IMPLEMENT_SERIAL(CXForm,CObject,1)
/*
BEGIN_MESSAGE_MAP(CXForm,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CXForm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
////////////////////////////////
//static double pi = acos(0.)*2.;
//////////////////////////////////
 
CXForm::CXForm()
{
} 

CXForm::CXForm(BOOL bParallel)
{
	m_bParallel = bParallel;
} 

void CXForm::Reflect(pMATRIX pM,WORLD N,double p)
{
/*****************************************************************************
 *
 *	Function:	Reflect()
 *
 *	purpose:	generates a reflection MATRIX about a Plane
 *				Given a Point on the Plane and the Normal
 *				to the plane.
 *
 *
 *****************************************************************************
 */
	////////////////////////////////////////////////////////////
	//	PLANE: Ax+By+Cz+D=0  or r.N = p
	//
	//		Given:
	//			r = (x,y,z) = Radius Vector (Pt. on the Plane)
	//			N = (A,B,C) = Unit Normal
	//			p = -D		= Distance of the Plane from a
	//							parallel plane thro' Origin
	//		Find:
	//	Local Matrix:
	//	
	//			Ra'	= [I - 2*n*nTrans]Ra + (2*p)n
	//
	//
	//	LOCAL MATRIX: in Homogeneous Coords
	//
	//			1-2*(A**2)		 -2*A*B		 -2*A*C		|	2*p*A
	//			 -2*A*B  		1-2*(B**2)	 -2*B*C		|	2*p*B
	//			 -2*A*C  		 -2*B*C		1-2*(C**2)	|	2*p*C
	//			-------------------------------------------------
	//				0				0			0		|     1	
	//	
	////////////////////////////////////////////////////////////// 			 
	pM->v[0][0]	= 1.-2*N.x*N.x;
	pM->v[0][1]	=   -2*N.x*N.y;
	pM->v[0][2]	=   -2*N.x*N.z;
	pM->v[0][3]	=	 2*p*N.x;
	///////////////////////////
	pM->v[1][0]	=   -2*N.x*N.y;
	pM->v[1][1]	= 1.-2*N.y*N.y;
	pM->v[1][2]	=   -2*N.y*N.z;
	pM->v[1][3]	=	 2*p*N.y;
	///////////////////////////
	pM->v[2][0]	=   -2*N.x*N.z;
	pM->v[2][1]	=   -2*N.y*N.z;
	pM->v[2][2]	= 1.-2*N.z*N.z;
	pM->v[2][3]	=	 2*p*N.z;
    /////////////////////
	return;
}	


void CXForm::Scale(pMATRIX pM,double sx,double sy,double sz,
					XFMODE mode)
{
/*****************************************************************************
 *
 *	Function:	Scale()
 *
 *	purpose:	replaces or concatenates a scaling MATRIX to another MATRIX
 *				based on mode.
 *
 *
 *****************************************************************************
 */
	switch(mode)
	{
		case XF_REPLACE:		// pM = S
		{		
			if( sx !=1.0 )
				pM->v[0][0]	*= sx;
			if( sy !=1.0 )
				pM->v[1][1]	*= sy;
			if( sz !=1.0 )
				pM->v[2][2]	*= sz;
			return;
		}
		/////////////		
		case XF_POSTMULT:		// pM . S = Rot . S
		{		
			if( sx !=1.0 )
			{
				pM->v[0][0]	= pM->v[0][0] * sx;
				pM->v[1][0]	= pM->v[1][0] * sx;
				pM->v[2][0]	= pM->v[2][0] * sx;
			}
			if( sy !=1.0 )
			{
				pM->v[0][1]	= pM->v[0][1] * sy;
				pM->v[1][1]	= pM->v[1][1] * sy;
				pM->v[2][1]	= pM->v[2][1] * sy;
			}
			if( sz !=1.0 )
			{
				pM->v[0][2]	= pM->v[0][2] * sz;
				pM->v[1][2]	= pM->v[1][2] * sz;
				pM->v[2][2]	= pM->v[2][2] * sz;
			}
			return;
		}
		/////////////		
		case XF_PREMULT:		// S . pM = Scale.Rot + Scale.Tran
		{		
			if( sx !=1.0 )
			{
				pM->v[0][0]	= pM->v[0][0] * sx;
				pM->v[0][1]	= pM->v[0][1] * sx;
				pM->v[0][2]	= pM->v[0][2] * sx;
				pM->v[0][3]	= pM->v[0][3] * sx;
				///////////////////////////////
			}
			if( sy !=1.0 )
			{
				pM->v[1][0]	= pM->v[1][0] * sy;
				pM->v[1][1]	= pM->v[1][1] * sy;
				pM->v[1][2]	= pM->v[1][2] * sy;
				pM->v[1][3]	= pM->v[1][3] * sy;
			}
			if( sz !=1.0 )
			{
				pM->v[2][0]	= pM->v[2][0] * sz;
				pM->v[2][1]	= pM->v[2][1] * sz;
				pM->v[2][2]	= pM->v[2][2] * sz;
				pM->v[2][3]	= pM->v[2][3] * sz;
			}
			return;	
		}
	}	
    /////////////////////
	return;
}	

void CXForm::Shear_X(pMATRIX pM,double sy,double sz,XFMODE mode)
{
	return;
}
void CXForm::Shear_Y(pMATRIX pM,double sx,double sz,XFMODE mode)
{
	return;
}
void CXForm::Shear_Z(pMATRIX pM,double sx,double sy,XFMODE mode)
{
/*****************************************************************************
 *
 *	Function:	Shear_Z()
 *
 *	purpose:	Replaces or Concatenates a shearing MATRIX to another MATRIX
 *				based on mode.
 *
 *	methods:	a local MATRIX is constructed of the following form:
 *
 *						1	0	sx	0
 *						0	1	sy	0
 *						0	0	1	0
 *						0	0	0	1
 *
 *****************************************************************************
 */
	switch(mode)
	{
		case XF_REPLACE:		// pM = Sh
		{		
			pM->v[0][2]	= sx;
			pM->v[1][2]	= sy;
			return;
		}
		/////////////		
		case XF_POSTMULT:		// pM . Sh = Rot . Sh
		{		

			pM->v[0][2]	+= pM->v[0][0] * sx + pM->v[0][1] * sy;
			pM->v[1][2]	+= pM->v[1][0] * sx + pM->v[1][1] * sy;
			pM->v[2][2]	+= pM->v[2][0] * sx + pM->v[2][1] * sy;

			return;
		}
		/////////////		
		case XF_PREMULT:		// Sh . pM = Shear.Rot + Shear.Tran
		{		
			pM->v[0][0]	+= pM->v[2][0] * sx;
			pM->v[0][1]	+= pM->v[2][1] * sx;
			pM->v[0][2]	+= pM->v[2][2] * sx; 
				
			pM->v[1][0]	+= pM->v[2][0] * sy;
			pM->v[1][1]	+= pM->v[2][1] * sy;
			pM->v[1][2]	+= pM->v[2][2] * sy;
	        //////////////////////////////// Sh . T
			pM->v[0][3]	+= pM->v[2][3] * sx;
			pM->v[1][3]	+= pM->v[2][3] * sy;
				
			return;	
		}
	}	
	///////////////////////////
	return;

}	

void CXForm::Rotate_X(pMATRIX pM,double ang,XFMODE mode)
{
/*****************************************************************************
 *
 *	Function:	Rotate_X()
 *
 *	purpose:	Replaces or concatenates the axis rotation matrices to another MATRIX.
 *              based on mode.
 *	methods:	as follows:
 *
 *						1	0	0	0		pitch(X)
 *						0	cp -sp	0
 *						0	sp	cp	0
 *						0	0	0	1
 *
 *	warnings:	all angles are expected to be in degrees.  conversion to
 *				radians is done here.
 *****************************************************************************
 */
	/////////////////
	double	sn,cs,nsn;
	double	tv0,tv1,tv2,tv3;
	double	vRad;
	///////////////////////////
	double Pi180 = 3.14159265359/180.;
    ///////////////////////////
	if( ang ) 
	{		// pitch
		vRad		= ang * Pi180;
		cs			= cos(vRad);
		sn			= sin(vRad);
		nsn			= -sn;
		////////////
		switch(mode)
		{
			case XF_REPLACE:		// pM = R
			{		
				pM->v[1][1]	= cs;
				pM->v[1][2]	= nsn;
				pM->v[2][1]	= sn;
				pM->v[2][2]	= cs;
				return;
			}
			/////////////		
			case XF_POSTMULT:		// pM . S = Rot . S
			{		
				tv0			= pM->v[0][1] * cs  + pM->v[0][2] * sn;
				tv1			= pM->v[1][1] * cs  + pM->v[1][2] * sn;
				tv2			= pM->v[2][1] * cs  + pM->v[2][2] * sn;

				pM->v[0][2]	= pM->v[0][1] * nsn + pM->v[0][2] * cs;
				pM->v[1][2]	= pM->v[1][1] * nsn + pM->v[1][2] * cs;
				pM->v[2][2]	= pM->v[2][1] * nsn + pM->v[2][2] * cs;

				pM->v[0][1]	= tv0;
				pM->v[1][1]	= tv1;
				pM->v[2][1]	= tv2;
				return;
			}
			/////////////		
			case XF_PREMULT:		// S . pM = Scale.Rot + Scale.Tran
			{		
				tv0			= pM->v[1][0] * cs  + pM->v[2][0] * nsn;
				tv1			= pM->v[1][1] * cs  + pM->v[2][1] * nsn;
				tv2			= pM->v[1][2] * cs  + pM->v[2][2] * nsn;
				tv3			= pM->v[1][3] * cs  + pM->v[2][3] * nsn;
		
				pM->v[2][0]	= pM->v[1][0] * sn  + pM->v[2][0] * cs;
				pM->v[2][1]	= pM->v[1][1] * sn  + pM->v[2][1] * cs;
				pM->v[2][2]	= pM->v[1][2] * sn  + pM->v[2][2] * cs;
				pM->v[2][3]	= pM->v[1][3] * sn  + pM->v[2][3] * cs;
		
				pM->v[1][0]	= tv0;
				pM->v[1][1]	= tv1;
				pM->v[1][2]	= tv2;
				pM->v[1][3]	= tv3;
				return;	
			}
		}
	}	
	///////////////////////////
	return;
}	

void CXForm::Rotate_Y(pMATRIX pM,double ang,XFMODE mode)
{
/*****************************************************************************
 *
 *	Function:	Rotate_Y()
 *
 *	purpose:	Replaces or concatenates the axis rotation matrices to another MATRIX.
 *              based on mode.
 *
 *	methods:	as follows:
 *
 *						cy	0   sy	0		yaw(Y)
 *						0	1	0	0
 *					    -sy	0	cy	0
 *						0	0	0	1
 *
 *
 *	warnings:	all angles are expected to be in degrees.  conversion to
 *				radians is done here.
 *****************************************************************************
 */
	/////////////////
	double	sn,cs,nsn;
	double	tv0,tv1,tv2,tv3;
	double	vRad;
	///////////////////////////
	double Pi180 = 3.14159265359/180.;
    ///////////////////////////
	if( ang ) 
	{		// pitch
		vRad		= ang * Pi180;
		cs			= cos(vRad);
		sn			= sin(vRad);
		nsn			= -sn;
		////////////
		switch(mode)
		{
			case XF_REPLACE:		// pM = R
			{		
				pM->v[0][0]	= cs;
				pM->v[0][2]	= sn;
				pM->v[2][0]	= nsn;
				pM->v[2][2]	= cs;
				return;
			}
			/////////////		
			case XF_POSTMULT:		// pM . S = Rot . S
			{		
				tv0			= pM->v[0][0] * cs  + pM->v[0][2] * nsn;
				tv1			= pM->v[1][0] * cs  + pM->v[1][2] * nsn;
				tv2			= pM->v[2][0] * cs  + pM->v[2][2] * nsn;

				pM->v[0][2]	= pM->v[0][0] * sn  + pM->v[0][2] * cs;
				pM->v[1][2]	= pM->v[1][0] * sn  + pM->v[1][2] * cs;
				pM->v[2][2]	= pM->v[2][0] * sn  + pM->v[2][2] * cs;

				pM->v[0][0]	= tv0;
				pM->v[1][0]	= tv1;
				pM->v[2][0]	= tv2;
				return;
			}
			/////////////		
			case XF_PREMULT:		// S . pM = Scale.Rot + Scale.Tran
			{		
				tv0			= pM->v[0][0] * cs  + pM->v[2][0] * sn;
				tv1			= pM->v[0][1] * cs  + pM->v[2][1] * sn;
				tv2			= pM->v[0][2] * cs  + pM->v[2][2] * sn;
				tv3			= pM->v[0][3] * cs  + pM->v[2][3] * sn;
		
				pM->v[2][0]	= pM->v[0][0] * nsn + pM->v[2][0] * cs;
				pM->v[2][1]	= pM->v[0][1] * nsn + pM->v[2][1] * cs;
				pM->v[2][2]	= pM->v[0][2] * nsn + pM->v[2][2] * cs;
				pM->v[2][3]	= pM->v[0][3] * nsn + pM->v[2][3] * cs;
		
				pM->v[0][0]	= tv0;
				pM->v[0][1]	= tv1;
				pM->v[0][2]	= tv2;
				pM->v[0][3]	= tv3;
				return;	
			} 
		}	
	}	
	///////////////////////////
	return;
}	

void CXForm::Rotate_Z(pMATRIX pM,double ang,XFMODE mode)
{
/*****************************************************************************
 *
 *	Function:	Rotate_Z()
 *
 *	purpose:	Replaces or concatenates the axis rotation matrices to another MATRIX.
 *              based on mode.
 *
 *	methods:	as follows:
 *
 *						cr -sr	0	0		roll(Z)
 *						sr	cr	0	0
 *						0	0	1	0
 *						0	0	0	1
 *
 *	warnings:	all angles are expected to be in degrees.  conversion to
 *				radians is done here.
 *****************************************************************************
 */
	/////////////////
	double	sn,cs,nsn;
	double	tv0,tv1,tv2,tv3;
	double	vRad;
	///////////////////////////
	double Pi180 = 3.14159265359/180.;
    ///////////////////////////
	if( ang ) 
	{		// roll(Z)
		vRad		= ang * Pi180;
		cs			= cos(vRad);
		sn			= sin(vRad);
		nsn			= -sn;
		/////////////
		switch(mode)
		{
			case XF_REPLACE:		// pM = R
			{		
				pM->v[0][0]	= cs;
				pM->v[0][1]	= nsn;
				pM->v[1][0]	= sn;
				pM->v[1][1]	= cs;
				return;
			}
			/////////////		
			case XF_POSTMULT:		// pM . S = Rot . S
			{		
				tv0			= pM->v[0][0] * cs  + pM->v[0][1] * sn;
				tv1			= pM->v[1][0] * cs  + pM->v[1][1] * sn;
				tv2			= pM->v[2][0] * cs  + pM->v[2][1] * sn;

				pM->v[0][2]	= pM->v[0][0] * nsn + pM->v[0][1] * cs;
				pM->v[1][2]	= pM->v[1][0] * nsn + pM->v[1][1] * cs;
				pM->v[2][2]	= pM->v[2][0] * nsn + pM->v[2][1] * cs;

				pM->v[0][1]	= tv0;
				pM->v[1][1]	= tv1;
				pM->v[2][1]	= tv2;
				return;
			}
			/////////////		
			case XF_PREMULT:		// S . pM = Scale.Rot + Scale.Tran
			{		
				tv0			= pM->v[0][0] * cs  + pM->v[1][0] * nsn;
				tv1			= pM->v[0][1] * cs  + pM->v[1][1] * nsn;
				tv2			= pM->v[0][2] * cs  + pM->v[1][2] * nsn;
				tv3			= pM->v[0][3] * cs  + pM->v[1][3] * nsn;
		
				pM->v[1][0]	= pM->v[0][0] * sn  + pM->v[1][0] * cs;
				pM->v[1][1]	= pM->v[0][1] * sn  + pM->v[1][1] * cs;
				pM->v[1][2]	= pM->v[0][2] * sn  + pM->v[1][2] * cs;
				pM->v[1][3]	= pM->v[0][3] * sn  + pM->v[1][3] * cs;
		
				pM->v[0][0]	= tv0;
				pM->v[0][1]	= tv1;
				pM->v[0][2]	= tv2;
				pM->v[0][3]	= tv3;
				return;	
			}
		}	
	}	
	///////////////////////////
	return;
}	

void CXForm::Translate(pMATRIX pM,double dx,double dy,double dz,
						XFMODE mode)
{
/*****************************************************************************
 *
 *	Function:	Translate()
 *
 *	purpose:	Replaces or inserts a translation factor into a MATRIX;
 *              based on mode.
 *
 *	methods:	the MATRIX is modified to the following form:
 *
 *						1	0	0	dx
 *						0	1	0	dy
 *						0	0	1	dz
 *						0	0	0	1
 *
 *****************************************************************************
 */
 	int i,j;
 	double sum,d[3];
 	////////////
	switch(mode)
	{
		case XF_REPLACE:		// pM = T
		{		
			pM->v[0][3] = dx;
			pM->v[1][3] = dy;
			pM->v[2][3] = dz;
			return;
		}
		/////////////		
		case XF_POSTMULT:		// pM . Tnew = Rot.Tnew + Told . 
		{
 			d[0] = dx;
 			d[1] = dy;
 			d[2] = dz;
 			////////////
			for (i=0;i<=2;i++)
			{
				sum = 0.0;
				for (j=0;j<=2;j++)
					sum += pM->v[i][j]*d[j];
				/////////////////////////			
				pM->v[i][3] += sum;
			}
			return;
		}
		/////////////		
		case XF_PREMULT:		// Tnew . pM = Tnew + Told
		{		
			pM->v[0][3] += dx;
			pM->v[1][3] += dy;
			pM->v[2][3] += dz;
			return;	
		}
	}	
    /////////////////////
	return;

}	

void CXForm::VRCtoWORLDRotationMATRIX(pMATRIX pM,pWORLD pNewZ,
										   pWORLD pUp	)
{                                                 
	////////////////////////////////////////////// Set Rotation MATRIX
	double	Rx[4],Ry[4],Rz[4];
	int sign,i,j,k,tmp;
	double r,a[4],cross;
	/////////////////////////////// Rz = NewZ/||NewZ||
	r = 1./sqrt(pNewZ->x*pNewZ->x + 
				pNewZ->y*pNewZ->y +
				pNewZ->z*pNewZ->z );
	Rz[1] = pNewZ->x * r;
	Rz[2] = pNewZ->y * r;
	Rz[3] = pNewZ->z * r;
	/////////////////////////////// Rx = UP x Rz/||VUP x Rz||
	a[1] = pUp->x;
	a[2] = pUp->y;
	a[3] = pUp->z;
	
	for (i=1;i<=3;i++)
	{
		j = (i+1>3)?1:i+1;
		k = (j+1>3)?1:j+1;
		cross = 0.;
		///////////
		for(sign = 1;sign>=-1;sign -=2)
		{
			cross += sign*a[j]*Rz[k];
			tmp = k;
			k	= j;
			j	= tmp;
		}
		Rx[i] = cross;
	}
	
	///////////////////// unit 
	r = 1./sqrt(Rx[1]*Rx[1] +Rx[2]*Rx[2] +Rx[3]*Rx[3]);
	Rx[1] *= r;
	Rx[2] *= r;
	Rx[3] *= r;
	/////////////////////////////// Ry = Rz x Rx/||Rz x Rx||
	for (i=1;i<=3;i++)
	{
		j = (i+1>3)?1:i+1;
		k = (j+1>3)?1:j+1;
		cross = 0.;
		///////////
		for(sign = 1;sign>=-1;sign -=2)
		{
			cross += sign*Rz[j]*Rx[k];
			tmp = k;
			k	= j;
			j	= tmp;
		}
		Ry[i] = cross;
	}
	///////////////////// unit 
	r = 1./sqrt(Ry[1]*Ry[1] +Ry[2]*Ry[2] +Ry[3]*Ry[3]);
	Ry[1] *= r;
	Ry[2] *= r;
	Ry[3] *= r;
    ////////////////////////////////// Row0:x/Row1:y/Row2:z
    pM->v[0][0] = Rx[1];
    pM->v[0][1] = Rx[2];
    pM->v[0][2] = Rx[3];
    
    pM->v[1][0] = Ry[1];
    pM->v[1][1] = Ry[2];
    pM->v[1][2] = Ry[3];
    
    pM->v[2][0] = Rz[1];
    pM->v[2][1] = Rz[2];
    pM->v[2][2] = Rz[3];
    ////////////////////
    
}

void CXForm::ComposeLocalMATRIX(pMATRIX pMLocal,
							double rx, double ry, double rz,
							double sx,double sy,double sz, 
							double shx,double shy,double shz, 
							double tx,double ty,double tz)
/*****************************************************************************
 *
 *	Function:	ComposeLocalMATRIX()
 *
 *	purpose:	constructs the Local transformation MATRIX from supplied
 *				parameters (rotations,scaling,shear and translations).
 *
 *	methods:	MATRIX multiplications are used to concatenate the
 *				parameters into supplied instance transform MATRIX.
 *
 *
 *	warnings:	the space coordinate system is a right handed
 *				coordinate system.  its axes are shown in the diagram
 *				below.
 *
 *									y
 *									+	
 *									|  /
 *									| /
 *									|/
 *							  ------------ +x
 *								   /|
 *								  /	|
 *								 +	|
 *                              z
 *****************************************************************************
 */
{
	/////////////////
	C3DMath	Math3D;
	C3DMath* p3DMath = &Math3D;
	p3DMath->GetIdentityMATRIX(pMLocal);
	//////
	Scale( 	pMLocal, sx, sy, sz, XF_REPLACE );
	Shear_X(pMLocal, shy, shz, XF_PREMULT );
	Shear_Y(pMLocal, shx, shz, XF_PREMULT );
	Shear_Z(pMLocal, shx, shy, XF_PREMULT );
	Rotate_Y(pMLocal, ry, XF_PREMULT );
	Rotate_X(pMLocal, rx, XF_PREMULT );
	Rotate_Z(pMLocal, rz, XF_PREMULT );
	Translate(pMLocal, tx, ty, tz, XF_PREMULT );
	///////////////////////////
	return;
}	

double CXForm::ComposeViewMATRIX(pMATRIX pNPar,
				WORLD VRP,WORLD VPN,WORLD VUP,
				WORLD CW, WORLD PRP,
				double Front,double Back,
				double width_U,double width_V)
{
//////////////////////////////////////////////////////////
//	N O T E: This does NOT premultiply by M matrix		//
//		where M = PerspectiveTo Parallel CVV matrix		//
//				(eqn. (6.48): pg 275/ Foley				//
//////////////////////////////////////////////////////////
//	1.	If THIS is used, CLIP in 3D which are Different	//
//			for Perspective & Parallel CVV, THEN 		//
//			Use TransformPerToParCVV() 					//
//			BEFORE Z-Buffering							//	
//	2.	To Clip in Homogeneous Coordinates, use			//
//			Alt_ComposeViewMATRIX(), CLIP and then		//		
//			DIVIDE	by W to get to 3D					//								//
//////////////////////////////////////////////////////////
//	Return:                                             //
//		For Perspective:	                            //
//			 zMin(Front Clipping Plane in NPC)   		//
//			 needed for 3DClipping later          		//
//			                                     		//
//		For Parallel:		                            //
//			zMin = 0;
	//////////////////////////////////////////////
	// 			 Canonical View MATRIX			//
	//////////////////////////////////////////////
	C3DMath	Math3D;
	C3DMath* p3DMath = &Math3D;
	p3DMath->GetIdentityMATRIX(pNPar);
	/////////////////////////////////// View Orientation MATRIX
	SetVOMATRIX(pNPar,VRP,VPN,VUP);
	/////////////////////////////////// Perspective or Parallel
	if(m_bParallel)
	{
		/////////////////////////////// View Mapping MATRIX
		Par_SetVMMATRIX(pNPar,CW,PRP,Front,Back,
								width_U,width_V);
		return 0.;
	}									
	else
        return // zMin
		/////////////////////////////// View Mapping MATRIX
		Per_SetVMMATRIX(pNPar,CW,PRP,Front,Back,
								width_U,width_V);
	////////////////
	return -1.;

}											
void CXForm::PerToParCVVMATRIX(pMATRIX pM,double dzMin)
{
	// Foley: p 275 eqn(6.48)
	//////////////////////////
	double r = 1./(1. + dzMin);
	//////////////////////////
    pM->v[2][2] = r;
    pM->v[2][3] = -dzMin * r;

    pM->v[3][2] = -1.;
    pM->v[3][3] = 0;
    //////////////////////////
}    

int CXForm::ALT_ComposeViewMATRIX(pMATRIX pNPar,
				WORLD VRP,WORLD VPN,WORLD VUP,
				WORLD CW, WORLD PRP,
				double Front,double Back,
				double width_U,double width_V)
{
//////////////////////////////////////////////////////////
//	N O T E: This DOES premultiply by M matrix			//
//		where M = PerspectiveTo Parallel CVV matrix		//
//				(eqn. (6.48): pg 275/ Foley				//
//////////////////////////////////////////////////////////
//	1.	To Clip in Homogeneous Coordinates, USE THIS to	//
//			TRANSFORM, then CLIP and then DIVIDE by W 	//
//			to get to 3D for Z-Buffering				//								//
//	2.	To Clip in 3D which are Different for			//
//			Perspective & Parallel CVV, TRANSFORM by 	//
//			ComposeViewMATRIX(), CLIP and THEN			//		
//			USE TransformPerToParCVV()					// 
//			BEFORE Z-Buffering							//	
//////////////////////////////////////////////////////////
//	Return:                                             //
//		For Perspective:	                            //
//			 zMin(Front Clipping Plane in NPC)   		//
//			 needed for 3DClipping later          		//
//			                                     		//
//		For Parallel:		                            //
//			zMin = 0;
	//////////////////////////////////////////////
	// 			 Canonical View MATRIX			//
	//////////////////////////////////////////////
	double dzMin = ComposeViewMATRIX(pNPar,VRP,VPN,VUP,
									CW,PRP,Front,Back,
									width_U,width_V);
	/////////////////////////////////// Perspective or Parallel
	if(m_bParallel)
	{
		return (int)dzMin;
	}									
	else
	{
		C3DMath	Math3D;
		C3DMath* p3DMath = &Math3D;
		MATRIX PerToParM;
		p3DMath->GetIdentityMATRIX(&PerToParM);
		/////////////////////////////// View Mapping MATRIX
		PerToParCVVMATRIX(&PerToParM,dzMin);
		Math3D.MultMATRIX(&PerToParM,pNPar,pNPar);
		////////////////
		return 0;
	}	

}											

void CXForm::SetVOMATRIX(pMATRIX pVOM,WORLD VRP,WORLD VPN,
						     				WORLD VUP)
{
	////////////////////////////////////////////// Set Rotation MATRIX
	VRCtoWORLDRotationMATRIX(pVOM,&VPN,&VUP);
	////////////////////////////////////////////// Translate VRP to Origin
	Translate(pVOM,-VRP.x,-VRP.y,-VRP.z,XF_POSTMULT);
    ////////////////////
}
	
void CXForm::Par_SetVMMATRIX(pMATRIX pVMM,
				WORLD CW, WORLD PRP,
				double Front, double Back,
				double width_U, double width_V	)
{
	WORLD DOP;
	//////////////////////////////////////// direction of Proj.
	DOP.x 		= CW.x - PRP.x;
	DOP.y 		= CW.y - PRP.y;
	DOP.z 		= CW.z - PRP.z;
	//////////////////////////////////////// Shear
	double shx 	= - DOP.x/DOP.z;	
	double shy 	= - DOP.y/DOP.z; 
	//////////////////////////////////////// Matrix
	C3DMath Math3D;
	C3DMath* p3DMath= &Math3D;
	MATRIX VM;
	pMATRIX pVM = &VM;
	p3DMath->GetIdentityMATRIX(pVM);
	//////////////////////////////////////// Scale
	Scale(&VM,2./width_U,2./width_V,1./(Front - Back),XF_REPLACE);
	//////////////////////////////////////// Translate + Shear Compose
	VM.v[0][2] += VM.v[0][0] * shx;
	VM.v[0][3] -= VM.v[0][0] * CW.x;
	VM.v[1][2] += VM.v[1][1] * shy;
	VM.v[1][3] -= VM.v[1][1] * CW.y;
	VM.v[2][3] -= VM.v[2][2] * Front;
	//////////////////////////////////////// PREMULTIPLY
	p3DMath->MultMATRIX(&VM,pVMM,pVMM);
	///////////////////////////////////
/*	
	///////////////////////////////
	Shear_Z(pVMM, shx, shy, PREMULT );
	//////////////////////////////////////// Translate
	Translate(pVMM, -CW.x, -CW.y, -Front, PREMULT);	
	//////////////////////////////////////// Scale
	Scale(pVMM,2./width_U,2./width_V,1./(Front - Back),PREMULT);
	///////////
*/
	return;	

}
		
double CXForm::Per_SetVMMATRIX(pMATRIX pVMM,
				WORLD CW, WORLD PRP,
				double Front, double Back,
				double width_U, double width_V	)
//////////////////////////////////////////////////////////				
//	Return:												//
//			 zMin(Front Clipping Plane in NPC)   		//
//			 needed for 3DClipping later          		//
//			                                     		//
//	NOTE:	 zMax(Back Clipping Plane should be = -1.   //
//			 zProj(Projection Plane in NPC)				//
//////////////////////////////////////////////////////////				
{
	WORLD DOP;
	//////////////////////////////////////// Translate COP
	Translate(pVMM, -PRP.x, -PRP.y, -PRP.z, XF_PREMULT);	
	//////////////////////////////////////// direction of Proj.
	DOP.x = CW.x - PRP.x;
	DOP.y = CW.y - PRP.y;
	DOP.z = CW.z - PRP.z;
	//////////////////////////////////////// Shear
	double shx = - DOP.x/DOP.z;	
	double shy = - DOP.y/DOP.z;
	///////////////////////////////
	Shear_Z(pVMM, shx, shy, XF_PREMULT );
	//////////////////////////////////////// Translate
//	Translate(pVMM, -CW.x, -CW.y, -Front, PREMULT);	
	//////////////////////////////////////// Scale
	double VRPz 	= -PRP.z;
	double rVRPzB 	= 1./(VRPz + Back);
	double Numer	= 2.* VRPz * rVRPzB;
	double sx		= Numer/width_U; 
	double sy		= Numer/width_V;
	///////// 
	Scale(pVMM, sx, sy, -rVRPzB, XF_PREMULT );
	/////////////////////////////////////// zMin
	double zProj,zMin;
	///////////////////////
	zProj	= - VRPz * rVRPzB;
	///////////////////////////////////////// 
	return (zMin = -(VRPz + Front) * rVRPzB );	

}

void CXForm::ComposeCombineMATRIX(
				pMATRIX pLM,pMATRIX pVM,pMATRIX pCM)
{
	//////////////////
	C3DMath	Math3D;
	C3DMath* p3DMath = &Math3D;
	/////////////////////////////////////// 
	p3DMath->GetIdentityMATRIX(pCM);
	p3DMath->F_MultMATRIX( pVM, pLM, pCM );
	///////////////////////////////////////
	return;
}	
/*
void CXForm::Transform(long* lSrc, long* lDes, pMATRIX pM, int nPrecision)
{

	double x,y,z,dWorldBase;
	dWorldBase = 1.0/pow(10.,(double)nPrecision);
	x = ( ((double)lSrc[0]) * dWorldBase);         // divide by 10**nPrecision
	y = ( ((double)lSrc[1]) * dWorldBase);         // divide by 10**nPrecision
	z = ( ((double)lSrc[2]) * dWorldBase);         // divide by 10**nPrecision 
	/////////////////
	WORLD src,dest;
	src.x			= x;       
	src.y			= y;       
	src.z			= z;
	////////////////////////////// 
	Transform(&src,&dest,pM);
	//////////////////////////////
	dWorldBase = 1.0/dWorldBase;
	////////////////////////////
	lDes[0] = ((long)(Fix2Int(dest.x)))*((long)dWorldBase);
	lDes[1] = ((long)(Fix2Int(dest.y)))*((long)dWorldBase);
	lDes[2] = ((long)(Fix2Int(dest.z)))*((long)dWorldBase);
	//////////////////////////////////////////////////////
	return;

}                            
*/

void CXForm::Transform(pWORLD pt1, pWORLD pt2, pMATRIX pM)
{

/*****************************************************************************
 *
 *	Function:	Transform()
 *
 *	purpose:	applies a transformation MATRIX to "wSrc", with the
 *				result returned at the address supplied for "wDes".
 *
 *	methods:	the source point is copied into a VECTOR form, then it
 *				and the transformation MATRIX are multiplied, as follows:
 *
 *					|x'| =	|a b c j||x|
 *					|y'|	|d e f k||y|
 *					|z'|	|g h i l||z|
 *					|1 |	|0 0 0 1||1|
 *
 *				or	x'=xa+yb+zc+j
 *					y'=xd+ye+zf+k
 *					z'=xg+yh+zi+l
 *****************************************************************************
 */
	double aX,aY,aZ;

	aX	= pt1->x;
	aY	= pt1->y;
	aZ	= pt1->z;
	
	pt2->x	= aX * pM->v[0][0]
			+ aY * pM->v[0][1]
			+ aZ * pM->v[0][2]
			+      pM->v[0][3];
	pt2->y	= aX * pM->v[1][0]
			+ aY * pM->v[1][1]
			+ aZ * pM->v[1][2]
			+      pM->v[1][3];
	pt2->z	= aX * pM->v[2][0]
			+ aY * pM->v[2][1]
			+ aZ * pM->v[2][2]
			+      pM->v[2][3];
	///////////
	return;			
			
}

void CXForm::TransformPerToParCVV(double dzMin, pWORLD pPer, pWORLD pPar)
{
/*****************************************************************************
 *
 *	Function:	TransformPerToParCVV()
 *
 *	purpose:	applies M (Foley: p 275) MATRIX to "pPer", with the
 *				result returned at the address supplied for "pPar".
 *
 *	methods:	the source point is copied into a VECTOR form, then it
 *				and the transformation MATRIX are multiplied, as follows:
 *
 *					|X| =	|1  0  0  0||x|
 *					|Y|		|0  1  0  0||y|
 *					|Z|		|0  0  i  j||z|
 *					|W|		|0  0  -1 0||1|
 *				where
 *					i = 1/(1+zMin)
 *					j = -zMin/(1+zMin)
 *				so
 *					x'= X/W = -x/z
 *					y'= Y/W = -y/z
 *					z'= Z/W = -i - j/z
 *					
 *
 *****************************************************************************
 */
	//////////////////////////
	double i 	= 1./(1. + dzMin);
	double j 	= -dzMin * i;
	double rz	= 1./pPer->z;
	//////////////////////////
	pPar->x = -pPer->x * rz;
	pPar->y = -pPer->y * rz;
	pPar->z = -i - j * rz;
    //////////////////////////
    return;
}    
 
void CXForm::ComposeWin3DtoScreen3DMATRIX(pMATRIX pM,
					WORLD Vmin, WORLD Vmax)
{
	////////////////////////////////////////
	//Mvv3Dv in eqn.(6.54)/ pg. 278: FOLEY//
	////////////////////////////////////////
	C3DMath	Math3D;
	C3DMath* p3DMath = &Math3D;
	p3DMath->GetIdentityMATRIX(pM);
	//////////////////////////////////////// Translate 
	Translate(pM, 1., 1.,1., XF_REPLACE);	
	//////////////////////////////////////// Scale
	Scale(pM,	.5*(Vmax.x - Vmin.x),
				.5*(Vmax.y - Vmin.y),
				   (Vmax.z - Vmin.z),XF_PREMULT );
	//////////////////////////////////////// Translate 
	Translate(pM, Vmin.x, Vmin.y, Vmin.z, XF_PREMULT);	
	///////////
	return;	

}
		
void CXForm::Project(pMATRIX pMvv3D,pWORLD ptIn, pWORLD ptOut)
{
/*****************************************************************************
 *
 *	Function:	Project()
 *
 *	methods:	1. Extend 3D to Homo ( step 5/pg279 FOLEY)
 *   			2. Operate on Mort or Mper ( step 6)
 *					1. & 2. together boil down to:
 *					For Parallel:|x y 0 1|
 *					For Perspect:|x y z z|
 *				3. Operate on Mvv3dv (eqn. 6.54/pg 278)
 *				4. Divide by (W=z) for Perspective (step 8)
 *					3. & 4. together CHANGED as follows:
 * For Perspective:
 * 		since our Transform routine always assumes w = 1, i.e.,,
 * 			X' = Rot. X + Tran. (w=1),
 * we first divide x and y components by W = z in |x y z z| of
 * perspective case i.e. transform  |x/z y/z 1 1|, because
 * each 3D coordinates can be represented by proportionate W
 *
 *	NOTE:
 *	      Mvv3D should have following structure:
 *
 *			|M00=Sx			0		0	|	M03=T0'	|
 *			|	0		M11=Sy		0	|	M13=T1' |
 *			|	0			0	M22=Sz	|	M23=T2'	|
 *			|---------------------------|-----------|
 *			|	0			0		0	|		1	|			
 *
 *****************************************************************************
 */
	///////////////////////////////////////////////////////////
	BOOL bParallel = TRUE; 	// for all time because perspective
							// will be transformed to parallel
							// before projection
	///////////////////////////////////////////////////////////							
	if (bParallel)
	{
        ptOut->x = pMvv3D->v[0][0]*ptIn->x + pMvv3D->v[0][3];
        ptOut->y = pMvv3D->v[1][1]*ptIn->y + pMvv3D->v[1][3];
        ptOut->z =                       	 pMvv3D->v[2][3];
		////////////////////////////
		return;
	}	
	else
	{
        ptOut->x = pMvv3D->v[0][0]*(ptIn->x/ptIn->z) + pMvv3D->v[0][3];	
        ptOut->y = pMvv3D->v[1][1]*(ptIn->y/ptIn->z) + pMvv3D->v[1][3];
        ptOut->z = pMvv3D->v[2][2]                   + pMvv3D->v[2][3];
		////////////////////////////
		return;
	}	
	////////
	return;

}                            

void CXForm::HeadToNewZLocMATRIX(pWORLD pFrom, pWORLD pTo, pMATRIX pM,XFMODE mode)
{
	C3DMath Math3D;
	////////////////////////////////////////////// Get NewZ Direction
	WORLD NewZ;
	pWORLD pNewZ = &NewZ;
	//////////////////////
	Math3D.Sub3DPts(pTo,pFrom,pNewZ);
    ///////////////////////////////////////////////// Create New Matrix
	MATRIX Mat;
	pMATRIX pMat = &Mat;  
	Math3D.GetIdentityMATRIX(pMat);
	///////////////////////////// Rotate to NewZ
	RotateToNewZMATRIX(pNewZ, pMat,XF_REPLACE);
	///////////////////////////// Translate to From
	Translate(pMat,pFrom->x,pFrom->y,pFrom->z,XF_PREMULT);
    ///////////////////////////////////////////////// Update according to mode
	int i,j;
	////////
	switch(mode)
	{
		case XF_REPLACE:

			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					pM->v[i][j] = pMat->v[i][j];
			break;


		case XF_PREMULT:	// New One is PreMultiplied
			Math3D.MultMATRIX(pMat,pM,pM);
			break;


		case XF_POSTMULT:	// New One is PostMultiplied
			Math3D.MultMATRIX(pM,pMat,pM);
			break;

	}
	///////		
    return;   
}

void CXForm::RotateToNewZMATRIX(pWORLD pNewZ, pMATRIX pM,XFMODE mode)
{
	C3DMath Math3D;
	///////////////
	MATRIX Mat;
	pMATRIX pMat = &Mat;  
	Math3D.GetIdentityMATRIX(pMat);
	////////////////////////////////////////////// Set Rotation MATRIX
	WORLD	y,Rx,Ry,Rz;
	double	r;
	/////////////////////////////// Rz = NewZ/||NewZ||
	r = 1./sqrt(pNewZ->x*pNewZ->x + 
				pNewZ->y*pNewZ->y +
				pNewZ->z*pNewZ->z );
	Rz.x = pNewZ->x * r;
	Rz.y = pNewZ->y * r;
	Rz.z = pNewZ->z * r;
	/////////////////////////////// Check if NewZ is y-Axis
	r = sqrt(pNewZ->x*pNewZ->x + pNewZ->z*pNewZ->z );
	if(r)	// NewZ is NOT  y or -y direction
	{
		/////////////////////////////// Rx = y x Rz/||y x Rz||
		y.x = 0;
		y.y = 1;
		y.z = 0;
		////////////
		Math3D.Cross3DPts(&y,&Rz,&Rx);
		Math3D.Normalize(&Rx,&Rx);
		/////////////////////////////// Ry = Rz x Rx/||Rz x Rx||
		Math3D.Cross3DPts(&Rz,&Rx,&Ry);
		Math3D.Normalize(&Ry,&Ry);
	   ///////////////////////////////
	}
	else	// NewZ is  y or -y direction
	{
		Rx.x = 1.;
		Rx.y = 0.;
		Rx.z = 0.;
    
		Ry.x = 0.;
		Ry.y = 0.;
		if(pNewZ->y<0)		//	-y dir
			Ry.z = Rz.y;
		else				//	+y dir
			Ry.z = -Rz.y;
	}
	//////////////////////// Col0:x/Col1:y/Col2:z
    pMat->v[0][0] = Rx.x;
    pMat->v[1][0] = Rx.y;
    pMat->v[2][0] = Rx.z;
    
    pMat->v[0][1] = Ry.x;
    pMat->v[1][1] = Ry.y;
    pMat->v[2][1] = Ry.z;
    
    pMat->v[0][2] = Rz.x;
    pMat->v[1][2] = Rz.y;
    pMat->v[2][2] = Rz.z;
    ///////////////////////////////////////////////// Update according to mode
	int i,j;
	////////
	switch(mode)
	{
		case XF_REPLACE:

			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					pM->v[i][j] = pMat->v[i][j];
			break;


		case XF_PREMULT:	// New One is PreMultiplied
			Math3D.MultMATRIX(pMat,pM,pM);
			break;


		case XF_POSTMULT:	// New One is PostMultiplied
			Math3D.MultMATRIX(pM,pMat,pM);
			break;

	}
	///////		
    return;   


}

void CXForm::HeadToNewYLocMATRIX(pWORLD pFrom, pWORLD pTo, pMATRIX pM,XFMODE mode)
{
	C3DMath Math3D;
	////////////////////////////////////////////// Get NewY Direction
	WORLD NewY;
	pWORLD pNewY = &NewY;
	//////////////////////
	Math3D.Sub3DPts(pTo,pFrom,pNewY);
    ///////////////////////////////////////////////// Create New Matrix
	MATRIX Mat;
	pMATRIX pMat = &Mat;  
	Math3D.GetIdentityMATRIX(pMat);
	///////////////////////////// Rotate to NewZ
	RotateToNewYMATRIX(pNewY, pMat,XF_REPLACE);
	///////////////////////////// Translate to From
	Translate(pMat,pFrom->x,pFrom->y,pFrom->z,XF_PREMULT);
    ///////////////////////////////////////////////// Update according to mode
	int i,j;
	////////
	switch(mode)
	{
		case XF_REPLACE:

			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					pM->v[i][j] = pMat->v[i][j];
			break;


		case XF_PREMULT:	// New One is PreMultiplied
			Math3D.MultMATRIX(pMat,pM,pM);
			break;


		case XF_POSTMULT:	// New One is PostMultiplied
			Math3D.MultMATRIX(pM,pMat,pM);
			break;

	}
	///////		
    return;   
}

void CXForm::RotateToNewYMATRIX(pWORLD pNewY, pMATRIX pM,XFMODE mode)
{
	C3DMath Math3D;
	///////////////
	MATRIX Mat;
	pMATRIX pMat = &Mat;  
	Math3D.GetIdentityMATRIX(pMat);
	////////////////////////////////////////////// Set Rotation MATRIX
	WORLD	z,Rx,Ry,Rz;
	double	r;
	/////////////////////////////// Ry = NewY/||NewY||
	Math3D.Normalize(pNewY,pNewY);
	//////////////////////////
	r = 1./sqrt(pNewY->x*pNewY->x + 
				pNewY->y*pNewY->y +
				pNewY->z*pNewY->z );
	Ry.x = pNewY->x * r;
	Ry.y = pNewY->y * r;
	Ry.z = pNewY->z * r;
	/////////////////////////////// Check if NewY is y-Axis 
	r = sqrt(Ry.x*Ry.x + Ry.z*Ry.z );
	if(r)	// NewY is NOT  y or -y direction
	{
		/////////////////////////////// Rx = Ry x z/||Ry x z||
		z.x = 0;
		z.y = -1;
		z.z = 0;
		////////////
		Math3D.Cross3DPts(&Ry,&z,&Rx);
		Math3D.Normalize(&Rx,&Rx);
		/////////////////////////////// Rz = Rx x Ry/||Rx x Ry||
		Math3D.Cross3DPts(&Rx,&Ry,&Rz);
		Math3D.Normalize(&Rz,&Rz);
	   ///////////////////////////////
	}
	else	// NewY is  y or -y direction
	{
		Rx.x = 1.;
		Rx.y = 0.;
		Rx.z = 0.;
    
		Rz.x = 0.;
		Rz.y = 0.;
		if(pNewY->y<0)		//	-y dir
			Rz.z = -1.;
		else				//	+y dir
			Rz.z = 1.;
	}
	//////////////////////// Col0:x/Col1:y/Col2:z
    pMat->v[0][0] = Rx.x;
    pMat->v[1][0] = Rx.y;
    pMat->v[2][0] = Rx.z;
    
    pMat->v[0][1] = Ry.x;
    pMat->v[1][1] = Ry.y;
    pMat->v[2][1] = Ry.z;
    
    pMat->v[0][2] = Rz.x;
    pMat->v[1][2] = Rz.y;
    pMat->v[2][2] = Rz.z;
    ///////////////////////////////////////////////// Update according to mode
	int i,j;
	////////
	switch(mode)
	{
		case XF_REPLACE:

			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					pM->v[i][j] = pMat->v[i][j];
			break;


		case XF_PREMULT:	// New One is PreMultiplied
			Math3D.MultMATRIX(pMat,pM,pM);
			break;


		case XF_POSTMULT:	// New One is PostMultiplied
			Math3D.MultMATRIX(pM,pMat,pM);
			break;

	}
	///////		
    return;   


}

void CXForm::HeadToNewXLocMATRIX(pWORLD pFrom, pWORLD pTo, pMATRIX pM,XFMODE mode)
{
	C3DMath Math3D;
	////////////////////////////////////////////// Get NewX Direction
	WORLD NewX;
	pWORLD pNewX = &NewX;
	//////////////////////
	Math3D.Sub3DPts(pTo,pFrom,pNewX);
    ///////////////////////////////////////////////// Create New Matrix
	MATRIX Mat;
	pMATRIX pMat = &Mat;  
	Math3D.GetIdentityMATRIX(pMat);
	///////////////////////////// Rotate to NewX
	RotateToNewXMATRIX(pNewX, pMat,XF_REPLACE);
	///////////////////////////// Translate to From
	Translate(pMat,pFrom->x,pFrom->y,pFrom->z,XF_PREMULT);
    ///////////////////////////////////////////////// Update according to mode
	int i,j;
	////////
	switch(mode)
	{
		case XF_REPLACE:

			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					pM->v[i][j] = pMat->v[i][j];
			break;


		case XF_PREMULT:	// New One is PreMultiplied
			Math3D.MultMATRIX(pMat,pM,pM);
			break;


		case XF_POSTMULT:	// New One is PostMultiplied
			Math3D.MultMATRIX(pM,pMat,pM);
			break;

	}
	///////		
    return;   
}

void CXForm::RotateToNewXMATRIX(pWORLD pNewX, pMATRIX pM,XFMODE mode)
{
	C3DMath Math3D;
	///////////////
	MATRIX Mat;
	pMATRIX pMat = &Mat;  
	Math3D.GetIdentityMATRIX(pMat);
	////////////////////////////////////////////// Set Rotation MATRIX
	WORLD	y,Rx,Ry,Rz;
	double	r;
	/////////////////////////////// Rx = NewX/||NewX||
	r = 1./sqrt(pNewX->x*pNewX->x + 
				pNewX->y*pNewX->y +
				pNewX->z*pNewX->z );
	Rx.x = pNewX->x * r;
	Rx.y = pNewX->y * r;
	Rx.z = pNewX->z * r;
	/////////////////////////////// Check if NewX is y-Axis
	r = sqrt(pNewX->x*pNewX->x + pNewX->z*pNewX->z );
	if(r)	// NewX is NOT  y or -y direction
	{
		
		/////////////////////////////// Rz = Rx x y/||Rx x y||
		//								Rz = Rx x (-y)/||Rx x (-y)||,if NewX.x<0, to Keep
		//																z dir +ve
		y.x = 0;
		y.y = (pNewX->x>0.)?1:-1;
		y.z = 0;
		////////////
		Math3D.Cross3DPts(&Rx,&y,&Rz);
		Math3D.Normalize(&Rz,&Rz);
		/////////////////////////////// Ry = Rz x Rx/||Rz x Rx||
		Math3D.Cross3DPts(&Rz,&Rx,&Ry);
		Math3D.Normalize(&Ry,&Ry);
	   ///////////////////////////////
	}
	else	// NewX is  y or -y direction
	{
		Rz.x = 0.;
		Rz.y = 0.;
		Rz.z = 1.;
    
		Ry.y = 0.;
		Ry.z = 0.;
		Ry.x = (pNewX->y<0)?Rx.y:-Rx.y;
		//////////////////////////////
/*
		if(pNewX->y<0)		//	-y dir
			Ry.x = Rx.y;
		else				//	+y dir
			Ry.x = -Rx.y;
*/
	}
	//////////////////////// Col0:x/Col1:y/Col2:z
    pMat->v[0][0] = Rx.x;
    pMat->v[1][0] = Rx.y;
    pMat->v[2][0] = Rx.z;
    
    pMat->v[0][1] = Ry.x;
    pMat->v[1][1] = Ry.y;
    pMat->v[2][1] = Ry.z;
    
    pMat->v[0][2] = Rz.x;
    pMat->v[1][2] = Rz.y;
    pMat->v[2][2] = Rz.z;
    ///////////////////////////////////////////////// Update according to mode
	int i,j;
	////////
	switch(mode)
	{
		case XF_REPLACE:

			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					pM->v[i][j] = pMat->v[i][j];
			break;


		case XF_PREMULT:	// New One is PreMultiplied
			Math3D.MultMATRIX(pMat,pM,pM);
			break;


		case XF_POSTMULT:	// New One is PostMultiplied
			Math3D.MultMATRIX(pM,pMat,pM);
			break;

	}
	///////		
    return;   

}

void CXForm::RotateAboutLineMATRIX(pMATRIX pM, pWORLD p0,pWORLD p1,double dAng,XFMODE mode)
{

	C3DMath Math3D;
	///////////////
	MATRIX Mat;
	pMATRIX pMat = &Mat;  
	Math3D.GetIdentityMATRIX(pMat);
	//////////////////////////////////////////////////////
	// NOTE:                                    		//
	// 			Eqn(5.79)/pg 227:Foley					// 
	//////////////////////////////////////////////////////
	double cs = cos(dAng); 
	double sn = sin(dAng);
	double cs1= 1. - cs; 
	//////////////////////
	double ux,uy,uz,r;
	//////////////////////
	ux 	= p1->x - p0->x; 
	uy 	= p1->y - p0->y; 
	uz 	= p1->z - p0->z;
	r	= 1./sqrt(ux*ux + uy*uy + uz*uz);
	//////// units
	ux *= r;  	
	uy *= r;  	
	uz *= r;
	/////////////////////////
	double ux2,uy2,uz2,uxuy,uyuz,uzux;
	ux2		= ux*ux;  	
	uy2		= uy*uy;  	
	uz2		= uz*uz;  	
	uxuy	= ux*uy;  	
	uyuz	= uy*uz;  	
	uzux	= uz*ux;  	
    ////////////////////////////////////////////// fill in
    pMat->v[0][0] = ux2			+ cs * (1. - ux2); 
    pMat->v[0][1] = uxuy * cs1	- uz * sn; 
    pMat->v[0][2] = uzux * cs1	+ uy * sn;
     
    pMat->v[1][0] = uxuy * cs1	+ uz * sn; 
    pMat->v[1][1] = uy2			+ cs * (1. - uy2); 
    pMat->v[1][2] = uyuz * cs1	- ux * sn;

    pMat->v[2][0] = uzux * cs1	- uy * sn; 
    pMat->v[2][1] = uyuz * cs1	+ ux * sn;
    pMat->v[2][2] = uz2			+ cs * (1. - uz2);
    ///////////////////////////////////////////////// Update according to mode
	int i,j;
	////////
	switch(mode)
	{
		case XF_REPLACE:

			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					pM->v[i][j] = pMat->v[i][j];
			break;


		case XF_PREMULT:	// New One is PreMultiplied
			Math3D.MultMATRIX(pMat,pM,pM);
			break;


		case XF_POSTMULT:	// New One is PostMultiplied
			Math3D.MultMATRIX(pM,pMat,pM);
			break;

	}
	///////		
    return; 

}

void CXForm::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	/////////////////////////
//	WORD w;
	/////// 
	if (ar.IsStoring())
	{
		TRACE(" XForm:    Storing\n");	// TODO: add storing code here
	}
	else
	{
		TRACE(" XForm:    Loading\n");	// TODO: add loading code here
	}
		
}
////////////////////////////////// end of module //////////////////
