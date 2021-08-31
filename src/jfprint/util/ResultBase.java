package jfprint.util;

import jfprint.base.NativeResource;


public final class ResultBase<T extends NativeResource> extends AbstractResult<T> {

    protected ResultBase(T value) {
        super(value);
    }

    public static ResultBase empty() {
        return new ResultBase(null);
    }

    public static <T extends NativeResource> ResultBase of(T value) {
        return new ResultBase(value);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }

        if (!(obj instanceof Result)) {
            return false;
        }

        return super.equals(obj);
    }
}
