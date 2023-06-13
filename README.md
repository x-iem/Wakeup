#Wakeup with Arduino
The Arduino is connected to a shutter remote, so that a small impulse on
one of the pins enables the transmission of the corresponding signal.

##Functionalities
This code tries to limit the amount of time the Arduino is actively running
by shutting down some of its functionnalites. It is possible to shut the
Arduino down for a maximum of 8 consecutive seconds. Repeating the
process as long as needed preserves thus the battery capacity of the
Arduino.
The number of minutes of sun gain or loss has been imported from a
public database that concerns the region of Saint-Etienne, France.
The code sends a signal to lift up the shutter when the
sun rises (according to time), another to partially close the shutter
when it is noon, and then to fully close the shutter when the sun sets.

##How to plug it to a controler
TO BE WRITTEN

##Limitations
###Time precision
The shutting down of the main processes of the Arduino and their reactivation
spends some time that needs to be taken in consideration, as a few more
ms spent per 8 seconds could result overtime in minutes per day late.
By experimenting, I noticed around an opening 20 minutes later than
the planned one, when the Arduino should have waited 8 hours.
However due to the lack of experiments data, I have not implemented the
functionnality that would compense such lateness.

I also question myself with the real utility of storing day to day
seconds before sunrise and sunset, as the Arduino isn't that precise
overall. Maybe just a small 555 connected to the Arduino as an interrupt
could improve the waking-time precision.
###Battery preservation
Something must be wrong in the way the Arduino "sleeps", as my pocket
battery only lasted a few days. But it can also happen to be caused
by the corresponding home-made electrical circuit that was build
alongside.
