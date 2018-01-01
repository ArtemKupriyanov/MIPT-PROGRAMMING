Select name from classes join ships on classes.class = ships.class where (country = 'Japan' or country is NULL) and (type = 'bb' or type is NULL) and (numGuns >= 9 or numGuns is NULL) and (bore < 19 or bore is Null) and (displacement <= 65000 or displacement is Null)
Union
Select name from ships where class is NULL

