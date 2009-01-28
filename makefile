TARGET  = GridStack

CFLAGS  = /D "__STDC__=1" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /EHsc /GR /W3 /nologo /c /Wp64 

!ifdef  RELEASE
ODIR    = Release
LFLAGS  = /OUT:"Release/GridStack_test.exe" /INCREMENTAL:NO /NOLOGO /DEBUG /PDB:"Release/GridStack.pdb" /SUBSYSTEM:CONSOLE /OPT:REF /OPT:ICF /MACHINE:X86   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib
CFLAGS  = $(CFLAGS) /O2 /G7 /D "NDEBUG" /FD /ML /GS    /Fo"Release/" /Fd"Release/vc70.pdb" /Zi 
!else
ODIR    = Debug
LFLAGS  = /OUT:"Debug/GridStack.exe" /INCREMENTAL /NOLOGO /DEBUG /PDB:"Debug/GridStack.pdb" /SUBSYSTEM:CONSOLE /MACHINE:X86   kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib
CFLAGS  = $(CFLAGS) /Od     /D "_DEBUG" /Gm /RTC1 /MLd /Fo"Debug/"   /Fd"Debug/vc70.pdb"   /ZI 
!endif

.cpp{$(ODIR)}.obj::
    $(CC) $(CFLAGS) /TP /YX"stdafx.h" /Fp$(ODIR)/SQLite_test.pch $<

.c{$(ODIR)}.obj::
    $(CC) $(CFLAGS) /TC $<

OBJS    = \
    $(ODIR)\GridStack.tab.obj\
    $(ODIR)\lex.yy.obj\
    $(ODIR)\Grids.obj\
    $(ODIR)\main.obj

all: $(ODIR)\$(TARGET).exe

$(ODIR):
    @-mkdir $(ODIR)

$(ODIR)\$(TARGET).exe: $(ODIR) $(OBJS)
    link $(LFLAGS) $(OBJS)
