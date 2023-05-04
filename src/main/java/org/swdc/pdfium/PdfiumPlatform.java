package org.swdc.pdfium;

import java.io.File;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.List;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class PdfiumPlatform {

    private static List<String> arch64 = Arrays.asList(
            "amd64","x64","x86_64"
    );

    public static void initializePdfium(File platformFolder) {
        if (!platformFolder.exists()) {
            if(!platformFolder.mkdirs()) {
                throw new RuntimeException("can not create native library folder: " + platformFolder.getAbsolutePath());
            }
        }
        String osArch = System.getProperty("os.arch");
        if (arch64.contains(osArch.toLowerCase())) {
            osArch = "x64";
        }

        File libFileLocation = platformFolder.getAbsoluteFile();
        String osName = System.getProperty("os.name").trim().toLowerCase();

        String resourceName = null;
        String libPrefix = "";
        String libSubfix = "";
        if (osName.contains("windows")) {
            libSubfix = "dll";
            resourceName = "/plafromPdfium/" + "windows-" + osArch + ".zip";
        } else if (osName.contains("mac")) {
            libPrefix = "lib";
            libSubfix = "dylib";
            resourceName = "/plafromPdfium/" + "macos-" + osArch + ".zip";
            String url = PdfiumPlatform.class.getProtectionDomain().getCodeSource().getLocation().getFile();
            String base = URLDecoder.decode(url, StandardCharsets.UTF_8);
            if (base.indexOf(".app") > 0) {
                // 位于MacOS的Bundle（.app软件包）内部，特殊处理以获取正确的路径。
                String location = base.substring(0, base.indexOf(".app")) + ".app/Contents/";
                Path target = new File(location).toPath();
                libFileLocation = target.resolve(platformFolder.getName()).toFile();
            }
        } else if (osName.contains("linux")) {
            libPrefix = "lib";
            libSubfix = "so";
            resourceName = "/plafromPdfium/" + "linux-" + osArch + ".zip";

        }

        if (resourceName == null) {
            throw new RuntimeException("this library does not support your system.");
        }

        File libPdfium = new File(libFileLocation.getAbsolutePath() + File.separator + libPrefix + "pdfium." + libSubfix);
        File libPdfiumSdk = new File(libFileLocation.getAbsolutePath() + File.separator + libPrefix + "pdfiumSDK." + libSubfix);
        if (!libPdfium.exists() || !libPdfiumSdk.exists()) {
            doExtractZip(libFileLocation,resourceName);
        }
        System.load(libPdfium.getAbsolutePath());
        System.load(libPdfiumSdk.getAbsolutePath());
    }

    private static void doExtractZip(File nativeFolder, String resourceName) {
        try {
            InputStream binaryInput = PdfiumPlatform.class.getModule()
                    .getResourceAsStream(resourceName);
            if (binaryInput == null) {
                throw new RuntimeException("this library does not support your system.");
            }
            ZipInputStream zin = new ZipInputStream(binaryInput);
            ZipEntry entry = null;
            Path basePath = nativeFolder.toPath();
            if (!Files.exists(basePath)) {
                Files.createDirectories(basePath);
            }
            while ((entry = zin.getNextEntry()) != null) {
                if (entry.isDirectory()) {
                    continue;
                }
                Path filePath = basePath.resolve(entry.getName());
                Path folder = filePath.getParent();
                if (!Files.exists(folder)) {
                    Files.createDirectories(folder);
                }
                OutputStream os = Files.newOutputStream(filePath);
                zin.transferTo(os);
                os.close();
            }
            zin.close();
            binaryInput.close();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

}
