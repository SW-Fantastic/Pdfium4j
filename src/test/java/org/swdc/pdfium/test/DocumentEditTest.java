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
        PdfiumImageObject object = document.createImageObject();
        if(object.loadImageFile(new File("test.jpg"))) {
            object.setBounds(120, 160, 0, 0);
            page.insertObject(object);
        }

        PdfiumFont font = document.loadFont(new File("font.ttf"));
        PdfiumTextObject textObject = document.createTextObject(font, 0.15f);
        textObject.setText("测试文本");
        textObject.setBounds(100, 80, 100, 400);
        page.insertObject(textObject);
        System.err.println(textObject.getText());
        System.err.println(font.getFontName());
        System.err.println("font embedded : " + font.isEmbedded());
        System.err.println("font size : " + textObject.getFontSize());
        font.close();

        PdfiumTextObject text = document.createTextObject("Arial", 0.25f);
        text.setText("Demo String");
        text.setBounds(100, 80, 0, 200);
        page.insertObject(text);
        System.err.println(text.getText());

        OutputStream os = Files.newOutputStream(Paths.get("test2.png"));
        PdfiumBitmapImage image = page.renderPage(4);
        BufferedImage image1 = image.createBufferedImage();
        ImageIO.write(image1,"png" ,os );

        page.generateContent();
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
