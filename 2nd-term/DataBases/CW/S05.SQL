select distinct	FirstName,	Address.City
from (Contact inner join SalesOrderHeader on Contact.ContactID = SalesOrderHeader.ContactID
			inner join Customer	on SalesOrderHeader.CustomerID = Customer.CustomerID and Customer.CustomerType = 'S'
			inner join CustomerAddress	on Customer.CustomerID = CustomerAddress.CustomerId	
			inner join Address	on CustomerAddress.AddressId = Address.AddressID)					
order by FirstName, Address.City