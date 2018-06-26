package sample;

import jfprint.Core;
import jfprint.DiscoveredDeviceList;
import static java.lang.String.format;
import jfprint.Device;
import jfprint.DiscoveredDevice;
import jfprint.Driver;
import jfprint.Img;
import jfprint.PrintData;
import jfprint.util.Consumer;
import jfprint.util.Wrapper;

/**
 *
 * @author thiago
 */
public class RunTests {

    public RunTests() {}

    public static void main(String[] args) throws Exception {

        System.out.println(System.getProperty("java.library.path") + "\n");

        System.out.println("Iniciando a lib.");
        Core.init();

        DiscoveredDeviceList list = DiscoveredDeviceList.dicoverDevices();

        System.out.println(format("Foram encontrados %d dispositivos.", list.size()));

        DiscoveredDevice ddev = list.get(0);
        Device dev = ddev.open();
        Driver dri = dev.getDriver();

        System.out.println(format("The driver is: %s and needs %d enroll stages", dri.getFullName(), dev.getNumEnrollStages()));
        System.out.println(format("The image resolution is %dx%d", dev.getImgWidth(), dev.getImgHeight()));

        Wrapper<PrintData> pdata = new Wrapper<>();
        Wrapper<Img> img = new Wrapper<>();

        int ret;
        do {
            ret = dev.enrollFingerImg(pdata, img);

            switch (ret) {
                case Device.FP_ENROLL_COMPLETE:
                    System.out.println("FP_ENROLL_COMPLETE");
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

            switch (vret) {
                case Device.FP_VERIFY_NO_MATCH:
                    System.out.println("NO MATCH!");
                    break;
                case Device.FP_VERIFY_MATCH:
                    System.out.println("MATCH!");
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

        Thread.sleep(1000);
        dri.close();
        dev.close();
        ddev.close();
        System.gc();
        Thread.sleep(2000);

        Core.exit();
        System.out.println("Lib desligada.");
    }
}
