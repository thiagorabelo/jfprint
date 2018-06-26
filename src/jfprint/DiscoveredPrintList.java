package jfprint;

import jfprint.base.NativeResource;
import static java.lang.String.format;
import java.nio.ByteBuffer;

/**
 *
 * @author thiago
 */
public class DiscoveredPrintList extends NativeResource {

    private ByteBuffer pointer;
    private int size;


    private DiscoveredPrintList() {
    }


    @Override
    protected void clearResources() {
        nativeClose();
        pointer.clear();
        pointer = null;
    }


    /**
     * Frees a list of discovered prints.
     *
     * This function also frees the discovered prints themselves,
     * so make sure you do not use any discovered prints after
     * calling this function.
     *
     * Called by method "clearResources()".
     */
    private native void nativeClose();

    private native DiscoveredPrint fp_get(int index);
    private static native DiscoveredPrintList fp_discoverPrints();


    public int size() {
        return size;
    }


    /**
     * Returns a discovered device from a list of discovered devices.
     *
     * @param index
     * @return discovered device instance
     */
    public DiscoveredPrint get(int index) {
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
     * Scans the users home directory and returns a list of prints that
     * were previously saved using {@link jfprint.PrintData#dataSave()}.
     *
     * @return    list of discovered prints, must be freed with close() after use.
     */
    public static DiscoveredPrintList discoverPrints() {
        return fp_discoverPrints();
    }
}
