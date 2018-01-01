with m as
(
select model, price from Printer
union
select model, price from PC
union
select model, price from Laptop
)
select model from M where price in
(select max(price) from M)

