select Product.maker, max(PC.price)
from Product inner join PC on PC.model = Product.model
group by maker
having (count(*) > 0)
