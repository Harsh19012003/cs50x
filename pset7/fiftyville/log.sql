-- Keep a log of any SQL queries you execute as you solve the mystery.

-- According to Ruth car license_plate_numbers
SELECT DISTINCT(name) FROM people
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
WHERE people.license_plate IN
    (SELECT courthouse_security_logs.license_plate FROM courthouse_security_logs
    WHERE hour = 10 AND minute <= 25 AND minute >= 15 AND day = 28 AND month = 7 AND year = 2020
    );
-- Names of suspect through witness 1 -
--Patrick Amber Elizabeth Roger Danielle Russell Evelyn Ernest


-- According to Eugene ATM on Fifer Street
SELECT name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number IN
    (SELECT account_number FROM atm_transactions
    WHERE day = 28 AND month = 7 AND year = 2020 AND atm_location = "Fifer Street"
    )
;
-- Names of suspect through witness 2 -
-- Ernest Robert Russell Roy Bobby Elizabeth Danielle Madison Victoria


-- According to talk on call and flight tommorow
SELECT name, destination_airport_id
FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE flights.id =
    (SELECT id
    FROM flights
    WHERE day = 29 AND month = 7 AND year = 2020 AND origin_airport_id =
        (SELECT id
        FROM airports
        WHERE city = "Fiftyville"
        )
    ORDER BY hour, minute
    LIMIT 1
    )
;
-- Names of suspect through witness 3 via flight-
-- Bobby Roger Madison Danielle Evelyn Edward Ernest Doris

SELECT name
FROM people
WHERE phone_number IN
    (SELECT receiver
    FROM phone_calls
    WHERE day = 28 AND month = 7 AND year = 2020 AND duration < 60
    )
;

-- Names of suspect through witness 3 via call-
-- Bobby Roger Victoria Madison Russell Evelyn Ernest Kimberly

-- So the final comman thief id Ernest.

SELECT *
FROM airports
WHERE id = 4;
-- He escaped to London

SELECT name
FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE day = 28 AND month = 7 AND year = 2020 AND duration < 60 AND caller =
    (SELECT phone_number
    FROM people
    WHERE name = "Ernest"
    )
;
-- thief’s accomplice who helped them escape is Berthold