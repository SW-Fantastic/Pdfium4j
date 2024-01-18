cmake_minimum_required(VERSION 3.12)
project(PdfiumSDK)

set (CMAKE_CONFIGURATION_TYPES "Release")

link_directories("dependencies")
add_library(PdfiumSDK SHARED PDFBitmapImpl.c PDFDocumentImpl.c PDFPageImpl.c PDFPageObjectImpl.c PDFWriterImpl.cpp)
target_link_libraries(PdfiumSDK -lpdfium)
