CREATE TABLE `adeye_database`.`test` (
  `coordinate` POINT NOT NULL,
  `modified_time` DATETIME NOT NULL,
  `obstacle_size` FLOAT NULL,
  `weather_type` VARCHAR(45) NULL,
  PRIMARY KEY (`coordinate`,`modified_time`));