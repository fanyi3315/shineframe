#pragma once

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#define SHINE_OS_WINDOWS
#define SHINE_OS "WINDOWS"
#ifdef _WIN64
//define something for Windows (64-bit only)
#else
//define something for Windows (32-bit only)
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#define SHINE_OS_IOS_SIMULATOR
#define SHINE_OS "IOS_SIMULATOR"
#elif TARGET_OS_IPHONE
// iOS device
#define SHINE_OS_IOS_PHONE
#define SHINE_OS "IOS_PHONE"
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#define SHINE_OS_MAC
#define SHINE_OS "MAC"
#else
#   error "Unknown Apple platform"
#endif
#elif __ANDROID__
// android
#define SHINE_OS_ANDROID
#define SHINE_OS "ANDROID"
#elif __linux__
// linux
#define SHINE_OS_LINUX
#define SHINE_OS "LINUX"
#elif __unix__ // all unices not caught above
// Unix
#define SHINE_OS_UNIX
#define SHINE_OS "UNIX"
#elif defined(_POSIX_VERSION)
// POSIX
#define SHINE_OS_POSIX "POSIX"
#define SHINE_OS "POSIX"
#else
#   error "Unknown compiler"
#endif

#include <iostream>
namespace shine
{
    typedef char int8;
    typedef unsigned char  uint8;
    typedef short  int16;
    typedef unsigned short  uint16;
    typedef int  int32;
    typedef unsigned int  uint32;
    typedef long  Long;
    typedef unsigned long  uLong;
    typedef long long  int64;
    typedef unsigned long long  uint64;

    typedef std::size_t size_t;
    typedef size_t size_type;

}

#define MACRO_EMPTY

#define SHINE_GEN_MEMBER_GET_METHOD(type, name, ...) public: \
    inline type& get_##name() { return _##name; } \
    inline const type& get_##name() const { return _##name; }

#define SHINE_GEN_MEMBER_SET_METHOD(type, name, prefix, ...) public: \
    template<typename T> \
    inline void prefix##_##name(const T &val) { _##name = val; } \
    template<typename T> \
    inline void prefix##_##name(T &&val) { _##name = val; }

#define SHINE_GEN_MEMBER_BODY(type, name, ...) protected: \
    type _##name  __VA_ARGS__;

#define SHINE_GEN_MEMBER_GETSET(type, name, ...) SHINE_GEN_MEMBER_GET_METHOD(type, name); \
    SHINE_GEN_MEMBER_SET_METHOD(type, name, set); \
    SHINE_GEN_MEMBER_BODY(type, name, __VA_ARGS__);

#define SHINE_GEN_MEMBER_GETREG(type, name, ...) SHINE_GEN_MEMBER_GET_METHOD(type, name); \
    SHINE_GEN_MEMBER_SET_METHOD(type, name, register); \
    SHINE_GEN_MEMBER_BODY(type, name, __VA_ARGS__);

#define SHINE_GEN_MEMBER_GET_ONLY(type, name, ...) SHINE_GEN_MEMBER_GET_METHOD(type, name); \
    SHINE_GEN_MEMBER_BODY(type, name, __VA_ARGS__);
