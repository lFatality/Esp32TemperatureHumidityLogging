#pragma once

#define SECONDS_TO_MS 1000

namespace parameters {

    /**
     * Sampling period
     * 
     * Defines how often the sensors will be read.
     * Dont set the value to low, reading the sensor and sending to the spreadsheet takes some time.
     * A value >= 5 seconds should be ok.
     */
    const int samplingPeriodInSeconds = 5;

    /**
     * Up time
     * 
     * How long the device should be awake before going to sleep to save power.
     * Set to 0 if you want to disable sleeping (setting the sleepTime to 0 has the same effect).
     */
    const int desiredUpTimeInSeconds = 30;

    /**
     * Sleep time
     * 
     * For how much time the device should stay asleep if deep sleep is active.
     * This can be useful for power saving.
     * Set to 0 if you dont want to go to sleep (setting the upTime to 0 has the same effect).
     */
    const int sleepTimeInSeconds = 60;
}
