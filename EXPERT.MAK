PROJ = EXPERT
PROJFILE = EXPERT.MAK
DEBUG = 0

PWBRMAKE  = pwbrmake
NMAKEBSC1  = set
NMAKEBSC2  = nmake
BRFLAGS  = /o $(PROJ).bsc /Iu
CFLAGS_G  = /AL /W2 /BATCH /FR$*.sbr
BROWSE	= 1
LINKER	= link
ILINK  = ilink
LRF  = echo > NUL
BIND  = bind
RC  = rc
IMPLIB	= implib
LFLAGS_G  = /NOI  /BATCH
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

OBJS  = EXP.obj AGENDA.obj BREADTH.obj DATA_BAS.obj ERROR.obj D_BASE.obj\
	GINOS.obj FORWARD.obj HOW_WHY.obj QUESTION.obj Q_BASE.obj USER_INT.obj\
	R_BASE.obj

all: $(PROJ).exe

.SUFFIXES: .c .obj

EXP.obj : EXP.C expert.h C:\C600\INCLUDE\stdio.h C:\C600\INCLUDE\string.h

AGENDA.obj : AGENDA.C

BREADTH.obj : BREADTH.C

DATA_BAS.obj : DATA_BAS.C

ERROR.obj : ERROR.C

D_BASE.obj : D_BASE.C

GINOS.obj : GINOS.C

FORWARD.obj : FORWARD.C

HOW_WHY.obj : HOW_WHY.C

QUESTION.obj : QUESTION.C

Q_BASE.obj : Q_BASE.C

USER_INT.obj : USER_INT.C

R_BASE.obj : R_BASE.C


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
