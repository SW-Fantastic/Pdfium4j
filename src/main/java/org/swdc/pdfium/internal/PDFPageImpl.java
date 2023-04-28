package org.swdc.pdfium.internal;

import java.nio.ByteBuffer;

public class PDFPageImpl {

    /**
     * 关闭此Page
     * @param pointer Page指针
     * @return 是否成功关闭
     */
    public static native boolean closePage(long pointer);

    public static native float getWidthF(long pointer);

    public static native float getHeightF(long pointer);

    public static native int getWidth(long pointer);

    public static native int getHeight(long pointer);

    /**
     * 是否有透明的部分。
     * @param pointer page指针
     * @return 是否含有透明部分
     */
    public static native boolean hasTransparency(long pointer);

    /**
     * 读取页面的标题。
     * @param documentPointer
     * @param pageIndex
     * @return
     */
    public static native String getPageTitle(long documentPointer, int pageIndex);


    /**
     * 渲染页面到指定的image。
     * @param pointer 页面指针
     * @param imagePointer 图像指针
     * @param x
     * @param y
     * @param width
     * @param height
     * @param rotation  0 (normal)
     *                  1 (rotated 90 degrees clockwise)
     *                  2 (rotated 180 degrees)
     *                  3 (rotated 90 degrees counter-clockwise)
     *
     * @return 是否成功渲染图片
     */

    public static native boolean renderBitmapImage(long pointer, long imagePointer, int x, int y, int width, int height, int rotation);

}
