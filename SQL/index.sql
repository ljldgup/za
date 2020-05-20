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
(i,'device1','temparature','ORA',RAND()*100,RAND()*10 + 10),
(i+1,'device1','pressure','ATA',RAND()*30,RAND()*20 + 20),
(i+2,'device1','temparature','ORA',RAND()*100,RAND()*30 + 30),
(i+3,'device1','pressure','TA',RAND()*80,RAND()*40 + 40),
(i+4,'device1','temparature','ORA',RAND()*100,RAND()*50 + 50),
(i+5,'device1','pressure','AA',RAND()*80,RAND()*60 + 61),
(i+6,'device1','temparature','ORA',RAND()*100,RAND()*70 + 70),
(i+7,'device1','pressure','ATA',RAND()*70,RAND()*80 + 80),
(i+8,'device1','temparature','OR',RAND()*100,RAND()*100 + 100),
(i+9,'device1','pressure','TA',RAND()*20,RAND()*10 + 11),
(i+10,'device2','temparature','ORA',RAND()*100,RAND()*20 + 20),
(i+11,'device2','pressure','AA',RAND()*60,RAND()*30 + 31),
(i+12,'device2','temparature','ORA',RAND()*100,RAND()*40 + 40),
(i+13,'device2','pressure','AA',RAND()*50,RAND()*60 + 60),
(i+14,'device2','temparature','ORA',RAND()*100,RAND()*70 + 70),
(i+15,'device3','pressure','AT',RAND()*40,RAND()*80 + 801),
(i+17,'device3','temparature','ORA',RAND()*100,RAND()*10 + 10),
(i+18,'device3','pressure','TA',RAND()*30,RAND()*20 + 21),
(i+19,'device3','temparature','ORA',RAND()*100,RAND()*30 + 40),
(i+20,'device3','pressure','TA',RAND()*20,RAND()*20 + 31);
set i=i+21;
end while;
commit;
end
$$$
delimiter ;



