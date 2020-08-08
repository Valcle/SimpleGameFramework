#pragma once

#if defined(_MSC_VER)
    #ifdef SGF_EXPORTS
        #define SGF_EXPORT __declspec(dllexport)
    #else
        #define SGF_EXPORT __declspec(dllimport)
    #endif
#else
    #define SGF_EXPORT
#endif