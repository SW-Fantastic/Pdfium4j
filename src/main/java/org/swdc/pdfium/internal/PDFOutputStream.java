package org.swdc.pdfium.internal;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.ByteBuffer;

public class PDFOutputStream extends OutputStream {

    private OutputStream dest;

    public PDFOutputStream(OutputStream dest) {
        this.dest = dest;
    }

    /**
     * JNI 通过这个方法把PDF的数据推到Java。
     * @param byteBuffer buffer
     * @param length buffer length
     * @throws IOException
     */
    public void write(ByteBuffer byteBuffer, int length) throws IOException {
        byte[] data = new byte[length];
        byteBuffer.get(data);
        dest.write(data);
    }

    @Override
    public void write(int b) throws IOException {
        dest.write(b);
    }

    @Override
    public void close() throws IOException {
        dest.close();
    }
}
