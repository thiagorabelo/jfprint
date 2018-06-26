package jfprint;

/**
 *
 * @author thiago
 */
public class Core {

    static {
        System.loadLibrary("fprint");
        System.loadLibrary("jfprintjni");
    }

    private static native int fp_init();
    private static native void fp_exit();


    //private static native void setDebug(int level);


    /**
     * Initialise libfprint.
     *
     * This function must be called before you attempt to use the library in any way.
     *
     * @throws Exception On error during initialization of the libfprint.
     */
    public static void init() throws Exception {
        if (fp_init() != 0) {
            throw new Exception("Can't open initialize libfprint");
        }
    }

    /**
     * Deinitialise libfprint.
     *
     * This function should be called during your program exit sequence.
     * You must not use any libfprint functions after calling this function,
     * unless you call {@link jfprint.Core#init() init} again.
     */
    public static void exit() {
        fp_exit();
    }
}
