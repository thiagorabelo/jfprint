package jfprint;

import jfprint.util.EnrollProgressInterface;
import jfprint.base.NativeResource;
import java.nio.ByteBuffer;

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

    native private String native_get_driver();
    native private String native_get_device_id();
    native private String native_get_name();
    native private boolean native_open();
    native private boolean native_close();
    native private FpPrint native_enroll(EnrollProgressInterface progress, TemplatePrint templatePrint);  // TODO: Fazer receber TemplatePrint


    private ByteBuffer pointer;


    private FpDevice() {}

    public String getDriver() {
        return native_get_driver();
    }

    public String getDeviceId() {
        return native_get_device_id();
    }

    public String getName() {
        return native_get_name();
    }

    public boolean openDevice() {
        return native_open();
    }

    public boolean closeDevice() {
        return native_close();
    }

    public FpPrint enroll(EnrollProgressInterface progress, TemplatePrint templatePrint) {
        return native_enroll(progress, templatePrint);
    }

    @Override
    protected void clearResources() {
        nativeClose();
        pointer.clear();
        pointer = null;
    }
}
