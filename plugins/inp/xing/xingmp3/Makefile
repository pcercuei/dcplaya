# $Id: Makefile,v 1.3 2002-09-12 17:57:31 ben Exp $

LIBRARY=yes

OBJS = cdct.o csbt.o cup.o cupl3.o
OBJS += cwinm.o dec8.o hwin.o icdct.o isbt.o
OBJS += iup.o iwinm.o l3dq.o l3init.o
OBJS += mdct.o mhead.o msis.o uph.o upsf.o

OPTIMIZE 		= $(OPTIMIZE_FOR_SPEED)
KOS_LOCAL_CFLAGS 	= -DLITTLE_ENDIAN=1
KOS_LOCAL_INCS		= -iquote . -iquote ../include 

include ../../../../Makefile.inc
