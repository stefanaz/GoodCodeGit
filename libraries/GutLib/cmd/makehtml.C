//
// create html documentation for the GutLib shared library
//
// $Author: gutsche $
// $Date: 2005/02/07 13:15:51 $
// $Revision: 1.4 $
//

{
// Load shared library
//gROOT->LoadMacro("../lib/$(ZARCH_TYPE)/libGutLib.so");

// remove anoying entry
gClassTable->Remove("GCValues_t");
gClassTable->Remove("Grid_Result_t");

// Create HTML documentation
THtml *html = new THtml();
html->SetOutputDir("../htmldoc");
html->MakeAll(kFALSE, "G*");
}
