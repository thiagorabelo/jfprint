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
    }


    private native void nativeClose();


    /**
     * Gets the driver ID for a discovered print.
     *
     * @return
     */
    public native int getDriverId();


    //Gets the devtype for a discovered print.
    public native long getDevtype();


    //Gets the finger code for a discovered print.
    public native int getFinger();


    //Removes a discovered print from disk.
    public native int delete();
}
