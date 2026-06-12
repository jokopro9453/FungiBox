CREATE DATABASE mediciones;

USE mediciones;

CREATE TABLE lecturas_optimizadas(
id INT UNSIGNED AUTO_INCREMENT,
habitacion TINYINT UNSIGNED NOT NULL,
temperatura FLOAT NOT NULL,
presion_atm FLOAT NOT NULL,
movimiento TINYINT UNSIGNED NOT NULL,
tiempo TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
PRIMARY KEY (id)
);

DESCRIBE lecturas_optimizadas;

INSERT INTO lecturas_optimizadas (habitacion, temperatura, presion_atm, movimiento) VALUES ( 3, 21.4, 1012.8, 0);
INSERT INTO lecturas_optimizadas (habitacion, temperatura, presion_atm, movimiento) VALUES (7, 12.4, 1050.7, 0);
INSERT INTO lecturas_optimizadas (habitacion, temperatura, presion_atm, movimiento) VALUES (3, 19.7, 1000.4, 1);

SELECT * FROM lecturas_optimizadas;

SET SQL_SAFE_UPDATES = 0;

UPDATE lecturas_optimizadas SET temperatura  = temperatura + 2.0 WHERE (habitacion = 3);

SET SQL_SAFE_UPDATES = 1;

SELECT * FROM lecturas_optimizadas; 
DROP TABLE lecturas_optimizadas;

UPDATE lecturas_optimizadas SET temperatura  = temperatura + 2.0 WHERE (habitacion = 3)
