#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <filesystem>

#include <pybind11/stl.h>
#include <pybind11/eval.h>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/detail/common.h>

#include "pybroker.h"

namespace py = pybind11;


EXPORT bool InitPythonPath() {
    using namespace py::literals;
    const char *szScriptPath = getenv("SCRIPT_PATH");
    if (!szScriptPath) {
        return false;
    }

    auto sysModule = py::module_::import("sys");
    auto sysPath = sysModule.attr("path");
    auto append = sysPath.attr("append");
    append(szScriptPath);

    std::cout << szScriptPath << std::endl;

    return true;
}
