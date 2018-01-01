select distinct PC1.model, PC2.model, PC1.speed, PC1.RAM
from PC as PC1, PC as PC2
where (PC1.model > PC2.model) and (PC1.speed = PC2.speed) and (PC1.RAM = PC2.RAM)
