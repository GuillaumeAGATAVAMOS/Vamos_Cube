{ 
	/*	
	 
	 Usage:
	 root LoadILL.C
	 
	 O. Stézowski
	 */
	
	// ---> GammaWare PART /////////////////////////
	
	//printf("******************************************************************** \n") ;
	//printf("                    Messages from LoadGw.C \n") ;
	//printf("******************************************************************** \n") ;
	
	// to add to ROOT the Gw path to look for macros
	TString tmp, macroPATH; const Char_t *CompOpt = "";
	
	macroPATH = gROOT->GetMacroPath(); tmp = Gw::Env::GetPath("MacrosPath"); 
	if ( macroPATH.Contains(tmp.Data()) == false ) { 
		printf("- Add %s to the macros path \n",tmp.Data());
		tmp += ":";
		macroPATH.Prepend(tmp.Data()); gROOT->SetMacroPath(macroPATH.Data());
	} 
	
	// add GammaWare include path to ROOT for compilation
	tmp = Gw::Env::GetPath("IncludePath");  printf("- Add %s to the include path \n",tmp.Data());
	tmp.Prepend(" .include "); 
	gROOT->ProcessLine(tmp.Data());
	
	// load the different Gw libraries needed
	gSystem->Load("libGWCORE.so");
	gSystem->Load("libGWPHYSICS.so");
	gSystem->Load("libEve.so");
	gSystem->Load("libGWTOOLS.so");
	gSystem->Load("libGWADF.so");
	gSystem->Load("libGWADFE.so");
	//gSystem->Load("libGWILL.so");
	
	tmp = "./" ;  printf("- Add %s to the include path \n",tmp.Data());
	tmp.Prepend(" .include ");  
	gROOT->ProcessLine(tmp.Data());
	
	// start a ROOT TBrowser
//    TBrowser *browser = new TBrowser();
    
    gROOT->GetRootFolder()->AddFolder("Tools","Tools");
    TFolder *f = (TFolder*)gROOT->GetRootFolder()->FindObject("Tools");
    Gw::GSPlayerTUI *SpectrumPlayer = new Gw::GSPlayerTUI("SpectrumPlayer","SpectrumPlayer");
    f->Add(SpectrumPlayer);
    browser->Add(f);
	
}
