# Copyright (C) 2017 Quentin "Naccyde" Deslandes.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the LICENSE file distributed with yall.

macro(targetInfos targetName)
	message("==== Target : ${targetName}")

	if (NOT "${_PUB_OPT}${_PUB_OPT_DEB}${_PUB_OPT_REL}${_PVT_OPT}${_PVT_OPT_DEB}${_PVT_OPT_REL}${_IFA_OPT}${_IFA_OPT_DEB}${_IFA_OPT_REL}" STREQUAL "")
		message("====\tCompile options :")

		if (NOT "${_PUB_OPT}${_PUB_OPT_DEB}${_PUB_OPT_REL}" STREQUAL "")
			message("====\t\tPUBLIC : ")

			if (NOT "${_PUB_OPT}" STREQUAL "")
				message("====\t\t\tAll   : ${_PUB_OPT}")
			endif ()
			if (NOT "${_PUB_OPT_DEB}" STREQUAL "")
				message("====\t\t\tDebug   : ${_PUB_OPT_DEB}")
			endif ()
			if (NOT "${_PUB_OPT_REL}" STREQUAL "")
				message("====\t\t\tRelease  : ${_PUB_OPT_REL}")
			endif ()
		endif ()

		if (NOT "${_PVT_OPT}${_PVT_OPT_DEB}${_PVT_OPT_REL}" STREQUAL "")
			message("====\t\tPRIVATE : ")

			if (NOT "${_PVT_OPT}" STREQUAL "")
				message("====\t\t\tAll   : ${_PVT_OPT}")
			endif ()
			if (NOT "${_PVT_OPT_DEB}" STREQUAL "")
				message("====\t\t\tDebug   : ${_PVT_OPT_DEB}")
			endif ()
			if (NOT "${_PVT_OPT_REL}" STREQUAL "")
				message("====\t\t\tRelease  : ${_PVT_OPT_REL}")
			endif ()
		endif ()

		if (NOT "${_IFA_OPT}${_IFA_OPT_DEB}${_IFA_OPT_REL}" STREQUAL "")
			message("====\t\tPRIVATE : ")

			if (NOT "${_IFA_OPT}" STREQUAL "")
				message("====\t\t\tAll   : ${_IFA_OPT}")
			endif ()
			if (NOT "${_IFA_OPT_DEB}" STREQUAL "")
				message("====\t\t\tDebug   : ${_IFA_OPT_DEB}")
			endif ()
			if (NOT "${_IFA_OPT_REL}" STREQUAL "")
				message("====\t\t\tRelease  : ${_IFA_OPT_REL}")
			endif ()
		endif ()
	endif ()

	if (NOT "${_PUB_DEF}${_PUB_DEF_DEB}${_PUB_DEF_REL}${_PVT_DEF}${_PVT_DEF_DEB}${_PVT_DEF_REL}${_IFA_DEF}${_IFA_DEF_DEB}${_IFA_DEF_REL}" STREQUAL "")
		message("====\tCompile definitions :")

		if (NOT "${_PUB_DEF}${_PUB_DEF_DEB}${_PUB_DEF_REL}" STREQUAL "")
			message("====\t\tPUBLIC : ")

			if (NOT "${_PUB_DEF}" STREQUAL "")
				message("====\t\t\tAll   : ${_PUB_DEF}")
			endif ()
			if (NOT "${_PUB_DEF_DEB}" STREQUAL "")
				message("====\t\t\tDebug   : ${_PUB_DEF_DEB}")
			endif ()
			if (NOT "${_PUB_DEF_REL}" STREQUAL "")
				message("====\t\t\tRelease  : ${_PUB_DEF_REL}")
			endif ()
		endif ()

		if (NOT "${_PVT_DEF}${_PVT_DEF_DEB}${_PVT_DEF_REL}" STREQUAL "")
			message("====\t\tPRIVATE : ")

			if (NOT "${_PVT_DEF}" STREQUAL "")
				message("====\t\t\tAll   : ${_PVT_DEF}")
			endif ()
			if (NOT "${_PVT_DEF_DEB}" STREQUAL "")
				message("====\t\t\tDebug   : ${_PVT_DEF_DEB}")
			endif ()
			if (NOT "${_PVT_DEF_REL}" STREQUAL "")
				message("====\t\t\tRelease  : ${_PVT_DEF_REL}")
			endif ()
		endif ()

		if (NOT "${_IFA_DEF}${_IFA_DEF_DEB}${_IFA_DEF_REL}" STREQUAL "")
			message("====\t\tPRIVATE : ")

			if (NOT "${_IFA_DEF}" STREQUAL "")
				message("====\t\t\tAll   : ${_IFA_DEF}")
			endif ()
			if (NOT "${_IFA_DEF_DEB}" STREQUAL "")
				message("====\t\t\tDebug   : ${_IFA_DEF_DEB}")
			endif ()
			if (NOT "${_IFA_DEF_REL}" STREQUAL "")
				message("====\t\t\tRelease  : ${_IFA_DEF_REL}")
			endif ()
		endif ()
	endif ()

	if (NOT "${_PUB_INCDIR}${_PVT_INCDIR}${IFA_INCDIR}" STREQUAL "")
		message("====\tInclude directories :")

		if (NOT "${_PUB_INCDIR}" STREQUAL "")
			message("====\t\tPUBLIC    : ${_PUB_INCDIR}")
		endif ()

		if (NOT "${_PVT_INCDIR}" STREQUAL "")
			message("====\t\tPRIVATE   : ${_PVT_INCDIR}")
		endif ()

		if (NOT "${_IFA_INCDIR}" STREQUAL "")
			message("====\t\tINTERFACE : ${_IFA_INCDIR}")
		endif ()
	endif ()

	if (NOT "${_PUB_LINKLIB}${_PVT_LINKLIB}${IFA_LINKLIB}" STREQUAL "")
		message("====\tLink libraries :")

		if (NOT "${_PUB_LINKLIB}" STREQUAL "")
			message("====\t\tPUBLIC    : ${_PUB_LINKLIB}")
		endif ()

		if (NOT "${_PVT_LINKLIB}" STREQUAL "")
			message("====\t\tPRIVATE   : ${_PVT_LINKLIB}")
		endif ()

		if (NOT "${_IFA_LINKLIB}" STREQUAL "")
			message("====\t\tINTERFACE : ${_IFA_LINKLIB}")
		endif ()
	endif ()
endmacro()
