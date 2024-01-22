package org.swdc.pdfium;

import org.swdc.pdfium.internal.PDFPageObjectImpl;

import java.io.IOException;

public class PdfiumFont implements AutoCloseable {

    private Long pointer;

    PdfiumFont(long pointer) {
        this.pointer = pointer;
    }

    protected void checkState() throws IOException {
        if (pointer == null || pointer == -1) {
            throw new IOException("the document has closed.");
        }
    }

    @Override
    public void close() throws IOException {
        if (pointer == null || pointer == -1) {
            return;
        }
        if(PDFPageObjectImpl.closeFont(pointer)) {
            pointer = -1L;
        }
    }

    public String getFontName() throws IOException {
        checkState();
        return PDFPageObjectImpl.getFontName(
                getPointer()
        );
    }

    public boolean isEmbedded() throws IOException {
        checkState();
        return PDFPageObjectImpl.isFontEmbedded(
                getPointer()
        );
    }


    Long getPointer() {
        return pointer;
    }
}
