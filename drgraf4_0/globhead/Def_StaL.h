#ifndef _DEF_STAL_H
#define _DEF_STAL_H 

////////////////////////////////////////// Last Number already assigned
#define STAL_LAST_NUMBER	9999
////////////////////////////////////////// Objects
#define STATICLOAD			6100       
#define FORCE				6101       
#define DISPLACE			6102        
#define PRESSURE			6103        
#define THERMAL				6104
#define	LUMPWT				6105
#define GRAVITY				6106		
/////////////////////////////////////////// NODE
#define NSL_FORCE           6007
#define NSL_FOR_NODE        6137
#define NSL_FOR_CNODE       6138
///////
#define NSL_FOR_EDIT  		61340
#define NSL_FOR_MOVE 		61350
#define NSL_FOR_POST		61380
#define NSL_FOR_UNPOST		61560
#define NSL_FOR_DELETE		61610
///////
#define NSL_DISPLACE        6008
#define NSL_DIS_NODE        6139
#define NSL_DIS_CNODE       6140
///////
#define NSL_DIS_EDIT  		61341
#define NSL_DIS_MOVE 		61351
#define NSL_DIS_POST		61381
#define NSL_DIS_UNPOST		61561
#define NSL_DIS_DELETE		61611
///////
#define NSL_PRESSURE        6009
#define NSL_PRS_NODE        6141
#define NSL_PRS_CNODE       6142
///////
#define NSL_PRS_EDIT  		61342
#define NSL_PRS_MOVE 		61352
#define NSL_PRS_POST		61382
#define NSL_PRS_UNPOST		61562
#define NSL_PRS_DELETE		61612
///////
#define NSL_THERMAL	        6010
#define NSL_THR_NODE        6143
#define NSL_THR_CNODE       6144
///////
#define NSL_THR_EDIT  		61343
#define NSL_THR_MOVE 		61353
#define NSL_THR_POST		61383
#define NSL_THR_UNPOST		61563
#define NSL_THR_DELETE		61613
///////
#define NSL_LUMPWT          6011
#define NSL_LWT_NODE        6145
#define NSL_LWT_CNODE       6146
///////
#define NSL_LWT_EDIT  		61344
#define NSL_LWT_MOVE 		61354
#define NSL_LWT_POST		61384
#define NSL_LWT_UNPOST		61564
#define NSL_LWT_DELETE		61614
///////
#define NSL_EDIT			6027
#define NSL_MOVE			6028
#define NSL_POST			6029
#define NSL_UNPOST			6030
#define NSL_DELETE			6031
/////////////////////////////////////////// CURVE
#define CSL_FORCE           6012
#define CSL_FOR_CIRCLE		6226
#define CSL_FOR_ELLIPSE 	6227
#define CSL_FOR_PARABOLA	6228
#define CSL_FOR_LINEAR 		6229
#define CSL_FOR_QUADRATIC	6230
#define	CSL_FOR_CUBIC       6289
#define CSL_FOR_HERMITE 	6231
#define CSL_FOR_BEZIER 		6232
#define CSL_FOR_BSPLINE 	6233
#define CSL_FOR_NURB		6260
#define CSL_FOR_STITCH      6277
#define CSL_FOR_SPAWN       6278
///////
#define CSL_FOR_EDIT  		6234
#define CSL_FOR_MOVE 		6235
#define CSL_FOR_POST		6238
#define CSL_FOR_UNPOST		6256
#define CSL_FOR_DELETE		6261
////////////////////////////////////////
#define CSL_DISPLACE        6013
#define CSL_DIS_CIRCLE		6326
#define CSL_DIS_ELLIPSE 	6327
#define CSL_DIS_PARABOLA	6328
#define CSL_DIS_LINEAR 		6329
#define CSL_DIS_QUADRATIC	6330
#define	CSL_DIS_CUBIC       6389
#define CSL_DIS_HERMITE 	6331
#define CSL_DIS_BEZIER 		6332
#define CSL_DIS_BSPLINE 	6333
#define CSL_DIS_NURB		6360
#define CSL_DIS_STITCH      6377
#define CSL_DIS_SPAWN       6378
///////
#define CSL_DIS_EDIT  		6334
#define CSL_DIS_MOVE 		6335
#define CSL_DIS_POST		6338
#define CSL_DIS_UNPOST		6356
#define CSL_DIS_DELETE		6361
////////////////////////////////////////
#define CSL_PRESSURE        6014
#define CSL_PRS_CIRCLE		6426
#define CSL_PRS_ELLIPSE 	6427
#define CSL_PRS_PARABOLA	6428
#define CSL_PRS_LINEAR 		6429
#define CSL_PRS_QUADRATIC	6430
#define	CSL_PRS_CUBIC       6489
#define CSL_PRS_HERMITE 	6431
#define CSL_PRS_BEZIER 		6432
#define CSL_PRS_BSPLINE 	6433
#define CSL_PRS_NURB		6460
#define CSL_PRS_STITCH      6477
#define CSL_PRS_SPAWN       6478
///////
#define CSL_PRS_EDIT  		6434
#define CSL_PRS_MOVE 		6435
#define CSL_PRS_POST		6438
#define CSL_PRS_UNPOST		6456
#define CSL_PRS_DELETE		6461
////////////////////////////////////////
#define CSL_THERMAL	        6015
#define CSL_THR_CIRCLE		6526
#define CSL_THR_ELLIPSE 	6527
#define CSL_THR_PARABOLA	6528
#define CSL_THR_LINEAR 		6529
#define CSL_THR_QUADRATIC	6530
#define	CSL_THR_CUBIC       6589
#define CSL_THR_HERMITE 	6531
#define CSL_THR_BEZIER 		6532
#define CSL_THR_BSPLINE 	6533
#define CSL_THR_NURB		6560
#define CSL_THR_STITCH      6577
#define CSL_THR_SPAWN       6578
///////
#define CSL_THR_EDIT  		6534
#define CSL_THR_MOVE 		6535
#define CSL_THR_POST		6538
#define CSL_THR_UNPOST		6556
#define CSL_THR_DELETE		6561
////////////////////////////////////////
#define CSL_LUMPWT          6016
#define CSL_LWT_CIRCLE		6626
#define CSL_LWT_ELLIPSE 	6627
#define CSL_LWT_PARABOLA	6628
#define CSL_LWT_LINEAR 		6629
#define CSL_LWT_QUADRATIC	6630
#define	CSL_LWT_CUBIC       6689
#define CSL_LWT_HERMITE 	6631
#define CSL_LWT_BEZIER 		6632
#define CSL_LWT_BSPLINE 	6633
#define CSL_LWT_NURB		6660
#define CSL_LWT_STITCH      6677
#define CSL_LWT_SPAWN       6678
///////
#define CSL_LWT_EDIT  		6634
#define CSL_LWT_MOVE 		6635
#define CSL_LWT_POST		6638
#define CSL_LWT_UNPOST		6656
#define CSL_LWT_DELETE		6661
///////
#define CSL_EDIT			6037
#define CSL_MOVE			6038
#define CSL_POST			6039
#define CSL_UNPOST			6040
#define CSL_DELETE			6041
/////////////////////////////////////////// PATCH
#define PSL_FORCE           6017
#define	PSL_FOR_TENSOR		6299		// 
#define	PSL_FOR_GORDONS		6298		// 
#define	PSL_FOR_COONS		6213		// 
#define	PSL_FOR_LOFT		6215		// 
#define	PSL_FOR_EXTRUDE		6216		// 
#define	PSL_FOR_DUCT		6217		// 
#define	PSL_FOR_SWEEP		6218		// 
#define	PSL_FOR_FLATPLATE	6220		// 
#define PSL_FOR_STITCH		6271
#define PSL_FOR_SPAWN       6272

#define PSL_FOR_EDIT		6221
#define PSL_FOR_MOVE		6222
#define PSL_FOR_POST		6237
#define PSL_FOR_UNPOST		6253
#define PSL_FOR_DELETE		6264
////////////////////////////////////////
#define PSL_DISPLACE        6018
#define	PSL_DIS_TENSOR		6399		// 
#define	PSL_DIS_GORDONS		6398		// 
#define	PSL_DIS_COONS		6313		// 
#define	PSL_DIS_LOFT		6315		// 
#define	PSL_DIS_EXTRUDE		6316		// 
#define	PSL_DIS_DUCT		6317		// 
#define	PSL_DIS_SWEEP		6318		// 
#define	PSL_DIS_FLATPLATE	6320		// 
#define PSL_DIS_STITCH		6371
#define PSL_DIS_SPAWN       6372

#define PSL_DIS_EDIT		6321
#define PSL_DIS_MOVE		6322
#define PSL_DIS_POST		6337
#define PSL_DIS_UNPOST		6353
#define PSL_DIS_DELETE		6364
////////////////////////////////////////
#define PSL_PRESSURE        6019
#define	PSL_PRS_TENSOR		6499		// 
#define	PSL_PRS_GORDONS		6498		// 
#define	PSL_PRS_COONS		6413		// 
#define	PSL_PRS_LOFT		6415		// 
#define	PSL_PRS_EXTRUDE		6416		// 
#define	PSL_PRS_DUCT		6417		// 
#define	PSL_PRS_SWEEP		6418		// 
#define	PSL_PRS_FLATPLATE	6420		// 
#define PSL_PRS_STITCH		6471
#define PSL_PRS_SPAWN       6472

#define PSL_PRS_EDIT		6421
#define PSL_PRS_MOVE		6422
#define PSL_PRS_POST		6437
#define PSL_PRS_UNPOST		6453
#define PSL_PRS_DELETE		6464
////////////////////////////////////////
#define PSL_THERMAL	        6020
#define	PSL_THR_TENSOR		6599		// 
#define	PSL_THR_GORDONS		6598		// 
#define	PSL_THR_COONS		6513		// 
#define	PSL_THR_LOFT		6515		// 
#define	PSL_THR_EXTRUDE		6516		// 
#define	PSL_THR_DUCT		6517		// 
#define	PSL_THR_SWEEP		6518		// 
#define	PSL_THR_FLATPLATE	6520		// 
#define PSL_THR_STITCH		6571
#define PSL_THR_SPAWN       6572

#define PSL_THR_EDIT		6521
#define PSL_THR_MOVE		6522
#define PSL_THR_POST		6537
#define PSL_THR_UNPOST		6553
#define PSL_THR_DELETE		6564
////////////////////////////////////////
#define PSL_LUMPWT          6021
#define	PSL_LWT_TENSOR		6699		// 
#define	PSL_LWT_GORDONS		6698		// 
#define	PSL_LWT_COONS		6613		// 
#define	PSL_LWT_LOFT		6615		// 
#define	PSL_LWT_EXTRUDE		6616		// 
#define	PSL_LWT_DUCT		6617		// 
#define	PSL_LWT_SWEEP		6618		// 
#define	PSL_LWT_FLATPLATE	6620		// 
#define PSL_LWT_STITCH		6671
#define PSL_LWT_SPAWN       6672

#define PSL_LWT_EDIT		6621
#define PSL_LWT_MOVE		6622
#define PSL_LWT_POST		6637
#define PSL_LWT_UNPOST		6653
#define PSL_LWT_DELETE		6664
///////
#define PSL_EDIT			6042
#define PSL_MOVE			6043
#define PSL_POST			6044
#define PSL_UNPOST			6045
#define PSL_DELETE			6046
/////////////////////////////////////////// SOLID
#define SSL_FORCE           6022
#define SSL_DISPLACE        6023
#define SSL_PRESSURE        6024
#define SSL_THERMAL	        6025
#define SSL_LUMPWT          6026
///////
#define SSL_FOR_EDIT		67210
#define SSL_FOR_MOVE		67220
#define SSL_FOR_POST		67370
#define SSL_FOR_UNPOST		67530
#define SSL_FOR_DELETE		67640
///////
#define SSL_DIS_EDIT		67211
#define SSL_DIS_MOVE		67221
#define SSL_DIS_POST		67371
#define SSL_DIS_UNPOST		67531
#define SSL_DIS_DELETE		67641
///////
#define SSL_PRS_EDIT		67212
#define SSL_PRS_MOVE		67222
#define SSL_PRS_POST		67372
#define SSL_PRS_UNPOST		67532
#define SSL_PRS_DELETE		67642
///////
#define SSL_THR_EDIT		67213
#define SSL_THR_MOVE		67223
#define SSL_THR_POST		67373
#define SSL_THR_UNPOST		67533
#define SSL_THR_DELETE		67643
///////
#define SSL_LWT_EDIT		67214
#define SSL_LWT_MOVE		67224
#define SSL_LWT_POST		67374
#define SSL_LWT_UNPOST		67534
#define SSL_LWT_DELETE		67644
///////
#define SSL_EDIT			6032
#define SSL_MOVE			6033
#define SSL_POST			6034
#define SSL_UNPOST			6035
#define SSL_DELETE			6036
////////////////////////////////
#define CSTATIC				6147	// StaticLoad Curves, Isopara or Non-Iso      
#define PSTATIC				6148       
#define SSTATIC				6149
////////////////////////////////       
//#define CFORCE				6147       
//#define PFORCE				6148       
//#define SFORCE				6149
////////////////////////////////
enum STALPROC				// STLport Generation PROCedure
	{
		STL_FORCE,
		STL_DISPLACE,
		STL_PRESSURE,
		STL_THERMAL,
		STL_LUMPWT
	};
	
enum STALSUBTYPE				// STLport Generation PROCedure
	{
		SSTL_FORCE_T,
		SSTL_FORCE_R,
		SSTL_DISPLACE_T,
		SSTL_DISPLACE_R
	};
////////////////////////////////////////////////////////
#endif

