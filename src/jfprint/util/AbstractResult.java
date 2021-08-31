package jfprint.util;

import jfprint.base.NativeResource;

import java.util.function.Consumer;
import java.util.function.Supplier;

public class AbstractResult<T extends NativeResource> {
    private final T value;

    protected AbstractResult(T t) {
        value = t;
    }

    public T getValue() {
        return value;
    }

    public boolean isPresent() {
        return value != null;
    }

    public AbstractResult<T> ifPresent(Consumer<? super T> consumer) {
        if (value != null)
            consumer.accept(value);
        return this;
    }

    public T orElse(T other) {
        return value != null ? value : other;
    }

    public T orElseGet(Supplier<? extends T> other) {
        return value != null ? value : other.get();
    }

    public <X extends Throwable> T orElseThrow(Supplier<? extends X> exceptionSupplier) throws X {
        if (value != null) {
            return value;
        } else {
            throw exceptionSupplier.get();
        }
    }

    public void closeIfPresent() {
        if (value != null) {
            value.close();
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }

        if (!(obj instanceof AbstractResult)) {
            return false;
        }

        return ((Result) obj).equals(value);
    }
}
