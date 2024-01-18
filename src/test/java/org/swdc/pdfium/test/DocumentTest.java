package org.swdc.pdfium.test;

import org.swdc.pdfium.*;

import javax.imageio.ImageIO;
import java.awt.image.*;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class DocumentTest {

    public static void main(String[] args) throws IOException {

        PdfiumPlatform.initializePdfium(new File("platform"));

        PdfiumDocument document = new PdfiumDocument(new File("./test2.pdf"));
        System.out.println("The document has : " + document.getPageCount() + " pages");
        PdfiumDocumentPage page = document.getPage(1);
        System.out.println("Page width: " + page.getWidthF() + " height: " + page.getHeightF());
        System.out.println("Page has transparency: " + page.hasTransparency());
        System.out.println(document.getMetadata(PdfiumDocumentMetaType.Producer));
        System.out.println(page.getTitle());

        for (int idx = 0 ; idx < page.getObjectCounts(); idx ++) {
            PdfiumPageObject object = page.getPageObject(idx);
            System.err.println(object.getObjectType().name());
        }

        List<PdfiumBookMark> mark = document.getBookMark();
        for (PdfiumBookMark item: mark) {
            System.err.println(item.getTitle());
            System.err.println(item.getPageIndex());
        }

        OutputStream os = Files.newOutputStream(Paths.get("test.png"));
        PdfiumBitmapImage image = page.renderPage(4);
        BufferedImage image1 = image.createBufferedImage();
        ImageIO.write(image1,"png" ,os );
        //os.write(data);
        os.close();

        page.close();
        image.close();

        document.write(new FileOutputStream("out.pdf"));
        document.close();
    }


}
