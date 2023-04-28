package org.swdc.pdfium;

import org.swdc.pdfium.internal.PDFDocumentImpl;
import org.swdc.pdfium.internal.PDFPageImpl;

import java.io.Closeable;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class PdfiumDocument implements Closeable {

    private Long pointer;
    private Map<Integer,PdfiumDocumentPage> loaded = new HashMap<>();

    public PdfiumDocument(File theFile) throws IOException {
        if (!theFile.exists()) {
            throw new FileNotFoundException(theFile.getAbsolutePath());
        }
        pointer = PDFDocumentImpl.loadDocument(theFile.getAbsolutePath());
        if (pointer == -1) {
            pointer = null;
            throw new IOException("failed to load document: " + theFile.getAbsolutePath());
        }
    }

    public int getPageCount() throws IOException {
        checkState();
        return PDFDocumentImpl.getPageCount(pointer);
    }

    public PdfiumDocumentPage getPage(int pageIndex) throws IOException {
        checkState();
        int count = getPageCount();
        if (pageIndex < 0 || pageIndex >= count) {
            return null;
        }
        if (loaded.containsKey(pageIndex)) {
            return loaded.get(pageIndex);
        }
        long pagePointer = PDFDocumentImpl.loadPage(pointer,pageIndex);
        if (pagePointer != -1) {
            PdfiumDocumentPage page = new PdfiumDocumentPage(this,pagePointer, pageIndex);
            loaded.put(pageIndex,page);
            return page;
        }
        PDFPageImpl.closePage(pagePointer);
        return null;
    }

    public String getTitle() throws IOException {
        return getMetadata(PdfiumDocumentMetaType.Title);
    }

    public String getAuthor() throws IOException {
        return getMetadata(PdfiumDocumentMetaType.Author);
    }

    public String getKeywords() throws IOException {
        return getMetadata(PdfiumDocumentMetaType.Keywords);
    }

    public String getCreator() throws IOException {
        return getMetadata(PdfiumDocumentMetaType.Creator);
    }

    public String getSubject() throws IOException {
        return getMetadata(PdfiumDocumentMetaType.Subject);
    }

    public String getCreationDate() throws IOException {
        return getMetadata(PdfiumDocumentMetaType.CreationDate);
    }

    public String getModifyDate() throws IOException {
        return getMetadata(PdfiumDocumentMetaType.ModDate);
    }

    public String getMetadata(PdfiumDocumentMetaType type) throws IOException {
        checkState();
        String text = PDFDocumentImpl.getMetadataText(pointer,type.name());
        if (text == null) {
            return "";
        }
        return text;
    }

    void closePage(int pageIndex) {
        loaded.remove(pageIndex);
    }

    final Long getPointer() {
        return pointer;
    }

    private void checkState() throws IOException {
        if (pointer == null || pointer == -1) {
            throw new IOException("the document has closed.");
        }
    }


    public List<PdfiumBookMark> getBookMark() throws IOException {
        checkState();
        List<PdfiumBookMark> marks = new ArrayList<>();
        long pointerMark = PDFDocumentImpl.getFirstBookMark(pointer,-1);
        if (pointerMark == -1 || pointerMark == 0) {
            return marks;
        }
        boolean hasNext = true;
        while (hasNext) {
            hasNext = pointerMark != -1 && pointerMark != 0;
            if (hasNext) {
                marks.add(new PdfiumBookMark(pointerMark,this));
                pointerMark = PDFDocumentImpl.getNextBookMark(pointer, pointerMark);
            }
        }
        return marks;
    }

    @Override
    public void close() throws IOException {
        if (pointer != null) {
            if(PDFDocumentImpl.closeDocument(pointer)) {
                pointer = null;
            }
        }
    }
}
