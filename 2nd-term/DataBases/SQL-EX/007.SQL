select * from (select model, price from PC
union
select model, price from Laptop
union
select model, price from Printer) as a
where a.model in (select model from Product where maker = 'B')
