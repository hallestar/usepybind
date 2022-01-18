#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "../../src/core/pybroker.h"
#include "../../src/core/util.h"

namespace py = pybind11;

int main() {
    PyBindEnv py_bind_env;
    if (!PyBindEnv::IsOkError(py_bind_env.InitializeInterpreter())) {
        std::cout << "py bind env init failed!" << std::endl;
        return 1;
    }

    const char *script_path = getenv("SCRIPT_PATH");
    auto py_err_no = py_bind_env.SetupPythonPath(script_path);
    if (PyBindEnv::kOk != py_err_no) {
        printf("setup python path failed! err_no=%d", py_err_no);
        return 1;
    }

    try {

        auto module_entry = py::module_::import("Entry");
        auto py_func_init_world = module_entry.attr("init_world");
        py_func_init_world();
        auto py_run_script = module_entry.attr("run_script");
        auto res = py_run_script("from Entry import gworld\nr=gworld");
        if (res.is(py::none())) {
            return 1;
        }

        std::cout << res.get_type().attr("__class__").attr("__name__").cast<std::string>() << std::endl;

        {
            auto py_world = module_entry.attr("gworld");
            for (int i = 0; i < 1000; ++i) {
                py_world.attr("update")();
            }
        }
    } catch (py::builtin_exception &e) {
        std::cerr << "raise py builtin exception" << e.what() << std::endl;

    } catch (py::error_already_set &e) {
        std::cerr << "raise py exception" << e.what() << std::endl;
    }

    return 0;
}