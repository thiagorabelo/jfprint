package jfprint.util;

import jfprint.base.NativeResource;


public final class Result<T extends NativeResource> extends AbstractResult<T> {
    private final int code;

    private Result(int code, T value) {
        super(value);
        this.code = code;
    }

    public static Result empty() {
        return new Result(0, null);
    }

    public static <T extends NativeResource> Result of(int code, T value) {
        return new Result(code, value);
    }

    public int getCode() {
        return code;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }

        if (!(obj instanceof Result)) {
            return false;
        }

        return code == ((Result) obj).code && super.equals(obj);
    }
}
