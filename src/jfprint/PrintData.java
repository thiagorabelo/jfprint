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


    // Convert a stored print into a unified representation inside a data buffer.
    public native byte [] getData();


 	// Load a stored print from a data buffer.
    public static native PrintData fromData(byte []buffer);


    // Saves a stored print to disk, assigned to a specific finger.
    public native int dataSave(int finger);


 	// Loads a previously stored print from disk.
    public static native PrintData dataLoad(Device device, int finger);


 	// Removes a stored print from disk previously saved with fp_print_data_save().
    public static native int delete(Device device, int finger);


 	// Attempts to load a stored print based on a discovered print record.
    public static native PrintData fromDiscoveredPrint(DiscoveredPrint discoveredPrint);


 	// Gets the driver ID for a stored print.
    public native long getDriverId();


 	// Gets the devtype for a stored print.
    public native long getDevtype();
}
