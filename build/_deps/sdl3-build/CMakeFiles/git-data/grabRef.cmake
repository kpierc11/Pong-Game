#
# Internal file for GetGitRevisionDescription.cmake
#
# Requires CMake 2.6 or newer (uses the 'function' command)
#
# Original Author:
# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu> <abiryan@ryand.net>
# http://academic.cleardefinition.com
# Iowa State University HCI Graduate Program/VRAC
#
# Copyright 2009-2012, Iowa State University
# Copyright 2011-2015, Contributors
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
# SPDX-License-Identifier: BSL-1.0

set(HEAD_HASH)

file(READ "C:/Users/Kaleb/Documents/GitHub/Pong-Game/build/_deps/sdl3-build/CMakeFiles/git-data/HEAD" HEAD_CONTENTS LIMIT 1024)

string(STRIP "${HEAD_CONTENTS}" HEAD_CONTENTS)
if(HEAD_CONTENTS MATCHES "ref")
	# named branch
	string(REPLACE "ref: " "" HEAD_REF "${HEAD_CONTENTS}")
	if(EXISTS "C:/Users/Kaleb/Documents/GitHub/Pong-Game/build/_deps/sdl3-src/.git/${HEAD_REF}")
		configure_file("C:/Users/Kaleb/Documents/GitHub/Pong-Game/build/_deps/sdl3-src/.git/${HEAD_REF}" "C:/Users/Kaleb/Documents/GitHub/Pong-Game/build/_deps/sdl3-build/CMakeFiles/git-data/head-ref" COPYONLY)
	else()
		configure_file("C:/Users/Kaleb/Documents/GitHub/Pong-Game/build/_deps/sdl3-src/.git/packed-refs" "C:/Users/Kaleb/Documents/GitHub/Pong-Game/build/_deps/sdl3-build/CMakeFiles/git-data/packed-refs" COPYONLY)
		file(READ "C:/Users/Kaleb/Documents/GitHub/Pong-Game/build/_deps/sdl3-build/CMakeFiles/git-data/packed-refs" PACKED_REFS)
		if(${PACKED_REFS} MATCHES "([0-9a-z]*) ${HEAD_REF}")
			set(HEAD_HASH "${CMAKE_MATCH_1}")
		endif()
	endif()
else()
	# detached HEAD
	configure_file("C:/Users/Kaleb/Documents/GitHub/Pong-Game/build/_deps/sdl3-src/.git/HEAD" "C:/Users/Kaleb/Documents/GitHub/Pong-Game/build/_deps/sdl3-build/CMakeFiles/git-data/head-ref" COPYONLY)
endif()

if(NOT HEAD_HASH)
	file(READ "C:/Users/Kaleb/Documents/GitHub/Pong-Game/build/_deps/sdl3-build/CMakeFiles/git-data/head-ref" HEAD_HASH LIMIT 1024)
	string(STRIP "${HEAD_HASH}" HEAD_HASH)
endif()
