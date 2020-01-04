#ifndef _DEF_TOLER_H
#define _DEF_TOLER_H 

///////////////////////////////////////////// Tolerances
#define NET_DOUBLE			.1			
#define NET_PIXEL			10			
#define TOL_DOUBLE_RATIO	.001		// .1%		
#define TOL_COLINEAR		.99		// within 1% (Dot product) should be 1.0,if Colinear		
#define TOL_COPLANAR		.01		// 1% (distance of 4th point from plane)
										// should be 0,if Coplanar
#define TOL_MERGENODE_X		.01
#define TOL_MERGENODE_Y		.01
#define TOL_MERGENODE_Z		.01
/////////////////////////////////
#endif
