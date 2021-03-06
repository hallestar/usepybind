#include <stdlib.h>
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

#include "../../src/core/pybroker.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)


namespace py = pybind11;

using namespace pyutil;

static std::string GetEntryPath(const char *scriptDir) {
    auto script_dir = std::filesystem::path(scriptDir);
    script_dir.append("Entry.py");
    return script_dir.string();
}

void PrintSeperator(const char szSep = '-') {
    std::ostringstream oss;
    for (int i = 0; i < 80; i++) {
        oss << szSep;
    }

    std::cout << oss.str() << std::endl;
}

void PrintList(const std::vector<uint32_t> &vec) {
    for (auto v : vec) {
        std::cout << v << std::endl;
    }
}

void PrintDict(const std::map<uint32_t, uint32_t> &dict) {
    for (const auto &pair : dict) {
        std::cout << "K: " << pair.first << " V: " << pair.second << std::endl;
    }
}


class Npc {
public:
    Npc(std::string &&name, uint32_t lv)
            : _name(name),
              _level(lv) {
    }

    const std::string &GetName() const {
        return _name;
    }

    void SetName(std::string &&name) {
        _name = std::move(name);
    }

    uint32_t GetLevel() const {
        return _level;
    }

    void SetLevel(uint32_t lv) {
        _level = lv;
    }

    std::string Repr() const {
        std::ostringstream oss;
        oss << "Name: " << _name << " Level: " << _level << std::endl;
        return oss.str();
    }

private:
    std::string _name;
    uint32_t _level;
};

PYBIND11_EMBEDDED_MODULE(tester, m) {
    m.doc() = "pybind11 tester";
    m.def("print_list", &PrintList, "A function print all elements");
    m.def("print_dict", &PrintDict, "A function print all elements");

    py::class_<Npc>(m, "CNpc")
            .def(py::init<std::string, uint32_t>())
            .def("get_level", &Npc::GetLevel)
            .def("set_level", &Npc::SetLevel)
            .def("get_name", &Npc::GetName)
            .def("set_name", &Npc::SetName)
            .def("__repr__", &Npc::Repr)
            .def(py::pickle(
                    [](const Npc &npc) { // __getstate__
                        return py::make_tuple(npc.GetName(), npc.GetLevel());
                    },
                    [](py::tuple t) { // __setstate__
                        if (t.size() < 2) {
                            throw std::runtime_error("invalid arguments!");
                        }

                        Npc p(t[0].cast<std::string>(), t[1].cast<uint32_t>());
                        return p;
                    }
            ));
}

//class Attr {
//public:
//    Attr& attr(const char* szAttrName) {
//        return *this;
//    }
//
//    template<typename ...Args>
//    void operator [](Args &&...args) {
//    }
//
//private:
//};


int main() {
    using namespace py::literals;
    PyBindEnv py_bind_env;
    if (!PyBindEnv::IsOkError(py_bind_env.InitializeInterpreter())) {
        std::cout<< "py bind env init failed!" << std::endl;
        return 1;
    }

    try {
        const char *script_path = getenv("SCRIPT_PATH");
        auto py_err_no = py_bind_env.SetupPythonPath(script_path);
        if (!PyBindEnv::IsOkError(py_err_no)) {
            printf("init python path failed! py_err_no=%d\n", py_err_no);
            return 1;
        }

        {
            PrintSeperator();
            auto test_list_func= []() {
                auto py_module = py::module_::import("Entry");
                auto py_func = py_module.attr("print_vector");
                py_func();
            };
            test_list_func();
        }

        {
            PrintSeperator();
            auto test_dict_func = []() {
                auto py_module = py::module_::import("Entry");
                auto py_func = py_module.attr("print_dict");
                py_func();
            };
            test_dict_func();
        }

        {
            PrintSeperator();
            auto func = []() {
                auto py_module = py::module_::import("Entry");
                auto py_func = py_module.attr("python_call_cpp_print_list");
                py_func(std::vector<uint32_t>({11000, 2000}));
                py_func(std::vector<float>({0.12312323, 123123.123}));
            };
            func();
        }

        {
            PrintSeperator();
            auto func = []() {
                auto py_module = py::module_::import("Entry");
                auto py_func = py_module.attr("python_call_cpp_print_dict");
                py_func(std::map<uint32_t, uint32_t>(
                        {
                                {11000, 100},
                                {22222, 400000},
                        }));
                py_func(std::map<std::string, std::string>(
                        {
                                {"kaaaaaaaaa", "kbbbbbbbbb"},
                                {"kccccccccc", "kddddddddd"}
                        }));
                auto pydict = py::dict("obj_name"_a = "name", "obj_cnt"_a = 100);
                py_func(pydict);
            };
            func();
        }

        {
            PrintSeperator();
            auto func = []() {
                auto py_module = py::module_::import("Entry");
                auto py_func_change_npc_prop = py_module.attr("change_npc_property");
                auto npc_data = py_func_change_npc_prop();
                auto py_func_load_npc = py_module.attr("load_npc_from_bytes");
                py_func_load_npc(npc_data);
            };
            func();
        }
    } catch (py::error_already_set &e) {
        std::cerr << "raise py exception" << e.what() << std::endl;
    } catch (py::builtin_exception &e) {
        std::cerr << "raise py builtin exception" << e.what() << std::endl;
    }

    return 0;
}