package org.swdc.pdfium;

import org.swdc.pdfium.internal.PDFPageImpl;
import org.swdc.pdfium.internal.PDFPageObjectImpl;

import java.io.Closeable;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class PdfiumDocumentPage implements Closeable {

    private Long pointer;
    private int pageIndex = -1;
    private PdfiumDocument document;

    private Map<Integer,PdfiumPageObject> objectMap;

    PdfiumDocumentPage(PdfiumDocument document, long pointer, int pageIndex) {
        this.pointer = pointer;
        this.pageIndex = pageIndex;
        this.document = document;
        this.objectMap = new HashMap<>();
    }

    private void checkState() throws IOException {
        if (pointer == null || pointer == -1) {
            throw new IOException("the document has closed.");
        }
    }

    @Override
    public void close() throws IOException {
        if (pageIndex < 0 || pointer == null) {
            return;
        }
        if (!PDFPageImpl.closePage(pointer)){
            throw new IOException("failed to close the page: " + pageIndex);
        } else {
            this.pointer = null;
            this.document.closePage(pageIndex);
            this.pageIndex = -1;
        }
    }

    public float getHeightF() throws IOException {
        checkState();
        return PDFPageImpl.getHeightF(pointer);
    }

    public float getWidthF() throws IOException {
        checkState();
        return PDFPageImpl.getWidthF(pointer);
    }

    public int getWidth() throws IOException {
        checkState();
        return PDFPageImpl.getWidth(pointer);
    }

    public int getHeight() throws IOException {
        checkState();
        return PDFPageImpl.getHeight(pointer);
    }

    public boolean hasTransparency() throws IOException {
        checkState();
        return PDFPageImpl.hasTransparency(pointer);
    }

    public PdfiumBitmapImage renderPage() throws IOException {
        return renderPage(1,PdfiumPageRotate.NO_ROTATE);
    }

    public PdfiumBitmapImage renderPage(int scale) throws IOException {
        return renderPage(scale,PdfiumPageRotate.NO_ROTATE);
    }

    public PdfiumBitmapImage renderPage(PdfiumPageRotate rotate) throws IOException {
        return renderPage(1, rotate);
    }

    public PdfiumPageRotate getPageRotate() throws IOException {
        checkState();
        int val = PDFPageImpl.getRotation(pointer);
        return PdfiumPageRotate.of(val);
    }

    public void setPageRotate(PdfiumPageRotate rotate) throws IOException {
        checkState();
        if (rotate == null) {
            return;
        }
        PDFPageImpl.setRotation(pointer,rotate.getValue());
    }

    void setPageIndex(int pageIndex) {
        this.pageIndex = pageIndex;
    }

    public String getTitle() throws IOException {
        checkState();
        if (document.getPointer() == null || document.getPointer() == 0 || document.getPointer() == -1) {
            return "";
        }
        return PDFPageImpl.getPageTitle(document.getPointer(), getPageIndex());
    }

    public PdfiumBitmapImage renderPage(int scale, PdfiumPageRotate rotate) throws IOException {
        checkState();
        if (rotate == null) {
            rotate = PdfiumPageRotate.NO_ROTATE;
        }
        int width = getWidth() * scale;
        int height = getHeight() * scale;
        PdfiumBitmapImage bitmapImage = new PdfiumBitmapImage(width, height, true);
        bitmapImage.fillRect(0, 0, width, height, "FFFFFFFF");
        if(!PDFPageImpl.renderBitmapImage(
                pointer,
                bitmapImage.getPointer(),
                0,
                0,
                width,
                height,
                rotate.getValue()
        )) {
            bitmapImage.close();
            throw new IOException("failed to render the page.");
        }
        return bitmapImage;
    }

    Long getPointer() {
        return pointer;
    }

    // ----- Page Objects ------ //


    public int getPageIndex() {
        return pageIndex;
    }

    // ----- Page Objects ------ //
    public int getObjectCounts() throws IOException {
        checkState();
        return PDFPageObjectImpl.getObjectCount(pointer);
    }

    public PdfiumPageObject getPageObject(int objectIndex) throws IOException {
        checkState();
        if (objectMap.containsKey(objectIndex)) {
            return objectMap.get(objectIndex);
        }
        if (objectIndex < 0 || objectIndex > getObjectCounts()) {
            return null;
        }
        long pointer = PDFPageObjectImpl
                .getPageObject(this.pointer,objectIndex);
        if (pointer <= 0) {
            return null;
        }
        PageObjectType type = PageObjectType.of(
                PDFPageObjectImpl.getPageObjectType(pointer)
        );
        PdfiumPageObject object;
        switch (type) {
            case IMAGE: {
                object = new PdfiumImageObject(this, pointer, objectIndex);
                break;
            }
            default: {
                object = new PdfiumPageObject(this, pointer, objectIndex);
                break;
            }
        }
        objectMap.put(objectIndex,object);
        return object;
    }

    void closeObject(int objectIndex) {
        objectMap.remove(objectIndex);
    }

    public boolean removeObject(PdfiumImageObject pageObject) throws IOException {
        checkState();
        if (pageObject == null) {
            return false;
        } else {
            pageObject.checkState();
        }
        if (pageObject.getOwner() != this) {
            return false;
        }
        boolean result = PDFPageObjectImpl.removeObjectFromPage(
                this.getPointer(),
                pageObject.getPointer()
        );
        if (result) {
            pageObject.close();
        }
        return result;
    }

    public boolean insertObject(PdfiumPageObject pageObject) throws IOException {
        checkState();
        if (pageObject == null) {
            return false;
        } else {
            pageObject.checkState();
        }
        if (pageObject.hasOwner()) {
            return false;
        }
        boolean result = PDFPageObjectImpl.insertObjectIntoPage(
                this.getPointer(),
                pageObject.getPointer()
        );
        if (result) {
            int index = getObjectCounts() - 1;
            pageObject.initOwner(this, index);
            objectMap.put(index, pageObject);
        }
        return result;
    }

    public boolean generateContent() throws IOException {
        checkState();
        return PDFPageImpl.generateContent(
                getPointer()
        );
    }
}
