package jfprint.exception;

import static java.lang.String.format;

/**
 *
 * @author thiago
 */
// TODO: This is the worst name ever. Give me a better name.
public class ClassNativeException extends NativeException {

    private Class cls;

    public ClassNativeException(Throwable cause, Class cls, String msg, String funcName, String locationInfo) {
        super(cause, msg, funcName, locationInfo);
        this.cls = cls;
    }

    public ClassNativeException(Throwable cause, Class cls, String msg, String when, String funcName, String locationInfo) {
        super(cause, msg, when, funcName, locationInfo);
        this.cls = cls;
    }

    public ClassNativeException(Class cls, String msg, String funcName, String locationInfo) {
        super(msg, funcName, locationInfo);
        this.cls = cls;
    }

    public ClassNativeException(Class cls, String msg, String when, String funcName, String locationInfo) {
        super(msg, when, funcName, locationInfo);
        this.cls = cls;
    }

    @Override
    public String getMessage() {
        return format("%s of class %s. Native Info: %s %s", getOriginalMessage(), cls.getCanonicalName(), getLocationInfo(), getFuncName());
    }
}
