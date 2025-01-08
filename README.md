# Pdfium4j

> this project has move to cpp-presets .
> 本项目已经迁移到cpp-presets项目中，对该项目感兴趣请移步：
> 下面的链接是核心库，它直接封装了C++项目，使用时请注意内存问题。
> 
> https://github.com/SW-Fantastic/cpp-presets/tree/master/pdfium
> 
> 下面的链接是Java封装，可以直接使用，当然目前并不完善，还请耐心等待。
> 这个库我也会在合适的时候，为它编写响应的文档和说明。
> 
> https://github.com/SW-Fantastic/cpp-presets/tree/master/pdfium4j


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
PdfiumPlatform.initializePdfium(new File("assets"));
// you can see library in this folder  "assets/platform/pdfium"
```

and then , you can create PdfiumDocument and do anything you need.

