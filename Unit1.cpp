#include <jpeg.hpp>
#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include <string.h>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGRID"
#pragma resource "*.dfm"
  #define max(a,b)    (((a) > (b)) ? (a) : (b))
  #define min(a,b)    (((a) < (b)) ? (a) : (b))
TForm1 *Form1;
TImage *undo;
TImage *redo;
AnsiString file_name;
TJPEGImage *myjpeg;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        DoubleBuffered=true;
        ScrollBox1->DoubleBuffered=true;
        Form1->FGShape->Brush->Color=TColor(clBlack);
        //Image1 = new TImage(this);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::New1Click(TObject *Sender)
{
       Image1->Picture=0; 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Open1Click(TObject *Sender)
{
Form1->CircleButton->Down=false;
Form1->SquareButton->Down=false;
Form1->SolidCirButton->Down=false;
Form1->RnRectButton->Down=false;
Form1->LineButton->Down=false;
Form1->FillButton->Down=false;
Form1->EraseButton->Down=false;
Form1->PencilButton->Down=false;
//Este necesar sa includem fisierul "jpeg.hpp"
OpenDialog1->Filter = "Bmp files(*.bmp)|*.BMP|JPEG images\
(*.jpg)|*.jpg;";
if ( OpenDialog1->Execute() )
{
if (!FileExists(OpenDialog1->FileName))
return; // ne asiguram ca s-a selectat un fisier
AnsiString temp2 = ExtractFileName(OpenDialog1->FileName);
AnsiString temp = ExtractFileExt(OpenDialog1->FileName);
AnsiString Ext = temp.LowerCase();
if ( Ext.AnsiPos( "jpg" ) > 0 ) // este un fisier jpg
{ //-- Decomprima jpeg-ul in imagine bitmap
TJPEGImage *myjpeg = new TJPEGImage();
myjpeg->LoadFromFile(OpenDialog1->FileName);
// creaza o replica de tip bitmap
myjpeg->DIBNeeded();
Image1->Picture->Bitmap->Assign(myjpeg);
delete myjpeg;
}
else if ( Ext.AnsiPos( "bmp" ) > 0)
Image1->Picture->Bitmap->LoadFromFile(
OpenDialog1->FileName);
//EditFile->Text = ExtractFileName(OpenDialog1->FileName);
//EditWidth->Text = Image1->Width;
//ditHeight->Text = Image1->Height;
//EditPixelFormat->Text =
//Image1->Picture->Bitmap->PixelFormat;
       //EditFile->Text = ExtractFileName(OpenDialog1->FileName);
       file_name= ExtractFileName(OpenDialog1->FileName) ;
       //EditFile->Text=file_name;
       ShowMessage(file_name);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Save1Click(TObject *Sender)
{
// Este necesar sa includem fisierul "jpeg.hpp"
// SaveDialog1->Filter ="Bmp files (*.bmp)|*.BMP| JPEG images
// (*.jpg;*.jpeg)| // *.jpg; *;jpeg" ;
SaveDialog1->Title = "Save Image";
SaveDialog1->DefaultExt = "jpg";
// SaveDialog1->Filter = "JPG|*.jpg";
SaveDialog1->Filter="JPEG images (*.jpg)|*.jpg;|Bmp files\
(*.bmp)|*.BMP";
SaveDialog1->FilterIndex = 1;
if (SaveDialog1->Execute())
{
AnsiString temp2 = ExtractFileName(SaveDialog1->FileName);
AnsiString temp = ExtractFileExt(SaveDialog1->FileName);
AnsiString Ext = temp.LowerCase();
if (Ext.AnsiPos("jpg") > 0) // este un jpg
{ //-- decomprima imaginea jpeg intr-un bitmap.
TJPEGImage *jp = new TJPEGImage();
try
{
jp->Assign(Image1->Picture->Bitmap);
jp->SaveToFile(SaveDialog1->FileName);
}
__finally
{
delete jp;
}
}
else if ( Ext.AnsiPos( "bmp" ) > 0 )
Image1->Picture->Bitmap->SaveToFile(SaveDialog1->FileName);
}
}
//---------------------------------------------------------------------------





void __fastcall TForm1::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    undo = new TImage(this);
        undo->Picture = Image1->Picture;
    if (Form1->FillButton->Down)
    {
        if (Button == mbLeft)
            Image1->Canvas->Brush->Color = Form1->FGShape->Brush->Color;
        else
            Image1->Canvas->Brush->Color = Form1->BGShape->Brush->Color;
            Image1->Canvas->FloodFill(X, Y, Image1->Canvas->Pixels[X][Y], fsSurface);
        return;
    }
    if (Button != mbLeft)
        return;

    if (Form1->EraseButton->Down)
    {
        Image1->Canvas->Pen->Color = BGShape->Brush->Color;
        Image1->Canvas->Brush->Color = BGShape->Brush->Color;
        Image1->Canvas->Pen->Width = SizeBar->Position+10;
        Image1->Canvas->Rectangle(X-1, Y-1, X, Y);
        Image1->Canvas->MoveTo(X,Y);
        return;

        undo = new TImage(this);
        undo->Picture = Image1->Picture;
    }

    if (Form1->PencilButton->Down)
    {
        Image1->Canvas->Pen->Color = Form1->FGShape->Brush->Color;
        Image1->Canvas->Brush->Color = Form1->BGShape->Brush->Color;
        Image1->Canvas->Pen->Width = SizeBar->Position;
        Image1->Canvas->MoveTo(X,Y);
        return;

        undo = new TImage(this);
        undo->Picture = Image1->Picture;
    }

    InitialX = X;
    InitialY = Y;
    X1=X;
    Y1=Y;

    TmpImage = new TImage(this);
    TmpImage->Picture = Image1->Picture;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{

 if (!Shift.Contains(ssLeft))
        return;

    if (Form1->FillButton->Down)
        return;

    if (Form1->PencilButton->Down)
    {
        Image1->Canvas->LineTo(X,Y);
        return;
    }

    if (Form1->EraseButton->Down)
    {
        Image1->Canvas->LineTo(X,Y);
        return;
    }
    if(Form1->CircleButton->Down || Form1->SquareButton->Down || Form1->SolidCirButton->Down || Form1->RnRectButton->Down || Form1->LineButton->Down)
    DrawShape(X, Y);
}

void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        redo = new TImage(this);
        redo->Picture = Image1->Picture;

    if (Button != mbLeft)
        return;

    if ((Form1->FillButton->Down) || (Form1->PencilButton->Down))
        return;

    if (Form1->EraseButton->Down)
    {
        Image1->Canvas->Pen->Width = 1;
        return;
    }
    if(Form1->CircleButton->Down || Form1->SquareButton->Down || Form1->SolidCirButton->Down || Form1->RnRectButton->Down || Form1->LineButton->Down)
    {
    DrawShape(X, Y);
    delete TmpImage;
    }
}

void __fastcall TForm1::DrawShape(int X, int Y)
{
         try{
    Image1->Picture = TmpImage->Picture;
                          }
                          catch(Exception &e) {}
    Image1->Canvas->Brush->Color = Form1->BGShape->Brush->Color;
    Image1->Canvas->Pen->Color = Form1->FGShape->Brush->Color;
    Image1->Canvas->Pen->Width = SizeBar->Position;


    if (Form1->CircleButton->Down)
        Image1->Canvas->Arc(InitialX, InitialY, X, Y, X, Y, X, Y);
    else if (Form1->SquareButton->Down)
        {
        Image1->Canvas->Pen->Width = SizeBar->Position;
        Image1->Canvas->Pen->Color = Form1->FGShape->Brush->Color;
        Image1->Canvas->Brush->Style= bsClear;
        Image1->Canvas->Rectangle(InitialX, InitialY, X, Y);
        }
    else if (Form1->SolidCirButton->Down)
        Image1->Canvas->Ellipse(InitialX, InitialY, X, Y);
    else if (Form1->RnRectButton->Down)
        {
        Image1->Canvas->Brush->Style= bsClear;
        Image1->Canvas->RoundRect(InitialX, InitialY, X, Y, X1, Y1);
        }
    else if (Form1->LineButton->Down)
        {
        Image1->Canvas->Pen->Width = SizeBar->Position;
        Image1->Canvas->MoveTo(X, Y);
        Image1->Canvas->LineTo(InitialX, InitialY);
        return;
        }
}



void __fastcall TForm1::ColorGrid1Change(TObject *Sender)
{
    FGShape->Brush->Color = ColorGrid1->ForegroundColor;
    if (FGShape->Brush->Color == TColor(clBlack))
        FGShape->Pen->Color = TColor(clWhite);
    else
        FGShape->Pen->Color = TColor(clBlack);

    if (BGShape->Brush->Color == TColor(clBlack))
        BGShape->Pen->Color = TColor(clWhite);
    else
        BGShape->Pen->Color = TColor(clBlack);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
        if(ColorDialog1->Execute())
        {
                Form1->BGShape->Brush->Color=ColorDialog1->Color;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
        if(ColorDialog1->Execute())
        {
                Form1->FGShape->Brush->Color=ColorDialog1->Color;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
          Image1->Stretch=!Image1->Stretch;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
        Image1->Proportional=!Image1->Proportional;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SizeBarChange(TObject *Sender)
{
        Form1->Edit1->Text=SizeBar->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
         //Image1->Enabled=false;
         Graphics::TBitmap *source = new Graphics::TBitmap;
         source->Assign( Image1->Picture->Bitmap );
         source->PixelFormat = Image1->Picture->Bitmap->PixelFormat;

         Graphics::TBitmap *dest = new Graphics::TBitmap;
         dest->Width = source->Width;
         dest->Height = source->Height;
         dest->PixelFormat = source->PixelFormat;


         dest->Width=source->Height;
         dest->Height=source->Width;

         for (int x=0;x<source->Width;x++)
         {
                for(int y=0;y<source->Height;y++)
                {
                        dest->Canvas->Pixels[y][source->Width-1-x]=
                        source->Canvas->Pixels[x][y];
                }
         }

        Image1->Picture->Bitmap=dest;
        delete dest;
        delete source;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
int angle=180;
         //Image1->Enabled=false;
         Graphics::TBitmap *SrcBitmap = new Graphics::TBitmap;
         SrcBitmap->Assign( Image1->Picture->Bitmap );
         SrcBitmap->PixelFormat = Image1->Picture->Bitmap->PixelFormat;
         //source->LoadFromFile(file_name);
         Graphics::TBitmap *DestBitmap = new Graphics::TBitmap;
         DestBitmap->Width = SrcBitmap->Width;
         DestBitmap->Height = SrcBitmap->Height;
         //DestBitmap->PixelFormat = SrcBitmap->PixelFormat;


        float radians=(2*3.1416*angle)/360;

float cosine=(float)cos(radians);
float sine=(float)sin(radians); 

float Point1x=(-SrcBitmap->Height*sine); 
float Point1y=(SrcBitmap->Height*cosine); 
float Point2x=(SrcBitmap->Width*cosine-SrcBitmap->Height*sine); 
float Point2y=(SrcBitmap->Height*cosine+SrcBitmap->Width*sine); 
float Point3x=(SrcBitmap->Width*cosine); 
float Point3y=(SrcBitmap->Width*sine); 

float minx=min(0,min(Point1x,min(Point2x,Point3x)));
float miny=min(0,min(Point1y,min(Point2y,Point3y))); 
float maxx=max(Point1x,max(Point2x,Point3x)); 
float maxy=max(Point1y,max(Point2y,Point3y)); 

int DestBitmapWidth=(int)ceil(fabs(maxx)-minx); 
int DestBitmapHeight=(int)ceil(fabs(maxy)-miny); 

DestBitmap->Height=DestBitmapHeight;
DestBitmap->Width=DestBitmapWidth;
for(int x=0;x<DestBitmapWidth;x++) 
{ 
  for(int y=0;y<DestBitmapHeight;y++) 
  { 
    int SrcBitmapx=(int)((x+minx)*cosine+(y+miny)*sine); 
    int SrcBitmapy=(int)((y+miny)*cosine-(x+minx)*sine); 
    if(SrcBitmapx>=0&&SrcBitmapx<SrcBitmap->Width&&SrcBitmapy>=0&& 
         SrcBitmapy<SrcBitmap->Height) 
    { 
      DestBitmap->Canvas->Pixels[x][y]= 
          SrcBitmap->Canvas->Pixels[SrcBitmapx][SrcBitmapy]; 
    } 
  } 
} 
//Show the rotated bitmap 
Image1->Picture->Bitmap=DestBitmap; 
delete DestBitmap; 
delete SrcBitmap;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Mirror1Click(TObject *Sender)
{
         //Graphics::TBitmap *source = new Graphics::TBitmap;
         //source->Assign( Image1->Picture->Bitmap );
         //source->PixelFormat = Image1->Picture->Bitmap->PixelFormat;

         Graphics::TBitmap *dest = new Graphics::TBitmap;
         dest->Width = Image1->Picture->Bitmap->Width;
         dest->Height = Image1->Picture->Bitmap->Height;
         //dest->PixelFormat = source->PixelFormat;


         //dest->Width=source->Height;
         //dest->Height=source->Width;

         for (int x=0;x<Image1->Picture->Bitmap->Width;x++)
         {
                for(int y=0;y<Image1->Picture->Bitmap->Height;y++)
                {
                        dest->Canvas->Pixels[Width -1 -x][y]=
                        Image1->Canvas->Pixels[x][y];
                }
         }

        Image1->Picture->Bitmap=dest;
        delete dest;
        //delete source;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zoomin1Click(TObject *Sender)
{
Graphics::TBitmap *source = new Graphics::TBitmap;
         source->Assign( Image1->Picture->Bitmap );
         source->PixelFormat = Image1->Picture->Bitmap->PixelFormat;

         Graphics::TBitmap *dest = new Graphics::TBitmap;
         dest->Width = source->Width;
         dest->Height = source->Height;
         dest->PixelFormat = source->PixelFormat;

        dest->Width = source->Width;
        dest->Height = source->Height;
        int x2=0;
        int y2=0;

        for (int y=0; y<source->Height; y++)
        {
          x2=0;
          for (int x=0; x<source->Width; x++)
         {
                dest->Canvas->Pixels[x2][y2]=source->Canvas->Pixels[x][y];
                dest->Canvas->Pixels[x2][y2+1]=source->Canvas->Pixels[x][y];
                dest->Canvas->Pixels[x2+1][y2]=source->Canvas->Pixels[x][y];
                dest->Canvas->Pixels[x2+1][y2+1]=source->Canvas->Pixels[x][y];
                x2=x2+2;
          }
         y2=y2+2;
        }
         Image1->Picture->Bitmap = dest;
         delete dest;  delete source;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zoomout1Click(TObject *Sender)
{

         Graphics::TBitmap *source = new Graphics::TBitmap;
         source->Assign( Image1->Picture->Bitmap );
         source->PixelFormat = Image1->Picture->Bitmap->PixelFormat;

         Graphics::TBitmap *dest = new Graphics::TBitmap;
         dest->Width = source->Width;
         dest->Height = source->Height;
         dest->PixelFormat = source->PixelFormat;

         dest->Width = source->Width/2;
         dest->Height = source->Height/2;
       
        int y2=0,x2=0;
        for (int i=0; i<source->Width; i=i+2 )
        {
                y2=0;
                for(int j=0; j<source->Height; j=j+2)
                {
                        dest->Canvas->Pixels[x2][y2] =source->Canvas->Pixels[i][j];
                        y2=y2+1;
                }
                x2=x2+1;
        }

         Image1->Picture->Bitmap = dest;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Binarizare1Click(TObject *Sender)
{
Graphics::TBitmap *source = new Graphics::TBitmap;
         source->Assign( Image1->Picture->Bitmap );
         source->PixelFormat = Image1->Picture->Bitmap->PixelFormat;

         Graphics::TBitmap *dest = new Graphics::TBitmap;
         dest->Width = source->Width;
         dest->Height = source->Height;
         dest->PixelFormat = source->PixelFormat;

         for(int y=1;y<source->Width-1;y++)
                for(int x=1;x<source->Height-1;x++)
                {
                        int sum=GetRValue(source->Canvas->Pixels[y][x])+
                       		  GetBValue(source->Canvas->Pixels[y][x])+
	                          GetGValue(source->Canvas->Pixels[y][x]);
                        if(sum/3<127)
	                         dest->Canvas->Pixels[y][x]= TColor(RGB(0,0,0));
                        else
            	           dest->Canvas->Pixels[y][x]= TColor(RGB(255,255,255));
                }

        Image1->Picture->Bitmap = dest;
        delete dest;  delete source;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdgeDetection1Click(TObject *Sender)
{
Graphics::TBitmap *source = new Graphics::TBitmap;
         source->Assign( Image1->Picture->Bitmap );
         source->PixelFormat = Image1->Picture->Bitmap->PixelFormat;

         Graphics::TBitmap *dest = new Graphics::TBitmap;
         dest->Width = source->Width;
         dest->Height = source->Height;
         dest->PixelFormat = source->PixelFormat;

        for(int y=1;y<source->Width-1;y++)
                for(int x=1;x<source->Height-1;x++)
                {
                        int val1= GetRValue(source->Canvas->Pixels[y-1][x-1]);
                        int val2= GetRValue(source->Canvas->Pixels[y][x]);
                        int valf= abs(val2-val1);
                        dest->Canvas->Pixels[y][x]=TColor(RGB(valf,valf,valf));
                }

        Image1->Picture->Bitmap=dest;
        delete dest;  delete source;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RedChannel1Click(TObject *Sender)
{
        if( Image1->Picture->Bitmap->Empty ==true )
                return;
        //crearea unui bitmap sursa temporar
        Graphics::TBitmap *source   = new Graphics::TBitmap;
        source->Assign( Image1->Picture->Bitmap );
        source->PixelFormat  =  Image1->Picture->Bitmap->PixelFormat;

        // crearea si stabilirea unui bitmap destinatie temporar
        Graphics::TBitmap *dest     = new Graphics::TBitmap;
        dest->Width                 = source->Width;
        dest->Height                = source->Height;
        dest->PixelFormat           = source->PixelFormat;

        RGBTRIPLE* pixels;
        TColor color;

        for( int y=0; y<source->Height; y++ )
                {
                    pixels = (RGBTRIPLE*)source->ScanLine[y];
                    for (int x=0; x<source->Width; x++)
                       dest->Canvas->Pixels[x][y] = TColor(RGB(pixels[x].rgbtRed, 0, 0));
                }
                //Asigneaza bitmapul destinatie inapoi catre Image1 si "curata"
                Image1->Picture->Bitmap = dest;
                delete dest;  delete source;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GreenChannel1Click(TObject *Sender)
{
          if( Image1->Picture->Bitmap->Empty ==true )
                return;
        //crearea unui bitmap sursa temporar
        Graphics::TBitmap *source   = new Graphics::TBitmap;
        source->Assign( Image1->Picture->Bitmap );
        source->PixelFormat  =  Image1->Picture->Bitmap->PixelFormat;

        // crearea si stabilirea unui bitmap destinatie temporar
        Graphics::TBitmap *dest     = new Graphics::TBitmap;
        dest->Width                 = source->Width;
        dest->Height                = source->Height;
        dest->PixelFormat           = source->PixelFormat;

        RGBTRIPLE* pixels;
        TColor color;
        for(int i=0;i<source->Height;i++)
                {
                        pixels=(RGBTRIPLE*)source->ScanLine[i];
                        for(int j=0;j<source->Width;j++)
                        {
                                dest->Canvas->Pixels[j][i]=TColor(RGB(0,pixels[j].rgbtGreen,0));
                        }
                }
                //Asigneaza bitmap-ul destinatie iinapoi catre Image1 si "curata"
                Image1->Picture->Bitmap=dest;
                delete dest;
                delete source;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BlueChannel1Click(TObject *Sender)
{
           if( Image1->Picture->Bitmap->Empty ==true )
                return;
        //crearea unui bitmap sursa temporar
        Graphics::TBitmap *source   = new Graphics::TBitmap;
        source->Assign( Image1->Picture->Bitmap );
        source->PixelFormat  =  Image1->Picture->Bitmap->PixelFormat;

        // crearea si stabilirea unui bitmap destinatie temporar
        Graphics::TBitmap *dest     = new Graphics::TBitmap;
        dest->Width                 = source->Width;
        dest->Height                = source->Height;
        dest->PixelFormat           = source->PixelFormat;

        RGBTRIPLE* pixels;
        TColor color;

        for(int i=0;i<source->Height;i++)
                {
                        pixels=(RGBTRIPLE*)source->ScanLine[i];
                        for(int j=0;j<source->Width;j++)
                        {
                                dest->Canvas->Pixels[j][i]=TColor(RGB(0,0,pixels[j].rgbtBlue));
                        }
                }
                //Asigneaza bitmap-ul destinatie inapoi catre Image1 si "curata"
                Image1->Picture->Bitmap=dest;
                delete dest;
                delete source;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Grayscale1Click(TObject *Sender)
{
        if( Image1->Picture->Bitmap->Empty ==true )
                return;
        //crearea unui bitmap sursa temporar
        Graphics::TBitmap *source   = new Graphics::TBitmap;
        source->Assign( Image1->Picture->Bitmap );
        source->PixelFormat  =  Image1->Picture->Bitmap->PixelFormat;

        // crearea si stabilirea unui bitmap destinatie temporar
        Graphics::TBitmap *dest     = new Graphics::TBitmap;
        dest->Width                 = source->Width;
        dest->Height                = source->Height;
        dest->PixelFormat           = source->PixelFormat;

        RGBTRIPLE* pixels;
        TColor color;

        double Y;
                for(int i=0;i<source->Height;i++)
                {
                        pixels=(RGBTRIPLE*)source->ScanLine[i];
                        for(int j=0;j<source->Width;j++)
                        {     Y=0;
                              Y=0.2126*pixels[j].rgbtRed+0.7152*pixels[j].rgbtGreen+0.0722*pixels[j].rgbtBlue ;
                              dest->Canvas->Pixels[j][i]=TColor(RGB(Y,Y,Y));
                        }
                }
                //Asigneaza bitmap-ul destinatie catre Image1 si "curata"
                Image1->Picture->Bitmap=dest;
                delete dest;
                delete source;
}
//---------------------------------------------------------------------------

