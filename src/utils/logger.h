#pragma once

#include <string>

namespace tinyraytracer
{
    namespace Logger
    {
        void debug   (const std::string& m);
        void message (const std::string& m);
        void error   (const std::string& m);
    }
}
