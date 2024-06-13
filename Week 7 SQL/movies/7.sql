SELECT movies.title, ratings.rating FROM movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE ratings.rating IS NOT NULL
AND year = 2010
ORDER BY ratings.rating DESC, movies.title ASC;
