SELECT movies.title FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE people.name = "Johnny Depp"

INTERSECT

SELECT movies.title FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE people.name = "Helena Bonham Carter";
