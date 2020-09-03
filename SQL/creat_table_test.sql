--docker run -p 3306:3306 --name msq  -e MYSQL_ROOT_PASSWORD=123456 -d mysql
--docker exec -it msq /bin/bash
--mysql -uroot -p123456
--SOURCE creat_table_test.sql

create database test;
-- DROP DATABASE test
use test;

-- 最后一个字段没有逗号
--自增必须为主键
CREATE TABLE RULES
(    
    rule_id int not null auto_increment,
    device text, 
	parameter text,
	alter_type text,
	min_values double,
	max_values double,
    primary key(rule_id)
);  
INSERT INTO RULES(device, parameter,alter_type,min_values,max_values) 
VALUES('device1','temparature','WRA',1500,1800) ;
INSERT INTO RULES(device, parameter,alter_type,min_values,max_values) 
VALUES('device1','voltage','BTA',0,220) ;
INSERT INTO RULES(device, parameter,alter_type,min_values,max_values) 
VALUES('device1','pressure','ATA',1000,2000) ;
INSERT INTO RULES(device, parameter,alter_type,min_values,max_values) 
VALUES('device2','temparature','WRA',1100,1300) ;
INSERT INTO RULES(device, parameter,alter_type,min_values,max_values) 
VALUES('device2','voltage','BTA',0,10) ;
INSERT INTO RULES(device, parameter,alter_type,min_values,max_values) 
VALUES('device2','pressure','ATA',200,300) ;


create index lmin_values on RULES(min_values);
show create table RULES;


mysql -uroot -p123456
SOURCE creat_table.sql

show databases like %es%

show create table RULES;
desc RULES;

--drop index lmin_values on RULES;

--alter database test charset gbk

show create table RULES;

create view tv as select * from RULES;

--update会被执行
explain update RULES set alter_type='sdf' where min_values=0;

--视图中的值会被更改
select * from tv;

select * from RULES order by max_values desc;
select concat(device, parameter) from RULES; 
select * from RULES  where parameter like '%re';
----------------------------------------------------------------------------------------

-- 这里界面输入时要先将分割符改成//, 这应后面;会被当成文本处理，procedure才会被编译
DELIMITER //
create procedure procedure_test(in valve int, out ototal int)
BEGIN
    declare total int DEFAULT 5;
    select sum(max_values) + sum(min_values) into total from RULES where max_values > valve;
    select total into ototal;
END//
DELIMITER ;

set @total=1;
select sum(max_values) + sum(min_values) into @total from RULES where min_values > 500;
SELECT @total;

set @total=1;
call procedure_test(500,@total);
SELECT @total;

--------------------------------------------------------------------

drop trigger if exists trigger_test;

set @total=1;
CREATE TRIGGER trigger_test AFTER UPDATE ON RULES
       FOR EACH ROW SET @total = @total + NEW.max_values;
       
UPDATE RULES SET max_values=2000 where max_values > 2000;
select @total;


--BEFORE 可以修改插入修改的值
drop trigger if exists trigger_test; 

delimiter //
CREATE TRIGGER trigger_test BEFORE INSERT ON RULES
FOR EACH ROW
BEGIN
    IF NEW.min_values < 0 THEN
        SET NEW.min_values = 0;
    ELSEIF NEW.min_values > 100 THEN
        SET NEW.min_values = 100;
    END IF;
END;//
DELIMITER ;

INSERT INTO RULES(device, parameter,alter_type,min_values,max_values) 
VALUES('deviceT1','pressure','ATA',-123,321) ;
INSERT INTO RULES(device, parameter,alter_type,min_values,max_values) 
VALUES('deviceT2','pressure','ATA',123,321) ;
SELECT * FROM RULES;

CREATE TABLE sensor_records
(
    org text,  
    depart text,
    device text,
    parameter text,
    record_value int,
    record_time DATE
);

INSERT INTO sensor_records (org,depart,device,parameter,record_value,record_time) 
VALUES('M1','d1','device1','temparature',1899,'2018-04-21'),
    ('M2','d2','device1','voltage',130,'2019-06-21'),
    ('M3','d2','device1','pressure',1600,'2020-07-21'),
    ('M1','d1','device2','temparature',1899,'2018-08-21'),
    ('M2','d2','device2','voltage',330,'2019-01-21'),
    ('M3','d2','device2','pressure',1600,'2020-02-21'),
    ('M1','d1','device1','temparature',1199,'2018-03-21'),
    ('M2','d2','device2','voltage',330,'2019-04-21'),
    ('M3','d2','device2','pressure',1600,'2020-04-21');

    --table_name tn 表明缩写
--得到检测上上下限
select sr.org, sr.depart, sr.device,sr.record_value, r.alter_type,  r.min_values, r.max_values from sensor_records sr, RULES r where
sr.device = r.device and sr.parameter = r.parameter

select  ans.org as organization, ans.depart, ans.alter_type, 
if(ans.record_value > ans.max_values,'too high','too low') 
from 
(select sr.org, sr.depart, sr.device,sr.record_value, r.alter_type,  r.min_values, r.max_values 
from sensor_records sr, RULES r 
where sr.device = r.device and sr.parameter = r.parameter) ans
where ans.record_value > ans.max_values or ans.record_value < ans.min_values;
