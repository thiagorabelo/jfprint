package jfprint.exception;

/**
 *
 * @author thiago
 */
public class CodeError extends Exception {

    int code;

    public CodeError(int code) {
        super();
        this.code = code;
    }

    public int getCode() {
        return code;
    }
}
