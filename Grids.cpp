#include <stdio.h>
#include <vector>
#include "common.h"
#include "grids.h"


/*
 * ���᮪ ����
 */
typedef struct
  {
    int Monitor;
    TLinear LeftDelta;
    TLinear Width;
    TLinear TopDelta;
    TLinear Height;
  }TGridCell;
typedef std::vector<TGridCell> TGrids;
TGrids Grids;
/*
 * ����� ����� �㭪樨 �� ������ ��������� ����
 */
/*
 * ���� �������襣� ��饣� ����⥫�
 */
unsigned int NOD(unsigned int A, unsigned int B)
  {
    if(A<B) std::swap(A,B);
    while(B)
      {
        A%=B;
        std::swap(A,B);
      }//WHILE
    return A;
  }//NOD
////////////////////////////////////////////////////////////////////////////////
/*
 * ������� TValue
 */
TValue SimplifyTValue(TValue V)
  {
    int nod=NOD(abs(V.N),abs(V.D));
    V.N/=nod;
    V.D/=nod;
    return V;
  }//SimplifyTValue
////////////////////////////////////////////////////////////////////////////////
/*
 * �������� ���� TValue
 */
TValue AddTValueTValue(TValue lhs, TValue rhs)
  {
    TValue Result;
    Result.N=lhs.N*rhs.D+rhs.N*lhs.D;
    Result.D=lhs.D*rhs.D;
    return SimplifyTValue(Result);
  }//AddTValueTValue
////////////////////////////////////////////////////////////////////////////////
/*
 * ���⠭�� ���� TValue
 */
TValue SubTValueTValue(TValue lhs, TValue rhs)
  {
    TValue Result;
    Result.N=lhs.N*rhs.D-rhs.N*lhs.D;
    Result.D=lhs.D*rhs.D;
    return SimplifyTValue(Result);
  }//SubTValueTValue
////////////////////////////////////////////////////////////////////////////////
/*
 * ��������� ���� TValue
 */
TValue MultTValueTValue(TValue lhs, TValue rhs)
  {
    TValue Result;
    Result.N=lhs.N*rhs.N;
    Result.D=lhs.D*rhs.D;
    return SimplifyTValue(Result);
  }//MultTValueTValue
////////////////////////////////////////////////////////////////////////////////
/*
 * �८�ࠧ����� �� 楫��� �᫠ � TValue
 */
TValue IntToTValue(int Value)
  {
    TValue Result;
    Result.N=Value;
    Result.D=1;
    return Result;
  }//IntToTValue
////////////////////////////////////////////////////////////////////////////////
/*
 * �८�ࠧ����� �⭮襭�� � TValue
 */
TValue ProportionToTValue(int Numerator, int Denumerator)
  {
    TValue Result;
    Result.N=Numerator;
    Result.D=Denumerator;
    return Result;
  }//ProportionToTValue
////////////////////////////////////////////////////////////////////////////////
/*
 * �८�ࠧ����� �� TValue � TLinear
 */
TLinear TValueToTLinear(TValue V)
  {
    TLinear Result;
    Result.A=IntToTValue(0);
    Result.B=V;
    return Result;
  }//TValueToTLinear
////////////////////////////////////////////////////////////////////////////////
/*
 * ������ �� TLinear TValue
 */
TLinear SubtractTLinearTValue(TLinear L, TValue V)
  {
    L.B=SubTValueTValue(L.B,V);
    return L;
  }//SubtractTLinearTValue
////////////////////////////////////////////////////////////////////////////////
/*
 * �������� TLinear �� TValue
 */
TLinear MultiplyTLinearTValue(TLinear L, TValue V)
  {
    L.A=MultTValueTValue(L.A,V);
    L.B=MultTValueTValue(L.B,V);
    return L;
  }//MultiplyTLinearTValue
////////////////////////////////////////////////////////////////////////////////
/*
 * ������� ��� �������� �᫠
 */
TLinear AddTLinearTLinear(TLinear L, TLinear R)
  {
    L.A=AddTValueTValue(L.A,R.A);
    L.B=AddTValueTValue(L.B,R.B);
    return L;
  }//AddTLinearTLinear
////////////////////////////////////////////////////////////////////////////////
/*
 * �������� ���� � ᯨ᮪ ����
 */
void AddWindow(int Monitor,
                TLinear LeftDelta, TLinear Width,
                TLinear TopDelta,  TLinear Height)
  {
    TGridCell Cell;
    Cell.Monitor=Monitor;
    Cell.LeftDelta=LeftDelta;
    Cell.Width=Width;
    Cell.TopDelta=TopDelta;
    Cell.Height=Height;
    Grids.push_back(Cell);
  }//AddWindow
////////////////////////////////////////////////////////////////////////////////
/*
 * ��⠭����� �࠭��� ��� ॣ���� � ��� ��������⥩
 */
void SetBorders(int Monitor, TRegion* Region,
                TLinear LeftDelta, TLinear Width,
                TLinear TopDelta,  TLinear Height
                )
  {
    switch(Region->RegionType)
      {
        case rtWindow:
             AddWindow(Monitor,LeftDelta,Width,TopDelta,Height);
             break;
        case rtHorizontal:
             {//�������� �ਭ� ����� ���ॣ������
               int Fraq=0;  //���� ���� ��� �ய��樮������ ॣ�����
               int Fixed=0; //���� ����, ���������� 䨪�஢���묨 ॣ������
               TLinear FraqHeight=Height, FraqWidth=Width;
               TListCage* SubRegion=NULL;
               for(SubRegion=Region->RegionList;SubRegion;SubRegion=SubRegion->Next)
                 {
                   if(SubRegion->Region->isFixed)
                     {
                       Fixed+=SubRegion->Region->Dimension;
                     }//THEN
                   else
                     {
                       Fraq+=SubRegion->Region->Dimension;
                     }//ELSE
                 }//FOR
               FraqWidth=SubtractTLinearTValue(FraqWidth,IntToTValue(Fixed));
               //�������� ����祭�� ���祭�� ����� ���ॣ������
               for(SubRegion=Region->RegionList;SubRegion;SubRegion=SubRegion->Next)
                 {
                   TLinear CurWidth;
                   if(SubRegion->Region->isFixed)
                     {
                       CurWidth=TValueToTLinear(IntToTValue(SubRegion->Region->Dimension));
                     }//THEN
                   else
                     {
                       CurWidth=MultiplyTLinearTValue(FraqWidth,ProportionToTValue(SubRegion->Region->Dimension,Fraq));
                     }//ELSE
                   SetBorders(  Monitor,SubRegion->Region,
                                LeftDelta, CurWidth,
                                TopDelta, Height
                                );
                   LeftDelta=AddTLinearTLinear(LeftDelta,CurWidth);
                 }//FOR
             }//�������� �ਭ� ����� ���ॣ������
             break;
        case rtVertical:
             {//�������� ����� ����� ���ॣ������
               int Fraq=0;  //���� ���� ��� �ய��樮������ ॣ�����
               int Fixed=0; //���� ����, ���������� 䨪�஢���묨 ॣ������
               TLinear FraqHeight=Height, FraqWidth=Width;
               TListCage* SubRegion=NULL;
               for(SubRegion=Region->RegionList;SubRegion;SubRegion=SubRegion->Next)
                 {
                   if(SubRegion->Region->isFixed)
                     {
                       Fixed+=SubRegion->Region->Dimension;
                     }//THEN
                   else
                     {
                       Fraq+=SubRegion->Region->Dimension;
                     }//ELSE
                 }//FOR
               FraqHeight=SubtractTLinearTValue(FraqHeight,IntToTValue(Fixed));
               //�������� ����祭�� ���祭�� ����� ���ॣ������
               for(SubRegion=Region->RegionList;SubRegion;SubRegion=SubRegion->Next)
                 {
                   TLinear CurHeight;
                   if(SubRegion->Region->isFixed)
                     {
                       CurHeight=TValueToTLinear(IntToTValue(SubRegion->Region->Dimension));
                     }//THEN
                   else
                     {
                       CurHeight=MultiplyTLinearTValue(FraqHeight,ProportionToTValue(SubRegion->Region->Dimension,Fraq));
                     }//ELSE
                   SetBorders(  Monitor,SubRegion->Region,
                                LeftDelta, Width,
                                TopDelta, CurHeight
                                );
                   TopDelta=AddTLinearTLinear(TopDelta,CurHeight);
                 }//FOR
             }//�������� �ਭ� ����� ���ॣ������
             break;
      }//SWITCH
  }//SetBorders
////////////////////////////////////////////////////////////////////////////////
/*
 * �뢥�� ��ࠦ����, ���஥ ����뢠�� ���न���� � ����࠭�⢥ ������
 */
void PrintCoordinate(FILE*OUT, int Monitor, TValue A, TValue B, char* Pivot, char* Dimension, char* PD)
  {
    if((A.N==0))
      {
        //���砩, ����� ��� ᬥ饭�� �� ���୮� �窨
        fprintf(OUT,Pivot,Monitor);
        if(B.N!=0)
          {
            fprintf(OUT," %c %d",(B.N>0)?'+':'-',abs(B.N));
            if(B.D!=1) fprintf(OUT,"/%d",B.D);
          }//THEN
      }//THEN
    else if((A.N==1)&&(A.D==1))
      {
        //���砩 ������� ᬥ饭��
        fprintf(OUT,PD,Monitor);
        if(B.N!=0)
          {
            fprintf(OUT," %c %d",(B.N>0)?'+':'-',abs(B.N));
            if(B.D!=1) fprintf(OUT,"/%d",B.D);
          }//THEN
      }//THEN
    else if((A.N==1)&&(B.N==0))
      {
        //���砩 ������� ��楫�
        fprintf(OUT,Pivot,Monitor);
        fprintf(OUT," + ");
        fprintf(OUT,Dimension,Monitor);
        fprintf(OUT," / %d",A.D);
      }//THEN
    else if((A.N==1))
      {
        //���砩 ������� ��楫�
        fprintf(OUT,Pivot,Monitor);
        fprintf(OUT," + ");
        fprintf(OUT,Dimension,Monitor);
        fprintf(OUT," / %d",A.D);
        if(B.N!=0)
          {
            fprintf(OUT," %c %d",(B.N>0)?'+':'-',abs(B.N));
            if(B.D!=1) fprintf(OUT,"/%d",B.D);
          }//THEN
      }//THEN
    else
      {
        //�� ��⠫�� ��砨
        fprintf(OUT,Pivot,Monitor);
        fprintf(OUT," + ");
        fprintf(OUT,Dimension,Monitor);
        fprintf(OUT," / %d * %d",A.D,A.N);
        if(B.N!=0)
          {
            fprintf(OUT," %c %d",(B.N>0)?'+':'-',abs(B.N));
            if(B.D!=1) fprintf(OUT,"/%d",B.D);
          }//THEN
      }//ELSE
    fprintf(OUT,"\n");
  }//PrintCoordinate
////////////////////////////////////////////////////////////////////////////////
/*
 * ���࠭��� ࠧ���� � 䠩�
 */
void SaveGridToFile(const char* FileName)
  {
    FILE* OUT=fopen(FileName,"wt");
    fprintf(OUT,"[Groups]\n\n  NumberOfGroups = %d\n\n",Grids.size());
    for(TGrids::iterator X=Grids.begin(),XEnd=Grids.end();X!=XEnd;++X)
      {
        TLinear Temp;
        fprintf(OUT,"[%d]\n",1+distance(Grids.begin(),X));
        //TriggerTop
        fprintf(OUT,"  TriggerTop    = ");
        PrintCoordinate(OUT,X->Monitor,X->TopDelta.A,X->TopDelta.B,"[Monitor%dTop]","[Monitor%dHeight]","[Monitor%dBottom]");
        //TriggerRight
        fprintf(OUT,"  TriggerRight  = ");
        Temp=AddTLinearTLinear(X->LeftDelta,X->Width);
        PrintCoordinate(OUT,X->Monitor,Temp.A,Temp.B,"[Monitor%dLeft]","[Monitor%dWidth]","[Monitor%dRight]");
        //TriggerBottom
        fprintf(OUT,"  TriggerBottom = ");
        Temp=AddTLinearTLinear(X->TopDelta,X->Height);
        PrintCoordinate(OUT,X->Monitor,Temp.A,Temp.B,"[Monitor%dTop]","[Monitor%dHeight]","[Monitor%dBottom]");
        //TriggerLeft
        fprintf(OUT,"  TriggerLeft   = ");
        PrintCoordinate(OUT,X->Monitor,X->LeftDelta.A,X->LeftDelta.B,"[Monitor%dLeft]","[Monitor%dWidth]","[Monitor%dRight]");
        //GridTop
        fprintf(OUT,"  GridTop       = ");
        PrintCoordinate(OUT,X->Monitor,X->TopDelta.A,X->TopDelta.B,"[Monitor%dTop]","[Monitor%dHeight]","[Monitor%dBottom]");
        //GridRight
        fprintf(OUT,"  GridRight     = ");
        Temp=AddTLinearTLinear(X->LeftDelta,X->Width);
        PrintCoordinate(OUT,X->Monitor,Temp.A,Temp.B,"[Monitor%dLeft]","[Monitor%dWidth]","[Monitor%dRight]");
        //GridBottom
        fprintf(OUT,"  GridBottom    = ");
        Temp=AddTLinearTLinear(X->TopDelta,X->Height);
        PrintCoordinate(OUT,X->Monitor,Temp.A,Temp.B,"[Monitor%dTop]","[Monitor%dHeight]","[Monitor%dBottom]");
        //GridLeft
        fprintf(OUT,"  GridLeft      = ");
        PrintCoordinate(OUT,X->Monitor,X->LeftDelta.A,X->LeftDelta.B,"[Monitor%dLeft]","[Monitor%dWidth]","[Monitor%dRight]");

        fprintf(OUT,"\n");
        //fprintf(OUT,"Window Left=MLeft+%d\/%d*MW+%d\/%d Top=MTop+%d\/%d*MH+%d\/%d Width=%d\/%d*MW+%d\/%d Height=%d\/%d*MH+%d\/%d\n",
        //        X->LeftDelta.A.N , X->LeftDelta.A.D ,X->LeftDelta.B.N,X->LeftDelta.B.D ,
        //        X->TopDelta.A.N  , X->TopDelta.A.D  ,X->TopDelta.B.N ,X->TopDelta.B.D  ,
        //        X->Width.A.N     , X->Width.A.D     ,X->Width.B.N    ,X->Width.B.D     ,
        //        X->Height.A.N    , X->Height.A.D    ,X->Height.B.N   ,X->Height.B.D    );

      }//FOR
    fclose(OUT);
  }//SaveGridToFile
////////////////////////////////////////////////////////////////////////////////
