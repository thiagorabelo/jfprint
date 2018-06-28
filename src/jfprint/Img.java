package jfprint;

import jfprint.base.NativeResource;
import java.nio.ByteBuffer;

/**
 *
 * @author thiago
 */
public class Img extends NativeResource {

    private ByteBuffer pointer;


    public Img() {
    }


    @Override
    protected void clearResources() {
        nativeClose();
        pointer.clear();
        pointer = null;
    }


    /**
     * Frees an image.
     *
     * Called by method "clearResources()".
     */
    private native void nativeClose();

    private native int fp_getHeight();
    private native int fp_getWidth();
    private native byte[] fp_getData();
    private native int fp_saveToFile(String path);
    private native void fp_standardize();
    private native Img fp_binarize();


 	//Gets the pixel height of an image.
    public int getHeight() {
        check();
        return fp_getHeight();
    }


    //Gets the pixel width of an image.
    public int getWidth() {
        check();
        return fp_getWidth();
    }


    //Gets the greyscale data for an image.
    public byte[] getData() {
        check();
        return fp_getData();
    }


    //A quick convenience function to save an image to a file in PGM format.
    public int saveToFile(String path) {
        check();
        return fp_saveToFile(path);
    }


    //Standardizes an image by normalizing its orientation, colors, etc.
    public void standardize() {
        check();
        fp_standardize();
    }


    //Get a binarized form of a standardized scanned image.
    public Img binarize() {
        check();
        return fp_binarize();
    }


    //Get a list of minutiae detected in an image.
    // struct fp_minutia** fp_img_get_minutiae(struct fp_img *img, int *nr_minutiae);
}
