with M as 
(
select PC.price, PC.model, PC.code
from PC join Product on PC.model = Product.model
where Product.maker = 'A'
union

select Laptop.price, Laptop.model, Laptop.code
from Laptop join Product on Laptop.model = Product.model
where Product.maker = 'A'
 )
select avg(price)
from M

