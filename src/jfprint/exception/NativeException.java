package jfprint.exception;

import static java.lang.String.format;

/**
 *
 * @author thiago
 */
public class NativeException extends RuntimeException {

    private String funcName;
    private String locationInfo;

    public NativeException(String msg, String funcName, String locationInfo) {
        super(msg);

        this.funcName = funcName;
        this.locationInfo = locationInfo;
    }

    public NativeException(Throwable cause, String msg, String funcName, String locationInfo) {
        super(msg, cause);

        this.funcName = funcName;
        this.locationInfo = locationInfo;
    }

    @Override
    public String getMessage() {
        return format("%s. Native Info: %s %s", getOriginalMessage(), locationInfo, funcName);
    }

    public String getOriginalMessage() {
        return super.getMessage();
    }

    public String getFuncName() {
        return funcName;
    }

    public String getLocationInfo() {
        return locationInfo;
    }
}
