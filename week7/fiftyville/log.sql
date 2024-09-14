-- Keep a log of any SQL queries you execute as you solve the mystery.

-- lists contents of db
.tables
/*
airports              crime_scene_reports   people
atm_transactions      flights               phone_calls
bakery_security_logs  interviews
bank_accounts         passengers
*/

-- display schema for crime_scene_reports -> Learn format of table for queries
.schema crime_scene_reports

-- all data from crime_scene_reports
SELECT * FROM crime_scene_reports

-- description from crime_scene_reports on July 28, 2021 on Humphrey Street
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

-- theft took place at 10:15 am at Humphrey Street Bakery. Interviews were conducted with three witnesses who were present at the time. --

-- Reviewing interviews transcript for more details
SELECT name, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;

-- Useful Interviews
/*
Ruth: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot AND drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame. -> 1
Eugene: I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street AND saw the thief there withdrawing some money. -> 2
Raymond: As the thief was leaving the bakery, they called someone who talked to them for less than a minute. -> 3 In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. -> 4
*/

-- display schema for bakery_security_logs -> Checking for useful data
.schema bakery_security_logs

-- looking at license_plate from people who exited the bakery within ten minute of the time of the theft
SELECT license_plate, minute FROM bakery_security_logs WHERE activity = "exit" AND year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute < 25;
/* 1*
+---------------+--------+
| license_plate | minute |
+---------------+--------+
| 5P2BI95       | 16     |
| 94KL13X       | 18     |
| 6P58WS2       | 18     |
| 4328GD8       | 19     |
| G412CB7       | 20     |
| L93JTIZ       | 21     |
| 322W7JE       | 23     |
| 0NTHK55       | 23     |
+---------------+--------+
*/

-- display schema for atm_transactions -> Checking for useful data
.schema atm_transactions

-- account number and amount for atm widthdraw transaction on day of theft
SELECT account_number, amount FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
/* 2*
+----------------+--------+
| account_number | amount |
+----------------+--------+
| 28500762       | 48     |
| 28296815       | 20     |
| 76054385       | 60     |
| 49610011       | 50     |
| 16153065       | 80     |
| 25506511       | 20     |
| 81061156       | 30     |
| 26013199       | 35     |
+----------------+--------+
*/

-- display schema for bank_accounts -> Checking for useful data
.schema bank_accounts

-- get person id of everyone with an account_number from table 2*
SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw");
/* 3*
+-----------+
| person_id |
+-----------+
| 686048    |
| 514354    |
| 458378    |
| 395717    |
| 396669    |
| 467400    |
| 449774    |
| 438727    |
+-----------+
*/

-- display schema for phone_calls -> Checking for useful data
.schema phone_calls

-- Looking for Caller and Reciver of calls less than 1 min that happens on the day of the crime *3
SELECT caller, receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 100;
/* 4*
+----------------+----------------+
|     caller     |    receiver    |
+----------------+----------------+
| (130) 555-0289 | (996) 555-8899 |
| (499) 555-9472 | (892) 555-8872 |
| (367) 555-5533 | (375) 555-8161 |
| (609) 555-5876 | (389) 555-5198 |
| (636) 555-4198 | (670) 555-8598 |
| (499) 555-9472 | (717) 555-1342 |
| (286) 555-6063 | (676) 555-6554 |
| (770) 555-1861 | (725) 555-3243 |
| (669) 555-6918 | (971) 555-6468 |
| (031) 555-6622 | (910) 555-3251 |
| (016) 555-9166 | (336) 555-0077 |
| (751) 555-6567 | (594) 555-6254 |
| (826) 555-1652 | (066) 555-9701 |
| (338) 555-6650 | (704) 555-2131 |
| (367) 555-5533 | (704) 555-5790 |
+----------------+----------------+
*/

-- display schema for flights -> Checking for useful data
.schema flights

-- display schema for airports -> Checking for useful data
.schema airports

-- Looking for fiftyville airport
SELECT id FROM airports WHERE city = "Fiftyville";

-- Looking for flight id and destination of earliest flight on 29/07/2021 (day after theft), leaving from fiftyville airport
SELECT id, destination_airport_id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour, minute LIMIT 1;

/* 5*
+----+------------------------+
| id | destination_airport_id |
+----+------------------------+
| 36 | 4                      |
+----+------------------------+
*/

-- Looking for city theif escaped to
SELECT city FROM airports WHERE id = 4;

-- The city the thief ESCAPED TO: New York City
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- display schema for passengers -> Checking for useful data
.schema passengers

-- get passport_number of evryone on fligt id 36 (earliest flight from fiftyville on the 29th)
SELECT passport_number FROM passengers WHERE flight_id = 36;

/* 6*
+-----------------+
| passport_number |
+-----------------+
| 7214083635      |
| 1695452385      |
| 5773159633      |
| 1540955065      |
| 8294398571      |
| 1988161715      |
| 9878712108      |
| 8496433585      |
+-----------------+
*/

-- display schema for people -> Checking for useful data
.schema people

-- retrive name of everyone with a licence plate from table 1*, an id from table 2*, is a caller from table 4* and has a pasport from table 5*
SELECT name FROM people WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs WHERE activity = "exit" AND year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute < 25)
        AND id in (SELECT person_id FROM bank_accounts WHERE account_number in (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"))
            AND phone_number in (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 100)
                AND passport_number in (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- The THIEF is: Bruce
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Get the name of who bruce called from the crime scene and the bank account used to purchase the plane ticket to find his accomplice

SELECT name FROM people WHERE id in (Select person_id FROM bank_accounts WHERE person_id in (SELECT id FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 100 AND caller = (SELECT phone_number FROM people WHERE name = "Bruce"))));

-- The ACCOMPLICE is: Robin
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

