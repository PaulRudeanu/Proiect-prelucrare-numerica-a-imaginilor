//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <jpeg.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialogImagine;
        TPageControl *PageControl1;
        TTabSheet *TabAlegere;
        TTabSheet *TabDetaliu;
        TScrollBox *ScrollBoxImagine;
        TImage *Imagine;
        TEdit *EditX;
        TEdit *EditY;
        TButton *ButtonIncarca;
        TLabel *LabelCoordonate;
        TLabel *LabelDimensiuni;
        TImage *ImagineDetalii;
        TStringGrid *StringGridS;
        TTabSheet *TabTranslare;
        TShape *ShapeDetaliu;
        TLabel *LabelEgalTab2;
        TStringGrid *StringGridT2;
        TStringGrid *StringGridT1;
        TButton *ButtonDCT;
        TButton *ButtonTranslare;
        TLabel *LabelT3b;
        TLabel *LabelT3a;
        TTabSheet *TabDCT;
        TStringGrid *StringGridD1;
        TLabel *LabelT4a;
        TLabel *LabelT4b;
        TStringGrid *StringGridD2;
        TImage *Image1;
        TLabel *Label1;
        void __fastcall MainMenuMainFormFisierIesireClick(TObject *Sender);
        void __fastcall MainMenuMainFormAjutorDespreClick(TObject *Sender);
        void __fastcall ButtonIncarcaClick(TObject *Sender);
        void __fastcall ImagineMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall ImagineClick(TObject *Sender);
        void __fastcall ImagineDetaliiMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall StringGridSDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall ShapeDetaliuMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ButtonTranslareClick(TObject *Sender);
        void __fastcall StringGridT1SelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall StringGridT1DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall ButtonDCTClick(TObject *Sender);
        void __fastcall StringGridT2DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall StringGridD1DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall StringGridD2DrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall StringGridD1SelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void __fastcall IncarcaImagine();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
