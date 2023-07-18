-- list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title. Movies that do not have ratings should not be included in the result.

SELECT
    title,
    rating
FROM
    movies
    JOIN
        ratings
        on movies.id = ratings.movie_id
WHERE
    year = 2010
    AND rating IS NOT NULL
ORDER BY
    rating DESC,
    title ASC;