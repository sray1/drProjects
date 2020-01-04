	  common/ShellParams/DD,RR,Dp1,Rp1,Dp2,Rp2,
     &					AMat1,AMat2,WMat1,WMat2,RMat1,RMat2,
     &					rE1,rE2,FMt1,FMt2
      Real(kind=8)	DD   ,RR                            
      Dimension	    DD(3),RR(3)
      Real(kind=8)	Dp1   ,Rp1   ,Dp2   ,Rp2                            
      Dimension	    Dp1(3),Rp1(3),Dp2(3),Rp2(3)
	  Real(kind=8)	AMat1       ,WMat1     ,RMat1                     
	  Dimension		AMat1(3,3)  ,WMat1(3,3),RMat1(3,3)
	  Real(kind=8)	AMat2       ,WMat2     ,RMat2                     
	  Dimension		AMat2(3,3)  ,WMat2(3,3),RMat2(3,3)
	  Real(kind=8)	rE1   ,rE2   ,FMt1   ,FMt2                        
	  Dimension		rE1(6),rE2(6),FMt1(6),FMt2(6)