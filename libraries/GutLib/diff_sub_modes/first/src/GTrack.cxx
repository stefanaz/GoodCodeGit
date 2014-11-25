//
// GTrack.cxx
//
// $Author: meyer $
// $Date: 2005/08/30 11:17:05 $
// $Revision: 1.14 $
//

#include <GTrack.h>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

#ifndef __CINT__
ClassImp(GTrack)
#endif

//_____________________________________________________________
// GTrack
//
// track class
//
GTrack::GTrack() : TVector3() {
  //
  // GTrack default constructor
  if ( gDebug ) cout << endl << "GTrack::GTrack default ctor called" << endl << endl;

  fID = 0;
  fID2 = 0;
  fType = kNothing;
  fMuonKinType = kNoMuonKin;
  fCharge = 0.0;
  fVertexID = 0;
  fPrimaryVertex = kFALSE;
  fSecondaryVertex = kFALSE;
  fVertexFittedTrackID = 0;
  fEndPosX = 0.0;
  fEndPosY = 0.0;
  fEndPosZ = 0.0;
  fZbzyTimingHits = 0;
  fAxialHits = 0;
  fStereoHits = 0;
  fInnerLayer = 0;
  fOuterLayer = 0;
  fDedx = 0.0;
  fDedxCorr = 0.0;
  fNDoF = 0;
  fChi2 = 0.0;
  fVChi2 = 0.0;
  fNMVDRBarrelHits = 0;
  fNMVDZBarrelHits = 0;
  fNMVDUWheelHits = 0;
  fNMVDVWheelHits = 0;
  fDedxMVD = 0.0;

  fW = 0;
  fPhiZero = 0;
  fT = 0;
  fDZero = 0;
  fZZero = 0;
  fCov_0 = 0;
  fCov_1 = 0;
  fCov_2 = 0;
  fCov_3 = 0;
  fCov_4 = 0;
  fCov_5 = 0;
  fCov_6 = 0;
  fCov_7 = 0;
  fCov_8 = 0;
  fCov_9 = 0;
  fCov_10 = 0;
  fCov_11 = 0;
  fCov_12 = 0;
  fCov_13 = 0;
  fCov_14 = 0;

  fUsedSuperLayersCut = kFALSE;
  fUsedHitsCut        = kFALSE;
  fUsedStereoHitsCut  = kFALSE;
  fZHCut              = kFALSE;
  fMVDHitsCut         = kFALSE;
  fZHCut              = kFALSE;
  fMVDHitsCut         = kFALSE;
  fAllCuts            = kFALSE;

  fImpactParameter               = 0.0;
  f2DImpactParameter             = 0.0;
  fImpactParameterSignificance   = 0.0;
  f2DImpactParameterSignificance = 0.0;
  fFakeWeight                    = 0.0;
  fFakeWeight_etalowpt           = 0.0;
  fFakeWeight_etahighpt          = 0.0;
  fFakeWeight_cum                = 0.0;

}

//_____________________________________________________________

GTrack::GTrack(Int_t id, Int_t id2, Int_t trktype, Double_t x, Double_t y, Double_t z, Double_t charge,
	       Int_t vertexid, Bool_t primary, Bool_t secondary,
	       Int_t vertexfittedtrackid, Double_t endposx, Double_t endposy, Double_t endposz, 
	       Int_t zbytiminghits, Int_t axialhits, Int_t stereohits,
	       Int_t innerlayer, Int_t outerlayer, Double_t dedx, Double_t dedxcorr,
	       Int_t ndof, Double_t chi2, Double_t vchi2, Int_t nbr, Int_t nbz, Int_t nwu, 
	       Int_t nwv, Double_t dedxmvd, Double_t w, Double_t phizero, Double_t t,
	       Double_t dzero, Double_t zzero) : TVector3(x,y,z) {
  //
  // GTrack default constructor
  if ( gDebug ) cout << endl << "GTrack::GTrack default ctor called" << endl << endl;

  fID = id;
  fID2 = id2;
  if ( trktype == 1 )
    fType = kCTD;
  else if ( trktype == 2 )
    fType = kREG;
  else if ( trktype == 3 )
    fType = kZTT;
  else
    fType = kNothing;
  if ( ( this->Eta() >= gCards->GetFMUONEtaLow() ) && ( this->Eta() <= gCards->GetFMUONEtaUp() ) ) {
    fMuonKinType = kForwardMuonKin;
  } else if ( ( this->Eta() >= gCards->GetBMUONEtaLow() ) && ( this->Eta() <= gCards->GetBMUONEtaUp() ) ) {
    fMuonKinType = kBarrelMuonKin;
  } else if ( ( this->Eta() >= gCards->GetRMUONEtaLow() ) && ( this->Eta() <= gCards->GetRMUONEtaUp() ) ) {
    fMuonKinType = kRearMuonKin;
  } else {
    fMuonKinType = kNoMuonKin;
  }
  fCharge = charge;
  fVertexID = vertexid;
  fPrimaryVertex = primary;
  fSecondaryVertex = secondary;
  fVertexFittedTrackID = vertexfittedtrackid;
  fEndPosX = endposx;
  fEndPosY = endposy;
  fEndPosZ = endposz;
  fZbzyTimingHits = zbytiminghits;
  fAxialHits = axialhits;
  fStereoHits = stereohits;
  fInnerLayer = innerlayer;
  fOuterLayer = outerlayer;
  fDedx = dedx;
  fDedxCorr = dedxcorr;
  fNDoF = ndof;
  fChi2 = chi2;
  fVChi2 = vchi2;
  fNMVDRBarrelHits = nbr;
  fNMVDZBarrelHits = nbz;
  fNMVDUWheelHits = nwu;
  fNMVDVWheelHits = nwv;
  fDedxMVD = dedxmvd;

  fW = w;
  fPhiZero = phizero;
  fT = t;
  fDZero = dzero;
  fZZero = zzero;
  fCov_0 = 0;
  fCov_1 = 0;
  fCov_2 = 0;
  fCov_3 = 0;
  fCov_4 = 0;
  fCov_5 = 0;
  fCov_6 = 0;
  fCov_7 = 0;
  fCov_8 = 0;
  fCov_9 = 0;
  fCov_10 = 0;
  fCov_11 = 0;
  fCov_12 = 0;
  fCov_13 = 0;
  fCov_14 = 0;

  fUsedSuperLayersCut = kFALSE;
  fUsedHitsCut        = kFALSE;
  fUsedStereoHitsCut  = kFALSE;
  fZHCut              = kFALSE;
  fMVDHitsCut         = kFALSE;
  fAllCuts            = kFALSE;

  fImpactParameter                   = 0.0;
  f2DImpactParameter                 = 0.0;
  fImpactParameterSignificance       = 0.0;
  f2DImpactParameterSignificance     = 0.0;

}

//_____________________________________________________________

GTrack::~GTrack() {
  //
  // GTrack default destructor
  if ( gDebug ) cout << endl << "GTrack::~GTrack dtor called" << endl << endl;

}

//_____________________________________________________________

TString GTrack::PrintMessage(TString option) {
  //
  // return print message in one line
  if ( gDebug ) cout << endl << "GTrack::PrintMessage called" << endl << endl;

  TString dummy = "GTrack: ";
  
  dummy.Append(gInclude->FormatedChar(" id: ",5));
  dummy.Append(gInclude->FormatedInt(fID,3,0," "));
  dummy.Append(gInclude->FormatedChar(" charge: ",9));
  dummy.Append(gInclude->FormatedInt((Int_t)fCharge,3,0," "));
  dummy.Append(gInclude->FormatedChar(" p: ",4));
  dummy.Append(gInclude->FormatedDouble(this->Mag(),3,2));
  dummy.Append(gInclude->FormatedChar(" inner sl: ",11));
  dummy.Append(gInclude->FormatedInt(this->GetInnerLayer(),1,0," "));
  dummy.Append(gInclude->FormatedChar(" outer sl: ",11));
  dummy.Append(gInclude->FormatedInt(this->GetOuterLayer(),1,0," "));
  dummy.Append(gInclude->FormatedChar(" chi2: ",7));
  dummy.Append(gInclude->FormatedDouble(this->GetChi2(),4,2));
  dummy.Append(gInclude->FormatedChar(" z_h: ",6));
  dummy.Append(gInclude->FormatedDouble(fZZero,4,2));
  dummy.Append(gInclude->FormatedChar(" mvd hits: ",11));
  dummy.Append(gInclude->FormatedInt(this->GetMVDHits(),9,0," "));
  dummy.Append(gInclude->FormatedChar(" used super layer cut: ",22));
  dummy.Append(gInclude->FormatedBool(GetUsedSuperLayersCut()));
  dummy.Append(gInclude->FormatedChar(" used hits cut: ",16));
  dummy.Append(gInclude->FormatedBool(GetUsedHitsCut()));
  dummy.Append(gInclude->FormatedChar(" used stereo hits cut: ",22));
  dummy.Append(gInclude->FormatedBool(GetUsedStereoHitsCut()));
  dummy.Append(gInclude->FormatedChar(" used mvd hits cut: ",20));
  dummy.Append(gInclude->FormatedBool(GetMVDHitsCut()));
  dummy.Append(gInclude->FormatedChar(" z_h cut: ",10));
  dummy.Append(gInclude->FormatedBool(GetZHCut()));
  dummy.Append(gInclude->FormatedChar(" allcuts: ",11));
  dummy.Append(gInclude->FormatedBool(GetAllCuts()));



  dummy.Append("\n");

  return dummy;
}

//_____________________________________________________________

Bool_t GTrack::Print(TString option) {
  //
  // print message
  if ( gDebug ) cout << endl << "GTrack::Print called" << endl << endl;

  option.ToUpper();

  if ( option.Contains("OUTPUTLIST") ) {
    gLister->FillOutputList(this->PrintMessage(option));
  } else {
    cout << this->PrintMessage(option);
  }

  return kTRUE;

}
 
//_____________________________________________________________

void GTrack::SetCov(Int_t index, Double_t value) {
  //
  // set values of covariant matrix
  if ( gDebug ) cout << endl << "GTrack::Setcov called" << endl << endl;

  if ( index == 0 )
    fCov_0 = value;
  else if ( index == 1 )
    fCov_1 = value;
  else if ( index == 2 )
    fCov_2 = value;
  else if ( index == 3 )
    fCov_3 = value;
  else if ( index == 4 )
    fCov_4 = value;
  else if ( index == 5 )
    fCov_5 = value;
  else if ( index == 6 )
    fCov_6 = value;
  else if ( index == 7 )
    fCov_7 = value;
  else if ( index == 8 )
    fCov_8 = value;
  else if ( index == 9 )
    fCov_9 = value;
  else if ( index == 10 )
    fCov_10 = value;
  else if ( index == 11 )
    fCov_11 = value;
  else if ( index == 12 )
    fCov_12 = value;
  else if ( index == 13 )
    fCov_13 = value;
  else if ( index == 14 )
    fCov_14 = value;
}
 
//_____________________________________________________________

Double_t GTrack::GetCov(Int_t index) {
  //
  // get values of covariant matrix
  if ( gDebug ) cout << endl << "GTrack::Getcov called" << endl << endl;

  if ( index == 0 )
    return fCov_0;
  else if ( index == 1 )
    return fCov_1;
  else if ( index == 2 )
    return fCov_2;
  else if ( index == 3 )
    return fCov_3;
  else if ( index == 4 )
    return fCov_4;
  else if ( index == 5 )
    return fCov_5;
  else if ( index == 6 )
    return fCov_6;
  else if ( index == 7 )
    return fCov_7;
  else if ( index == 8 )
    return fCov_8;
  else if ( index == 9 )
    return fCov_9;
  else if ( index == 10 )
    return fCov_10;
  else if ( index == 11 )
    return fCov_11;
  else if ( index == 12 )
    return fCov_12;
  else if ( index == 13 )
    return fCov_13;
  else if ( index == 14 )
    return fCov_14;

  return 0.0;
}

//_____________________________________________________________

Bool_t GTrack::CalcImpactParameters(Double_t new_x_ref, Double_t new_x_ref_sigma,
				    Double_t new_y_ref, Double_t new_y_ref_sigma,
				    Double_t new_z_ref, Double_t new_z_ref_sigma, 
				    TLorentzVector *reference) {

  //
  // calc impact parameters in 3D and 2D from old helix parameters and new reference in x,y
  // taken from vcreref from vctrack
  //          c      --------------------------------------------------------
  //          c     Utility routine to rereference a helix
  //          c     IN  xold    = x reference
  //          c     "   yold    = y reference
  //          c     "   pold(5) = helix parameters ala vctrhl
  //          c                 (phi, Q/R, QDCA, Z, cot(theta))
  //          c     "   cold(15)= covariance matrix
  //          c     "   new_x_ref    = new x reference in the vicinity
  //          c     "   new_y_ref    = new y reference in the vicinity
  //          c     OUT pnew(5) = new helix parameters
  //          c         cnew(15)=new covariance matrix
  //          c
  //          c     Method: old helix recalculated assuming an axial magnetic
  //          c             field (i.e. no swim is done).
  //          c
  //          c     called by user  (GFHartner June12,2002 new at 70num3).
  //          c     --------------------------------------------------------
  //
  //  if ( gDebug ) 

  // only calculate impact parameter if reference != 0
  if ( reference != 0 ) { 

    Double_t CHARGE,RADIUS;
    Double_t A1O,A2O,A3O,SINA1O,COSA1O;
    Double_t COSALO,SINALO,XHO,YHO,XCEN,YCEN,RREF;
    Double_t COSALN,SINALN,COSA1N,SINA1N,A1N,A2N,QR,S;
    Double_t XHN,YHN,A3N;
    Double_t A4O,A5O,DAZ,A4N,A5N;
    Double_t C11,C12,C13,C14,C15,C22,C23,C24,C25,C33,C34,C35,C44,C45,C55;
    Double_t SS,D31,D33,D32;
    Double_t xold,yold;
    Double_t pnew[5],cnew[15];

    xold =0;
    yold =0;

    //C     TRANSPORT AXIAL HELIX PARAMETERS (NO SWIM)
    A1O=fPhiZero;
    A2O=fW*10;
    A3O=fDZero/10;
    A4O=fZZero/10;
    A5O=fT;
    //    cout <<" fPhiZero fW fDZero fT " << fPhiZero << fW << fDZero << fT << endl;
    SINA1O=TMath::Sin(A1O);
    COSA1O=TMath::Cos(A1O);
    if(A2O >= 0.0){
      CHARGE= 1.0 ;
    }else{
      CHARGE=-1.0;

    }
    RADIUS=CHARGE/A2O;
    COSALO=-CHARGE*SINA1O;
    SINALO= CHARGE*COSA1O;
    XHO=xold + A3O*SINA1O;
    YHO=yold - A3O*COSA1O;
    XCEN=XHO-RADIUS*COSALO;
    YCEN=YHO-RADIUS*SINALO;
    RREF=sqrt( pow((new_x_ref-XCEN),2) + pow((new_y_ref-YCEN),2) );
    COSALN=(new_x_ref-XCEN)/RREF;
    SINALN=(new_y_ref-YCEN)/RREF;
    COSA1N= CHARGE*SINALN;
    SINA1N=-CHARGE*COSALN;
    A1N =TMath::ATan2(SINA1N,COSA1N);
    if(A1N < 0.0) {A1N=A1N+TMath::TwoPi();}
    DAZ=A1N-A1O;
    if(DAZ < -TMath::Pi()){DAZ=DAZ+TMath::TwoPi();}
    if(DAZ > TMath::Pi()){DAZ=DAZ-TMath::TwoPi();}
    QR=CHARGE*RADIUS;
    S=-QR*DAZ;
    XHN=XHO+QR*(-SINA1N+SINA1O);
    YHN=YHO+QR*( COSA1N-COSA1O);
    A1N=A1O-S*A2O;
    A2N=A2O;
    A3N=(XHN-new_x_ref)*SINA1N - (YHN-new_y_ref)*COSA1N;
    A4N=A4O + S*A5O;
    A5N=A5O;

    pnew[0]=A1N;
    pnew[1]=A2N;
    pnew[2]=A3N;
    pnew[3]=A4N;
    pnew[4]=A5N;

    //C     TRANSPORT COVARIANCE
    C11=fCov_0;
    C12=fCov_1;
    C13=fCov_2;
    C14=fCov_3;
    C15=fCov_4;
    C22=fCov_5;
    C23=fCov_6;
    C24=fCov_7;
    C25=fCov_8;
    C33=fCov_9;
    C34=fCov_10;
    C35=fCov_11;
    C44=fCov_12;
    C45=fCov_13;
    C55=fCov_14;
    SS=S*S;
    cnew[ 0]=C11 - 2.*S*C12 + SS*C22;
    cnew[ 1]=C12 - S*C22;
    D31=(xold-new_x_ref)*COSA1N + (yold-new_y_ref)*SINA1N;
    D33= TMath::Cos(A2O*S);
    D32= (1.-D33)/A2O/A2O -S*D31 -S*(A3O+1./A2O)*TMath::Sin(A2O*S);
    cnew[ 2]=D31*(C11-S*C12)+D32*(C12-S*C22)+D33*(C13-S*C23);
    cnew[ 3]=C14 + S*C15 - S*(C24 + S*C25);
    cnew[ 4]=C15 - S*C25;
    cnew[ 5]=C22;
    cnew[ 6]=D31*C12 + D32*C22 + D33*C23;
    cnew[ 7]=C24 + S*C25;
    cnew[ 8]=C25;
    cnew[ 9]=D31*C11*D31 + 2.*D31*C12*D32 + 2.*D31*C13*D33
      +D32*C22*D32 + 2.*D32*C23*D33 + D33*C33*D33;
    cnew[10]= D31*(C14+S*C15) + D32*(C24+S*C25) + D33*(C34+S*C35);
    cnew[11]=D31*C15 + D32*C25 + D33*C35;
    cnew[12]=C44 + 2.*S*C45 + SS*C55;
    cnew[13]=C45 + S*C55;
    cnew[14]=C55;

    // calculate three vector of impact parameter
    TVector3 impact((pnew[2]*TMath::Sin(pnew[0])),(-pnew[2]*TMath::Cos(pnew[0])),pnew[3]);
    TVector2 impact2((pnew[2]*TMath::Sin(pnew[0])),(-pnew[2]*TMath::Cos(pnew[0])));

      // calculate scalar product from reference and impact-parameter
    // impact parameter is only calculated if chosen mjmatch exists, therefore a b-reference candidate exists
    Double_t sign = impact.Dot(reference->Vect());
    // normalize sign
    sign = sign / TMath::Abs(sign);

    // calculate sign in case of 2D impact parameter
    Double_t sign2d = impact2.X()*reference->Px()+impact2.Y()*reference->Py();
    // normalize sign2d
    sign2d = sign2d / TMath::Abs(sign2d);

  
    fImpactParameter   = sign*impact.Mag();

    f2DImpactParameter = sign2d*impact2.Mod();


    //_______________________________
    if ( gCards->GetMC()&& !(gCards->GetMCLF() && gCards->GetDoFake()) ){

      Double_t gau = gRandom->Gaus();
      
      Double_t ranuni = gRandom->Uniform();


      Double_t smerbw=Ranbw(ranuni)*( exp(3.0275-2.2336*this->Pt()) + 4.8768)*0.001;
      Double_t smergau=gau*0.0048781;


      f2DImpactParameter =  f2DImpactParameter + smerbw + smergau;
    }


    // for 3D, error of new reference not taken into account yet
    fImpactParameterSignificance = fImpactParameter / cnew[9] ;

    // 2D reference error

    TVector2 unit2 = impact2.Unit();

    Double_t delta_spot = TMath::Sqrt( (TMath::Power(unit2.X(),2) * TMath::Power(new_x_ref_sigma,2)) +
				       (TMath::Power(unit2.Y(),2) * TMath::Power(new_y_ref_sigma,2)) );
    Double_t tot_error = TMath::Sqrt( TMath::Power(delta_spot,2) + TMath::Power(cnew[9],2) );

    //     cout << " f2DImpactParameter " <<  f2DImpactParameter << endl;

    f2DImpactParameterSignificance = f2DImpactParameter / tot_error ;

  }

  return kTRUE;
}
  //_________________________________________________________________________

Double_t  GTrack::Ranbw(Double_t r){

//    Generates Random Numbers according to a Breit Wigner
//    with Gamma=1 and Mean=0
//    Input:  r = random numbre uniformly distributed between 0 and 1
//    Output: ranbw
//
//    The following parameters control the behavior:
//    eps:  precision
//    Zmin,Zmax max output values (the rest of the tails are not generated)
//
//    Massimo Corradi 17/12/2004
//    updated         17/02/2005
  
  
  Double_t eps;

  //    parameter (eps=1.E-7)
  eps=1.E-7;
  Double_t zmin;
  Double_t zmax;

  zmin=-50.;
  zmax= 50.;

  Double_t ranbw;
  Double_t z;
  Double_t z0;
  Double_t z1,fun,fmin,fmax,ovpi,f0,f1,dr;


    ovpi = 1./TMath::ACos(-1);
    fmin=0.5+ovpi*TMath::ATan(2*zmin);
    fmax=0.5+ovpi*TMath::ATan(2*zmax);

	if (r>=1.){
	  cout << "RANBW ERROR: r must be between 0 and 1 "<< r<< endl;

	  ranbw=zmax;
	    return ranbw;
	}
	else if (r<=0.){
	  cout << "RANBW ERROR: r must be between 0 and 1 "<< r<<endl;
	  ranbw=zmin;
	  return ranbw;
	}
      
	r=r*(fmax-fmin)+fmin;
	z0=zmin;
	z1=zmax;
	z=0.;

   fun=0.5+ovpi*atan(2*z);
   dr=fun-r;

   while((dr>eps)||(dr<-eps)){

   fun=0.5+ovpi*atan(2*z);
   dr=fun-r;

   // find z0 and z1
   if (dr>eps){
     z1=z;
     z=z0+0.5*(z1-z0);
     
   }else if (dr < -eps){
       z0=z;
       z=z0+0.5*(z1-z0);       
     }
   }

   if (dr> 0.){
     z1=z;
     f1=fun;
     f0=0.5+ovpi*atan(2*z0);
   }
   else{
     z0=z;
     f0=fun;
     f1=0.5+ovpi*atan(2*z1);
   }
  

    // then interpolate
   ranbw=z0+(r-f0)*(z1-z0)/(f1-f0);
   return ranbw;

}
