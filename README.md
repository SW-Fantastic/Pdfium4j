# Pdfium4j

this is the PDF render based Google PDFium, only support 
render the pdf file now。

基于PDFium的PDF渲染类库，通过JNI对PDFium进行了包装，目前支持的功能
有限，推荐和PDFBox等其他PDF类库配合使用。

关于PDFium的二进制包，我使用了此项目：
https://github.com/bblanchon/pdfium-binaries


## Get start

clone this project and install to your local-maven-repo
and then add it into your project want to use.

this library need java version 11 or higher and support 
`Windows x64`，`MacOS x64` system.

using this method to initialize the pdfium sdk:

```java
// where should the library extract and load the native library
PdfiumPlatform.initializePdfium(new File("platform"));
```

and then , you can create PdfiumDocument and do anything you need.

