//#define _CRT_SECURE_NO_WARNINGS

#include "Platform.h"
#include "PDFBitmapImpl.h"

/*
 * Class:     org_swdc_pdfium_internal_PDFBitmapImpl
 * Method:    createBitmap
 * Signature: (IIZ)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFBitmapImpl_createBitmap
  (JNIEnv * env, jclass clazz, jint width, jint height, jboolean alpha) {

    FPDF_BITMAP bitmap = FPDFBitmap_Create(width, height, alpha == JNI_TRUE ? 1 : 0);
    if (bitmap == NULL) {
        return -1;
    }
    return (jlong)(intptr_t)(bitmap);
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFBitmapImpl
 * Method:    fillRect
 * Signature: (JIIIIJ)V
 */
JNIEXPORT void JNICALL Java_org_swdc_pdfium_internal_PDFBitmapImpl_fillRect
  (JNIEnv * env, jclass clazz, jlong pointer, jint left, jint top, jint width, jint height, jlong color) {
    
    if(pointer == 0 || pointer == -1) {
        return;
    }

    FPDF_BITMAP bitmap = (FPDF_BITMAP)pointer;
    FPDF_DWORD theColor = (FPDF_DWORD)color;

    int theWidth = FPDFBitmap_GetWidth(bitmap);
    int theHeight = FPDFBitmap_GetHeight(bitmap);

    if(width < 0 || theWidth < width || height < 0 || theHeight < height) {
        return;
    }
    FPDFBitmap_FillRect(bitmap,left,top,width,height, theColor);
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFBitmapImpl
 * Method:    getWidth
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFBitmapImpl_getWidth
  (JNIEnv * env, jclass clazz, jlong pointer) {

    if(pointer == 0 || pointer == -1) {
        return 0;
    }

    FPDF_BITMAP bitmap = (FPDF_BITMAP)pointer;
    return FPDFBitmap_GetWidth(bitmap);
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFBitmapImpl
 * Method:    getHeight
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFBitmapImpl_getHeight
  (JNIEnv * env, jclass clazz, jlong pointer) {

    if(pointer == 0 || pointer == -1) {
        return 0;
    }

    FPDF_BITMAP bitmap = (FPDF_BITMAP)pointer;
    return FPDFBitmap_GetHeight(bitmap);
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFBitmapImpl
 * Method:    getStride
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFBitmapImpl_getStride
  (JNIEnv * env, jclass clazz, jlong pointer) {

    if(pointer == 0 || pointer == -1) {
        return 0;
    }
    FPDF_BITMAP bitmap = (FPDF_BITMAP)pointer;
    return FPDFBitmap_GetStride(bitmap);
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFBitmapImpl
 * Method:    getBuffer
 * Signature: (J)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_org_swdc_pdfium_internal_PDFBitmapImpl_getBuffer
  (JNIEnv * env, jclass clazz, jlong pointer) {

    if(pointer == 0 || pointer == -1) {
        return NULL;
    }
    FPDF_BITMAP bitmap = (FPDF_BITMAP)pointer;
    int format = FPDFBitmap_GetFormat(bitmap);
    if(format == FPDFBitmap_Unknown) {
        return NULL;
    }
    int theHeight = FPDFBitmap_GetHeight(bitmap);
    int stride = FPDFBitmap_GetStride(bitmap);
    int bufSize = stride * theHeight;
    
    void* buffer = FPDFBitmap_GetBuffer(bitmap);
    return (*env)->NewDirectByteBuffer(env,buffer, bufSize);
  }


/*
 * Class:     org_swdc_pdfium_internal_PDFBitmapImpl
 * Method:    releaseBitmap
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFBitmapImpl_releaseBitmap
  (JNIEnv * env, jclass clazz, jlong pointer) {
    if(pointer == 0 || pointer == -1) {
        return JNI_FALSE;
    }
    FPDF_BITMAP bitmap = (FPDF_BITMAP)pointer;
    FPDFBitmap_Destroy(bitmap);
    return JNI_TRUE;
  }

