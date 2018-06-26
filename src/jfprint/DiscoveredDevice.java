package jfprint;

import jfprint.base.NativeResource;
import java.nio.ByteBuffer;

/**
 *
 * @author thiago
 *
 * It does not need to be freed.
 */
public class DiscoveredDevice extends NativeResource {


    private ByteBuffer pointer;


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

    private native Device fp_open();


    /**
     * Opens and initialises a device.
     *
     * This is the function you call in order to convert a discovered device
     * into an actual device handle that you can perform operations with.
     *
     * @return    the opened device handle, or {@code null} on error.
     */
    public Device open() {
        check();
        return fp_open();
    }


    /**
     * Gets the driver for a discovered device.
     *
     * @param
     * @return    the driver backing the device
     */
    //public native Driver fp_dscv_dev_get_driver(fp_dscv_dev dev);


    /**
     * Gets the devtype for a discovered device.
     *
     * @param
     * @return    the devtype of the device
     */
    //public native uint32_t fp_dscv_dev_get_devtype(fp_dscv_dev dev);


    /**
     * Determines if a specific stored print appears to be compatible with a discovered device.
     *
     * @param
     * @param
     * @return
     */
    //public native boolean fp_dscv_dev_supports_print_data(fp_dscv_dev dev, fp_print_data data);


    /**
     * Determines if a specific discovered print appears to be compatible with a discovered device.
     *
     * @param
     * @param
     * @return    1 if the print is compatible with the device, 0 otherwise.
     */
    //public native int fp_dscv_dev_supports_dscv_print(fp_dscv_dev dev, fp_dscv_print data);
}
