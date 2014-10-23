//
// File generated by rootcint at Thu Oct 23 10:41:32 2014

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
#include "GBacDict.h"

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
   void GBac_ShowMembers(void *obj, TMemberInspector &R__insp, char *R__parent);
   static void *new_GBac(void *p = 0);
   static void *newArray_GBac(Long_t size, void *p);
   static void delete_GBac(void *p);
   static void deleteArray_GBac(void *p);
   static void destruct_GBac(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::GBac*)
   {
      ::GBac *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::GBac >(0);
      static ::ROOT::TGenericClassInfo 
         instance("GBac", ::GBac::Class_Version(), "/data/zenith234d/stefan/GoodCodeGit/libraries/GutLib/inc//GBac.h", 16,
                  typeid(::GBac), DefineBehavior(ptr, ptr),
                  &::GBac::Dictionary, isa_proxy, 0,
                  sizeof(::GBac) );
      instance.SetNew(&new_GBac);
      instance.SetNewArray(&newArray_GBac);
      instance.SetDelete(&delete_GBac);
      instance.SetDeleteArray(&deleteArray_GBac);
      instance.SetDestructor(&destruct_GBac);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::GBac*)
   {
      return GenerateInitInstanceLocal((::GBac*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::GBac*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *GBac::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *GBac::Class_Name()
{
   return "GBac";
}

//______________________________________________________________________________
const char *GBac::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GBac*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GBac::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::GBac*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void GBac::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GBac*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *GBac::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::GBac*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void GBac::Streamer(TBuffer &R__b)
{
   // Stream an object of class GBac.

   GPhysObj::Streamer(R__b);
}

//______________________________________________________________________________
void GBac::ShowMembers(TMemberInspector &R__insp, char *R__parent)
{
      // Inspect the data members of an object of class GBac.
      TClass *R__cl = ::GBac::IsA();
      Int_t R__ncp = strlen(R__parent);
      if (R__ncp || R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__parent, "fbac_etotCut", &fbac_etotCut);
      R__insp.Inspect(R__cl, R__parent, "fnbacmuCut", &fnbacmuCut);
      R__insp.Inspect(R__cl, R__parent, "*fGeneralbac_etot", &fGeneralbac_etot);
      R__insp.Inspect(R__cl, R__parent, "*fGeneralnbacmu", &fGeneralnbacmu);
      R__insp.Inspect(R__cl, R__parent, "*fGeneralbac_etot_uncut", &fGeneralbac_etot_uncut);
      R__insp.Inspect(R__cl, R__parent, "*fGeneralnbacmu_uncut", &fGeneralnbacmu_uncut);
      R__insp.Inspect(R__cl, R__parent, "*fControlbac_etot", &fControlbac_etot);
      R__insp.Inspect(R__cl, R__parent, "*fControlnbacmu", &fControlnbacmu);
      R__insp.Inspect(R__cl, R__parent, "*fControlbac_etot_uncut", &fControlbac_etot_uncut);
      R__insp.Inspect(R__cl, R__parent, "*fControlnbacmu_uncut", &fControlnbacmu_uncut);
      GPhysObj::ShowMembers(R__insp, R__parent);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_GBac(void *p) {
      return  p ? new(p) ::GBac : new ::GBac;
   }
   static void *newArray_GBac(Long_t nElements, void *p) {
      return p ? new(p) ::GBac[nElements] : new ::GBac[nElements];
   }
   // Wrapper around operator delete
   static void delete_GBac(void *p) {
      delete ((::GBac*)p);
   }
   static void deleteArray_GBac(void *p) {
      delete [] ((::GBac*)p);
   }
   static void destruct_GBac(void *p) {
      typedef ::GBac current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::GBac

/********************************************************
* /data/zenith234d/stefan/GoodCodeGit/libraries/GutLib/dict/GBacDict.cxx
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

extern "C" void G__cpp_reset_tagtableGBacDict();

extern "C" void G__set_cpp_environmentGBacDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("/data/zenith234d/stefan/GoodCodeGit/libraries/GutLib/inc//GBac.h");
  G__cpp_reset_tagtableGBacDict();
}
#include <new>
extern "C" int G__cpp_dllrevGBacDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* GBac */
static int G__GBacDict_164_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GBac* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GBac[n];
     } else {
       p = new((void*) gvp) GBac[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new GBac;
     } else {
       p = new((void*) gvp) GBac;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GBacDictLN_GBac));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GBacDict_164_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GBac*) G__getstructoffset())->Checkbac_etotCut());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GBacDict_164_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GBac*) G__getstructoffset())->ChecknbacmuCut());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GBacDict_164_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GBac*) G__getstructoffset())->Getbac_etotCut());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GBacDict_164_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((GBac*) G__getstructoffset())->GetnbacmuCut());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GBacDict_164_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) GBac::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GBacDict_164_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GBac::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GBacDict_164_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) GBac::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GBacDict_164_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      GBac::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GBacDict_164_0_22(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((GBac*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GBacDict_164_0_23(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GBac::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GBacDict_164_0_24(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GBac::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GBacDict_164_0_25(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) GBac::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__GBacDict_164_0_26(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) GBac::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__GBacDict_164_0_27(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   GBac* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new GBac(*(GBac*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__GBacDictLN_GBac));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef GBac G__TGBac;
static int G__GBacDict_164_0_28(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
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
       delete[] (GBac*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((GBac*) (soff+(sizeof(GBac)*i)))->~G__TGBac();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (GBac*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((GBac*) (soff))->~G__TGBac();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__GBacDict_164_0_29(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   GBac* dest = (GBac*) G__getstructoffset();
   *dest = *(GBac*) libp->para[0].ref;
   const GBac& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* GBac */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncGBacDict {
 public:
  G__Sizep2memfuncGBacDict(): p(&G__Sizep2memfuncGBacDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncGBacDict::*p)();
};

size_t G__get_sizep2memfuncGBacDict()
{
  G__Sizep2memfuncGBacDict a;
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
extern "C" void G__cpp_setup_inheritanceGBacDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__GBacDictLN_GBac))) {
     GBac *G__Lderived;
     G__Lderived=(GBac*)0x1000;
     {
       GPhysObj *G__Lpbase=(GPhysObj*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GBacDictLN_GBac),G__get_linked_tagnum(&G__GBacDictLN_GPhysObj),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__GBacDictLN_GBac),G__get_linked_tagnum(&G__GBacDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,0);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableGBacDict() {

   /* Setting up typedef entry */
   G__search_typename2("Bool_t",103,-1,0,-1);
   G__setnewtype(-1,"Boolean (0=false, 1=true) (bool)",0);
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<TSchemaHelper>",117,G__get_linked_tagnum(&G__GBacDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__GBacDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GBacDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__GBacDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__GBacDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__GBacDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* GBac */
static void G__setup_memvarGBac(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__GBacDictLN_GBac));
   { GBac *p; p=(GBac*)0x1000; if (p) { }
   G__memvar_setup((void*)0,103,0,0,-1,G__defined_typename("Bool_t"),-1,4,"fbac_etotCut=",0,(char*)NULL);
   G__memvar_setup((void*)0,103,0,0,-1,G__defined_typename("Bool_t"),-1,4,"fnbacmuCut=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GBacDictLN_TH1D),-1,-1,4,"fGeneralbac_etot=",0,"bac_etot");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GBacDictLN_TH1D),-1,-1,4,"fGeneralnbacmu=",0,"nbacmu");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GBacDictLN_TH1D),-1,-1,4,"fGeneralbac_etot_uncut=",0,"uncut bac_etot distribution");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GBacDictLN_TH1D),-1,-1,4,"fGeneralnbacmu_uncut=",0,"uncut nbacmu distribution");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GBacDictLN_TH1D),-1,-1,4,"fControlbac_etot=",0,"bac_etot");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GBacDictLN_TH1D),-1,-1,4,"fControlnbacmu=",0,"nbacmu");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GBacDictLN_TH1D),-1,-1,4,"fControlbac_etot_uncut=",0,"uncut bac_etot");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GBacDictLN_TH1D),-1,-1,4,"fControlnbacmu_uncut=",0,"uncut nbacmu");
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__GBacDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarGBacDict() {
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
static void G__setup_memfuncGBac(void) {
   /* GBac */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__GBacDictLN_GBac));
   G__memfunc_setup("GBac",333,G__GBacDict_164_0_1, 105, G__get_linked_tagnum(&G__GBacDictLN_GBac), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("CreateGeneral",1298,(G__InterfaceMethod) NULL,103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("CreateControl",1333,(G__InterfaceMethod) NULL,103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("FillGeneral",1093,(G__InterfaceMethod) NULL,103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("FillControl",1128,(G__InterfaceMethod) NULL,103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Do",179,(G__InterfaceMethod) NULL,103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Checkbac_etotCut",1611,G__GBacDict_164_0_7, 103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ChecknbacmuCut",1408,G__GBacDict_164_0_8, 103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Getbac_etotCut",1421,G__GBacDict_164_0_9, 103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetnbacmuCut",1218,G__GBacDict_164_0_10, 103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Reset",515,(G__InterfaceMethod) NULL,103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetAllCuts",984,(G__InterfaceMethod) NULL,103, -1, G__defined_typename("Bool_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("PrintMessage",1234,(G__InterfaceMethod) NULL,117, G__get_linked_tagnum(&G__GBacDictLN_TString), -1, 0, 1, 1, 1, 0, "u 'TString' - 0 - option", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Print",525,(G__InterfaceMethod) NULL,103, -1, G__defined_typename("Bool_t"), 0, 1, 1, 1, 0, "u 'TString' - 0 - option", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Class",502,G__GBacDict_164_0_15, 85, G__get_linked_tagnum(&G__GBacDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&GBac::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__GBacDict_164_0_16, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GBac::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__GBacDict_164_0_17, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&GBac::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__GBacDict_164_0_18, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&GBac::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__GBacDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 2, 1, 1, 0, 
"u 'TMemberInspector' - 1 - insp C - - 0 - parent", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__GBacDict_164_0_22, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__GBacDict_164_0_23, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GBac::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__GBacDict_164_0_24, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GBac::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__GBacDict_164_0_25, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&GBac::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__GBacDict_164_0_26, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&GBac::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("GBac", 333, G__GBacDict_164_0_27, (int) ('i'), G__get_linked_tagnum(&G__GBacDictLN_GBac), -1, 0, 1, 1, 1, 0, "u 'GBac' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~GBac", 459, G__GBacDict_164_0_28, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__GBacDict_164_0_29, (int) ('u'), G__get_linked_tagnum(&G__GBacDictLN_GBac), -1, 1, 1, 1, 1, 0, "u 'GBac' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncGBacDict() {
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
extern "C" void G__cpp_setup_globalGBacDict() {
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

extern "C" void G__cpp_setup_funcGBacDict() {
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
G__linked_taginfo G__GBacDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__GBacDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__GBacDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__GBacDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__GBacDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__GBacDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__GBacDictLN_TString = { "TString" , 99 , -1 };
G__linked_taginfo G__GBacDictLN_TH1D = { "TH1D" , 99 , -1 };
G__linked_taginfo G__GBacDictLN_GPhysObj = { "GPhysObj" , 99 , -1 };
G__linked_taginfo G__GBacDictLN_GBac = { "GBac" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableGBacDict() {
  G__GBacDictLN_TClass.tagnum = -1 ;
  G__GBacDictLN_TBuffer.tagnum = -1 ;
  G__GBacDictLN_TMemberInspector.tagnum = -1 ;
  G__GBacDictLN_TObject.tagnum = -1 ;
  G__GBacDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__GBacDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__GBacDictLN_TString.tagnum = -1 ;
  G__GBacDictLN_TH1D.tagnum = -1 ;
  G__GBacDictLN_GPhysObj.tagnum = -1 ;
  G__GBacDictLN_GBac.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableGBacDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__GBacDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__GBacDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__GBacDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__GBacDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__GBacDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__GBacDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__GBacDictLN_TString);
   G__get_linked_tagnum_fwd(&G__GBacDictLN_TH1D);
   G__get_linked_tagnum_fwd(&G__GBacDictLN_GPhysObj);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__GBacDictLN_GBac),sizeof(GBac),-1,29952,"Bac class for everything which is related only to BAC",G__setup_memvarGBac,G__setup_memfuncGBac);
}
extern "C" void G__cpp_setupGBacDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupGBacDict()");
  G__set_cpp_environmentGBacDict();
  G__cpp_setup_tagtableGBacDict();

  G__cpp_setup_inheritanceGBacDict();

  G__cpp_setup_typetableGBacDict();

  G__cpp_setup_memvarGBacDict();

  G__cpp_setup_memfuncGBacDict();
  G__cpp_setup_globalGBacDict();
  G__cpp_setup_funcGBacDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncGBacDict();
  return;
}
class G__cpp_setup_initGBacDict {
  public:
    G__cpp_setup_initGBacDict() { G__add_setup_func("GBacDict",(G__incsetup)(&G__cpp_setupGBacDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initGBacDict() { G__remove_setup_func("GBacDict"); }
};
G__cpp_setup_initGBacDict G__cpp_setup_initializerGBacDict;

