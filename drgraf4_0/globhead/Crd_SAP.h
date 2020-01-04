#ifndef _SAP_INFO_H
#define _SAP_INFO_H
///////////////////////////////////////////////////////////// GLOBALS
enum SAP_EL_NUMBER
	{
		NONE,
		TRUSS=1,
		BEAM=2,
		PL_STRESS=3,
		PL_STRAIN=4,	// AxiSym, Pl.Strain(thk=1), Pl.Stress(thk=t)
		BRICK_8=5,	// 8-Node Brick
		QUADPLATE=6,	// Quadrilateral Plate & Shell
		BOUNDARY=7,
		FE_3D=8,
		PIPE=12

	};
/////////////////////////////////////////////////////////////////////////////
#endif 

