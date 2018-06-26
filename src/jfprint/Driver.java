package jfprint;

import jfprint.base.NativeResource;
import java.nio.ByteBuffer;

/**
 *
 * @author thiago
 *
 * It does not need to be freed.
 */
public class Driver extends NativeResource {

    private ByteBuffer pointer;

    private Driver() {
    }


    @Override
    protected void clearResources() {
        pointer.clear();
        pointer = null;
    }


    /**
     *
     */
    private native void nativeClose();


    /**
     * Retrieves the name of the driver.
     *
     * @return The driver name.
     */
    public native String getName();


    /**
     * Retrieves a descriptive name of the driver.
     *
     * @return The descriptive name of the driver.
     */
    public native String getFullName();


    /**
     * Retrieves the driver ID code for a driver.
     *
     * @return The driver ID.
     */
    public native long getDriverID();
}
