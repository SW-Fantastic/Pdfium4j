package org.swdc.pdfium;

import org.swdc.pdfium.internal.PDFPageObjectImpl;

import java.io.IOException;

public class PdfiumPageObject implements AutoCloseable {

    private Long pointer;

    private PdfiumDocumentPage page;

    private int index;

    PdfiumPageObject(PdfiumDocumentPage page, long pointer, int index) {
        this.page = page;
        this.pointer = pointer;
        this.index = index;
    }

    protected void checkState() throws IOException {
        if (pointer == null || pointer == -1) {
            throw new IOException("the document has closed.");
        }
    }

    public boolean hasOwner() {
        return this.page != null && this.index > 0;
    }

    void initOwner(PdfiumDocumentPage page, int index) {
        if (!hasOwner()) {
            this.page = page;
            this.index = index;
            return;
        }
        throw new RuntimeException("this object already has a owner page.");
    }

    @Override
    public void close() throws IOException {
        if (pointer <= 0 && index<= 0) {
            return;
        } else {
            if (!this.hasOwner()) {
                PDFPageObjectImpl.destroyObject(pointer);
            } else {
                this.page.closeObject(this.index);
            }
            this.pointer = -1L;
            this.index = -1;
        }
    }

    protected long getPointer() {
        return pointer;
    }

    public PageObjectType getObjectType() throws IOException {
        checkState();
        int type = PDFPageObjectImpl.getPageObjectType(pointer);
        return PageObjectType.of(type);
    }

    public PdfiumDocumentPage getOwner() {
        return page;
    }

    public int getIndex() {
        return index;
    }

    public boolean setBounds(float width, float height, float posX, float posY) throws IOException {
        checkState();
        if (width < 0 || height < 0 || posX < 0 || posY < 0) {
            return false;
        }
        return PDFPageObjectImpl.setObjectMatrix(
                getPointer(), width, 0, 0, height, posX, posY
        );
    }

    public boolean setSize(float width, float height) throws IOException {
        checkState();
        float[] matrix = PDFPageObjectImpl
                .getObjectMatrix(getPointer());
        matrix[0] = width;
        matrix[3] = height;
        return PDFPageObjectImpl.setObjectMatrix(
                getPointer(),
                matrix[0], matrix[1], matrix[2],
                matrix[3], matrix[4], matrix[5]
        );
    }

    public float getPosX() throws IOException {
        checkState();
        return PDFPageObjectImpl
                .getObjectMatrix(getPointer())[4];
    }

    public float getPosY() throws IOException {
        checkState();
        return PDFPageObjectImpl
                .getObjectMatrix(getPointer())[5];
    }

    public float getWidth() throws IOException {
        checkState();
        return PDFPageObjectImpl
                .getObjectMatrix(getPointer())[0];
    }

    public float getHeight() throws IOException {
        checkState();
        return PDFPageObjectImpl
                .getObjectMatrix(getPointer())[3];
    }
}
