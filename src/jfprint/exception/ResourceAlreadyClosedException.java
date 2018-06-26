package jfprint.exception;

import static java.lang.String.format;

/**
 *
 * @author thiago
 */
public class ResourceAlreadyClosedException extends RuntimeException {

    public ResourceAlreadyClosedException(Class cls) {
        super(format("%s instance has already been closed", cls.getCanonicalName()));
    }
}
