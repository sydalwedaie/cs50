-- list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
SELECT DISTINCT
    title
FROM
    movies
    JOIN
        stars
        ON movies.id = stars.movie_id
    JOIN
        people
        ON stars.person_id = people.id
    JOIN
        ratings
        ON ratings.movie_id = movies.id
WHERE
    people.name = 'Chadwick Boseman'
ORDER BY
    rating DESC LIMIT 5;