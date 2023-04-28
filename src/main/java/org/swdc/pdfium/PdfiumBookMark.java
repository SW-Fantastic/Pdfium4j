package org.swdc.pdfium;

import org.swdc.pdfium.internal.PDFDocumentImpl;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class PdfiumBookMark {

    private Long pointer;

    private PdfiumDocument document;

    private List<PdfiumBookMark> children = new ArrayList<>();

    PdfiumBookMark(long pointer, PdfiumDocument document) {
        this.pointer = pointer;
        this.document = document;

        long next = PDFDocumentImpl.getFirstBookMark(document.getPointer(), pointer);
        boolean hasChildren = next != -1 && next != 0 && next != pointer;;
        if (hasChildren) {
            PdfiumBookMark mark = new PdfiumBookMark(next,document);
            children.add(mark);
            PDFDocumentImpl.getNextBookMark(document.getPointer(), next);
        }
    }

    private void checkState() throws IOException {
        if (pointer == null || pointer == -1) {
            throw new IOException("the document has closed.");
        }
    }

    public int getPageIndex() throws IOException {
        checkState();
        return PDFDocumentImpl.getBookMarkPageIndex(document.getPointer(), pointer);
    }

    public String getTitle() throws IOException {
        checkState();
        String title = PDFDocumentImpl.getBookMarkTitle(pointer);
        if (title == null) {
            return "";
        }
        return title;
    }


}
