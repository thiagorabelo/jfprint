package examples;

import jfprint.*;

import java.sql.SQLOutput;
import java.util.Calendar;
import java.util.Date;


/**
 *
 * @author thiago
 */
public class RunTests {

    private static Date getDate(int year, int month, int day) {
        Calendar calendar = Calendar.getInstance();
        calendar.set(year, month, day);
        return calendar.getTime();
    }

    public static void main(String[] args) throws Exception {
        System.out.println("Iniciando...");
        try (FpContext ctx = FpContext.contextNew()) {
            System.out.printf("Foram encontrados %d dispositivos\n", ctx.numDevices());
            try (FpDevice dev = ctx.getDevice(0)) {
                System.out.printf("Device Driver: %s\n", dev.getDriver());
                System.out.printf("Device ID: %s\n", dev.getDeviceId());
                System.out.printf("Device Name: %s\n", dev.getName());

                if (dev.openDevice()) {
                    TemplatePrint template = new TemplatePrint(FpFinger.FP_FINGER_LEFT_INDEX);
                    template.setUsername("Thiago Rabelo");
                    template.setDate(getDate(1983, Calendar.NOVEMBER, 5));

                    FpPrint print = dev.enroll((device, completedStages, intermediate_print) -> {
                        System.out.printf("Etapa: %d e Dedo: %d\n", completedStages, intermediate_print.getFinger().value);
                    }, template);

                    System.out.printf("O dedo escaneado foi: %d\n", print.getFinger().value);

                    dev.closeDevice();
                }
            }
        }
    }
}
