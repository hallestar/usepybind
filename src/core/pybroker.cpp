#include <sstream>
#include <iostream>
#include <filesystem>

#include <pybind11/stl.h>
#include <pybind11/eval.h>
#include <pybind11/embed.h>

#include "pybroker.h"
#include "util.h"

namespace py = pybind11;

PYUTIL_NAMESPACE_BEGIN


EXPORT bool SetupPythonPath(const char *script_path) {
    if (!script_path) {
        return false;
    }

    try {
        auto sys_module = py::module_::import("sys");
        auto sys_path = sys_module.attr("path");
        auto append = sys_path.attr("append");
        append(script_path);
    } catch (py::builtin_exception &e) {
        return false;
    }

    return true;
}

PyBindEnv::ErrCode PyBindEnv::SetupPythonPath(const char *script_path) const {
    if (!script_path) {
        return kErrScriptPathNotFound;
    }

    try {
        auto sys_module = py::module_::import("sys");
        auto sys_path = sys_module.attr("path");
        auto append = sys_path.attr("append");
        append(script_path);
    } CATCH_PY_EXEC

    return kOk;
}

PyBindEnv::ErrCode PyBindEnv::InitializeInterpreter() {
    if (is_initialize_) {
        return kErrInitialized;
    }

    try {
        py::initialize_interpreter();
        is_initialize_ = true;
    } CATCH_PY_EXEC

    return kOk;
}

PyBindEnv::ErrCode PyBindEnv::FinalizeInterpreter() {
    if (!is_initialize_) {
        return kErrNotInitialized;
    }

    try {
        py::finalize_interpreter();
        is_initialize_ = false;
    } CATCH_PY_EXEC

    return kOk;
}

PyBindEnv::~PyBindEnv() {
    if (is_initialize_) {
        FinalizeInterpreter();
    }
}

PyBindEnv::PyBindEnv()
        : is_initialize_(false) {
}


PYUTIL_NAMESPACE_END
