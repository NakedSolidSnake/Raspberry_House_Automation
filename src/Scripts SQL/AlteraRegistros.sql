-- Modifica o id
UPDATE Usuarios
SET id = 99
WHERE id = 1;  

-- Modifica a Data
UPDATE Usuarios
SET timestamp = 01-01-01
WHERE id = 99;

-- Modifica o Nome
UPDATE Usuarios
SET Nome = 'Modificado'
WHERE id = 99;

