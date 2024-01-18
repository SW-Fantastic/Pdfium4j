package org.swdc.pdfium;

public enum PageObjectType {

    UNKNOWN(0),
    TEXT(1),
    PATH(2),
    IMAGE(3),
    SHADING(4),
    FORM(5)

    ;

    private int type;

    PageObjectType(int val) {
        this.type = val;
    }

    public int getType() {
        return type;
    }

    public static PageObjectType of(int type) {
        for (PageObjectType item: values()) {
            if (item.getType() == type) {
                return item;
            }
        }
        return UNKNOWN;
    }
}
