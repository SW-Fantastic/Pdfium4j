package org.swdc.pdfium.internal;

import java.nio.ByteBuffer;

public class PDFPageImpl {

    /**
     * 添加一个新的PDF页面
     * @param documentPointer PDF文档指针
     * @param index 页面index
     * @param width 宽度
     * @param height 高度
     * @return 新页面指针（失败则是0）
     */
    public static native long createPage(long documentPointer,int index, double width, double height);

    /**
     * 删除一页
     * @param documentPointer document指针
     * @param pageIndex page的Index
     */
    public static native void removePage(long documentPointer, int pageIndex);

    /**
     * 关闭此Page
     * @param pointer Page指针
     * @return 是否成功关闭
     */
    public static native boolean closePage(long pointer);

    /**
     * 页面的宽度
     * @param pointer
     * @return 页面的宽度
     */
    public static native float getWidthF(long pointer);

    /**
     * 获取页面的高度
     * @param pointer
     * @return Float类型的页面高度
     */
    public static native float getHeightF(long pointer);

    /**
     * 页面的宽度
     * @param pointer
     * @return 页面的宽度
     */
    public static native int getWidth(long pointer);

    /**
     * 获取页面的高度
     * @param pointer
     * @return Float类型的页面高度
     */
    public static native int getHeight(long pointer);

    /**
     * 页面的旋转角度
     * @param pointer page指针
     * @return 角度
     */
    public static native int getRotation(long pointer);

    /**
     * 设置页面的旋转角度
     * @param pointer 页面指针
     * @param rotation 角度
     */
    public static native void setRotation(long pointer, int rotation);

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

    public static native boolean generateContent(long pointer);
}
