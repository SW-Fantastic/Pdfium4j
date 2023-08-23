#include <stdlib.h>

#include "Platform.h"
#include "PDFDocumentImpl.h"


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv env;
    if((*vm)->GetEnv(vm,(void **) &env, JNI_VERSION_1_4) != JNI_OK) { 
        return -1;
    }
    FPDF_LIBRARY_CONFIG config;
    config.version = 2;
    config.m_pUserFontPaths = NULL;
    config.m_pIsolate = NULL;
    config.m_v8EmbedderSlot = 0;

    FPDF_InitLibraryWithConfig(&config);

    return JNI_VERSION_1_4;
}

JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved) {
    FPDF_DestroyLibrary();
}

/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    loadDocument
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_loadDocument
  (JNIEnv * env, jclass clazz, jstring theFilePath) {

    const char * str = (*env)->GetStringUTFChars(env,theFilePath, 0);
    FPDF_DOCUMENT doc = FPDF_LoadDocument(str, NULL);
    (*env)->ReleaseStringUTFChars(env,theFilePath,str);

    if (!doc) {
        return -1;
    }

    return (jlong)(intptr_t)(doc);
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    closeDocument
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_closeDocument
  (JNIEnv * env, jclass clazz, jlong pointer) {
    if(pointer == 0) {
        return JNI_FALSE;
    }
    FPDF_DOCUMENT doc = (FPDF_DOCUMENT)pointer;
    FPDF_CloseDocument(doc);
    return JNI_TRUE;
  }

  /*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    getPageCount
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_getPageCount
  (JNIEnv * env, jclass clazz, jlong pointer) {
    if(pointer == 0) {
        return -1;
    }
    FPDF_DOCUMENT doc = (FPDF_DOCUMENT)pointer;
    return FPDF_GetPageCount(doc);
  }

  /*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    loadPage
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_loadPage
  (JNIEnv * env, jclass clazz, jlong pointer, jint pageIndex) {
    if(pointer == 0) {
        return -1;
    }
    FPDF_DOCUMENT doc = (FPDF_DOCUMENT)pointer;
    int count = FPDF_GetPageCount(doc);
    if(pageIndex < 0 || pageIndex >= count) {
      return -1;
    }
    FPDF_PAGE page = FPDF_LoadPage(doc, pageIndex);
    return (jlong)(intptr_t)(page);
  }


/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    getMetadataText
 * Signature: (JLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_getMetadataText
  (JNIEnv * env, jclass clazz, jlong pointer, jstring tag) {

    if(pointer == 0 || pointer == -1) {
      return NULL;
    }
    FPDF_DOCUMENT doc = (FPDF_DOCUMENT)pointer;
    const char* text = (*env)->GetStringUTFChars(env,tag,NULL);
    unsigned long length = FPDF_GetMetaText(doc,text, NULL,0);
    if(length == 0) {
      (*env)->ReleaseStringUTFChars(env,tag,text);
      return NULL;
    }
    char16_t* buffer = (char16_t*)malloc(sizeof(char16_t) * length);
    FPDF_GetMetaText(doc,text,buffer,length);
    (*env)->ReleaseStringUTFChars(env,tag,text);
    jstring str = (*env)->NewString(env,(jchar*)buffer,(length / sizeof(char16_t)) - 1);
    free(buffer);

    return str;
  }


  /*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    getFirstBookMark
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_getFirstBookMark
  (JNIEnv * env, jclass clazz, jlong pointer, jlong parentBookMark) {

    if(pointer == 0 || pointer == -1) {
      return -1;
    }

    FPDF_BOOKMARK parent = parentBookMark == 0 || parentBookMark == -1 ? NULL : (FPDF_BOOKMARK)parentBookMark;
    FPDF_DOCUMENT doc = (FPDF_DOCUMENT)pointer;
    FPDF_BOOKMARK bookMark = FPDFBookmark_GetFirstChild(doc,parent);
    return (jlong)(intptr_t)bookMark;
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    getNextBookMark
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_getNextBookMark
  (JNIEnv * env, jclass clazz, jlong pointer, jlong bookMarkPointer) {
    if(pointer == 0 || pointer == -1 || bookMarkPointer == 0 || bookMarkPointer == -1) {
      return -1;
    }
    FPDF_DOCUMENT doc = (FPDF_DOCUMENT)pointer;
    FPDF_BOOKMARK bookMark = (FPDF_BOOKMARK)bookMarkPointer;
    FPDF_BOOKMARK next = FPDFBookmark_GetNextSibling(doc,bookMark);
    return (jlong)(intptr_t)next;
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    getBookMarkPageIndex
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_getBookMarkPageIndex
  (JNIEnv * env, jclass clazz, jlong pointer,jlong bookMarkPointer) {
    if(pointer == 0 || pointer == -1 || bookMarkPointer == 0 || bookMarkPointer == -1) {
      return -1;
    }
    FPDF_DOCUMENT doc = (FPDF_DOCUMENT)pointer;
    FPDF_BOOKMARK bookMark = (FPDF_BOOKMARK)bookMarkPointer;
    FPDF_DEST dest = FPDFBookmark_GetDest(doc,bookMark);
    if(dest == NULL) {
      return -1;
    }
    return FPDFDest_GetDestPageIndex(doc,dest);
  }

/*
 * Class:     org_swdc_pdfium_internal_PDFDocumentImpl
 * Method:    getBookMarkTitle
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_swdc_pdfium_internal_PDFDocumentImpl_getBookMarkTitle
  (JNIEnv * env, jclass clazz, jlong pointer) {

    if(pointer == 0 || pointer == -1) {
      return NULL;
    }
    FPDF_BOOKMARK bookMark = (FPDF_BOOKMARK)pointer;
    unsigned long length = FPDFBookmark_GetTitle(bookMark,NULL,0);
    if (length == 0){
      return NULL;
    }
    char16_t* buffer = (char16_t*)malloc(sizeof(char16_t) * length);
    FPDFBookmark_GetTitle(bookMark,buffer,length);
    jstring str = (*env)->NewString(env,(jchar*)buffer,(length / sizeof(char16_t)) - 1);
    free(buffer);
    return str;
  }