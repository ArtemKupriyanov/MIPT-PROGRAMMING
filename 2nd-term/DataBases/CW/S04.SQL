select Contact.FirstName, Contact.MiddleName, Contact.LastName, Contact.Phone
	from (Contact  join SalesOrderHeader on contact.ContactID = SalesOrderHeader.ContactID) 
		 join Customer on SalesOrderHeader.CustomerID=Customer.CustomerID
where Customer.CustomerType = 'I' and Contact.Phone like '1 (11) 500 555-01%'
order by Contact.Phone desc