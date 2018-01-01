select Ships.class, name, country
from Classes join Ships on Classes.class = Ships.class
where numGuns >= 10

