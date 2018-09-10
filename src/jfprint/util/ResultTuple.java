package jfprint.util;

import jfprint.base.NativeResource;


/**
 *
 * @author thiago
 */
public class ResultTuple<T extends NativeResource> extends Wrapper<T> {

    int result;

    public ResultTuple(int result) {
        super();
        this.result = result;
    }

    public ResultTuple(T obj, int result) {
        super(obj);
        this.result = result;
    }

    public int getResult() {
        return result;
    }
}
