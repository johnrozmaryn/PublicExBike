# ExBike
 ESP32 web based control over exercise bike resistance

 This is totally ugly, but it works. If you're logged in to my home network, you go to the website at http://exbike.local and click on the resistance number you want.

The resistance motor has a variable resistor that we read like an analog input, going from around 50ish to around 400something over the range of motion that's probably acceptable.

The DC Motor that drives the magnetic resistance plate has two input wires. Powering one wire moves the motor one direction, powering the other wire rotates the motor in the other direction.

I initially just tried to directly power the motor using the outputs on the ESP32, but it appears that those only can push up to 40mA, and I need more current than that for motion. I ended up using a L9100S motor controller, with the extra input voltage coming directly from the VIN pin of the ESP32.
