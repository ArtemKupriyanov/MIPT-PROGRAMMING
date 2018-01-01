select name from battles where year(date) not in (select launched from ships where launched is not NULL)

