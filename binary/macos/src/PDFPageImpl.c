#include "jni.h"
#include <stdlib.h>
#include "../pdfium_universal/include/fpdf_edit.h"
#include "../pdfium_universal/include/fpdf_doc.h"
#include "../pdfium_universal/include/fpdfview.h"
#include "PDFPageImpl.h"

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    closePage
 * Signature: (J)J
 */
JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_closePage
  (JNIEnv * env, jclass clazz, jlong pointer) {

    if(pointer == 0 || pointer == -1) {
        return 0;
    }
    FPDF_PAGE page = (FPDF_PAGE)pointer;
    FPDF_ClosePage(page);
    return JNI_TRUE;
  }

  /*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    getWidthF
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_getWidthF
  (JNIEnv * env, jclass clazz, jlong pointer) {
    
    if(pointer == 0 || pointer == -1) {
        return 0;
    }
    FPDF_PAGE page = (FPDF_PAGE)pointer;
    return (jfloat)FPDF_GetPageWidthF(page);
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    getHeightF
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_getHeightF
  (JNIEnv * env, jclass clazz, jlong pointer) {

    if(pointer == 0 || pointer == -1) {
        return 0;
    }
    FPDF_PAGE page = (FPDF_PAGE)pointer;
    return (jfloat)FPDF_GetPageHeightF(page);
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    getWidth
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_getWidth
  (JNIEnv * env, jclass clazz, jlong pointer) {
    if(pointer == 0 || pointer == -1) {
        return 0;
    }
    FPDF_PAGE page = (FPDF_PAGE)pointer;
    return (jint)FPDF_GetPageWidth(page);
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    getHeight
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_getHeight
  (JNIEnv * env, jclass clazz, jlong pointer) {
    if(pointer == 0 || pointer == -1) {
        return 0;
    }
    FPDF_PAGE page = (FPDF_PAGE)pointer;
    return (jint)FPDF_GetPageHeight(page);
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    hasTransparency
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_hasTransparency
  (JNIEnv * env, jclass clazz, jlong pointer) {

    if(pointer == 0 || pointer == -1) {
        return 0;
    }
    FPDF_PAGE page = (FPDF_PAGE)pointer;
    return FPDFPage_HasTransparency(page) == 1 ? JNI_TRUE : JNI_FALSE;
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    getPageTitle
 * Signature: (JJI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_getPageTitle
  (JNIEnv * env, jclass clazz, jlong pointer, jint pageIdx) {
    if(pointer == 0 || pointer == -1 ) {
        return 0;
    }
    FPDF_DOCUMENT doc = (FPDF_DOCUMENT)pointer;
    unsigned long length = FPDF_GetPageLabel(doc,pageIdx, NULL,0);
    if(length == 0) {
      return NULL;
    }
    uint16_t* buffer = (uint16_t*)malloc(sizeof(uint16_t) * length);
    FPDF_GetPageLabel(doc,pageIdx,buffer,length);
    jstring str = (*env)->NewString(env,(jchar*)buffer,(length / sizeof(uint16_t)) - 1);
    free(buffer);
    return str;
  }


/*
 * Class:     org_swdc_pdfium_internal_PDFPageImpl
 * Method:    renderBitmapImage
 * Signature: (JJIIIII)Z
 */
JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFPageImpl_renderBitmapImage
  (JNIEnv * env, jclass clazz, jlong pointer, jlong pointerImage, jint x, jint y, jint width, jint height, jint rotate) {

    if(pointer == 0 || pointer == -1 || pointerImage == 0 || pointerImage == -1) {
      return JNI_FALSE;
    }
    FPDF_PAGE page = (FPDF_PAGE)pointer;
    FPDF_BITMAP bitmap = (FPDF_BITMAP)pointerImage;
    FPDF_RenderPageBitmap(bitmap,page,x,y,width,height,rotate,FPDF_ANNOT);
    return JNI_TRUE;
  }
