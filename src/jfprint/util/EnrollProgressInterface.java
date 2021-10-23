package jfprint.util;

import jfprint.FpDevice;
import jfprint.FpPrint;

// javap -cp bin/ -s jfprint.util.EnrollProgressInterface
public interface EnrollProgressInterface {
    void callback(FpDevice dev, int completedStages, FpPrint print);
}
