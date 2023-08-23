#ifndef C_PDFIUM
#define C_PDFIUM


#include "external/pdfium/include/fpdf_doc.h"
#include "external/pdfium/include/fpdf_edit.h"
#include "external/pdfium/include/fpdfview.h"

#ifdef _WIN32

    #pragma comment(lib, "pdfium.dll.lib")

    #include <Windows.h>
    #include <uchar.h>
    #include "external/windows/jni.h"


    #define API_EXPORT extern "C" __declspec(dllexport)

#elif __APPLE__

    #include <stdio.h>
    #include <dlfcn.h>
    #include "external/osx/jni.h"

    #define char16_t uint16_t
    #define API_EXPORT extern "C"

#endif

#endif