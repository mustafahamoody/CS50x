/*
References
SQLite: EXCEPT Operator. (n.d.). TechOnTheNet. Retrieved August 9, 2023, from https://www.techonthenet.com/sqlite/except.php
*/

SELECT name FROM people WHERE id in
    (SELECT person_id FROM stars WHERE movie_id in
        (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Kevin Bacon" and birth = 1958)))
            EXCEPT SELECT name FROM people WHERE id in(SELECT id FROM people WHERE name = "Kevin Bacon" and birth = 1958);