#ifndef _SUPPDEF_H
#define _SUPPDEF_H 

////////////////////////////////////////// Last Number already assigned
#define SUPP_LAST_NUMBER			5020
////////////////////////////////////////// Objects
#define SUPPORT						5105		
#define	LIN_SUPPORT					5106
#define NON_SUPPORT					5107
#define	SUPPORT_RIGID				5108
#define	SUPPORT_LINSPRING			5109
#define	SUPPORT_LINSNUBBER			5110
#define	SUPPORT_NLSPRING			5111
#define	SUPPORT_NLSNUBBER			5112
/////////////////////////////////////////// NODE
#define NSUP_RIGID		            5001
#define NSUP_RIG_NODE				5137
#define NSUP_RIG_CNODE				5138
///////
#define NSUP_LINSPRING              5002
#define NSUP_LSP_NODE				5139
#define NSUP_LSP_CNODE				5140
///////
#define NSUP_LINSNUBBER             5003
#define NSUP_LSN_NODE				5141
#define NSUP_LSN_CNODE				5142
///////
#define NSUP_NLSPRING	            5004
#define NSUP_NSP_NODE				5143
#define NSUP_NSP_CNODE				5144
///////
#define NSUP_NLSNUBBER              5005
#define NSUP_NSN_NODE				5145
#define NSUP_NSN_CNODE				5146
///////
#define NSUP_EDIT					5027
#define NSUP_MOVE					5028
#define NSUP_POST					5029
#define NSUP_UNPOST					5030
#define NSUP_DELETE					5031
/////////////////////////////////////////// CURVE
#define CSUP_RIGID		            5006
#define CSUP_RIG_CIRCLE				5226
#define CSUP_RIG_ELLIPSE 			5227
#define CSUP_RIG_PARABOLA			5228
#define CSUP_RIG_LINEAR 			5229
#define CSUP_RIG_QUADRATIC			5230
#define	CSUP_RIG_CUBIC				5289
#define CSUP_RIG_HERMITE 			5231
#define CSUP_RIG_BEZIER 			5232
#define CSUP_RIG_BSPLINE 			5233
#define CSUP_RIG_NURB				5260
#define CSUP_RIG_STITCH				5277
#define CSUP_RIG_SPAWN				5278
///////
#define CSUP_RIG_EDIT  				5234
#define CSUP_RIG_MOVE 				5235
#define CSUP_RIG_POST				5238
#define CSUP_RIG_UNPOST				5256
#define CSUP_RIG_DELETE				5261
////////////////////////////////////////
#define CSUP_LINSPRING              5007
#define CSUP_LSP_CIRCLE				5326
#define CSUP_LSP_ELLIPSE 			5327
#define CSUP_LSP_PARABOLA			5328
#define CSUP_LSP_LINEAR 			5329
#define CSUP_LSP_QUADRATIC			5330
#define	CSUP_LSP_CUBIC				5389
#define CSUP_LSP_HERMITE 			5331
#define CSUP_LSP_BEZIER 			5332
#define CSUP_LSP_BSPLINE 			5333
#define CSUP_LSP_NURB				5360
#define CSUP_LSP_STITCH				5377
#define CSUP_LSP_SPAWN				5378
///////
#define CSUP_LSP_EDIT  				5334
#define CSUP_LSP_MOVE 				5335
#define CSUP_LSP_POST				5338
#define CSUP_LSP_UNPOST				5356
#define CSUP_LSP_DELETE				5361
////////////////////////////////////////
#define CSUP_LINSNUBBER             5008
#define CSUP_LSN_CIRCLE				5426
#define CSUP_LSN_ELLIPSE 			5427
#define CSUP_LSN_PARABOLA			5428
#define CSUP_LSN_LINEAR 			5429
#define CSUP_LSN_QUADRATIC			5430
#define	CSUP_LSN_CUBIC				5489
#define CSUP_LSN_HERMITE 			5431
#define CSUP_LSN_BEZIER 			5432
#define CSUP_LSN_BSPLINE 			5433
#define CSUP_LSN_NURB				5460
#define CSUP_LSN_STITCH				5477
#define CSUP_LSN_SPAWN				5478
///////
#define CSUP_LSN_EDIT  				5434
#define CSUP_LSN_MOVE 				5435
#define CSUP_LSN_POST				5438
#define CSUP_LSN_UNPOST				5456
#define CSUP_LSN_DELETE				5461
////////////////////////////////////////
#define CSUP_NLSPRING	            5009
#define CSUP_NSP_CIRCLE				5526
#define CSUP_NSP_ELLIPSE 			5527
#define CSUP_NSP_PARABOLA			5528
#define CSUP_NSP_LINEAR 			5529
#define CSUP_NSP_QUADRATIC			5530
#define	CSUP_NSP_CUBIC				5589
#define CSUP_NSP_HERMITE 			5531
#define CSUP_NSP_BEZIER 			5532
#define CSUP_NSP_BSPLINE 			5533
#define CSUP_NSP_NURB				5560
#define CSUP_NSP_STITCH				5577
#define CSUP_NSP_SPAWN				5578
///////
#define CSUP_NSP_EDIT  				5534
#define CSUP_NSP_MOVE 				5535
#define CSUP_NSP_POST				5538
#define CSUP_NSP_UNPOST				5556
#define CSUP_NSP_DELETE				5561
////////////////////////////////////////
#define CSUP_NLSNUBBER              5010
#define CSUP_NSN_CIRCLE				5626
#define CSUP_NSN_ELLIPSE 			5627
#define CSUP_NSN_PARABOLA			5628
#define CSUP_NSN_LINEAR 			5629
#define CSUP_NSN_QUADRATIC			5630
#define	CSUP_NSN_CUBIC				5689
#define CSUP_NSN_HERMITE 			5631
#define CSUP_NSN_BEZIER 			5632
#define CSUP_NSN_BSPLINE 			5633
#define CSUP_NSN_NURB				5660
#define CSUP_NSN_STITCH				5677
#define CSUP_NSN_SPAWN				5678
///////
#define CSUP_NSN_EDIT  				5634
#define CSUP_NSN_MOVE 				5635
#define CSUP_NSN_POST				5638
#define CSUP_NSN_UNPOST				5656
#define CSUP_NSN_DELETE				5661
///////
#define CSUP_EDIT					5037
#define CSUP_MOVE					5038
#define CSUP_POST					5039
#define CSUP_UNPOST					5040
#define CSUP_DELETE					5041
/////////////////////////////////////////// PATCH
#define PSUP_RIGID		            5011
#define PSUP_RIG_EXTRUDE			5701
#define PSUP_RIG_ROTATE				5702
#define PSUP_RIG_LOFT2				5703
#define PSUP_RIG_LOFT3				5704
#define PSUP_RIG_LOFT4				5705
#define PSUP_RIG_LOFTMANY			5706
#define PSUP_RIG_SWEEP				5707
#define PSUP_RIG_DUCT				5708
#define PSUP_RIG_TENSOR				5709
#define PSUP_RIG_COONS				5710
#define PSUP_RIG_GORDON				5711
#define PSUP_RIG_FLAT				5712
#define PSUP_RIG_STITCH				5713
#define PSUP_RIG_SPAWN				5714
///////
#define PSUP_LINSPRING              5012
#define PSUP_LSP_EXTRUDE			5721
#define PSUP_LSP_ROTATE				5722
#define PSUP_LSP_LOFT2				5723
#define PSUP_LSP_LOFT3				5724
#define PSUP_LSP_LOFT4				5725
#define PSUP_LSP_LOFTMANY			5726
#define PSUP_LSP_SWEEP				5727
#define PSUP_LSP_DUCT				5728
#define PSUP_LSP_TENSOR				5729
#define PSUP_LSP_COONS				5730
#define PSUP_LSP_GORDON				5731
#define PSUP_LSP_FLAT				5732
#define PSUP_LSP_STITCH				5733
#define PSUP_LSP_SPAWN				5734
///////
#define PSUP_LINSNUBBER             5013
#define PSUP_LSN_EXTRUDE			5741
#define PSUP_LSN_ROTATE				5742
#define PSUP_LSN_LOFT2				5743
#define PSUP_LSN_LOFT3				5744
#define PSUP_LSN_LOFT4				5745
#define PSUP_LSN_LOFTMANY			5746
#define PSUP_LSN_SWEEP				5747
#define PSUP_LSN_DUCT				5748
#define PSUP_LSN_TENSOR				5749
#define PSUP_LSN_COONS				5750
#define PSUP_LSN_GORDON				5751
#define PSUP_LSN_FLAT				5752
#define PSUP_LSN_STITCH				5753
#define PSUP_LSN_SPAWN				5754
///////
#define PSUP_NLSPRING	            5014
#define PSUP_NSP_EXTRUDE			5761
#define PSUP_NSP_ROTATE				5762
#define PSUP_NSP_LOFT2				5763
#define PSUP_NSP_LOFT3				5764
#define PSUP_NSP_LOFT4				5765
#define PSUP_NSP_LOFTMANY			5766
#define PSUP_NSP_SWEEP				5767
#define PSUP_NSP_DUCT				5768
#define PSUP_NSP_TENSOR				5769
#define PSUP_NSP_COONS				5770
#define PSUP_NSP_GORDON				5771
#define PSUP_NSP_FLAT				5772
#define PSUP_NSP_STITCH				5773
#define PSUP_NSP_SPAWN				5774
///////
#define PSUP_NLSNUBBER              5015
#define PSUP_NSN_EXTRUDE			5781
#define PSUP_NSN_ROTATE				5782
#define PSUP_NSN_LOFT2				5783
#define PSUP_NSN_LOFT3				5784
#define PSUP_NSN_LOFT4				5785
#define PSUP_NSN_LOFTMANY			5786
#define PSUP_NSN_SWEEP				5787
#define PSUP_NSN_DUCT				5788
#define PSUP_NSN_TENSOR				5789
#define PSUP_NSN_COONS				5790
#define PSUP_NSN_GORDON				5791
#define PSUP_NSN_FLAT				5792
#define PSUP_NSN_STITCH				5793
#define PSUP_NSN_SPAWN				5794
///////
#define PSUP_EDIT					5047
#define PSUP_MOVE					5048
#define PSUP_POST					5049
#define PSUP_UNPOST					5050
#define PSUP_DELETE					5051
/////////////////////////////////////////// Solid
#define SSUP_RIGID		            5016
#define SSUP_RIG_EXTRUDE			5801
#define SSUP_RIG_ROTATE				5802
#define SSUP_RIG_LOFT2				5803
#define SSUP_RIG_LOFT3				5804
#define SSUP_RIG_LOFT4				5805
#define SSUP_RIG_LOFTMANY			5806
#define SSUP_RIG_SWEEP				5807
#define SSUP_RIG_DUCT				5808
#define SSUP_RIG_TENSOR				5809
#define SSUP_RIG_COONS				5810
#define SSUP_RIG_GORDON				5811
//#define SSUP_RIG_FLAT				5812
#define SSUP_RIG_STITCH				5813
#define SSUP_RIG_SPAWN				5814
///////
#define SSUP_LINSPRING              5017
#define SSUP_LSP_EXTRUDE			5821
#define SSUP_LSP_ROTATE				5822
#define SSUP_LSP_LOFT2				5823
#define SSUP_LSP_LOFT3				5824
#define SSUP_LSP_LOFT4				5825
#define SSUP_LSP_LOFTMANY			5826
#define SSUP_LSP_SWEEP				5827
#define SSUP_LSP_DUCT				5828
#define SSUP_LSP_TENSOR				5829
#define SSUP_LSP_COONS				5830
#define SSUP_LSP_GORDON				5831
//#define SSUP_LSP_FLAT				5832
#define SSUP_LSP_STITCH				5833
#define SSUP_LSP_SPAWN				5834
///////
#define SSUP_LINSNUBBER             5818
#define SSUP_LSN_EXTRUDE			5841
#define SSUP_LSN_ROTATE				5842
#define SSUP_LSN_LOFT2				5843
#define SSUP_LSN_LOFT3				5844
#define SSUP_LSN_LOFT4				5845
#define SSUP_LSN_LOFTMANY			5846
#define SSUP_LSN_SWEEP				5847
#define SSUP_LSN_DUCT				5848
#define SSUP_LSN_TENSOR				5849
#define SSUP_LSN_COONS				5850
#define SSUP_LSN_GORDON				5851
#define SSUP_LSN_FLAT				5852
#define SSUP_LSN_STITCH				5853
#define SSUP_LSN_SPAWN				5854
///////
#define SSUP_NLSPRING	            5019
#define SSUP_NSP_EXTRUDE			5861
#define SSUP_NSP_ROTATE				5862
#define SSUP_NSP_LOFT2				5863
#define SSUP_NSP_LOFT3				5864
#define SSUP_NSP_LOFT4				5865
#define SSUP_NSP_LOFTMANY			5866
#define SSUP_NSP_SWEEP				5867
#define SSUP_NSP_DUCT				5868
#define SSUP_NSP_TENSOR				5869
#define SSUP_NSP_COONS				5870
#define SSUP_NSP_GORDON				5871
//#define SSUP_NSP_FLAT				5872
#define SSUP_NSP_STITCH				5873
#define SSUP_NSP_SPAWN				5874
///////
#define SSUP_NLSNUBBER              5020
#define SSUP_NSN_EXTRUDE			5881
#define SSUP_NSN_ROTATE				5882
#define SSUP_NSN_LOFT2				5883
#define SSUP_NSN_LOFT3				5884
#define SSUP_NSN_LOFT4				5885
#define SSUP_NSN_LOFTMANY			5886
#define SSUP_NSN_SWEEP				5887
#define SSUP_NSN_DUCT				5888
#define SSUP_NSN_TENSOR				5889
#define SSUP_NSN_COONS				5890
#define SSUP_NSN_GORDON				5891
//#define SSUP_NSN_FLAT				5892
#define SSUP_NSN_STITCH				5893
#define SSUP_NSN_SPAWN				5894
///////
#define SSUP_EDIT					5057
#define SSUP_MOVE					5058
#define SSUP_POST					5059
#define SSUP_UNPOST					5060
#define SSUP_DELETE					5061
////////////////////////////////////////////////////////////////       
enum SUPPPROC				// Support Generation PROCedure
	{
		SUP_RIGID,
		SUP_LINSPR,
		SUP_LINSNU,
		SUP_NONSPR,
		SUP_NONSNU
	};
	
enum SUPPSUBTYPE				// Support Generation PROCedure
	{
		SST_RIGID,
		SST_LINSPR_T,
		SST_LINSPR_R,
		SST_LINSNU_T,
		SST_LINSNU_R,
	};
	
enum JOINTCOORD				// Support Joint Coord Basis
	{
		JC_DEFAULT,
		JC_X_FIXEDDIR,
		JC_X_TAN_CURVE,
		JC_I_TAN_PATCH,
		JC_Z_NOR_PATCH
	};	
						 
enum NONSUPP				// Support Generation Type
	{
		NS_GAP,
		NS_STOP
	};	
						 
////////////////////////////////
#endif

