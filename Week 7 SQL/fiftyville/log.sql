-- Keep a log of any SQL queries you execute as you solve the mystery.

-- We know that the theft took place on July 28, 2021 and that it took place on Humphrey Street.

SELECT * FROM crime_scene_reports
WHERE street = "Humphrey Street" AND year = 2021 AND month = 7 AND day = 28;

-- The crime scene reports we found out, took place at 10:15 AM at the bakery.
-- Three witnesses were present and mentioned the bakery.

SELECT * FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28;

-- Ruth said the thief got into a car in the bakery parking lot and drove away and security footage from the bakery parking lot.
-- Also someone mentioned that he recognized the thief because earlier that morning he saw the thief withdrawing some money on Leggett Street.
-- Raymond mentioned the thief called someone after leaving the bakery and talked to them for less than a minute.
-- The thief said on the phone that they were planning to take the earliest flight out of Fiftyville tomorrow and asked the person he was talking to to buy the tickets.

SELECT * FROM people
WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE activity = "exit" AND year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 40
)
AND phone_number IN (
    SELECT caller FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
)
AND people.id IN (
    SELECT person_id FROM bank_accounts
    WHERE bank_accounts.account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"
    )
);

-- From the leads about the bakery parking and the ATM withdrawal and the call, we get back 3 suspects.
-- Taylor, Diana and Bruce.

SELECT * FROM people
WHERE phone_number IN (
    SELECT receiver FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller IN ("(286) 555-6063", "(770) 555-1861", "(367) 555-5533")
);

-- From checking the receivers of those phone calls, we get the 3 suspects phone numbers that might be the accomplices.
-- James, Philip and Robin.

SELECT * FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
AND caller IN ("(286) 555-6063", "(770) 555-1861", "(367) 555-5533")
AND receiver IN ("(676) 555-6554", "(725) 555-3243", "(375) 555-8161");

-- From the names and the number of the possible suspects and accomplices we can check who called who.
-- Taylor called James, Diana called Philip and Bruce called Robin.

SELECT * FROM flights
JOIN airports ON airports.id = flights.origin_airport_id
WHERE flights.year = 2021 AND flights.month = 7 AND flights.day = 29 AND flights.hour BETWEEN 00 AND 12 AND airports.city = "Fiftyville"
ORDER BY flights.hour, flights.minute;

SELECT full_name, city FROM airports
WHERE id IN (1, 4, 11);

-- The thief said he wants to leave as early as possible tomorrow.
-- Checking the earliest flights we get back 3 flights: to New York at 8:20 AM, to Chicago at 9:30 AM and to San Francisco at 12:15 PM.

SELECT name, passport_number FROM people
WHERE people.name IN ("Bruce", "Taylor", "Diana", "James", "Philip", "Robin")
AND passport_number IN (
    SELECT passport_number FROM passengers
    JOIN flights ON flights.id = passengers.flight_id
    JOIN airports ON airports.id = flights.origin_airport_id
    WHERE flights.year = 2021 AND flights.month = 7 AND flights.day = 29 AND flights.hour BETWEEN 00 AND 12
    AND flights.origin_airport_id IN (
        SELECT airports.id FROM airports
        WHERE airports.city = "Fiftyville"
    )
    AND flights.destination_airport_id IN (
        SELECT airports.id FROM airports
        WHERE airports.city IN ("New York City", "Chicago", "San Francisco")
    )
);

-- From the three suspects, Bruce and Taylor flew on the 29th on one of the three aforementioned flights.

SELECT f.*, origin.full_name AS origin_airport, destination.full_name AS destination_airport
FROM flights f
JOIN airports origin ON f.origin_airport_id = origin.id
JOIN airports destination ON f.destination_airport_id = destination.id
WHERE origin.id = 8 AND f.year = 2021 AND f.month = 7 AND f.day = 29
ORDER BY f.hour, f.minute;

-- Now we know both of them flew to LaGuardia (New York).
-- Combine info from all testimonies:

SELECT p.name
FROM bakery_security_logs bsl
JOIN people p ON p.license_plate = bsl.license_plate
JOIN bank_accounts ba ON ba.person_id = p.id
JOIN atm_transactions at ON at.account_number = ba.account_number
JOIN phone_calls pc ON pc.caller = p.phone_number
WHERE bsl.year = 2021 AND bsl.month = 7 AND bsl.day = 28 AND bsl.hour = 10 AND bsl.minute BETWEEN 15 AND 25
AND at.atm_location = 'Leggett Street' AND at.year = 2021 AND at.month = 7 AND at.day = 28
AND pc.year = 2021 AND pc.month = 7 AND pc.day = 28 AND pc.duration < 60;

--We narrow down to Bruce and Diana
--And we know that Bruce and Taylor flew on the 29th
--So the thief is Bruce and we know that Bruce called Robin on phone, which make him his accomplice.

