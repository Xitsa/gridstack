#include <stdio.h>
#include "common.h"
#include "grids.h"
/*
 * Описания мониторов
 */
TMonitor* Monitors=NULL;


/*
 * Главная программа
 */
int main(int argc, char** argv)
  {
    if(argc!=3)
      {
        printf("Use: GridStack input.stack output.grid\n");
      }//THEN
    else
      {
        int Token=0;
        InitParse(argv[1]);
        if(!yyparse())
          {
            TMonitor* Monitor=Monitors;
            for(;Monitor;Monitor=Monitor->Next)
              {
                TLinear LeftDelta, Width, TopDelta, Height;
                LeftDelta.A=IntToTValue(0);   LeftDelta.B=IntToTValue(0);
                TopDelta.A=IntToTValue(0);    TopDelta.B=IntToTValue(0);
                Width.A=IntToTValue(1);       Width.B=IntToTValue(0);
                Height.A=IntToTValue(1);      Height.B=IntToTValue(0);
                SetBorders(Monitor->Monitor,Monitor->Region, LeftDelta, Width, TopDelta, Height);
                //printf("Monitor %d\n",Monitor->Monitor);
                //BrowseTree(Monitor->Region,2);
              }
          }//THEN
        FinishParse();
        SaveGridToFile(argv[2]);
        DeleteTree(Monitors);
      }//ELSE
  }//main
////////////////////////////////////////////////////////////////////////////////
