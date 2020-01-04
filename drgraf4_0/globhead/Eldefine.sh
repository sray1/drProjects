#ifndef _ELDEFINE_H
#define _ELDEFINE_H 

#define	NONE				-1
////////////////////////////////////////// Last Number already assigned
#define LAST_NUMBER			1122
////////////////////////////////////////// Objects
#define NODE				1001        // that can use EDIT & MOVE
#define CNODE				1036        // that can use EDIT & MOVE
//////////////////////////////// 
#define	TRUSS 				1008		// TRUSS Library
/////////////////////////////////////////////////////////////////// Beam Library
#define	BEAM				1004
/////////////////////////////////////////////////////////////////// Pipe Library
#define PIPE				1002 
#define	ELBOW				1003
/////////////////////////////////////////////////////////////////// SUPPORT Library
#define SUPPORT				1005		
#define	LIN_SUPPORT			1006
#define NON_SUPPORT			1007
/////////////////////////////////////////////////////////////////// 2D FEMs Library
#define	PLATE				1105		// PLATE Library 
////////////////////////////////////////////////////////
#define	TRIANGLE			1010		// Triangle Library
#define	TR_3				1107		// Triangle 3 Nodes
#define	TR_6				1108		// Triangle 6 Nodes
#define	TR_9				1109		// Triangle 9 Nodes
#define	TR_10				1110		// Triangle 10 Nodes
////////////////////////////////////////////////////////
#define	QUAD 				1009		// Quad Library
#define	QU_4				1111		// Quad 4 Nodes
#define	QU_8				1112		// Quad 8 Nodes
#define	QU_9				1113		// Quad 9 Nodes
#define	QU_12				1114		// Quad 12 Nodes
#define	QU_16				1115		// Quad 16 Nodes
///////////////////////////////////////////////////////////////////
//#define	PLANE 				1009		// PLANE Library (Membrane)
///////////////////////////////////////////////////////////////////
#define	SHELL 				1011		// SHELL Library
//////////////////////////////////////////////////////////////////// 3D FEMs Library
#define	FE3D				1106		// Brick
////////////////////////////////////////////////
#define	HEXAHED				1059		// HEXA Library
#define	HE_8				1116		// HEXA 8 Nodes
#define	HE_20				1117		// HEXA 20 Nodes
#define	HE_21				1118		// HEXA 21 Nodes
////////////////////////////////////////////////
#define	PENTAHED			1058		// PENTA Library
#define	PE_6				1119		// PENTA 6 Nodes
#define	PE_15				1120		// PENTA 15 Nodes
////////////////////////////////////////////////
#define	TETRAHED 			1057		// TETRA Library
#define	TE_4				1121		// TETRA 4 Nodes
#define	TE_10				1122		// TETRA 10 Nodes
//////////////////////////////////////////////////////// 
#define	PATCH 				1012		// PATCH Library 
#define	P_TENSOR			1099		// 
#define	P_GORDONS			1098		// 
#define	P_COONS				1013		// 
#define	P_BEZIER			1093
#define	P_BSPLINE           1094
#define	P_NURB              1095
#define	P_ROTATE			1014		// 
#define	P_LOFT				1015		// 
#define	P_EXTRUDE			1016		// 
#define	P_DUCT				1017		// 
#define	P_SWEEP				1018		// 
//#define	P_QUADS				1019		// 
#define	P_FLATPLATE			1020		// 
#define	P_LINEAR			1083
#define	P_QUADRATIC         1084
#define	P_CUBIC             1085
#define P_EDIT				1021
#define P_MOVE				1022
#define P_POST				1037
#define P_UNPOST			1053
#define P_DELETE			1064
#define P_STITCH            1071
#define P_SPAWN             1072
#define P_ROTATE_B          1073		// Button action
#define P_XLATE             1074
#define P_SCALE             1075
#define P_SHEAR             1076
#define P_PROFILE           1097
#define P_OPER				1104
////////////////////////////////////////////////////////
#define	SOLID 				1040		// SOLID Library 
#define	S_TENSOR			1101		// 
#define	S_GORDONS			1100		// 
#define	S_COONS				1041		// 
#define	S_BEZIER			1090
#define	S_BSPLINE           1091
#define	S_NURB              1092
#define	S_ROTATE			1042		// 
#define	S_LOFT				1043		// 
#define	S_EXTRUDE			1044		// 
#define	S_DUCT				1045		// 
#define	S_SWEEP				1046		// 
//#define	P_QUADS				1047		// 
#define	S_FLATPLATE			1048		// 
#define	S_LINEAR			1086
#define	S_QUADRATIC         1087
#define	S_CUBIC             1088
#define S_EDIT				1049
#define S_MOVE				1050
#define S_POST				1051
#define S_UNPOST			1054
#define S_DELETE			1063
#define S_STITCH            1065
#define S_SPAWN	            1066
#define S_ROTATE_B          1067
#define S_XLATE             1068
#define S_SCALE             1069
#define S_SHEAR             1070
#define S_OPER				1103
////////////////////////////////////////// Element Tools:Edit & Move
#define E_EDIT				1023
#define E_MOVE				1024
#define E_POST				1039
#define E_UNPOST			1055
#define E_DELETE			1062
//////////////////////////////////////////
#define CURVE				1025	
#define C_CIRCLE			1026
#define C_ELLIPSE 			1027
#define C_PARABOLA 			1028
#define C_LINEAR 			1029
#define C_QUADRATIC			1030
#define	C_CUBIC             1089
#define C_HERMITE 			1031
#define C_BEZIER 			1032
#define C_BSPLINE 			1033
#define C_NURB	 			1060
#define C_EDIT  			1034
#define C_MOVE 				1035
#define C_POST				1038
#define C_UNPOST			1056
#define C_DELETE			1061
#define C_STITCH            1077
#define C_SPAWN             1078
#define C_ROTATE            1079
#define C_XLATE             1080
#define C_SCALE             1081
#define C_SHEAR             1082
#define C_PROFILE           1096
#define C_OPER				1102
//////////////////////////////////////////
#define OBJ3D				1052
////////////////////////////////
#endif

