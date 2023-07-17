-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find the crime scene report on July 28, 2021 on Humphrey Street.
SELECT description FROM crime_scene_reports
WHERE
	year = 2021 AND
    month = 7 AND
    day = 28 AND;

-- Findings:
-- Time: 10:15am
-- Location: Humphrey Street bakery
-- Notes: 3 witnesses. All mentioned the bakery
-- Three other crims that might be connected:
--     Vandalism: 12:04 on Axmark Road
-- 	   Money laundering: 12:30 on Widenius Street
--	   Shoplifting: 03:01 on Boyce Avenue


-- Next: Find the bakery security logs on that day
SELECT * FROM bakery_security_logs
WHERE
	year = 2021 AND
    month = 7 AND
    day = 28 AND
    hour > 8 AND
    hour < 11;

-- Results
/*
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 254 | 2021 | 7     | 28  | 9    | 14     | entrance | 4328GD8       |
| 255 | 2021 | 7     | 28  | 9    | 15     | entrance | 5P2BI95       |
| 256 | 2021 | 7     | 28  | 9    | 20     | entrance | 6P58WS2       |
| 257 | 2021 | 7     | 28  | 9    | 28     | entrance | G412CB7       |
| 258 | 2021 | 7     | 28  | 10   | 8      | entrance | R3G7486       |
| 259 | 2021 | 7     | 28  | 10   | 14     | entrance | 13FNH73       |
| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
| 268 | 2021 | 7     | 28  | 10   | 35     | exit     | 1106N58       |
| 269 | 2021 | 7     | 28  | 10   | 42     | entrance | NRYN856       |
| 270 | 2021 | 7     | 28  | 10   | 44     | entrance | WD5M8I6       |
| 271 | 2021 | 7     | 28  | 10   | 55     | entrance | V47T75I       |
+-----+------+-------+-----+------+--------+----------+---------------+
*/

-- Next: Find the interview reports
SELECT * FROM interviews
WHERE
	year = 2021 AND
    month = 7
    AND day = 28;

/*
Ruth: Thief exited withing 10 minutes
Eugene: Earlier that morning, thief withdrew money from ATM on Leggett Street
Raymond: Phone call (less than a min)at exit, asked for earliest flight out of Fiftyville tomorrow
*/

-- Next: Investigate license places of cars that exited after the time of theft
SELECT * FROM people
WHERE license_plate IN
	('5P2BI95','94KL13X','6P58WS2','4328GD8','G412CB7','L93JTIZ','322W7JE');

/*
+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
| 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+---------+----------------+-----------------+---------------+
*/

-- Next: Investigate ATM on Leggett Street
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street';

/*
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 275 | 86363979       | 2021 | 7     | 28  | Leggett Street | deposit          | 10     |
| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
*/

-- Next: Investigate phone calls
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 61;

/*
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
| 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
| 234 | (609) 555-5876 | (389) 555-5198 | 2021 | 7     | 28  | 60       |
| 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
| 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
| 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
| 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
+-----+----------------+----------------+------+-------+-----+----------+
*/

-- Join the people and phone calls and filter on the time, duration and license plate
SELECT * FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 61 AND license_plate IN ('5P2BI95','94KL13X','6P58WS2','4328GD8','G412CB7','L93JTIZ','322W7JE');

/*
+--------+-------+----------------+-----------------+---------------+-----+----------------+----------------+------+-------+-----+----------+
|   id   | name  |  phone_number  | passport_number | license_plate | id  |     caller     |    receiver    | year | month | day | duration |
+--------+-------+----------------+-----------------+---------------+-----+----------------+----------------+------+-------+-----+----------+
| 398010 | Sofia | (130) 555-0289 | 1695452385      | G412CB7       | 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       | 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
+--------+-------+----------------+-----------------+---------------+-----+----------------+----------------+------+-------+-----+----------+
*/

-- Find the names of those who withdrew money
/*
+----------------+-----------+---------------+--------+---------+----------------+-----------------+---------------+
| account_number | person_id | creation_year |   id   |  name   |  phone_number  | passport_number | license_plate |
+----------------+-----------+---------------+--------+---------+----------------+-----------------+---------------+
| 49610011       | 686048    | 2010          | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
| 86363979       | 948985    | 2010          | 948985 | Kaelyn  | (098) 555-1164 | 8304650265      | I449449       |
| 26013199       | 514354    | 2012          | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 16153065       | 458378    | 2012          | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
| 28296815       | 395717    | 2014          | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| 25506511       | 396669    | 2014          | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 28500762       | 467400    | 2014          | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| 76054385       | 449774    | 2015          | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
| 81061156       | 438727    | 2018          | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
+----------------+-----------+---------------+--------+---------+----------------+-----------------+---------------+
*/

-- From the last two queries, possible suspect are: Bruice and Diana (passports: 5773159633 and 3592750733)

-- Next: Investigate flights on July 29
SELECT * FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville');

/*
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |
| 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     |
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
| 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
| 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+
*/

-- Next: Find if suspects are on flight 36 or 43 from the previous query
SELECT * FROM passengers WHERE flight_id IN (36, 43) AND passport_number IN (5773159633, 3592750733);

/*
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 36        | 5773159633      | 4A   |
+-----------+-----------------+------+
*/
-- Bamm! Bruice, passport number 5773159633 was on flight 36 bound for a destination with destination_airport_id of 4

SELECT city FROM airports WHERE id = 4;

/*
+---------------+
|     city      |
+---------------+
| New York City |
+---------------+

*/

-- Bruce is in NY now
-- From the phone_calls records, we know the reciever of the call was (375) 555-8161

SELECT name FROM people WHERE phone_number = '(375) 555-8161';

-- And so the accomplice is Robin