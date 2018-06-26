package jfprint.util;

import java.util.NoSuchElementException;
import java.util.Optional;

/**
 *
 * @author thiago
 */
public class Wrapper<T> {

    T obj;


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


    public void ifPresent(Consumer<T> consumer) {
        if (obj != null) {
            consumer.accept(obj);
        }
    }
}
