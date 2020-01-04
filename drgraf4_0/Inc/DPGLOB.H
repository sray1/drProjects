/***************************************************************************/
/*        dpglob.h  Global variables for dreamPIPE  input preprocessor     */
/***************************************************************************/
BOOL    bLineOn;            /* are we tracking a line ? */
BOOL    bIsometricOn;
BOOL    bZoomOn;
BOOL    LayerOff[20];    /* indicates which elements/layers to be disp */
BOOL    bCB[20];         /* Check-box status */

/****** Cursor handles *************************/
HANDLE hCrossCursor;
HANDLE hArrowCursor;
HANDLE hWaitCursor;

/****** Pen Handles ****************************/
HPEN hAxisPen;
HPEN hLabelPen;
HPEN hBeamPen;
HPEN hTempPen;

/****** Global mode parameters ******************/
int FileMode=0; /* =FREEFORMAT, 1=FIXFORMAT */
int ElementMode=0;  /* 0=Node, 1=Pipe, 2=Elbow, 3=Beam, 4=Support, 5=NL Supp */


/****** CFG file parameters *********************/
char *CFGCodes[] = {
   "GRAPHICS","UNITS","DECPLACES","ZOOMFACTOR" 
   };
int MaxCFGCodes = 4;
char *ScreenCodes[] = {
   "CGA","HERCULES","EGA"
    };
int MaxScreenCodes = 3;
char *UnitsCodes[] = {
    "FPS","CGS","SI"
    };
int MaxUnitsCodes = 3;


/******  standard number formats  **********/
int FmtNo = 0; 
char FmtStr[] = "% 4d.%.4d %2s    ";
char *FmtUnit[] = {
      "in",   /* FPS */
      "cm",   /* CGS */
      "m "    /* SI  */
     };
long int FmtBase=10000;
int DecPlaces=4;



/****** BitMap/window locational/scale params ********/
struct MapCrd {
     long int x,y,z;
     };

long int MapFact=100;   /*  Magnification factor of window */
long int OldMapFact=100;
long int MapFactTemp=5;
struct MapCrd MapScLoc = {0,0,0}; /* Rel locn of window in Map */
struct MapCrd AnchorLoc ={0,0,0};
struct MapCrd MaxLoc ={1,1,1};
struct MapCrd MinLoc ={0,0,0};
struct MapCrd NewMovLoc ={0,0,0};
int FixedAxis=4;       /* 1= x axis fixed, 2= y , 4 = z  */
BOOL bDeltaMove=FALSE; /* relative movement ? */
BOOL bRefresh=TRUE;    /* dynamic refresh of drawing ? */
BOOL bDialogON=FALSE;  /* show element dialog at each naode selection ? */

int VScrollPos=0;
int HScrollPos=0;      /* Position of scroll elevators */

char AnchorNode[ID_LEN],NewNode[ID_LEN];
POINT AnchorPos;
POINT OldMovPos;
POINT NewMovPos;

long int SupportMapFact;

/****** Isometric parameters *************************/
long Tht;         /* camera angle wrt x axis */
long Phi;         /* camera angle wrt z axis */
long Rho;         /* camera dist to origin */
long Dist;        /* Distance of screen */
long IsoMapFact;  /* Scaling factor */
long AngleStep;   /* for Theta and Phi modification */


/********** Screen CFG parameters *******************/
/****** default : SCREEN=CGA        ****************/
int Wnd_y_Offset =19;
int Wnd_x_lo     =0;
int Wnd_x_hi     =629;
int Wnd_y_lo     =0;
int Wnd_y_hi     =153;

int X_LocnWindow   =111;
int Y_LocnWindow   =181;
int CX_LocnWindow  =530;
int CY_LocnWindow  =60;


/****************************************************************/
/*    DEK file parameters                                       */
/****************************************************************/
/******* data file parameters ************************/
char DataFileName[16] = UNTITLED; 
int CardNo;  /* card number */

/******* keywords ************************************/
char *KeyWords[] = {
    "C","FIXFORMAT","FREEFORMAT",
    "NODE","CNODE","PIPE","END",
    "ELBOW","BEAM",
    "RIGIDSUP",
    "TSPRING","TSNUBBER",
    "RSPRING","RSNUBBER",
    "MASTER","PIPEPROP"
     };
int MaxKeyWords=16;

/****************************************************************/

char *ElementNames[]= {
    "Node   ","Pipe   ","Elbow  ","Beam   ","Support","NL Supp"
     };

/******* Node variables / data structure *************/
struct Node {
    char id[ID_LEN];
    long int x,y,z;
    char nid_r[ID_LEN];
    char sup_id[ID_LEN];           /* pad 10 char field */
    char show,data[DATA_LEN];
    };
struct Node Node_Table[MAX_NODES];
int Max_Nodes=0;


/******** Pipe variables/ data structure **************/
struct Pipe {
    char line_id[ID_LEN];
    char nid_i[ID_LEN],nid_j[ID_LEN];
    char rid_i[ID_LEN],rid_j[ID_LEN];   /* pad 2 nos 5 char fields */
    char pid[ID_LEN],mid[ID_LEN];
    char kid_i[ID_LEN],kid_j[ID_LEN];   /* pad 5 char field */
    int numseg;               /* pad 5 char field */
    char show,data[DATA_LEN];
    };
struct Pipe Pipe_Table[MAX_PIPES];
int Max_Pipes=0;


/******** Beam variables/ data structure **************/
struct Beam {
    char group_id[ID_LEN];
    char nid_i[ID_LEN],nid_j[ID_LEN];
    char rid_i[ID_LEN],rid_j[ID_LEN],nid_k[ID_LEN];   /* pad 5 char field */
    char pid[ID_LEN],mid[ID_LEN];                /* pad 3 nos 5 char fields */
    int numseg;                        /* pad 5 char field */
    char show,data[DATA_LEN];
    };
struct Beam Beam_Table[MAX_BEAMS];
int Max_Beams=0;


/******** Elbow variables/ data structure **************/
struct Elbow {
    char line_id[ID_LEN];
    char nid_i[ID_LEN],nid_j[ID_LEN];
    char nid_cc[ID_LEN],nid_ti[ID_LEN];
    char nid_a[ID_LEN],nid_b[ID_LEN];
    char pid[ID_LEN],mid[ID_LEN];
    char kid_i[ID_LEN],kid_j[ID_LEN];
    int numseg;     /*  pad 5 char field */
    char rid_i[ID_LEN],rid_j[ID_LEN];
    char show,data[DATA_LEN];
    };
struct Elbow Elbow_Table[MAX_ELBOWS];
int Max_Elbows=0;


/******** Support variables/ data structure **************/
struct Support {
    char id[ID_LEN];
    int kode;
    char stiffness[10];
    char nid_a[ID_LEN];            /* pad 3 nos 10 char fields */
    char show,data[DATA_LEN];
    };
struct Support Support_Table[MAX_SUPPORTS];
int Max_Supports=0;


/******** NonLin Support variables/ data structure **************/
struct NL_Supp {
    char id[ID_LEN];
    int kode;
    char stiffness[10];
    char nid_a[ID_LEN];            /* pad 3 nos 10 char fields */
    char show,data[DATA_LEN];
    };
struct NL_Supp NL_Supp_Table[1]; /* change 1 to MAX_NL_SUPPS */
int Max_NL_Supps=0;

/******** PipeProp       variables/ data structure **************/
struct PipeProp {
    char gid[ID_LEN];             /* pad 1 no 10 char field */
    char od[10];
    char thk[ID_LEN];
    char thki[ID_LEN];
    long int r;
    char pi[10];
    char show,data[DATA_LEN];
    };
struct PipeProp PipeProp_Table[MAX_PIPEPROPS];
int Max_PipeProps=0;

/******** Master         variables/ data structure **************/
struct Master {
    char xstat[ID_LEN];
    char unit[ID_LEN];
    char g[10];
    long int fac;
    char lambda[10];
    char damp[10];              /* pad 10 char field */
    char show,data[DATA_LEN];
    };
struct Master  Master_Table[MAX_MASTERS];
int Max_Masters=0;

/******** MetaCards ... unrecognised cards **********************/
struct MetaCard {
    char p[CARD_SIZE];
    };
struct MetaCard MetaCard_Table[MAX_METACARDS];
int Max_MetaCards=0;
