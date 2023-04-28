package org.swdc.pdfium.internal;

public class PDFDocumentImpl {

    /**
     * 载入PDF文件，返回Pdfium的指针
     * @param absolutePath 文件路径
     * @return document pointer
     */
    public static native long loadDocument(String absolutePath);

    /**
     * 关闭PDF文件
     * @param pointer 文件的指针
     * @return 是否成功
     */
    public static native boolean closeDocument(long pointer);

    /**
     * 获取页面总数
     * @param pointer 文档指针
     * @return 页面数量
     */
    public static native int getPageCount(long pointer);


    /**
     * 载入一个PDF页面
     * @param pointer 文档指针
     * @param pageIndex 页面的index
     * @return 页面指针
     */
    public static native long loadPage(long pointer, int pageIndex);


    /**
     * 返回元数据
     * @param pointer Document的指针
     * @param metaType 想要获取的类型
     * @return
     */
    public static native String getMetadataText(long pointer,String metaType);

    /**
     * 返回第一个bookMark的指针。
     * @param pointer 文档的指针
     * @param parentBookMark 上级的bookmark指针，如果是顶级的bookmark，可以为空
     * @return
     */
    public static native long getFirstBookMark(long pointer, long parentBookMark);


    /**
     * 返回下一个Bookmark指针
     * @param pointer
     * @param currentBookMark
     * @return
     */
    public static native long getNextBookMark(long pointer, long currentBookMark);

    /**
     * 返回BookMark的PageIndex
     */
    public static native int getBookMarkPageIndex(long pointer,long bookMarkPointer);

    /**
     * 返回bookMark的标题
     * @param bookMarkPointer
     * @return
     */
    public static native String getBookMarkTitle(long bookMarkPointer);

}
