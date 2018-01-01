select distinct	Customer.CustomerID
from Customer inner join SalesOrderHeader on Customer.CustomerID = SalesOrderHeader.CustomerID
where (orderDate <= getdate() and OrderDate not between '2004-01-01' and getdate())
	