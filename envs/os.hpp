
#pragma once
#include <boost/predef.h>
#include <boost/filesystem.hpp>
#include <../template/singleton.hpp>

#if BOOST_OS_CYGWIN || BOOST_OS_LINUX || BOOST_OS_UNIX
    #define OS_POSIX
#elif BOOST_OS_WINDOWS
    #define OS_WINDOWS
#endif

#ifdef OS_REPORT_BUILDING_ENVIRONMENT
    #ifdef OS_WINDOWS
        #pragma message("build on windows")
    #endif

    #ifdef OS_POSIX
        #pragma message "build on posix"
    #endif
#endif

CONST_STATIC_STRING_EXP(directory_separator, boost::filesystem::path("/").make_preferred().native());

static void append_directory_separator(std::string& p)
{
    if(!p.empty() && p.back() != directory_separator())
        p.append(directory_separator());
}

