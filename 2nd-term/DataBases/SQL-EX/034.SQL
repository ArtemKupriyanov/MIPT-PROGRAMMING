select name from
Ships join Classes on Ships.class = Classes.class
where launched >= 1922 and displacement > 35000 and type = 'bb'

