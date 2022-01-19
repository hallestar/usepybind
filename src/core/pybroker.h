#ifndef TRYPYBIND_PYBROKER_H
#define TRYPYBIND_PYBROKER_H

#include <pybind11/pybind11.h>

#include "common.h"


#if(defined WIN32 || defined _WIN32) && defined LDIMPL
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

PYUTIL_NAMESPACE_BEGIN

// 管理pybind11定义的python解释器的
// 在调用任何python相关代码之前,须显示调用InitializeInterpreter进行解释器初始化
// 解释器的有两种释放方式
// 1. 退出当前作用域之后 会自动调用 FinalizeInterpreter
// 2. 手动 FinalizeInterpreter
// FinalizeInterpreter之后不能再调用任何python相关代码
class EXPORT PyBindEnv {
public:
    enum ErrCode {
        kOk,

        kErrScriptPathNotFound,

        kErrInitialized,
        kErrNotInitialized,

        kErrRuntimeError,

        kStopIteration,
        kIndexError,
        kKeyError,
        kValueError,
        kTypeError,
        kBufferError,
        kImportError,
        kAttributeError,
        kCastError,
        kReferenceCastError,
    };

public:
    explicit PyBindEnv();

    PyBindEnv(const PyBindEnv &) = delete;

    PyBindEnv(PyBindEnv &&other) noexcept {}

    PyBindEnv &operator=(const PyBindEnv &) = delete;

    PyBindEnv &operator=(PyBindEnv &&) = delete;

    ~PyBindEnv();

    // 初始化
    ErrCode InitializeInterpreter();

    // 结束python解释器，
    ErrCode FinalizeInterpreter();

    // 初始化Python脚本路径, 目前只处理一个路径
    ErrCode SetupPythonPath(const char *script_path) const;

    static bool IsOkError(ErrCode e) { return e == kOk; }

private:
    bool is_initialize_ = false;
};


#define CATCH_PY_EXEC                                                   \
    CATCH_PY_EXEC_TO_CODE(stop_iteration,          kStopIteration)      \
    CATCH_PY_EXEC_TO_CODE(index_error,             kIndexError)         \
    CATCH_PY_EXEC_TO_CODE(key_error,               kKeyError)           \
    CATCH_PY_EXEC_TO_CODE(value_error,             kValueError)         \
    CATCH_PY_EXEC_TO_CODE(type_error,              kTypeError)          \
    CATCH_PY_EXEC_TO_CODE(buffer_error,            kBufferError)        \
    CATCH_PY_EXEC_TO_CODE(import_error,            kImportError)        \
    CATCH_PY_EXEC_TO_CODE(attribute_error,         kAttributeError)     \
    CATCH_PY_EXEC_TO_CODE(cast_error,              kCastError)          \
    CATCH_PY_EXEC_TO_CODE(reference_cast_error,    kReferenceCastError)


#define CATCH_PY_EXEC_TO_CODE(exc, py_errno)        \
    catch (const py::exc& e) {                      \
        return PyBindEnv::py_errno;                 \
    }

PYUTIL_NAMESPACE_END

#endif //TRYPYBIND_PYBROKER_H
