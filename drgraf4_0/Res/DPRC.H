/************************************************************************/
/*                     dprc.h DreamPIPE header file  for RC             */
/************************************************************************/



/*****  Resource names ****************/


/*****  Menu stuff ********************/

#define IDM_V_ZOOM_IN                  101
#define IDM_V_ZOOM_OUT                 102
#define IDM_V_ZOOM_ALL                 103
#define IDM_V_ZOOM_ISOMETRIC           104
#define IDM_V_ZOOM_LIST                105

#define IDM_S_PARAMETERS               201
#define IDM_S_ELEMENTS                 202
#define IDM_S_REFRESH                  203
#define IDM_S_DIALOG_ON                204

#define IDM_E_NODE                     300
#define IDM_E_PIPE                     301
#define IDM_E_ELBOW                    302
#define IDM_E_BEAM                     303
#define IDM_E_SUPPORT                  304
#define IDM_E_NL_SUPP                  305

/*    POPUP   "PreProcess"	    */
#define IDM_PP_BATCH		       401
#define IDM_PP_MODEL		       402
#define IDM_PP_STATIC		       403
#define IDM_PP_SPECTRA		       404
#define IDM_PP_HISTORY		       405
#define IDM_PP_MODE		       406
#define IDM_PP_COMBIN		       407
#define IDM_PP_CODE		       408
#define IDM_PRE_DATAGEN 	       409

/*    POPUP   "Database"	    */

#define IDM_DB_STIF		       501
#define IDM_DB_STATIC		       502
#define IDM_DB_MODE		       503
#define IDM_DB_SPECTRA		       504
#define IDM_DB_HISTORY		       505
#define IDM_DB_LOADSET		       506
#define IDM_DB_CODE		       507
/*    POPUP   "Analysis"	    */
#define IDM_SA_ESTIF		       601
#define IDM_SA_GSTIF		       602
#define IDM_SA_TMATRIX		       603
#define IDM_SA_STATIC		       604
#define IDM_SA_MODE		       605
#define IDM_SA_SPECTRA		       606
#define IDM_SA_HISTORY		       607
/*    POPUP   "Response"	    */
#define IDM_RR_STATIC		       701
#define IDM_RR_MODE		       702
#define IDM_RR_SPECTRA		       703
#define IDM_RR_HISTORY		       704
#define IDM_RR_LOADSET		       705
/*    POPUP   "CodeStress"	    */
#define IDM_SR_B311		       801
#define IDM_SR_B313		       802
#define IDM_SR_B314		       803
#define IDM_SR_B318		       804
#define IDM_SR_CLASS_1		       805
#define IDM_SR_CLASS_2		       806
/*   POPUP  Graphics Constants	    */
#define IDM_GD_MODEL		       901
#define IDM_GD_STATIC		       902
#define IDM_GD_MODE		       903
#define IDM_GD_IN_SPECTRA	       904
#define IDM_GD_LR_SPECTRA	       905
#define IDM_GD_IO_SPECTRA	       906
#define IDM_GD_IN_HISTORY	       907
#define IDM_GD_LR_HISTORY	       908
#define IDM_GD_IO_HISTORY	       909
#define IDM_GD_LOADSET		       910
#define IDM_GD_CODE		       911


/****** Dialog Box constants **************************/
/****** Special Dialog Box constants ******************/
#define IDD_ELEMENTS_NODE     50
#define IDD_ELEMENTS_PIPE     51
#define IDD_ELEMENTS_BEAM     52
#define IDD_ELEMENTS_ELBOW    53
#define IDD_ELEMENTS_SUPPORT  54
#define IDD_ELEMENTS_NL_SUPP  55

#define IDD_PARAMETERS_XMIN     71
#define IDD_PARAMETERS_XMAX     72
#define IDD_PARAMETERS_YMIN     73
#define IDD_PARAMETERS_YMAX     74
#define IDD_PARAMETERS_FACTOR   75
#define IDD_PARAMETERS_FIX      76
#define IDD_PARAMETERS_UNITS    77

/****** Common element dialog box constants ***********/
#define IDD_OK            1
#define IDD_ESC           2
#define IDD_ADD           101
#define IDD_DEL           102
#define IDD_ID            103
#define IDD_LIST          104
#define IDD_EDIT          105

#define IDD_FILE_PATH     12 

/**** Node dialog constants *****/
#define IDD_NODE_X        201
#define IDD_NODE_Y        202
#define IDD_NODE_Z        203
#define IDD_NODE_NID_R    204
#define IDD_NODE_SUP_ID   205
#define IDD_NODE_CONTROL  206

/**** Pipe dialog constants *****/
#define IDD_PIPE_LINE_ID   301
#define IDD_PIPE_NID_I     302
#define IDD_PIPE_NID_J     303
#define IDD_PIPE_RID_I     304
#define IDD_PIPE_RID_J     305
#define IDD_PIPE_PID       306
#define IDD_PIPE_MID       307
#define IDD_PIPE_KID_I     308
#define IDD_PIPE_KID_J     309
#define IDD_PIPE_NUMSEG    310

/**** Beam dialog constants *****/
#define IDD_BEAM_GROUP_ID  401
#define IDD_BEAM_NID_I     402
#define IDD_BEAM_NID_J     403
#define IDD_BEAM_RID_I     404
#define IDD_BEAM_RID_J     405
#define IDD_BEAM_NID_K     406
#define IDD_BEAM_PID       407
#define IDD_BEAM_MID       408
#define IDD_BEAM_NUMSEG    409

/**** Elbow dialog constants *****/
#define IDD_ELBOW_LINE_ID  500
#define IDD_ELBOW_NID_I    501
#define IDD_ELBOW_NID_J    502
#define IDD_ELBOW_NID_CC   503
#define IDD_ELBOW_NID_TI   504
#define IDD_ELBOW_NID_A    505
#define IDD_ELBOW_NID_B    506
#define IDD_ELBOW_PID      507
#define IDD_ELBOW_MID      508
#define IDD_ELBOW_KID_I    509
#define IDD_ELBOW_KID_J    510
#define IDD_ELBOW_NUMSEG   511
#define IDD_ELBOW_RID_I    512
#define IDD_ELBOW_RID_J    513

/**** Support dialog constants *****/
#define IDD_SUPPORT_ID        601
#define IDD_SUPPORT_KODE      602
#define IDD_SUPPORT_STIFFNESS 603
#define IDD_SUPPORT_NID_A     604
#define IDD_SUPPORT_TSPRING   605
#define IDD_SUPPORT_RSPRING   606
#define IDD_SUPPORT_TSNUBBER  607
#define IDD_SUPPORT_RSNUBBER  608

/**** NL Support dialog constants *****/
#define IDD_NL_SUPP_ID        701
#define IDD_NL_SUPP_KODE      702
#define IDD_NL_SUPP_STIFFNESS 703
#define IDD_NL_SUPP_NID_A     704
