package jfprint;

import jfprint.base.NativeResource;
import java.nio.ByteBuffer;
import jfprint.util.Wrapper;

/**
 *
 * @author thiago
 */
public class Device extends NativeResource {

    /* Definido em "fprint.h" */
    public static final int FP_ENROLL_COMPLETE = 1;
    public static final int FP_ENROLL_FAIL = 2;
    public static final int FP_ENROLL_PASS = 3;
    public static final int FP_ENROLL_RETRY = 100;
    public static final int FP_ENROLL_RETRY_TOO_SHORT = 101;
    public static final int FP_ENROLL_RETRY_CENTER_FINGER = 102;
    public static final int FP_ENROLL_RETRY_REMOVE_FINGER = 103;


    /* Definido em "fprint.h" */
    public static final int FP_VERIFY_NO_MATCH = 0;
    public static final int FP_VERIFY_MATCH = 1;
    public static final int FP_VERIFY_RETRY = FP_ENROLL_RETRY;
    public static final int FP_VERIFY_RETRY_TOO_SHORT = FP_ENROLL_RETRY_TOO_SHORT;
    public static final int FP_VERIFY_RETRY_CENTER_FINGER = FP_ENROLL_RETRY_CENTER_FINGER;
    public static final int FP_VERIFY_RETRY_REMOVE_FINGER = FP_ENROLL_RETRY_REMOVE_FINGER;


    private ByteBuffer pointer;

    private Device() {}


    @Override
    public void clearResources() {
        nativeClose();
        pointer.clear();
        pointer = null;
    }


    /**
     * Close a device.
     *
     * Called by superclass's method "close()".
     */
    private native void nativeClose();


    /**
     * Get the driver for a fingerprint device.
     *
     * @return    the driver controlling the device.
     */
    public native Driver getDriver();


    /**
     * Gets the number of enroll stages required to enroll a fingerprint with the device.
     *
     * @return    the number of enroll stages.
     */
    public native int getNumEnrollStages();


    /**
     * Gets the devtype for a device.
     *
     * @return    the devtype.
     */
    public native long getDevType();


    /**
     * Determines if a stored print is compatible with a certain device.
     *
     * @param
     * @return    {@code true} if the print is compatible with the device, {@code false} if not
     */
    public native boolean supportsPrintData(PrintData printData);


    /**
     * Determines if a discovered print appears to be compatible with a certain device.
     *
     * @param
     * @return    {@code true} if the print is compatible with the device, {@code false} if not
     */
    public native boolean supportsDiscoveredPrint(DiscoveredPrint discoveredPrint);


    /**
     * Determines if a device has imaging capabilities.
     *
     * @return    {@code true} if the device is an imaging device,
     *            {@code false} if the device does not provide images
     *            to the host computer.
     */
    public native boolean supportsImaging();


    /**
     * Determines if a device is capable of identification through fp_identify_finger() and similar.
     *
     * @return    {@code true} if the device is capable of identification, {@code false} otherwise.
     */
    public native boolean supportsIdentification();


    /**
     * Captures an image from a device.
     *
     * @param
     * @return    {@code 0} on success, non-zero on error. {@code ENOTSUP} indicates
     *            that either the unconditional flag was set but the device does not
     *            support this, or that the device does not support imaging.
     */
    public native Img imgCapture(boolean unconditional);


    /**
     * Gets the expected width of images that will be captured from the device.
     *
     * @return    the expected image width, or {@code 0} for variable,
     *            or {@code -1} for non-imaging devices.
     */
    public native int getImgWidth();


    /**
     * Gets the expected height of images that will be captured from the device.
     *
     * @return    the expected image height, or {@code 0} for variable,
     *            or {@code -1} for non-imaging devices.
     */
    public native int getImgHeight();


    /**
     * Performs an enroll stage.
     *
     * @param
     * @return   negative code on error, otherwise a code of {@code FP_ENROLL_???}.
     */
    public native int enrollFingerImg(Wrapper<PrintData> printDataWrapper, Wrapper<Img> imgWrapper);


    /**
     * Performs a new scan and verify it against a previously enrolled print.
     *
     * @param
     * @return    negative code on error, otherwise a code of {@code FP_VERIFY_???}.
     */
    public native int verifyFingerImg(PrintData enrolled_print, Wrapper<Img> imgWrapper);


    /**
     * Performs a new scan and attempts to identify the scanned finger against a collection of previously enrolled fingerprints.
     *
     * @param
     * @return    negative code on error, otherwise a code of {@code FP_VERIFY_???}.
     */
    // public native int identifyFingerImg(struct fp_dev *dev, struct fp_print_data **print_gallery, size_t *match_offset, struct fp_img **img)


    /**
     * Performs an enroll stage.
     *
     * @param
     * @return    negative code on error, otherwise a code of {@code FP_ENROLL_???}.
     */
    // public native int enrollFinger(struct fp_dev *dev, struct fp_print_data **print_data)


    /**
     * Performs a new scan and verify it against a previously enrolled print.
     *
     * @param
     * @return    negative code on error, otherwise a code of {@code FP_VERIFY_???}.
     */
    // public native int verifyFinger(struct fp_dev *dev, struct fp_print_data *enrolled_print)


    /**
     * Performs a new scan and attempts to identify the scanned finger against a collection of previously enrolled fingerprints.
     *
     * @param
     * @return    negative code on error, otherwise a code of {@code FP_VERIFY_???}.
     */
    // public native int identifyFinger (struct fp_dev *dev, struct fp_print_data **print_gallery, size_t *match_offset)
}
