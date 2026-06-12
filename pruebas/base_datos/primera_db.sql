CREATE DATABASE control_domotico;
USE control_domotico;

CREATE TABLE estado_dispositivos(
id INT AUTO_INCREMENT,
dispositivo VARCHAR(50) NOT NULL,
estado_uso INT NOT NULL, 
PRIMARY KEY(id)
);

DESCRIBE estado_dispositivos;