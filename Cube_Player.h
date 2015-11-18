#include <iostream>
#include <utility>
#include <RQ_OBJECT.h>
#include "TH2.h"
#include "TString.h"
#include "TNamed.h"
#include "TObject.h"
#ifndef Cube_Player_H
#define Cube_Player_H



namespace Gw {

    class Cube_Player : public TNamed
    {
        RQ_OBJECT("Cube_Player")

    private:
        Int_t fLastX, fLastY;
        Int_t x;Int_t y;
        Int_t fLastMouseX;              // last x mouse position
        Int_t fLastMouseY;              // last y mouse position

    protected:

        void Draw_Rect_AND_Name_Z(Bool_t Mode=false);
        void Draw_Rect_AND_Name_A(Bool_t Mode=false);

    public:

        Cube_Player(const char* name, const char *title);
        virtual ~Cube_Player();

        TString ReturnZWithALatex(Int_t Zz,Int_t Aa);

        void Plot_Current_Spectra(Int_t z,Int_t a,const char *OPTION="N",const char * OPTION2="N",Float_t StrengthMin=0);

        void SetCanvas();

        void Redraw();

        void Display_All_Nuclei();

        void XEventAction(Int_t event, Int_t px, Int_t py, TObject *obj);

        static Bool_t OpenContextMenu(const char* method, TObject* obj, const char* alt_method_name = "");

        void DrawSpectra(const char * Nuclei_Name="100Zr",const char * Option="N",const char *OPTION2="N",Float_t StrengthMin=0);

        void Draw_Serie_Isotopique(Int_t z,Int_t AMin,Int_t AMax);

        Bool_t IsLsDraw(const char * Option="N");

        Bool_t IsVMode(const char * Option="N");

        signed short int IsZMode(const char * OPTION2="N");

        void Draw_Arrow(Float_t Scale,Float_t Max_Position,Float_t Energy,Int_t Color);

        ClassDef(Cube_Player,1)

            };

}//namespace

#endif
