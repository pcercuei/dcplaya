#
# Make exe plugins LAN driver
#
# (C) COPYRIGHT 2002 Ben(jamin) Gerard <ben@sasahipa.com>
#
#
# $Id: Makefile,v 1.1 2004/07/09 21:20:17 vincentp Exp $
#

LEZ=yes

LEF_EXTRA := 

KOS_LOCAL_CFLAGS += -DHOST_LITTLE_ENDIAN -DDCPLAYA=1

KOS_LOCAL_INCS += -iquote .. -iquote . -iquote ../../../../include -iquote ../../../../libs

OPTIMIZE = $(OPTIMIZE_FOR_SPEED)

TARGETS = lan.lez


include ../../../../Makefile.inc

