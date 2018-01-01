select customerType, count(customerID) as cnt
from Customer
group by customerType