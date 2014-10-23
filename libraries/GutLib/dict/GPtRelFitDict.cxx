//
// File generated by rootcint at Thu Oct 23 10:41:37 2014

// Do NOT change. Changes will be lost next time file is generated
//

#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "GPtRelFitDict.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"

// START OF SHADOWS

namespace ROOT {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOT
// END OF SHADOWS

namespace ROOT {
   void GPtRelFit_ShowMembers(void *obj, TMemberInspector &R__insp, char *R__parent);
   static void *new_GPtRelFit(void *p = 0);
   static void *newArray_GPtRelFit(Long_t size, void *p);
   static void delete_GPtRelFit(void *p);
   static void deleteArray_GPtRelFit(void *p);
   static void destruct_GPtRelFit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GPtRelFit*)
   {
      ::GPtRelFit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GPtRelFit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GPtRelFit", ::GPtRelFit::Class_Version(), "/data/zenith234d/stefan/GoodCodeGit/libraries/GutLib/inc//GPtRelFit.h", 20,
                  typeid(::GPtRelFit), DefineBehavior(ptr, ptr),
                  &::GPtRelFit::Dictionary, isa_proxy, 0,
                  sizeof(::GPtRelFit) );
      instance.SetNew(&new_GPtRelFit);
      instance.SetNewArray(&newArray_GPtRelFit);
      instance.SetDelete(&delete_GPtRelFit);
      instance.SetDeleteArray(&deleteArray_GPtRelFit);
      instance.SetDestructor(&destruct_GPtRelFit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GPtRelFit*)
   {
      return GenerateInitInstanceLocal((::GPtRelFit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::GPtRelFit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *GPtRelFit::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *GPtRelFit::Class_Name()
{
   return "GPtRelFit";
}

//______________________________________________________________________________
const char *GPtRelFit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GPtRelFit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GPtRelFit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GPtRelFit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void GPtRelFit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GPtRelFit*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *GPtRelFit::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GPtRelFit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void GPtRelFit::Streamer(TBuffer &R__b)
{
   // Stream an object of class GPtRelFit.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      fName.Streamer(R__b);
      R__b >> fBScale;
      R__b >> fBScaleErr;
      R__b >> fCLFScale;
      R__b >> fCLFScaleErr;
      R__b >> fBFraction;
      R__b >> fBFractionErr;
      R__b >> fChi2;
      R__b >> fBins;
      R__b >> fParameter;
      R__b.CheckByteCount(R__s, R__c, GPtRelFit::IsA());
   } else {
      R__c = R__b.WriteVersion(GPtRelFit::IsA(), kTRUE);
      TObject::Streamer(R__b);
      fName.Streamer(R__b);
      R__b << fBScale;
      R__b << fBScaleErr;
      R__b << fCLFScale;
      R__b << fCLFScaleErr;
      R__b << fBFraction;
      R__b << fBFractionErr;
      R__b << fChi2;
      R__b << fBins;
      R__b << fParameter;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

//______________________________________________________________________________
void GPtRelFit::ShowMembers(TMemberInspector &R__insp, char *R__parent)
{
      // Inspect the data members of an object of class GPtRelFit.
      TClass *R__cl = ::GPtRelFit::IsA();
      Int_t R__ncp = strlen(R__parent);
      if (R__ncp || R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__parent, "fName", &fName);
      fName.ShowMembers(R__insp, strcat(R__parent,"fName.")); R__parent[R__ncp] = 0;
      R__insp.Inspect(R__cl, R__parent, "fBScale", &fBScale);
      R__insp.Inspect(R__cl, R__parent, "fBScaleErr", &fBScaleErr);
      R__insp.Inspect(R__cl, R__parent, "fCLFScale", &fCLFScale);
      R__insp.Inspect(R__cl, R__parent, "fCLFScaleErr", &fCLFScaleErr);
      R__insp.Inspect(R__cl, R__parent, "fBFraction", &fBFraction);
      R__insp.Inspect(R__cl, R__parent, "fBFractionErr", &fBFractionErr);
      R__insp.Inspect(R__cl, R__parent, "fChi2", &fChi2);
      R__insp.Inspect(R__cl, R__parent, "fBins", &fBins);
      R__insp.Inspect(R__cl, R__parent, "fParameter", &fParameter);
      TObject::ShowMembers(R__insp, R__parent);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GPtRelFit(void *p) {
      return  p ? new(p) ::GPtRelFit : new ::GPtRelFit;
   }
   static void *newArray_GPtRelFit(Long_t nElements, void *p) {
      return p ? new(p) ::GPtRelFit[nElements] : new ::GPtRelFit[nElements];
   }
   // Wrapper around operator delete
   static void delete_GPtRelFit(void *p) {
      delete ((::GPtRelFit*)p);
   }
   static void deleteArray_GPtRelFit(void *p) {
      delete [] ((::GPtRelFit*)p);
   }
   static void destruct_GPtRelFit(void *p) {
      typedef ::GPtRelFit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GPtRelFit

/********************************************************
* /data/zenith234d/stefan/GoodCodeGit/libraries/GutLib/dict/GPtRelFitDict.cxx
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && __GNUC__ >= 4 && ((__GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1) || (__GNUC_MINOR__ >= 3))
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtableGPtRelFitDict();

extern "C" void G__set_cpp_environmentGPtRelFitDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("/data/zenith234d/stefan/GoodCodeGit/libraries/GutLib/inc//GPtRelFit.h");
  G__cpp_reset_tagtableGPtRelFitDict();
}
#include <new>
extern "C" int G__cpp_dllrevGPtRelFitDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* GPtRelFit */
static int G__GPtRelFitDict_165_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GPtRelFit* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GPtRelFit[n];
     } else {
       p = new((void*) gvp) GPtRelFit[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GPtRelFit;
     } else {
       p = new((void*) gvp) GPtRelFit;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GPtRelFitDictLN_GPtRelFit));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GPtRelFit* p = NULL;
   char* gvp = (char*) G__getgvp();
   //m: 10
   if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
     p = new GPtRelFit(
*((TString*) G__int(libp->para[0])), (Double_t) G__double(libp->para[1])
, (Double_t) G__double(libp->para[2]), (Double_t) G__double(libp->para[3])
, (Double_t) G__double(libp->para[4]), (Double_t) G__double(libp->para[5])
, (Double_t) G__double(libp->para[6]), (Double_t) G__double(libp->para[7])
, (Int_t) G__int(libp->para[8]), (Int_t) G__int(libp->para[9]));
   } else {
     p = new((void*) gvp) GPtRelFit(
*((TString*) G__int(libp->para[0])), (Double_t) G__double(libp->para[1])
, (Double_t) G__double(libp->para[2]), (Double_t) G__double(libp->para[3])
, (Double_t) G__double(libp->para[4]), (Double_t) G__double(libp->para[5])
, (Double_t) G__double(libp->para[6]), (Double_t) G__double(libp->para[7])
, (Int_t) G__int(libp->para[8]), (Int_t) G__int(libp->para[9]));
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GPtRelFitDictLN_GPtRelFit));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      {
         TString* pobj;
         TString xobj = ((GPtRelFit*) G__getstructoffset())->Print(*((TString*) G__int(libp->para[0])));
         pobj = new TString(xobj);
         result7->obj.i = (long) ((void*) pobj);
         result7->ref = result7->obj.i;
         G__store_tempobject(*result7);
      }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      {
         TString* pobj;
         TString xobj = ((GPtRelFit*) G__getstructoffset())->GetName();
         pobj = new TString(xobj);
         result7->obj.i = (long) ((void*) pobj);
         result7->ref = result7->obj.i;
         G__store_tempobject(*result7);
      }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letdouble(result7, 100, (double) ((GPtRelFit*) G__getstructoffset())->GetBScale());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letdouble(result7, 100, (double) ((GPtRelFit*) G__getstructoffset())->GetBScaleErr());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letdouble(result7, 100, (double) ((GPtRelFit*) G__getstructoffset())->GetCLFScale());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letdouble(result7, 100, (double) ((GPtRelFit*) G__getstructoffset())->GetCLFScaleErr());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letdouble(result7, 100, (double) ((GPtRelFit*) G__getstructoffset())->GetBFraction());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letdouble(result7, 100, (double) ((GPtRelFit*) G__getstructoffset())->GetBFractionErr());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letdouble(result7, 100, (double) ((GPtRelFit*) G__getstructoffset())->GetChi2());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((GPtRelFit*) G__getstructoffset())->GetNdof());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((GPtRelFit*) G__getstructoffset())->GetBins());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((GPtRelFit*) G__getstructoffset())->GetParameter());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GPtRelFit*) G__getstructoffset())->SetName(*((TString*) G__int(libp->para[0])));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GPtRelFit*) G__getstructoffset())->SetBScale((Double_t) G__double(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GPtRelFit*) G__getstructoffset())->SetBScaleErr((Double_t) G__double(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GPtRelFit*) G__getstructoffset())->SetCLFScale((Double_t) G__double(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_19(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GPtRelFit*) G__getstructoffset())->SetCLFScaleErr((Double_t) G__double(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_20(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GPtRelFit*) G__getstructoffset())->SetBFraction((Double_t) G__double(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_21(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GPtRelFit*) G__getstructoffset())->SetBFractionErr((Double_t) G__double(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_22(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GPtRelFit*) G__getstructoffset())->SetChi2((Double_t) G__double(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_23(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GPtRelFit*) G__getstructoffset())->SetBins((Int_t) G__int(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_24(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GPtRelFit*) G__getstructoffset())->SetParameter((Int_t) G__int(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_25(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) GPtRelFit::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_26(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GPtRelFit::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_27(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) GPtRelFit::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_28(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      GPtRelFit::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_32(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GPtRelFit*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_33(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GPtRelFit::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_34(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GPtRelFit::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_35(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GPtRelFit::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GPtRelFitDict_165_0_36(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GPtRelFit::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__GPtRelFitDict_165_0_37(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   GPtRelFit* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new GPtRelFit(*(GPtRelFit*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GPtRelFitDictLN_GPtRelFit));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef GPtRelFit G__TGPtRelFit;
static int G__GPtRelFitDict_165_0_38(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   char* gvp = (char*) G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 1
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == (char*)G__PVOID) {
       delete[] (GPtRelFit*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((GPtRelFit*) (soff+(sizeof(GPtRelFit)*i)))->~G__TGPtRelFit();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (GPtRelFit*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((GPtRelFit*) (soff))->~G__TGPtRelFit();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__GPtRelFitDict_165_0_39(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GPtRelFit* dest = (GPtRelFit*) G__getstructoffset();
   *dest = *(GPtRelFit*) libp->para[0].ref;
   const GPtRelFit& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* GPtRelFit */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncGPtRelFitDict {
 public:
  G__Sizep2memfuncGPtRelFitDict(): p(&G__Sizep2memfuncGPtRelFitDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncGPtRelFitDict::*p)();
};

size_t G__get_sizep2memfuncGPtRelFitDict()
{
  G__Sizep2memfuncGPtRelFitDict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritanceGPtRelFitDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__GPtRelFitDictLN_GPtRelFit))) {
     GPtRelFit *G__Lderived;
     G__Lderived=(GPtRelFit*)0x1000;
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GPtRelFitDictLN_GPtRelFit),G__get_linked_tagnum(&G__GPtRelFitDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableGPtRelFitDict() {

   /* Setting up typedef entry */
   G__search_typename2("Int_t",105,-1,0,-1);
   G__setnewtype(-1,"Signed integer 4 bytes (int)",0);
   G__search_typename2("Double_t",100,-1,0,-1);
   G__setnewtype(-1,"Double 8 bytes",0);
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<TSchemaHelper>",117,G__get_linked_tagnum(&G__GPtRelFitDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GPtRelFitDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GPtRelFitDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GPtRelFitDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GPtRelFitDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__GPtRelFitDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* GPtRelFit */
static void G__setup_memvarGPtRelFit(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__GPtRelFitDictLN_GPtRelFit));
   { GPtRelFit *p; p=(GPtRelFit*)0x1000; if (p) { }
   G__memvar_setup((void*)0,117,0,0,G__get_linked_tagnum(&G__GPtRelFitDictLN_TString),-1,-1,4,"fName=",0,"describer of fit");
   G__memvar_setup((void*)0,100,0,0,-1,G__defined_typename("Double_t"),-1,4,"fBScale=",0,"scale factor for b mc");
   G__memvar_setup((void*)0,100,0,0,-1,G__defined_typename("Double_t"),-1,4,"fBScaleErr=",0,"error on scale factor for b mc");
   G__memvar_setup((void*)0,100,0,0,-1,G__defined_typename("Double_t"),-1,4,"fCLFScale=",0,"scale factor for c and lf mc");
   G__memvar_setup((void*)0,100,0,0,-1,G__defined_typename("Double_t"),-1,4,"fCLFScaleErr=",0,"error on scale factor for c and lf mc");
   G__memvar_setup((void*)0,100,0,0,-1,G__defined_typename("Double_t"),-1,4,"fBFraction=",0,"b fraction");
   G__memvar_setup((void*)0,100,0,0,-1,G__defined_typename("Double_t"),-1,4,"fBFractionErr=",0,"error on b fraction");
   G__memvar_setup((void*)0,100,0,0,-1,G__defined_typename("Double_t"),-1,4,"fChi2=",0,"chi2");
   G__memvar_setup((void*)0,105,0,0,-1,G__defined_typename("Int_t"),-1,4,"fBins=",0,"number of bins");
   G__memvar_setup((void*)0,105,0,0,-1,G__defined_typename("Int_t"),-1,4,"fParameter=",0,"number of parameter");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GPtRelFitDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarGPtRelFitDict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncGPtRelFit(void) {
   /* GPtRelFit */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__GPtRelFitDictLN_GPtRelFit));
   G__memfunc_setup("GPtRelFit",849,G__GPtRelFitDict_165_0_1, 105, G__get_linked_tagnum(&G__GPtRelFitDictLN_GPtRelFit), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GPtRelFit",849,G__GPtRelFitDict_165_0_2, 105, G__get_linked_tagnum(&G__GPtRelFitDictLN_GPtRelFit), -1, 0, 10, 1, 1, 0, 
"u 'TString' - 0 - name d - 'Double_t' 0 - bscale "
"d - 'Double_t' 0 - bscaleerr d - 'Double_t' 0 - clfscale "
"d - 'Double_t' 0 - clfscaleerr d - 'Double_t' 0 - bfraction "
"d - 'Double_t' 0 - bfractionerr d - 'Double_t' 0 - chi2 "
"i - 'Int_t' 0 - bins i - 'Int_t' 0 - parameter", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Print",525,G__GPtRelFitDict_165_0_3, 117, G__get_linked_tagnum(&G__GPtRelFitDictLN_TString), -1, 0, 1, 1, 1, 0, "u 'TString' - 0 - option", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetName",673,G__GPtRelFitDict_165_0_4, 117, G__get_linked_tagnum(&G__GPtRelFitDictLN_TString), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetBScale",842,G__GPtRelFitDict_165_0_5, 100, -1, G__defined_typename("Double_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetBScaleErr",1139,G__GPtRelFitDict_165_0_6, 100, -1, G__defined_typename("Double_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetCLFScale",989,G__GPtRelFitDict_165_0_7, 100, -1, G__defined_typename("Double_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetCLFScaleErr",1286,G__GPtRelFitDict_165_0_8, 100, -1, G__defined_typename("Double_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetBFraction",1176,G__GPtRelFitDict_165_0_9, 100, -1, G__defined_typename("Double_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetBFractionErr",1473,G__GPtRelFitDict_165_0_10, 100, -1, G__defined_typename("Double_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetChi2",614,G__GPtRelFitDict_165_0_11, 100, -1, G__defined_typename("Double_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetNdof",679,G__GPtRelFitDict_165_0_12, 105, -1, G__defined_typename("Int_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetBins",684,G__GPtRelFitDict_165_0_13, 105, -1, G__defined_typename("Int_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetParameter",1217,G__GPtRelFitDict_165_0_14, 105, -1, G__defined_typename("Int_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("SetName",685,G__GPtRelFitDict_165_0_15, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TString' - 0 - input", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("SetBScale",854,G__GPtRelFitDict_165_0_16, 121, -1, -1, 0, 1, 1, 1, 0, "d - 'Double_t' 0 - input", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("SetBScaleErr",1151,G__GPtRelFitDict_165_0_17, 121, -1, -1, 0, 1, 1, 1, 0, "d - 'Double_t' 0 - input", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("SetCLFScale",1001,G__GPtRelFitDict_165_0_18, 121, -1, -1, 0, 1, 1, 1, 0, "d - 'Double_t' 0 - input", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("SetCLFScaleErr",1298,G__GPtRelFitDict_165_0_19, 121, -1, -1, 0, 1, 1, 1, 0, "d - 'Double_t' 0 - input", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("SetBFraction",1188,G__GPtRelFitDict_165_0_20, 121, -1, -1, 0, 1, 1, 1, 0, "d - 'Double_t' 0 - input", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("SetBFractionErr",1485,G__GPtRelFitDict_165_0_21, 121, -1, -1, 0, 1, 1, 1, 0, "d - 'Double_t' 0 - input", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("SetChi2",626,G__GPtRelFitDict_165_0_22, 121, -1, -1, 0, 1, 1, 1, 0, "d - 'Double_t' 0 - input", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("SetBins",696,G__GPtRelFitDict_165_0_23, 121, -1, -1, 0, 1, 1, 1, 0, "i - 'Int_t' 0 - input", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("SetParameter",1229,G__GPtRelFitDict_165_0_24, 121, -1, -1, 0, 1, 1, 1, 0, "i - 'Int_t' 0 - input", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Class",502,G__GPtRelFitDict_165_0_25, 85, G__get_linked_tagnum(&G__GPtRelFitDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&GPtRelFit::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__GPtRelFitDict_165_0_26, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GPtRelFit::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__GPtRelFitDict_165_0_27, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&GPtRelFit::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__GPtRelFitDict_165_0_28, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&GPtRelFit::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__GPtRelFitDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 2, 1, 1, 0, 
"u 'TMemberInspector' - 1 - insp C - - 0 - parent", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__GPtRelFitDict_165_0_32, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__GPtRelFitDict_165_0_33, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GPtRelFit::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__GPtRelFitDict_165_0_34, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GPtRelFit::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__GPtRelFitDict_165_0_35, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GPtRelFit::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__GPtRelFitDict_165_0_36, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GPtRelFit::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("GPtRelFit", 849, G__GPtRelFitDict_165_0_37, (int) ('i'), G__get_linked_tagnum(&G__GPtRelFitDictLN_GPtRelFit), -1, 0, 1, 1, 1, 0, "u 'GPtRelFit' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~GPtRelFit", 975, G__GPtRelFitDict_165_0_38, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__GPtRelFitDict_165_0_39, (int) ('u'), G__get_linked_tagnum(&G__GPtRelFitDictLN_GPtRelFit), -1, 1, 1, 1, 1, 0, "u 'GPtRelFit' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncGPtRelFitDict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalGPtRelFitDict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {
}

static void G__cpp_setup_func12() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcGPtRelFitDict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
  G__cpp_setup_func12();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__GPtRelFitDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__GPtRelFitDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__GPtRelFitDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__GPtRelFitDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__GPtRelFitDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__GPtRelFitDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__GPtRelFitDictLN_TString = { "TString" , 99 , -1 };
G__linked_taginfo G__GPtRelFitDictLN_GPtRelFit = { "GPtRelFit" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableGPtRelFitDict() {
  G__GPtRelFitDictLN_TClass.tagnum = -1 ;
  G__GPtRelFitDictLN_TBuffer.tagnum = -1 ;
  G__GPtRelFitDictLN_TMemberInspector.tagnum = -1 ;
  G__GPtRelFitDictLN_TObject.tagnum = -1 ;
  G__GPtRelFitDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__GPtRelFitDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GPtRelFitDictLN_TString.tagnum = -1 ;
  G__GPtRelFitDictLN_GPtRelFit.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableGPtRelFitDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__GPtRelFitDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__GPtRelFitDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__GPtRelFitDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__GPtRelFitDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__GPtRelFitDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__GPtRelFitDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__GPtRelFitDictLN_TString);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__GPtRelFitDictLN_GPtRelFit),sizeof(GPtRelFit),-1,62720,"PtRel Fit parameter",G__setup_memvarGPtRelFit,G__setup_memfuncGPtRelFit);
}
extern "C" void G__cpp_setupGPtRelFitDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupGPtRelFitDict()");
  G__set_cpp_environmentGPtRelFitDict();
  G__cpp_setup_tagtableGPtRelFitDict();

  G__cpp_setup_inheritanceGPtRelFitDict();

  G__cpp_setup_typetableGPtRelFitDict();

  G__cpp_setup_memvarGPtRelFitDict();

  G__cpp_setup_memfuncGPtRelFitDict();
  G__cpp_setup_globalGPtRelFitDict();
  G__cpp_setup_funcGPtRelFitDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncGPtRelFitDict();
  return;
}
class G__cpp_setup_initGPtRelFitDict {
  public:
    G__cpp_setup_initGPtRelFitDict() { G__add_setup_func("GPtRelFitDict",(G__incsetup)(&G__cpp_setupGPtRelFitDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initGPtRelFitDict() { G__remove_setup_func("GPtRelFitDict"); }
};
G__cpp_setup_initGPtRelFitDict G__cpp_setup_initializerGPtRelFitDict;
