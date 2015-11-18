#include "includes_cube.h"

#include "KeySymbols.h"

#ifndef ROOT_TStyle
#include "TStyle.h"
#endif

#ifndef ROOT_TCanvas
#include "TCanvas.h"
#endif

#ifndef ROOT_TSpectrum
#include "TSpectrum.h"
#endif

#ifndef ROOT_TFrame
#include "TFrame.h"
#endif

#ifndef ROOT_TROOT
#include "TROOT.h"
#endif

#if ROOT_VERSION_CODE >= ROOT_VERSION(5,15,0)
#include "TMath.h"
#endif

#ifndef Cube_Player_H
#include "Cube_Player.h"
#endif

#include "ENSDF_DATAe680.h"

#include "TContextMenu.h"
#include "TArrow.h"

using namespace std;
using namespace Gw;

Cube_Player::Cube_Player(const char* name, const char *title) :
        TNamed(name,title)
{
}


Cube_Player::~Cube_Player()
{
C_Chart->Disconnect();
C_Chart->DisconnectWidget();
delete Current_Spectra;
}


void Cube_Player::SetCanvas()
{
    // to connect the current canvas
    TVirtualPad *pad = TVirtualPad::Pad(); TCanvas *c = NULL;

    if ( pad ) {
        c = pad->GetCanvas();
    }

    c->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)",
               "Gw::Cube_Player",this,"XEventAction(Int_t,Int_t,Int_t,TObject*)");

    cout<<endl;InfoMessage("Canvas is connected; you can select nuclei and see gamma spectra");cout<<endl;
    InfoMessage("Type 'r' to begin moving on the chart");cout<<endl;
    InfoMessage("Type 'h' to display help");cout<<endl;
}

void Cube_Player::XEventAction(Int_t event, Int_t px, Int_t py, TObject */*sel*/)
{
    // Do action depending on X actions

    TVirtualPad *pad = gROOT->GetSelectedPad(); if ( pad == NULL ) return;



    bool CTRL ;
    if(px==0 && py==4129){CTRL=true;}else{CTRL=false;}


    bool LastCTRL ;
    if(fLastX==0 && fLastY==4129){LastCTRL=true;}else{LastCTRL=false;}

    EKeySym Key = (EKeySym)py;

    switch (event) {
    case kMouseMotion:
        // to keep track of the last mouse position
        fLastX = px; fLastY = py;
        break;



    case kKeyPress:
        {


            Int_t key = px, keysym = py;
            switch ((EKeySym)keysym) {
            case kKey_Left:
                cout<<"left arrow"<<endl;
                break;
            case kKey_Right:
                cout<<"rightarrow"<<endl;
                break;
            case kKey_Down:
                cout<<"down arrow"<<endl;
                break;
            case kKey_h:
                cout<<endl;
                InfoMessage("HELP : Keys used to interact with nucleide chart:");cout<<endl;
                InfoMessage("      h->Show Help");cout<<endl;
                InfoMessage("      r->Reset coordinates of the chart");cout<<endl;
                InfoMessage("      z->Increase by one proton");cout<<endl;
                InfoMessage("      s->Decrease by one proton");cout<<endl;
                InfoMessage("      d->Increase by one neutron");cout<<endl;
                InfoMessage("      q->Increase by one neutron");cout<<endl;
                InfoMessage("      Pave_Num_Enter->Show Spectrum of the selected nucleus");cout<<endl;
                InfoMessage("      Ctrl+a -> Draw All Nuclei");cout<<endl;
                InfoMessage("      Ctrl+r -> Reset Drawing");cout<<endl;
                InfoMessage("      Ctrl+d -> Draw Spectrum of one Nuclei ex: 100Zr. Option : L(Draw LS), V(Verbose Mode) ");cout<<endl;
                InfoMessage("                OPTION2 : Z+1;Z-1;Z+- -> Draw Energies of the Z+(-)(+and-) Nuclei");cout<<endl;
                InfoMessage("                StrengthMin : Display only intensities above this limit");cout<<endl;
                InfoMessage("      Ctrl+i -> Draw Spectra of an isotopic set between Amin and Amax");cout<<endl;
                InfoMessage("      Ctrl+x -> Exit");cout<<endl;
                break;
            case kKey_Up:
                cout<<"up arrow"<<endl;
                break;
            case kKey_z:
                Draw_Rect_AND_Name_Z(false);
                break;
            case kKey_d:
                Draw_Rect_AND_Name_A(false);
                break;
            case kKey_s:
                Draw_Rect_AND_Name_Z(true);
                break;
            case kKey_q:
                Draw_Rect_AND_Name_A(true);
                break;
            case kKey_r:
                x=0;y=0;
                break;
            case   kKey_Enter://faire entrée normal
                Plot_Current_Spectra(x,y,0);
                break;

            default :
                    break;
        }
            break;

        }//end kKeyPress

        fLastX = px;
        fLastY = py;

    }//End Switch


    if   (Key == kKey_r  && CTRL==false && LastCTRL==true)//CTRL+r
    {
        Redraw();gPad->Modified();gPad->Update();
    }

    if   (Key == kKey_a && !CTRL && LastCTRL )//CTRL+a
    {
        Display_All_Nuclei();gPad->Modified();gPad->Update();
    }

    if   (Key == kKey_d && !CTRL && LastCTRL )//CTRL+d
    {
        OpenContextMenu("DrawSpectra",this);
    }
    if   (Key == kKey_x && !CTRL && LastCTRL )//CTRL+x
    {
        delete Cube;
        C_Chart->Close();
    }
    if   (Key == kKey_i && !CTRL && LastCTRL )//CTRL+i
    {
        OpenContextMenu("Draw_Serie_Isotopique",this);
    }

    fLastX = px;
    fLastY = py;
    //cout<<"fLastX "<<fLastX<<"fLastY "<<fLastY<<endl;

}


void Cube_Player::Draw_Rect_AND_Name_Z(Bool_t Mode)

{


    TVirtualPad *pad = gROOT->GetSelectedPad(); if ( pad == NULL ) return;

    pad->cd();

    /*TLatex Tl;*/Tl.SetTextFont(43); Tl.SetTextSize(13);


                  if(Mode==false){x+=1;}else{x-=1;}


                  switch (x) {

                  case 0:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                  case 1:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                  case 2:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                  case 3:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                  case 4:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                  case 5:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                  case 6:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                  case 7:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                  case 8:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                  case 9:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                  case 10:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                  case 11:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                  case 12:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                  case 13:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                  case 14:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                  case 15:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                  case 16:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                  case 17:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                  case 18:
                      Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;


                  }

                  gPad->Modified();gPad->Update();

              }

void Cube_Player::Draw_Rect_AND_Name_A(Bool_t Mode)

{


    TVirtualPad *pad = gROOT->GetSelectedPad(); if ( pad == NULL ) return;

    pad->cd();

    /*TLatex Tl*/;Tl.SetTextFont(43); Tl.SetTextSize(13);

                 if(Mode==false){y+=1;}else{y-=1;}

                 switch (x) {

                 case 0:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                 case 1:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                 case 2:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                 case 3:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                 case 4:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                 case 5:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                 case 6:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                 case 7:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                 case 8:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                 case 9:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                 case 10:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                 case 11:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                 case 12:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                 case 13:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                 case 14:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                 case 15:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                 case 16:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                 case 17:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;
                 case 18:
                     Tl.DrawLatex(A_Offset+y,Z_Offset+x,ReturnZWithALatex(x,A_Offset+y));   break;

                 }

                 gPad->Modified();gPad->Update();

             }

TString Cube_Player::ReturnZWithALatex(Int_t Zz,Int_t Aa)

{
    TString ZWithA="#font[22]{^{";
    ZWithA+=Aa;
    ZWithA+="}";
    ZWithA+=Z[Zz];
    ZWithA+="}";

    return ZWithA;
}

void Cube_Player::Plot_Current_Spectra(Int_t z,Int_t a,const char *OPTION,const char* OPTION2,Float_t StrengthMin)
{

  cout<<"yoooooo"<<endl;
    Float_t *E =new Float_t[Maximum_Gamma_Read];
    Float_t *EZmoin =new Float_t[Maximum_Gamma_Read];
    Float_t *EZplus =new Float_t[Maximum_Gamma_Read];

    E=DATABASE->Import_E(z,a,Cube->IsLsDraw(OPTION),Cube->IsVMode(OPTION),StrengthMin);
    Float_t Max_Position=0,Max_PositionZplus=0,Max_PositionZmoin=0;

    switch(Cube->IsZMode(OPTION2))
    {
    case -1:
        EZmoin=DATABASE->Import_E(z-1,a,Cube->IsLsDraw(OPTION),Cube->IsVMode(OPTION),StrengthMin);
        break;
    case 1:
        EZplus =DATABASE->Import_E(z+1,a,Cube->IsLsDraw(OPTION),Cube->IsVMode(OPTION),StrengthMin);
        break;
    case 2:
        EZmoin =DATABASE->Import_E(z-1,a,Cube->IsLsDraw(OPTION),Cube->IsVMode(OPTION),StrengthMin);
        EZplus =DATABASE->Import_E(z+1,a,Cube->IsLsDraw(OPTION),Cube->IsVMode(OPTION),StrengthMin);
        break;

    }//end Switch

    if(!gSystem->IsFileInIncludePath(FileName))
    {


        ErrorMessage("*************************************");
        ErrorMessage("***Spectra are not in include PATH***");
        ErrorMessage("*************************************");

    }else
    {
        fOutputSpectra=TFile::Open(FileName);

        TList *list = (TList*)fOutputSpectra->Get("ListOfHists");

        TString FolderName ="All_ICE/GammaSpectra/";
        TList *list2 = (TList*)list->FindObject("All_ICE");
        TList *list3 = (TList*)list2->FindObject("GammaSpectra");
        TList *list4 = (TList*)list3->FindObject( Form("Z%d",Z_Offset+z));

        TString SpecName="Z";SpecName+=Z_Offset+z;SpecName+="_A";SpecName+=a+A_Offset;

        Current_Spectra = (TH1F*)list4->FindObject(SpecName);
        Float_t Scale=Current_Spectra->GetMaximum();

        if(Current_Spectra!=0x0)
        {
           // cout<<SpecName<<endl;

            new TCanvas();

            Current_Spectra->Draw();
            Current_Spectra->SetTitle(ReturnZWithALatex(z,a+A_Offset));
            Current_Spectra->GetXaxis()->SetTitle("Energy");
            Current_Spectra->GetYaxis()->SetTitle("Counts");

            for(Int_t k=0;k<Maximum_Gamma_Read;k++)
            {
                if(E[k]<1)break;
                Max_Position=0;Max_PositionZplus=0;Max_PositionZmoin=0;

                for(Int_t j=0;j<6;j++)
                {

                    float Position = Current_Spectra->GetBinContent((Int_t)E[k]-3+j);
                    float PositionZplus = Current_Spectra->GetBinContent((Int_t)E[k]-3+j);//to change by EZplus
                    float PositionZmoin = Current_Spectra->GetBinContent((Int_t)E[k]-3+j);//to change by EZmoin
                    if(Position>=Max_Position){Max_Position=Position;}
                    if(PositionZplus>=Max_PositionZplus){Max_PositionZplus=PositionZplus;}
                    if(PositionZmoin>=Max_PositionZmoin){Max_PositionZmoin=PositionZmoin;}

                }

                Cube->Draw_Arrow(Scale,Max_Position,E[k],0);

                //Boucle sur les nouvelles é,ergie ? y reflechir de maniere que ce soit facile a manier

                if(Cube->IsZMode(OPTION2)==1)
                {
                Cube->Draw_Arrow(Scale,Max_PositionZplus,E[k],1);//To Change E
                }
                if(Cube->IsZMode(OPTION2)==-1)
                {
                Cube->Draw_Arrow(Scale,Max_PositionZmoin,E[k],2);//To Change E
                }
                if(Cube->IsZMode(OPTION2)==2)
                {
                Cube->Draw_Arrow(Scale,Max_PositionZplus,E[k],1);//To Change E
                Cube->Draw_Arrow(Scale,Max_PositionZmoin,E[k],2);//To Change E
                }

            }


        }
        else
        {
            cout<<endl;ErrorMessage("**************************************");
            ErrorMessage("**NOT ENOUGH STAT FOR THIS NUCLEUS***");
            ErrorMessage("**************************************");cout<<endl;
        }



    }

}

void Cube_Player::Redraw()
{
    Chart_Bidim->Draw("colz");
    cout<<endl; InfoMessage(" Redrawing CHART ");cout<<endl;
}

void Cube_Player::Display_All_Nuclei()
{
    Tl.SetTextFont(43); Tl.SetTextSize(13);

    for(Int_t i=0;i<=18;i++)
    {
        for(Int_t j=-5;j<=36;j++)
        {
            if((Z_Offset+i)<=(0.4*(A_Offset+j)+4) && (i+Z_Offset)>=(0.4*(A_Offset+j)-3))Tl.DrawLatex(A_Offset+j,Z_Offset+i,ReturnZWithALatex(i,A_Offset+j));

        }
    }

}

Bool_t Cube_Player::OpenContextMenu(const char* method, TObject* obj, const char *alt_method_name)
{
    // Open context menu for given method of object *obj.
    // By default title of menu is 'obj->ClassName()::method'
    // You can give an alternative method name in 'alt_method_name'
    // Returns kFALSE if the given method is not defined for the class of object in question.
    //
    // WARNING: even if this method returns kTRUE, this is no guarantee that the method
    // has indeed been executed. The user may have pressed the 'Cancel' button...

    TMethod* m = obj->IsA()->GetMethodAllAny(method);
    if(!m)
    {
        obj->Warning("OpenContextMenu","%s is not a method of %s",method,obj->ClassName());
        return kFALSE;
    }
    TString Method=alt_method_name;
    if(Method=="") Method=method;
    TContextMenu * cm = new TContextMenu(Method, Form("%s::%s",obj->ClassName(),Method.Data()));
    cm->Action(obj,m);
    delete cm;
    return kTRUE;
}


void Cube_Player::DrawSpectra(const char * Nuclei_Name,const char* Option,const char * OPTION2,Float_t StrengthMin)
{

    InfoMessage(Nuclei_Name);
    Int_t Zz=0;
    TString B=Nuclei_Name;
    TString A=(B(0,2));
    TString Rest =B(2,2);

    if(A(0,1)=="1"){ A=(B(0,3));Rest =B(3,2);}

    Int_t NNucleiToRead = sizeof(Z)/sizeof(TString);

    for(Int_t i=0;i<=NNucleiToRead;i++)
    {
        if(Z[i]==Rest)break;
        Zz=i;
    }
    Zz+=1;
    Int_t AInt=A.Atoi();
    cout<<"Stregth "<<StrengthMin<<endl;

    Plot_Current_Spectra(Zz,AInt-A_Offset,Option,OPTION2,StrengthMin);

}


void Cube_Player::Draw_Serie_Isotopique(Int_t z,Int_t AMin,Int_t AMax)
{

    Float_t tMax=0,Old_tMax=0;
    Int_t Aref=0;
    Int_t Counter=0;
    TLegend *leg = new TLegend(0.8,0.5,0.9,0.9);
    TString Leg_Name="Isotopes ";Leg_Name+=Z[z-Z_Offset];
    leg->SetHeader(Leg_Name);

    if(!gSystem->IsFileInIncludePath(FileName))
    {


        ErrorMessage("*************************************");
        ErrorMessage("***Spectra are not in include PATH***");
        ErrorMessage("*************************************");

    }else
    {
        new TCanvas();
        fOutputSpectra=TFile::Open(FileName);

        TList *list = (TList*)fOutputSpectra->Get("ListOfHists");

        TString FolderName ="All_ICE/GammaSpectra/";
        TList *list2 = (TList*)list->FindObject("All_ICE");
        TList *list3 = (TList*)list2->FindObject("GammaSpectra");
        TList *list4 = (TList*)list3->FindObject( Form("Z%d",z));


        for(Int_t i=AMin;i<=AMax;i++)
        {

            TString SpecName="Z";SpecName+=z;SpecName+="_A";SpecName+=i;

            Current_Spectra = (TH1F*)list4->FindObject(SpecName);

            if(Current_Spectra!=0x0)
            {
                Current_Spectra->SetLineColor(Color[i-AMin]);


                tMax=Current_Spectra->GetMaximum();
                if(tMax>=Old_tMax){Old_tMax=tMax;Aref=(Int_t)i;}
               // cout<<"Old_tMax"<<Old_tMax<<endl;
            }
        }

        for(Int_t i=AMin-1;i<=AMax;i++)
        {

            if(i==Aref)continue;

            TString SpecName="Z";SpecName+=z;SpecName+="_A";SpecName+=i;

            TString SpecNameFirst="Z";SpecNameFirst+=z;SpecNameFirst+="_A";SpecNameFirst+=Aref;

            if(Counter==0)
            {
                Current_Spectra = (TH1F*)list4->FindObject(SpecNameFirst);
                Current_Spectra->SetLineColor(kBlack);Current_Spectra->SetTitle(Leg_Name);
            }else
            {

                Current_Spectra = (TH1F*)list4->FindObject(SpecName);
                if(Current_Spectra!=0x0){Current_Spectra->SetLineColor(Color[i-AMin]);Current_Spectra->SetTitle(Leg_Name);}
            }

            gStyle->SetOptStat(0);


            if(Current_Spectra!=0x0)
            {

                if(Counter==0)
                {
                    Current_Spectra->Draw();leg->AddEntry(Current_Spectra,ReturnZWithALatex(z-Z_Offset,Aref),"l");
                    Current_Spectra->GetXaxis()->SetTitle("Energy");
                    Current_Spectra->GetYaxis()->SetTitle("Counts");
                }else
                {
                    Current_Spectra->Draw("SAME");
                    leg->AddEntry(Current_Spectra,ReturnZWithALatex(z-Z_Offset,i),"l");
                    Current_Spectra->GetXaxis()->SetTitle("Energy");
                    Current_Spectra->GetYaxis()->SetTitle("Counts");
                }

            }
            else
            {


                cout<<endl;ErrorMessage("**************************************");
                ErrorMessage("***NOT ENOUGH STAT FOR THIS NUCLEUS***");
                ErrorMessage("**************************************");cout<<endl;
            }
            cout<<"Nucleus : "<<i<<endl;
            if(i>=120)break;
            leg->Draw("SAME");
            Counter++;

        }


        Counter=0;
    }

}

Bool_t Cube_Player::IsLsDraw(const char *Option)
{

    TString Possibilities[8]={"l","L","lV","LV","Lv","Vl","VL","vL"};
    TString A=Option;

    for(Int_t i=0;i<(Int_t)(sizeof(Possibilities)/sizeof(TString));i++)
    {

        if(Option==Possibilities[i]|| A(0,1)==Possibilities[i] ||A(1,1)==Possibilities[i]){return 1;}

    }

}
Bool_t Cube_Player::IsVMode(const char *Option)
{

    TString Possibilities[8]={"v","V","lV","LV","Lv","Vl","VL","vL"};
    TString A=Option;

    for(Int_t i=0;i<(Int_t)(sizeof(Possibilities)/sizeof(TString));i++)
    {

        if(Option==Possibilities[i] || A(0,1)==Possibilities[i] || A(1,1)==Possibilities[i] ){return 1;}

    }
}

signed short int Cube_Player::IsZMode(const char *Option)
{

    TString Possibilities[12]={"Z+1","z+1","Z+","z+","Z-1","z-1","Z-","z-","z+-","Z+-","Z-+","z-+"};
    signed short int Resultat =0;
        if(Option==Possibilities[0]||Option==Possibilities[1]||Option==Possibilities[2]||Option==Possibilities[3])Resultat=1;
        if(Option==Possibilities[4]||Option==Possibilities[5]||Option==Possibilities[6]||Option==Possibilities[7])Resultat= -1;
        if(Option==Possibilities[8]||Option==Possibilities[9]||Option==Possibilities[10]||Option==Possibilities[11])Resultat= 2;

        return Resultat;

}

signed short int Cube_Player::IsAMode(const char *Option)
{

    TString Possibilities[12]={"A+1","a+1","A+","a+","A-1","a-1","A-","A-","A+-","a+-","A-+","a-+"};
    signed short int Resultat =0;
        if(Option==Possibilities[0]||Option==Possibilities[1]||Option==Possibilities[2]||Option==Possibilities[3])Resultat=1;
        if(Option==Possibilities[4]||Option==Possibilities[5]||Option==Possibilities[6]||Option==Possibilities[7])Resultat= -1;
        if(Option==Possibilities[8]||Option==Possibilities[9]||Option==Possibilities[10]||Option==Possibilities[11])Resultat= 2;

        return Resultat;

}



void Cube_Player::Draw_Arrow(Float_t Scale,Float_t Max_Position,Float_t Energy,Int_t Color)
{

    TArrow *Gamma_Arrow = new TArrow(Energy,(Max_Position + Scale/100.) ,Energy,(Max_Position +Scale/10.),0.005,"<|");
    Gamma_Arrow->SetAngle(40);
    Gamma_Arrow->SetLineColor(Gamma_Arrow_Color[Color]);
    Gamma_Arrow->SetFillColor(Gamma_Arrow_Color[Color]);
    Gamma_Arrow->SetLineWidth(1);
    Gamma_Arrow->Draw();

    TLatex Tl;
    TString Energy_Name=Form("%0.1f",Energy);
    //Par défaut la couleur rouge est le noyau sélectionné
    //couleur 1 a Z+1
    //Couleur 2 à Z-1
    switch(Color)
    {
    case 1:
        Energy_Name+=" Z+";break;
    case 2:
        Energy_Name+=" Z-";break;
    }
    Tl.SetTextAngle(90);
    Tl.SetTextSize(0.012);
    Tl.SetTextColor(Gamma_Arrow_Color[Color]);
    Tl.DrawLatex(Energy,(Max_Position +1.2*Scale/10.),Energy_Name);

}

ClassImp(Cube_Player);
