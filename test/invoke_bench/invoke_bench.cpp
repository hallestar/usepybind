#include <stdlib.h>
#include <iostream>
//#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
#include <pybind11/pytypes.h>
#include "../../src/core/pybroker.h"
#include "../../src/core/util.h"

namespace py = pybind11;
using namespace pyutil;


//static void BM_StringCreation(benchmark::State& state) {
//    for (auto _ : state)
//        std::string empty_string;
//}
//// Register the function as a benchmark
//BENCHMARK(BM_StringCreation);
//
//// Define another benchmark
//static void BM_StringCopy(benchmark::State& state) {
//    std::string x = "hello";
//    for (auto _ : state)
//        std::string copy(x);
//}
//BENCHMARK(BM_StringCopy);
//
//BENCHMARK_MAIN();


class PyBindFixture : public benchmark::Fixture {
public:
    void SetUp(const ::benchmark::State& state) {
        if (!PyBindEnv::IsOkError(py_bind_env_.InitializeInterpreter())) {
            exit(EXIT_FAILURE);
            return;
        }

        const char *script_path = getenv("SCRIPT_PATH");
        auto py_err_no = py_bind_env_.SetupPythonPath(script_path);
        if (PyBindEnv::kOk != py_err_no) {
            exit(EXIT_FAILURE);
            return;
        }


    }

    void TearDown(const ::benchmark::State& state) {
        py_bind_env_.FinalizeInterpreter();
    }

    PyBindEnv py_bind_env_;
};

BENCHMARK_F(PyBindFixture, ImportModule)(::benchmark::State& st) {
    for (auto _ : st) {
        auto module_entry = py::module_::import("Entry");
    }
}

BENCHMARK_F(PyBindFixture, GetModuleAttr)(benchmark::State& st) {
        auto py_module_ = py::module_::import("Entry");
        auto py_func_ = py_module_.attr("empty_call");
        for (auto _ : st) {
            auto py_func_init_world = py_module_.attr("empty_call");
        }
}


BENCHMARK_F(PyBindFixture, CallEmptyFunction)(benchmark::State& st) {
    auto py_module_ = py::module_::import("Entry");
    auto py_func_ = py_module_.attr("empty_call");
    for (auto _ : st) {
        py_func_();
    }
}

BENCHMARK_F(PyBindFixture, GetVarFromPyBind)(benchmark::State& st) {
    auto py_module_ = py::module_::import("Entry");
    auto py_func_ = py_module_.attr("empty_call");
    auto py_func_get_val = py_module_.attr("get_test_var_for_export");
    for (auto _ : st) {
        auto res = py_func_get_val();
    }
}

BENCHMARK_MAIN();
