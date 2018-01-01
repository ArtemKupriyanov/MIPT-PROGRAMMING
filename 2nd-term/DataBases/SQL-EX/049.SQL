select name from classes join ships on classes.class = ships.class where bore = 16
union
select ship from classes join outcomes on class = ship where bore = 16

