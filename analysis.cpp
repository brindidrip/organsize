#include "analysis.h"

Analysis::Analysis(int tag)
{
#ifdef _WIN32
   //define something for Windows (32-bit and 64-bit, this part is common)
   #ifdef _WIN64
      //define something for Windows (64-bit only)
      machine_platform = WIN64;
   #else
      //define something for Windows (32-bit only)
      machine_platform = WIN32;
   #endif
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    // linux
    machine_platform = LINUX;
#elif __unix__ // all unices not caught above
    // Unix
    machine_platform = UNIX;
#elif defined(_POSIX_VERSION)
    // POSIX
    machine_platform = POSIX;
#else
#   error "Unknown compiler"
#endif
}

Analysis::~Analysis(){}