//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include <StdActns.hpp>
#include <ExtActns.hpp>
#include <Buttons.hpp>
#include "CGRID.h"
//---------------------------------------------------------------------------
const int crDraw  = 7;
const int crFill  = 5;
const int crErase = 8;
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *New1;
        TMenuItem *Open1;
        TMenuItem *Save1;
        TMenuItem *Exit1;
        TScrollBox *ScrollBox1;
        TImage *Image1;
        TOpenPictureDialog *OpenPictureDialog1;
        TSaveDialog *SaveDialog1;
        TActionManager *ActionManager1;
        TAction *Action1;
        TEditCut *EditCut1;
        TAction *Action2;
        TOpenPicture *OpenPicture1;
        TEditDelete *EditDelete1;
        TImageList *ImageList1;
        TMenuItem *N1;
        TPanel *Panel1;
        TToolBar *ToolBar1;
        TSpeedButton *PencilButton;
        TToolButton *ToolButton1;
        TSpeedButton *EraseButton;
        TToolButton *ToolButton2;
        TSpeedButton *FillButton;
        TToolButton *ToolButton3;
        TSpeedButton *CircleButton;
        TToolButton *ToolButton7;
        TSpeedButton *LineButton;
        TToolButton *ToolButton8;
        TSpeedButton *SquareButton;
        TToolButton *ToolButton9;
        TSpeedButton *RnRectButton;
        TToolButton *ToolButton10;
        TSpeedButton *SolidCirButton;
        TPanel *Panel2;
        TCColorGrid *ColorGrid1;
        TSpeedButton *SpeedButton1;
        TShape *FGShape;
        TLabel *Label1;
        TSpeedButton *SpeedButton2;
        TShape *BGShape;
        TLabel *Label2;
        TSpeedButton *SpeedButton3;
        TColorDialog *ColorDialog1;
        TSpeedButton *SpeedButton4;
        TOpenDialog *OpenDialog1;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TTrackBar *SizeBar;
        TEdit *Edit1;
        TSpeedButton *SpeedButton5;
        TSpeedButton *SpeedButton6;
        TMenuItem *Actions1;
        TMenuItem *Mirror1;
        TMenuItem *Zoomin1;
        TMenuItem *Zoomout1;
        TMenuItem *Binarizare1;
        TMenuItem *EdgeDetection1;
        TMenuItem *Color1;
        TMenuItem *RedChannel1;
        TMenuItem *GreenChannel1;
        TMenuItem *BlueChannel1;
        TMenuItem *Grayscale1;
        void __fastcall New1Click(TObject *Sender);
        void __fastcall Open1Click(TObject *Sender);
        void __fastcall Save1Click(TObject *Sender);
        //void __fastcall PencilButtonClick(TObject *Sender);
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        //void __fastcall FillButtonClick(TObject *Sender);
        //void __fastcall FormCreate(TObject *Sender);
        //void __fastcall EraseButtonClick(TObject *Sender);
        void __fastcall ColorGrid1Change(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall SizeBarChange(TObject *Sender);
        void __fastcall SpeedButton5Click(TObject *Sender);
        void __fastcall SpeedButton6Click(TObject *Sender);
        void __fastcall Mirror1Click(TObject *Sender);
        void __fastcall Zoomin1Click(TObject *Sender);
        void __fastcall Zoomout1Click(TObject *Sender);
        void __fastcall Binarizare1Click(TObject *Sender);
        void __fastcall EdgeDetection1Click(TObject *Sender);
        void __fastcall RedChannel1Click(TObject *Sender);
        void __fastcall GreenChannel1Click(TObject *Sender);
        void __fastcall BlueChannel1Click(TObject *Sender);
        void __fastcall Grayscale1Click(TObject *Sender);
private:
    int InitialX;
    int InitialY;
    int X1;
    int Y1;
    TImage *TmpImage;
public:		
        __fastcall TForm1(TComponent* Owner);
       
        void __fastcall DrawShape(int X, int Y);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 