package jfprint.util;

/**
 *
 * @author thiago
 * @param <T> The type of input operation
 */
@FunctionalInterface
public interface Consumer<T> {
    public void accept(T value);
}
