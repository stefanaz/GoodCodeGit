//
// GConnectTree.cxx
//
// $Author: rubinsky $
// $Date: 2006/10/20 09:36:52 $
// $Revision: 1.35 $
//

#include <GConnectTree.h>
#include <iostream>

#ifndef GUT_GInclude
#include <GInclude.h>
#endif

using namespace std;

#ifndef __CINT__
ClassImp(GConnectTree)
#endif

  GConnectTree *gData = 0;

//_____________________________________________________________
// GConnectTree
// Connection to root tree from NTuple using Tree->MakeClass()
//
//
GConnectTree::GConnectTree(TChain *chain) : TObject() {
  //
  // GConnectTree default constructor
  if ( gDebug ) cout << "GConnectTree::GConnectTree ctor called" << endl;

  // initialize variables
  gData = this;
  fOK   = kFALSE;
  new_mubacdca = kFALSE;

  // init chain
  fOK = this->Init(chain);

}

//_____________________________________________________________

GConnectTree::~GConnectTree() {
  //
  // GConnectTree default destructor
  if ( gDebug ) cout << "GConnectTree::~GConnectTree dtor called" << endl;

}

//_____________________________________________________________

Bool_t GConnectTree::Init(TChain *chain) {
  //
  // Init chain, connect to branches
  if ( gDebug ) cout << "GConnectTree::Init called" << endl;

  // set branches according to flags
  // possible future setting by cardsfile
  Bool_t BAC         = kTRUE;
  Bool_t BACMAT      = kTRUE;
  Bool_t CAL         = kTRUE;
  Bool_t FCALIR      = kTRUE;
  Bool_t RCALIR      = kTRUE;
  Bool_t EVENT       = kTRUE;
  Bool_t TAKEINFO    = kTRUE;
  Bool_t GMUON       = kTRUE;
  Bool_t GMU_JET     = kFALSE;
  Bool_t GMU_JET_NEW = kTRUE;
  Bool_t GMU_MC      = kTRUE;
  Bool_t ktJETS_A    = kTRUE;
  Bool_t ktJETS_B    = kTRUE;
  Bool_t ktJETS_C    = kTRUE;
  Bool_t ktJETS_D    = kTRUE;
  Bool_t MCSUMS      = kFALSE;
  Bool_t MCJETS      = kFALSE;
  Bool_t MCKINE      = kFALSE;
  Bool_t FMCKIN      = kFALSE;
  Bool_t MCVTX       = kFALSE;
  Bool_t MUON        = kFALSE;
  Bool_t FMU_MPM     = kFALSE;
  Bool_t FMUmfrtz    = kFALSE;
  Bool_t MV          = kFALSE;
  Bool_t SIRA        = kTRUE;
  Bool_t SI_KIN      = kTRUE;
  Bool_t TRIGGER     = kTRUE;
  Bool_t VERTEX      = kTRUE;
  Bool_t BSPOT       = kTRUE;
  Bool_t ZUFOS       = kTRUE;
  Bool_t Tracking    = kTRUE;
  Bool_t Trk_vtx     = kTRUE;
  Bool_t Trk_qual    = kTRUE;
  Bool_t Trk_MVD     = kTRUE;
  Bool_t Trk_imp     = kTRUE;
  Bool_t SECVTX      = kTRUE;
  Bool_t VCTRHLa     = kFALSE;
  Bool_t BREMAT      = kFALSE;
  Bool_t OWN_MC      = kFALSE;
  Bool_t OWN_MC_JETS = kFALSE;
  Bool_t OWN         = kTRUE;
  
  //default: use PHP jets
  SetDISPHPJets(1);
  if ( gCards->GetMC() ) {
    MCSUMS = kTRUE;
    //    MCJETS = kTRUE;
    MCKINE = kTRUE;
    MCVTX  = kTRUE;
    if ( gCards->GetMCOwn() )
      OWN_MC = kTRUE;
    if ( gCards->GetFMCK() )
      FMCKIN = kTRUE;
    if ( gCards->GetMCOwnJets() )
      OWN_MC_JETS = kTRUE;
  }
//    if (  gCards->GetNewNtuple() ){
//      GMU_JET_NEW = kTRUE;
//    }
//    if (GMU_JET_NEW) {
//      GMU_JET = kFALSE;
//    }

  if( gCards -> GetHERA1() ){ 

    if ( BAC ) {
      chain->SetBranchAddress("bac_etot",&bac_etot);
      chain->SetBranchAddress("bac_etot_o2r",&bac_etot_o2r);
      chain->SetBranchAddress("bac_npad",&bac_npad);
      chain->SetBranchAddress("bac_npad_o2r",&bac_npad_o2r);
      chain->SetBranchAddress("bac_et",&bac_et);
      chain->SetBranchAddress("bac_px",&bac_px);
      chain->SetBranchAddress("bac_py",&bac_py);
      chain->SetBranchAddress("nbacmu",&nbacmu);
      chain->SetBranchAddress("mubac_xyz",mubac_xyz);
      chain->SetBranchAddress("mubac_dxyz",mubac_dxyz);
      chain->SetBranchAddress("mubac_cos",mubac_cos);
      chain->SetBranchAddress("mubac_dcos",mubac_dcos);
      chain->SetBranchAddress("mubac_eloss",mubac_eloss);
      chain->SetBranchAddress("mubac_deloss",mubac_deloss);
      chain->SetBranchAddress("mubac_unit",mubac_unit);
      chain->SetBranchAddress("mubac_dim",mubac_dim);
      chain->SetBranchAddress("mubac_quality",mubac_quality);
      chain->SetBranchAddress("ahit",ahit);
      chain->SetBranchAddress("pad",pad);
    }

    if ( CAL ) {
      chain->SetBranchAddress("cal_px",&cal_px);
      chain->SetBranchAddress("cal_py",&cal_py);
      chain->SetBranchAddress("cal_pz",&cal_pz);
      chain->SetBranchAddress("cal_e",&cal_e);
      chain->SetBranchAddress("cal_et",&cal_et);
      chain->SetBranchAddress("cal_empz",&cal_empz);
      chain->SetBranchAddress("cal_pt",&cal_pt);
      chain->SetBranchAddress("cal_phi",&cal_phi);
      chain->SetBranchAddress("remc",remc);
      chain->SetBranchAddress("bemc",bemc);
      chain->SetBranchAddress("femc",femc);
      chain->SetBranchAddress("rhac",rhac);
      chain->SetBranchAddress("bhac",bhac);
      chain->SetBranchAddress("fhac",fhac);
      chain->SetBranchAddress("bhac2",bhac2);
      chain->SetBranchAddress("fhac2",fhac2);
      chain->SetBranchAddress("nfemc",&nfemc);
      chain->SetBranchAddress("nfhac1",&nfhac1);
      chain->SetBranchAddress("nfhac2",&nfhac2);
      chain->SetBranchAddress("nbemc",&nbemc);
      chain->SetBranchAddress("nbhac1",&nbhac1);
      chain->SetBranchAddress("nbhac2",&nbhac2);
      chain->SetBranchAddress("nremc",&nremc);
      chain->SetBranchAddress("nrhac",&nrhac);
      chain->SetBranchAddress("cal_tf",&cal_tf);
      chain->SetBranchAddress("cal_tb",&cal_tb);
      chain->SetBranchAddress("cal_tr",&cal_tr);
      chain->SetBranchAddress("cal_tg",&cal_tg);
      chain->SetBranchAddress("cal_tf",&cal_tf);
      chain->SetBranchAddress("cal_tb",&cal_tb);
      chain->SetBranchAddress("cal_tr",&cal_tr);
      chain->SetBranchAddress("cal_tg",&cal_tg);
      //     chain->SetBranchAddress("cal_tf_e",&cal_tf_e);
      //     chain->SetBranchAddress("cal_tb_e",&cal_tb_e);
      //     chain->SetBranchAddress("cal_tr_e",&cal_tr_e);
      //     chain->SetBranchAddress("cal_tg_e",&cal_tg_e);
      //     chain->SetBranchAddress("cal_tf_n",&cal_tf_n);
      //     chain->SetBranchAddress("cal_tb_n",&cal_tb_n);
      //     chain->SetBranchAddress("cal_tr_n",&cal_tr_n);
      //     chain->SetBranchAddress("cal_tg_n",&cal_tg_n);
      chain->SetBranchAddress("etamax_ce",&etamax_ce);
      chain->SetBranchAddress("etamax_ce4",&etamax_ce4);
      chain->SetBranchAddress("cal_et10",&cal_et10);
      chain->SetBranchAddress("mtrknoe_pi",&mtrknoe_pi);
      chain->SetBranchAddress("mtrknoe_k",&mtrknoe_k);
      chain->SetBranchAddress("e_hk",&e_hk);
      chain->SetBranchAddress("unmen_pi",&unmen_pi);
      chain->SetBranchAddress("unmen_k",&unmen_k);
      chain->SetBranchAddress("sparkf",&sparkf);
    }

  if ( FCALIR ) {
    chain->SetBranchAddress("pex1ir",pex1ir);
    chain->SetBranchAddress("et1ir",&et1ir);
    chain->SetBranchAddress("etex1ir",&etex1ir);
    chain->SetBranchAddress("pex2ir",pex2ir);
    chain->SetBranchAddress("et2ir",&et2ir);
    chain->SetBranchAddress("etex2ir",&etex2ir);
  }

  if ( RCALIR ) {
    chain->SetBranchAddress("percir",percir);
    chain->SetBranchAddress("etrcir",&etrcir);
  }

  if ( EVENT ) {
    chain->SetBranchAddress("runnr",&runnr);
    chain->SetBranchAddress("eventnr",&eventnr);
  }

  if ( GMUON ) {
    chain->SetBranchAddress("nmu",&nmu);
    chain->SetBranchAddress("muqual",muqual);
    chain->SetBranchAddress("mucharge",mucharge);
    chain->SetBranchAddress("mupt",mupt);
    chain->SetBranchAddress("muth",muth);
    chain->SetBranchAddress("muph",muph);
    chain->SetBranchAddress("mup",mup);
    chain->SetBranchAddress("muperr",muperr);
    chain->SetBranchAddress("mutrfl",mutrfl);
    chain->SetBranchAddress("mutrid",mutrid);
    chain->SetBranchAddress("muvcid",muvcid);
    chain->SetBranchAddress("muztid",muztid);
    chain->SetBranchAddress("mustid",mustid);
    chain->SetBranchAddress("muvtxfl",muvtxfl);
    chain->SetBranchAddress("muvtxid",muvtxid);
    chain->SetBranchAddress("muglomu",muglomu);
    chain->SetBranchAddress("mubremat",mubremat);
    chain->SetBranchAddress("mumubac",mumubac);
    chain->SetBranchAddress("mumamma",mumamma);
    chain->SetBranchAddress("mumpmat",mumpmat);
    chain->SetBranchAddress("mumufo",mumufo);
    chain->SetBranchAddress("mumip",mumip);
    chain->SetBranchAddress("mumv",mumv);
    chain->SetBranchAddress("mucalfl",mucalfl);
    chain->SetBranchAddress("mucalene",mucalene);
    chain->SetBranchAddress("muhac2",muhac2);
    chain->SetBranchAddress("muzufid",muzufid);
    chain->SetBranchAddress("muisol",    muisol	 );
    chain->SetBranchAddress("munis",	 munis	 );
    chain->SetBranchAddress("muisdrmip", muisdrmip);
    chain->SetBranchAddress("muisetmip", muisetmip);
    chain->SetBranchAddress("muistumip", muistumip);
    chain->SetBranchAddress("mupmip",mupmip);
    chain->SetBranchAddress("muhene",muhene);
    chain->SetBranchAddress("mutime",mutime);
    chain->SetBranchAddress("muchfl",muchfl);
    chain->SetBranchAddress("muchid",muchid);
    chain->SetBranchAddress("mupmat",mupmat);

    // change in variable mubacfl
    // in new ntuples, it is called mubacdca and
    // changed its type from int to float_t
    // check if mubacfl or mubacdca is filled in ntuple
    // set boolean
    // spool variabled in corresponding variables
    // let return funtion choose which one to return
    // return is always float
    // in case of mubacfl, cast of int to float
    if ( chain->GetBranch("mubacdca") ) {
      new_mubacdca = kTRUE;
    } else if ( chain->GetBranch("mubacfl") ) {
      new_mubacdca = kFALSE;
    } else {
      new_mubacdca = kFALSE;
    }

    if ( new_mubacdca ) {
      chain->SetBranchAddress("mubacdca",mubacdca);
    } else {
      chain->SetBranchAddress("mubacfl",mubacfl);
    }

    chain->SetBranchAddress("mubacid",mubacid);
    chain->SetBranchAddress("mudxy",mudxy);
    chain->SetBranchAddress("mudz",mudz);
    if ( gCards->GetdCache() ) {
      chain->SetBranchAddress("mundof",mundof);
      chain->SetBranchAddress("muz",muz);
      chain->SetBranchAddress("muprec",muprec);
    } else {
      for ( Int_t i = 0; i < 20; ++i ) {
	mundof[i] = 0;
	muz[i] = 0.0;
	muprec[i] = 0.0;
      }
    }

  }

  if ( GMU_JET ) {
    chain->SetBranchAddress("mujetfl",mujetfl);
    chain->SetBranchAddress("mujetid",mujetid);
    chain->SetBranchAddress("mujetdr",mujetdr);
    chain->SetBranchAddress("mujetpt",mujetpt);
    chain->SetBranchAddress("mujetdr2",mujetdr2);
    chain->SetBranchAddress("mujetpt2",mujetpt2);
    chain->SetBranchAddress("muhjet_id",muhjet_id);
  }
  if ( GMU_JET_NEW ) {
    chain->SetBranchAddress("mujetfl_a",mujetfl_a);
    chain->SetBranchAddress("mujetid_a",mujetid_a);
    chain->SetBranchAddress("mujetdr_a",mujetdr_a);
    chain->SetBranchAddress("mujetpt_a",mujetpt_a);
    chain->SetBranchAddress("mujetdr2_a",mujetdr2_a);
    chain->SetBranchAddress("mujetpt2_a",mujetpt2_a);

    chain->SetBranchAddress("mujetfl_b",mujetfl_b);
    chain->SetBranchAddress("mujetid_b",mujetid_b);
    chain->SetBranchAddress("mujetdr_b",mujetdr_b);
    chain->SetBranchAddress("mujetpt_b",mujetpt_b);
    chain->SetBranchAddress("mujetdr2_b",mujetdr2_b);
    chain->SetBranchAddress("mujetpt2_b",mujetpt2_b);

    chain->SetBranchAddress("mujetfl_c",mujetfl_c);
    chain->SetBranchAddress("mujetid_c",mujetid_c);
    chain->SetBranchAddress("mujetdr_c",mujetdr_c);
    chain->SetBranchAddress("mujetpt_c",mujetpt_c);
    chain->SetBranchAddress("mujetdr2_c",mujetdr2_c);
    chain->SetBranchAddress("mujetpt2_c",mujetpt2_c);

    chain->SetBranchAddress("mujetfl_d",mujetfl_d);
    chain->SetBranchAddress("mujetid_d",mujetid_d);
    chain->SetBranchAddress("mujetdr_d",mujetdr_d);
    chain->SetBranchAddress("mujetpt_d",mujetpt_d);
    chain->SetBranchAddress("mujetdr2_d",mujetdr2_d);
    chain->SetBranchAddress("mujetpt2_d",mujetpt2_d);
  }

  if ( GMU_MC ) {
    chain->SetBranchAddress("muick",muick);
    chain->SetBranchAddress("mupartyp",mupartyp);
    chain->SetBranchAddress("mumc_p",mumc_p);
    chain->SetBranchAddress("mudirtyp",mudirtyp);
    chain->SetBranchAddress("mumc_d",mumc_d);
    chain->SetBranchAddress("muqtyp",muqtyp);
    chain->SetBranchAddress("mumc_q",mumc_q);
    chain->SetBranchAddress("mutruefl",mutruefl);
    chain->SetBranchAddress("mudecdist",mudecdist);
  }
  if ( FMCKIN ) {
    chain->SetBranchAddress("npart",&npart);
    chain->SetBranchAddress("part_id",part_id);
    chain->SetBranchAddress("part_prt",part_prt);
    chain->SetBranchAddress("part_p",part_p);
  }

  if ( ktJETS_A ) {
    chain->SetBranchAddress("kt_njet_a",&kt_njet_a);
    chain->SetBranchAddress("kt_etjet_a",kt_etjet_a);
    chain->SetBranchAddress("kt_etajet_a",kt_etajet_a);
    chain->SetBranchAddress("kt_phijet_a",kt_phijet_a);
    chain->SetBranchAddress("kt_masjet_a",kt_masjet_a);
  }

  if ( ktJETS_B ) {
    chain->SetBranchAddress("kt_njet_b",&kt_njet_b);
    chain->SetBranchAddress("kt_etjet_b",kt_etjet_b);
    chain->SetBranchAddress("kt_etajet_b",kt_etajet_b);
    chain->SetBranchAddress("kt_phijet_b",kt_phijet_b);
    chain->SetBranchAddress("kt_masjet_b",kt_masjet_b);
  }

  if ( ktJETS_C ) {
    chain->SetBranchAddress("kt_njet_c",&kt_njet_c);
    chain->SetBranchAddress("kt_etjet_c",kt_etjet_c);
    chain->SetBranchAddress("kt_etajet_c",kt_etajet_c);
    chain->SetBranchAddress("kt_phijet_c",kt_phijet_c);
    chain->SetBranchAddress("kt_masjet_c",kt_masjet_c);
  }

  if ( ktJETS_D ) {
    chain->SetBranchAddress("kt_njet_d",&kt_njet_d);
    chain->SetBranchAddress("kt_etjet_d",kt_etjet_d);
    chain->SetBranchAddress("kt_etajet_d",kt_etajet_d);
    chain->SetBranchAddress("kt_phijet_d",kt_phijet_d);
    chain->SetBranchAddress("kt_masjet_d",kt_masjet_d);
  }

  if ( MCSUMS ) {
    chain->SetBranchAddress("mc_ez",&mc_ez);
    chain->SetBranchAddress("mc_esum",&mc_esum);
    chain->SetBranchAddress("mc_etcone",&mc_etcone);
    chain->SetBranchAddress("mc_ercal",&mc_ercal);
  }

  if ( MCJETS ) {
    chain->SetBranchAddress("mc_njet",&mc_njet);
    chain->SetBranchAddress("mc_etj",mc_etj);
    chain->SetBranchAddress("mc_rapj",mc_rapj);
    chain->SetBranchAddress("mc_phij",mc_phij);
    chain->SetBranchAddress("mc_pxj",mc_pxj);
    chain->SetBranchAddress("mc_pyj",mc_pyj);
    chain->SetBranchAddress("mc_pzj",mc_pzj);
    chain->SetBranchAddress("mc_ej",mc_ej);
  }

  if ( MCKINE ) {
    chain->SetBranchAddress("mc_el",&mc_el);
    chain->SetBranchAddress("mc_ep",&mc_ep);
    chain->SetBranchAddress("mc_x",&mc_x);
    chain->SetBranchAddress("mc_y",&mc_y);
    chain->SetBranchAddress("mc_q2",&mc_q2);
    chain->SetBranchAddress("mc_mu",&mc_mu);
    chain->SetBranchAddress("mc_pt",&mc_pt);
    chain->SetBranchAddress("mc_xpro",&mc_xpro);
    chain->SetBranchAddress("mc_xgam",&mc_xgam);
    chain->SetBranchAddress("mc_xpom",&mc_xpom);
    chain->SetBranchAddress("mc_beta",&mc_beta);
    chain->SetBranchAddress("mc_t",&mc_t);
    chain->SetBranchAddress("mc_idl",&mc_idl);
    chain->SetBranchAddress("mc_pidl",&mc_pidl);
    chain->SetBranchAddress("mc_pidp",&mc_pidp);
    chain->SetBranchAddress("mc_idfsl",&mc_idfsl);
    chain->SetBranchAddress("mc_pfsl",mc_pfsl);
    chain->SetBranchAddress("mc_pfsph",mc_pfsph);
    chain->SetBranchAddress("mc_vtx",mc_vtx);
    chain->SetBranchAddress("mc_ichnn",&mc_ichnn);
  }

  if ( MCVTX ) {
    chain->SetBranchAddress("mcvtx",mcvtx);
  }

  if ( MUON ) {
    chain->SetBranchAddress("nomu",&nomu);
    chain->SetBranchAddress("bmuon1",&bmuon1);
    chain->SetBranchAddress("bmuon2",&bmuon2);
    chain->SetBranchAddress("bmnrmips",&bmnrmips);
    chain->SetBranchAddress("bmmmtrk",&bmmmtrk);
    chain->SetBranchAddress("muonf1",&muonf1);
    chain->SetBranchAddress("muonf2",&muonf2);
    chain->SetBranchAddress("mupt1",&mupt1);
    chain->SetBranchAddress("muth1",&muth1);
    chain->SetBranchAddress("muph1",&muph1);
    chain->SetBranchAddress("mupt2",&mupt2);
    chain->SetBranchAddress("muth2",&muth2);
    chain->SetBranchAddress("muph2",&muph2);
    chain->SetBranchAddress("fmntrk",&fmntrk);
    chain->SetBranchAddress("fmntrp",&fmntrp);
    chain->SetBranchAddress("fmangr",&fmangr);
    chain->SetBranchAddress("fmrecp",&fmrecp);
    chain->SetBranchAddress("fmmatch",&fmmatch);
    chain->SetBranchAddress("mbchi2",mbchi2);
    chain->SetBranchAddress("mbp",mbp);
    chain->SetBranchAddress("mbdca",mbdca);
    chain->SetBranchAddress("mbtrfl",mbtrfl);
  }

  if ( FMU_MPM) {
    chain->SetBranchAddress("nfmu",&nfmu);
    chain->SetBranchAddress("fmux",fmux);
    chain->SetBranchAddress("fmuy",fmuy);
    chain->SetBranchAddress("fmuz",fmuz);
    chain->SetBranchAddress("fmuchi",fmuchi);
    chain->SetBranchAddress("fmuprob",fmuprob);
    chain->SetBranchAddress("fmuti",fmuti);
    chain->SetBranchAddress("fmufi",fmufi);
    chain->SetBranchAddress("fmutqor",fmutqor);
    chain->SetBranchAddress("fmutz",fmutz);
    chain->SetBranchAddress("fmutqd",fmutqd);
    chain->SetBranchAddress("fmutchi",fmutchi);
    chain->SetBranchAddress("fmutndf",fmutndf);
    chain->SetBranchAddress("fmutksw",fmutksw);
  }

  if ( FMUmfrtz ) {
    chain->SetBranchAddress("nmf",&nmf);
    chain->SetBranchAddress("mfx",mfx);
    chain->SetBranchAddress("mfy",mfy);
    chain->SetBranchAddress("mfz",mfz);
    chain->SetBranchAddress("mfvx",mfvx);
    chain->SetBranchAddress("mfvy",mfvy);
    chain->SetBranchAddress("mfqop",mfqop);
    chain->SetBranchAddress("mfo",mfo);
    chain->SetBranchAddress("mfndf",mfndf);
    chain->SetBranchAddress("mfpro",mfpro);
    chain->SetBranchAddress("mfndff",mfndff);
    chain->SetBranchAddress("mfprof",mfprof);
    chain->SetBranchAddress("mfhdc",mfhdc);
    chain->SetBranchAddress("mfhlt",mfhlt);
    chain->SetBranchAddress("fmusid",fmusid);
    chain->SetBranchAddress("fmushr",fmushr);
    chain->SetBranchAddress("fmusrchi",fmusrchi);
    chain->SetBranchAddress("fmusnr",fmusnr);
    chain->SetBranchAddress("fmushp",fmushp);
    chain->SetBranchAddress("fmusnp",fmusnp);
    chain->SetBranchAddress("fmusp",fmusp);
    chain->SetBranchAddress("fmusthe",fmusthe);
    chain->SetBranchAddress("fmusphi",fmusphi);
  }

  if ( MV ) {
    chain->SetBranchAddress("umv_ncmuo",&umv_ncmuo);
    chain->SetBranchAddress("umv_trkmuo",umv_trkmuo);
    chain->SetBranchAddress("umv_trrmuo",umv_trrmuo);
    chain->SetBranchAddress("umv_trnmuo",umv_trnmuo);
    chain->SetBranchAddress("umv_trqmuo",umv_trqmuo);
    chain->SetBranchAddress("umv_tobr",umv_tobr);
    chain->SetBranchAddress("umv_trmmuo",umv_trmmuo);
    chain->SetBranchAddress("umv_trtmuo",umv_trtmuo);
    chain->SetBranchAddress("umv_trpmuo",umv_trpmuo);
    chain->SetBranchAddress("umv_trcmuo",umv_trcmuo);
    chain->SetBranchAddress("umv_tremuo",umv_tremuo);
    chain->SetBranchAddress("umv_trdmuo",umv_trdmuo);
    chain->SetBranchAddress("umv_timuo",umv_timuo);
    chain->SetBranchAddress("umv_xcmuo",umv_xcmuo);
    chain->SetBranchAddress("umv_ycmuo",umv_ycmuo);
    chain->SetBranchAddress("umv_zcmuo",umv_zcmuo);
    chain->SetBranchAddress("umv_heemuo",umv_heemuo);
    chain->SetBranchAddress("umv_hexmuo",umv_hexmuo);
    chain->SetBranchAddress("umv_heymuo",umv_heymuo);
    chain->SetBranchAddress("umv_hezmuo",umv_hezmuo);
    chain->SetBranchAddress("umv_prmuo",umv_prmuo);
    chain->SetBranchAddress("umv_efmuo",umv_efmuo);
    chain->SetBranchAddress("umv_comuo",umv_comuo);
    chain->SetBranchAddress("umv_pumuo",umv_pumuo);
    chain->SetBranchAddress("umv_prcmuo",umv_prcmuo);
    chain->SetBranchAddress("umv_efcmuo",umv_efcmuo);
    chain->SetBranchAddress("umv_cocmuo",umv_cocmuo);
    chain->SetBranchAddress("umv_pucmuo",umv_pucmuo);
    chain->SetBranchAddress("umv_ecamuo",umv_ecamuo);
    chain->SetBranchAddress("uex_calmuo",uex_calmuo);
    chain->SetBranchAddress("uey_calmuo",uey_calmuo);
    chain->SetBranchAddress("uez_calmuo",uez_calmuo);
    chain->SetBranchAddress("uet_calmuo",uet_calmuo);
  }

  if ( SIRA) {
    chain->SetBranchAddress("sincand",&sincand);
    chain->SetBranchAddress("sierror",&sierror);
    chain->SetBranchAddress("siprob",siprob);
    chain->SetBranchAddress("sipos",sipos);
    chain->SetBranchAddress("sicalpos",sicalpos);
    chain->SetBranchAddress("sicalene",sicalene);
    chain->SetBranchAddress("siein",siein);
    chain->SetBranchAddress("sienin",sienin);
    chain->SetBranchAddress("siecorr",siecorr);
    chain->SetBranchAddress("sith",sith);
    chain->SetBranchAddress("siph",siph);
    chain->SetBranchAddress("sipt",sipt);
    chain->SetBranchAddress("sixdet",sixdet);
    chain->SetBranchAddress("siydet",siydet);
  }

  if ( SI_KIN ) {
    chain->SetBranchAddress("sixel",sixel);
    chain->SetBranchAddress("siyel",siyel);
    chain->SetBranchAddress("siq2el",siq2el);
    chain->SetBranchAddress("sixda",sixda);
    chain->SetBranchAddress("siyda",siyda);
    chain->SetBranchAddress("siq2da",siq2da);
    chain->SetBranchAddress("sixda_cell",sixda_cell);
    chain->SetBranchAddress("siyda_cell",siyda_cell);
    chain->SetBranchAddress("siq2da_cell",siq2da_cell);
    chain->SetBranchAddress("sixjb",sixjb);
    chain->SetBranchAddress("siyjb",siyjb);
    chain->SetBranchAddress("siq2jb",siq2jb);
    chain->SetBranchAddress("sixjb_cell",sixjb_cell);
    chain->SetBranchAddress("siyjb_cell",siyjb_cell);
    chain->SetBranchAddress("siq2jb_cell",siq2jb_cell);
  }

  if ( TRIGGER ) {
    chain->SetBranchAddress("fltw",fltw);
    chain->SetBranchAddress("fltpsw",fltpsw);
    chain->SetBranchAddress("fltfl",&fltfl);
    chain->SetBranchAddress("gslt_global",&gslt_global);
    chain->SetBranchAddress("sltw",sltw);
    chain->SetBranchAddress("sltupw",sltupw);
    chain->SetBranchAddress("tltw",tltw);
    chain->SetBranchAddress("dstw",dstw);
    //   chain->SetBranchAddress("fltfcw",fltfcw);
    //   chain->SetBranchAddress("fltpsfcw",fltpsfcw);
  }

  if ( VERTEX ) {
    chain->SetBranchAddress("ntrkvtx",&ntrkvtx);
    chain->SetBranchAddress("xvtx",&xvtx);
    chain->SetBranchAddress("yvtx",&yvtx);
    chain->SetBranchAddress("zvtx",&zvtx);
    chain->SetBranchAddress("chivtx",&chivtx);
    chain->SetBranchAddress("nsecvtx",&nsecvtx);
    chain->SetBranchAddress("xsecvtx",xsecvtx);
    chain->SetBranchAddress("ysecvtx",ysecvtx);
    chain->SetBranchAddress("zsecvtx",zsecvtx);
    chain->SetBranchAddress("chisecvtx",chisecvtx);
    chain->SetBranchAddress("fetatr",&fetatr);
    chain->SetBranchAddress("betatr",&betatr);
    chain->SetBranchAddress("pt_tr",&pt_tr);
    chain->SetBranchAddress("empz_tr_pi",&empz_tr_pi);
    chain->SetBranchAddress("et_tr",&et_tr);
    chain->SetBranchAddress("e_tr_pi",&e_tr_pi);
    chain->SetBranchAddress("phi_tr",&phi_tr);
    chain->SetBranchAddress("zvtx_fcal",&zvtx_fcal);
    chain->SetBranchAddress("fcal_nrgoodcells",&fcal_nrgoodcells);
    chain->SetBranchAddress("fcal_vzerr",&fcal_vzerr);
  }

  if ( ZUFOS ) {
    chain->SetBranchAddress("v_h_px_zu",&v_h_px_zu);
    chain->SetBranchAddress("v_h_py_zu",&v_h_py_zu);
    chain->SetBranchAddress("v_h_pz_zu",&v_h_pz_zu);
    chain->SetBranchAddress("v_h_e_zu",&v_h_e_zu);
    chain->SetBranchAddress("etamax_zu",&etamax_zu);
    chain->SetBranchAddress("etamax_zu4",&etamax_zu4);
    chain->SetBranchAddress("fgap",&fgap);
    chain->SetBranchAddress("bgap",&bgap);
    chain->SetBranchAddress("nzufos",&nzufos);
    chain->SetBranchAddress("tufo",tufo);
    chain->SetBranchAddress("zufo_bsp",zufo_bsp);
    chain->SetBranchAddress("zufo",zufo);
    chain->SetBranchAddress("zufoeemc",zufoeemc);
  }

  if ( Tracking ) {
    chain->SetBranchAddress("trk_ntracks",&trk_ntracks);
    chain->SetBranchAddress("trk_type",trk_type);
    chain->SetBranchAddress("ntrack_type",ntrack_type);
    chain->SetBranchAddress("def_trk_type",&def_trk_type);
    chain->SetBranchAddress("trk_id",trk_id);
    chain->SetBranchAddress("trk_id2",trk_id2);
    chain->SetBranchAddress("trk_px",trk_px);
    chain->SetBranchAddress("trk_py",trk_py);
    chain->SetBranchAddress("trk_pz",trk_pz);
    chain->SetBranchAddress("trk_charge",trk_charge);
  }

  if ( Trk_vtx ) {
    chain->SetBranchAddress("trk_vtx",trk_vtx);
    chain->SetBranchAddress("trk_prim_vtx",trk_prim_vtx);
    chain->SetBranchAddress("trk_sec_vtx",trk_sec_vtx);
    chain->SetBranchAddress("trk_vxid",trk_vxid);
  }

  if ( Trk_qual ) {
    chain->SetBranchAddress("trk_endpos",trk_endpos);
    chain->SetBranchAddress("trk_nzbyt",trk_nzbyt);
    chain->SetBranchAddress("trk_naxial",trk_naxial);
    chain->SetBranchAddress("trk_nstereo",trk_nstereo);
    chain->SetBranchAddress("trk_ndof",trk_ndof);
    chain->SetBranchAddress("trk_layinner",trk_layinner);
    chain->SetBranchAddress("trk_layouter",trk_layouter);
    chain->SetBranchAddress("trk_dedxctd",trk_dedxctd);
    chain->SetBranchAddress("trk_dedxctdcr",trk_dedxctdcr);
    chain->SetBranchAddress("trk_chi2",trk_chi2);
    chain->SetBranchAddress("trk_vchi2",trk_vchi2);
  }

  if ( Trk_MVD ) {
    chain->SetBranchAddress("trk_nbr",trk_nbr);
    chain->SetBranchAddress("trk_nbz",trk_nbz);
    chain->SetBranchAddress("trk_nwu",trk_nwu);
    chain->SetBranchAddress("trk_nwv",trk_nwv);
    chain->SetBranchAddress("trk_dedxmvd",trk_dedxmvd);
    
    if ( !gCards->GetNewNtuple()&& gCards->GetMVDActivate()) {
      chain->SetBranchAddress("trk_w",trk_w);
      chain->SetBranchAddress("trk_phizero",trk_phizero);
      chain->SetBranchAddress("trk_t",trk_t);
      chain->SetBranchAddress("trk_dzero",trk_dzero);
      chain->SetBranchAddress("trk_zzero",trk_zzero);
      chain->SetBranchAddress("trk_cov",trk_cov);
    } else if ( gCards->GetNewNtuple() && gCards->GetMVDActivate() ) {
      chain->SetBranchAddress("trk_helpar",trk_helpar);
      chain->SetBranchAddress("trk_covmat",trk_covmat);
    }  else {
      for ( Int_t i = 0; i < 300; ++i ) {
	trk_w[i] = 0.0;
	trk_phizero[i] = 0.0;
	trk_t[i] = 0.0;
	trk_dzero[i] = 0.0;
	trk_zzero[i] = 0.0;
	for ( Int_t j = 0; j < 15; ++j)
	  trk_cov[i][j] = 0.0;
      }
    }
  }

  if ( VCTRHLa ) {
    chain->SetBranchAddress("nvctrhl",&nvctrhl);
    chain->SetBranchAddress("vctrhl_id",vctrhl_id);
    chain->SetBranchAddress("vctrhl_trkn",vctrhl_trkn);
    chain->SetBranchAddress("vctrhl_qovr",vctrhl_qovr);
    chain->SetBranchAddress("vctrhl_zh",vctrhl_zh);
    chain->SetBranchAddress("vctrhl_pgevc",vctrhl_pgevc);
    chain->SetBranchAddress("vcatcal_kodswm",vcatcal_kodswm);
  }

  if ( BREMAT ) {
    chain->SetBranchAddress("brenmu",&brenmu);
    chain->SetBranchAddress("bremat_nmatch",&bremat_nmatch);
    chain->SetBranchAddress("bremat_everror",&bremat_everror);
    chain->SetBranchAddress("bremat_error",bremat_error);
    chain->SetBranchAddress("bremat_ivc",bremat_ivc);
    chain->SetBranchAddress("bremat_imu",bremat_imu);
    chain->SetBranchAddress("bremat_delta",bremat_delta);
    chain->SetBranchAddress("bremat_xres",bremat_xres);
    chain->SetBranchAddress("bremat_yres",bremat_yres);
    chain->SetBranchAddress("bremat_slopxres",bremat_slopxres);
    chain->SetBranchAddress("bremat_slopyres",bremat_slopyres);
    chain->SetBranchAddress("bremat_invpres",bremat_invpres);
    chain->SetBranchAddress("bremat_covres",bremat_covres);
    chain->SetBranchAddress("bremat_chi2mat",bremat_chi2mat);
    chain->SetBranchAddress("bremat_probmat",bremat_probmat);
    chain->SetBranchAddress("bremat_chi2matp",bremat_chi2matp);
    chain->SetBranchAddress("bremat_probmatp",bremat_probmatp);
    chain->SetBranchAddress("bremat_endpos",bremat_endpos);
  }
  
  if ( OWN_MC ) {
    chain->SetBranchAddress("fmck_nkin",&fmck_nkin);
    chain->SetBranchAddress("fmck_q2",&fmck_q2);
    chain->SetBranchAddress("fmck_w",&fmck_w);
    chain->SetBranchAddress("fmck_xg",&fmck_xg);
    chain->SetBranchAddress("fmck_nstor",&fmck_nstor);
    chain->SetBranchAddress("fmck_id",fmck_id);
    chain->SetBranchAddress("fmck_px",fmck_px);
    chain->SetBranchAddress("fmck_py",fmck_py);
    chain->SetBranchAddress("fmck_pz",fmck_pz);
    chain->SetBranchAddress("fmck_e",fmck_e);
    chain->SetBranchAddress("fmck_m",fmck_m);
    //    chain->SetBranchAddress("fmck_pt",fmck_pt);
    //    chain->SetBranchAddress("fmck_eta",fmck_eta);
    chain->SetBranchAddress("fmck_daug",fmck_daug);
    chain->SetBranchAddress("fmck_prt",fmck_prt);
    chain->SetBranchAddress("fmck_prat",fmck_prat);
    chain->SetBranchAddress("fmck_impar",fmck_impar);
    chain->SetBranchAddress("fmck_impar2",fmck_impar2);
    //    chain->SetBranchAddress("fmck_dsignif",fmck_dsignif);
    //    chain->SetBranchAddress("fmck_dsignif2",fmck_dsignif2);
    chain->SetBranchAddress("fmvtx_nstor",&fmvtx_nstor);
    chain->SetBranchAddress("fmvtx_id",fmvtx_id);
    chain->SetBranchAddress("fmvtx_r",fmvtx_r);
    chain->SetBranchAddress("fmvtx_time",fmvtx_time);
    chain->SetBranchAddress("fmvtx_prby",fmvtx_prby);
  } else {
    fmck_nkin = 0;
    fmck_q2 = 0;
    fmck_w = 0;
    fmck_xg = 0;
    fmvtx_nstor = 0;
    fmck_nstor = 0;
    for ( Int_t i = 0; i < 100; ++i ) {
      fmck_id[i] = 0;
      fmck_px[i] = 0;
      fmck_py[i] = 0;
      fmck_pz[i] = 0;
      fmck_e[i] = 0;
      fmck_m[i] = 0;
      //      fmck_pt[i] = 0;
      //      fmck_eta[i] = 0;
      fmck_daug[i] = 0;
      fmck_prt[i] = 0;
      fmck_prat[i] = 0;
      fmck_impar[i] = 0;
      fmck_impar2[i] = 0;
      //      fmck_dsignif[i] = 0;
      //      fmck_dsignif2[i] = 0;
      fmvtx_id[i] = 0;
      for ( Int_t j = 0; j < 3; ++j ) 
	fmvtx_r[i][j] = 0;
      fmvtx_time[i] = 0;
      fmvtx_prby[i] = 0;
    }
  }
  

  if ( OWN_MC_JETS ) {
    chain->SetBranchAddress("fmck_hadjet",fmck_hadjet);
    chain->SetBranchAddress("fmck_mhadjet",fmck_mhadjet);
    chain->SetBranchAddress("fmck_bhadjet",fmck_bhadjet);
    chain->SetBranchAddress("fmck_mbhadjet",fmck_mbhadjet);
    chain->SetBranchAddress("fmck_partjet",fmck_partjet);
    chain->SetBranchAddress("fmck_mpartjet",fmck_mpartjet);
    chain->SetBranchAddress("nhjets",&nhjets);
    chain->SetBranchAddress("pxhjet",pxhjet);
    chain->SetBranchAddress("pyhjet",pyhjet);
    chain->SetBranchAddress("pzhjet",pzhjet);
    chain->SetBranchAddress("ehjet",ehjet);
    chain->SetBranchAddress("nhmjets",&nhmjets);
    chain->SetBranchAddress("pxhmjet",pxhmjet);
    chain->SetBranchAddress("pyhmjet",pyhmjet);
    chain->SetBranchAddress("pzhmjet",pzhmjet);
    chain->SetBranchAddress("ehmjet",ehmjet);
    chain->SetBranchAddress("nhbjets",&nhbjets);
    chain->SetBranchAddress("pxhbjet",pxhbjet);
    chain->SetBranchAddress("pyhbjet",pyhbjet);
    chain->SetBranchAddress("pzhbjet",pzhbjet);
    chain->SetBranchAddress("ehbjet",ehbjet);
    chain->SetBranchAddress("nhbmjets",&nhbmjets);
    chain->SetBranchAddress("pxhbmjet",pxhbmjet);
    chain->SetBranchAddress("pyhbmjet",pyhbmjet);
    chain->SetBranchAddress("pzhbmjet",pzhbmjet);
    chain->SetBranchAddress("ehbmjet",ehbmjet);
    chain->SetBranchAddress("npjets",&npjets);
    chain->SetBranchAddress("pxpjet",pxpjet);
    chain->SetBranchAddress("pypjet",pypjet);
    chain->SetBranchAddress("pzpjet",pzpjet);
    chain->SetBranchAddress("epjet",epjet);
    chain->SetBranchAddress("npmjets",&npmjets);
    chain->SetBranchAddress("pxpmjet",pxpmjet);
    chain->SetBranchAddress("pypmjet",pypmjet);
    chain->SetBranchAddress("pzpmjet",pzpmjet);
    chain->SetBranchAddress("epmjet",epmjet);
  } else {
    for ( Int_t i = 0; i < 100; ++i ) {
      fmck_hadjet[i]   = 0;
      fmck_mhadjet[i]  = 0;
      fmck_bhadjet[i]  = 0;
      fmck_mbhadjet[i] = 0;
      fmck_partjet[i]  = 0;
      fmck_mpartjet[i] = 0;
    }
    nhjets   = 0;
    nhmjets  = 0;
    nhbjets  = 0;
    nhbmjets = 0;
    npjets   = 0;
    npmjets  = 0;
    for ( Int_t i = 0; i < 10; ++i ) {
      pxhjet[i]   = 0.0;
      pyhjet[i]   = 0.0;
      pzhjet[i]   = 0.0;
      ehjet[i]    = 0.0;
      pxhmjet[i]  = 0.0;
      pyhmjet[i]  = 0.0;
      pzhmjet[i]  = 0.0;
      ehmjet[i]   = 0.0;
      pxhbjet[i]  = 0.0;
      pyhbjet[i]  = 0.0;
      pzhbjet[i]  = 0.0;
      ehbjet[i]   = 0.0;
      pxhbmjet[i] = 0.0;
      pyhbmjet[i] = 0.0;
      pzhbmjet[i] = 0.0;
      ehbmjet[i]  = 0.0;
      pxpjet[i]   = 0.0;
      pypjet[i]   = 0.0;
      pzpjet[i]   = 0.0;
      epjet[i]    = 0.0;
      pxpmjet[i]  = 0.0;
      pypmjet[i]  = 0.0;
      pzpmjet[i]  = 0.0;
      epmjet[i]   = 0.0;
    }
  }
  
  }else if (gCards->GetHERA2()){

  if ( BAC ) {
    chain->SetBranchAddress("Bac_etot",&bac_etot);
    chain->SetBranchAddress("Bac_etot_o2r",&bac_etot_o2r);
    chain->SetBranchAddress("Bac_npad",&bac_npad);
    chain->SetBranchAddress("Bac_npad_o2r",&bac_npad_o2r);
    chain->SetBranchAddress("Bac_et",&bac_et);
    chain->SetBranchAddress("Bac_px",&bac_px);
    chain->SetBranchAddress("Bac_py",&bac_py);
    chain->SetBranchAddress("Nbacmu",&nbacmu);
    chain->SetBranchAddress("Mubac_xyz",mubac_xyz);
    chain->SetBranchAddress("Mubac_dxyz",mubac_dxyz);
    chain->SetBranchAddress("Mubac_cos",mubac_cos);
    chain->SetBranchAddress("Mubac_dcos",mubac_dcos);
    chain->SetBranchAddress("Mubac_eloss",mubac_eloss);
    chain->SetBranchAddress("Mubac_deloss",mubac_deloss);
    chain->SetBranchAddress("Mubac_unit",mubac_unit);
    chain->SetBranchAddress("Mubac_dim",mubac_dim);
    chain->SetBranchAddress("Mubac_quality",mubac_quality);
    chain->SetBranchAddress("Ahit",ahit);
    chain->SetBranchAddress("Pad",pad);
  }

  if ( BACMAT ) {
    chain->SetBranchAddress("Bm_n",&bm_n);
    chain->SetBranchAddress("Bm_idvc",bm_idvc);
    chain->SetBranchAddress("Bm_idmubac",bm_idmubac);
    chain->SetBranchAddress("Bm_istop",bm_istop);
    chain->SetBranchAddress("Bm_error",bm_error);
    chain->SetBranchAddress("Bm_readout",bm_readout);
  }

  if ( CAL ) {
    chain->SetBranchAddress("Cal_px",&cal_px);
    chain->SetBranchAddress("Cal_py",&cal_py);
    chain->SetBranchAddress("Cal_pz",&cal_pz);
    chain->SetBranchAddress("Cal_e",&cal_e);
    chain->SetBranchAddress("Cal_et",&cal_et);
    chain->SetBranchAddress("Cal_empz",&cal_empz);
    chain->SetBranchAddress("Cal_pt",&cal_pt);
    chain->SetBranchAddress("Cal_phi",&cal_phi);
    chain->SetBranchAddress("Remc",remc);
    chain->SetBranchAddress("Bemc",bemc);
    chain->SetBranchAddress("Femc",femc);
    chain->SetBranchAddress("Rhac",rhac);
    chain->SetBranchAddress("Bhac",bhac);
    chain->SetBranchAddress("Fhac",fhac);
    chain->SetBranchAddress("Bhac2",bhac2);
    chain->SetBranchAddress("Fhac2",fhac2);
    chain->SetBranchAddress("Nfemc",&nfemc);
    chain->SetBranchAddress("Nfhac1",&nfhac1);
    chain->SetBranchAddress("Nfhac2",&nfhac2);
    chain->SetBranchAddress("Nbemc",&nbemc);
    chain->SetBranchAddress("Nbhac1",&nbhac1);
    chain->SetBranchAddress("Nbhac2",&nbhac2);
    chain->SetBranchAddress("Nremc",&nremc);
    chain->SetBranchAddress("Nrhac",&nrhac);
    chain->SetBranchAddress("Cal_tf",&cal_tf);
    chain->SetBranchAddress("Cal_tb",&cal_tb);
    chain->SetBranchAddress("Cal_tr",&cal_tr);
    chain->SetBranchAddress("Cal_tg",&cal_tg);
    chain->SetBranchAddress("Cal_tf",&cal_tf);
    chain->SetBranchAddress("Cal_tb",&cal_tb);
    chain->SetBranchAddress("Cal_tr",&cal_tr);
    chain->SetBranchAddress("Cal_tg",&cal_tg);
    /*
    chain->SetBranchAddress("Cal_tf_e",&cal_tf_e);
    chain->SetBranchAddress("Cal_tb_e",&cal_tb_e);
    chain->SetBranchAddress("Cal_tr_e",&cal_tr_e);
    chain->SetBranchAddress("Cal_tg_e",&cal_tg_e);
    chain->SetBranchAddress("Cal_tf_n",&cal_tf_n);
    chain->SetBranchAddress("Cal_tb_n",&cal_tb_n);
    chain->SetBranchAddress("Cal_tr_n",&cal_tr_n);
    chain->SetBranchAddress("Cal_tg_n",&cal_tg_n);
    */
    chain->SetBranchAddress("Etamax_ce",&etamax_ce);
    chain->SetBranchAddress("Etamax_ce4",&etamax_ce4);
    chain->SetBranchAddress("Cal_et10",&cal_et10);
    chain->SetBranchAddress("Mtrknoe_pi",&mtrknoe_pi);
    chain->SetBranchAddress("Mtrknoe_k",&mtrknoe_k);
    chain->SetBranchAddress("E_hk",&e_hk);
    chain->SetBranchAddress("Unmen_pi",&unmen_pi);
    chain->SetBranchAddress("Unmen_k",&unmen_k);
    chain->SetBranchAddress("Sparkf",&sparkf);
  }

  if ( FCALIR ) {
    chain->SetBranchAddress("Pex1ir",pex1ir);
    chain->SetBranchAddress("Et1ir",&et1ir);
    chain->SetBranchAddress("Etex1ir",&etex1ir);
    chain->SetBranchAddress("Pex2ir",pex2ir);
    chain->SetBranchAddress("Et2ir",&et2ir);
    chain->SetBranchAddress("Etex2ir",&etex2ir);
  }

  if ( RCALIR ) {
    chain->SetBranchAddress("Percir",percir);
    chain->SetBranchAddress("Etrcir",&etrcir);
  }
  
  if ( EVENT ) {
    chain->SetBranchAddress("Runnr",&runnr);
    chain->SetBranchAddress("Eventnr",&eventnr);
  }

  if ( TAKEINFO ){
   chain->SetBranchAddress("Mvdtake",&mvdtake);
  }

  if ( GMUON ) {
    chain->SetBranchAddress("Nmu",&nmu);
    chain->SetBranchAddress("Muqual",muqual);
    chain->SetBranchAddress("Mucharge",mucharge);
    chain->SetBranchAddress("Mupt",mupt);
    chain->SetBranchAddress("Muth",muth);
    chain->SetBranchAddress("Muph",muph);
    chain->SetBranchAddress("Mup",mup);
    chain->SetBranchAddress("Muperr",muperr);
    chain->SetBranchAddress("Mutrfl",mutrfl);
    chain->SetBranchAddress("Mutrid",mutrid);
    chain->SetBranchAddress("Muvcid",muvcid);
    chain->SetBranchAddress("Muztid",muztid);
    chain->SetBranchAddress("Mustid",mustid);
    chain->SetBranchAddress("Muvtxfl",muvtxfl);
    chain->SetBranchAddress("Muvtxid",muvtxid);
    chain->SetBranchAddress("Muglomu",muglomu);
    chain->SetBranchAddress("Mubremat",mubremat); 
    chain->SetBranchAddress("Mubacmat",mubacmat);
    chain->SetBranchAddress("Mumubac",mumubac);
    chain->SetBranchAddress("Mumamma",mumamma);
    chain->SetBranchAddress("Mumpmat",mumpmat);
    chain->SetBranchAddress("Mumufo",mumufo);
    chain->SetBranchAddress("Mumip",mumip);
    chain->SetBranchAddress("Munphi",munphi);
    chain->SetBranchAddress("Mumv",mumv);
    chain->SetBranchAddress("Mucalfl",mucalfl);
    chain->SetBranchAddress("Mucalene",mucalene);
    chain->SetBranchAddress("Muhac2",muhac2);
    chain->SetBranchAddress("Muzufid",muzufid);
    chain->SetBranchAddress("Muisol",    muisol	 );
    chain->SetBranchAddress("Munis",	 munis	 );
    chain->SetBranchAddress("Muisdrmip", muisdrmip);
    chain->SetBranchAddress("Muisetmip", muisetmip);
    chain->SetBranchAddress("Muistumip", muistumip);
    chain->SetBranchAddress("Mupmip",mupmip);
    chain->SetBranchAddress("Muhene",muhene);
    chain->SetBranchAddress("Mutime",mutime);
    chain->SetBranchAddress("Muchfl",muchfl);
    chain->SetBranchAddress("Muchid",muchid);
    chain->SetBranchAddress("Mupmat",mupmat);
  
    // change in variable mubacfl
    // in new ntuples, it is called mubacdca and
    // changed its type from int to float_t
    // check if mubacfl or mubacdca is filled in ntuple
    // set boolean
    // spool variabled in corresponding variables
    // let return funtion choose which one to return
    // return is always float
    // in case of mubacfl, cast of int to float
    if ( chain->GetBranch("Mubacdca") ) {
      new_mubacdca = kTRUE;
    } else if ( chain->GetBranch("Mubacfl") ) {
      new_mubacdca = kFALSE;
    } else {
      new_mubacdca = kFALSE;
    }

    if ( new_mubacdca ) {
      chain->SetBranchAddress("Mubacdca",mubacdca);
    } else {
      chain->SetBranchAddress("Mubacfl",mubacfl);
    }

    //    chain->SetBranchAddress("mubacid",mubacid);
    chain->SetBranchAddress("Mudxy",mudxy);
    chain->SetBranchAddress("Mudz",mudz);
    
    //    if ( gCards->GetdCache() ) {
      chain->SetBranchAddress("Mundof",mundof);
      chain->SetBranchAddress("Muz",muz);
      chain->SetBranchAddress("Muprec",muprec);
      //    } else {
      //      for ( Int_t i = 0; i < 20; ++i ) {
      //	mundof[i] = 0;
      //	muz[i] = 0.0;
      //	muprec[i] = 0.0;
      //    }
      //  }
    
  }
  
  if ( GMU_JET ) {
    chain->SetBranchAddress("Mujetfl",mujetfl);
    chain->SetBranchAddress("Mujetid",mujetid);
    chain->SetBranchAddress("Mujetdr",mujetdr);
    chain->SetBranchAddress("Mujetpt",mujetpt);
    chain->SetBranchAddress("Mujetdr2",mujetdr2);
    chain->SetBranchAddress("Mujetpt2",mujetpt2);
    chain->SetBranchAddress("Muhjet_id",muhjet_id);
  }
  if ( GMU_JET_NEW ) {
    chain->SetBranchAddress("Mujetfl_a",mujetfl_a);
    chain->SetBranchAddress("Mujetid_a",mujetid_a);
    chain->SetBranchAddress("Mujetdr_a",mujetdr_a);
    chain->SetBranchAddress("Mujetpt_a",mujetpt_a);
    chain->SetBranchAddress("Mujetdr2_a",mujetdr2_a);
    chain->SetBranchAddress("Mujetpt2_a",mujetpt2_a);

    chain->SetBranchAddress("Mujetfl_b",mujetfl_b);
    chain->SetBranchAddress("Mujetid_b",mujetid_b);
    chain->SetBranchAddress("Mujetdr_b",mujetdr_b);
    chain->SetBranchAddress("Mujetpt_b",mujetpt_b);
    chain->SetBranchAddress("Mujetdr2_b",mujetdr2_b);
    chain->SetBranchAddress("Mujetpt2_b",mujetpt2_b);

    chain->SetBranchAddress("Mujetfl_c",mujetfl_c);
    chain->SetBranchAddress("Mujetid_c",mujetid_c);
    chain->SetBranchAddress("Mujetdr_c",mujetdr_c);
    chain->SetBranchAddress("Mujetpt_c",mujetpt_c);
    chain->SetBranchAddress("Mujetdr2_c",mujetdr2_c);
    chain->SetBranchAddress("Mujetpt2_c",mujetpt2_c);

    chain->SetBranchAddress("Mujetfl_d",mujetfl_d);
    chain->SetBranchAddress("Mujetid_d",mujetid_d);
    chain->SetBranchAddress("Mujetdr_d",mujetdr_d);
    chain->SetBranchAddress("Mujetpt_d",mujetpt_d);
    chain->SetBranchAddress("Mujetdr2_d",mujetdr2_d);
    chain->SetBranchAddress("Mujetpt2_d",mujetpt2_d);
  }

  if ( GMU_MC ) {
    chain->SetBranchAddress("Muick",muick);
    chain->SetBranchAddress("Mupartyp",mupartyp);
    chain->SetBranchAddress("Mumc_p",mumc_p);
    chain->SetBranchAddress("Mudirtyp",mudirtyp);
    chain->SetBranchAddress("Mumc_d",mumc_d);
    chain->SetBranchAddress("Muqtyp",muqtyp);
    chain->SetBranchAddress("Mumc_q",mumc_q);
    chain->SetBranchAddress("Mutruefl",mutruefl);
    chain->SetBranchAddress("Mudecdist",mudecdist);
  }
  if ( FMCKIN ) {
    chain->SetBranchAddress("Npart",&npart);
    chain->SetBranchAddress("Part_id",part_id);
    chain->SetBranchAddress("Part_prt",part_prt);
    chain->SetBranchAddress("Part_p",part_p);
  }

  if ( ktJETS_A ) {
    chain->SetBranchAddress("Kt_njet_a",&kt_njet_a);
    chain->SetBranchAddress("Kt_etjet_a",kt_etjet_a);
    chain->SetBranchAddress("Kt_etajet_a",kt_etajet_a);
    chain->SetBranchAddress("Kt_phijet_a",kt_phijet_a);
    chain->SetBranchAddress("Kt_masjet_a",kt_masjet_a);
  }

  if ( ktJETS_B ) {
    chain->SetBranchAddress("Kt_njet_b",&kt_njet_b);
    chain->SetBranchAddress("Kt_etjet_b",kt_etjet_b);
    chain->SetBranchAddress("Kt_etajet_b",kt_etajet_b);
    chain->SetBranchAddress("Kt_phijet_b",kt_phijet_b);
    chain->SetBranchAddress("Kt_masjet_b",kt_masjet_b);
  }

  if ( ktJETS_C ) {
    chain->SetBranchAddress("Kt_njet_c",&kt_njet_c);
    chain->SetBranchAddress("Kt_etjet_c",kt_etjet_c);
    chain->SetBranchAddress("Kt_etajet_c",kt_etajet_c);
    chain->SetBranchAddress("Kt_phijet_c",kt_phijet_c);
    chain->SetBranchAddress("Kt_masjet_c",kt_masjet_c);
  }

  if ( ktJETS_D ) {
    chain->SetBranchAddress("Kt_njet_d",&kt_njet_d);
    chain->SetBranchAddress("Kt_etjet_d",kt_etjet_d);
    chain->SetBranchAddress("Kt_etajet_d",kt_etajet_d);
    chain->SetBranchAddress("Kt_phijet_d",kt_phijet_d);
    chain->SetBranchAddress("Kt_masjet_d",kt_masjet_d);
  }

  if ( MCSUMS ) {
    chain->SetBranchAddress("Mc_ez",&mc_ez);
    chain->SetBranchAddress("Mc_esum",&mc_esum);
    chain->SetBranchAddress("Mc_etcone",&mc_etcone);
    chain->SetBranchAddress("Mc_ercal",&mc_ercal);
  }

  if ( MCJETS ) {
    chain->SetBranchAddress("Mc_njet",&mc_njet);
    chain->SetBranchAddress("Mc_etj",mc_etj);
    chain->SetBranchAddress("Mc_rapj",mc_rapj);
    chain->SetBranchAddress("Mc_phij",mc_phij);
    chain->SetBranchAddress("Mc_pxj",mc_pxj);
    chain->SetBranchAddress("Mc_pyj",mc_pyj);
    chain->SetBranchAddress("Mc_pzj",mc_pzj);
    chain->SetBranchAddress("Mc_ej",mc_ej);
  }

  if ( MCKINE ) {
    chain->SetBranchAddress("Mc_el",&mc_el);
    chain->SetBranchAddress("Mc_ep",&mc_ep);
    chain->SetBranchAddress("Mc_x",&mc_x);
    chain->SetBranchAddress("Mc_y",&mc_y);
    chain->SetBranchAddress("Mc_q2",&mc_q2);
    chain->SetBranchAddress("Mc_mu",&mc_mu);
    chain->SetBranchAddress("Mc_pt",&mc_pt);
    chain->SetBranchAddress("Mc_xpro",&mc_xpro);
    chain->SetBranchAddress("Mc_xgam",&mc_xgam);
    chain->SetBranchAddress("Mc_xpom",&mc_xpom);
    chain->SetBranchAddress("Mc_beta",&mc_beta);
    chain->SetBranchAddress("Mc_t",&mc_t);
    chain->SetBranchAddress("Mc_idl",&mc_idl);
    chain->SetBranchAddress("Mc_pidl",&mc_pidl);
    chain->SetBranchAddress("Mc_pidp",&mc_pidp);
    chain->SetBranchAddress("Mc_idfsl",&mc_idfsl);
    chain->SetBranchAddress("Mc_pfsl",mc_pfsl);
    chain->SetBranchAddress("Mc_pfsph",mc_pfsph);
    chain->SetBranchAddress("Mc_vtx",mc_vtx);
    chain->SetBranchAddress("Mc_ichnn",&mc_ichnn);
  }

  if ( MCVTX ) {
    chain->SetBranchAddress("Mcvtx",mcvtx);
  }

  if ( MUON ) {
    chain->SetBranchAddress("Nomu",&nomu);
    chain->SetBranchAddress("Bmuon1",&bmuon1);
    chain->SetBranchAddress("Bmuon2",&bmuon2);
    chain->SetBranchAddress("Bmnrmips",&bmnrmips);
    chain->SetBranchAddress("Bmmmtrk",&bmmmtrk);
    chain->SetBranchAddress("Muonf1",&muonf1);
    chain->SetBranchAddress("Muonf2",&muonf2);
    chain->SetBranchAddress("Mupt1",&mupt1);
    chain->SetBranchAddress("Muth1",&muth1);
    chain->SetBranchAddress("Muph1",&muph1);
    chain->SetBranchAddress("Mupt2",&mupt2);
    chain->SetBranchAddress("Muth2",&muth2);
    chain->SetBranchAddress("Muph2",&muph2);
    chain->SetBranchAddress("Fmntrk",&fmntrk);
    chain->SetBranchAddress("Fmntrp",&fmntrp);
    chain->SetBranchAddress("Fmangr",&fmangr);
    chain->SetBranchAddress("Fmrecp",&fmrecp);
    chain->SetBranchAddress("Fmmatch",&fmmatch);
    chain->SetBranchAddress("Mbchi2",mbchi2);
    chain->SetBranchAddress("Mbp",mbp);
    chain->SetBranchAddress("Mbdca",mbdca);
    chain->SetBranchAddress("Mbtrfl",mbtrfl);
  }

  if ( FMU_MPM) {
    chain->SetBranchAddress("Nfmu",&nfmu);
    chain->SetBranchAddress("Fmux",fmux);
    chain->SetBranchAddress("Fmuy",fmuy);
    chain->SetBranchAddress("Fmuz",fmuz);
    chain->SetBranchAddress("Fmuchi",fmuchi);
    chain->SetBranchAddress("Fmuprob",fmuprob);
    chain->SetBranchAddress("Fmuti",fmuti);
    chain->SetBranchAddress("Fmufi",fmufi);
    chain->SetBranchAddress("Fmutqor",fmutqor);
    chain->SetBranchAddress("Fmutz",fmutz);
    chain->SetBranchAddress("Fmutqd",fmutqd);
    chain->SetBranchAddress("Fmutchi",fmutchi);
    chain->SetBranchAddress("Fmutndf",fmutndf);
    chain->SetBranchAddress("Fmutksw",fmutksw);
  }

  if ( FMUmfrtz ) {
    chain->SetBranchAddress("Nmf",&nmf);
    chain->SetBranchAddress("Mfx",mfx);
    chain->SetBranchAddress("Mfy",mfy);
    chain->SetBranchAddress("Mfz",mfz);
    chain->SetBranchAddress("Mfvx",mfvx);
    chain->SetBranchAddress("Mfvy",mfvy);
    chain->SetBranchAddress("Mfqop",mfqop);
    chain->SetBranchAddress("Mfo",mfo);
    chain->SetBranchAddress("Mfndf",mfndf);
    chain->SetBranchAddress("Mfpro",mfpro);
    chain->SetBranchAddress("Mfndff",mfndff);
    chain->SetBranchAddress("Mfprof",mfprof);
    chain->SetBranchAddress("Mfhdc",mfhdc);
    chain->SetBranchAddress("Mfhlt",mfhlt);
    chain->SetBranchAddress("Fmusid",fmusid);
    chain->SetBranchAddress("Fmushr",fmushr);
    chain->SetBranchAddress("Fmusrchi",fmusrchi);
    chain->SetBranchAddress("Fmusnr",fmusnr);
    chain->SetBranchAddress("Fmushp",fmushp);
    chain->SetBranchAddress("Fmusnp",fmusnp);
    chain->SetBranchAddress("Fmusp",fmusp);
    chain->SetBranchAddress("Fmusthe",fmusthe);
    chain->SetBranchAddress("Fmusphi",fmusphi);
  }

  if ( MV ) {
    chain->SetBranchAddress("Umv_ncmuo",&umv_ncmuo);
    chain->SetBranchAddress("Umv_trkmuo",umv_trkmuo);
    chain->SetBranchAddress("Umv_trrmuo",umv_trrmuo);
    chain->SetBranchAddress("Umv_trnmuo",umv_trnmuo);
    chain->SetBranchAddress("Umv_trqmuo",umv_trqmuo);
    chain->SetBranchAddress("Umv_tobr",umv_tobr);
    chain->SetBranchAddress("Umv_trmmuo",umv_trmmuo);
    chain->SetBranchAddress("Umv_trtmuo",umv_trtmuo);
    chain->SetBranchAddress("Umv_trpmuo",umv_trpmuo);
    chain->SetBranchAddress("Umv_trcmuo",umv_trcmuo);
    chain->SetBranchAddress("Umv_tremuo",umv_tremuo);
    chain->SetBranchAddress("Umv_trdmuo",umv_trdmuo);
    chain->SetBranchAddress("Umv_timuo",umv_timuo);
    chain->SetBranchAddress("Umv_xcmuo",umv_xcmuo);
    chain->SetBranchAddress("Umv_ycmuo",umv_ycmuo);
    chain->SetBranchAddress("Umv_zcmuo",umv_zcmuo);
    chain->SetBranchAddress("Umv_heemuo",umv_heemuo);
    chain->SetBranchAddress("Umv_hexmuo",umv_hexmuo);
    chain->SetBranchAddress("Umv_heymuo",umv_heymuo);
    chain->SetBranchAddress("Umv_hezmuo",umv_hezmuo);
    chain->SetBranchAddress("Umv_prmuo",umv_prmuo);
    chain->SetBranchAddress("Umv_efmuo",umv_efmuo);
    chain->SetBranchAddress("Umv_comuo",umv_comuo);
    chain->SetBranchAddress("Umv_pumuo",umv_pumuo);
    chain->SetBranchAddress("Umv_prcmuo",umv_prcmuo);
    chain->SetBranchAddress("Umv_efcmuo",umv_efcmuo);
    chain->SetBranchAddress("Umv_cocmuo",umv_cocmuo);
    chain->SetBranchAddress("Umv_pucmuo",umv_pucmuo);
    chain->SetBranchAddress("Umv_ecamuo",umv_ecamuo);
    chain->SetBranchAddress("Uex_calmuo",uex_calmuo);
    chain->SetBranchAddress("Uey_calmuo",uey_calmuo);
    chain->SetBranchAddress("Uez_calmuo",uez_calmuo);
    chain->SetBranchAddress("Uet_calmuo",uet_calmuo);
  }

  if ( SIRA) {
    chain->SetBranchAddress("Sincand",&sincand);
    chain->SetBranchAddress("Sierror",&sierror);
    chain->SetBranchAddress("Siprob",siprob);
    chain->SetBranchAddress("Sipos",sipos);
    chain->SetBranchAddress("Sicalpos",sicalpos);
    chain->SetBranchAddress("Sicalene",sicalene);
    chain->SetBranchAddress("Siein",siein);
    chain->SetBranchAddress("Sienin",sienin);
    chain->SetBranchAddress("Siecorr",siecorr);
    chain->SetBranchAddress("Sith",sith);
    chain->SetBranchAddress("Siph",siph);
    chain->SetBranchAddress("Sipt",sipt);
    chain->SetBranchAddress("Sixdet",sixdet);
    chain->SetBranchAddress("Siydet",siydet);
  }

  if ( SI_KIN ) {
    chain->SetBranchAddress("Sixel",sixel);
    chain->SetBranchAddress("Siyel",siyel);
    chain->SetBranchAddress("Siq2el",siq2el);
    chain->SetBranchAddress("Sixda",sixda);
    chain->SetBranchAddress("Siyda",siyda);
    chain->SetBranchAddress("Siq2da",siq2da);
    chain->SetBranchAddress("Sixda_cell",sixda_cell);
    chain->SetBranchAddress("Siyda_cell",siyda_cell);
    chain->SetBranchAddress("Siq2da_cell",siq2da_cell);
    chain->SetBranchAddress("Sixjb",sixjb);
    chain->SetBranchAddress("Siyjb",siyjb);
    chain->SetBranchAddress("Siq2jb",siq2jb);
    chain->SetBranchAddress("Sixjb_cell",sixjb_cell);
    chain->SetBranchAddress("Siyjb_cell",siyjb_cell);
    chain->SetBranchAddress("Siq2jb_cell",siq2jb_cell);
  }

  if ( TRIGGER ) {
    chain->SetBranchAddress("Fltw",fltw);
    chain->SetBranchAddress("Fltpsw",fltpsw);
    chain->SetBranchAddress("Fltfl",&fltfl);
    chain->SetBranchAddress("Gslt_global",&gslt_global);
    chain->SetBranchAddress("Sltw",sltw);
    chain->SetBranchAddress("Sltupw",sltupw);
    chain->SetBranchAddress("Tltw",tltw);
    chain->SetBranchAddress("Dstw",dstw);
    //   chain->SetBranchAddress("fltfcw",fltfcw);
    //   chain->SetBranchAddress("fltpsfcw",fltpsfcw);
  }

  if ( VERTEX ) {
    chain->SetBranchAddress("Ntrkvtx",&ntrkvtx);
    chain->SetBranchAddress("Xvtx",&xvtx);
    chain->SetBranchAddress("Yvtx",&yvtx);
    chain->SetBranchAddress("Zvtx",&zvtx);
    chain->SetBranchAddress("Chivtx",&chivtx);
    chain->SetBranchAddress("Nsecvtx",&nsecvtx);
    chain->SetBranchAddress("Xsecvtx",xsecvtx);
    chain->SetBranchAddress("Ysecvtx",ysecvtx);
    chain->SetBranchAddress("Zsecvtx",zsecvtx);
    chain->SetBranchAddress("Chisecvtx",chisecvtx);
    chain->SetBranchAddress("Fetatr",&fetatr);
    chain->SetBranchAddress("Betatr",&betatr);
    chain->SetBranchAddress("Pt_tr",&pt_tr);
    chain->SetBranchAddress("Empz_tr_pi",&empz_tr_pi);
    chain->SetBranchAddress("Et_tr",&et_tr);
    chain->SetBranchAddress("E_tr_pi",&e_tr_pi);
    chain->SetBranchAddress("Phi_tr",&phi_tr);
    chain->SetBranchAddress("Zvtx_fcal",&zvtx_fcal);
    chain->SetBranchAddress("Fcal_nrgoodcells",&fcal_nrgoodcells);
    chain->SetBranchAddress("Fcal_vzerr",&fcal_vzerr);
  }

  if( BSPOT ) {
    chain->SetBranchAddress("Bspt_x",&bspt_x);
    chain->SetBranchAddress("Bspt_y",&bspt_y);
    chain->SetBranchAddress("Bspt_z",&bspt_z);
  }


  if ( ZUFOS ) {
    chain->SetBranchAddress("V_h_px_zu",&v_h_px_zu);
    chain->SetBranchAddress("V_h_py_zu",&v_h_py_zu);
    chain->SetBranchAddress("V_h_pz_zu",&v_h_pz_zu);
    chain->SetBranchAddress("V_h_e_zu",&v_h_e_zu);
    chain->SetBranchAddress("Etamax_zu",&etamax_zu);
    chain->SetBranchAddress("Etamax_zu4",&etamax_zu4);
    chain->SetBranchAddress("Fgap",&fgap);
    chain->SetBranchAddress("Bgap",&bgap);
    chain->SetBranchAddress("Nzufos",&nzufos);
    chain->SetBranchAddress("Tufo",tufo);
    chain->SetBranchAddress("Zufo_bsp",zufo_bsp);
    chain->SetBranchAddress("Zufo",zufo);
    chain->SetBranchAddress("Zufoeemc",zufoeemc);
  }

  if ( Tracking ) {
    chain->SetBranchAddress("Trk_ntracks",&trk_ntracks);
    chain->SetBranchAddress("Trk_type",trk_type);
    chain->SetBranchAddress("Ntrack_type",ntrack_type);
    chain->SetBranchAddress("Def_trk_type",&def_trk_type);
    chain->SetBranchAddress("Trk_id",trk_id);
    chain->SetBranchAddress("Trk_id2",trk_id2);
    chain->SetBranchAddress("Trk_px",trk_px);
    chain->SetBranchAddress("Trk_py",trk_py);
    chain->SetBranchAddress("Trk_pz",trk_pz);
    chain->SetBranchAddress("Trk_charge",trk_charge);
  }

  if ( Trk_vtx ) {
    chain->SetBranchAddress("Trk_vtx",trk_vtx);
    chain->SetBranchAddress("Trk_prim_vtx",trk_prim_vtx);
    chain->SetBranchAddress("Trk_sec_vtx",trk_sec_vtx);
    chain->SetBranchAddress("Trk_vxid",trk_vxid);
  }

  if ( Trk_qual ) {
    chain->SetBranchAddress("Trk_endpos",trk_endpos);
    chain->SetBranchAddress("Trk_nzbyt",trk_nzbyt);
    chain->SetBranchAddress("Trk_naxial",trk_naxial);
    chain->SetBranchAddress("Trk_nstereo",trk_nstereo);
    chain->SetBranchAddress("Trk_ndof",trk_ndof);
    chain->SetBranchAddress("Trk_layinner",trk_layinner);
    chain->SetBranchAddress("Trk_layouter",trk_layouter);
    chain->SetBranchAddress("Trk_dedxctd",trk_dedxctd);
    chain->SetBranchAddress("Trk_dedxctdcr",trk_dedxctdcr);
    chain->SetBranchAddress("Trk_chi2",trk_chi2);
    chain->SetBranchAddress("Trk_vchi2",trk_vchi2);
  }

  if ( Trk_MVD ) {
    chain->SetBranchAddress("Trk_nbr",trk_nbr);
    chain->SetBranchAddress("Trk_nbz",trk_nbz);
    chain->SetBranchAddress("Trk_nwu",trk_nwu);
    chain->SetBranchAddress("Trk_nwv",trk_nwv);
    chain->SetBranchAddress("Trk_dedxmvd",trk_dedxmvd);
    
    if ( !gCards->GetNewNtuple()&& gCards->GetMVDActivate()) {
      chain->SetBranchAddress("Trk_w",trk_w);
      chain->SetBranchAddress("Trk_phizero",trk_phizero);
      chain->SetBranchAddress("Trk_t",trk_t);
      chain->SetBranchAddress("Trk_dzero",trk_dzero);
      chain->SetBranchAddress("Trk_zzero",trk_zzero);
      chain->SetBranchAddress("Trk_cov",trk_cov);
    } else if ( gCards->GetNewNtuple() && gCards->GetMVDActivate() ) {
      chain->SetBranchAddress("Trk_helpar",trk_helpar);
      chain->SetBranchAddress("Trk_covmat",trk_covmat);
    }  else {
      for ( Int_t i = 0; i < 300; ++i ) {
	trk_w[i] = 0.0;
	trk_phizero[i] = 0.0;
	trk_t[i] = 0.0;
	trk_dzero[i] = 0.0;
	trk_zzero[i] = 0.0;
	for ( Int_t j = 0; j < 15; ++j)
	  trk_cov[i][j] = 0.0;
      }
    }
  }

  if ( Trk_imp ) {
    chain->SetBranchAddress("Trk_imppar",trk_imppar);
    chain->SetBranchAddress("Trk_imperr",trk_imperr);
    chain->SetBranchAddress("Trk_pca",trk_pca);
  }

  if( SECVTX ) {
    chain->SetBranchAddress("Vtxredprm_x",&vtxredprm_x);
    chain->SetBranchAddress("Vtxredprm_y",&vtxredprm_y);
    chain->SetBranchAddress("Vtxredprm_z",&vtxredprm_z);
    chain->SetBranchAddress("Vtxredprm_chi2",&vtxredprm_chi2);
    chain->SetBranchAddress("Vtxredprm_cov",&vtxredprm_cov);
    chain->SetBranchAddress("Vtxredprm_ndf",&vtxredprm_ndf);
    chain->SetBranchAddress("Nr_secvtx",&nr_secvtx);
    chain->SetBranchAddress("Vtxsec_x",vtxsec_x);
    chain->SetBranchAddress("Vtxsec_y",vtxsec_y);
    chain->SetBranchAddress("Vtxsec_z",vtxsec_z);
    chain->SetBranchAddress("Vtxsec_mass",vtxsec_mass);
    chain->SetBranchAddress("Vtxsec_chi2",vtxsec_chi2);
    chain->SetBranchAddress("Vtxsec_ndf",vtxsec_ndf);
    chain->SetBranchAddress("Vtxsec_multi",vtxsec_multi);
    chain->SetBranchAddress("Vtxsec_cov",vtxsec_cov);
    chain->SetBranchAddress("Vtxsec_zttid",vtxsec_zttid);
    chain->SetBranchAddress("Vtxsec2d_x",vtxsec2d_x);
    chain->SetBranchAddress("Vtxsec2d_y",vtxsec2d_y);
    chain->SetBranchAddress("Vtxsec2d_z",vtxsec2d_z);
    chain->SetBranchAddress("Vtxsec2d_mass",vtxsec2d_mass);
    chain->SetBranchAddress("Vtxsec2d_chi2",vtxsec2d_chi2);
    chain->SetBranchAddress("Vtxsec2d_ndf",vtxsec2d_ndf);
    chain->SetBranchAddress("Vtxsec2d_cov",vtxsec2d_cov);
  }

  if ( VCTRHLa ) {
    chain->SetBranchAddress("Nvctrhl",&nvctrhl);
    chain->SetBranchAddress("Vctrhl_id",vctrhl_id);
    chain->SetBranchAddress("Vctrhl_trkn",vctrhl_trkn);
    chain->SetBranchAddress("Vctrhl_qovr",vctrhl_qovr);
    chain->SetBranchAddress("Vctrhl_zh",vctrhl_zh);
    chain->SetBranchAddress("Vctrhl_pgevc",vctrhl_pgevc);
    chain->SetBranchAddress("Vcatcal_kodswm",vcatcal_kodswm);
  }

  if ( BREMAT ) {
    chain->SetBranchAddress("Brenmu",&brenmu);
    chain->SetBranchAddress("Bremat_nmatch",&bremat_nmatch);
    chain->SetBranchAddress("Bremat_everror",&bremat_everror);
    chain->SetBranchAddress("Bremat_error",bremat_error);
    chain->SetBranchAddress("Bremat_ivc",bremat_ivc);
    chain->SetBranchAddress("Bremat_imu",bremat_imu);
    chain->SetBranchAddress("Bremat_delta",bremat_delta);
    chain->SetBranchAddress("Bremat_xres",bremat_xres);
    chain->SetBranchAddress("Bremat_yres",bremat_yres);
    chain->SetBranchAddress("Bremat_slopxres",bremat_slopxres);
    chain->SetBranchAddress("Bremat_slopyres",bremat_slopyres);
    chain->SetBranchAddress("Bremat_invpres",bremat_invpres);
    chain->SetBranchAddress("Bremat_covres",bremat_covres);
    chain->SetBranchAddress("Bremat_chi2mat",bremat_chi2mat);
    chain->SetBranchAddress("Bremat_probmat",bremat_probmat);
    chain->SetBranchAddress("Bremat_chi2matp",bremat_chi2matp);
    chain->SetBranchAddress("Bremat_probmatp",bremat_probmatp);
    chain->SetBranchAddress("Bremat_endpos",bremat_endpos);
  }

  if ( OWN_MC ) {
    chain->SetBranchAddress("Fmck_nkin",&fmck_nkin);
    chain->SetBranchAddress("Fmck_q2",&fmck_q2);
    chain->SetBranchAddress("Fmck_w",&fmck_w);
    chain->SetBranchAddress("Fmck_xg",&fmck_xg);
    chain->SetBranchAddress("Fmck_nstor",&fmck_nstor);
    chain->SetBranchAddress("Fmck_id",fmck_id);
    chain->SetBranchAddress("Fmck_px",fmck_px);
    chain->SetBranchAddress("Fmck_py",fmck_py);
    chain->SetBranchAddress("Fmck_pz",fmck_pz);
    chain->SetBranchAddress("Fmck_e",fmck_e);
    chain->SetBranchAddress("Fmck_m",fmck_m);
    //    chain->SetBranchAddress("Fmck_pt",fmck_pt);
    //    chain->SetBranchAddress("Fmck_eta",fmck_eta);
    chain->SetBranchAddress("Fmck_daug",fmck_daug);
    chain->SetBranchAddress("Fmck_prt",fmck_prt);
    chain->SetBranchAddress("Fmck_prat",fmck_prat);
    chain->SetBranchAddress("Fmck_impar",fmck_impar);
    chain->SetBranchAddress("Fmck_impar2",fmck_impar2);
    //    chain->SetBranchAddress("Fmck_dsignif",fmck_dsignif);
    //    chain->SetBranchAddress("Fmck_dsignif2",fmck_dsignif2);
    chain->SetBranchAddress("Fmvtx_nstor",&fmvtx_nstor);
    chain->SetBranchAddress("Fmvtx_id",fmvtx_id);
    chain->SetBranchAddress("Fmvtx_r",fmvtx_r);
    chain->SetBranchAddress("Fmvtx_time",fmvtx_time);
    chain->SetBranchAddress("Fmvtx_prby",fmvtx_prby);
  } else {
    fmck_nkin = 0;
    fmck_q2 = 0;
    fmck_w = 0;
    fmck_xg = 0;
    fmvtx_nstor = 0;
    fmck_nstor = 0;
    for ( Int_t i = 0; i < 100; ++i ) {
      fmck_id[i] = 0;
      fmck_px[i] = 0;
      fmck_py[i] = 0;
      fmck_pz[i] = 0;
      fmck_e[i] = 0;
      fmck_m[i] = 0;
      //      fmck_pt[i] = 0;
      //      fmck_eta[i] = 0;
      fmck_daug[i] = 0;
      fmck_prt[i] = 0;
      fmck_prat[i] = 0;
      fmck_impar[i] = 0;
      fmck_impar2[i] = 0;
      //      fmck_dsignif[i] = 0;
      //      fmck_dsignif2[i] = 0;
      fmvtx_id[i] = 0;
      for ( Int_t j = 0; j < 3; ++j ) 
	fmvtx_r[i][j] = 0;
      fmvtx_time[i] = 0;
      fmvtx_prby[i] = 0;
    }
  }


  if ( OWN_MC_JETS ) {
    chain->SetBranchAddress("Fmck_hadjet",fmck_hadjet);
    chain->SetBranchAddress("Fmck_mhadjet",fmck_mhadjet);
    chain->SetBranchAddress("Fmck_bhadjet",fmck_bhadjet);
    chain->SetBranchAddress("Fmck_mbhadjet",fmck_mbhadjet);
    chain->SetBranchAddress("Fmck_partjet",fmck_partjet);
    chain->SetBranchAddress("Fmck_mpartjet",fmck_mpartjet);
    chain->SetBranchAddress("Nhjets",&nhjets);
    chain->SetBranchAddress("Pxhjet",pxhjet);
    chain->SetBranchAddress("Pyhjet",pyhjet);
    chain->SetBranchAddress("Pzhjet",pzhjet);
    chain->SetBranchAddress("Ehjet",ehjet);
    chain->SetBranchAddress("Nhmjets",&nhmjets);
    chain->SetBranchAddress("Pxhmjet",pxhmjet);
    chain->SetBranchAddress("Pyhmjet",pyhmjet);
    chain->SetBranchAddress("Pzhmjet",pzhmjet);
    chain->SetBranchAddress("Ehmjet",ehmjet);
    chain->SetBranchAddress("Nhbjets",&nhbjets);
    chain->SetBranchAddress("Pxhbjet",pxhbjet);
    chain->SetBranchAddress("Pyhbjet",pyhbjet);
    chain->SetBranchAddress("Pzhbjet",pzhbjet);
    chain->SetBranchAddress("Ehbjet",ehbjet);
    chain->SetBranchAddress("Nhbmjets",&nhbmjets);
    chain->SetBranchAddress("Pxhbmjet",pxhbmjet);
    chain->SetBranchAddress("Pyhbmjet",pyhbmjet);
    chain->SetBranchAddress("Pzhbmjet",pzhbmjet);
    chain->SetBranchAddress("Ehbmjet",ehbmjet);
    chain->SetBranchAddress("Npjets",&npjets);
    chain->SetBranchAddress("Pxpjet",pxpjet);
    chain->SetBranchAddress("Pypjet",pypjet);
    chain->SetBranchAddress("Pzpjet",pzpjet);
    chain->SetBranchAddress("Epjet",epjet);
    chain->SetBranchAddress("Npmjets",&npmjets);
    chain->SetBranchAddress("Pxpmjet",pxpmjet);
    chain->SetBranchAddress("Pypmjet",pypmjet);
    chain->SetBranchAddress("Pzpmjet",pzpmjet);
    chain->SetBranchAddress("Epmjet",epmjet);
  } else {
    for ( Int_t i = 0; i < 100; ++i ) {
      fmck_hadjet[i]   = 0;
      fmck_mhadjet[i]  = 0;
      fmck_bhadjet[i]  = 0;
      fmck_mbhadjet[i] = 0;
      fmck_partjet[i]  = 0;
      fmck_mpartjet[i] = 0;
    }
    nhjets   = 0;
    nhmjets  = 0;
    nhbjets  = 0;
    nhbmjets = 0;
    npjets   = 0;
    npmjets  = 0;
    for ( Int_t i = 0; i < 10; ++i ) {
      pxhjet[i]   = 0.0;
      pyhjet[i]   = 0.0;
      pzhjet[i]   = 0.0;
      ehjet[i]    = 0.0;
      pxhmjet[i]  = 0.0;
      pyhmjet[i]  = 0.0;
      pzhmjet[i]  = 0.0;
      ehmjet[i]   = 0.0;
      pxhbjet[i]  = 0.0;
      pyhbjet[i]  = 0.0;
      pzhbjet[i]  = 0.0;
      ehbjet[i]   = 0.0;
      pxhbmjet[i] = 0.0;
      pyhbmjet[i] = 0.0;
      pzhbmjet[i] = 0.0;
      ehbmjet[i]  = 0.0;
      pxpjet[i]   = 0.0;
      pypjet[i]   = 0.0;
      pzpjet[i]   = 0.0;
      epjet[i]    = 0.0;
      pxpmjet[i]  = 0.0;
      pypmjet[i]  = 0.0;
      pzpmjet[i]  = 0.0;
      epmjet[i]   = 0.0;
    }
  }
  
  }




  if ( OWN ) {
    //   chain->SetBranchAddress("zes_select",&zes_select);
    //   chain->SetBranchAddress("lumi",&lumi);
  }


  return kTRUE;
}

//_____________________________________________________________

Bool_t GConnectTree::Gettrk_prim_vtx(Int_t index){ 
  //
  // convert uchar_t to bool
  if ( gDebug ) cout << "GConnectTree::Gettrk_prim_vtx called" << endl;

  TString input(trk_prim_vtx[index]);
  istrstream stream(input.Data());
  Int_t number = 0;
  stream >> number;
  if ( number == 1 )
    return kTRUE;
  else 
    return kFALSE;
}

//_____________________________________________________________

Bool_t GConnectTree::Gettrk_sec_vtx(Int_t index){ 
  //
  // convert uchar_t to bool
  if ( gDebug ) cout << "GConnectTree::Gettrk_sec_vtx called" << endl;

  TString input(trk_sec_vtx[index]);
  istrstream stream(input.Data());
  Int_t number = 0;
  stream >> number;
  if ( number == 1 )
    return kTRUE;
  else 
    return kFALSE;
}

//_____________________________________________________________

Bool_t GConnectTree::SetDISPHPJets(Int_t index){
  // set the flag which jetfinde to use 
  // 0:OLD ntuple 1:PHP 2:DIS(Lab) 3:DIS(Breit)

  Bool_t newntuple;
  Bool_t debug_out;
  debug_out = kFALSE;
  newntuple = kFALSE;

  
  if ( gCards->GetNewNtuple()==kFALSE ){ // override autodetect
    newntuple = kFALSE;
    if (debug_out) cout << "Old Ntule SET!" << endl;
    if ( gCards->GetJETBreit() )
      cout << "ERROR: Old Ntule SET, but require breitframe!" << endl;
  }
  else if ( index < 3) {
    if ( gCards->GetSinistraDIS() && index == 2) { // new ntuple needed for DIS
      newntuple = kTRUE;
      if (debug_out) cout << "New Ntule found! (DIS required)" << endl;
    }
    else if ( Getkt_njet_b() > 0 ||  Getkt_njet_c() > 0 ){ // new blocks filled -> new ntuple
      newntuple = kTRUE;
      if (debug_out) cout << "New Ntule found! (jets_a/_b not 0)" << endl;
    }
    else if ( Getkt_njet_a() > 0 && (Getkt_njet_b()>=0 && Getkt_njet_c()>=0 )){ // new blocks empty, common filled -> old ntuple
      newntuple = kFALSE;
      if (debug_out) cout << "Old Ntule found! (jets_b/_c == 0)" << endl;
    }
    else
      if (debug_out) cout << "Can not decide which jetfinder to use! Use Old Ntuple!"<<endl;
  }
  else if ( index == 3 ) { // new ntuple needed for DIS especially for breitframe
    newntuple = kTRUE;
    if (debug_out) cout << "New Ntule found! (Breitframe required)" << endl;
  }
  

  if ( newntuple == kFALSE ){
    fDISPHPJets=0;
  }
  else if (index >= 0 && index <=3) {
    fDISPHPJets=index;
  }
  else { 
    cout << "WARNING: ERROR in GConnectTree::SetDISPHPJets. Can not decide which jetfinder to use!" << endl; 
    return kFALSE;
  }
  if (debug_out) cout << "                                          njet_a=" << Getkt_njet_a() << "  njet_b=" << Getkt_njet_b() << " njet_c=" << Getkt_njet_c()<< " Getkt_njet()=" << Getkt_njet() << " DISPHPJets=" << fDISPHPJets << endl;
  return kTRUE;
}

//_____________________________________________________________

Float_t GConnectTree::Getfmck_q2(){
//    if ( fmck_q2 == 0 && mc_q2 > 0) {
  // fmck_q2 not filled correctly for rapgap and ariadne
    return mc_q2;
//    }
//    else
//      return fmck_q2;
}
//_____________________________________________________________

Int_t GConnectTree::Getmujetfl(Int_t index){
  if ( GetDISPHPJets() == 0)      return Getmujetfl_old(index); // old ntuple
  else if ( GetDISPHPJets() == 1) return Getmujetfl_a(index); // PhP
  else if ( GetDISPHPJets() == 2) return Getmujetfl_b(index); // DIS Labframe
  else if ( GetDISPHPJets() == 3) return Getmujetfl_c(index); // DIS Breitframe
  else {
    cout << "WARNING: ERROR in GConnectTree::Getmujetfl. Can not decide which jetfinder to use!" << endl; 
    return -999;
  }
}

Int_t GConnectTree::Getmujetid(Int_t index){
  if ( GetDISPHPJets() == 0)     return Getmujetid_old(index); // old ntuple 
  else if ( GetDISPHPJets()== 1) return Getmujetid_a(index); // PhP
  else if ( GetDISPHPJets()== 2) return Getmujetid_b(index); // DIS Labframe
  else if ( GetDISPHPJets()== 3) return Getmujetid_c(index); // DIS Breitframe
  else {
    cout << "WARNING: ERROR in GConnectTree::Getmujetid. Can not decide which jetfinder to use!" << endl; 
    return -999;
  }
}
Float_t GConnectTree::Getmujetdr(Int_t index){
  if ( GetDISPHPJets() == 0)     return Getmujetdr_old(index); // old ntuple 
  else if ( GetDISPHPJets()== 1) return Getmujetdr_a(index); // PhP
  else if ( GetDISPHPJets()== 2) return Getmujetdr_b(index); // DIS Labframe
  else if ( GetDISPHPJets()== 3) return Getmujetdr_c(index); // DIS Breitframe
  else {
    cout << "WARNING: ERROR in GConnectTree::Getmujetdr. Can not decide which jetfinder to use!" << endl; 
    return -999.;
  }
}
Float_t GConnectTree::Getmujetpt(Int_t index){
  if ( GetDISPHPJets() == 0)     return Getmujetpt_old(index); // old ntuple 
  else if ( GetDISPHPJets()== 1) return Getmujetpt_a(index); // PhP
  else if ( GetDISPHPJets()== 2) return Getmujetpt_b(index); // DIS Labframe
  else if ( GetDISPHPJets()== 3) return Getmujetpt_c(index); // DIS Breitframe
  else {
    cout << "WARNING: ERROR in GConnectTree::Getmujetpt. Can not decide which jetfinder to use!" << endl; 
    return -999.;
  }
}

Float_t GConnectTree::Getmujetdr2(Int_t index){
  if ( GetDISPHPJets() == 0)     return Getmujetdr2_old(index); // old ntuple 
  else if ( GetDISPHPJets()== 1) return Getmujetdr2_a(index); // PhP
  else if ( GetDISPHPJets()== 2) return Getmujetdr2_b(index); // DIS Labframe
  else if ( GetDISPHPJets()== 3) return Getmujetdr2_c(index); // DIS Breitframe
  else { 
    cout << "WARNING: ERROR in GConnectTree::Getmujetdr2. Can not decide which jetfinder to use!" << endl; 
    return -999.;
  }
}

Float_t GConnectTree::Getmujetpt2(Int_t index){
  if ( GetDISPHPJets() == 0)     return Getmujetpt2_old(index); // old ntuple 
  else if ( GetDISPHPJets()== 1) return Getmujetpt2_a(index); // PhP
  else if ( GetDISPHPJets()== 2) return Getmujetpt2_b(index); // DIS Labframe
  else if ( GetDISPHPJets()== 3) return Getmujetpt2_c(index); // DIS Breitframe
  else { 
    cout << "WARNING: ERROR in GConnectTree::Getmujetpt2. Can not decide which jetfinder to use!" << endl; 
    return -999.;
  }
}

Int_t   GConnectTree::Getkt_njet(){
  if ( GetDISPHPJets()== 0)      return Getkt_njet_a(); // old ntuple
  else if ( GetDISPHPJets()== 1) return Getkt_njet_a(); // PhP
  else if ( GetDISPHPJets()== 2) return Getkt_njet_b(); // DIS Labframe
  else if ( GetDISPHPJets()== 3) return Getkt_njet_c(); // DIS Breitframe
  else { 
    cout << "WARNING: ERROR in GConnectTree::Getkt_njet. Can not decide which jetfinder to use!" << endl; 
    return -999;
  }
}

Float_t GConnectTree::Getkt_etjet(Int_t index){
  if ( GetDISPHPJets()== 0)      return Getkt_etjet_a(index); // old ntuple
  else if ( GetDISPHPJets()== 1) return Getkt_etjet_a(index); // PhP
  else if ( GetDISPHPJets()== 2) return Getkt_etjet_b(index); // DIS Labframe
  else if ( GetDISPHPJets()== 3) return Getkt_etjet_c(index); // DIS Breitframe
  else { 
    cout << "WARNING: ERROR in GConnectTree::Getkt_etjet. Can not decide which jetfinder to use!" << endl; 
    return -999.;
  }
}

Float_t GConnectTree::Getkt_etjetbreit(Int_t index){
  if ( GetDISPHPJets()== 0)      return -999; // old ntuple
  else if ( GetDISPHPJets()== 1) return -999; // no etbreit in php 
  else if ( GetDISPHPJets()== 2) return -999; // no etbreit in labframe
  else if ( GetDISPHPJets()== 3) return Getkt_etjet_d(index); // DIS Breitframe without boost back
  else { 
    cout << "WARNING: ERROR in GConnectTree::Getkt_etjetbreit. Can not decide which jetfinder to use!" << endl; 
    return -999.;
  }
}

Float_t GConnectTree::Getkt_etajet(Int_t index){
  if ( GetDISPHPJets()== 0)      return Getkt_etajet_a(index); // old ntuple
  else if ( GetDISPHPJets()== 1) return Getkt_etajet_a(index); // PhP
  else if ( GetDISPHPJets()== 2) return Getkt_etajet_b(index); // DIS Labframe
  else if ( GetDISPHPJets()== 3) return Getkt_etajet_c(index); // DIS Breitframe
  else { 
    cout << "WARNING: ERROR in GConnectTree::Getkt_etajet. Can not decide which jetfinder to use!" << endl; 
    return -999.;
  }
}

Float_t GConnectTree::Getkt_phijet(Int_t index){
  if ( GetDISPHPJets()== 0)      return Getkt_phijet_a(index); // old ntuple
  else if ( GetDISPHPJets()== 1) return Getkt_phijet_a(index); // PhP
  else if ( GetDISPHPJets()== 2) return Getkt_phijet_b(index); // DIS Labframe
  else if ( GetDISPHPJets()== 3) return Getkt_phijet_c(index); // DIS Breitframe
  else { 
    cout << "WARNING: ERROR in GConnectTree::Getkt_phijet. Can not decide which jetfinder to use!" << endl; 
    return -999.;
  }
}

Float_t GConnectTree::Getkt_masjet(Int_t index){
  if ( GetDISPHPJets()== 0)      return Getkt_masjet_a(index); // old ntuple
  else if ( GetDISPHPJets()== 1) return Getkt_masjet_a(index); // PhP
  else if ( GetDISPHPJets()== 2) return Getkt_masjet_b(index); // DIS Labframe
  else if ( GetDISPHPJets()== 3) return Getkt_masjet_c(index); // DIS Breitframe
  else { 
    cout << "WARNING: ERROR in GConnectTree::Getkt_masjet. Can not decide which jetfinder to use!" << endl; 
    return -999.;
  }
}

//_____________________________________________________________

Double_t GConnectTree:: Gettrk_zzero(Int_t index){
  if (gCards->GetNewNtuple())trk_zzero[index]=trk_helpar[index][3]*10;
  return trk_zzero[index];
}
//_____________________________________________________________

Double_t GConnectTree:: Gettrk_dzero(Int_t index){
  if (gCards->GetNewNtuple())trk_dzero[index]=trk_helpar[index][2]*10;
  return trk_dzero[index];
}
//_____________________________________________________________

Double_t GConnectTree:: Gettrk_w(Int_t index)  {

  if (gCards->GetNewNtuple())trk_w[index]=trk_helpar[index][1]/10;

  return trk_w[index];
}
//_____________________________________________________________

Double_t GConnectTree:: Gettrk_t(Int_t index)  {

  if (gCards->GetNewNtuple())trk_t[index]=trk_helpar[index][4];

  return trk_t[index];
}
//_____________________________________________________________

Double_t GConnectTree:: Gettrk_phizero(Int_t index)  {

  if (gCards->GetNewNtuple())trk_phizero[index]=trk_helpar[index][0];

  return trk_phizero[index];
}
//_____________________________________________________________

Double_t GConnectTree:: Gettrk_cov(Int_t index, Int_t index2)  {

  if (gCards->GetNewNtuple())trk_cov[index][index2]=trk_covmat[index][index2];

  return trk_cov[index][index2];
}


