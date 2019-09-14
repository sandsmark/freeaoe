#include "Utility.h"

#include "Logger.h"

#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#else
extern "C" {
#include <unistd.h>
}
#endif


bool util::openUrl(const std::string &url, std::string *error)
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

#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__)
static std::string wintendoExePath()
{
    std::vector<CHAR> pathBuf;
    DWORD ret;
    do {
        pathBuf.resize(pathBuf.size() + MAX_PATH);
        ret = GetModuleFileName(NULL, pathBuf.data(), DWORD(pathBuf.size()));

        // Windows APIs are a special kind of retarded, 0 means it failed
        if (ret == 0) {
            WARN << "Failed to query wintendo exe path";
            return {};
        }
    } while(ret >= pathBuf.size());

    return std::string(pathBuf.data(), ret);
//    return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t>{}.to_bytes(std::wstring(pathBuf, ret));
}
#else
static std::string procExePath()
{
    const std::string path = "/proc/" + std::to_string(getpid()) + "/exe";
    if (!std::filesystem::is_symlink(path)) {
        WARN << path << "is not a valid symlink";
        return {};
    }

    return std::filesystem::read_symlink(path);
}
#endif



std::string util::executablePath()
{
    std::string path;
#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__)
    path = wintendoExePath();
#else
    path = procExePath();
#endif
    if (path.empty()) {
        WARN << "Failed to resolve executable path";
        path = std::filesystem::current_path().string();
    }

    return path;
}
