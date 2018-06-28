package jfprint.exception;

import static java.lang.String.format;

/**
 *
 * @author thiago
 */
public class ClassNativeException extends NativeException {

    private Class cls;

    public ClassNativeException(Class cls, String msg, String funcName, String locationInfo) {
        super(msg, funcName, locationInfo);

        this.cls = cls;
    }

    @Override
    public String getMessage() {
        return format("%s of class %s. Native Info: %s %s", getOriginalMessage(), cls.getCanonicalName(), getLocationInfo(), getFuncName());
    }
}
