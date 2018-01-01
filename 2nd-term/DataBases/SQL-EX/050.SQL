select distinct battles.name from classes join ships on classes.class = ships.class and classes.class = 'Kongo' join outcomes on outcomes.ship = ships.name join battles on battles.name = outcomes.battle

