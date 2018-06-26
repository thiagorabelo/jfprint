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
     * Called by superclass's method "close()".
     */
    private native void nativeClose();


 	//Gets the pixel height of an image.
    public native int getHeight();


    //Gets the pixel width of an image.
    public native int getWidth();


    //Gets the greyscale data for an image.
    public native byte[] getData();


    //A quick convenience function to save an image to a file in PGM format.
    public native int saveToFile(String path);


    //Standardizes an image by normalizing its orientation, colors, etc.
    public native void standardize();


    //Get a binarized form of a standardized scanned image.
    public native Img binarize();


    //Get a list of minutiae detected in an image.
    // struct fp_minutia** fp_img_get_minutiae(struct fp_img *img, int *nr_minutiae);
}
