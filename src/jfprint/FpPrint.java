package jfprint;

import jfprint.base.NativeResource;

import java.nio.ByteBuffer;

public class FpPrint extends NativeResource {

    native private void nativeClose();

    native private int native_get_finger();


    private ByteBuffer pointer;

    public FpFinger getFinger() {
        int finger_value = native_get_finger();
        return FpFinger.getByValue(finger_value);
    }

    @Override
    protected void clearResources() {
        nativeClose();
        pointer.clear();
        pointer = null;
    }
}
