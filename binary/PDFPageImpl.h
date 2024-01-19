/* DO NOT EDIT THIS FILE - it is machine generated */
#include "Platform.h"
/* Header for class org_swdc_pdfium_internal_PDFPageImpl */

#ifndef _Included_org_swdc_pdfium_internal_PDFPageImpl
#define _Included_org_swdc_pdfium_internal_PDFPageImpl
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    createPage
 * Signature: (JIDD)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_createPage
  (JNIEnv *, jclass, jlong, jint, jdouble, jdouble);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    removePage
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_removePage
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    closePage
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_closePage
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    getWidthF
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_getWidthF
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    getHeightF
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_getHeightF
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    getWidth
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_getWidth
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    getHeight
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_getHeight
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    getRotation
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_getRotation
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    setRotation
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_setRotation
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    hasTransparency
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_hasTransparency
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    getPageTitle
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_getPageTitle
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    renderBitmapImage
 * Signature: (JJIIIII)Z
 */
JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_renderBitmapImage
  (JNIEnv *, jclass, jlong, jlong, jint, jint, jint, jint, jint);

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    generateContent
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_generateContent
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
