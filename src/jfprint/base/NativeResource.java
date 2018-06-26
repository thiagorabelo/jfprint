package jfprint.base;

import java.io.Closeable;
import jfprint.exception.ResourceAlreadyClosedException;

/**
 *
 * @author thiago
 */
public abstract class NativeResource implements Closeable {

    private boolean closed = false;

    protected abstract void clearResources();


    protected void check() {
        if (closed) {
            throw new ResourceAlreadyClosedException(this.getClass());
        }
    }


    @Override
    public void close() {
        if (!closed) {
            clearResources();
            closed = true;
        }
    }

    @Override
    protected void finalize() throws Throwable {
        try {
            close();
        } finally {
            super.finalize();
        }
    }
}
