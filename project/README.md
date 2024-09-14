# rpsRobot
#### Video Demo:  https://youtu.be/uTbOzdD_spo
#### Description:

**Overview:**

When connected to the robot hand and flex sensor gloves that I had built in the lab and connected to an Arduino, this code can load onto the Arduino and work independently from the computer.

At the start, the Arduino will initialize all the connected electronics, via the setup() function, then it will run the loop() function, which is the equivalent of a C main function that would loop infinitely.
The loop function will then call the waitingPos() function, and wait for the player to press the play button to start.
It will then run the game() function, which itself runs other functions to determine the result, and return the winner (or if it's a tie), to the result() function which will print the winner to the terminal, if connected to a computer,
and light the appropriate LED (green for user wins, yellow for tie, and red for robot wins).

------------------------------------------------------------------------------------------------------------------------------------------

**Breakdown:**

*Libraries and globals:*

First includes the Arduino servo header library and names the different servos.
Then define the pins of the connected electronics for easy reference.
Finally defines some global variables for calculations that are needed to determine the angle from the flex sensor,
it defines the output voltage from the Arduino 5V pin, the resistance of the 47 kΩ pull-down resistor
and the resistance of the flex sensor when straight and bent.
Since the program is being demoed in an online simulator, all values are ideal,
however, when connected to the actual robot hand, all these values need to be calibrated to the measured values
of components to ensure correct functionality.

*setup():*

This function runs once on Arduino start-up and sets up all the electronics.
It first starts the serial monitor, which is basically Arduino equivalent to setting up to print to the terminal.
It then tells the Arduino to use the play buttons and the flex sensors as inputs.
And then tells it to use the servo motors and LEDs as outputs.

*waiting():*

This is the first function that does something visible and is fairly basic.
It sets the hand to the waiting position, pointing it straight up as a fist, and turns all LEDs off.
This function runs at the start before the user presses the play button.

*buttonPressed():*

Gets the current state of the button and returns a bool, true if pressed and false if not pressed.
Fairly simple, and mostly used for abstraction.

*angle():*

Takes a flex sensor as input (which from what I understood is an int to refer to its pin on the Arduino),
and returns the calculated angle as a float.
The angle is calculated by running the Arduino analogRead() function on the given senor, doing some math on that value
and mapping it.
If interested you can learn more about this function works here: https://lastminuteengineers.com/flex-sensor-arduino-tutorial/#google_vignette

*userInput():*

The user input function runs the angle() function 3 times passing in a different flex sensor as input and returning it to a float variable each time.
It then takes the three fingers' angles and determines the user's chosen position, either rock paper scissors and returns a char, either 'r', 'p', or 's' respectively.
If the user makes an invalid choice, for instance by sticking up just their index finger, the function will return 'f' for fail for handling later.

*wristMove():*

Shakes the wrist three times as in the rock paper scissor pre-play motion
and prints "Hand up" and "Hand down" to the serial monitor as it is doing the respective motion.

*robotInput():*

The robot input function generates a random number between 0 (inclusive) and 3 (exclusive),
It then moves the fingers to the chosen position, 0 for rock, 1 for scissors, and 2 for paper,
and returns the chosen value as a char, either 'r', 's' or, 'p' respectively.
In case of an error, the switch statement will default to return 'f' for fail, although in practice,
I don't expect and haven't ever seen 'f' return from this function, but just as defensive measures I left it in.

*game():*

This function runs the wristMove() function, then runs the userInput() and robotInput() function,
checks if any of them returned 'f' and if so returns 'f' itself. If not, then everything worked as expected,
so it proceeds and prints the user and robot choice to the serial monitor. It then determines the winner a la the rock paper scissors game logic that we know and returns the winner as a char, either 'u' for user, 'r' for robot, or 't' for tie.

*result():*

Takes the return value from game() as a parameter and prints the winner and lights the appropriate LED.
If the user wins it turns on the green LED, if the robot wins it turns on the red LED, and if it was a tie it turns on the yellow LED.
If 'f' is passed to it it prints that there was an unexpected value and flashes all LEDs three times to indicate that an error has occurred.

*loop():*

This function can be thought of as the master function that either directly or indirectly calls all the other function (apart from setup()).
It first runs the waiting() function.
Then waits until buttonPressed() returns true to continue,
and then it passes the game() function as a parameter to the result() function to run the whole game and display the winner.
Finally, it waits one second before starting the loop() function again.

------------------------------------------------------------------------------------------------------------------------------------------

**Demo:**

Link for interactive Tinkercad demo: https://www.tinkercad.com/things/0RWr0JmEtjK?sharecode=n_j-Boapor4LKM4ImKIqxd4gGfwazXAQdru56Ed5xDk

Demoes the rock paper scissors robot's play button, flex sensors, and LED functionality.
Note: This demo does not test servo motors functionality, as it would be challenging to test and demonstrate the
correct functionality of the robot's servos without connecting them to any fingers or joints.

------------------------------------------------------------------------------------------------------------------------------------------

**Background:**

When I was in the eleventh grade, I took a computer technology/engineering course and as the cumulative project, I built a robotic hand that plays rock paper scissors with you.
However, due to the limited time in the course, it only covered the hardware side of things (which by the end mostly focused on the Arduino microcontroller board) and barely coved programming,
mostly only the lines of code needed to run the connected components.
Since the Arduino programing language is based on C++, as someone with then, limited knowledge of programming,
I was happy to have it functioning, all be it not very well as most of the time the robot hand would move unexpectedly, and I had no clue as to why that could be.

Now after I have completed this course I thought it would be a fun and interesting final project to look back at my code, and now that I finally understand what's happening under the hood,
to analyze it from the top down, and rebuild the program and logic from the bottom up, and I finally got it to work as expected!

------------------------------------------------------------------------------------------------------------------------------------------

**References:**

Arduino LED - Complete Tutorial. (n.d.). The Robotics Back-End. Retrieved August 18, 2023, from https://roboticsbackend.com/arduino-led-complete-tutorial/

Arduino Push Button - Complete Tutorial. (n.d.). The Robotics Back-End. Retrieved August 18, 2023, from https://roboticsbackend.com/arduino-push-button-tutorial/

bool. (2019, July 18). Arduino. Retrieved August 18, 2023, from https://www.arduino.cc/reference/en/language/variables/data-types/bool/

Button. (2018, February 5). Arduino. Retrieved August 18, 2023, from https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button

C - Operators. (n.d.). Tutorialspoint. Retrieved August 18, 2023, from https://www.tutorialspoint.com/cprogramming/c_operators.htm

C Switch. (n.d.). W3Schools. Retrieved August 18, 2023, from https://www.w3schools.com/c/c_switch.php

How to share a public link with Tinkercad – Moon Camp Challenge. (n.d.). Moon Camp Challenge. Retrieved August 18, 2023, from https://mooncampchallenge.org/how-to-share-a-public-link-with-tinkercad/

If Statement (Conditional Statement). (2015, July 29). Arduino Documentation. Retrieved August 18, 2023, from https://docs.arduino.cc/built-in-examples/control-structures/ifStatementConditional

In-Depth: Interfacing Flex Sensor with Arduino. (n.d.). Last Minute Engineers -. Retrieved August 18, 2023, from https://lastminuteengineers.com/flex-sensor-arduino-tutorial/#google_vignette

Learn to Use the Arduino's Analog I/O. (n.d.). DigiKey. Retrieved August 18, 2023, from https://www.digikey.com/en/maker/projects/learn-to-use-the-arduinos-analog-io/d3215f289c714847a6576a73717cd161

random(). (2019, February 21). Arduino. Retrieved August 18, 2023, from https://www.arduino.cc/reference/en/language/functions/random-numbers/random/

Sam98, & aarg. (2017, August 1). lvalue required as left operand of assignment - Programming Questions. Arduino Forum. Retrieved August 18, 2023, from https://forum.arduino.cc/t/lvalue-required-as-left-operand-of-assignment/473216

Shahid, A., & haxor789. (n.d.). Do we need to use break; after return in a switch statement? Codecademy. Retrieved August 18, 2023, from https://www.codecademy.com/forum_questions/533415567c82ca30fd002201

Shinde, S. (2023, January 25). Why do We Use the Arduino Programming Language? How is it Helpful? Emeritus. Retrieved August 19, 2023, from https://emeritus.org/blog/coding-arduino-programming-language/