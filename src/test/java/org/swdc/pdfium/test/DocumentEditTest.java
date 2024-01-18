package org.swdc.pdfium.test;

import org.swdc.pdfium.*;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;

public class DocumentEditTest {

    public static void main(String[] args) throws IOException {

        PdfiumPlatform.initializePdfium(new File("assets"));
        PdfiumDocument document = new PdfiumDocument();

        PdfiumDocumentPage page = document.createPage(0, 500, 600);
        page.close();

        document.write(new FileOutputStream("demo.pdf"));
        document.close();

        PdfiumDocument testExist = new PdfiumDocument(new File("./test2.pdf"));
        PdfiumDocumentPage testPg = testExist.getPage(1);
        PdfiumDocumentPage testCrPage = testExist.createPage(1,600 , 800);
        PdfiumDocumentPage testPg2 = testExist.getPage(2);

        testExist.removePage(testCrPage);

        testExist.write(new FileOutputStream("demo2.pdf"));
        testExist.close();
    }

}
