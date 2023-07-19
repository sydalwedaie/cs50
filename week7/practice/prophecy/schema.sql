CREATE TABLE students (
    id INTEGER,
    student_name TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE houses(
    id INTEGER,
    house TEXT,
    head TEXT,
    PRIMARY KEY (id)
);

CREATE TABLE assignments (
    student_id INT,
    house_id INT,
    FOREIGN KEY (student_id) REFERENCES students(id),
    FOREIGN key (house_id) REFERENCES houses(id)
);