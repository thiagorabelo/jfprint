package jfprint;

import jfprint.base.NativeResource;
import java.nio.ByteBuffer;

/**
 *
 * @author thiago
 */
public class PrintData extends NativeResource {

    private static final int LEFT_THUMB = 1; /** thumb (left hand) */
	private static final int LEFT_INDEX = 2; /** index finger (left hand) */
	private static final int LEFT_MIDDLE = 3; /** middle finger (left hand) */
	private static final int LEFT_RING = 4; /** ring finger (left hand) */
	private static final int LEFT_LITTLE = 5; /** little finger (left hand) */
	private static final int RIGHT_THUMB = 6; /** thumb (right hand) */
	private static final int RIGHT_INDEX = 7; /** index finger (right hand) */
	private static final int RIGHT_MIDDLE = 8; /** middle finger (right hand) */
	private static final int RIGHT_RING = 9; /** ring finger (right hand) */
	private static final int RIGHT_LITTLE = 10; /** little finger (right hand) */


    private ByteBuffer pointer;


    private PrintData() {
    }


    @Override
    protected void clearResources() {
        nativeClose();
        pointer.clear();
        pointer = null;
    }


    // Frees a stored print.
    private native void nativeClose();

    private native byte [] fp_getData();
    private static native PrintData fp_fromData(byte []buffer);
    private native int fp_dataSave(int finger);
    private static native PrintData fp_dataLoad(Device device, int finger);
    private static native int fp_delete(Device device, int finger);
    private static native PrintData fp_fromDiscoveredPrint(DiscoveredPrint discoveredPrint);
    private native long fp_getDriverId();
    private native long fp_getDevtype();


    // Convert a stored print into a unified representation inside a data buffer.
    public byte [] getData() {
        check();
        return fp_getData();
    }


 	// Load a stored print from a data buffer.
    public static PrintData fromData(byte []buffer) {
        return fp_fromData(buffer);
    }


    // Saves a stored print to disk, assigned to a specific finger.
    public int dataSave(int finger) {
        check();
        return fp_dataSave(finger);
    }


 	// Loads a previously stored print from disk.
    public static PrintData dataLoad(Device device, int finger) {
        return fp_dataLoad(device, finger);
    }


 	// Removes a stored print from disk previously saved with fp_print_data_save().
    public static int delete(Device device, int finger) {
        return fp_delete(device, finger);
    }


 	// Attempts to load a stored print based on a discovered print record.
    public static PrintData fromDiscoveredPrint(DiscoveredPrint discoveredPrint) {
        return fp_fromDiscoveredPrint(discoveredPrint);
    }


 	// Gets the driver ID for a stored print.
    public long getDriverId() {
        check();
        return fp_getDriverId();
    }


 	// Gets the devtype for a stored print.
    public long getDevtype() {
        check();
        return fp_getDevtype();
    }
}
