select distinct model, type from Product
where model not like '%[^a-z]%' or model not like '%[^A-Z]%' or model not like '%[^0-9]%'

