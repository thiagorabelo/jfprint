package jfprint.util;

import jfprint.base.NativeResource;

public class ResultTuple<A extends NativeResource, B extends NativeResource> {
    private final int code;
    private final ResultBase<A> first;
    private final ResultBase<B> second;

    private ResultTuple(int code, A first, B second) {
        this.code = code;
        this.first = ResultBase.of(first);
        this.second = ResultBase.of(second);
    }

    public static ResultTuple empty() {
        return new ResultTuple(0, null, null);
    }

    public static <A extends NativeResource, B extends NativeResource> ResultTuple of(int code, A first, B second) {
        return new ResultTuple(code, first, second);
    }

    public int getCode() {
        return code;
    }

    public ResultBase<A> getFirst() {
        return first;
    }

    public ResultBase<B> getSecond() {
        return second;
    }

    public void closeIfPresent() {
        first.closeIfPresent();
        second.closeIfPresent();
    }
}
