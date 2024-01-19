#include "PDFPageObjectImpl.h"
#include <string.h>

JavaVM* VM = NULL;
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

  int readByteBuffer(void* param, unsigned long position, unsigned char* pBuf, unsigned long size) {
    JNIEnv* env = NULL;
    int status = VM->GetEnv((void**)&env, JNI_VERSION_1_4);
    if (status == JNI_EDETACHED || env == NULL) {
      VM->AttachCurrentThread((void**)&env,NULL);
    }
    jbyteArray buffer = (jbyteArray)param;

    jbyte* data = env->GetByteArrayElements(buffer,NULL);
    int total = env->GetArrayLength(buffer);
    int rest = total - position;
    if(rest > size) {
      memcpy(pBuf, data + position, size);
    } else {
      memcpy(pBuf, data + position, rest);
    }
    env->ReleaseByteArrayElements(buffer, data, 0);
    return size;
  }

  /*
   * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
   * Method:    loadObjectJpegData
   * Signature: (J[B)Z
   */
  JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_loadObjectJpegData
    (JNIEnv * env, jclass clazz, jlong objPointer, jbyteArray buffer) {

      if(objPointer == 0 || objPointer == -1) {
        return JNI_FALSE;
      }

      if(buffer == NULL) {
        return JNI_FALSE;
      }
      if (!VM) {
          env->GetJavaVM(&VM);
      }
      FPDF_PAGEOBJECT object = (FPDF_PAGEOBJECT)objPointer;

      FPDF_FILEACCESS access;
      access.m_Param = (jbyteArray)env->NewGlobalRef(buffer);
      access.m_FileLen = env->GetArrayLength(buffer);
      access.m_GetBlock = &readByteBuffer;
      int rst = FPDFImageObj_LoadJpegFile(NULL, 0, object, &access);
      if(rst) {
        return JNI_TRUE;
      }
      return JNI_FALSE;
    }

  /*
   * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
   * Method:    insertObjectIntoPage
   * Signature: (JJ)Z
   */
  JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_insertObjectIntoPage
    (JNIEnv * env, jclass clazz, jlong pagePointer, jlong objPointer) {

      if(objPointer == 0 || objPointer == -1) {
        return JNI_FALSE;
      }

      if(pagePointer == 0 || pagePointer == -1) {
        return JNI_FALSE;
      }

      FPDF_PAGEOBJECT object = (FPDF_PAGEOBJECT)objPointer;
      FPDF_PAGE page = (FPDF_PAGE)pagePointer;

      FPDFPage_InsertObject(page, object);

      return JNI_TRUE;
    }

  /*
   * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
   * Method:    removeObjectFromPage
   * Signature: (JJ)Z
   */
  JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_removeObjectFromPage
    (JNIEnv * env, jclass clazz, jlong pagePointer, jlong objPointer) {

      if(objPointer == 0 || objPointer == -1) {
        return JNI_FALSE;
      }

      if(pagePointer == 0 || pagePointer == -1) {
        return JNI_FALSE;
      }

      FPDF_PAGEOBJECT object = (FPDF_PAGEOBJECT)objPointer;
      FPDF_PAGE page = (FPDF_PAGE)pagePointer;

      if(FPDFPage_RemoveObject(page,object)) {
        return JNI_TRUE;
      }
      return JNI_FALSE;
    }

    /*
   * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
   * Method:    setObjectMatrix
   * Signature: (JFFFFFF)Z
   */
  JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_setObjectMatrix
    (JNIEnv * env, jclass clazz, jlong objPointer, jfloat a, jfloat b, jfloat c, jfloat d, jfloat e, jfloat f) {

      if(objPointer == 0 || objPointer == -1) {
        return JNI_FALSE;
      }

      FPDF_PAGEOBJECT object = (FPDF_PAGEOBJECT)objPointer;

      FS_MATRIX matrix;
      matrix.a = a;
      matrix.b = b;
      matrix.c = c;
      matrix.d = d;
      matrix.e = e;
      matrix.f = f;

      if(FPDFPageObj_SetMatrix(object,&matrix)) {
        return JNI_TRUE;
      }
      return JNI_FALSE;
  }

  /*
   * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
   * Method:    getObjectMatrix
   * Signature: (J)[F
   */
  JNIEXPORT jfloatArray JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_getObjectMatrix
    (JNIEnv * env, jclass clazz, jlong objPointer) {

      if(objPointer == 0 || objPointer == -1) {
        return JNI_FALSE;
      }

      FPDF_PAGEOBJECT object = (FPDF_PAGEOBJECT)objPointer;

      FS_MATRIX matrix;
      if(FPDFPageObj_GetMatrix(object,&matrix)) {
        float result[6] = {
          matrix.a,
          matrix.b,
          matrix.c,
          matrix.d,
          matrix.e,
          matrix.f
        };
        jfloatArray arrayOfResult = env->NewFloatArray(6);
        env->SetFloatArrayRegion(arrayOfResult, 0, 6, (jfloat*)&result);
        return arrayOfResult;
      }

      return NULL;
    }

    /*
   * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
   * Method:    createTextObject
   * Signature: (J)J
   */
  JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_createTextObject
      (JNIEnv * env, jclass clazz, jlong documentPointer, jstring font, jfloat size) {

      if(documentPointer == 0 || documentPointer == -1) {
        return -1;
      }

      const char* cFontName = env->GetStringUTFChars(font, 0);

      FPDF_DOCUMENT document = (FPDF_DOCUMENT)documentPointer;
      FPDF_PAGEOBJECT obj = FPDFPageObj_NewTextObj(document,cFontName,size);
      env->ReleaseStringUTFChars(font,cFontName);

      if(obj) {
        return (jlong)(intptr_t)(obj);
      }

      return NULL;
    }

    /*
   * Class:     org_swdc_pdfium_internal_PDFPageObjectImpl
   * Method:    setTextObjectString
   * Signature: (JLjava/lang/String;)Z
   */
  JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFPageObjectImpl_setTextObjectString
    (JNIEnv * env, jclass clazz, jlong objPointer, jstring text) {

      if(objPointer == 0 || objPointer == -1) {
        return JNI_FALSE;
      }

      FPDF_PAGEOBJECT object = (FPDF_PAGEOBJECT)objPointer;

      FPDF_WIDESTRING utf16 = (FPDF_WIDESTRING)env->GetStringChars(text, NULL);
      int rst = FPDFText_SetText(object,utf16);
      env->ReleaseStringChars(text,(const jchar*)utf16);

      return rst ? JNI_TRUE : JNI_FALSE;
    }
