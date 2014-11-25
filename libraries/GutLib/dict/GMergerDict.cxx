//
// File generated by rootcint at Fri Oct 24 10:58:02 2014

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
#include "GMergerDict.h"

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
   void GMerger_ShowMembers(void *obj, TMemberInspector &R__insp, char *R__parent);
   static void *new_GMerger(void *p = 0);
   static void *newArray_GMerger(Long_t size, void *p);
   static void delete_GMerger(void *p);
   static void deleteArray_GMerger(void *p);
   static void destruct_GMerger(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GMerger*)
   {
      ::GMerger *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GMerger >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GMerger", ::GMerger::Class_Version(), "/data/zenith234d/stefan/GoodCodeGit/libraries/GutLib/inc//GMerger.h", 20,
                  typeid(::GMerger), DefineBehavior(ptr, ptr),
                  &::GMerger::Dictionary, isa_proxy, 0,
                  sizeof(::GMerger) );
      instance.SetNew(&new_GMerger);
      instance.SetNewArray(&newArray_GMerger);
      instance.SetDelete(&delete_GMerger);
      instance.SetDeleteArray(&deleteArray_GMerger);
      instance.SetDestructor(&destruct_GMerger);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GMerger*)
   {
      return GenerateInitInstanceLocal((::GMerger*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::GMerger*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *GMerger::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *GMerger::Class_Name()
{
   return "GMerger";
}

//______________________________________________________________________________
const char *GMerger::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GMerger*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GMerger::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GMerger*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void GMerger::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GMerger*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *GMerger::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GMerger*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void GMerger::Streamer(TBuffer &R__b)
{
   // Stream an object of class GMerger.

   TObject::Streamer(R__b);
}

//______________________________________________________________________________
void GMerger::ShowMembers(TMemberInspector &R__insp, char *R__parent)
{
      // Inspect the data members of an object of class GMerger.
      TClass *R__cl = ::GMerger::IsA();
      Int_t R__ncp = strlen(R__parent);
      if (R__ncp || R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__parent, "*fOneD", &fOneD);
      R__insp.Inspect(R__cl, R__parent, "*fOneD_unweighted", &fOneD_unweighted);
      R__insp.Inspect(R__cl, R__parent, "*fOneDLabel", &fOneDLabel);
      R__insp.Inspect(R__cl, R__parent, "*fTwoD", &fTwoD);
      R__insp.Inspect(R__cl, R__parent, "*fTwoD_unweighted", &fTwoD_unweighted);
      R__insp.Inspect(R__cl, R__parent, "*fPtRel", &fPtRel);
      R__insp.Inspect(R__cl, R__parent, "*fOneDCopy", &fOneDCopy);
      R__insp.Inspect(R__cl, R__parent, "*fImpact", &fImpact);
      R__insp.Inspect(R__cl, R__parent, "*fTwoDProjection", &fTwoDProjection);
      TObject::ShowMembers(R__insp, R__parent);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GMerger(void *p) {
      return  p ? new(p) ::GMerger : new ::GMerger;
   }
   static void *newArray_GMerger(Long_t nElements, void *p) {
      return p ? new(p) ::GMerger[nElements] : new ::GMerger[nElements];
   }
   // Wrapper around operator delete
   static void delete_GMerger(void *p) {
      delete ((::GMerger*)p);
   }
   static void deleteArray_GMerger(void *p) {
      delete [] ((::GMerger*)p);
   }
   static void destruct_GMerger(void *p) {
      typedef ::GMerger current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GMerger

/********************************************************
* /data/zenith234d/stefan/GoodCodeGit/libraries/GutLib/dict/GMergerDict.cxx
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

extern "C" void G__cpp_reset_tagtableGMergerDict();

extern "C" void G__set_cpp_environmentGMergerDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("/data/zenith234d/stefan/GoodCodeGit/libraries/GutLib/inc//GMerger.h");
  G__cpp_reset_tagtableGMergerDict();
}
#include <new>
extern "C" int G__cpp_dllrevGMergerDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* GMerger */
static int G__GMergerDict_155_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GMerger* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GMerger[n];
     } else {
       p = new((void*) gvp) GMerger[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GMerger;
     } else {
       p = new((void*) gvp) GMerger;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GMergerDictLN_GMerger));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GMerger* p = NULL;
   char* gvp = (char*) G__getgvp();
   //m: 2
   if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
     p = new GMerger((int) G__int(libp->para[0]), (char**) G__int(libp->para[1]));
   } else {
     p = new((void*) gvp) GMerger((int) G__int(libp->para[0]), (char**) G__int(libp->para[1]));
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GMergerDictLN_GMerger));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->DecodeCommandline((int) G__int(libp->para[0]), (char**) G__int(libp->para[1])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      {
         TString* pobj;
         TString xobj = ((GMerger*) G__getstructoffset())->HelpMessage();
         pobj = new TString(xobj);
         result7->obj.i = (long) ((void*) pobj);
         result7->ref = result7->obj.i;
         G__store_tempobject(*result7);
      }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->InitLists());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistoFiles((TFile*) G__int(libp->para[0]), (TFile*) G__int(libp->para[1])
, *((TString*) G__int(libp->para[2]))));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistoTree((TFile*) G__int(libp->para[0]), (TFile*) G__int(libp->para[1])
, *((TString*) G__int(libp->para[2]))));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->CopyFile(*((TString*) G__int(libp->para[0])), *((TString*) G__int(libp->para[1]))
, *((TString*) G__int(libp->para[2]))));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->CopyFiles(*((TString*) G__int(libp->para[0])), *((TString*) G__int(libp->para[1]))
, *((TString*) G__int(libp->para[2]))));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistograms(*((TString*) G__int(libp->para[0]))));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistogramsStage1((TFile*) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistogramsStage2((TFile*) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistogramsStage3((TFile*) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistogramsStage4((TFile*) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistogramsPtRel((TFile*) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistogramsImpact((TFile*) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistogramsStage1(*((TString*) G__int(libp->para[0]))));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistogramsStage2(*((TString*) G__int(libp->para[0]))));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_19(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistogramsStage3(*((TString*) G__int(libp->para[0]))));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_20(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistogramsStage4(*((TString*) G__int(libp->para[0]))));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_21(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistogramsPtRel(*((TString*) G__int(libp->para[0]))));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_22(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MergeHistogramsImpact(*((TString*) G__int(libp->para[0]))));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_23(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->FinalizeHistograms(*((TString*) G__int(libp->para[0]))));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_24(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GMerger*) G__getstructoffset())->MakeProjections((TFile*) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_25(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) GMerger::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_26(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GMerger::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_27(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) GMerger::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_28(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      GMerger::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_32(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GMerger*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_33(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GMerger::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_34(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GMerger::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_35(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GMerger::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GMergerDict_155_0_36(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GMerger::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__GMergerDict_155_0_37(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   GMerger* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new GMerger(*(GMerger*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GMergerDictLN_GMerger));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef GMerger G__TGMerger;
static int G__GMergerDict_155_0_38(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
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
       delete[] (GMerger*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((GMerger*) (soff+(sizeof(GMerger)*i)))->~G__TGMerger();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (GMerger*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((GMerger*) (soff))->~G__TGMerger();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__GMergerDict_155_0_39(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GMerger* dest = (GMerger*) G__getstructoffset();
   *dest = *(GMerger*) libp->para[0].ref;
   const GMerger& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* GMerger */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncGMergerDict {
 public:
  G__Sizep2memfuncGMergerDict(): p(&G__Sizep2memfuncGMergerDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncGMergerDict::*p)();
};

size_t G__get_sizep2memfuncGMergerDict()
{
  G__Sizep2memfuncGMergerDict a;
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
extern "C" void G__cpp_setup_inheritanceGMergerDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__GMergerDictLN_GMerger))) {
     GMerger *G__Lderived;
     G__Lderived=(GMerger*)0x1000;
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GMergerDictLN_GMerger),G__get_linked_tagnum(&G__GMergerDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableGMergerDict() {

   /* Setting up typedef entry */
   G__search_typename2("Bool_t",103,-1,0,-1);
   G__setnewtype(-1,"Boolean (0=false, 1=true) (bool)",0);
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<TSchemaHelper>",117,G__get_linked_tagnum(&G__GMergerDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GMergerDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GMergerDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GMergerDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GMergerDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__GMergerDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* GMerger */
static void G__setup_memvarGMerger(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__GMergerDictLN_GMerger));
   { GMerger *p; p=(GMerger*)0x1000; if (p) { }
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GMergerDictLN_TList),-1,-1,4,"fOneD=",0,"list of 1-D histogram names");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GMergerDictLN_TList),-1,-1,4,"fOneD_unweighted=",0,"list of unweighted 1-D histogram names");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GMergerDictLN_TList),-1,-1,4,"fOneDLabel=",0,"list of 1d labeled histograms");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GMergerDictLN_TList),-1,-1,4,"fTwoD=",0,"list of 2-D histogram names");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GMergerDictLN_TList),-1,-1,4,"fTwoD_unweighted=",0,"list of 2-D histogram names");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GMergerDictLN_TList),-1,-1,4,"fPtRel=",0,"list of histograms for which the ptrel fit is done");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GMergerDictLN_TList),-1,-1,4,"fOneDCopy=",0,"list of MC histograms which are only copied to the next higher level");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GMergerDictLN_TList),-1,-1,4,"fImpact=",0,"list of histograms for which the impact fit is done");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GMergerDictLN_TList),-1,-1,4,"fTwoDProjection=",0,"list of 2D Histograms to make 1D Projections");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GMergerDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarGMergerDict() {
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
static void G__setup_memfuncGMerger(void) {
   /* GMerger */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__GMergerDictLN_GMerger));
   G__memfunc_setup("GMerger",681,G__GMergerDict_155_0_1, 105, G__get_linked_tagnum(&G__GMergerDictLN_GMerger), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GMerger",681,G__GMergerDict_155_0_2, 105, G__get_linked_tagnum(&G__GMergerDictLN_GMerger), -1, 0, 2, 1, 1, 0, 
"i - - 0 - argc C - - 2 - argv", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DecodeCommandline",1707,G__GMergerDict_155_0_3, 103, -1, G__defined_typename("Bool_t"), 0, 2, 1, 1, 0, 
"i - - 0 - argc C - - 2 - argv", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("HelpMessage",1102,G__GMergerDict_155_0_4, 117, G__get_linked_tagnum(&G__GMergerDictLN_TString), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("InitLists",931,G__GMergerDict_155_0_5, 103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistoFiles",1514,G__GMergerDict_155_0_6, 103, -1, G__defined_typename("Bool_t"), 0, 3, 1, 1, 0, 
"U 'TFile' - 0 - inputfile U 'TFile' - 0 - outputfile "
"u 'TString' - 0 - directory", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistoTree",1415,G__GMergerDict_155_0_7, 103, -1, G__defined_typename("Bool_t"), 0, 3, 1, 1, 0, 
"U 'TFile' - 0 - inputfile U 'TFile' - 0 - outputfile "
"u 'TString' - 0 - directory", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("CopyFile",795,G__GMergerDict_155_0_8, 103, -1, G__defined_typename("Bool_t"), 0, 3, 1, 1, 0, 
"u 'TString' - 0 - inputfile u 'TString' - 0 - outpufile "
"u 'TString' - 0 - directory", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("CopyFiles",910,G__GMergerDict_155_0_9, 103, -1, G__defined_typename("Bool_t"), 0, 3, 1, 1, 0, 
"u 'TString' - 0 - inputfiles u 'TString' - 0 - outpufile "
"u 'TString' - 0 - directory", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistograms",1553,G__GMergerDict_155_0_10, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "u 'TString' - 0 - filename", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistogramsStage1",2102,G__GMergerDict_155_0_11, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "U 'TFile' - 0 - file", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistogramsStage2",2103,G__GMergerDict_155_0_12, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "U 'TFile' - 0 - file", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistogramsStage3",2104,G__GMergerDict_155_0_13, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "U 'TFile' - 0 - file", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistogramsStage4",2105,G__GMergerDict_155_0_14, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "U 'TFile' - 0 - file", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistogramsPtRel",2040,G__GMergerDict_155_0_15, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "U 'TFile' - 0 - file", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistogramsImpact",2159,G__GMergerDict_155_0_16, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "U 'TFile' - 0 - file", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistogramsStage1",2102,G__GMergerDict_155_0_17, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "u 'TString' - 0 - filename", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistogramsStage2",2103,G__GMergerDict_155_0_18, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "u 'TString' - 0 - filename", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistogramsStage3",2104,G__GMergerDict_155_0_19, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "u 'TString' - 0 - filename", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistogramsStage4",2105,G__GMergerDict_155_0_20, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "u 'TString' - 0 - filename", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistogramsPtRel",2040,G__GMergerDict_155_0_21, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "u 'TString' - 0 - filename", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MergeHistogramsImpact",2159,G__GMergerDict_155_0_22, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "u 'TString' - 0 - filename", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("FinalizeHistograms",1875,G__GMergerDict_155_0_23, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "u 'TString' - 0 - filename", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("MakeProjections",1550,G__GMergerDict_155_0_24, 103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "U 'TFile' - 0 - file", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Class",502,G__GMergerDict_155_0_25, 85, G__get_linked_tagnum(&G__GMergerDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&GMerger::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__GMergerDict_155_0_26, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GMerger::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__GMergerDict_155_0_27, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&GMerger::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__GMergerDict_155_0_28, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&GMerger::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__GMergerDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 2, 1, 1, 0, 
"u 'TMemberInspector' - 1 - insp C - - 0 - parent", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__GMergerDict_155_0_32, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__GMergerDict_155_0_33, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GMerger::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__GMergerDict_155_0_34, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GMerger::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__GMergerDict_155_0_35, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GMerger::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__GMergerDict_155_0_36, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GMerger::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("GMerger", 681, G__GMergerDict_155_0_37, (int) ('i'), G__get_linked_tagnum(&G__GMergerDictLN_GMerger), -1, 0, 1, 1, 1, 0, "u 'GMerger' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~GMerger", 807, G__GMergerDict_155_0_38, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__GMergerDict_155_0_39, (int) ('u'), G__get_linked_tagnum(&G__GMergerDictLN_GMerger), -1, 1, 1, 1, 1, 0, "u 'GMerger' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncGMergerDict() {
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
extern "C" void G__cpp_setup_globalGMergerDict() {
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

extern "C" void G__cpp_setup_funcGMergerDict() {
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
G__linked_taginfo G__GMergerDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__GMergerDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__GMergerDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__GMergerDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__GMergerDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__GMergerDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__GMergerDictLN_TList = { "TList" , 99 , -1 };
G__linked_taginfo G__GMergerDictLN_TString = { "TString" , 99 , -1 };
G__linked_taginfo G__GMergerDictLN_TFile = { "TFile" , 99 , -1 };
G__linked_taginfo G__GMergerDictLN_GMerger = { "GMerger" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableGMergerDict() {
  G__GMergerDictLN_TClass.tagnum = -1 ;
  G__GMergerDictLN_TBuffer.tagnum = -1 ;
  G__GMergerDictLN_TMemberInspector.tagnum = -1 ;
  G__GMergerDictLN_TObject.tagnum = -1 ;
  G__GMergerDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__GMergerDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GMergerDictLN_TList.tagnum = -1 ;
  G__GMergerDictLN_TString.tagnum = -1 ;
  G__GMergerDictLN_TFile.tagnum = -1 ;
  G__GMergerDictLN_GMerger.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableGMergerDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__GMergerDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__GMergerDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__GMergerDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__GMergerDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__GMergerDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__GMergerDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__GMergerDictLN_TList);
   G__get_linked_tagnum_fwd(&G__GMergerDictLN_TString);
   G__get_linked_tagnum_fwd(&G__GMergerDictLN_TFile);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__GMergerDictLN_GMerger),sizeof(GMerger),-1,62720,"merges histogram and tree files to one file",G__setup_memvarGMerger,G__setup_memfuncGMerger);
}
extern "C" void G__cpp_setupGMergerDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupGMergerDict()");
  G__set_cpp_environmentGMergerDict();
  G__cpp_setup_tagtableGMergerDict();

  G__cpp_setup_inheritanceGMergerDict();

  G__cpp_setup_typetableGMergerDict();

  G__cpp_setup_memvarGMergerDict();

  G__cpp_setup_memfuncGMergerDict();
  G__cpp_setup_globalGMergerDict();
  G__cpp_setup_funcGMergerDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncGMergerDict();
  return;
}
class G__cpp_setup_initGMergerDict {
  public:
    G__cpp_setup_initGMergerDict() { G__add_setup_func("GMergerDict",(G__incsetup)(&G__cpp_setupGMergerDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initGMergerDict() { G__remove_setup_func("GMergerDict"); }
};
G__cpp_setup_initGMergerDict G__cpp_setup_initializerGMergerDict;

