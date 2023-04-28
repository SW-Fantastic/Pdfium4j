# https://github.com/bblanchon/pdfium-binaries
# PDFium可以在这里下载。
PDFDocumentImpl.o:
	gcc -c ./src/PDFDocumentImpl.c -o PDFDocumentImpl.o

PDFPageImpl.o: 
	gcc -c ./src/PDFPageImpl.c -o PDFPageImpl.o

PDFBitmapImpl.o :
	gcc -c ./src/PDFBitmapImpl.c -o PDFBitmapImpl.o

all: PDFDocumentImpl.o PDFPageImpl.o PDFBitmapImpl.o
	gcc PDFDocumentImpl.o PDFPageImpl.o PDFBitmapImpl.o -L./pdfium_universal/lib/ -lpdfium -fPIC -shared -o libPdfiumSDK.dylib

clean: 
	rm PDFDocumentImpl.o
	rm PDFPageImpl.o
	rm PDFBitmapImpl.o
	rm 	libPdfiumSDK.dylib