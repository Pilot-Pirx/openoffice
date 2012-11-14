#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2000, 2011 Oracle and/or its affiliates.
#
# OpenOffice.org - a multi-platform office productivity suite
#
# This file is part of OpenOffice.org.
#
# OpenOffice.org is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License version 3
# only, as published by the Free Software Foundation.
#
# OpenOffice.org is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License version 3 for more details
# (a copy is included in the LICENSE file that accompanied this code).
#
# You should have received a copy of the GNU Lesser General Public License
# version 3 along with OpenOffice.org.  If not, see
# <http://www.openoffice.org/license.html>
# for a copy of the LGPLv3 License.
#
#*************************************************************************
ifeq ($(GUI),WNT)

$(eval $(call gb_Executable_Executable,odbcconfig))

$(eval $(call gb_Executable_set_targettype_gui,odbcconfig,YES))

$(eval $(call gb_Executable_add_api,odbcconfig,\
	udkapi \
	offapi \
))

$(eval $(call gb_Executable_set_include,odbcconfig,\
	$$(INCLUDE) \
	-I$(WORKDIR)/inc/ \
	-I$(OUTDIR)/inc/ \
	-I$(SRCDIR)/dbaccess/inc \
	-I$(SRCDIR)/dbaccess/inc/dbaccess \
	-I$(SRCDIR)/dbaccess/inc/pch \
))

$(eval $(call gb_Executable_add_linked_libs,odbcconfig,\
	sal \
	stl \
	tl \
	vcl \
	vos3 \
	user32 \
	$(gb_STDLIBS) \
))

$(eval $(call gb_Executable_add_exception_objects,odbcconfig,\
	dbaccess/win32/source/odbcconfig/odbcconfig \
))

endif
# vim: set noet sw=4 ts=4:
