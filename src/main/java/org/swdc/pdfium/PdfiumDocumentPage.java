package org.swdc.pdfium;

import org.swdc.pdfium.internal.PDFPageImpl;

import java.io.Closeable;
import java.io.IOException;

public class PdfiumDocumentPage implements Closeable {

    private Long pointer;
    private int pageIndex = -1;
    private PdfiumDocument document;

    PdfiumDocumentPage(PdfiumDocument document, long pointer, int pageIndex) {
        this.pointer = pointer;
        this.pageIndex = pageIndex;
        this.document = document;
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

    public int getPageIndex() {
        return pageIndex;
    }
}
