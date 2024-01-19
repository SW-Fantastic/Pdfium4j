package org.swdc.pdfium;

import org.swdc.pdfium.internal.PDFPageObjectImpl;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

public class PdfiumImageObject extends PdfiumPageObject {

    PdfiumImageObject(PdfiumDocumentPage page, long pointer, int index) {
        super(page, pointer, index);
    }

    public boolean loadImageFile(File file) throws IOException {
        checkState();
        if (!file.exists()) {
            return false;
        }
        String name = file.getName().toLowerCase();
        if (name.endsWith("jpg") || name.endsWith("jpeg")) {
            byte[] data = Files.readAllBytes(file.toPath());
            return PDFPageObjectImpl
                    .loadObjectJpegData(this.getPointer(), data);
        }
        return false;
    }


}
