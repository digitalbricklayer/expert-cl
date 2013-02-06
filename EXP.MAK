PROJ = EXP
PROJFILE = EXP.MAK
DEBUG = 1

PWBRMAKE  = pwbrmake
NMAKEBSC1  = set
NMAKEBSC2  = nmake
BRFLAGS  =  /o $(PROJ).bsc /Iu
BROWSE	= 1
CFLAGS_G  = /AH /W2 /BATCH /FR$*.sbr
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
BIND  = bind
RC  = rc
IMPLIB	= implib
LFLAGS_G  = /NOI /BATCH
LFLAGS_D  = /CO /INC /FAR /PACKC
LFLAGS_R  = /EXE /FAR /PACKC
MAPFILE_D  = NUL
MAPFILE_R  = NUL
CC  = cl
CFLAGS_D  = /qc /Gi$(PROJ).mdt /Zr /Zi /Od
CFLAGS_R  = /Ot /Oi /Ol /Oe /Og /Gs
ASM  = masm
AFLAGS_G  = /Mx /T
AFLAGS_D  = /Zi
RUNFLAGS  = animals.dat

OBJS  = EXP.obj AGENDA.obj BREADTH.obj DATA_BAS.obj D_BASE.obj ERROR.obj\
	FORWARD.obj HOW_WHY.obj PARSE.obj QUESTION.obj Q_BASE.obj R_BASE.obj\
	USER_INT.obj

all: $(PROJ).exe

.SUFFIXES: .c .obj

EXP.obj : EXP.C expert.h C:\C600\INCLUDE\stdio.h C:\C600\INCLUDE\string.h

AGENDA.obj : AGENDA.C expert.h C:\C600\INCLUDE\stdio.h\
	C:\C600\INCLUDE\string.h

BREADTH.obj : BREADTH.C expert.h C:\C600\INCLUDE\stdio.h\
	C:\C600\INCLUDE\string.h

DATA_BAS.obj : DATA_BAS.C expert.h C:\C600\INCLUDE\stdio.h\
	C:\C600\INCLUDE\string.h

D_BASE.obj : D_BASE.C expert.h C:\C600\INCLUDE\stdio.h\
	C:\C600\INCLUDE\string.h

ERROR.obj : ERROR.C expert.h C:\C600\INCLUDE\stdio.h C:\C600\INCLUDE\string.h

FORWARD.obj : FORWARD.C expert.h C:\C600\INCLUDE\stdio.h\
	C:\C600\INCLUDE\string.h

HOW_WHY.obj : HOW_WHY.C expert.h C:\C600\INCLUDE\stdio.h\
	C:\C600\INCLUDE\string.h

PARSE.obj : PARSE.C expert.h C:\C600\INCLUDE\stdio.h C:\C600\INCLUDE\string.h

QUESTION.obj : QUESTION.C expert.h C:\C600\INCLUDE\graph.h\
	C:\C600\INCLUDE\stdio.h C:\C600\INCLUDE\string.h

Q_BASE.obj : Q_BASE.C expert.h C:\C600\INCLUDE\stdio.h\
	C:\C600\INCLUDE\string.h

R_BASE.obj : R_BASE.C expert.h C:\C600\INCLUDE\stdio.h\
	C:\C600\INCLUDE\string.h

USER_INT.obj : USER_INT.C C:\C600\INCLUDE\graph.h expert.h\
	C:\C600\INCLUDE\stdio.h C:\C600\INCLUDE\string.h


$(PROJ).bsc : 

$(PROJ).exe : $(OBJS)
!IF $(DEBUG)
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_D)
$(LLIBS_G: = +^
) +
$(LLIBS_D: = +^
) +
$(LIBS: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_D);
<<
!ELSE
	$(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_R)
$(LLIBS_G: = +^
) +
$(LLIBS_R: = +^
) +
$(LIBS: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_R);
<<
!ENDIF
!IF $(DEBUG)
	$(ILINK) -a -e "$(LINKER) @$(PROJ).lrf" $@
!ELSE
	$(LINKER) @$(PROJ).lrf
!ENDIF
	$(NMAKEBSC1) MAKEFLAGS=
	$(NMAKEBSC2) $(NMFLAGS) -f $(PROJFILE) $(PROJ).bsc


.c.obj :
!IF $(DEBUG)
	$(CC) /c $(CFLAGS_G) $(CFLAGS_D) /Fo$@ $<
!ELSE
	$(CC) /c $(CFLAGS_G) $(CFLAGS_R) /Fo$@ $<
!ENDIF


run: $(PROJ).exe
	$(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
	CV $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
