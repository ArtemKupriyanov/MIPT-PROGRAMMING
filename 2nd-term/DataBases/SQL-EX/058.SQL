SELECT M.maker, T.type, 
CAST(CAST((SELECT COUNT(*) 
FROM Product 
WHERE (maker = M.maker) 
AND type = T.type)*100 AS NUMERIC(6,2)) / 
(SELECT COUNT(*) 
FROM Product 
WHERE (maker = M.maker)) AS NUMERIC(6,2)) AS prc
FROM (SELECT DISTINCT maker 
FROM Product) AS M, 
(SELECT DISTINCT type 
FROM Product) AS T

