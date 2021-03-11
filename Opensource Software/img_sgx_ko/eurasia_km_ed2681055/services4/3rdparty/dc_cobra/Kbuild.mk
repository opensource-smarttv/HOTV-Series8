# Copyright	2010 Imagination Technologies Limited. All rights reserved.
#
# No part of this software, either material or conceptual may be
# copied or distributed, transmitted, transcribed, stored in a
# retrieval system or translated into any human or computer
# language in any form by any means, electronic, mechanical,
# manual or other-wise, or disclosed to third parties without
# the express written permission of: Imagination Technologies
# Limited, HomePark Industrial Estate, Kings Langley,
# Hertfordshire, WD4 8LZ, UK
#
# $Log: Kbuild.mk $
#

ccflags-y += \
 -I$(TOP)/services4/3rdparty/dc_cobra 

dc_cobra-y += \
	services4/3rdparty/dc_cobra/dc_cobra_displayclass.o \
	services4/3rdparty/dc_cobra/dc_cobra_linux.o \
	services4/3rdparty/dc_cobra/dc_cobra_osk.o \
	services4/3rdparty/dc_cobra/dc_cobra_util.o
