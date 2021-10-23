package jfprint;

import jfprint.base.NativeResource;

import java.nio.ByteBuffer;

/**
 *
 * @author thiago
 */
public class FpContext extends NativeResource {

    static {
        System.loadLibrary("fprint-2");
        System.loadLibrary("jfprint_jni");
    }

    native private void nativeClose();

    native private static FpContext native_context_new();
    native private int native_n_devices();
    native private FpDevice native_get_device(int index);


    private ByteBuffer pointer;

    private FpContext() {}

    public static FpContext contextNew() {
        return native_context_new();
    }

    public int numDevices() {
        return native_n_devices();
    }

    public FpDevice getDevice(int index) {
        return native_get_device(index);
    }

    @Override
    protected void clearResources() {
        nativeClose();
        pointer.clear();
        pointer = null;
    }
}
