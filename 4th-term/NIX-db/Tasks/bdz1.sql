DROP TABLE matrixes;

CREATE TABLE matrixes (
	n_matrix INT not NULL,
	n_row INT not NULL,
	n_col INT not NULL,
	value INT not NULL
);

--1 3
--2 4
INSERT INTO matrixes 
VALUES (1, 1, 1, 1), (1, 2, 1, 2), (1, 1, 2, 3), (1, 2, 2, 4);

--1 0
--0 1
INSERT INTO matrixes 
VALUES (2, 1, 1, 1), (2, 2, 1, 0), (2, 1, 2, 0), (2, 2, 2, 1);

--1 1
--1 1
INSERT INTO matrixes 
VALUES (3, 1, 1, 1), (3, 2, 1, 1), (3, 1, 2, 1), (3, 2, 2, 1);

--1
--2
--3
INSERT INTO matrixes 
VALUES (4, 1, 1, 1), (4, 2, 1, 2), (4, 3, 1, 3)


--1 2 3
INSERT INTO matrixes 
VALUES (5, 1, 1, 1), (5, 1, 2, 2), (5, 1, 3, 3)

-- для п.9
-- Заводим матрицу D
-- 1 3 3
-- 2 3 1 
INSERT INTO matrixes 
VALUES (0, 1, 1, 1), (0, 2, 1, 2), (0, 1, 2, 3), (0, 2, 2, 3),
(0, 1, 3, 3), (0, 2, 3, 1)

--Заведем для теста матрицу А
--1 4 7
--2 5 8
--3 6 9
INSERT INTO matrixes 
VALUES (7, 1, 1, 1), (7, 2, 1, 2), (7, 3, 1, 3), (7, 1, 2, 4),
(7, 2, 2, 5), (7, 3, 2, 6), (7, 1, 3, 7),
(7, 2, 3, 8), (7, 3, 3, 9)

select * from matrixes;

--2) обычный вывод
declare @param INT;
set @param = 4;
select n_row, n_col, value 
from matrixes 
where matrixes.n_matrix = @param;

--3) меняю столбцы на строки и наоборот
declare @param INT
set @param = 1;
select n_col as n_row, n_row as n_col, value
from matrixes
where matrixes.n_matrix = @param;

--4) проверяются только квадратные матрицы.
--если все-таки нужно было проверять все, то вместо select COUNT(*)
--пишем iif(проверка на квадратность, которая реализована в п.7, COUNT(*), 1)
declare @param INT
set @param = 4;
select iif(T.cnt_not_equals = 0, 'yes', 'no') from 
(select COUNT(*) as cnt_not_equals from (select n_row, n_col, value 
from matrixes 
where matrixes.n_matrix = @param) as M inner join
(select n_col as n_row, n_row as n_col, value
from matrixes
where matrixes.n_matrix = @param) as M_transpose 
on M.n_col = M_transpose.n_col and M.n_row = M_transpose.n_row
where M.value <> M_transpose.value) as T;

--5) просто вывожу матрицу как в п.1, но value умножаю на число @n
declare @param INT, @n INT
set @param = 2;
set @n = 3;
select n_row, n_col, @n * value as value 
from matrixes
where matrixes.n_matrix = @param;

--6) в моем понимании - вектор - столбец или строка. 
--Поэтому я просто делаю проверку если число строк равно 1,
--то требуется, чтобы число столбцов было > 1. Матрицу 1 на 1
--я все-таки не считаю вектором. Аналогично, если число столбцов
--равно 1
declare @param INT
set @param = 5;
select iif(max(matrixes.n_row) = 1, 
iif(max(matrixes.n_col) > 1, 'yes', 'no'), 
iif(max(matrixes.n_col) = 1, 'yes', 'no')) as ans
from matrixes
where matrixes.n_matrix = @param;

--7) т.к столбцы занумерованы в порядке возрастания, то размер матрицы
--можно вычислить, выбрав максимальное значение по нумерации 
--столбцов и строк. 
declare @param INT
set @param = 1;
select 
iif(max(matrixes.n_col) = max(matrixes.n_row), 'yes', 'no') as ans
from matrixes
where matrixes.n_matrix = @param;

--8)
declare @param INT
set @param = 0;
select matrixes.n_row % 2 + matrixes.n_row / 2 as n_row, 
matrixes.n_col % 2 + matrixes.n_col / 2 as n_col, matrixes.value
from matrixes
where matrixes.n_matrix = @param and 
matrixes.n_col % 2 = 0 and matrixes.n_row % 2 = 1;

--9) джоим с собой же D. Получаем, что в новой матрице val1 и val2 задают координаты нужных
--элементов. Еще одном джойном выбираем уже нужные элементы из заданной матрицы
declare @m1 INT
set @m1 = 7
select A.value from (
(select n_row, n_col, value from matrixes where n_matrix = @m1) as A 
inner join
(select D1.value as val1, D2.value as val2 from (
(select * from matrixes where n_matrix = 0) as D1
inner join
(select * from matrixes where n_matrix = 0) as D2
on D1.n_col = D2.n_col and D1.n_row > D2.n_row)) as D_coord
on A.n_col = D_coord.val1 and A.n_row = D_coord.val2
)


--10) можно складывать матрицы только одинаковых рамеров.
--размер матрицы можно узнать по идее из п.7
declare @m1 INT, @m2 INT
set @m1 = 1
set @m2 = 7
select iif((select MAX(n_col) from matrixes where n_matrix = @m1) = 
(select MAX(n_col) from matrixes where n_matrix = @m2), iif( 
(select MAX(n_row) from matrixes where n_matrix = @m1) = 
(select MAX(n_row) from matrixes where n_matrix = @m2), 'yes', 'no'), 'no' )

--11) Джойним 2 матрицы, при условии, положение элемента первой матрицы
--совпадает с положением элемента второй матрицы. Возвращаем их сумму
declare @m1 INT, @m2 INT
set @m1 = 1
set @m2 = 2
IF (select iif((select MAX(n_col) from matrixes where n_matrix = @m1) = 
(select MAX(n_col) from matrixes where n_matrix = @m2), iif( 
(select MAX(n_row) from matrixes where n_matrix = @m1) = 
(select MAX(n_row) from matrixes where n_matrix = @m2), 'yes', 'no'), 'no' )) = 'yes'
begin
select m1.n_row, m1.n_col, m1.value + m2.value as value from
(select * from matrixes where n_matrix = @m1) as m1 inner join 
(select * from matrixes where n_matrix = @m2 ) as m2 on 
m1.n_col = m2.n_col and m1.n_row = m2.n_row
end
else
	select 'no solutions'

--12) 2 матрицы А и B можно перемножить, 
--если A in M(n x k) и B in M(k x m)
declare @m1 INT, @m2 INT
set @m1 = 7
set @m2 = 4
select iif((select MAX(n_col) from matrixes where n_matrix = @m1) = 
(select MAX(n_row) from matrixes where n_matrix = @m2), 'yes', 'no' )

--13)
declare @m1 INT, @m2 INT
set @m1 = 1
set @m2 = 2
IF iif((select MAX(n_col) from matrixes where n_matrix = @m1) = 
(select MAX(n_row) from matrixes where n_matrix = @m2), 'yes', 'no' ) = 'yes'
BEGIN
	select T.f_n_row, T.s_n_col, sum(T.value) as value from (select M1.n_row as f_n_row, M1.n_col as f_n_col, 
	M2.n_row as s_n_row, M2.n_col as s_n_col, M1.value * M2.value as value
	from (select * from matrixes where n_matrix = @m1) as M1
	inner join (select * from matrixes where n_matrix = @m2) as M2 
	on M1.n_col = M2.n_row) as T
	group by T.f_n_row, T.s_n_col
END
else
	select 'no solutions'

--14)
--нужно решить уравнение AX = B => X = A^(-1)*B = |т.к. матрица А - ортогональная| = A^T * B
--заведем ортогональную матрицу
--1 0
--0 -1
INSERT INTO matrixes 
VALUES (13, 1, 1, 1), (13, 2, 1, 0), (13, 1, 2, 0), (13, 2, 2, -1);

declare @B INT
set @B = 1
IF iif((select MAX(n_col) from matrixes where n_matrix = @B) = 
(select MAX(n_row) from matrixes where n_matrix = 13), 'yes', 'no' ) = 'yes'
BEGIN
	select T.f_n_row, T.s_n_col, sum(T.value) as value from (select M1.n_row as f_n_row, M1.n_col as f_n_col, 
	M2.n_row as s_n_row, M2.n_col as s_n_col, M1.value * M2.value as value
	from (select n_col as n_row, n_row as n_col, value from matrixes where n_matrix = 13) as M1
	--собственно джойним транспонированную ортогональную с В
	inner join (select * from matrixes where n_matrix = @B) as M2 
	on M1.n_col = M2.n_row) as T
	group by T.f_n_row, T.s_n_col
END
else
	select 'no solutions'

--15) аналогично сложению матриц
declare @C INT, @B INT
set @C = 2
set @B = 1
IF (select iif((select MAX(n_col) from matrixes where n_matrix = @C) = 
(select MAX(n_col) from matrixes where n_matrix = @B), iif( 
(select MAX(n_row) from matrixes where n_matrix = @C) = 
(select MAX(n_row) from matrixes where n_matrix = @B), 'yes', 'no'), 'no' )) = 'yes'
begin
select C.n_row, C.n_col, B.value - C.value as value from
(select * from matrixes where n_matrix = @C) as C inner join 
(select * from matrixes where n_matrix = @B ) as B on 
C.n_col = B.n_col and C.n_row = B.n_row
end
else
	select 'no solutions'
										