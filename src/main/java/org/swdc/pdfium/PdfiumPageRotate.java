package org.swdc.pdfium;

public enum PdfiumPageRotate {

    NO_ROTATE(0),
    CLOCKWISE_90(1),
    HORIZONTAL_FLIP(2),
    COUNTER_CLOCKWISE_90(3);

    private int value;
    PdfiumPageRotate(int val) {
        this.value = val;
    }

    public int getValue() {
        return value;
    }

    public static PdfiumPageRotate of(int val) {
        for (PdfiumPageRotate v: values()) {
            if (v.value == val) {
                return v;
            }
        }
        return null;
    }
}
