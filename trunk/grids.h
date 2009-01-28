#ifndef _________GRIDS___________H___
#define _________GRIDS___________H___

#include "common.h"
/*
 * Вспомогательные переменные и типы
 */
/*
 * Дробь = n/d
 */
typedef struct _tag_Value
  {
    int N,D;
  }TValue;
/*
 * Тип описания линейного преобразования
 * y=ax+b
 */
typedef struct _tag_Linear
  {
    TValue A,B;
  }TLinear;
/*
 * Преобразовать из целого числа в TValue
 */
TValue IntToTValue(int Value);
/*
 * Установить границы для региона и его подобластей
 */
void SetBorders(int Monitor, TRegion* Region,
                TLinear LeftDelta, TLinear Width,
                TLinear TopDelta,  TLinear Height
                );
/*
 * Сохранить разметку в файл
 */
void SaveGridToFile(const char* FileName);
#endif//_________GRIDS___________H___
