/* DO NOT EDIT THIS FILE - it is machine generated */
#include "jni.h"
/* Header for class org_swdc_pdfium_internal_PDFDocumentImpl */

#ifndef _Included_org_swdc_pdfium_internal_PDFDocumentImpl
#define _Included_org_swdc_pdfium_internal_PDFDocumentImpl
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    loadDocument
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_loadDocument
  (JNIEnv *, jclass, jstring);

/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    closeDocument
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_closeDocument
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    getPageCount
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_getPageCount
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    loadPage
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_loadPage
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    getMetadataText
 * Signature: (JLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_getMetadataText
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    getFirstBookMark
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_getFirstBookMark
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    getNextBookMark
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_getNextBookMark
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    getBookMarkPageIndex
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_getBookMarkPageIndex
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    getBookMarkTitle
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_getBookMarkTitle
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
