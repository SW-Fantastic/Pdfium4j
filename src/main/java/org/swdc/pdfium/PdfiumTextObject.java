package org.swdc.pdfium;

import org.swdc.pdfium.internal.PDFPageObjectImpl;

import java.io.IOException;

public class PdfiumTextObject extends PdfiumPageObject {

    PdfiumTextObject(PdfiumDocumentPage page, long pointer, int index) {
        super(page, pointer, index);
    }

    public boolean setText(String text) throws IOException {
        checkState();
        if (text == null) {
            return false;
        }
        return PDFPageObjectImpl.setTextObjectString(
                getPointer(),
                text
        );
    }

}
