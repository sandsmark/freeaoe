#include "Utility.h"

#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#else
extern "C" {
#include <unistd.h>
}
#endif


bool util::openUrl(const std::__cxx11::string &url, std::__cxx11::string *error)
{
#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__)
    uintptr_t ret = reinterpret_cast<uintptr_t>(ShellExecuteA(nullptr, nullptr,
                                                              url.c_str(),
                                                              nullptr, nullptr, SW_SHOWNORMAL));
    if (ret <= 32) {
        if (error) {
            *error = "Windows doesn't have sane error stuff, so this is all we know: " + std::to_string(ret);
        }

        return false;
    }
#else
    // Again, this only handles "accidental" need for escaping, don't trust it for user input
    const std::string escapedUrl = "$'" + stringReplace(url, "'", "\'") + "'";
    const std::string command = "xdg-open " + escapedUrl;

    int ret = system(command.c_str());
    if (errno) {
        if (error) {
            *error = "Error: " + std::string(strerror(errno)) + "(" + std::to_string(ret) + ")";
        }

        return false;
    }
#endif
    return true;
}
