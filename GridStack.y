%{
#include <stdio.h>
#include <malloc.h>
#include "common.h"
%}
%union
 {
  int       IntVal;
  TRegion*  Region;
  TListCage*RegionList;
  TMonitor* Monitor;
 }

%token <IntVal> MONITOR WINDOW HSTACK VSTACK OPEN CLOSE
%token <IntVal> DIMENSION FIX_DIMENTION
%type  <Region> window hstack vstack region
%type  <RegionList> region_list
%type  <Monitor> monitor monitor_list

%%
start:          monitor_list
                                            {
                                                Monitors=$1;
                                            }
        ;
monitor_list:   monitor
                                            {
                                                $$=$1;
                                            }
        |       monitor monitor_list
                                            {
                                                $1->Next=$2;
                                                $$=$1;
                                            }
        ;
monitor:        MONITOR DIMENSION region
                                            {
                                                TMonitor* Monitor=(TMonitor*)malloc(sizeof(TMonitor));
                                                Monitor->Region=$3;
                                                Monitor->Monitor=$2;
                                                Monitor->Next=NULL;
                                                $$=Monitor;
                                            }
        ;
region_list:    region
                                            {
                                                TListCage* Cage=(TListCage*)malloc(sizeof(TListCage));
                                                Cage->Region=$1;
                                                Cage->Next=NULL;
                                                $$=Cage;
                                            }
        |       region region_list
                                            {
                                                TListCage* Cage=(TListCage*)malloc(sizeof(TListCage));
                                                Cage->Region=$1;
                                                Cage->Next=$2;
                                                $$=Cage;
                                            }
        ;
region:         window
        |       hstack
        |       vstack
        ;
window:         WINDOW DIMENSION
                                            {
                                                TRegion* Window=(TRegion*)malloc(sizeof(TRegion));
                                                Window->RegionType=rtWindow;
                                                Window->isFixed=0;
                                                Window->Dimension=$2;
                                                Window->RegionList=NULL;
                                                $$=Window;
                                            }
        |       WINDOW FIX_DIMENTION
                                            {
                                                TRegion* Window=(TRegion*)malloc(sizeof(TRegion));
                                                Window->RegionType=rtWindow;
                                                Window->isFixed=1;
                                                Window->Dimension=$2;
                                                Window->RegionList=NULL;
                                                $$=Window;
                                            }
        |       WINDOW
                                            {
                                                TRegion* Window=(TRegion*)malloc(sizeof(TRegion));
                                                Window->RegionType=rtWindow;
                                                Window->isFixed=0;
                                                Window->Dimension=1;
                                                Window->RegionList=NULL;
                                                $$=Window;
                                            }
        ;
hstack:         HSTACK OPEN region_list CLOSE
                                            {
                                                TRegion* Window=(TRegion*)malloc(sizeof(TRegion));
                                                Window->RegionType=rtHorizontal;
                                                Window->isFixed=0;
                                                Window->Dimension=1;
                                                Window->RegionList=$3;
                                                $$=Window;
                                            }
        |       HSTACK DIMENSION OPEN region_list CLOSE
                                            {
                                                TRegion* Window=(TRegion*)malloc(sizeof(TRegion));
                                                Window->RegionType=rtHorizontal;
                                                Window->isFixed=0;
                                                Window->Dimension=$2;
                                                Window->RegionList=$4;
                                                $$=Window;
                                            }
        |       HSTACK FIX_DIMENTION OPEN region_list CLOSE
                                            {
                                                TRegion* Window=(TRegion*)malloc(sizeof(TRegion));
                                                Window->RegionType=rtHorizontal;
                                                Window->isFixed=1;
                                                Window->Dimension=$2;
                                                Window->RegionList=$4;
                                                $$=Window;
                                            }
        ;
vstack:         VSTACK OPEN region_list CLOSE
                                            {
                                                TRegion* Window=(TRegion*)malloc(sizeof(TRegion));
                                                Window->RegionType=rtVertical;
                                                Window->isFixed=0;
                                                Window->Dimension=1;
                                                Window->RegionList=$3;
                                                $$=Window;
                                            }
        |       VSTACK DIMENSION OPEN region_list CLOSE
                                            {
                                                TRegion* Window=(TRegion*)malloc(sizeof(TRegion));
                                                Window->RegionType=rtVertical;
                                                Window->isFixed=0;
                                                Window->Dimension=$2;
                                                Window->RegionList=$4;
                                                $$=Window;
                                            }
        |       VSTACK FIX_DIMENTION OPEN region_list CLOSE
                                            {
                                                TRegion* Window=(TRegion*)malloc(sizeof(TRegion));
                                                Window->RegionType=rtVertical;
                                                Window->isFixed=1;
                                                Window->Dimension=$2;
                                                Window->RegionList=$4;
                                                $$=Window;
                                            }
        ;
%%
/*
 * Выдать сообщение об ошибке
 */
void yyerror(char* Message)
  {
    printf("YYE: %s\n",Message);
  }//yyerror
////////////////////////////////////////////////////////////////////////////////
/*
 * Пройтись по дереву и выдать его содержимое на экран
 */
void BrowseTree(TRegion* Region, unsigned short Prefix)
  {
    unsigned short f=0;
    TListCage* Cage=NULL;
    for(f=0;f<Prefix;++f)
        printf(" ");
    switch(Region->RegionType)
      {
        case rtWindow:
             printf("Window ");
             break;
        case rtVertical:
             printf("VerticalZone ");
             break;
        case rtHorizontal:
             printf("HorizontalZone ");
             break;
        default:
             printf("UnknownZone ");
             break;
      }//SWITCH
    printf("%d%c\n",Region->Dimension,(Region->isFixed)?'!':' ');
    for(Cage=Region->RegionList;Cage;Cage=Cage->Next)
      {
        BrowseTree(Cage->Region,Prefix+2);
      }//FOR
  }//BrowseTree
////////////////////////////////////////////////////////////////////////////////
/*
 * Освободить память, выделенную под данные
 */
void DeleteRegion(TRegion* Region)
  {
    unsigned short f=0;
    TListCage* Cage=Region->RegionList;
    TListCage* Next=NULL;
    while(Cage)
      {
        Next=Cage->Next;
        DeleteRegion(Cage->Region);
        free(Cage);
        Cage=Next;
      }//WHILE
    free(Region);
  }//BrowseTree
////////////////////////////////////////////////////////////////////////////////
void DeleteTree(TMonitor* Monitor)
  {
    while(Monitor)
      {
        TMonitor* Next=Monitor->Next;
        DeleteRegion(Monitor->Region);
        free(Monitor);
        Monitor=Next;
      }//WHILE
  }//DeleteTree
////////////////////////////////////////////////////////////////////////////////
