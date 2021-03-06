//
// GConnectTree.h
//
// $Author: ibloch $
// $Date: 2007/01/04 22:32:03 $
// $Revision: 1.29 $
//

#ifndef GUT_GConnectTree
#define GUT_GConnectTree

#ifndef ROOT_TObject
#include <TObject.h>
#endif

//class iostream;
class TChain;
class GConnectTree : public TObject {

 private:

  Bool_t      fOK;    // flag tells if object was created all right

  // Declaration of leaves types, name of block respect orange block name

  // BAC
  Float_t         bac_etot;
  Float_t         bac_etot_o2r;
  UInt_t          bac_npad;
  UInt_t          bac_npad_o2r;
  Float_t         bac_et;
  Float_t         bac_px;
  Float_t         bac_py;
  Int_t           nbacmu;
  Float_t         mubac_xyz[150][3];   //[nbacmu]
  Float_t         mubac_dxyz[150][3];  //[nbacmu]
  Float_t         mubac_cos[150][3];   //[nbacmu]
  Float_t         mubac_dcos[150][3];  //[nbacmu]
  Float_t         mubac_eloss[150];    //[nbacmu]
  Float_t         mubac_deloss[150];   //[nbacmu]
  UInt_t          mubac_unit[150];     //[nbacmu]
  UInt_t          mubac_dim[150];      //[nbacmu]
  UInt_t          mubac_quality[150];  //[nbacmu]
  UInt_t          ahit[150];           //[nbacmu]
  UInt_t          pad[150];            //[nbacmu]


  // BACMAT

  Int_t           bm_n;
  Int_t           bm_idvc[100];
  Int_t           bm_idmubac[100];
  Int_t           bm_istop[100];
  Int_t           bm_error[100];
  Int_t           bm_readout[100];

  // CAL
  Float_t         cal_px;
  Float_t         cal_py;
  Float_t         cal_pz;
  Float_t         cal_e;
  Float_t         cal_et;
  Float_t         cal_empz;
  Float_t         cal_pt;
  Float_t         cal_phi;
  Float_t         remc[6];
  Float_t         bemc[6];
  Float_t         femc[6];
  Float_t         rhac[6];
  Float_t         bhac[6];
  Float_t         fhac[6];
  Float_t         bhac2[6];
  Float_t         fhac2[6];
  Int_t           nfemc;
  Int_t           nfhac1;
  Int_t           nfhac2;
  Int_t           nbemc;
  Int_t           nbhac1;
  Int_t           nbhac2;
  Int_t           nremc;
  Int_t           nrhac;
  Float_t         cal_tf;
  Float_t         cal_tb;
  Float_t         cal_tr;
  Float_t         cal_tg;
  /*
  Float_t         cal_tf_e;
  Float_t         cal_tb_e;
  Float_t         cal_tr_e;
  Float_t         cal_tg_e;
  UInt_t          cal_tf_n;
  UInt_t          cal_tb_n;
  UInt_t          cal_tr_n;
  UInt_t          cal_tg_n;
  */
  Float_t         etamax_ce;
  Float_t         etamax_ce4;
  Float_t         cal_et10;
  Float_t         mtrknoe_pi;
  Float_t         mtrknoe_k;
  Float_t         e_hk;
  Float_t         unmen_pi;
  Float_t         unmen_k;
  Int_t           sparkf;

  // FCALIR
  Float_t         pex1ir[4];
  Float_t         et1ir;
  Float_t         etex1ir;
  Float_t         pex2ir[4];
  Float_t         et2ir;
  Float_t         etex2ir;

  // RCALIR
  Float_t         percir[4];
  Float_t         etrcir;   

  // EVENT
  Int_t           runnr;
  Int_t           eventnr;

  // TAKEINFO

  Int_t           mvdtake;

  //GMUON
  Int_t           nmu;
  Int_t           muqual[20];       //[nmu]
  Int_t           mucharge[20];     //[nmu]
  Float_t         mupt[20];         //[nmu]
  Float_t         muth[20];         //[nmu]
  Float_t         muph[20];         //[nmu]
  Float_t         mup[20][3];       //[nmu]
  Float_t         muperr[20];       //[nmu]
  Int_t           mutrfl[20];       //[nmu]
  Int_t           mutrid[20];       //[nmu]
  Int_t           muvcid[20];       //[nmu]
  Int_t           muztid[20];       //[nmu]    //real new 041118
  Int_t           mustid[20];       //[nmu]    //real new 041118
  Int_t           muvtxfl[20];      //[nmu]
  Int_t           muvtxid[20];      //[nmu]
  Int_t           muglomu[20];      //[nmu]
  Int_t           mubremat[20];     //[nmu]
  Int_t           mubacmat[20];     //[nmu]
  Int_t           mumubac[20];      //[nmu]
  Int_t           mumamma[20];      //[nmu]
  Int_t           mumpmat[20];      //[nmu]
  Int_t           mumufo[20];       //[nmu]
  Int_t           munphi[20];       //[nmu]
  Int_t           mumip[20];        //[nmu]
  Int_t           mumv[20];         //[nmu]
  Int_t           mucalfl[20];      //[nmu]
  Float_t         mucalene[20];     //[nmu]    //real new 041118
  Float_t         muhac2[20];       //[nmu]    //real new 041118
  Int_t           muzufid[20];      //[nmu]
  Float_t         muisol[20][10];   //[nmu]    //real new 041118
  Int_t           munis[20][10];    //[nmu]    //real new 041118
  Float_t         muisdrmip[20][2]; //[nmu]    //real new 041118
  Float_t         muisetmip[20][2]; //[nmu]    //real new 041118
  Int_t           muistumip[20][2]; //[nmu]    //real new 041118
  Float_t         mupmip[20];       //[nmu]
  Float_t         muhene[20];       //[nmu]
  Float_t         mutime[20];       //[nmu]    //real new 041118
  Int_t           muchfl[20];       //[nmu]
  Int_t           muchid[20];       //[nmu]
  Float_t         mupmat[20];       //[nmu]
  Bool_t          new_mubacdca;
  Float_t         mubacdca[20];     //[nmu]
  Int_t           mubacfl[20];      //[nmu]
  Int_t           mubacid[20];      //[nmu]
  Int_t           mudxy[20];        //[nmu]    //real new 041118
  Int_t           mudz[20];         //[nmu]    //real new 041118

  // variables important for dcache mode
  Int_t           mundof[20];       //[nmu]
  Float_t         muz[20];          //[nmu]
  Float_t         muprec[20];       //[nmu]

  // GMU_JET
  Int_t           mujetfl[20];      //[nmu]
  Int_t           mujetid[20];      //[nmu]
  Float_t         mujetdr[20];      //[nmu]
  Float_t         mujetpt[20];      //[nmu]
  Float_t         mujetdr2[20];     //[nmu]     //real new 041118
  Float_t         mujetpt2[20];     //[nmu]     //real new 041118
  Int_t           muhjet_id[20];    //[nmu]

  // GMU_JET_A
  Int_t           mujetfl_a[20];    //[nmu]
  Int_t           mujetid_a[20];    //[nmu]
  Float_t         mujetdr_a[20];    //[nmu]
  Float_t         mujetpt_a[20];    //[nmu]
  Float_t         mujetdr2_a[20];   //[nmu]     //real new 041118
  Float_t         mujetpt2_a[20];   //[nmu]     //real new 041118
  Int_t           muhjet_id_a[20];  //[nmu]

  // GMU_JET_B
  Int_t           mujetfl_b[20];    //[nmu]
  Int_t           mujetid_b[20];    //[nmu]
  Float_t         mujetdr_b[20];    //[nmu]
  Float_t         mujetpt_b[20];    //[nmu]
  Float_t         mujetdr2_b[20];   //[nmu]
  Float_t         mujetpt2_b[20];   //[nmu]
  Int_t           muhjet_id_b[20];  //[nmu]

  // GMU_JET_C
  Int_t           mujetfl_c[20];    //[nmu]
  Int_t           mujetid_c[20];    //[nmu]
  Float_t         mujetdr_c[20];    //[nmu]
  Float_t         mujetpt_c[20];    //[nmu]
  Float_t         mujetdr2_c[20];   //[nmu]
  Float_t         mujetpt2_c[20];   //[nmu]
  Int_t           muhjet_id_c[20];  //[nmu]

  // GMU_JET_D
  Int_t           mujetfl_d[20];    //[nmu]
  Int_t           mujetid_d[20];    //[nmu]
  Float_t         mujetdr_d[20];    //[nmu]
  Float_t         mujetpt_d[20];    //[nmu]
  Float_t         mujetdr2_d[20];   //[nmu]
  Float_t         mujetpt2_d[20];   //[nmu]
  Int_t           muhjet_id_d[20];  //[nmu]

  // GMU_MC
  Int_t           muick[20];        //[nmu]
  Int_t           mupartyp[20];     //[nmu]
  Float_t         mumc_p[20][4];    //[nmu]
  Int_t           mudirtyp[20];     //[nmu]
  Float_t         mumc_d[20][4];    //[nmu]
  Int_t           muqtyp[20];       //[nmu]
  Float_t         mumc_q[20][4];    //[nmu]
  Int_t           mutruefl[20];     //[nmu]
  Float_t         mudecdist[20];    //[nmu]
  // FMCKIN
  Int_t           npart;            
  Int_t           part_id[511];     //[npart]
  Int_t           part_prt[511];    //[npart]
  Float_t         part_p[511][4];   //[npart]


  //JETS
  Int_t           fDISPHPJets;
  // ktJETS_A
  Int_t           kt_njet_a;
  Float_t         kt_etjet_a[512];    //[kt_njet_a]
  Float_t         kt_etajet_a[512];   //[kt_njet_a]
  Float_t         kt_phijet_a[512];   //[kt_njet_a]
  Float_t         kt_masjet_a[512];   //[kt_njet_a]

  // ktJETS_B
  Int_t           kt_njet_b;
  Float_t         kt_etjet_b[512];    //[kt_njet_b]
  Float_t         kt_etajet_b[512];   //[kt_njet_b]
  Float_t         kt_phijet_b[512];   //[kt_njet_b]
  Float_t         kt_masjet_b[512];   //[kt_njet_b]

  // ktJETS_C
  Int_t           kt_njet_c;
  Float_t         kt_etjet_c[512];    //[kt_njet_c]
  Float_t         kt_etajet_c[512];   //[kt_njet_c]
  Float_t         kt_phijet_c[512];   //[kt_njet_c]
  Float_t         kt_masjet_c[512];   //[kt_njet_c]

  // ktJETS_D
  Int_t           kt_njet_d;
  Float_t         kt_etjet_d[512];    //[kt_njet_d]
  Float_t         kt_etajet_d[512];   //[kt_njet_d]
  Float_t         kt_phijet_d[512];   //[kt_njet_d]
  Float_t         kt_masjet_d[512];   //[kt_njet_d]

  // MCSUMS
  Float_t         mc_ez;
  Float_t         mc_esum;
  Float_t         mc_etcone;
  Float_t         mc_ercal;

  // MCJETS
  Int_t           mc_njet;
  Float_t         mc_etj[4];   //[mc_njet]
  Float_t         mc_rapj[4];  //[mc_njet]
  Float_t         mc_phij[4];  //[mc_njet]
  Float_t         mc_pxj[4];   //[mc_njet]
  Float_t         mc_pyj[4];   //[mc_njet]
  Float_t         mc_pzj[4];   //[mc_njet]
  Float_t         mc_ej[4];    //[mc_njet]

  // MCKINE
  Float_t         mc_el;
  Float_t         mc_ep;
  Float_t         mc_x;
  Float_t         mc_y;
  Float_t         mc_q2;
  Float_t         mc_mu;
  Float_t         mc_pt;
  Float_t         mc_xpro;
  Float_t         mc_xgam;
  Float_t         mc_xpom;
  Float_t         mc_beta;
  Float_t         mc_t;
  Int_t           mc_idl;
  Int_t           mc_pidl;
  Int_t           mc_pidp;
  Int_t           mc_idfsl;
  Float_t         mc_pfsl[4];
  Float_t         mc_pfsph[4];
  Float_t         mc_vtx[3];
  Int_t           mc_ichnn;

  // MCVTX
  Float_t         mcvtx[3];

  // MUON
  Int_t           nomu;
  Int_t           bmuon1;
  Int_t           bmuon2;
  Float_t         bmnrmips;
  Float_t         bmmmtrk;
  Int_t           muonf1;
  Int_t           muonf2;
  Float_t         mupt1;
  Float_t         muth1;
  Float_t         muph1;
  Float_t         mupt2;
  Float_t         muth2;
  Float_t         muph2;
  Int_t           fmntrk;
  Int_t           fmntrp;
  Int_t           fmangr;
  Float_t         fmrecp;
  Float_t         fmmatch;
  Float_t         mbchi2[2];
  Float_t         mbp[3][2];
  Float_t         mbdca[2];
  Int_t           mbtrfl[2];

  // FMU_MPM
  Int_t           nfmu;
  Float_t         fmux[5];       //[nfmu]
  Float_t         fmuy[5];       //[nfmu]
  Float_t         fmuz[5];       //[nfmu]
  Float_t         fmuchi[5];     //[nfmu]
  Float_t         fmuprob[5];    //[nfmu]
  Int_t           fmuti[5];      //[nfmu]
  Int_t           fmufi[5];      //[nfmu]
  Float_t         fmutqor[5];    //[nfmu]
  Float_t         fmutz[5];      //[nfmu]
  Float_t         fmutqd[5];     //[nfmu]
  Float_t         fmutchi[5];    //[nfmu]
  Int_t           fmutndf[5];    //[nfmu]
  Int_t           fmutksw[5];    //[nfmu]

  // FMUmfrtz
  Int_t           nmf;
  Float_t         mfx[10];        //[nmf]
  Float_t         mfy[10];        //[nmf]
  Float_t         mfz[10];        //[nmf]
  Float_t         mfvx[10];       //[nmf]
  Float_t         mfvy[10];       //[nmf]
  Float_t         mfqop[10];      //[nmf]
  Int_t           mfo[10];        //[nmf]
  Int_t           mfndf[10];      //[nmf]
  Float_t         mfpro[10];      //[nmf]
  Int_t           mfndff[10];     //[nmf]
  Float_t         mfprof[10];     //[nmf]
  Int_t           mfhdc[10];      //[nmf]
  Int_t           mfhlt[10];      //[nmf]
  Int_t           fmusid[10];     //[nmf]
  Int_t           fmushr[10];     //[nmf]
  Float_t         fmusrchi[10];   //[nmf]
  Int_t           fmusnr[10];     //[nmf]
  Int_t           fmushp[10];     //[nmf]
  Int_t           fmusnp[10];     //[nmf]
  Float_t         fmusp[10];      //[nmf]
  Float_t         fmusthe[10];    //[nmf]
  Float_t         fmusphi[10];    //[nmf]

  // MV
  Int_t           umv_ncmuo;
  Int_t           umv_trkmuo[50];   //[umv_ncmuo]
  Int_t           umv_trrmuo[50];   //[umv_ncmuo]
  Int_t           umv_trnmuo[50];   //[umv_ncmuo]
  Int_t           umv_trqmuo[50];   //[umv_ncmuo]
  Int_t           umv_tobr[50];     //[umv_ncmuo]
  Float_t         umv_trmmuo[50];   //[umv_ncmuo]
  Float_t         umv_trtmuo[50];   //[umv_ncmuo]
  Float_t         umv_trpmuo[50];   //[umv_ncmuo]
  Float_t         umv_trcmuo[50];   //[umv_ncmuo]
  Float_t         umv_tremuo[50];   //[umv_ncmuo]
  Float_t         umv_trdmuo[50];   //[umv_ncmuo]
  Float_t         umv_timuo[50];    //[umv_ncmuo]
  Float_t         umv_xcmuo[50];    //[umv_ncmuo]
  Float_t         umv_ycmuo[50];    //[umv_ncmuo]
  Float_t         umv_zcmuo[50];    //[umv_ncmuo]
  Float_t         umv_heemuo[50];   //[umv_ncmuo]
  Float_t         umv_hexmuo[50];   //[umv_ncmuo]
  Float_t         umv_heymuo[50];   //[umv_ncmuo]
  Float_t         umv_hezmuo[50];   //[umv_ncmuo]
  Float_t         umv_prmuo[50];    //[umv_ncmuo]
  Float_t         umv_efmuo[50];    //[umv_ncmuo]
  Float_t         umv_comuo[50];    //[umv_ncmuo]
  Float_t         umv_pumuo[50];    //[umv_ncmuo]
  Float_t         umv_prcmuo[50];   //[umv_ncmuo]
  Float_t         umv_efcmuo[50];   //[umv_ncmuo]
  Float_t         umv_cocmuo[50];   //[umv_ncmuo]
  Float_t         umv_pucmuo[50];   //[umv_ncmuo]
  Float_t         umv_ecamuo[50];   //[umv_ncmuo]
  Float_t         uex_calmuo[50];   //[umv_ncmuo]
  Float_t         uey_calmuo[50];   //[umv_ncmuo]
  Float_t         uez_calmuo[50];   //[umv_ncmuo]
  Float_t         uet_calmuo[50];   //[umv_ncmuo]

  // SIRA
  Int_t           sincand;
  Int_t           sierror;
  Float_t         siprob[4];      //[sincand]
  Float_t         sipos[4][3];    //[sincand]
  Float_t         sicalpos[4][3]; //[sincand]
  Float_t         sicalene[4];    //[sincand]
  Float_t         siein[4];       //[sincand]
  Float_t         sienin[4];      //[sincand]
  Float_t         siecorr[4][3];  //[sincand]
  Float_t         sith[4];        //[sincand]
  Float_t         siph[4];        //[sincand]
  Float_t         sipt[4];        //[sincand]
  UInt_t          sixdet[4][3];   //[sincand]
  UInt_t          siydet[4][3];   //[sincand]

  // SI_TRK
  UInt_t          sitrknr[4];     //[sincand]
  UInt_t          sinrsl[4];      //[sincand]
  Float_t         sidca[4];       //[sincand]
  Float_t         sitrkp[4];      //[sincand]
  Float_t         sitrkth[4];     //[sincand]
  Float_t         sitrkph[4];     //[sincand]
  Float_t         sitrkq[4];      //[sincand]
  Float_t         sitrkdme[4];    //[sincand]
  Float_t         sitrkpos[4][3]; //[sincand]

  // SI_DET
  UInt_t          sisrtf[4];      //[sincand]
  UInt_t          sisrtquad[4];   //[sincand]
  Int_t           sihesf[4];      //[sincand]
  UInt_t          sicorrcode[4];  //[sincand]
  Float_t         sisrtpos[4][2]; //[sincand]
  Float_t         sisrtene[4];    //[sincand]
  Float_t         sihespos[4][2]; //[sincand]
  Float_t         sihesene[4];    //[sincand]
  Float_t         sihesr[4];      //[sincand]
  Float_t         siprsene[4][3]; //[sincand]
  // SI_HAD
  Float_t         siccet[4];      //[sincand]
  Float_t         siccempz[4];    //[sincand]
  Float_t         sietamax[4];    //[sincand]
  Float_t         sicehmom[4][4]; //[sincand]
  Float_t         sizuhmom[4][4]; //[sincand]
  Float_t         sicchmom[4][4]; //[sincand]

  // SI_KIN
  Float_t         sixel[4];       //[sincand]
  Float_t         siyel[4];       //[sincand]
  Float_t         siq2el[4];      //[sincand]
  Float_t         sixda[4];       //[sincand]
  Float_t         siyda[4];       //[sincand]
  Float_t         siq2da[4];      //[sincand]
  Float_t         sixda_cell[4];  //[sincand]
  Float_t         siyda_cell[4];  //[sincand]
  Float_t         siq2da_cell[4]; //[sincand]
  Float_t         sixjb[4];       //[sincand]
  Float_t         siyjb[4];       //[sincand]
  Float_t         siq2jb[4];      //[sincand]
  Float_t         sixjb_cell[4];  //[sincand]
  Float_t         siyjb_cell[4];  //[sincand]
  Float_t         siq2jb_cell[4]; //[sincand]

  // SI_CELLS
  UInt_t          sincell[4];     //[sincand]    
  UInt_t          sicellptr[4];   //[sincand]  

  // TRIGGER
  UInt_t           fltw[2];
  UInt_t           fltpsw[2];
  UInt_t           fltfl;
  UInt_t           gslt_global;
  UInt_t           sltw[6];
  UInt_t           sltupw[6];   //real new 041118
  UInt_t           tltw[15];
  UInt_t           dstw[4];
  UInt_t           fltfcw[2];
  UInt_t           fltpsfcw[2];

  // ADDITIONAL TRIGGER INFO     
  UInt_t           bitword[2];    
  UInt_t           fltdat_trkmul; 
  UInt_t           fltdat_vtxtrk; 
  UInt_t           fltdat_trkcl;  

  // VERTEX
  Int_t           ntrkvtx;
  Float_t         xvtx;
  Float_t         yvtx;
  Float_t         zvtx;
  Float_t         chivtx;
  Int_t           nsecvtx;
  Float_t         xsecvtx[40];        //[nsecvtx]
  Float_t         ysecvtx[40];        //[nsecvtx]
  Float_t         zsecvtx[40];        //[nsecvtx]
  Float_t         chisecvtx[40];      //[nsecvtx]
  Float_t         fetatr;
  Float_t         betatr;
  Float_t         pt_tr;
  Float_t         empz_tr_pi;
  Float_t         et_tr;
  Float_t         e_tr_pi;
  Float_t         phi_tr;
  Float_t         zvtx_fcal;
  UInt_t          fcal_nrgoodcells;
  Float_t         fcal_vzerr;

  // BSPOT

  Float_t         bspt_x;
  Float_t         bspt_y;
  Float_t         bspt_z;

  // ZUFOS
  Float_t         v_h_px_zu;
  Float_t         v_h_py_zu;
  Float_t         v_h_pz_zu;
  Float_t         v_h_e_zu;
  Float_t         etamax_zu;
  Float_t         etamax_zu4;
  Float_t         fgap;
  Float_t         bgap;
  Int_t           nzufos;
  UInt_t          tufo[1000][4];       //[nzufos]
  UInt_t          zufo_bsp[1000];      //[nzufos]     //real new 041118
  Float_t         zufo[1000][4];       //[nzufos]
  Float_t         zufoeemc[1000];      //[nzufos]   

  // Tracking
  Int_t           trk_ntracks;
  UInt_t          trk_type[300];       //[trk_ntracks]
  UInt_t          ntrack_type[4];
  UInt_t          def_trk_type;
  UInt_t          trk_id[300];         //[trk_ntracks]
  Int_t           trk_id2[300];        //[trk_ntracks]
  Float_t         trk_px[300];         //[trk_ntracks]
  Float_t         trk_py[300];         //[trk_ntracks]
  Float_t         trk_pz[300];         //[trk_ntracks]
  Float_t         trk_charge[300];     //[trk_ntracks]

  // Trk_vtx
  Int_t           trk_vtx[300];        //[trk_ntracks]      
  UChar_t         trk_prim_vtx[300];   //[trk_ntracks] 
  UChar_t         trk_sec_vtx[300];    //[trk_ntracks]  
  UInt_t          trk_vxid[300];       //[trk_ntracks]     

  // Trk_qual
  Float_t         trk_endpos[300][3];  //[trk_ntracks]
  UInt_t          trk_nzbyt[300];      //[trk_ntracks]    
  UInt_t          trk_naxial[300];     //[trk_ntracks]   
  UInt_t          trk_nstereo[300];    //[trk_ntracks]  
  UInt_t          trk_ndof[300];       //[trk_ntracks]     
  UInt_t          trk_layinner[300];   //[trk_ntracks] 
  UInt_t          trk_layouter[300];   //[trk_ntracks] 
  Float_t         trk_dedxctd[300];    //[trk_ntracks]  
  Float_t         trk_dedxctdcr[300];  //[trk_ntracks]
  Float_t         trk_chi2[300];       //[trk_ntracks]     
  Float_t         trk_vchi2[300];      //[trk_ntracks]    

  // Trk_MVD
  UInt_t          trk_nbr[300];        //[trk_ntracks]      
  UInt_t          trk_nbz[300];        //[trk_ntracks]      
  UInt_t          trk_nwu[300];        //[trk_ntracks]      
  UInt_t          trk_nwv[300];        //[trk_ntracks]      
  Float_t         trk_dedxmvd[300];    //[trk_ntracks]  
  Float_t         trk_w[300];          //[trk_ntracks]	       
  Float_t         trk_phizero[300];    //[trk_ntracks]  
  Float_t         trk_t[300];          //[trk_ntracks]	       
  Float_t         trk_dzero[300];      //[trk_ntracks]    
  Float_t         trk_zzero[300];      //[trk_ntracks]    
  Float_t         trk_cov[300][15];    //[trk_ntracks]
 
 //trk_mvd new style  
  Float_t         trk_helpar[300][5];  //[trk_ntracks]  
  Float_t         trk_covmat[300][15]; //[trk_ntracks]  

  // Trk_imp
  Float_t         trk_imppar[300];      //[trk_ntracks] 
  Float_t         trk_imperr[300];      //[trk_ntracks] 
  Float_t         trk_pca[300][3];      //[trk_ntracks] 

  // SECVTX
  Float_t         vtxredprm_x;
  Float_t         vtxredprm_y;
  Float_t         vtxredprm_z;
  Float_t         vtxredprm_chi2;
  Float_t         vtxredprm_cov[6];
  Float_t         vtxredprm_ndf;
  Int_t           nr_secvtx;
  Float_t         vtxsec_x[300];         //[nr_secvtx]
  Float_t         vtxsec_y[300];         //[nr_secvtx]
  Float_t         vtxsec_z[300];         //[nr_secvtx]
  Float_t         vtxsec_mass[300];      //[nr_secvtx]
  Float_t         vtxsec_chi2[300];      //[nr_secvtx]
  Float_t         vtxsec_ndf[300];       //[nr_secvtx]
  UInt_t          vtxsec_multi[300];     //[nr_secvtx]
  Float_t         vtxsec_cov[300][6];    //[nr_secvtx]
  UInt_t          vtxsec_zttid[300][15]; //[nr_secvtx]
  Float_t         vtxsec2d_x[300];       //[nr_secvtx]
  Float_t         vtxsec2d_y[300];       //[nr_secvtx]
  Float_t         vtxsec2d_z[300];       //[nr_secvtx]
  Float_t         vtxsec2d_mass[300];    //[nr_secvtx]
  Float_t         vtxsec2d_chi2[300];    //[nr_secvtx]
  Float_t         vtxsec2d_ndf[300];     //[nr_secvtx]
  Float_t         vtxsec2d_cov[300][6];  //[nr_secvtx]

  // VCTRHLa
  Int_t           nvctrhl;                             
  UInt_t          vctrhl_id[300];      //[nvctrhl]	       
  UInt_t          vctrhl_trkn[300];    //[nvctrhl]      
  Float_t         vctrhl_qovr[300];    //[nvctrhl]      
  Float_t         vctrhl_zh[300];      //[nvctrhl]	       
  Float_t         vctrhl_pgevc[300];   //[nvctrhl]     
  Int_t           vcatcal_kodswm[300]; //[nvctrhl]   

  // BREMAT
  Int_t           brenmu;
  Int_t           bremat_nmatch;
  Int_t           bremat_everror;
  Int_t           bremat_error[10];        //[brenmu]
  Int_t           bremat_ivc[10];          //[brenmu]
  Int_t           bremat_imu[10];          //[brenmu]
  Float_t         bremat_delta[10];        //[brenmu]
  Float_t         bremat_xres[10];         //[brenmu]
  Float_t         bremat_yres[10];         //[brenmu]
  Float_t         bremat_slopxres[10];     //[brenmu]
  Float_t         bremat_slopyres[10];     //[brenmu]
  Float_t         bremat_invpres[10];      //[brenmu]
  Float_t         bremat_covres[10][15];   //[brenmu]
  Float_t         bremat_chi2mat[10];      //[brenmu]
  Float_t         bremat_probmat[10];      //[brenmu]
  Float_t         bremat_chi2matp[10];     //[brenmu]
  Float_t         bremat_probmatp[10];     //[brenmu]
  Float_t         bremat_endpos[10][3];    //[brenmu]

  // own fmckin block
  Int_t           fmck_nkin;
  Float_t         fmck_q2;
  Float_t         fmck_w;
  Float_t         fmck_xg;
  Int_t           fmck_nstor;
  Int_t           fmck_id[100];        //[fmck_nstor]
  Float_t         fmck_px[100];        //[fmck_nstor]
  Float_t         fmck_py[100];        //[fmck_nstor]
  Float_t         fmck_pz[100];        //[fmck_nstor]
  Float_t         fmck_e[100];         //[fmck_nstor]
  Float_t         fmck_m[100];         //[fmck_nstor]
  //  Float_t         fmck_pt[100];    //[fmck_nstor]
  //  Float_t         fmck_eta[100];   //[fmck_nstor]
  Int_t           fmck_daug[100];      //[fmck_nstor]
  Int_t           fmck_prt[100];       //[fmck_nstor]
  Int_t           fmck_prat[100];      //[fmck_nstor]
  Float_t         fmck_impar[100];     //[fmck_nstor]
  Float_t         fmck_impar2[100];    //[fmck_nstor]

  // new

  //  Float_t         fmck_dsignif[100];   //[fmck_nstor]
  //  Float_t         fmck_dsignif2[100];  //[fmck_nstor]
  Int_t           fmvtx_nstor;
  Int_t           fmvtx_id[100];       //[fmvtx_nstor]
  Float_t         fmvtx_r[100][3];     //[fmvtx_nstor]
  Float_t         fmvtx_time[100];     //[fmvtx_nstor]
  Int_t           fmvtx_prby[100];     //[fmvtx_nstor]

  // own MC jets
  Float_t         fmck_hadjet[100];    //[fmck_nstor]
  Float_t         fmck_mhadjet[100];   //[fmck_nstor]
  Float_t         fmck_bhadjet[100];   //[fmck_nstor]
  Float_t         fmck_mbhadjet[100];  //[fmck_nstor]
  Float_t         fmck_partjet[100];   //[fmck_nstor]
  Float_t         fmck_mpartjet[100];  //[fmck_nstor]
  Int_t           nhjets;
  Float_t         pxhjet[10];    //[nhjets]
  Float_t         pyhjet[10];    //[nhjets]
  Float_t         pzhjet[10];    //[nhjets]
  Float_t         ehjet[10];     //[nhjets]
  Int_t           nhmjets;
  Float_t         pxhmjet[10];   //[nhmjets]
  Float_t         pyhmjet[10];   //[nhmjets]
  Float_t         pzhmjet[10];   //[nhmjets]
  Float_t         ehmjet[10];    //[nhmjets]
  Int_t           nhbjets;
  Float_t         pxhbjet[10];   //[nhbjets]
  Float_t         pyhbjet[10];   //[nhbjets]
  Float_t         pzhbjet[10];   //[nhbjets]
  Float_t         ehbjet[10];    //[nhbjets]
  Int_t           nhbmjets;
  Float_t         pxhbmjet[10];  //[nhbmjets]
  Float_t         pyhbmjet[10];  //[nhbmjets]
  Float_t         pzhbmjet[10];  //[nhbmjets]
  Float_t         ehbmjet[10];   //[nhbmjets]
  Int_t           npjets;
  Float_t         pxpjet[10];    //[npjets]
  Float_t         pypjet[10];    //[npjets]
  Float_t         pzpjet[10];    //[npjets]
  Float_t         epjet[10];     //[npjets]
  Int_t           npmjets;
  Float_t         pxpmjet[10];   //[npmjets]
  Float_t         pypmjet[10];   //[npmjets]
  Float_t         pzpmjet[10];   //[npmjets]
  Float_t         epmjet[10];    //[npmjets]

  // OWN VARIABLES
  Int_t           zes_select;
  Float_t         lumi[2];

 public:
  GConnectTree(TChain *chain);
  virtual ~GConnectTree();
  virtual Bool_t Init(TChain *chain);
  inline virtual Bool_t IsOK()                                     { return fOK;}

  // access functions
  inline virtual Float_t Getbac_etot()                             { return bac_etot;}
  inline virtual Float_t Getbac_etot_o2r()                         { return bac_etot_o2r;}
  inline virtual UInt_t  Getbac_npad()                             { return bac_npad;}
  inline virtual UInt_t  Getbac_npad_o2r()                         { return bac_npad_o2r;}
  inline virtual Float_t Getbac_et()                               { return bac_et;}
  inline virtual Float_t Getbac_px()                               { return bac_px;}
  inline virtual Float_t Getbac_py()                               { return bac_py;}
  inline virtual Int_t   Getnbacmu()                               { return nbacmu;}
  inline virtual Float_t Getmubac_xyz(Int_t index, Int_t coord)    { return mubac_xyz[index][coord];}
  inline virtual Float_t Getmubac_dxyz(Int_t index, Int_t coord)   { return mubac_dxyz[index][coord];}
  inline virtual Float_t Getmubac_cos(Int_t index, Int_t coord)    { return mubac_cos[index][coord];}
  inline virtual Float_t Getmubac_dcos(Int_t index, Int_t coord)   { return mubac_dcos[index][coord];}
  inline virtual Float_t Getmubac_eloss(Int_t index)               { return mubac_eloss[index];}
  inline virtual Float_t Getmubac_deloss(Int_t index)              { return mubac_deloss[index];}
  inline virtual UInt_t  Getmubac_unit(Int_t index)                { return mubac_unit[index];}
  inline virtual UInt_t  Getmubac_dim(Int_t index)                 { return mubac_dim[index];}
  inline virtual UInt_t  Getmubac_quality(Int_t index)             { return mubac_quality[index];}
  inline virtual UInt_t  Getahit(Int_t index)                      { return ahit[index];}
  inline virtual UInt_t  Getpad(Int_t index)                       { return pad[index];}

  // BACMAT

  inline virtual Int_t GetBm_n()                                   { return bm_n;}
  inline virtual Int_t GetBm_idvc(Int_t index)                     { return bm_idvc[index];}
  inline virtual Int_t GetBm_idmubac(Int_t index)                  { return bm_idmubac[index];}
  inline virtual Int_t GetBm_istop(Int_t index)                    { return bm_istop[index];}
  inline virtual Int_t GetBm_error(Int_t index)                    { return bm_error[index];}
  inline virtual Int_t GetBm_readout(Int_t index)                  { return bm_readout[index];}

  // CAL
  inline virtual Float_t Getcal_px()                               { return cal_px;}
  inline virtual Float_t Getcal_py()                               { return cal_py;}
  inline virtual Float_t Getcal_pz()                               { return cal_pz;}
  inline virtual Float_t Getcal_e()                                { return cal_e;}
  inline virtual Float_t Getcal_et()                               { return cal_et;}
  inline virtual Float_t Getcal_empz()                             { return cal_empz;}
  inline virtual Float_t Getcal_pt()                               { return cal_pt;}
  inline virtual Float_t Getcal_phi()                              { return cal_phi;}
  inline virtual Float_t Getremc(Int_t index)                      { return remc[index];}
  inline virtual Float_t Getbemc(Int_t index)                      { return bemc[index];}
  inline virtual Float_t Getfemc(Int_t index)                      { return femc[index];}
  inline virtual Float_t Getrhac(Int_t index)                      { return rhac[index];}
  inline virtual Float_t Getbhac(Int_t index)                      { return bhac[index];}
  inline virtual Float_t Getfhac(Int_t index)                      { return fhac[index];}
  inline virtual Float_t Getbhac2(Int_t index)                     { return bhac2[index];}
  inline virtual Float_t Getfhac2(Int_t index)                     { return fhac2[index];}
  inline virtual Int_t   Getnfmec()                                { return nfemc;}
  inline virtual Int_t   Getnfhac1()                               { return nfhac1;}
  inline virtual Int_t   Getnfhac2()                               { return nfhac2;}
  inline virtual Int_t   Getnbmec()                                { return nbemc;}
  inline virtual Int_t   Getnbhac1()                               { return nbhac1;}
  inline virtual Int_t   Getnbhac2()                               { return nbhac2;}
  inline virtual Int_t   Getnrmec()                                { return nremc;}
  inline virtual Int_t   Getnrhac()                                { return nrhac;}
  inline virtual Float_t Getcal_tf()                               { return cal_tf;}
  inline virtual Float_t Getcal_tb()                               { return cal_tb;}
  inline virtual Float_t Getcal_tr()                               { return cal_tr;}
  inline virtual Float_t Getcal_tg()                               { return cal_tg;}
  /*
  inline virtual Float_t Getcal_tf_e()                             { return cal_tf_e;}
  inline virtual Float_t Getcal_tb_e()                             { return cal_tb_e;}
  inline virtual Float_t Getcal_tr_e()                             { return cal_tr_e;}
  inline virtual Float_t Getcal_tg_e()                             { return cal_tg_e;}
  inline virtual Float_t Getcal_tf_n()                             { return cal_tf_n;}
  inline virtual Float_t Getcal_tb_n()                             { return cal_tb_n;}
  inline virtual Float_t Getcal_tr_n()                             { return cal_tr_n;}
  inline virtual Float_t Getcal_tg_n()                             { return cal_tg_n;}
  */
  inline virtual Float_t Getetamax_ce()                            { return etamax_ce;}
  inline virtual Float_t Getetamax_ce4()                           { return etamax_ce4;}
  inline virtual Float_t Getcal_et10()                             { return cal_et10;}
  inline virtual Float_t Getmtrknoe_pi()                           { return mtrknoe_pi;}
  inline virtual Float_t Getmtrknoe_k()                            { return mtrknoe_k;}
  inline virtual Float_t Gete_hk()                                 { return e_hk;}
  inline virtual Float_t Getunmen_pi()                             { return unmen_pi;}
  inline virtual Float_t Getunmen_k()                              { return unmen_k;}
  inline virtual Int_t   Getsparkf()                               { return sparkf;}

  // FCALIR
  inline virtual Float_t Getpex1ir(Int_t index)                    { return pex1ir[index];}
  inline virtual Float_t Getet1ir()                                { return et1ir;}
  inline virtual Float_t Getetex1ir()                              { return etex1ir;}
  inline virtual Float_t Getpex2ir(Int_t index)                    { return pex2ir[index];}
  inline virtual Float_t Getet2ir()                                { return et2ir;}
  inline virtual Float_t Getetex2ir()                              { return etex2ir;}

  // RCALIR
  inline virtual Float_t Getpercir(Int_t index)                    { return percir[index];}
  inline virtual Float_t Getetrcir()                               { return etrcir;}

  // EVENT
  inline virtual Int_t   Getrunnr()                                { return runnr;}
  inline virtual Int_t   Geteventnr()                              { return eventnr;}

  // TAKEINFO

  inline virtual Int_t   Getmvdtake()                              { return mvdtake; }

  // GMUON
  inline virtual Int_t   Getnmu()                                  { return nmu;}
  inline virtual Int_t   Getmuqual(Int_t index)                    { return muqual[index];}
  inline virtual Int_t   Getmucharge(Int_t index)                  { return mucharge[index];}
  inline virtual Float_t Getmupt(Int_t index)                      { return mupt[index];}
  inline virtual Float_t Getmuth(Int_t index)                      { return muth[index];}
  inline virtual Float_t Getmuph(Int_t index)                      { return muph[index];}
  inline virtual Float_t Getmup(Int_t index, Int_t coord)          { return mup[index][coord];}
  inline virtual Float_t Getmuperr(Int_t index)                    { return muperr[index];}
  inline virtual Int_t   Getmutrfl(Int_t index)                    { return mutrfl[index];}
  inline virtual Int_t   Getmutrid(Int_t index)                    { return mutrid[index];}
  inline virtual Int_t   Getmuvcid(Int_t index)                    { return muvcid[index];}
  inline virtual Int_t   Getmuztid(Int_t index)                    { return muztid[index];} //[nmu]   //real new 041118
  inline virtual Int_t   Getmustid(Int_t index)                    { return mustid[index];} //[nmu]   //real new 041118
  inline virtual Int_t   Getmuvtxfl(Int_t index)                   { return muvtxfl[index];}
  inline virtual Int_t   Getmuvtxid(Int_t index)                   { return muvtxid[index];}
  inline virtual Int_t   Getmuglomu(Int_t index)                   { return muglomu[index];}
  inline virtual Int_t   Getmubremat(Int_t index)                  { return mubremat[index];}
  inline virtual Int_t   Getmubacmat(Int_t index)                  { return mubacmat[index];}
  inline virtual Int_t   Getmumubac(Int_t index)                   { return mumubac[index];}
  inline virtual Int_t   Getmumamma(Int_t index)                   { return mumamma[index];}
  inline virtual Int_t   Getmumpmat(Int_t index)                   { return mumpmat[index];}
  inline virtual Int_t   Getmundof(Int_t index)                    { return mundof[index];} 
  inline virtual Int_t   Getmunphi(Int_t index)                    { return munphi[index];}
  inline virtual Float_t Getmuz(Int_t index)                       { return muz[index];}
  inline virtual Int_t   Getmumufo(Int_t index)                    { return mumufo[index];}
  inline virtual Int_t   Getmumip(Int_t index)                     { return mumip[index];}
  inline virtual Int_t   Getmumv(Int_t index)                      { return mumv[index];}
  inline virtual Int_t   Getmucalfl(Int_t index)                   { return mucalfl[index];}
  inline virtual Float_t Getmucalene(Int_t index)                  { return mucalene[index];} //[nmu]     //real new 041118
  inline virtual Float_t Getmuhac2(Int_t index)                    { return muhac2[index];}   //[nmu]     //real new 041118

  inline virtual Int_t   Getmuzufid(Int_t index)                   { return muzufid[index];}
  inline virtual Float_t Getmuisol(Int_t index, Int_t coord)       { return muisol[index][coord];}   //[nmu]  //real new 041118
  inline virtual Int_t   Getmunis(Int_t index, Int_t coord)        { return munis[index][coord];}    //[nmu]  //real new 041118
  inline virtual Float_t Getmuisdrmip(Int_t index, Int_t coord)    { return muisdrmip[index][coord];} //[nmu]  //real new 041118
  inline virtual Float_t Getmuisetmip(Int_t index, Int_t coord)    { return muisetmip[index][coord];} //[nmu]  //real new 041118
  inline virtual Int_t   Getmuistumip(Int_t index, Int_t coord)    { return muistumip[index][coord];} //[nmu]  //real new 041118
  inline virtual Float_t Getmupmip(Int_t index)                    { return mupmip[index];}
  inline virtual Float_t Getmuhene(Int_t index)                    { return muhene[index];}
  inline virtual Float_t Getmutime(Int_t index)                    { return mutime[index];}    //[nmu]  //real new 041118
  inline virtual Int_t   Getmuchfl(Int_t index)                    { return muchfl[index];}
  inline virtual Int_t   Getmuchid(Int_t index)                    { return muchid[index];}
  inline virtual Float_t Getmupmat(Int_t index)                    { return mupmat[index];}
  inline virtual Float_t Getmubacfl(Int_t index)                   { if ( new_mubacdca ) return mubacdca[index];
                                                                     else return (Float_t)(mubacfl[index]);}
  inline virtual Int_t   Getmubacid(Int_t index)                   { return mubacid[index];}
  inline virtual Int_t   Getmudxy(Int_t index)                     { return mudxy[index];}       //[nmu]     //real new 041118
  inline virtual Int_t   Getmudz(Int_t index)                      { return mudz[index];}        //[nmu]     //real new 041118
  inline virtual Float_t Getmuprec(Int_t index)                    { return muprec[index];}

  // GMU_JET
  Int_t   Getmujetfl(Int_t index); 
  Int_t   Getmujetid(Int_t index); 
  Float_t Getmujetdr(Int_t index); 
  Float_t Getmujetpt(Int_t index); 
  Float_t Getmujetdr2(Int_t index); //[nmu]     //real new 041118
  Float_t Getmujetpt2(Int_t index); //[nmu]     //real new 041118
  inline virtual Int_t   Getmuhjet_id(Int_t index)                 { return muhjet_id[index];  }
  // GMU_JET old
  inline virtual Int_t   Getmujetfl_old(Int_t index)               { return mujetfl[index];    }
  inline virtual Int_t   Getmujetid_old(Int_t index)               { return mujetid[index];    }
  inline virtual Float_t Getmujetdr_old(Int_t index)               { return mujetdr[index];    }
  inline virtual Float_t Getmujetpt_old(Int_t index)               { return mujetpt[index];    }
  inline virtual Float_t Getmujetdr2_old(Int_t index)              { return mujetdr2[index];   }
  inline virtual Float_t Getmujetpt2_old(Int_t index)              { return mujetpt2[index];   }
  // GMU_JET_A
  inline virtual Int_t   Getmujetfl_a(Int_t index)                 { return mujetfl_a[index];  }
  inline virtual Int_t   Getmujetid_a(Int_t index)                 { return mujetid_a[index];  }
  inline virtual Float_t Getmujetdr_a(Int_t index)                 { return mujetdr_a[index];  }
  inline virtual Float_t Getmujetpt_a(Int_t index)                 { return mujetpt_a[index];  }
  inline virtual Float_t Getmujetdr2_a(Int_t index)                { return mujetdr2_a[index]; }
  inline virtual Float_t Getmujetpt2_a(Int_t index)                { return mujetpt2_a[index]; }
  // GMU_JET_B
  inline virtual Int_t   Getmujetfl_b(Int_t index)                 { return mujetfl_b[index];  }
  inline virtual Int_t   Getmujetid_b(Int_t index)                 { return mujetid_b[index];  }
  inline virtual Float_t Getmujetdr_b(Int_t index)                 { return mujetdr_b[index];  }
  inline virtual Float_t Getmujetpt_b(Int_t index)                 { return mujetpt_b[index];  }
  inline virtual Float_t Getmujetdr2_b(Int_t index)                { return mujetdr2_b[index]; }
  inline virtual Float_t Getmujetpt2_b(Int_t index)                { return mujetpt2_b[index]; }
  // GMU_JET_c
  inline virtual Int_t   Getmujetfl_c(Int_t index)                 { return mujetfl_c[index];  }
  inline virtual Int_t   Getmujetid_c(Int_t index)                 { return mujetid_c[index];  }
  inline virtual Float_t Getmujetdr_c(Int_t index)                 { return mujetdr_c[index];  }
  inline virtual Float_t Getmujetpt_c(Int_t index)                 { return mujetpt_c[index];  }
  inline virtual Float_t Getmujetdr2_c(Int_t index)                { return mujetdr2_c[index]; }
  inline virtual Float_t Getmujetpt2_c(Int_t index)                { return mujetpt2_c[index]; }
  // GMU_JET_d
  inline virtual Int_t   Getmujetfl_d(Int_t index)                 { return mujetfl_d[index];  }
  inline virtual Int_t   Getmujetid_d(Int_t index)                 { return mujetid_d[index];  }
  inline virtual Float_t Getmujetdr_d(Int_t index)                 { return mujetdr_d[index];  }
  inline virtual Float_t Getmujetpt_d(Int_t index)                 { return mujetpt_d[index];  }
  inline virtual Float_t Getmujetdr2_d(Int_t index)                { return mujetdr2_d[index]; }
  inline virtual Float_t Getmujetpt2_d(Int_t index)                { return mujetpt2_d[index]; }

  // GMU_MC
  inline virtual Int_t   Getmuick(Int_t index)                     { return muick[index];         }
  inline virtual Int_t   Getmupartyp(Int_t index)                  { return mupartyp[index];      }
  inline virtual Float_t Getmumc_p(Int_t index, Int_t coord)       { return mumc_p[index][coord]; }
  inline virtual Int_t   Getmudirtyp(Int_t index)                  { return mudirtyp[index];      }
  inline virtual Float_t Getmumc_d(Int_t index, Int_t coord)       { return mumc_d[index][coord]; }
  inline virtual Int_t   Getmuqtyp(Int_t index)                    { return muqtyp[index];        }
  inline virtual Float_t Getmumc_q(Int_t index, Int_t coord)       { return mumc_q[index][coord]; }
  inline virtual Int_t   Getmutruefl(Int_t index)                  { return mutruefl[index];      }
  inline virtual Float_t Getmudecdist(Int_t index)                 { return mudecdist[index];     }
  // FMCKIN
  inline virtual Int_t   Getnpart()                                { return npart;}
  inline virtual Int_t   Getpart_id(Int_t index)                   { return part_id[index];}
  inline virtual Int_t   Getpart_prt(Int_t index)                  { return part_prt[index];}
  inline virtual Float_t Getpart_p(Int_t index, Int_t coord)       { return part_p[index][coord];}
  
  // ktJETS
  
  Bool_t  SetDISPHPJets(Int_t index);
  inline virtual Int_t GetDISPHPJets() {return fDISPHPJets;}
  
  Int_t   Getkt_njet();
  Float_t Getkt_etjet(Int_t index);
  Float_t Getkt_etajet(Int_t index); 
  Float_t Getkt_phijet(Int_t index);
  Float_t Getkt_masjet(Int_t index);
  Float_t Getkt_etjetbreit(Int_t index);
  // ktJETS_a
  inline virtual Int_t   Getkt_njet_a()                            { return kt_njet_a;          }
  inline virtual Float_t Getkt_etjet_a(Int_t index)                { return kt_etjet_a[index];  } 
  inline virtual Float_t Getkt_etajet_a(Int_t index)               { return kt_etajet_a[index]; }
  inline virtual Float_t Getkt_phijet_a(Int_t index)               { return kt_phijet_a[index]; }
  inline virtual Float_t Getkt_masjet_a(Int_t index)               { return kt_masjet_a[index]; }
  // ktJETS_b
  inline virtual Int_t   Getkt_njet_b()                            { return kt_njet_b;          }
  inline virtual Float_t Getkt_etjet_b(Int_t index)                { return kt_etjet_b[index];  } 
  inline virtual Float_t Getkt_etajet_b(Int_t index)               { return kt_etajet_b[index]; }
  inline virtual Float_t Getkt_phijet_b(Int_t index)               { return kt_phijet_b[index]; }
  inline virtual Float_t Getkt_masjet_b(Int_t index)               { return kt_masjet_b[index]; }
  // ktJETS_c
  inline virtual Int_t   Getkt_njet_c()                            { return kt_njet_c;          }
  inline virtual Float_t Getkt_etjet_c(Int_t index)                { return kt_etjet_c[index];  } 
  inline virtual Float_t Getkt_etajet_c(Int_t index)               { return kt_etajet_c[index]; }
  inline virtual Float_t Getkt_phijet_c(Int_t index)               { return kt_phijet_c[index]; }
  inline virtual Float_t Getkt_masjet_c(Int_t index)               { return kt_masjet_c[index]; }
  // ktJETS_d
  inline virtual Int_t   Getkt_njet_d()                            { return kt_njet_d;          }
  inline virtual Float_t Getkt_etjet_d(Int_t index)                { return kt_etjet_d[index];  }  
  inline virtual Float_t Getkt_etajet_d(Int_t index)               { return kt_etajet_d[index]; }
  inline virtual Float_t Getkt_phijet_d(Int_t index)               { return kt_phijet_d[index]; }
  inline virtual Float_t Getkt_masjet_d(Int_t index)               { return kt_masjet_d[index]; }

  // MCSUMS
  inline virtual Float_t Getmc_ez()                                { return mc_ez;              }
  inline virtual Float_t Getmc_esum()                              { return mc_esum;            }
  inline virtual Float_t Getmc_etcone()                            { return mc_etcone;          }
  inline virtual Float_t Getmc_ercal()                             { return mc_ercal;           }

  // MCJETS
  inline virtual Int_t   Getmc_njet()                              { return mc_njet;            }
  inline virtual Float_t Getmc_etj(Int_t index)                    { return mc_etj[index];      }   
  inline virtual Float_t Getmc_rapj(Int_t index)                   { return mc_rapj[index];     }   
  inline virtual Float_t Getmc_phij(Int_t index)                   { return mc_phij[index];     }   
  inline virtual Float_t Getmc_pxj(Int_t index)                    { return mc_pxj[index];      }   
  inline virtual Float_t Getmc_pyj(Int_t index)                    { return mc_pyj[index];      }   
  inline virtual Float_t Getmc_pzj(Int_t index)                    { return mc_pzj[index];      }   
  inline virtual Float_t Getmc_ej(Int_t index)                     { return mc_ej[index];       }   

  // MCKINE
  inline virtual Float_t Getmc_el()                                { return mc_el;}
  inline virtual Float_t Getmc_ep()                                { return mc_ep;}
  inline virtual Float_t Getmc_x()                                 { return mc_x;}
  inline virtual Float_t Getmc_y()                                 { return mc_y;}
  inline virtual Float_t Getmc_q2()                                { return mc_q2;}
  inline virtual Float_t Getmc_mu()                                { return mc_mu;}
  inline virtual Float_t Getmc_pt()                                { return mc_pt;}
  inline virtual Float_t Getmc_xpro()                              { return mc_xpro;}
  inline virtual Float_t Getmc_xgam()                              { return mc_xgam;}
  inline virtual Float_t Getmc_xpom()                              { return mc_xpom;}
  inline virtual Float_t Getmc_beta()                              { return mc_beta;}
  inline virtual Float_t Getmc_t()                                 { return mc_t;}
  inline virtual Int_t   Getmc_idl()                               { return mc_idl;}
  inline virtual Int_t   Getmc_pidl()                              { return mc_pidl;}
  inline virtual Int_t   Getmc_pidp()                              { return mc_pidp;}
  inline virtual Int_t   Getmc_idfsl()                             { return mc_idfsl;}
  inline virtual Float_t Getmc_pfsl(Int_t index)                   { return mc_pfsl[index];}
  inline virtual Float_t Getmc_pfsph(Int_t index)                  { return mc_pfsph[index];}
  inline virtual Float_t Getmc_vtx(Int_t index)                    { return mc_vtx[index];}
  inline virtual Int_t   Getmc_ichnn()                             { return mc_ichnn;}

  // MCVTX
  inline virtual Float_t Getmcvtx(Int_t index)                     { return mcvtx[index];}

  // MUON
  inline virtual Int_t   Getnomu()                                 { return nomu;}
  inline virtual Int_t   Getbmuon1()                               { return bmuon1;}
  inline virtual Int_t   Getbmuon2()                               { return bmuon2;}
  inline virtual Float_t Getbmnrmips()                             { return bmnrmips;}
  inline virtual Float_t Getbmmmtrk()                              { return bmmmtrk;}
  inline virtual Int_t   Getmuonf1()                               { return muonf1;}
  inline virtual Int_t   Getmuonf2()                               { return muonf2;}
  inline virtual Float_t Getmupt1()                                { return mupt1;}
  inline virtual Float_t Getmuth1()                                { return muth1;}
  inline virtual Float_t Getmuph1()                                { return muph1;}
  inline virtual Float_t Getmupt2()                                { return mupt2;}
  inline virtual Float_t Getmuth2()                                { return muth2;}
  inline virtual Float_t Getmuph2()                                { return muph2;}
  inline virtual Int_t   Getfmntrk()                               { return fmntrk;}
  inline virtual Int_t   Getfmntrp()                               { return fmntrp;}
  inline virtual Int_t   Getfmangr()                               { return fmangr;}
  inline virtual Float_t Getfmrecp()                               { return fmrecp;}
  inline virtual Float_t Getfmmatch()                              { return fmmatch;}
  inline virtual Float_t Getmbchi2(Int_t index)                    { return mbchi2[index];}
  inline virtual Float_t Getmbp(Int_t coord, Int_t index)          { return mbp[coord][index];}
  inline virtual Float_t Getmbdca(Int_t index)                     { return mbdca[index];}
  inline virtual Int_t   Getmbtrfl(Int_t index)                    { return mbtrfl[index];}

  // FMU_MPM
  inline virtual Int_t   Getnfmu()                                 { return nfmu;}
  inline virtual Float_t Getfmux(Int_t index)                      { return fmux[index];}
  inline virtual Float_t Getfmuy(Int_t index)                      { return fmuy[index];}
  inline virtual Float_t Getfmuz(Int_t index)                      { return fmuz[index];}
  inline virtual Float_t Getfmuchi(Int_t index)                    { return fmuchi[index];}
  inline virtual Float_t Getfmuprob(Int_t index)                   { return fmuprob[index];}
  inline virtual Int_t   Getfmuti(Int_t index)                     { return fmuti[index];}
  inline virtual Int_t   Getfmufi(Int_t index)                     { return fmufi[index];}
  inline virtual Float_t Getfmutqor(Int_t index)                   { return fmutqor[index];}
  inline virtual Float_t Getfmutz(Int_t index)                     { return fmutz[index];}
  inline virtual Float_t Getfmutqd(Int_t index)                    { return fmutqd[index];}
  inline virtual Float_t Getfmutchi(Int_t index)                   { return fmutchi[index];}
  inline virtual Int_t   Getfmutndf(Int_t index)                   { return fmutndf[index];}
  inline virtual Int_t   Getfmutksw(Int_t index)                   { return fmutksw[index];} 

  // FMUmfrtz
  inline virtual Int_t   Getnmf()                                  { return nmf;}
  inline virtual Float_t Getmfx(Int_t index)                       { return mfx[index];}
  inline virtual Float_t Getmfy(Int_t index)                       { return mfy[index];}
  inline virtual Float_t Getmfz(Int_t index)                       { return mfz[index];}
  inline virtual Float_t Getmfvx(Int_t index)                      { return mfvx[index];}
  inline virtual Float_t Getmfvy(Int_t index)                      { return mfvy[index];}
  inline virtual Float_t Getmfqop(Int_t index)                     { return mfqop[index];}
  inline virtual Int_t   Getmfo(Int_t index)                       { return mfo[index];}
  inline virtual Int_t   Getmfndf(Int_t index)                     { return mfndf[index];}
  inline virtual Float_t Getmfpro(Int_t index)                     { return mfpro[index];}
  inline virtual Int_t   Getmfndff(Int_t index)                    { return mfndff[index];}
  inline virtual Float_t Getmfprof(Int_t index)                    { return mfprof[index];}
  inline virtual Int_t   Getmfhdc(Int_t index)                     { return mfhdc[index];}
  inline virtual Int_t   Getmfhlt(Int_t index)                     { return mfhlt[index];}
  inline virtual Int_t   Getfmusid(Int_t index)                    { return fmusid[index];}
  inline virtual Int_t   Getfmushr(Int_t index)                    { return fmushr[index];}
  inline virtual Float_t Getfmusrchi(Int_t index)                  { return fmusrchi[index];}
  inline virtual Int_t   Getfmusnr(Int_t index)                    { return fmusnr[index];}
  inline virtual Int_t   Getfmushp(Int_t index)                    { return fmushp[index];}
  inline virtual Int_t   Getfmusnp(Int_t index)                    { return fmusnp[index];}
  inline virtual Float_t Getfmusp(Int_t index)                     { return fmusp[index];}
  inline virtual Float_t Getfmusthe(Int_t index)                   { return fmusthe[index];}
  inline virtual Float_t Getfmusphi(Int_t index)                   { return fmusphi[index];}

  // MV
  inline virtual Int_t   Getumv_ncmuo()                            { return umv_ncmuo;}
  inline virtual Int_t   Getumv_trkmuo(Int_t index)                { return umv_trkmuo[index];}   
  inline virtual Int_t   Getumv_trrmuo(Int_t index)                { return umv_trrmuo[index];}   
  inline virtual Int_t   Getumv_trnmuo(Int_t index)                { return umv_trnmuo[index];}   
  inline virtual Int_t   Getumv_trqmuo(Int_t index)                { return umv_trqmuo[index];}   
  inline virtual Int_t   Getumv_tobr(Int_t index)                  { return umv_tobr[index];}   
  inline virtual Float_t Getumv_trmmuo(Int_t index)                { return umv_trmmuo[index];}   
  inline virtual Float_t Getumv_trtmuo(Int_t index)                { return umv_trtmuo[index];}   
  inline virtual Float_t Getumv_trpmuo(Int_t index)                { return umv_trpmuo[index];}   
  inline virtual Float_t Getumv_trcmuo(Int_t index)                { return umv_trcmuo[index];}   
  inline virtual Float_t Getumv_tremuo(Int_t index)                { return umv_tremuo[index];}   
  inline virtual Float_t Getumv_trdmuo(Int_t index)                { return umv_trdmuo[index];}   
  inline virtual Float_t Getumv_timuo(Int_t index)                 { return umv_timuo[index];}   
  inline virtual Float_t Getumv_xcmuo(Int_t index)                 { return umv_xcmuo[index];}   
  inline virtual Float_t Getumv_ycmuo(Int_t index)                 { return umv_ycmuo[index];}   
  inline virtual Float_t Getumv_zcmuo(Int_t index)                 { return umv_zcmuo[index];}   
  inline virtual Float_t Getumv_heemuo(Int_t index)                { return umv_heemuo[index];}   
  inline virtual Float_t Getumv_hexmuo(Int_t index)                { return umv_hexmuo[index];}   
  inline virtual Float_t Getumv_heymuo(Int_t index)                { return umv_heymuo[index];}   
  inline virtual Float_t Getumv_hezmuo(Int_t index)                { return umv_hezmuo[index];}   
  inline virtual Float_t Getumv_prmuo(Int_t index)                 { return umv_prmuo[index];}   
  inline virtual Float_t Getumv_efmuo(Int_t index)                 { return umv_efmuo[index];}   
  inline virtual Float_t Getumv_comuo(Int_t index)                 { return umv_comuo[index];}   
  inline virtual Float_t Getumv_pumuo(Int_t index)                 { return umv_pumuo[index];}   
  inline virtual Float_t Getumv_prcmuo(Int_t index)                { return umv_prcmuo[index];}   
  inline virtual Float_t Getumv_efcmuo(Int_t index)                { return umv_efcmuo[index];}   
  inline virtual Float_t Getumv_cocmuo(Int_t index)                { return umv_cocmuo[index];}   
  inline virtual Float_t Getumv_pucmuo(Int_t index)                { return umv_pucmuo[index];}   
  inline virtual Float_t Getumv_ecamuo(Int_t index)                { return umv_ecamuo[index];}   
  inline virtual Float_t Getuex_calmuo(Int_t index)                { return uex_calmuo[index];}   
  inline virtual Float_t Getuey_calmuo(Int_t index)                { return uey_calmuo[index];}   
  inline virtual Float_t Getuez_calmuo(Int_t index)                { return uez_calmuo[index];}   
  inline virtual Float_t Getuet_calmuo(Int_t index)                { return uet_calmuo[index];}   

  // SIRA
  inline virtual Int_t   Getsincand()                              { return sincand;}
  inline virtual Int_t   Getsierror()                              { return sierror;}
  inline virtual Float_t Getsiprob(Int_t index)                    { return siprob[index];}   
  inline virtual Float_t Getsipos(Int_t index, Int_t coord)        { return sipos[index][coord];}   
  inline virtual Float_t Getsicalpos(Int_t index, Int_t coord)     { return sicalpos[index][coord];}   
  inline virtual Float_t Getsicalene(Int_t index)                  { return sicalene[index];}   
  inline virtual Float_t Getsiein(Int_t index)                     { return siein[index];}   
  inline virtual Float_t Getsienin(Int_t index)                    { return sienin[index];}   
  inline virtual Float_t Getsiecorr(Int_t index, Int_t coord)      { return siecorr[index][coord];}   
  inline virtual Float_t Getsith(Int_t index)                      { return sith[index];}   
  inline virtual Float_t Getsiph(Int_t index)                      { return siph[index];}   
  inline virtual Float_t Getsipt(Int_t index)                      { return sipt[index];}   
  inline virtual UInt_t  Getsixdet(Int_t index, Int_t coord)       { return sixdet[index][coord];}   
  inline virtual UInt_t  Getsiydet(Int_t index, Int_t coord)       { return siydet[index][coord];}   

  // SI_TRK
  inline virtual UInt_t   Getsitrknr(Int_t index)                   { return sitrknr[index];}   
  inline virtual UInt_t   Getsinrsl(Int_t index)                    { return sinrsl[index];}   
  inline virtual Float_t Getsidca(Int_t index)                     { return sidca[index];}   
  inline virtual Float_t Getsitrkp(Int_t index)                    { return sitrkp[index];}   
  inline virtual Float_t Getsitrkth(Int_t index)                   { return sitrkth[index];}   
  inline virtual Float_t Getsitrkph(Int_t index)                   { return sitrkph[index];}   
  inline virtual Float_t Getsitrkq(Int_t index)                    { return sitrkq[index];}   
  inline virtual Float_t Getsitrkdme(Int_t index)                  { return sitrkdme[index];}   
  inline virtual Float_t Getsitrkpos(Int_t index, Int_t coord)     { return sitrkpos[index][coord];}   

  // SI_DET
  inline virtual Float_t Getsisrtf(Int_t index)                    { return (Float_t)(sisrtf[index]);}   
  inline virtual UInt_t  Getsisrtquad(Int_t index)                 { return sisrtquad[index];}   
  inline virtual Int_t   Getsihesf(Int_t index)                    { return sihesf[index];}   
  inline virtual UInt_t  Getsicorrcode(Int_t index)                { return sicorrcode[index];}   
  inline virtual Float_t Getsisrtpos(Int_t index, Int_t coord)     { return sisrtpos[index][coord];}   
  inline virtual Float_t Getsisrtene(Int_t index)                  { return sisrtene[index];}   
  inline virtual Float_t Getsihespos(Int_t index, Int_t coord)     { return sihespos[index][coord];}   
  inline virtual Float_t Getsihesene(Int_t index)                  { return sihesene[index];}   
  inline virtual Float_t Getsihesr(Int_t index)                    { return sihesr[index];}   
  inline virtual Float_t Getsiprsene(Int_t index, Int_t coord)     { return siprsene[index][coord];}   

  // SI_HAD
  inline virtual Float_t Getsiccet(Int_t index)                    { return siccet[index];}
  inline virtual Float_t Getsiccempz(Int_t index)                  { return siccempz[index];}
  inline virtual Float_t Getsietamax(Int_t index)                  { return sietamax[index];}
  inline virtual Float_t Getsicehmom(Int_t index, Int_t coord)     { return sicehmom[index][coord];}
  inline virtual Float_t Getsizuhmom(Int_t index, Int_t coord)     { return sizuhmom[index][coord];}
  inline virtual Float_t Getsicchmom(Int_t index, Int_t coord)     { return sicchmom[index][coord];}

  // SI_KIN
  inline virtual Float_t Getsiyel(Int_t index)                     { return siyel[index];}
  inline virtual Float_t Getsixel(Int_t index)                     { return sixel[index]; }
  inline virtual Float_t Getsiq2el(Int_t index)                    { return siq2el[index]; }
  inline virtual Float_t Getsiyda(Int_t index)                     { return siyda[index]; }
  inline virtual Float_t Getsiyda_cell(Int_t index)                { return siyda_cell[index];}
  inline virtual Float_t Getsixda(Int_t index)                     { return sixda[index]; }
  inline virtual Float_t Getsixda_cell(Int_t index)                { return sixda_cell[index];}
  inline virtual Float_t Getsiq2da(Int_t index)                    { return siq2da[index]; }
  inline virtual Float_t Getsiq2da_cell(Int_t index)               { return siq2da_cell[index];}
  inline virtual Float_t Getsiq2jb(Int_t index)                    { return siq2jb[index]; }
  inline virtual Float_t Getsiq2jb_cell(Int_t index)               { return siq2jb_cell[index];}
  inline virtual Float_t Getsixjb(Int_t index)                     { return sixjb[index]; }
  inline virtual Float_t Getsixjb_cell(Int_t index)                { return sixjb_cell[index];}
  inline virtual Float_t Getsiyjb(Int_t index)                     { return siyjb[index]; }
  inline virtual Float_t Getsiyjb_cell(Int_t index)                { return siyjb_cell[index];}

  // SI_CELLS
  inline virtual Int_t   Getsincell(Int_t index)                   { return sincell[index];}
  inline virtual Int_t   Getsicellptr(Int_t index)                 { return sicellptr[index];}

  // TRIGGER
  inline virtual UInt_t   Getfltw(Int_t index)                      { return fltw[index];}
  inline virtual UInt_t   Getfltpsw(Int_t index)                    { return fltpsw[index];}
  inline virtual UInt_t   Getfltfl()                                { return fltfl;}
  inline virtual UInt_t   Getgslt_global()                          { return gslt_global;}
  inline virtual UInt_t   Getsltw(Int_t index)                      { return sltw[index];}
  inline virtual UInt_t   Getsltupw(Int_t index)                    { return sltupw[index];}   //real new 041118
  inline virtual UInt_t   Gettltw(Int_t index)                      { return tltw[index];}
  inline virtual UInt_t   Getdstw(Int_t index)                      { return dstw[index];}
  inline virtual UInt_t   Getfltfcw(Int_t index)                    { return fltfcw[index];}
  inline virtual UInt_t   Getfltpsfcw(Int_t index)                  { return fltpsfcw[index];}

  // VERTEX
  inline virtual Int_t   Getntrkvtx()                              { return ntrkvtx;}
  inline virtual Float_t Getxvtx()                                 { return xvtx;}
  inline virtual Float_t Getyvtx()                                 { return yvtx;}
  inline virtual Float_t Getzvtx()                                 { return zvtx;}
  inline virtual Float_t Getchivtx()                               { return chivtx;}
  inline virtual Int_t   Getnsecvtx()                              { return nsecvtx;}
  inline virtual Float_t Getxsecvtx(Int_t index)                   { return xsecvtx[index];}
  inline virtual Float_t Getysecvtx(Int_t index)                   { return ysecvtx[7];}
  inline virtual Float_t Getzsecvtx(Int_t index)                   { return zsecvtx[7];}
  inline virtual Float_t Getchisecvtx(Int_t index)                 { return chisecvtx[7];}
  inline virtual Float_t Getfetatr()                               { return fetatr;}
  inline virtual Float_t Getbetatr()                               { return betatr;}
  inline virtual Float_t Getpt_tr()                                { return pt_tr;}
  inline virtual Float_t Getempz_tr_pi()                           { return empz_tr_pi;}
  inline virtual Float_t Getet_tr()                                { return et_tr;}
  inline virtual Float_t Gete_tr_pi()                              { return e_tr_pi;}
  inline virtual Float_t Getphi_tr()                               { return phi_tr;}
  inline virtual Float_t Getzvtx_fcal()                            { return zvtx_fcal;}
  inline virtual UInt_t  Getfcal_nrgoodcells()                     { return fcal_nrgoodcells;}
  inline virtual Float_t Getfcal_vzerr()                           { return fcal_vzerr;}

  // BSPOT

  inline virtual Float_t Getbspt_x()                               { return bspt_x; }
  inline virtual Float_t Getbspt_y()                               { return bspt_y; }
  inline virtual Float_t Getbspt_z()                               { return bspt_z; }

  // ZUFOS
  inline virtual Float_t Getv_h_px_zu()                            { return v_h_px_zu;}
  inline virtual Float_t Getv_h_py_zu()                            { return v_h_py_zu;}
  inline virtual Float_t Getv_h_pz_zu()                            { return v_h_pz_zu;}
  inline virtual Float_t Getv_h_e_zu()                             { return v_h_e_zu;}
  inline virtual Float_t Getetamax_zu()                            { return etamax_zu;}
  inline virtual Float_t Getetamax_zu4()                           { return etamax_zu4;}
  inline virtual Float_t Getfgap()                                 { return fgap;}
  inline virtual Float_t Getbgap()                                 { return bgap;}
  inline virtual Int_t   Getnzufos()                               { return nzufos;}
  inline virtual UInt_t  Gettufo(Int_t index, Int_t coord)         { return tufo[index][coord];}   
  inline virtual UInt_t  Getzufo_bsp(Int_t index)                  { return zufo_bsp[index];}      //[nzufos]     //real new 041118
  inline virtual Float_t Getzufo(Int_t index, Int_t coord)         { return zufo[index][coord];}
  inline virtual Float_t Getzufoeemc(Int_t index)                  { return zufoeemc[index];}   

  // Tracking
  inline virtual Int_t   Gettrk_ntracks()                          { return trk_ntracks;}
  inline virtual UInt_t  Gettrk_type(Int_t index)                  { return trk_type[index];}
  inline virtual UInt_t  Getntrack_type(Int_t index)               { return ntrack_type[index];}
  inline virtual UInt_t  Getdef_trk_type()                         { return def_trk_type;}
  inline virtual UInt_t  Gettrk_id(Int_t index)                    { return trk_id[index];}   
  inline virtual UInt_t  Gettrk_id2(Int_t index)                   { return trk_id2[index];}   
  inline virtual Float_t Gettrk_px(Int_t index)                    { return trk_px[index];}   
  inline virtual Float_t Gettrk_py(Int_t index)                    { return trk_py[index];}   
  inline virtual Float_t Gettrk_pz(Int_t index)                    { return trk_pz[index];}   
  inline virtual Float_t Gettrk_charge(Int_t index)                { return trk_charge[index];}   

  // Trk_vtx
  inline virtual Int_t   Gettrk_vtx(Int_t index)                   { return trk_vtx[index];}   
  Bool_t                 Gettrk_prim_vtx(Int_t index);   
  virtual Bool_t         Gettrk_sec_vtx(Int_t index);   
  inline virtual UInt_t  Gettrk_vxid(Int_t index)                  { return trk_vxid[index];}   

  // Trk_qual
  inline virtual Float_t Gettrk_endpos(Int_t index, Int_t coord)   { return trk_endpos[index][coord];}   
  inline virtual UInt_t  Gettrk_nzbyt(Int_t index)                 { return trk_nzbyt[index];}   
  inline virtual UInt_t  Gettrk_naxial(Int_t index)                { return trk_naxial[index];}   
  inline virtual UInt_t  Gettrk_nstereo(Int_t index)               { return trk_nstereo[index];}   
  inline virtual UInt_t  Gettrk_ndof(Int_t index)                  { return trk_ndof[index];}   
  inline virtual UInt_t  Gettrk_layinner(Int_t index)              { return trk_layinner[index];}   
  inline virtual UInt_t  Gettrk_layouter(Int_t index)              { return trk_layouter[index];}   
  inline virtual Float_t Gettrk_dedxctd(Int_t index)               { return trk_dedxctd[index];}   
  inline virtual Float_t Gettrk_dedxctdcr(Int_t index)             { return trk_dedxctdcr[index];}
  inline virtual Float_t Gettrk_chi2(Int_t index)                  { return trk_chi2[index];}   
  inline virtual Float_t Gettrk_vchi2(Int_t index)                 { return trk_vchi2[index];}   

  // Trk_MVD
  inline virtual UInt_t   Gettrk_nbr(Int_t index)                  { return trk_nbr[index];}
  inline virtual UInt_t   Gettrk_nbz(Int_t index)                  { return trk_nbz[index];}
  inline virtual UInt_t   Gettrk_nwu(Int_t index)                  { return trk_nwu[index];}
  inline virtual UInt_t   Gettrk_nwv(Int_t index)                  { return trk_nwv[index];}
  inline virtual Float_t  Gettrk_dedxmvd(Int_t index)              { return trk_dedxmvd[index];}
  
  Double_t Gettrk_w(Int_t index);
  Double_t Gettrk_t(Int_t index);
  Double_t Gettrk_phizero(Int_t index);
  Double_t Gettrk_dzero(Int_t index);
  Double_t Gettrk_zzero(Int_t index);
  Double_t Gettrk_cov(Int_t index, Int_t index2);

  // Trk_imp
  inline virtual Float_t Gettrk_imppar(Int_t index)                { return trk_imppar[index];}
  inline virtual Float_t Gettrk_imperr(Int_t index)                { return trk_imperr[index];}
  inline virtual Float_t Gettrk_pca(Int_t index, Int_t coord)      { return trk_pca[index][coord];}
			 
  // SECVTX
  inline virtual Float_t          Getvtxredprm_x()                           { return vtxredprm_x;}
  inline virtual Float_t          Getvtxredprm_y()                           { return vtxredprm_y;}
  inline virtual Float_t          Getvtxredprm_z()                           { return vtxredprm_z;}
  inline virtual Float_t          Getvtxredprm_chi2()                        { return vtxredprm_chi2;}
  inline virtual Float_t          Getvtxredprm_cov(Int_t coord)              { return vtxredprm_cov[coord];}
  inline virtual Float_t          Getvtxredprm_ndf()                         { return vtxredprm_ndf;}
  inline virtual Int_t            Getnr_secvtx()                             { return nr_secvtx;}
  inline virtual Float_t          Getvtxsec_x(Int_t index)                   { return vtxsec_x[index];} 
  inline virtual Float_t          Getvtxsec_y(Int_t index)                   { return vtxsec_y[index];}   
  inline virtual Float_t          Getvtxsec_z(Int_t index)                   { return vtxsec_z[index];}     
  inline virtual Float_t          Getvtxsec_mass(Int_t index)                { return vtxsec_mass[index];}     
  inline virtual Float_t          Getvtxsec_chi2(Int_t index)                { return vtxsec_chi2[index];}     
  inline virtual Float_t          Getvtxsec_ndf(Int_t index)                 { return vtxsec_ndf[index];}      
  inline virtual UInt_t           Getvtxsec_multi(Int_t index)               { return vtxsec_multi[index];}     
  inline virtual Float_t          Getvtxsec_cov(Int_t index, Int_t coord)    { return vtxsec_cov[index][coord];}
  inline virtual UInt_t           Getvtxsec_zttid(Int_t index, Int_t coord)  { return vtxsec_zttid[index][coord];}
  inline virtual Float_t          Getvtxsec2d_x(Int_t index)                 { return vtxsec2d_x[index];}
  inline virtual Float_t          Getvtxsec2d_y(Int_t index)                 { return vtxsec2d_y[index];}
  inline virtual Float_t          Getvtxsec2d_z(Int_t index)                 { return vtxsec2d_z[index];} 
  inline virtual Float_t          Getvtxsec2d_mass(Int_t index)              { return vtxsec2d_mass[index];}   
  inline virtual Float_t          Getvtxsec2d_chi2(Int_t index)              { return vtxsec2d_chi2[index];} 
  inline virtual Float_t          Getvtxsec2d_ndf(Int_t index)               { return vtxsec2d_ndf[index];} 
  inline virtual Float_t          Getvtxsec2d_cov(Int_t index, Int_t coord)  { return vtxsec2d_cov[index][coord];}

  // VCTRHLa
  inline virtual UInt_t  Getnvctrhl()                              { return nvctrhl;}
  inline virtual UInt_t  Getvctrhl_id(Int_t index)                 { return vctrhl_id[index];}   
  inline virtual UInt_t  Getvctrhl_trkn(Int_t index)               { return vctrhl_trkn[index];}   
  inline virtual Float_t Getvctrhl_qovr(Int_t index)               { return vctrhl_qovr[index];}   
  inline virtual Float_t Getvctrhl_zh(Int_t index)                 { return vctrhl_zh[index];}   
  inline virtual Float_t Getvctrhl_pgevc(Int_t index)              { return vctrhl_pgevc[index];}   
  inline virtual Int_t   Getvcatcal_kodswm(Int_t index)            { return vcatcal_kodswm[index];}   

  // BREMAT
  inline virtual Int_t   Getbrenmu()                               { return brenmu;}
  inline virtual Int_t   Getbremat_nmatch()                        { return bremat_nmatch;}
  inline virtual Int_t   Getbremat_everror()                       { return bremat_everror;}
  inline virtual Int_t   Getbremat_error(Int_t index)              { return bremat_error[index];}
  inline virtual Int_t   Getbremat_ivc(Int_t index)                { return bremat_ivc[index];}
  inline virtual Int_t   Getbremat_imu(Int_t index)                { return bremat_imu[index];}
  inline virtual Float_t Getbremat_delta(Int_t index)              { return bremat_delta[index];}
  inline virtual Float_t Getbremat_xres(Int_t index)               { return bremat_xres[index];}
  inline virtual Float_t Getbremat_yres(Int_t index)               { return bremat_yres[index];}
  inline virtual Float_t Getbremat_slopxres(Int_t index)           { return bremat_slopxres[index];}
  inline virtual Float_t Getbremat_slopyres(Int_t index)           { return bremat_slopyres[index];}
  inline virtual Float_t Getbremat_invpres(Int_t index)            { return bremat_invpres[index];}
  inline virtual Float_t Getbremat_covres(Int_t index, Int_t coord){ return bremat_covres[index][coord];}
  inline virtual Float_t Getbremat_chi2mat(Int_t index)            { return bremat_chi2mat[index];}
  inline virtual Float_t Getbremat_probmat(Int_t index)            { return bremat_probmat[index];}
  inline virtual Float_t Getbremat_chi2matp(Int_t index)           { return bremat_chi2matp[index];}
  inline virtual Float_t Getbremat_probmatp(Int_t index)           { return bremat_probmatp[index];}
  inline virtual Float_t Getbremat_endpos(Int_t index, Int_t coord){ return bremat_endpos[index][coord];}

  // own fmckin block
  inline virtual Int_t   Getfmck_nkin()                            { return fmck_nkin; }
  /*    inline virtual Float_t Getfmck_q2()                              { return fmck_q2; } */
  Float_t Getfmck_q2();   //return fmck_q2 or mc_q2
  inline virtual Float_t Getfmck_w()                               { return fmck_w; }
  inline virtual Float_t Getfmck_xg()                              { return fmck_xg; }
  inline virtual Int_t   Getfmck_nstor()                           { return fmck_nstor; }
  inline virtual Int_t   Getfmck_id(Int_t index)                   { return fmck_id[index]; }
  inline virtual Float_t Getfmck_px(Int_t index)                   { return fmck_px[index]; }
  inline virtual Float_t Getfmck_py(Int_t index)                   { return fmck_py[index]; }
  inline virtual Float_t Getfmck_pz(Int_t index)                   { return fmck_pz[index]; }
  inline virtual Float_t Getfmck_e(Int_t index)                    { return fmck_e[index]; }
  inline virtual Float_t Getfmck_m(Int_t index)                    { return fmck_m[index]; }
  //  inline virtual Float_t Getfmck_pt(Int_t index)                   { return fmck_pt[index]; }
  //  inline virtual Float_t Getfmck_eta(Int_t index)                  { return fmck_eta[index]; }
  inline virtual Int_t   Getfmck_daug(Int_t index)                 { return fmck_daug[index]; }
  inline virtual Int_t   Getfmck_prt(Int_t index)                  { return fmck_prt[index]; }
  inline virtual Int_t   Getfmck_prat(Int_t index)                 { return fmck_prat[index]; }
  inline virtual Float_t Getfmck_impar(Int_t index)                { return fmck_impar[index]; }
  inline virtual Float_t Getfmck_impar2(Int_t index)               { return fmck_impar2[index]; }
  //  inline virtual Float_t Getfmck_dsignif(Int_t index)              { return fmck_dsignif[index]; }
  //  inline virtual Float_t Getfmck_dsignif2(Int_t index)             { return fmck_dsignif2[index]; }
  inline virtual Int_t   Getfmvtx_nstor()                          { return fmvtx_nstor; }
  inline virtual Int_t   Getfmvtx_id(Int_t index)                  { return fmvtx_id[index]; }
  inline virtual Float_t Getfmvtx_r(Int_t index, Int_t coord)      { return fmvtx_r[index][coord]; }
  inline virtual Float_t Getfmvtx_time(Int_t index)                { return fmvtx_time[index]; }
  inline virtual Int_t   Getfmvtx_prby(Int_t index)                { return fmvtx_prby[index]; }

  inline virtual Float_t Getfmck_hadjet(Int_t index)               { return fmck_hadjet[index]; }
  inline virtual Float_t Getfmck_mhadjet(Int_t index)              { return fmck_mhadjet[index]; }
  inline virtual Float_t Getfmck_bhadjet(Int_t index)              { return fmck_bhadjet[index]; }
  inline virtual Float_t Getfmck_mbhadjet(Int_t index)             { return fmck_mbhadjet[index]; }
  inline virtual Float_t Getfmck_partjet(Int_t index)              { return fmck_partjet[index]; }
  inline virtual Float_t Getfmck_mpartjet(Int_t index)             { return fmck_mpartjet[index]; }
  inline virtual Int_t   Getnhjets()                               { return nhjets; }
  inline virtual Float_t Getpxhjet(Int_t index)                    { return pxhjet[index]; }
  inline virtual Float_t Getpyhjet(Int_t index)                    { return pyhjet[index]; }
  inline virtual Float_t Getpzhjet(Int_t index)                    { return pzhjet[index]; }
  inline virtual Float_t Getehjet(Int_t index)                     { return ehjet[index]; }
  inline virtual Int_t   Getnhmjets()                              { return nhmjets; }
  inline virtual Float_t Getpxhmjet(Int_t index)                   { return pxhmjet[index]; }
  inline virtual Float_t Getpyhmjet(Int_t index)                   { return pyhmjet[index]; }
  inline virtual Float_t Getpzhmjet(Int_t index)                   { return pzhmjet[index]; }
  inline virtual Float_t Getehmjet(Int_t index)                    { return ehmjet[index]; }
  inline virtual Int_t   Getnhbjets()                              { return nhbjets; }
  inline virtual Float_t Getpxhbjet(Int_t index)                   { return pxhbjet[index]; }
  inline virtual Float_t Getpyhbjet(Int_t index)                   { return pyhbjet[index]; }
  inline virtual Float_t Getpzhbjet(Int_t index)                   { return pzhbjet[index]; }
  inline virtual Float_t Getehbjet(Int_t index)                    { return ehbjet[index]; }
  inline virtual Int_t   Getnhbmjets()                             { return nhbmjets; }
  inline virtual Float_t Getpxhbmjet(Int_t index)                  { return pxhbmjet[index]; }
  inline virtual Float_t Getpyhbmjet(Int_t index)                  { return pyhbmjet[index]; }
  inline virtual Float_t Getpzhbmjet(Int_t index)                  { return pzhbmjet[index]; }
  inline virtual Float_t Getehbmjet(Int_t index)                   { return ehbmjet[index]; }
  inline virtual Int_t   Getnpjets()                               { return npjets; };
  inline virtual Float_t Getpxpjet(Int_t index)                    { return pxpjet[index]; }
  inline virtual Float_t Getpypjet(Int_t index)                    { return pypjet[index]; }
  inline virtual Float_t Getpzpjet(Int_t index)                    { return pzpjet[index]; }
  inline virtual Float_t Getepjet(Int_t index)                     { return epjet[index]; }
  inline virtual Int_t   Getnpmjets()                              { return npmjets; }
  inline virtual Float_t Getpxpmjet(Int_t index)                   { return pxpmjet[index]; }
  inline virtual Float_t Getpypmjet(Int_t index)                   { return pypmjet[index]; }
  inline virtual Float_t Getpzpmjet(Int_t index)                   { return pzpmjet[index]; }
  inline virtual Float_t Getepmjet(Int_t index)                    { return epmjet[index]; }

  // OWN VARIABLES
  inline virtual Int_t   Getzes_select()                           { return zes_select;}
  inline virtual Float_t Getlumi(Int_t index)                      { return lumi[index];}

  ClassDef(GConnectTree,0) // Connection to root tree from NTuple using Tree->MakeClass()
    };

    R__EXTERN GConnectTree *gData;

#endif
