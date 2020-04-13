#pragma once

/*
Simple Deep Sleep with Timer Wake Up
=====================================
ESP32 offers a deep sleep mode for effective power
saving as power is an important factor for IoT
applications. In this mode CPUs, most of the RAM,
and all the digital peripherals which are clocked
from APB_CLK are powered off. The only parts of
the chip which can still be powered on are:
RTC controller, RTC peripherals ,and RTC memories
This code displays the most basic deep sleep with
a timer to wake it up and how to store data in
RTC memory to use it over reboots
This code is under Public Domain License.
Author:
Pranav Cherukupalli <cherukupallip@gmail.com>
Fynn Boyer <fynn-boyer@web.de>
*/

#include "Arduino.h"
#include <functional>

/**
 * Class to put the board in a deep sleep to save power.
 * Can be powered up again by use of a timer for example.
 */
class SleepController {
public:
    SleepController() = default;

    /**
     * @brief Makes the chip go into a deep sleep for the specified time.
     * 
     * @param sleepTimeInSeconds How many seconds to sleep 
     */
    void sleep(int sleepTimeInSeconds);

    /**
     * @brief Prints information about the wakeup reason and keeps track of the boot timer.
     * 
     * Should be called at the start of the setup() function.
     * 
     * @warn This function uses Serial.printf() so the Serial Monitor should be initialized first.
     */
    void analyzeBoot();

    /**
     * @brief Attach a callback function that is called after wake up.
     * 
     * To pass a free-standing callback function, just pass the function name.
     * To pass class methods you can use std::bind.
     * 
     * Example syntax for std::bind:
     * 
     * MyClass::MyClass() {
     *     using namespace std::placeholders; // for `_1`
     * 
     *     SleepController.attachCallback(std::bind(&MyClass::Callback, this, _1));
     * }
     * 
     * @param callback The callback function, pass nullptr to delete
     */
    //void attachCallback(std::function<void(void*)> callback);

private:
    /**
     * @brief Method to print the reason by which ESP32 has been awaken from sleep.
     */
    void print_wakeup_reason();

    //std::function<void(void*)> callback = nullptr; ///< callback function after wake up
};
