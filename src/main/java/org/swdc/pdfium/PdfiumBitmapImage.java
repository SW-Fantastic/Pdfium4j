package org.swdc.pdfium;

import org.swdc.pdfium.internal.PDFBitmapImpl;

import java.awt.*;
import java.awt.color.ColorSpace;
import java.awt.image.*;
import java.io.Closeable;
import java.io.IOException;
import java.nio.ByteBuffer;

public class PdfiumBitmapImage implements Closeable {

    private Long pointer;

    public PdfiumBitmapImage(int width, int height, boolean hasAlpha) throws IOException {
        long pointer = PDFBitmapImpl.createBitmap(width, height, hasAlpha);
        if (pointer == -1) {
            throw new IOException("can not create bitmap image.");
        }
        this.pointer = pointer;
    }

    public int getWidth() throws IOException {
        checkState();
        return PDFBitmapImpl.getWidth(pointer);
    }

    public int getHeight() throws IOException {
        checkState();
        return PDFBitmapImpl.getHeight(pointer);
    }

    public void fillRect(int left, int top, int width, int height, String hex) throws IOException {
        checkState();
        PDFBitmapImpl.fillRect(
                pointer,
                left ,
                top ,
                width ,
                height ,
                Long.parseUnsignedLong(hex, 16)
        );
    }

    public int getStride() throws IOException {
        checkState();
        return PDFBitmapImpl.getStride(pointer);
    }

    public ByteBuffer getBuffer() throws IOException {
        checkState();
        return PDFBitmapImpl.getBuffer(pointer);
    }

    private void checkState() throws IOException {
        if (pointer == null || pointer == -1) {
            throw new IOException("the document has closed.");
        }
    }

    public BufferedImage createBufferedImage() throws IOException {

        ByteBuffer byteBuffer = getBuffer();
        byte[] data = new byte[byteBuffer.capacity()];
        byteBuffer.get(data);

        int width = getWidth();
        int height = getHeight();

        DataBuffer dataBuffer = new DataBufferByte(data,width * height * 4);
        ColorModel colorModel = new ComponentColorModel(ColorSpace.getInstance(ColorSpace.CS_sRGB),
                new int[] {8,8,8,8}, true, false, Transparency.OPAQUE, DataBuffer.TYPE_BYTE);
        WritableRaster raster = Raster.createInterleavedRaster(
                dataBuffer, width, height, width * 4, 4, new int[] {0, 1, 2, 3}, null);
        return new BufferedImage(colorModel, raster, false, null);
    }

    @Override
    public void close() throws IOException {
        if (pointer == null || pointer == -1) {
            return;
        }
        if(!PDFBitmapImpl.releaseBitmap(pointer)) {
            throw new IOException("failed to release image.");
        } else {
            pointer = null;
        }
    }

    final Long getPointer() {
        return pointer;
    }
}
