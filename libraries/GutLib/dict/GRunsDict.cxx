//
// File generated by rootcint at Thu Oct 23 10:41:38 2014

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
#include "GRunsDict.h"

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
   void GRuns_ShowMembers(void *obj, TMemberInspector &R__insp, char *R__parent);
   static void *new_GRuns(void *p = 0);
   static void *newArray_GRuns(Long_t size, void *p);
   static void delete_GRuns(void *p);
   static void deleteArray_GRuns(void *p);
   static void destruct_GRuns(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GRuns*)
   {
      ::GRuns *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GRuns >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GRuns", ::GRuns::Class_Version(), "/data/zenith234d/stefan/GoodCodeGit/libraries/GutLib/inc//GRuns.h", 23,
                  typeid(::GRuns), DefineBehavior(ptr, ptr),
                  &::GRuns::Dictionary, isa_proxy, 0,
                  sizeof(::GRuns) );
      instance.SetNew(&new_GRuns);
      instance.SetNewArray(&newArray_GRuns);
      instance.SetDelete(&delete_GRuns);
      instance.SetDeleteArray(&deleteArray_GRuns);
      instance.SetDestructor(&destruct_GRuns);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GRuns*)
   {
      return GenerateInitInstanceLocal((::GRuns*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::GRuns*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *GRuns::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *GRuns::Class_Name()
{
   return "GRuns";
}

//______________________________________________________________________________
const char *GRuns::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GRuns*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GRuns::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GRuns*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void GRuns::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GRuns*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *GRuns::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GRuns*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void GRuns::Streamer(TBuffer &R__b)
{
   // Stream an object of class GRuns.

   GPhysObj::Streamer(R__b);
}

//______________________________________________________________________________
void GRuns::ShowMembers(TMemberInspector &R__insp, char *R__parent)
{
      // Inspect the data members of an object of class GRuns.
      TClass *R__cl = ::GRuns::IsA();
      Int_t R__ncp = strlen(R__parent);
      if (R__ncp || R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__parent, "*fRuns", &fRuns);
      R__insp.Inspect(R__cl, R__parent, "fNRuns", &fNRuns);
      R__insp.Inspect(R__cl, R__parent, "*fMVDRuns", &fMVDRuns);
      R__insp.Inspect(R__cl, R__parent, "fNMVDRuns", &fNMVDRuns);
      R__insp.Inspect(R__cl, R__parent, "fPeriod", &fPeriod);
      R__insp.Inspect(R__cl, R__parent, "fMVDPeriod", &fMVDPeriod);
      R__insp.Inspect(R__cl, R__parent, "fCurrentRunNumber", &fCurrentRunNumber);
      R__insp.Inspect(R__cl, R__parent, "fCurrentRunEvtake", &fCurrentRunEvtake);
      R__insp.Inspect(R__cl, R__parent, "fCurrentMVDRunNumber", &fCurrentMVDRunNumber);
      R__insp.Inspect(R__cl, R__parent, "fCurrentRunMvdtake", &fCurrentRunMvdtake);
      R__insp.Inspect(R__cl, R__parent, "fLastAddedLuminosity", &fLastAddedLuminosity);
      R__insp.Inspect(R__cl, R__parent, "fLumiAddedToHeader", &fLumiAddedToHeader);
      GPhysObj::ShowMembers(R__insp, R__parent);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GRuns(void *p) {
      return  p ? new(p) ::GRuns : new ::GRuns;
   }
   static void *newArray_GRuns(Long_t nElements, void *p) {
      return p ? new(p) ::GRuns[nElements] : new ::GRuns[nElements];
   }
   // Wrapper around operator delete
   static void delete_GRuns(void *p) {
      delete ((::GRuns*)p);
   }
   static void deleteArray_GRuns(void *p) {
      delete [] ((::GRuns*)p);
   }
   static void destruct_GRuns(void *p) {
      typedef ::GRuns current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GRuns

/********************************************************
* /data/zenith234d/stefan/GoodCodeGit/libraries/GutLib/dict/GRunsDict.cxx
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

extern "C" void G__cpp_reset_tagtableGRunsDict();

extern "C" void G__set_cpp_environmentGRunsDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("/data/zenith234d/stefan/GoodCodeGit/libraries/GutLib/inc//GRuns.h");
  G__cpp_reset_tagtableGRunsDict();
}
#include <new>
extern "C" int G__cpp_dllrevGRunsDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* GRuns */
static int G__GRunsDict_167_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GRuns* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GRuns[n];
     } else {
       p = new((void*) gvp) GRuns[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GRuns;
     } else {
       p = new((void*) gvp) GRuns;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GRunsDictLN_GRuns));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GRuns*) G__getstructoffset())->CheckUpgradeRun());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GRuns*) G__getstructoffset())->CheckRun());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GRuns*) G__getstructoffset())->CheckMvdtake());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GRuns*) G__getstructoffset())->CheckEvtake());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GRuns*) G__getstructoffset())->InitEvtakeList((EZRunPeriod) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GRuns*) G__getstructoffset())->InitMvdtakeList((EZRunPeriod) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GRuns*) G__getstructoffset())->CheckEvtakeList((Int_t) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GRuns*) G__getstructoffset())->CheckMvdtakeList((Int_t) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) ((GRuns*) G__getstructoffset())->GetRun((Int_t) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((GRuns*) G__getstructoffset())->GetNRuns());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) ((GRuns*) G__getstructoffset())->GetRuns());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GRuns*) G__getstructoffset())->CheckMBTake());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GRuns*) G__getstructoffset())->CheckFMUTake());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GRuns*) G__getstructoffset())->CheckShiftedVertexRuns());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((GRuns*) G__getstructoffset())->MBTAKE((Int_t) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((GRuns*) G__getstructoffset())->FMUTAKE((Int_t) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_19(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((GRuns*) G__getstructoffset())->FMUTAKE96((Int_t) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_20(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((GRuns*) G__getstructoffset())->FMUTAKE97((Int_t) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_21(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((GRuns*) G__getstructoffset())->FMUTAKE99((Int_t) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_22(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((GRuns*) G__getstructoffset())->FMUTAKE00((Int_t) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_23(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((GRuns*) G__getstructoffset())->FMUTAKE04((Int_t) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_24(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letdouble(result7, 100, (double) ((GRuns*) G__getstructoffset())->GetLastAddedLuminosity());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_27(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) GRuns::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_28(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GRuns::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_29(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) GRuns::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_30(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      GRuns::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_34(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GRuns*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_35(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GRuns::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_36(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GRuns::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_37(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GRuns::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GRunsDict_167_0_38(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GRuns::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__GRunsDict_167_0_39(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   GRuns* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new GRuns(*(GRuns*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GRunsDictLN_GRuns));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef GRuns G__TGRuns;
static int G__GRunsDict_167_0_40(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
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
       delete[] (GRuns*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((GRuns*) (soff+(sizeof(GRuns)*i)))->~G__TGRuns();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (GRuns*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((GRuns*) (soff))->~G__TGRuns();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__GRunsDict_167_0_41(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GRuns* dest = (GRuns*) G__getstructoffset();
   *dest = *(GRuns*) libp->para[0].ref;
   const GRuns& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* GRuns */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncGRunsDict {
 public:
  G__Sizep2memfuncGRunsDict(): p(&G__Sizep2memfuncGRunsDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncGRunsDict::*p)();
};

size_t G__get_sizep2memfuncGRunsDict()
{
  G__Sizep2memfuncGRunsDict a;
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
extern "C" void G__cpp_setup_inheritanceGRunsDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__GRunsDictLN_GRuns))) {
     GRuns *G__Lderived;
     G__Lderived=(GRuns*)0x1000;
     {
       GPhysObj *G__Lpbase=(GPhysObj*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GRunsDictLN_GRuns),G__get_linked_tagnum(&G__GRunsDictLN_GPhysObj),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GRunsDictLN_GRuns),G__get_linked_tagnum(&G__GRunsDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,0);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableGRunsDict() {

   /* Setting up typedef entry */
   G__search_typename2("Int_t",105,-1,0,-1);
   G__setnewtype(-1,"Signed integer 4 bytes (int)",0);
   G__search_typename2("Double_t",100,-1,0,-1);
   G__setnewtype(-1,"Double 8 bytes",0);
   G__search_typename2("Bool_t",103,-1,0,-1);
   G__setnewtype(-1,"Boolean (0=false, 1=true) (bool)",0);
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<TSchemaHelper>",117,G__get_linked_tagnum(&G__GRunsDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GRunsDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GRunsDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GRunsDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GRunsDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__GRunsDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* GRuns */
static void G__setup_memvarGRuns(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__GRunsDictLN_GRuns));
   { GRuns *p; p=(GRuns*)0x1000; if (p) { }
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GRunsDictLN_TClonesArray),-1,-1,4,"fRuns=",0,"array of runs from evtake list");
   G__memvar_setup((void*)0,105,0,0,-1,G__defined_typename("Int_t"),-1,4,"fNRuns=",0,"counter for runs from evtake list");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GRunsDictLN_TClonesArray),-1,-1,4,"fMVDRuns=",0,"array of runs from mvdtake list");
   G__memvar_setup((void*)0,105,0,0,-1,G__defined_typename("Int_t"),-1,4,"fNMVDRuns=",0,"counter for runs from mvdtake list");
   G__memvar_setup((void*)0,105,0,0,G__get_linked_tagnum(&G__GRunsDictLN_EZRunPeriod),-1,-1,4,"fPeriod=",0,"period for runs which are currently filled in arrays");
   G__memvar_setup((void*)0,105,0,0,G__get_linked_tagnum(&G__GRunsDictLN_EZRunPeriod),-1,-1,4,"fMVDPeriod=",0,"period for mvd runs which are currently filled in arrays");
   G__memvar_setup((void*)0,105,0,0,-1,G__defined_typename("Int_t"),-1,4,"fCurrentRunNumber=",0,"current checked run for evtake");
   G__memvar_setup((void*)0,103,0,0,-1,G__defined_typename("Bool_t"),-1,4,"fCurrentRunEvtake=",0,"result of evtake for current run");
   G__memvar_setup((void*)0,105,0,0,-1,G__defined_typename("Int_t"),-1,4,"fCurrentMVDRunNumber=",0,"current checked run for mvdtake");
   G__memvar_setup((void*)0,103,0,0,-1,G__defined_typename("Bool_t"),-1,4,"fCurrentRunMvdtake=",0,"result of mvdtake for current run");
   G__memvar_setup((void*)0,100,0,0,-1,G__defined_typename("Double_t"),-1,4,"fLastAddedLuminosity=",0,"has to be substracted again if mvdtake or evtake is activated and activated beamspotcut is kFALSE");
   G__memvar_setup((void*)0,103,0,0,-1,G__defined_typename("Bool_t"),-1,4,"fLumiAddedToHeader=",0,"flag if lumi for current run was added to header counter");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GRunsDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarGRunsDict() {
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
static void G__setup_memfuncGRuns(void) {
   /* GRuns */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__GRunsDictLN_GRuns));
   G__memfunc_setup("GRuns",495,G__GRunsDict_167_0_1, 105, G__get_linked_tagnum(&G__GRunsDictLN_GRuns), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetAllCuts",984,(G__InterfaceMethod) NULL,103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("CheckUpgradeRun",1499,G__GRunsDict_167_0_3, 103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("CheckRun",787,G__GRunsDict_167_0_4, 103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("CheckMvdtake",1194,G__GRunsDict_167_0_5, 103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("CheckEvtake",1086,G__GRunsDict_167_0_6, 103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("InitEvtakeList",1424,G__GRunsDict_167_0_7, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "i 'EZRunPeriod' - 0 - period", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("InitMvdtakeList",1532,G__GRunsDict_167_0_8, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "i 'EZRunPeriod' - 0 - period", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("CheckEvtakeList",1498,G__GRunsDict_167_0_9, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "i - 'Int_t' 0 - runnr", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("CheckMvdtakeList",1606,G__GRunsDict_167_0_10, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "i - 'Int_t' 0 - runnr", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetRun",597,G__GRunsDict_167_0_11, 85, G__get_linked_tagnum(&G__GRunsDictLN_GRun), -1, 0, 1, 1, 1, 0, "i - 'Int_t' 0 - runnummer", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetNRuns",790,G__GRunsDict_167_0_12, 105, -1, G__defined_typename("Int_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetRuns",712,G__GRunsDict_167_0_13, 85, G__get_linked_tagnum(&G__GRunsDictLN_TClonesArray), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("CheckMBTake",1010,G__GRunsDict_167_0_14, 103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("CheckFMUTake",1099,G__GRunsDict_167_0_15, 103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("CheckShiftedVertexRuns",2251,G__GRunsDict_167_0_16, 103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MBTAKE",436,G__GRunsDict_167_0_17, 105, -1, G__defined_typename("Int_t"), 0, 1, 1, 1, 0, "i - 'Int_t' 0 - run", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("FMUTAKE",525,G__GRunsDict_167_0_18, 105, -1, G__defined_typename("Int_t"), 0, 1, 1, 1, 0, "i - 'Int_t' 0 - run", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("FMUTAKE96",636,G__GRunsDict_167_0_19, 105, -1, G__defined_typename("Int_t"), 0, 1, 1, 1, 0, "i - 'Int_t' 0 - run", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("FMUTAKE97",637,G__GRunsDict_167_0_20, 105, -1, G__defined_typename("Int_t"), 0, 1, 1, 1, 0, "i - 'Int_t' 0 - run", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("FMUTAKE99",639,G__GRunsDict_167_0_21, 105, -1, G__defined_typename("Int_t"), 0, 1, 1, 1, 0, "i - 'Int_t' 0 - run", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("FMUTAKE00",621,G__GRunsDict_167_0_22, 105, -1, G__defined_typename("Int_t"), 0, 1, 1, 1, 0, "i - 'Int_t' 0 - run", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("FMUTAKE04",625,G__GRunsDict_167_0_23, 105, -1, G__defined_typename("Int_t"), 0, 1, 1, 1, 0, "i - 'Int_t' 0 - run", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetLastAddedLuminosity",2243,G__GRunsDict_167_0_24, 100, -1, G__defined_typename("Double_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("PrintMessage",1234,(G__InterfaceMethod) NULL,117, G__get_linked_tagnum(&G__GRunsDictLN_TString), -1, 0, 1, 1, 1, 0, "u 'TString' - 0 - option", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Print",525,(G__InterfaceMethod) NULL,103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "u 'TString' - 0 - option", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Class",502,G__GRunsDict_167_0_27, 85, G__get_linked_tagnum(&G__GRunsDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&GRuns::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__GRunsDict_167_0_28, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GRuns::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__GRunsDict_167_0_29, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&GRuns::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__GRunsDict_167_0_30, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&GRuns::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__GRunsDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 2, 1, 1, 0, 
"u 'TMemberInspector' - 1 - insp C - - 0 - parent", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__GRunsDict_167_0_34, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__GRunsDict_167_0_35, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GRuns::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__GRunsDict_167_0_36, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GRuns::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__GRunsDict_167_0_37, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GRuns::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__GRunsDict_167_0_38, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GRuns::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("GRuns", 495, G__GRunsDict_167_0_39, (int) ('i'), G__get_linked_tagnum(&G__GRunsDictLN_GRuns), -1, 0, 1, 1, 1, 0, "u 'GRuns' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~GRuns", 621, G__GRunsDict_167_0_40, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__GRunsDict_167_0_41, (int) ('u'), G__get_linked_tagnum(&G__GRunsDictLN_GRuns), -1, 1, 1, 1, 1, 0, "u 'GRuns' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncGRunsDict() {
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
extern "C" void G__cpp_setup_globalGRunsDict() {
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

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcGRunsDict() {
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
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__GRunsDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__GRunsDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__GRunsDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__GRunsDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__GRunsDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__GRunsDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__GRunsDictLN_TString = { "TString" , 99 , -1 };
G__linked_taginfo G__GRunsDictLN_TClonesArray = { "TClonesArray" , 99 , -1 };
G__linked_taginfo G__GRunsDictLN_GPhysObj = { "GPhysObj" , 99 , -1 };
G__linked_taginfo G__GRunsDictLN_EZRunPeriod = { "EZRunPeriod" , 101 , -1 };
G__linked_taginfo G__GRunsDictLN_GRun = { "GRun" , 99 , -1 };
G__linked_taginfo G__GRunsDictLN_GRuns = { "GRuns" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableGRunsDict() {
  G__GRunsDictLN_TClass.tagnum = -1 ;
  G__GRunsDictLN_TBuffer.tagnum = -1 ;
  G__GRunsDictLN_TMemberInspector.tagnum = -1 ;
  G__GRunsDictLN_TObject.tagnum = -1 ;
  G__GRunsDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__GRunsDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GRunsDictLN_TString.tagnum = -1 ;
  G__GRunsDictLN_TClonesArray.tagnum = -1 ;
  G__GRunsDictLN_GPhysObj.tagnum = -1 ;
  G__GRunsDictLN_EZRunPeriod.tagnum = -1 ;
  G__GRunsDictLN_GRun.tagnum = -1 ;
  G__GRunsDictLN_GRuns.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableGRunsDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__GRunsDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__GRunsDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__GRunsDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__GRunsDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__GRunsDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__GRunsDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__GRunsDictLN_TString);
   G__get_linked_tagnum_fwd(&G__GRunsDictLN_TClonesArray);
   G__get_linked_tagnum_fwd(&G__GRunsDictLN_GPhysObj);
   G__get_linked_tagnum_fwd(&G__GRunsDictLN_EZRunPeriod);
   G__get_linked_tagnum_fwd(&G__GRunsDictLN_GRun);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__GRunsDictLN_GRuns),sizeof(GRuns),-1,29952,"Runs Class for everything which is related only to run information",G__setup_memvarGRuns,G__setup_memfuncGRuns);
}
extern "C" void G__cpp_setupGRunsDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupGRunsDict()");
  G__set_cpp_environmentGRunsDict();
  G__cpp_setup_tagtableGRunsDict();

  G__cpp_setup_inheritanceGRunsDict();

  G__cpp_setup_typetableGRunsDict();

  G__cpp_setup_memvarGRunsDict();

  G__cpp_setup_memfuncGRunsDict();
  G__cpp_setup_globalGRunsDict();
  G__cpp_setup_funcGRunsDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncGRunsDict();
  return;
}
class G__cpp_setup_initGRunsDict {
  public:
    G__cpp_setup_initGRunsDict() { G__add_setup_func("GRunsDict",(G__incsetup)(&G__cpp_setupGRunsDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initGRunsDict() { G__remove_setup_func("GRunsDict"); }
};
G__cpp_setup_initGRunsDict G__cpp_setup_initializerGRunsDict;
