-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Checking the description of the crime happened at the given time and location.
SELECT description
  FROM crime_scene_reports
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND street = 'Humphrey Street';
-- Two incidents happened that day. Only one is related to theft.

-- Finding the names of the witnesses from the interviews table. Also, checking their interviews' transcripts.
SELECT name, transcript
  FROM interviews
 WHERE year = 2021
   AND month = 7
   AND day = 28;

-- Found two transcripts with the name- Eugene, checking how many Eugenes are present in the 'people' table.
SELECT name
  FROM people
 WHERE name = 'Eugene';
-- Found out that there is only one Eugene.

-- Findling the names of the 3 witnesses from the list of names of people who gave interviews on July 28, 2021.
SELECT name, transcript
  FROM interviews
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND transcript LIKE '%bakery%'
 ORDER BY name;
-- Witnesses are- Eugene, Raymond, and Ruth.

-- So, checking the account number of the person who did that transaction.
SELECT account_number, amount
  FROM atm_transactions
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND atm_location = 'Leggett Street'
   AND transaction_type = 'withdraw';
-- Finding the names associated with the corresponding account numbers. Putting these names in the 'Suspect List'
SELECT name, atm_transactions.amount
  FROM people
  JOIN bank_accounts
    ON people.id = bank_accounts.person_id
  JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
 WHERE atm_transactions.year = 2021
   AND atm_transactions.month = 7
   AND atm_transactions.day = 28
   AND atm_transactions.atm_location = 'Leggett Street'
   AND atm_transactions.transaction_type = 'withdraw';

-- First finding the information about the aiport in Fiftyville which would be the origin of the flight of the thief.
SELECT abbreviation, full_name, city
  FROM airports
 WHERE city = 'Fiftyville';
-- Finding the flights on July 29 from Fiftyville airport, and ordering them by time.
SELECT flights.id, full_name, city, flights.hour, flights.minute
  FROM airports
  JOIN flights
    ON airports.id = flights.destination_airport_id
 WHERE flights.origin_airport_id =
       (SELECT id
          FROM airports
         WHERE city = 'Fiftyville')
   AND flights.year = 2021
   AND flights.month = 7
   AND flights.day = 29
 ORDER BY flights.hour, flights.minute;

-- Checking the list of passengers in that flight. Putting them all in 'Suspect List'. Ordering the names according to their passport numbers.
SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat
  FROM people
  JOIN passengers
    ON people.passport_number = passengers.passport_number
  JOIN flights
    ON passengers.flight_id = flights.id
 WHERE flights.year = 2021
   AND flights.month = 7
   AND flights.day = 29
   AND flights.hour = 8
   AND flights.minute = 20
 ORDER BY passengers.passport_number;

-- Checking the phone call records to find the person who bought the tickets.
-- Firstly, checking the possible names of the caller, and putting these names in the 'Suspect List'.
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.caller
 WHERE phone_calls.year = 2021
   AND phone_calls.month = 7
   AND phone_calls.day = 28
   AND phone_calls.duration <= 60
 ORDER BY phone_calls.duration;
-- Secondly, checking the possible names of the call-receiver.
SELECT name, phone_calls.duration
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.receiver
 WHERE phone_calls.year = 2021
   AND phone_calls.month = 7
   AND phone_calls.day = 28
   AND phone_calls.duration <= 60
   ORDER BY phone_calls.duration;

-- SO, checking the license plates of cars within that time frame. Then, checking out the names of those cars' owners. They could be suspects.
SELECT name, bakery_security_logs.hour, bakery_security_logs.minute
  FROM people
  JOIN bakery_security_logs
    ON people.license_plate = bakery_security_logs.license_plate
 WHERE bakery_security_logs.year = 2021
   AND bakery_security_logs.month = 7
   AND bakery_security_logs.day = 28
   AND bakery_security_logs.activity = 'exit'
   AND bakery_security_logs.hour = 10
   AND bakery_security_logs.minute >= 15
   AND bakery_security_logs.minute <= 25
 ORDER BY bakery_security_logs.minute;
