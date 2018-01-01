select model, price from Printer where price = (select max(price) from Printer)

