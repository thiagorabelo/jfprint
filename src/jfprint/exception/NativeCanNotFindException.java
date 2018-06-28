package jfprint.exception;

import static java.lang.String.format;

/**
 *
 * @author thiago
 */
public class NativeCanNotFindException extends RuntimeException {

    private String cls;

    public NativeCanNotFindException(String cls) {
        super(format("Can not find class %s", cls));
        this.cls = cls;
    }

    public String getCls() {
        return cls;
    }
}
