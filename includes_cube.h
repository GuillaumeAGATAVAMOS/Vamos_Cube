#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>



#include "TFile.h"
#include "TCanvas.h"
#include "TObject.h"
#include "TSystem.h"
#include "TH2F.h"
#include "TLatex.h"
#include "TContextMenu.h"
#include "TColor.h"
#include "TLegend.h"

#include "Cube_Player.h"
#include "ENSDF_DATAe680.h"

using namespace std;
using namespace Gw;

Int_t Z_Offset=29;
Int_t A_Offset=79;


Cube_Player *Cube;

ENSDF_DATAe680 *DATABASE;

TFile *fInputChart;

TFile *fOutputSpectra;

Int_t Maximum_Gamma_Read =300;

TH2F *Chart_Bidim=0x0;
TH1F *Current_Spectra=0x0;

TCanvas *C_Chart=0x0;

TLatex Tl;

Color_t Gamma_Arrow_Color[3]={kRed,kGreen,kBlue};

TString Raw_Directory="/agataDAS1/AGATA/Experiments/e680/Analysis/Users/Gui/Level_Scheme/Import_ENSDF/Zr100.ags";

Color_t Color[27]={1,2,3,4,5,6,7,8,9,kOrange+10,kRed+2,kPink+10,kMagenta-4,kViolet+6,kAzure+10,kCyan+3,kGreen,kYellow,kOrange+8,kRed+4,kPink+8,kMagenta-2,kViolet+8,kAzure+8,kCyan+1,kGreen+2,kYellow+2};

TString Name ="Canvas_1";

TString FileName = Form("GlobalPlots_CorrXYProj_OnlyZCuts_NoReb_ERes_inf_0.01.root");

TString Z[20]={"Cu","Zn","Ga","Ge","As","Se","Br","Kr","Rb","Sr","Y","Zr","Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd"};
TString ZMAJ[20]={"CU","ZN","GA","GE","AS","SE","BR","KR","RB","SR","Y","ZR","NB","MO","TC","RU","RH","PD","AG","CD"};


void ErrorMessage(const char *err)
{
    cout<<"\e[1;91m"<<err<<"\e[0m"<<endl;
}

void InfoMessage(const char *info)
{
    cout<<"\e[1;92m"<<info<<"\e[0m"<<endl;
}

void WarningMessage(const char *warn)
{
    cout<<"\e[1;93m"<<warn<<"\e[0m"<<endl;
}
