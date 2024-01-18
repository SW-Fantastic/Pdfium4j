#include <stdlib.h>
#include "PDFWriterImpl.h"

typedef struct PDFWriter_ : FPDF_FILEWRITE {

    jobject os;
    JNIEnv* env;
    jmethodID writeMethod;

} PDFWriter;

#ifdef __cplusplus
extern "C" {
#endif

int writePdfData(FPDF_FILEWRITE* self, const void* data, unsigned long size) {

  PDFWriter* writer = reinterpret_cast<PDFWriter*>(self);
  char* writeBuffer = static_cast<char *>(const_cast<void *>(data));
  
  JNIEnv* env = writer->env;
  jobject output = writer->os;
  jmethodID write = writer->writeMethod;

  unsigned long pos = 0;
  char* current = writeBuffer + pos;
  int batchSize = 1024 * 1024 * 2;

  while (pos < size) {
    int curSize = 0;
    if(size > batchSize) {
      curSize = batchSize;
    } else {
      curSize = size - pos;
    }
    jobject buf = env->NewDirectByteBuffer(current, batchSize);
    env->CallVoidMethod(output,write,buf,curSize);
    current = current + curSize;
    pos = pos + curSize;
  }

  return size;

}

/*
 * Class:     org_swdc_pdfium_internal_PDFWriterImpl
 * Method:    writeDocument
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_swdc_pdfium_internal_PDFWriterImpl_writeDocument
  (JNIEnv * env, jclass clazz, jlong docPointer, jobject outputstream) {

    FPDF_DOCUMENT doc = (FPDF_DOCUMENT)docPointer;
    PDFWriter writer;
    writer.os = outputstream;
    writer.WriteBlock = &writePdfData;
    writer.env = env;

    jclass os = env->FindClass("org/swdc/pdfium/internal/PDFOutputStream");
    writer.writeMethod = env->GetMethodID(os,"write","(Ljava/nio/ByteBuffer;I)V");

    FPDF_SaveAsCopy(doc,&writer,FPDF_NO_INCREMENTAL);

    return 0;
  }

#ifdef __cplusplus
}
#endif