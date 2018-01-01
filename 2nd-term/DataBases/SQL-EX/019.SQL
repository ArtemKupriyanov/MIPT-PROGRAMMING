select Product.maker, avg(Laptop.screen)
from Product inner join Laptop on Product.model = Laptop.model
group by Product.maker

