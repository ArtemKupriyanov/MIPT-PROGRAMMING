DROP TABLE mdz1;

CREATE TABLE mdz1 (
  ????       INT,
  ????       DATETIME,
  ?????????? nvarchar(50),
  ?????      nvarchar(50),
  ?????      INT,
  ????       FLOAT,
  CONSTRAINT pk_mdz1 PRIMARY KEY (????, ?????)
);

INSERT INTO mdz1 VALUES (3, '2016-10-09', 'Artem', 'Auto', 2, 10090);
INSERT INTO mdz1 VALUES (1, '2016-10-08', 'Dima', 'Home', 1, 10302);
INSERT INTO mdz1 VALUES (2, '2016-10-07', 'Nastya', 'Edu', 5, 10306);
INSERT INTO mdz1 VALUES (4, '2016-10-06', 'Sasha', 'Drink', 15, 10036);
INSERT INTO mdz1 VALUES (4, '2016-10-15', 'Maxim', 'Sport-invent', 7, 15400);
INSERT INTO mdz1 VALUES (4, '2016-10-15', 'Anton', 'Startup', 1, 15400);
INSERT INTO mdz1 VALUES (4, '2016-10-10', 'Zhenya', 'Food', 30, 15400);
INSERT INTO mdz1 VALUES (4, '2016-10-01', 'Ira', 'Prints', 30, 14200);
INSERT INTO mdz1 VALUES (4, '2016-10-12', 'Vadim', 'Data', 1, 1350);
INSERT INTO mdz1 VALUES (7, '2016-10-25', 'Vlad', 'Docs', 7, 7);

SELECT * FROM mdz1;

