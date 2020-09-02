
--mysql -uroot -p123456
--SOURCE creat_table.sql

create database test;
use test;

CREATE TABLE workorder
(    
    org text, # type of insect  
	depart text,
	equip text,
	workorder text,
    starttime DATE, # date collected  
    endtime DATE
);  
INSERT INTO workorder (org,depart,equip,workorder,starttime,endtime) 
VALUES('M1','MOLDING','MIXER1','Job1','2018-04-17','2018-04-21') ;
INSERT INTO workorder (org,depart,equip,workorder,starttime,endtime) 
VALUES('M1','MOLDING','MIXER1','Job2','2017-03-17','2017-04-21')


CREATE TABLE RULES
(    
    rule_id int,
    device text, 
	parameter text,
	alter_type text,
	min_values double,
	max_values double
);  
INSERT INTO RULES(	rule_id,device, parameter,alter_type,min_values,max_values) 
VALUES(1,'device1','temparature','WRA',1,1800) ;
INSERT INTO RULES(	rule_id,device, parameter,alter_type,min_values,max_values) 
VALUES(1,'device1','voltage','BTA',5,0) ;
INSERT INTO RULES(	rule_id,device, parameter,alter_type,min_values,max_values) 
VALUES(1,'device1','pressure','ATA',0,3000) ;

create index lmin_values on RULES(min_values);
show create table RULES;

show databases like %es%


show create table RULES;
desc RULES;

drop index lmin_values on RULES;

alter database haha charset gbk

show create table RULES;

create view tv as select * from RULES;

--update会被执行
explain update RULES set alter_type='sdf' where min_values=0;

--视图中的值会被更改
select * from tv;

select * from RULES order by max_values desc;
select concat(device,parameter) from RULES; 
select * from RULES  where parameter like '%re';

