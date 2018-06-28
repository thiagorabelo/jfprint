package sample;

import jfprint.Core;
import jfprint.DiscoveredDeviceList;
import static java.lang.String.format;
import jfprint.Device;
import jfprint.DiscoveredDevice;
import jfprint.Driver;
import jfprint.Img;
import jfprint.PrintData;
import jfprint.util.Wrapper;

/**
 *
 * @author thiago
 */
public class RunTests {

    private static Device getDevice() {
        try (DiscoveredDeviceList list = DiscoveredDeviceList.dicoverDevices()) {
            System.out.println(format("Found %d devices.", list.size()));

            if (list.size() == 0) {
                return null;
            }

            try (DiscoveredDevice ddev = list.get(0)) {
                Device dev = ddev.open();
                if (dev == null) {
                    return null;
                }

                Driver dri = dev.getDriver();

                System.out.println(format("The driver is: '%s' and needs %d enroll stages", dri.getFullName(), dev.getNumEnrollStages()));
                System.out.println(format("The image resolution is %dx%d", dev.getImgWidth(), dev.getImgHeight()));

                return dev;
            }
        }
    }

    public static void main(String[] args) throws Exception {

        System.out.println(System.getProperty("java.library.path") + "\n");

        System.out.println("Initializing the lib.");
        Core.init();

        Wrapper<PrintData> pdata = new Wrapper<>();

        try (Device dev = getDevice()) {
            if (dev != null) {
                int ret;
                Wrapper<Img> img = new Wrapper<>();

                do {
                    ret = dev.enrollFingerImg(pdata, img);

                    switch (ret) {
                        case Device.FP_ENROLL_COMPLETE:
                            System.out.println("FP_ENROLL_COMPLETE");
                            String imgPath = "/tmp/enrolled.pgm";
                            img.ifPresent(i -> {
                                i.saveToFile(imgPath);
                                System.out.println(format("Image enrolled saved at: %s", imgPath));
                            }).closeIfPresent();
                            break;
                        case Device.FP_ENROLL_FAIL:
                            System.out.println("FP_ENROLL_FAIL");
                            return;
                        case Device.FP_ENROLL_PASS:
                            System.out.println("FP_ENROLL_PASS");
                            return;
                        case Device.FP_ENROLL_RETRY:
                            System.out.println("FP_ENROLL_RETRY");
                            break;
                        case Device.FP_ENROLL_RETRY_TOO_SHORT:
                            System.out.println("FP_ENROLL_RETRY_TOO_SHORT");
                            break;
                        case Device.FP_ENROLL_RETRY_CENTER_FINGER:
                            System.out.println("FP_ENROLL_RETRY_CENTER_FINGER");
                            break;
                        case Device.FP_ENROLL_RETRY_REMOVE_FINGER:
                            System.out.println("FP_ENROLL_RETRY_REMOVE_FINGER");
                            break;
                        default:
                            System.out.println(format("EROLL ERROR: %d", ret));
                    }
                } while (ret != Device.FP_ENROLL_COMPLETE);

                pdata.ifPresent(data -> {
                    System.out.println("Lets' verify:");

                    Wrapper<Img> vimg = new Wrapper<>();

                    int vret = dev.verifyFingerImg(data, vimg);

                    System.out.println(format("Verifi status code: %d", vret));

                    switch (vret) {
                        case Device.FP_VERIFY_NO_MATCH:
                            System.out.println("NO MATCH!");
                            break;
                        case Device.FP_VERIFY_MATCH:
                            System.out.println("MATCH!");
                            String imgPath = "/tmp/virified.pgm";
                            vimg.ifPresent(i -> {
                                i.saveToFile(imgPath);
                                System.out.println(format("Image verified saved at: %s", imgPath));
                            }).closeIfPresent();
                            break;
                        case Device.FP_VERIFY_RETRY:
                            System.out.println("Scan didn't quite work. Please try again.");
                            break;
                        case Device.FP_VERIFY_RETRY_TOO_SHORT:
                            System.out.println("Swipe was too short, please try again.");
                            break;
                        case Device.FP_VERIFY_RETRY_CENTER_FINGER:
                            System.out.println("Please center your finger on the sensor and try again.");
                            break;
                        case Device.FP_VERIFY_RETRY_REMOVE_FINGER:
                            System.out.println("Please remove finger from the sensor and try again.");
                            break;
                    }
                });
            }
        } finally {
            pdata.closeIfPresent();
        }

        System.gc();
        Thread.sleep(1000);

        Core.exit();
        System.out.println("Turn off lib.");
    }
}
