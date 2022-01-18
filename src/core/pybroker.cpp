#include <sstream>
#include <iostream>
#include <filesystem>

#include <pybind11/stl.h>
#include <pybind11/eval.h>
#include <pybind11/embed.h>

#include "pybroker.h"

namespace py = pybind11;


EXPORT bool SetupPythonPath() {
    const char *script_path = getenv("SCRIPT_PATH");
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

PyBindEnv::ErrCode PyBindEnv::SetupPythonPath() const {
    const char *script_path = getenv("SCRIPT_PATH");
    if (!script_path) {
        return kErrScriptPathNotFound;
    }

    try {
        auto sys_module = py::module_::import("sys");
        auto sys_path = sys_module.attr("path");
        auto append = sys_path.attr("append");
        append(script_path);
    } catch (py::builtin_exception &e) {
        return ParsePyExceptionToErrorCode(e);
    }

    return kOk;
}

PyBindEnv::ErrCode PyBindEnv::InitializeInterpreter() {
    if (is_initialize_) {
        return kErrInitialized;
    }

    try {
        py::initialize_interpreter();
        is_initialize_ = true;
    } catch (py::builtin_exception &e) {
        return ParsePyExceptionToErrorCode(e);
    }

    return kOk;
}

PyBindEnv::ErrCode PyBindEnv::FinalizeInterpreter() {
    if (!is_initialize_) {
        return kErrNotInitialized;
    }

    try {
        py::finalize_interpreter();
        is_initialize_ = false;
    } catch (py::builtin_exception &e) {
        return ParsePyExceptionToErrorCode(e);
    }

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

PyBindEnv::ErrCode PyBindEnv::ParsePyExceptionToErrorCode(const pybind11::builtin_exception &) const {

    stop_iteration
    index_error
    key_error
    value_error
    type_error
    buffer_error
    import_error
    attribute_error
    cast_error
    reference_cast_error



    return PyBindEnv::kErrRuntimeError;
}

