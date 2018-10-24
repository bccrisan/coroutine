// ---------------------------------------------------------------------------
//
//  Author
//      Park DongHa     | luncliff@gmail.com
//
// ---------------------------------------------------------------------------
#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "net.h"
#include <system_error>

namespace net::internal
{
WSADATA wsa{};
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) noexcept
{
    // Library Init
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        auto& data = net::internal::wsa;
        data = WSADATA{};

        // Version 2.2
        if (::WSAStartup(MAKEWORD(2, 2), std::addressof(data)))
            // WSASYSNOTREADY
            // WSAVERNOTSUPPORTED
            // WSAEINPROGRESS
            // WSAEPROCLIM
            // WSAEFAULT
            return FALSE;
    }
    // Library Release
    else if (fdwReason == DLL_PROCESS_DETACH)
    {
        ::WSACleanup();
    }

    return TRUE;
}
