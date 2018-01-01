select distinct Product.type, Product.model, Laptop.speed
from Product inner join Laptop on Product.model = Laptop.model
where Laptop.speed < (	select min(PC.speed) from PC )
