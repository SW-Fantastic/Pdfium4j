package org.swdc.pdfium;

import org.swdc.pdfium.internal.PDFPageObjectImpl;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;

public class PdfiumTextObject extends PdfiumPageObject {

    PdfiumTextObject(PdfiumDocumentPage page, long pointer, int index) {
        super(page, pointer, index);
    }

    public float getFontSize() throws IOException {
        checkState();
        return PDFPageObjectImpl.getFontSize(
                getPointer()
        );
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

    public String getText() throws IOException {
        checkState();
        if (getOwner() == null) {
            return null;
        }
        byte[] data = PDFPageObjectImpl.getTextObjectString(
                getPointer(),
                getOwner().getPointer()
        );
        InputStreamReader reader = new InputStreamReader(
                new ByteArrayInputStream(data),
                StandardCharsets.UTF_16LE
        );
        StringBuilder sb = new StringBuilder();
        int cur = 0;
        while ((cur = reader.read()) > 0) {
            sb.append((char) cur);
        }
        return sb.toString();
    }



}
