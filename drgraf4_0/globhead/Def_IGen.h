#ifndef _DEF_IGEN_H
#define _DEF_IGEN_H 

#define	NONE				-1
#define	UNONE				(UINT)NONE
////////////////////////////////////////// Last Number already assigned
#define IGEN_LAST_NUMBER	1171
////////////////////////////////////////// Controls
#define GENERATOR			1171	//110198
/////////////////////////////////
#define CREATEOPS			1167
#define COP_CREATE			11671
#define COP_TRANSLATE		11672
#define COP_ROTATE			11673
#define COP_SCALE			11674
#define COP_REFLECT			11675
#define COP_SHEAR			11676
#define COP_SPAWN			11677
#define COP_STITCH			11678
#define COP_BLEND			11679
#define COP_EXTRACT			11680
////////////////////////////////
#define GENOPS				1160        
#define GOP_EDIT			11601
#define GOP_MOVE			11602
#define GOP_POST			11603
#define GOP_UNPOST			11604
#define GOP_DELETE			11605
#define GOP_MERGE			11606
/////////////////////////////////
#define FEMOPS				1161        
#define BULLOPS				1162
////////////////////////////////////////// Dimensions        
#define EDIM_0				1163
#define EDIM_1				1164
#define EDIM_2				1165
#define EDIM_3				1166
////////////////////////////////
#define NODE				1001        // that can use EDIT & MOVE
#define INODE				10010        // that can use EDIT & MOVE
#define CNODE				1036        // that can use EDIT & MOVE
#define MNODE				1123        // that can use EDIT & MOVE
#define N_COP_STITCH             10747
#define N_COP_SPAWN				 1074
#define N_COP_XLATE              10740
#define N_COP_ROTATE             10741
#define N_COP_SCALE              10742
#define N_COP_REFLECT            10743
#define N_COP_SHEAR				 10744
#define N_COP_BEND               10745
#define N_COP_TWIST              10746
#define	N_ROTATE			10361		// to Create Curve 
#define	N_LOFT				10362		// to Create Curve
#define	N_EXTRUDE			10363		// to Create Curve 
#define	N_DUCT				10364		// to Create Curve 
#define	N_SWEEP				10365		// to Create Curve 
#define	N_COP_EXTRACT		10366		// 
#define N_OPER				1158
#define N_SUPP				1146
#define N_STAL				1150
#define N_DYNL				11501
#define N_SPEL				11502
//
#define N_EDIT				1023
#define N_MOVE				1024
#define N_POST				1039
#define N_UNPOST			1055
#define N_DELETE			1062
#define N_MERGE				1167
//////////////////////////////////////////////////////// 
#define	PATCH 				1012		// PATCH Library 
#define	P_TENSOR			1099		// 
#define	P_GORDON			1098		// 
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
//
#define P_EDIT				1021
#define P_MOVE				1022
#define P_POST				1037
#define P_UNPOST			1053
#define P_DELETE			1064
#define P_MERGE				1168
//
#define P_ROTATE_B          1073		// Button action
#define P_COP_STITCH             1071
#define P_COP_SPAWN				 1072
#define P_COP_XLATE              10720
#define P_COP_ROTATE             10721
#define P_COP_SCALE              10722
#define P_COP_REFLECT            10723
#define P_COP_SHEAR				 10724
#define P_COP_BEND               10725
#define P_COP_TWIST              10726
#define P_COP_BLEND              10727
#define	P_COP_EXTRACT			 10728		// 
#define P_PROFILE           1097
#define P_OPER				1104
#define P_SUPP				1147
#define P_STAL				1151
#define P_DYNL				1155
#define P_SPEL				1159
////////////////////////////////////////////////////////
#define	SOLID 				1040		// SOLID Library 
#define	S_TENSOR			1101		// 
#define	S_GORDON			1100		// 
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
//
#define S_EDIT				1049
#define S_MOVE				1050
#define S_POST				1051
#define S_UNPOST			1054
#define S_DELETE			1063
#define S_MERGE				1169
//
#define S_ROTATE_B          1067
#define S_COP_STITCH             1065
#define S_COP_SPAWN				 1066
#define S_COP_XLATE              10660
#define S_COP_ROTATE             10661
#define S_COP_SCALE              10662
#define S_COP_REFLECT            10663
#define S_COP_SHEAR				 10664
#define S_COP_BEND               10665
#define S_COP_TWIST              10666
#define S_COP_BLEND              10667
#define	S_COP_EXTRACT			 10668		// 
#define S_PROFILE           10971		// P_PROFILE = 1097
#define S_OPER				1103
#define S_SUPP				1148
#define S_STAL				1152
#define S_DYNL				1156
#define S_SPEL				1160
//////////////////////////////////////////
#define CURVE				1025	
#define C_CIRCLE			1026
#define C_ELLIPSE 			1027
#define C_PARABOLA 			1028
#define C_HYPERBOLA 			10281
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
#define C_MERGE				1170
#define C_COP_STITCH             1077
#define C_COP_SPAWN				 1078
#define C_COP_XLATE              10780
#define C_COP_ROTATE             10781
#define C_COP_SCALE              10782
#define C_COP_REFLECT            10783
#define C_COP_SHEAR				 10784
#define C_COP_BEND               10785
#define C_COP_TWIST              10786
#define C_COP_BLEND              10787
#define	C_COP_EXTRACT			 10788		// 
#define C_PROFILE           1096
#define C_OPER				1102
#define C_SUPP				1149
#define C_STAL				1153
#define C_DYNL				1157
#define C_SPEL				1161
////////////////////////////////////////// OBJ3D Library
#define OBJ3D				1052
#define O_EDIT				10521
#define O_MOVE				10522
#define O_DELETE			10523
#define O_POST				10524
#define O_UNPOST			10525
#define O_MERGE				10526
//
#define O_COP_STITCH        11658
#define O_COP_SPAWN			11659
#define O_COP_XLATE         11660
#define O_COP_ROTATE        11661
#define O_COP_SCALE         11662
#define O_COP_REFLECT       11663
#define O_COP_SHEAR			11664
#define O_COP_BEND          11665
#define O_COP_TWIST         11666
////////////////////////////////
enum SPAWNTYPE
{
	SPN_ROT_ABT_LINE,	// rotation about a Line
	SPN_ROT_REF_2_TAR,	// rotation from reference to target
	SPN_SYMM_N,			// Normal + point
	SPN_SYMM_3,			// 3 points on a plane		
	SPN_DIRECT,			// Direct Input of Matrix
	SPN_XFORMS,
	SPN_NONE
};	
	
enum XFORMTYPE				// Xformation Generation Type
	{
		XT_DIRECT,
		XT_XFORMS,
		XT_SYMMETRIC
	};
	
enum MOVETYPE				// Move Type
	{
		MT_TRANSLATE,
		MT_ROTATE
	};
////////////////////////////////
#endif

