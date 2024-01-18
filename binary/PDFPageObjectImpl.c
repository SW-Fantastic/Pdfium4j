#include "PDFPageObjectImpl.h"
/*
 * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
 * Method:    getObjectCount
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_getObjectCount
  (JNIEnv * env, jclass clazz, jlong pagePointer) {

    if(pagePointer == 0 || pagePointer == -1) {
      return 0;
    }

    FPDF_PAGE page = (FPDF_PAGE)pagePointer;
    return FPDFPage_CountObjects(page);
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
 * Method:    getPageObject
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_getPageObject
  (JNIEnv * env, jclass clazz, jlong pagePointer, jint index) {

    if(pagePointer == 0 || pagePointer == -1 || index < 0) {
      return -1;
    }

    FPDF_PAGE page = (FPDF_PAGE)pagePointer;
    int objectCounts = FPDFPage_CountObjects(page);
    if(index > objectCounts) {
        return -1;
    }
    FPDF_PAGEOBJECT obj = FPDFPage_GetObject(page, index);
    return (jlong)(intptr_t)(obj);
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
 * Method:    getPageObjectType
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_getPageObjectType
  (JNIEnv * env, jclass clazz, jlong objPointer) {

    if(objPointer == 0 || objPointer == -1) {
      return -1;
    }
    FPDF_PAGEOBJECT object = (FPDF_PAGEOBJECT)objPointer;
    return FPDFPageObj_GetType(object);

  }

/*
 * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
 * Method:    destroyObject
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_destroyObject
  (JNIEnv * env, jclass clazz, jlong objPointer) {
    if(objPointer == 0 || objPointer == -1) {
      return JNI_FALSE;
    }
    FPDF_PAGEOBJECT object = (FPDF_PAGEOBJECT)objPointer;
    FPDFPageObj_Destroy(object);
    return JNI_TRUE;
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
 * Method:    createImageObject
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_createImageObject
  (JNIEnv * env, jclass clazz, jlong documentPointer) {

    if(documentPointer == 0 || documentPointer == -1) {
      return -1;
    }

    FPDF_DOCUMENT document = (FPDF_DOCUMENT)documentPointer;
    FPDF_PAGEOBJECT pageObject = FPDFPageObj_NewImageObj(document);
    if( !pageObject ) {
        return -1;
    }

    return (jlong)(intptr_t)(pageObject);
  }