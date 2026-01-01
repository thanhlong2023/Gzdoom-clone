#include "core/Log.h"

#include <filesystem>
#include <string_view>

int main(int argc, char* argv[])
{
    constexpr std::string_view kVersion = "gzclone v0.1.0";
    LogInfo("Version: %s", kVersion.data());

    const auto cwd = std::filesystem::current_path();
    LogInfo("CWD: %s", cwd.string().c_str());

    LogInfo("Arguments (%d):", argc);
    for (int i = 0; i < argc; ++i)
    {
        LogInfo("  argv[%d]: %s", i, argv[i]);
    }

    return 0;
}
