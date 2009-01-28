#ifndef  _______GRIDSTACKCOMMON____H__
#define  _______GRIDSTACKCOMMON____H__




#ifdef __cplusplus
extern "C"{
#endif

/*
 * Типы регионов
 */
typedef enum _tag_RegionType
  {
    rtWindow,
    rtVertical,
    rtHorizontal
  }TRegionType;

/*
 * Элемент списка регионов
 */
struct _tag_Region;
typedef struct _tag_ListCage
  {
    struct _tag_Region* Region;
    struct _tag_ListCage* Next;
  }TListCage;
/*
 * Регион экрана
 */
typedef struct _tag_Region
  {
    TRegionType RegionType;
    unsigned short isFixed; //Признак того, что это абсолютная величина
    int Dimension;          //Изменяемая размерность
    TListCage* RegionList;  //Список регионов
  }TRegion;
/*
 * Описание монитора
 */
typedef struct _tag_Monitor
  {
    TRegion* Region;
    int Monitor;
    struct _tag_Monitor* Next;
  }TMonitor;
/*
 * Описания мониторов
 */
extern TMonitor* Monitors;
/*
 * Открыть указанный файл для разбора
 */
void InitParse(char* FileName);
/*
 * Закрыть файл разбора
 */
void FinishParse(void);
/*
 * Главная функция сканера
 */
int yylex( void );
/*
 * Главная функция разборщика
 */
int yyparse (void);
/*
 * Выдать сообщение об ошибке
 */
void yyerror(char* Message);
/*
 * Пройтись по дереву и выдать его содержимое на экран
 */
void BrowseTree(TRegion* Region, unsigned short Prefix);
/*
 * Освободить память, выделенную под данные
 */
void DeleteTree(TMonitor* Monitor);
#ifdef __cplusplus
}
#endif


#endif //_______GRIDSTACKCOMMON____H__
