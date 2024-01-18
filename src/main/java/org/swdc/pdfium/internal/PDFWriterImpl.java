package org.swdc.pdfium.internal;

public class PDFWriterImpl {

    public static native long writeDocument(long documentPointer,PDFOutputStream outputStream);

}
