package org.swdc.pdfium.internal;

import java.nio.ByteBuffer;

public class PDFBitmapImpl {

    public static native long createBitmap(int width, int height, boolean hasAlpha);

    public static native void fillRect(long pointer,int left, int top, int width, int height, long color);

    public static native int getWidth(long pointer);

    public static native int getHeight(long pointer);

    public static native int getStride(long pointer);

    public static native ByteBuffer getBuffer(long pointer);

    public static native boolean releaseBitmap(long pointer);

}
