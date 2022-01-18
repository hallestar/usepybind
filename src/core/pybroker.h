#ifndef TRYPYBIND_PYBROKER_H
#define TRYPYBIND_PYBROKER_H


#if(defined WIN32|| defined _WIN32) && defined LDIMPL
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

EXPORT bool InitPythonPath();


#endif //TRYPYBIND_PYBROKER_H
