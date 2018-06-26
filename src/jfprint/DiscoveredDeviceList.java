package jfprint;

import jfprint.base.NativeResource;
import java.nio.ByteBuffer;
import static java.lang.String.format;

/**
 *
 * @author thiago
 */
public class DiscoveredDeviceList extends NativeResource {


    private ByteBuffer pointer;
    private int size;


    private DiscoveredDeviceList() {
    }


    /**
     * Close a device.
     *
     * Called by method "clearResources()".
     */
    @Override
    protected void clearResources() {
        nativeClose();
        pointer.clear();
        pointer = null;
    }


    /**
     * Free a list of discovered devices.
     *
     * This function destroys the list and all discovered devices that it included,
     * so make sure you have opened your discovered device before freeing the list.
     *
     * Called by method "clearResources()".
     */
    private native void nativeClose();

    private native DiscoveredDevice fp_get(int index);
    private static native DiscoveredDeviceList fp_dicoverDevices();


    public int size() {
        return size;
    }


    /**
     * Returns a discovered device from a list of discovered devices.
     *
     * @param index
     * @return discovered device instance
     */
    public DiscoveredDevice get(int index) {
        check();

        if (size == 0) {
            throw new ArrayIndexOutOfBoundsException("it is empty");
        }

        if (index >= size) {
            throw new ArrayIndexOutOfBoundsException(format("%d out of interval [0, %d[", index, size));
        }

        return fp_get(index);
    }


    /**
     * Scans the system and returns a list of discovered devices.
     *
     * @return    list of discovered devices. Must be freed with close() after use.
     */
    public static DiscoveredDeviceList dicoverDevices() {
        return fp_dicoverDevices();
    }


    /**
     * Searches a list of discovered devices for a device that appears to be compatible with a stored print.
     *
     * @param
     * @param
     * @return    the first discovered device that appears to
     *            support the print, or NULL if no apparently
     *            compatible devices could be found
     */
    //public native fp_dscv_dev fp_dscv_dev_for_print_data(fp_dscv_dev devs, fp_print_data data);


    /**
     * Searches a list of discovered devices for a device that appears to be compatible with a discovered print.
     *
     * @param
     * @param
     * @return    the first discovered device that appears to support the print,
     *            or NULL if no apparently compatible devices could be found
     */
    //fp_dscv_dev fp_dscv_dev_for_dscv_print(fp_dscv_dev devs, fp_dscv_print print	);
}
