package org.swdc.pdfium.internal;

public class PDFPageObjectImpl {


    /**
     * 获取PageObject的数量
     * @param pagePointer page指针
     * @return PageObject对象的数量
     */
    public static native int getObjectCount(long pagePointer);

    /**
     * 获取指定的PageObject
     * @param pagePointer 页面指针
     * @param objectIndex PageObject的Index
     * @return 指定的PageObject的指针。
     */
    public static native long getPageObject(long pagePointer, int objectIndex);

    /**
     * 获取指定PageObject的类型
     * @param objectPointer PageObject的指针
     * @return 类型
     * @see org.swdc.pdfium.PageObjectType
     */
    public static native int getPageObjectType(long objectPointer);

    /**
     * 销毁指定的PageObject
     * 危险操作，只有未插入文档的PageObject可以销毁。
     * @param objectPointer PageObject的指针。
     * @return 是否销毁成功。
     */
    public static native boolean destroyObject(long objectPointer);


    public static native long createImageObject(long documentPointer);

}