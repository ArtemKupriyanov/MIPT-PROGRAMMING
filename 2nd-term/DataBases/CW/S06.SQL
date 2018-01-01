select 	CountryRegion.Name,	Contact.FirstName
from( select CountryRegion.Name, Contact.FirstName,
from
	CountryRegion
	join Address on CountryRegion.CountryRegionCode = Address.CountryRegionCode
	join CustomerAddress on Address.AddressID = CustomerAddress.AddressID
	join Customer on CustomerAddress.CustomerID = Customer.CustomerID
	join SalesOrderHeader on SalesOrderHeader.CustomerID = Customer.CustomerID
	join Contact on Contact.ContactID = SalesOrderHeader.ContactID
group by CountryRegion.Name, Contact.FirstName)


