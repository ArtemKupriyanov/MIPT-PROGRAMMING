--1) Создайте таблицы, заведите ключи. Разберитесь с инструкцией на примере созданной базы
DROP TABLE mdz1;

CREATE TABLE mdz1 (
  ндок       INT,
  Дата       DATE,
  Покупатель nvarchar(50),
  Товар      nvarchar(50),
  Колво      INT,
  Цена       FLOAT,
  CONSTRAINT pk_mdz1 PRIMARY KEY (ндок, Товар)
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

--2) Все даты (уникальные значения, ключевое слово distinct, пишется в предложении SELECT), когда покупался товар;
SELECT DISTINCT Дата FROM mdz1;
--3) Уникальных покупателей, которые закупались на прошлой неделе
--чет не робит сравнение дат
SELECT DISTINCT Покупатель FROM mdz1 
WHERE mdz1.Дата >= '24-10-2016' and mdz1.Дата <= '30-10-2016';

--4) Уникальных покупателей, упорядочить по фамилии;
--фамилия?
select distinct Покупатель from mdz1
order by Покупатель asc
--5) Посчитайте для каждой строки стоимости товара, купленного покупателем (колво * цена)
SELECT mdz1.Колво, mdz1.Цена, mdz1.Цена * mdz1.Колво FROM mdz1;
--6) Выбрать все документы, которые введены в январе 2016 и покупатель начинается с буквы «А» или колво в документе больше 5-ти, а цена меньше 10
SELECT *
FROM mdz1
WHERE mdz1.Дата >= '2016-01-01'
      AND mdz1.Дата <= '2016-01-31'
      AND (mdz1.Покупатель LIKE 'A%'
      OR (mdz1.Колво > 5 AND mdz1.Цена < 10));
--7) 5 первых покупателей, закупавшихся в сентябре 2016, из списка покупателей, упорядоченных по алфавиту;
SELECT TOP(5) T.Покупатель FROM ( SELECT mdz1.Покупатель
                    FROM mdz1
                    WHERE mdz1.Дата >= '2016-10-01' AND mdz1.Дата <= '2016-10-31'
                    ) as T
ORDER BY T.Покупатель ASC 
--8) Покупателей, которые покупали товар, название которого задано параметром;
 declare @product_name nvarchar(50)
 set @product_name = 'Edu'
 select mdz1.Покупатель from mdz1
 where mdz1.Товар = @product_name

--9) Номер документа, по которому продали товар с максимальной стоимостью (колво * цена);
select top(1) T.ндок
from (select mdz1.ндок, sum(mdz1.Колво*mdz1.Цена) as стоимость from mdz1
group by mdz1.ндок) as T
order by T.стоимость desc
--10) Подумать, как по каждому документу посчитать суммарную стоимость всех товаров в документе (если в документе несколько товаров)? (аналог «итого» в чеке в магазине).--1) Создайте таблицы, заведите ключи. Разберитесь с инструкцией на примере созданной базы
--так посчитал же в пунте 9 ?
select mdz1.ндок, sum(mdz1.Колво*mdz1.Цена) 
as Итог from mdz1
group by mdz1.ндок