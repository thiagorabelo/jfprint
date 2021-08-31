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

    native private static FpContext context_new();
    native private int n_devices();
    native private FpDevice get_device(int index);


    private ByteBuffer pointer;

    private FpContext() {}

    public static FpContext contextNew() {
        return context_new();
    }

    public int numDevices() {
        return n_devices();
    }

    public FpDevice getDevice(int index) {
        return get_device(index);
    }

    @Override
    protected void clearResources() {
        nativeClose();
        pointer.clear();
        pointer = null;
    }
}
