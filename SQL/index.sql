drop procedure if exists zqtest; 
delimiter $$$
create procedure zqtest(IN c_num INTEGER)
begin
declare i int default 0;
/*追加
@是用户变量
此处是局部变脸，declare后不用加＠
select count(*) into i from RULES;
i可以是变量或者表
*/
set i = (select count(*) from RULES);
set c_num = c_num + i;
start transaction;
while i<c_num do
INSERT INTO `RULES` VALUES 
(i,'device1','temparature','ORA',RAND()*10000,RAND()*10000 + 10),
(i+1,'device1','pressure','ATA',RAND()*30000,RAND()*20000 + 20),
(i+2,'device1','temparature','ORA',RAND()*10000,RAND()*30000 + 30),
(i+3,'device1','pressure','TA',RAND()*80000,RAND()*40000 + 40),
(i+4,'device1','temparature','ORA',RAND()*10000,RAND()*50000 + 50),
(i+5,'device1','pressure','AA',RAND()*80000,RAND()*60000 + 61),
(i+6,'device1','temparature','ORA',RAND()*10000,RAND()*70 + 70),
(i+7,'device1','pressure','ATA',RAND()*70,RAND()*80000 + 80),
(i+8,'device1','temparature','OR',RAND()*10000,RAND()*10000 + 100),
(i+9,'device1','pressure','TA',RAND()*20000,RAND()*10000 + 11),
(i+10,'device2','temparature','ORA',RAND()*10000,RAND()*20000 + 20),
(i+11,'device2','pressure','AA',RAND()*60000,RAND()*30000 + 31),
(i+12,'device2','temparature','ORA',RAND()*10000,RAND()*40000 + 40),
(i+13,'device2','pressure','AA',RAND()*50000,RAND()*60000 + 60),
(i+14,'device2','temparature','ORA',RAND()*10000,RAND()*70 + 70),
(i+15,'device3','pressure','AT',RAND()*40000,RAND()*80000 + 801),
(i+16,'device3','pressure','AT',RAND()*40000,RAND()*80000 + 801),
(i+17,'device3','temparature','ORA',RAND()*10000,RAND()*10000 + 10),
(i+18,'device3','pressure','TA',RAND()*30000,RAND()*20000 + 21),
(i+19,'device3','temparature','ORA',RAND()*10000,RAND()*30000 + 40),
(i+20,'device3','pressure','TA',RAND()*20000,RAND()*20000 + 31),
(i+21,'device1','pressure','ATA',RAND()*30000,RAND()*20000 + 20),
(i+22,'device1','temparature','ORA',RAND()*10000,RAND()*30000 + 30),
(i+23,'device1','pressure','TA',RAND()*80000,RAND()*40000 + 40),
(i+24,'device1','temparature','ORA',RAND()*10000,RAND()*50000 + 50),
(i+25,'device1','pressure','AA',RAND()*80000,RAND()*60000 + 61),
(i+26,'device1','temparature','ORA',RAND()*10000,RAND()*70 + 70),
(i+27,'device1','pressure','ATA',RAND()*70,RAND()*80000 + 80),
(i+28,'device1','temparature','OR',RAND()*10000,RAND()*10000 + 100),
(i+29,'device1','pressure','TA',RAND()*20000,RAND()*10000 + 11),
(i+30,'device2','temparature','ORA',RAND()*10000,RAND()*20000 + 20),
(i+31,'device2','pressure','AA',RAND()*60000,RAND()*30000 + 31),
(i+32,'device2','temparature','ORA',RAND()*10000,RAND()*40000 + 40),
(i+33,'device2','pressure','AA',RAND()*50000,RAND()*60000 + 60),
(i+34,'device2','temparature','ORA',RAND()*10000,RAND()*70 + 70),
(i+35,'device3','pressure','AT',RAND()*40000,RAND()*80000 + 801),
(i+36,'device3','temparature','ORA',RAND()*10000,RAND()*10000 + 10),
(i+37,'device3','pressure','TA',RAND()*30000,RAND()*20000 + 21),
(i+38,'device3','temparature','ORA',RAND()*10000,RAND()*30000 + 40),
(i+39,'device3','pressure','TA',RAND()*20000,RAND()*20000 + 31),
(i+40,'device1','temparature','ORA',RAND()*10000,RAND()*10000 + 10),
(i+41,'device1','pressure','ATA',RAND()*30000,RAND()*20000 + 20),
(i+42,'device1','temparature','ORA',RAND()*10000,RAND()*30000 + 30),
(i+43,'device1','pressure','TA',RAND()*80000,RAND()*40000 + 40),
(i+44,'device1','temparature','ORA',RAND()*10000,RAND()*50000 + 50),
(i+45,'device1','pressure','AA',RAND()*80000,RAND()*60000 + 61),
(i+46,'device1','temparature','ORA',RAND()*10000,RAND()*70 + 70),
(i+47,'device1','pressure','ATA',RAND()*70,RAND()*80000 + 80),
(i+48,'device1','temparature','OR',RAND()*10000,RAND()*10000 + 100),
(i+49,'device1','pressure','TA',RAND()*20000,RAND()*10000 + 11),
(i+50,'device2','temparature','ORA',RAND()*10000,RAND()*20000 + 20),
(i+51,'device2','pressure','AA',RAND()*60000,RAND()*30000 + 31),
(i+52,'device2','temparature','ORA',RAND()*10000,RAND()*40000 + 40),
(i+53,'device2','pressure','AA',RAND()*50000,RAND()*60000 + 60),
(i+54,'device2','temparature','ORA',RAND()*10000,RAND()*70 + 70),
(i+55,'device3','pressure','AT',RAND()*40000,RAND()*80000 + 801),
(i+56,'device3','temparature','ORA',RAND()*10000,RAND()*10000 + 10),
(i+57,'device3','pressure','TA',RAND()*30000,RAND()*20000 + 21),
(i+58,'device3','temparature','ORA',RAND()*10000,RAND()*30000 + 40),
(i+69,'device3','pressure','TA',RAND()*20000,RAND()*20000 + 31);
set i=i+21;
end while;
commit;
end
$$$
delimiter ;


call zqtest(100000)
select count(*) from RULES;

create index lmin_values on RULES(min_values);
--drop index lmin_values on RULES;

select count(*) from RULES where max_values >4000;

select count(*) from RULES where min_values >4000;
 

