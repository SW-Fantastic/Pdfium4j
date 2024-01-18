/* DO NOT EDIT THIS FILE - it is machine generated */
#include "Platform.h"
/* Header for class org_swdc_pdfium_internal_PDFPageObjectImpl */

#ifndef _Included_org_swdc_pdfium_internal_PDFPageObjectImpl
#define _Included_org_swdc_pdfium_internal_PDFPageObjectImpl
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
 * Method:    getObjectCount
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_getObjectCount
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
 * Method:    getPageObject
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_getPageObject
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
 * Method:    getPageObjectType
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_getPageObjectType
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
 * Method:    closeObject
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_destroyObject
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
 * Method:    createImageObject
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_createImageObject
  (JNIEnv *, jclass, jlong);
  
#ifdef __cplusplus
}
#endif
#endif
