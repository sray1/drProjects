typedef struct D3types 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with object
		int			type;  		// 0 	= tool
								// 1	= specs
								// 2	= operation
		char*		otherName; 	// name,if needed
	}D3TYPES;
extern D3TYPES FAR D3Types[];
extern int nMax_Dr3DTypes;
