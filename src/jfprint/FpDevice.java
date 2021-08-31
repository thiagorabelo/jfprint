package jfprint;

import jfprint.base.NativeResource;
import java.nio.ByteBuffer;
import jfprint.exception.CodeError;
import jfprint.util.Result;
import jfprint.util.ResultTuple;

/**
 *
 * @author thiago
 */
public class FpDevice extends NativeResource {

    // https://fprint.freedesktop.org/libfprint-stable/

    /* Definido em "fprint.h" */
//    public static final int FP_ENROLL_COMPLETE = 1;
//    public static final int FP_ENROLL_FAIL = 2;
//    public static final int FP_ENROLL_PASS = 3;
//    public static final int FP_ENROLL_RETRY = 100;
//    public static final int FP_ENROLL_RETRY_TOO_SHORT = 101;
//    public static final int FP_ENROLL_RETRY_CENTER_FINGER = 102;
//    public static final int FP_ENROLL_RETRY_REMOVE_FINGER = 103;


    /* Definido em "fprint.h" */
//    public static final int FP_VERIFY_NO_MATCH = 0;
//    public static final int FP_VERIFY_MATCH = 1;
//    public static final int FP_VERIFY_RETRY = FP_ENROLL_RETRY;
//    public static final int FP_VERIFY_RETRY_TOO_SHORT = FP_ENROLL_RETRY_TOO_SHORT;
//    public static final int FP_VERIFY_RETRY_CENTER_FINGER = FP_ENROLL_RETRY_CENTER_FINGER;
//    public static final int FP_VERIFY_RETRY_REMOVE_FINGER = FP_ENROLL_RETRY_REMOVE_FINGER;


    native private void nativeClose();

    native private String get_driver();
    native private String get_device_id();
    native private String get_name();


    private ByteBuffer pointer;

    private FpDevice() {}

    public String getDriver() {
        return get_driver();
    }

    public String getDeviceId() {
        return get_device_id();
    }

    public String getName() {
        return get_name();
    }

    @Override
    protected void clearResources() {
        nativeClose();
        pointer.clear();
        pointer = null;
    }
}
