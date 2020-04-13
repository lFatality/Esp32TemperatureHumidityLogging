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
     * Desired Up time
     * 
     * How long the device should be awake before going to sleep to save power.
     * Set to 0 if you want to sleep immediately after the first sample.
     * The order of operation is wakeup->setup->loop(sample->checkForSleep->WaitSampleTime).
     * Check for sleep compares the time since the last boot with the desired up time.
     * If we're up for the desiredUpTime, we go to sleep.
     * 
     * Example:
     * You sample every 5 seconds. You want to sample 3 times and then go to sleep.
     * Remember that you also sample at t=0. You set the desired upTime to 10 seconds.
     * You sample at t=0, t=5, and t=10 (you sample before checking for sleep), then you go to sleep.
     */
    const int desiredUpTimeInSeconds = 10;

    /**
     * Sleep time
     * 
     * For how much time the device should stay asleep if deep sleep is active.
     * This can be useful for power saving.
     * Set to 0 if you dont want to go to sleep.
     */
    const int sleepTimeInSeconds = 60;
}
