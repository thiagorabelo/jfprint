package examples;

import jfprint.FpContext;
import jfprint.FpDevice;


/**
 *
 * @author thiago
 */
public class RunTests {

    public static void main(String[] args) throws Exception {
        System.out.println("Iniciando...");
        try (FpContext ctx = FpContext.contextNew()) {
            System.out.printf("Foram encontrados %d dispositivos\n", ctx.numDevices());
            try (FpDevice dev = ctx.getDevice(0)) {
                System.out.printf("Device Driver: %s\n", dev.getDriver());
                System.out.printf("Device ID: %s\n", dev.getDeviceId());
                System.out.printf("Device Name: %s\n", dev.getName());
            }
        }
    }
}
