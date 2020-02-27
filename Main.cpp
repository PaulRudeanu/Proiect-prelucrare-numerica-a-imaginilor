//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "math.h"
#include "jpeg.hpp"     //pentru suport JPEG
#include <windows.h>    //pentru a obtine calea catre fisierul executabil
#include <shellapi.h>   //si a lansa o comanda
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMainForm *MainForm;

int S[8][8];      //matricea nivelelor de gri aferente unei portiuni de 8x8 pixeli din cadrul unei imagini
int T[8][8];      //matricea ce va contine rezultatul transformarii
double rez, INVERS_RAD_2 = 1/sqrt(2);    //variabila rezultat pentru o valoare din cadrul matricei de transformare; 1/radical(2)
int latime, inaltime, pozX, pozY;        //intaltimea si latimea imaginii, pozitia curenta a mouse-ului

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
        //la deschiderea aplicatiei, doar primul tab este vizibil, toate celelate vor fi ascunse
        TabDetaliu->TabVisible = false;
        TabTranslare->TabVisible = false;
        TabDCT->TabVisible = false;


}
//---------------------------------------------------------------------------  
void __fastcall TMainForm::MainMenuMainFormFisierIesireClick(
      TObject *Sender)
{
        //iesire din program
        MainForm->Close();        
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MainMenuMainFormAjutorDespreClick(
      TObject *Sender)
{
        //informatii versiune program, autor
        AnsiString info = " Transformata Cosinus Discreta, autor Rudeanu Paul, 3132A an III,Iunie 2017";
        MessageDlg(info, mtInformation, TMsgDlgButtons() << mbOK, 0);   //http://www.functionx.com/bcb/topics/msgbox.htm
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::ButtonIncarcaClick(TObject *Sender)
{
        //incarcare imagine
        IncarcaImagine();
        if (!Imagine->Picture->Bitmap->Empty)   //afisam rezolutia imaginii incarcate
        {
                LabelDimensiuni->Caption = "Dimensiuni imagine: " + AnsiString(Imagine->Picture->Bitmap->Width) + " x " + AnsiString(Imagine->Picture->Bitmap->Height) + " pixeli";
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IncarcaImagine()
{
        //Incarcarea unui fisier BMP sau JPG
        OpenDialogImagine->Filter = "Toate imaginile permise (*.bmp, *.jpg, *.jpe, *.jpeg)|*.bmp; *.jpg; *.jpe; *.jpeg|Imagini BMP (*.bmp)|*.BMP| JPEG images (*.jpg) | *.jpg; " ;
        if (OpenDialogImagine->Execute())
        {
            if (!FileExists(OpenDialogImagine->FileName))
                return; // make sure it exists, else get out.
            AnsiString temp2 = ExtractFileName(OpenDialogImagine->FileName);
            AnsiString temp = ExtractFileExt(OpenDialogImagine->FileName);
            AnsiString Ext = temp.LowerCase();

            if (Ext.AnsiPos("jpg") > 0 || Ext.AnsiPos("jpe") > 0 || Ext.AnsiPos("jpeg") > 0)  // it's a jpg
            {   //-- Decompress the jpeg image into a bitmap.
                TJPEGImage *myjpeg = new TJPEGImage();
                myjpeg->LoadFromFile(OpenDialogImagine->FileName);
                myjpeg->DIBNeeded();  // used when jpeg image needs bitmap rep
                Imagine->Picture->Bitmap->Assign(myjpeg);
                delete myjpeg;
            }
            else if (Ext.AnsiPos("bmp") > 0)
                Imagine->Picture->Bitmap->LoadFromFile(OpenDialogImagine->FileName);

            //crearea unui bitmap sursa temporar
            Graphics::TBitmap *source = new Graphics::TBitmap;
            source->Assign( Imagine->Picture->Bitmap );
            source->PixelFormat  =  Imagine->Picture->Bitmap->PixelFormat;

            //determina latimea si inaltimea imaginii incarcate
            latime = Imagine->Picture->Bitmap->Width;
            inaltime = Imagine->Picture->Bitmap->Height;

            ShapeDetaliu->Visible = true;

        }
}

//tabul 1



void __fastcall TMainForm::ImagineMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
        if (Imagine->Picture->Bitmap->Empty)
        {
                EditX->Text = "";
                EditY->Text = "";
        }
        //afisam coordonatele punctului
        else                                //dar numai daca a fost incarcata o imagine!
        {
                EditX->Text = X;
                EditY->Text = Y;

                pozX = X;
                pozY = Y;
		//ShowMessage(String(pozY) + " respectiv: " + String(pozX) + " latime: " + latime +" inaltime: " + inaltime);

                int margine = ShapeDetaliu->Width / 2;  //implicit, 4

		if (pozX < margine) pozX = margine;
		if (pozX > latime - margine) pozX = latime - margine;

		if (pozY < margine) pozY = margine;
		if (pozY > inaltime - margine) pozY = inaltime - margine;

                //afisam un patrat cu centrul in punctul curent
                ShapeDetaliu->Left = pozX - margine;	//centram patratul in jurul coordonatelor
                ShapeDetaliu->Top = pozY - margine;	//va functiona indiferent de dimensiunea patratului de selectie
        }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ShapeDetaliuMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        ShapeDetaliu->Visible=false;
        ImagineClick(Sender);
        ShapeDetaliu->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ImagineClick(TObject *Sender)
{
        //click pe imagine => preia matricea valorilor

        if (Imagine->Picture->Bitmap->Empty)
        {
                MessageDlg("Incarcati mai intai o imagine!", mtError, TMsgDlgButtons() << mbOK, 0);
                ButtonIncarca->SetFocus();
                return;
        }

        if (latime < 8 || inaltime < 8)
        {
                MessageDlg("Imaginea curenta are o rezolutie prea mica! Minimul acceptat este de 8x8 pixeli!", mtError, TMsgDlgButtons() << mbOK, 0);
                Imagine->Picture = NULL;
                LabelDimensiuni->Caption = "";
                return;
        }

        Graphics::TBitmap *culoriS = new Graphics::TBitmap;
        culoriS->Width = 8;
        culoriS->Height = 8;
        culoriS->PixelFormat = pf24bit;

        TColor culoareTemp;
        for (int i=0; i<8; i++)    //de la y-4 la y+3 inclusiv, pe linii
        {
                for (int j=0; j<8; j++) //de la x-4 la x+3 inclusiv, pe coloane acum
                {
                        culoareTemp = Imagine->Picture->Bitmap->Canvas->Pixels[pozY-4+i][pozX-4+j];
                        //ShowMessage(String(i+pozY-4) + " respectiv: " + String(j+pozX-4));  //coordonatele pixelilor ce vor fi preluati de pe imaginea initiala
                        S[i][j] = GetRValue(culoareTemp) + GetGValue(culoareTemp) + GetBValue(culoareTemp);
                        S[i][j] /= 3;   //salvare valori nivele de gri

                        //atentie la imaginile cu pierderi de calitate, precum JPEG
                        //cel mai simplu mod, dar care nu face conversia in gri
                        //culoriS->Canvas->Pixels[i][j] = Imagine->Picture->Bitmap->Canvas->Pixels[i+y-4][j+x-4];

                        //sau, in forma echivalenta, realizand si conversia in nivele de gri:
                        culoriS->Canvas->Pixels[i][j] = TColor(RGB(S[i][j], S[i][j], S[i][j]));
                }
        }

		
        //operatiuni din tabul 2 [detalii imagine]

        //facem zoom pentru a vedea detaliile zonei selectate de utilizator
        Graphics::TBitmap *detaliu = new Graphics::TBitmap;
        detaliu->Width = ImagineDetalii->Width;
        detaliu->Height = ImagineDetalii->Height;
        detaliu->PixelFormat = pf8bit;

        for (int i=0; i<detaliu->Height; i++)
        {
                for (int j=0; j<detaliu->Width; j++)
                {
                        detaliu->Canvas->Pixels[i][j] = culoriS->Canvas->Pixels[int(i*8/detaliu->Height)][int(j*8/detaliu->Width)];
                }
        }

        ImagineDetalii->Picture->Bitmap = detaliu;      //asignare imagine
        delete detaliu;         //si apoi
        delete culoriS;         //eliberare memorie

        for (int i=0; i<StringGridS->RowCount; i++)
        {
                for (int j=0; j<StringGridS->ColCount; j++)
                {
                        //populare StringGrid cu valorile de gri corespunzatoare culorilor din detaliu
                        StringGridS->Cells[i][j]=S[i][j];
                }
        }

             //alternare vizibilitate tab
        TabDetaliu->TabVisible = true;          //afisam tabul pentru detalii imagine
        PageControl1->ActivePageIndex = 1;      //si accesam acest tab

        TabTranslare->TabVisible = false;       //celelalte taburi vor fi ascunse momentan
        TabDCT->TabVisible = false;
}
//end of tab 1


//tabul 2
//---------------------------------------------------------------------------
void __fastcall TMainForm::ImagineDetaliiMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
        //selectia valorii din matrice corespunzatoare "pixelului" (mai exact detaliului unui pixel) curent din imagine
        TGridRect selectie;
        selectie.Left = X * 8 / ImagineDetalii->Width;
        selectie.Right =  X * 8 / ImagineDetalii->Width;
        selectie.Top = Y * 8 / ImagineDetalii->Height;
        selectie.Bottom = Y * 8 / ImagineDetalii->Height;
        StringGridS->Selection = selectie;
}
//---------------------------------------------------------------------------

//formatare + highlight valoare din matrice
void __fastcall TMainForm::StringGridSDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
        //formatare corespunzatoare
        AnsiString text;
        long int WidthOfText;
        long int WidthOfCell;
        long int LeftOffset;

        text = StringGridS->Cells[ACol][ARow];
        WidthOfText = Canvas->TextWidth(StringGridS->Cells[ACol][ARow]);
        WidthOfCell= StringGridS->ColWidths[ACol];
        LeftOffset = (WidthOfCell - WidthOfText) * 0.2;

        //colorarea zonei selectate
        if (State.Contains(gdSelected))
        {
                StringGridS->Canvas->Brush->Color = clHighlight;
                StringGridS->Canvas->Font->Color = clHighlightText;
                StringGridS->Canvas->FillRect(Rect);
        }

        StringGridS->Canvas->TextRect(Rect,Rect.Left+LeftOffset,Rect.Top+15,text);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonTranslareClick(TObject *Sender)
{
        //translarea matricei S din intervalul [0, 255] in [-128, 127]
        //pentru a creste precizia calculului

        //mai intai populam primul StringGrid de pe tab-ul 3
        for (int i=0; i<StringGridT1->RowCount; i++)
        {
                for (int j=0; j<StringGridT1->ColCount; j++)
                {
                        //populare StringGrid cu valorile de gri corespunzatoare culorilor din detaliu
                        StringGridT1->Cells[i][j]=S[i][j];
                }
        }

        //apoi translatam matricea S, scazand 128 din valoarea fiecarui element:
        for (int i=0; i<8; i++)
        {
                for (int j=0; j<8; j++)
                {
                        S[i][j] -= 128;
                }
        }

        //populam al doilea StringGrid din tabul 3 cu rezultatul
        for (int i=0; i<StringGridT2->RowCount; i++)
        {
                for (int j=0; j<StringGridT2->ColCount; j++)
                {
                        //populare StringGrid cu valorile de gri corespunzatoare culorilor din detaliu
                        StringGridT2->Cells[i][j]=S[i][j];
                }
        }
        TabTranslare->TabVisible = true;          //afisam tabul pentru translare
        PageControl1->ActivePageIndex = 2;      //si accesam acest tab
        
        TabDCT->TabVisible = false;             //ultimul tab ramane ascuns
}
//---------------------------------------------------------------------------
//end of tab2

//tabul 3


//selectie valoare din tab 3 - stringgrid 1
void __fastcall TMainForm::StringGridT1SelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{

        TGridRect selectie;
        selectie.Left = ACol;
        selectie.Right = ACol;
        selectie.Top = ARow;
        selectie.Bottom = ARow;
        StringGridT2->Selection = selectie;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StringGridT1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
        //formatare corespunzatoare
        AnsiString text;
        long int WidthOfText;
        long int WidthOfCell;
        long int LeftOffset;

        text = StringGridT1->Cells[ACol][ARow];
        WidthOfText = Canvas->TextWidth(StringGridT1->Cells[ACol][ARow]);
        WidthOfCell= StringGridT1->ColWidths[ACol];
        LeftOffset = (WidthOfCell - WidthOfText) * 0.2;

        //colorarea zonei selectate
        if (State.Contains(gdSelected))
        {
                StringGridT1->Canvas->Brush->Color = clHighlight;
                StringGridT1->Canvas->Font->Color = clHighlightText;
                StringGridT1->Canvas->FillRect(Rect);
        }

        StringGridT1->Canvas->TextRect(Rect,Rect.Left+LeftOffset,Rect.Top+15,text);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StringGridT2DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
        //formatare corespunzatoare
        AnsiString text;
        long int WidthOfText;
        long int WidthOfCell;
        long int LeftOffset;

        text = StringGridT2->Cells[ACol][ARow];
        WidthOfText = Canvas->TextWidth(StringGridT2->Cells[ACol][ARow]);
        WidthOfCell= StringGridT2->ColWidths[ACol];
        LeftOffset = (WidthOfCell - WidthOfText) * 0.3;

        //colorarea zonei selectate
        if (State.Contains(gdSelected))
        {
                StringGridT2->Canvas->Brush->Color = clHighlight;
                StringGridT2->Canvas->Font->Color = clHighlightText;
                StringGridT2->Canvas->FillRect(Rect);
        }

        StringGridT2->Canvas->TextRect(Rect,Rect.Left+LeftOffset,Rect.Top+15,text);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ButtonDCTClick(TObject *Sender)
{
        //mai intai populam primul StringGrid de pe tab-ul 4
        for (int i=0; i<StringGridD1->RowCount; i++)
        {
                for (int j=0; j<StringGridD1->ColCount; j++)
                {
                        //populare StringGrid cu valorile de gri corespunzatoare culorilor din detaliu
                        StringGridD1->Cells[i][j]=S[i][j];
                }
        }

        //transformarea cosinus discreta
        for (int y = 0; y < 8; y++)
        {
                for (int x = 0; x < 8; x++)
                {
                        rez = 0; // resetam rezultatul la 0 inainte de a calcula valorile din matricea DCT

                        double Cx = 1;
                        double Cy = 1;

                        if (x == 0) Cx = INVERS_RAD_2;
                        if (y == 0) Cy = INVERS_RAD_2;

                        for (int i = 0; i < 8; i++)
                        {
                                for (int j = 0; j < 8; j++)
                                {
                                        rez += S[i][j] * cos((2*j+1)*x*M_PI/16) * cos((2*i+1)*y*M_PI/16);
                                }
                        }

                        T[y][x] = Cx * Cy * rez * 0.25; //salvam valorile rezultate in matricea DCT
                }
        }

        //populam al doilea StringGrid din tabul 4 cu rezultatul
        for (int i=0; i<StringGridD2->RowCount; i++)
        {
                for (int j=0; j<StringGridD2->ColCount; j++)
                {
                        //populare StringGrid cu valorile de gri corespunzatoare culorilor din detaliu
                        StringGridD2->Cells[i][j]=T[i][j];
                }
        }

        //in final
        TabDCT->TabVisible = true;          //afisam tabul pentru translare
        PageControl1->ActivePageIndex = 3;      //si accesam acest tab
}
//---------------------------------------------------------------------------
//end of tab 3

//tabul 4



void __fastcall TMainForm::StringGridD1SelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
        TGridRect selectie;
        selectie.Left = ACol;
        selectie.Right = ACol;
        selectie.Top = ARow;
        selectie.Bottom = ARow;
        StringGridD2->Selection = selectie;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::StringGridD1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
        //formatare corespunzatoare
        AnsiString text;
        long int WidthOfText;
        long int WidthOfCell;
        long int LeftOffset;

        text = StringGridD1->Cells[ACol][ARow];
        WidthOfText = Canvas->TextWidth(StringGridD1->Cells[ACol][ARow]);
        WidthOfCell= StringGridD1->ColWidths[ACol];
        LeftOffset = (WidthOfCell - WidthOfText) * 0.2;

        //colorarea zonei selectate
        if (State.Contains(gdSelected))
        {
                StringGridD1->Canvas->Brush->Color = clHighlight;
                StringGridD1->Canvas->Font->Color = clHighlightText;
                StringGridD1->Canvas->FillRect(Rect);
        }

        StringGridD1->Canvas->TextRect(Rect,Rect.Left+LeftOffset,Rect.Top+15,text);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StringGridD2DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
        //formatare corespunzatoare
        AnsiString text;
        long int WidthOfText;
        long int WidthOfCell;
        long int LeftOffset;

        text = StringGridD2->Cells[ACol][ARow];

        //colorarea zonei selectate
        if (State.Contains(gdSelected))
        {
                StringGridD2->Canvas->Brush->Color = clHighlight;
                StringGridD2->Canvas->Font->Color = clHighlightText;
                StringGridD2->Canvas->FillRect(Rect);
        }

        StringGridD2->Canvas->TextRect(Rect,Rect.Left,Rect.Top+15,text);
}
//---------------------------------------------------------------------------






