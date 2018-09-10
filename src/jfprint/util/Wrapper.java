package jfprint.util;

import java.util.NoSuchElementException;
import jfprint.base.NativeResource;

/**
 *
 * @author thiago
 */
public class Wrapper<T extends NativeResource> {

    protected T obj = null;


    public Wrapper() {
    }


    public Wrapper(T obj) {
        this.obj = obj;
    }


    public T get() {
        if (obj == null) {
            throw new NoSuchElementException("Wrapper is empty");
        }

        return obj;
    }


//    public T set(T obj) {
//        T older = this.obj;
//        this.obj = obj;
//        return older;
//    }


    public boolean isPresent() {
        return obj != null;
    }


    public Wrapper<T> ifPresent(Consumer<T> consumer) {
        if (obj != null) {
            consumer.accept(obj);
        }
        return this;
    }

    public void closeIfPresent() {
        if (obj != null) {
            obj.close();
        }
    }
}
