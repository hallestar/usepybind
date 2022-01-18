#ifndef TRYPYBIND_PYBROKER_H
#define TRYPYBIND_PYBROKER_H

#include <pybind11/pybind11.h>


#if(defined WIN32 || defined _WIN32) && defined LDIMPL
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif


// 管理pybind11定义的python解释器的
class EXPORT PyBindEnv {
public:
    enum ErrCode {
        kOk,

        kErrScriptPathNotFound,

        kErrInitialized,
        kErrNotInitialized,

        kErrRuntimeError,
    };

public:
    PyBindEnv();

    PyBindEnv(PyBindEnv &) = delete;

    ~PyBindEnv();

    ErrCode InitializeInterpreter();

    // 释放python解释器，
    ErrCode FinalizeInterpreter();

    // 初始化Python脚本路径, 目前只处理一个路径
    ErrCode SetupPythonPath() const;

private:
    ErrCode ParsePyExceptionToErrorCode(const pybind11::builtin_exception &) const;

private:

    bool is_initialize_;
};

// 初始化Python脚本路径, 目前只处理一个路径
EXPORT bool SetupPythonPath();


#endif //TRYPYBIND_PYBROKER_H
