package jfprint;

import jfprint.base.NativeResource;
import java.nio.ByteBuffer;

/**
 *
 * @author thiago
 */
public class DiscoveredPrint extends NativeResource {

    private ByteBuffer pointer;


    private DiscoveredPrint() {
    }


    @Override
    protected void clearResources() {
        nativeClose();
        pointer.clear();
        pointer = null;
    }


    /**
     * Called by method "clearResources()".
     * 
     */
    private native void nativeClose();

    private native int fp_getDriverId();
    private native long fp_getDevtype();
    private native int fp_getFinger();
    private native int fp_delete();


    /**
     * Gets the driver ID for a discovered print.
     *
     * @return
     */
    public int getDriverId() {
        check();
        return fp_getDriverId();
    }


    //Gets the devtype for a discovered print.
    public long getDevtype() {
        check();
        return fp_getDevtype();
    }


    //Gets the finger code for a discovered print.
    public int getFinger() {
        check();
        return getFinger();
    }


    //Removes a discovered print from disk.
    public int delete() {
        check();
        return delete();
    }
}
