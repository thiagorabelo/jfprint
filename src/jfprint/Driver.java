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
        nativeClose();
        pointer.clear();
        pointer = null;
    }


    /**
     * Close a device.
     *
     * Called by method "clearResources()".
     */
    private native void nativeClose();

    private native String fp_getName();
    private native String fp_getFullName();
    private native long fp_getDriverID();


    /**
     * Retrieves the name of the driver.
     *
     * @return The driver name.
     */
    public String getName() {
        check();
        return fp_getName();
    }


    /**
     * Retrieves a descriptive name of the driver.
     *
     * @return The descriptive name of the driver.
     */
    public String getFullName() {
        check();
        return fp_getFullName();
    }


    /**
     * Retrieves the driver ID code for a driver.
     *
     * @return The driver ID.
     */
    public long getDriverID() {
        check();
        return fp_getDriverID();
    }
}
