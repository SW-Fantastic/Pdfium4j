package org.swdc.pdfium;

import org.swdc.pdfium.internal.PDFPageObjectImpl;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;

public class PdfiumImageObject extends PdfiumPageObject {

    PdfiumImageObject(PdfiumDocumentPage page, long pointer, int index) {
        super(page, pointer, index);
    }

    public boolean loadImage(InputStream inputStream) throws IOException {
        checkState();
        BufferedImage image = ImageIO.read(inputStream);
        ByteArrayOutputStream os = new ByteArrayOutputStream();
        ImageIO.write(image,"jpg" , os);
        byte[] data = os.toByteArray();
        return PDFPageObjectImpl
                .loadObjectJpegData(this.getPointer(), data);
    }

    public boolean loadImageFile(File file) throws IOException {
        checkState();
        if (!file.exists()) {
            return false;
        }
        String name = file.getName().toLowerCase();
        byte[] data = null;
        if (name.endsWith("jpg") || name.endsWith("jpeg")) {
            data = Files.readAllBytes(file.toPath());
        } else {
            BufferedImage image = ImageIO.read(file);
            ByteArrayOutputStream os = new ByteArrayOutputStream();
            ImageIO.write(image,"jpg" , os);
            data = os.toByteArray();
        }
        return PDFPageObjectImpl
                .loadObjectJpegData(this.getPointer(), data);
    }


}
