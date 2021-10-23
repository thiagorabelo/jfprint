package jfprint;

import java.util.Arrays;

public enum FpFinger {
    FP_FINGER_UNKNOWN(0),
    FP_FINGER_LEFT_THUMB(1),
    FP_FINGER_LEFT_INDEX(2),
    FP_FINGER_LEFT_MIDDLE(3),
    FP_FINGER_LEFT_RING(4),
    FP_FINGER_LEFT_LITTLE(5),
    FP_FINGER_RIGHT_THUMB(6),
    FP_FINGER_RIGHT_INDEX(7),
    FP_FINGER_RIGHT_MIDDLE(8),
    FP_FINGER_RIGHT_RING(9),
    FP_FINGER_RIGHT_LITTLE(10);

    public static FpFinger FP_FINGER_FIRST = FP_FINGER_LEFT_THUMB;
    public static FpFinger FP_FINGER_LAST = FP_FINGER_RIGHT_LITTLE;


    public static FpFinger getByValue(int finger) {
        return Arrays.asList(FpFinger.values())
                .stream()
                .filter(f -> f.value == finger)
                .findFirst()
                .orElse(FP_FINGER_UNKNOWN);
    }

    public final int value;

    private FpFinger(int value) {
        this.value = value;
    }
}
