package jfprint.exception;

import static java.lang.String.format;

/**
 *
 * @author thiago
 */
public class NativeException extends RuntimeException {

    private String when;
    private String funcName;
    private String locationInfo;

    public NativeException(String msg, String funcName, String locationInfo) {
        super(msg);

        this.when = null;
        this.funcName = funcName;
        this.locationInfo = locationInfo;
    }

    public NativeException(String msg, String when, String funcName, String locationInfo) {
        super(msg);

        this.when = when;
        this.funcName = funcName;
        this.locationInfo = locationInfo;
    }

    public NativeException(Throwable cause, String msg, String funcName, String locationInfo) {
        super(msg, cause);

        this.when = null;
        this.funcName = funcName;
        this.locationInfo = locationInfo;
    }

    public NativeException(Throwable cause, String msg, String when, String funcName, String locationInfo) {
        super(msg, cause);

        this.when = when;
        this.funcName = funcName;
        this.locationInfo = locationInfo;
    }

    @Override
    public String getMessage() {
        if (when == null) {
            return format("%s. Native Info: %s - %s", getOriginalMessage(), locationInfo, funcName);
        } else {
            return format("%s. When: %s. Native Info: %s - %s", getOriginalMessage(), when, locationInfo, funcName);
        }
    }

    public String getOriginalMessage() {
        return super.getMessage();
    }

    public String getWhen() {
        return when;
    }

    public String getFuncName() {
        return funcName;
    }

    public String getLocationInfo() {
        return locationInfo;
    }
}
