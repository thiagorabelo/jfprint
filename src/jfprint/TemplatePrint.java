package jfprint;

import java.util.Calendar;
import java.util.Date;

public class TemplatePrint {

    private int finger;
    private String username;
    private String description;
    private Date date;

    public TemplatePrint() {
        this(FpFinger.FP_FINGER_UNKNOWN);
    }

    public TemplatePrint(FpFinger finger) {
        this.finger = finger.value;
    }

    public int getFinger() {
        return finger;
    }

    public void setFinger(int finger) {
        this.finger = finger;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public Calendar getCalendar() {
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(date);
        return calendar;
    }
}
