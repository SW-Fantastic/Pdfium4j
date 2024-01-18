package org.swdc.pdfium;

import org.swdc.pdfium.internal.PDFPageObjectImpl;

import java.io.IOException;

public class PdfiumPageObject implements AutoCloseable {

    private Long pointer;

    private PdfiumDocumentPage page;

    private int index;

    /**
     * 只有新创建的Object，并且没有被插入页面的时候才应当为true。
     */
    protected boolean shouldBeDestroy = false;

    PdfiumPageObject(PdfiumDocumentPage page, long pointer, int index) {
        this.page = page;
        this.pointer = pointer;
        this.index = index;
    }

    private void checkState() throws IOException {
        if (pointer == null || pointer == -1) {
            throw new IOException("the document has closed.");
        }
    }

    @Override
    public void close() throws Exception {
        if (pointer <= 0 && index<= 0) {
            return;
        } else {
            if (shouldBeDestroy) {
                PDFPageObjectImpl.destroyObject(pointer);
            }
            this.page.closeObject(this.index);
            this.pointer = -1L;
            this.index = -1;
        }
    }

    public PageObjectType getObjectType() throws IOException {
        checkState();
        int type = PDFPageObjectImpl.getPageObjectType(pointer);
        return PageObjectType.of(type);
    }

    void setShouldBeDestroy(boolean shouldBeDestroy) {
        this.shouldBeDestroy = shouldBeDestroy;
    }
}
