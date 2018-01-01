select count(*) 
from (
	select Customer.CustomerID
	from Customer join CustomerAddress on Customer.CustomerID = CustomerAddress.CustomerID
	group by Customer.CustomerID
	having count(*) > 1
) as my_table