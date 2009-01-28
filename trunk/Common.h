#ifndef  _______GRIDSTACKCOMMON____H__
#define  _______GRIDSTACKCOMMON____H__




#ifdef __cplusplus
extern "C"{
#endif

/*
 * ���� ॣ�����
 */
typedef enum _tag_RegionType
  {
    rtWindow,
    rtVertical,
    rtHorizontal
  }TRegionType;

/*
 * ������� ᯨ᪠ ॣ�����
 */
struct _tag_Region;
typedef struct _tag_ListCage
  {
    struct _tag_Region* Region;
    struct _tag_ListCage* Next;
  }TListCage;
/*
 * ������ �࠭�
 */
typedef struct _tag_Region
  {
    TRegionType RegionType;
    unsigned short isFixed; //�ਧ��� ⮣�, �� �� ��᮫�⭠� ����稭�
    int Dimension;          //�����塞�� ࠧ��୮���
    TListCage* RegionList;  //���᮪ ॣ�����
  }TRegion;
/*
 * ���ᠭ�� ������
 */
typedef struct _tag_Monitor
  {
    TRegion* Region;
    int Monitor;
    struct _tag_Monitor* Next;
  }TMonitor;
/*
 * ���ᠭ�� �����஢
 */
extern TMonitor* Monitors;
/*
 * ������ 㪠����� 䠩� ��� ࠧ���
 */
void InitParse(char* FileName);
/*
 * ������� 䠩� ࠧ���
 */
void FinishParse(void);
/*
 * ������� �㭪�� ᪠���
 */
int yylex( void );
/*
 * ������� �㭪�� ࠧ���騪�
 */
int yyparse (void);
/*
 * �뤠�� ᮮ�饭�� �� �訡��
 */
void yyerror(char* Message);
/*
 * �ன��� �� ��ॢ� � �뤠�� ��� ᮤ�ন��� �� �࠭
 */
void BrowseTree(TRegion* Region, unsigned short Prefix);
/*
 * �᢮������ ������, �뤥������ ��� �����
 */
void DeleteTree(TMonitor* Monitor);
#ifdef __cplusplus
}
#endif


#endif //_______GRIDSTACKCOMMON____H__
