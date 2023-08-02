p30-p67; p84-109 p123-129,p132-133
##### 0717
[29].列出各种地点的最低年龄,以及该年龄对人名
select min(age) as age, address from users group by address;

select a.name,b.age,b.address from users a join (select min(age) as age, address from users group by address) b on a.age=b.age and a.address=b.address;

[30].列出各个部门male的最低年龄
select min(age) as age,address from users where gender='male' group by address;

mysql函数:ifnulll(xxx,0)

[31].列出所有员工年工资,按照年薪从低到高排序

[32].列出用户朋友年龄大于30的用户名称和朋友名称;



##### 0621
[22].列出年龄高于公司平均年龄的员工,所在地址别名,朋友,工资等级
1.找到平均薪资
select avg(age) as avgage from users;
2.和users(朋友),agegrade(工资等级),addr(地址别名)做表的左连接.
select a.name,b.anoname,c.name,d.grade 
from users a join (select avg(age) as avgage from users) t on a.age>t.avgage 
left join addr b on a.address=b.address 
left join users c on a.friendid=c.id 
left join agegrade d on a.age between d.loage and d.hiage;
标签:[多表查询],[左连接]

[23].列出与kong性别相同的所有员工及其地址名称.
1.找到kong的性别
select gender from users where name='kong';
2.(注意,要不包含kong的话,要加上and筛选)
select a.name, a.address from users a where a.gender=(select gender from users where name='kong' and a.name<>kong);

[24].列出年龄等于地址'beijing'中的员工年龄的其他员工姓名和年龄;
1.地址等于beijing的员工年龄
select distinct age from users where address='beijing';
2.s
select a.name,a.age from users a where a.age in (select distinct age from users where address='beijing') and a.address<>'beijing';
[debug]注意对于select age from users having address='beijing';会报错.但select * from users having address='beijing';不报错; 虽然说,没有group by默认分一组,但这个和group by分一组是不同的.这个分组只是对于聚合函数而言的;就是说在select的时候如果前面没有group by默认分一组,但不使用聚合函数,用*,或者其他查询的话,就没有分组的概念了.如果默认分一组了,就要满足一组在一行中不能有歧义这个关键概念; 而对于上述报错区别,不要去细究了.只要遵守语法规范,having和group by一起出现,就不会出问题.

[25].列出年龄高于地址在beijing的所有员工年龄的员工姓名,年龄和地址别名
1.beijing最大年龄
select max(age) from users where address='beijing';
2.s
select a.name,a.age,b.anoname 
from users a left join addr b on a.address=b.address 
where a.age>
(select max(age) from users where address='beijing') 
and a.address<>'beijing';

[26].列出每个地址员工的员工数量,平均年龄
1.员工数量表
select address,count(*) as num, avg(age) as avage
 from users group by address;

[27].列出所有员工的姓名,地址别名和工资等级和工作年限
select a.name,b.anoname,c.grade, timestampdiff(MONTH,a.entrydate,now()) as nianxian from
  users a left join addr b on a.address=b.address
  left join agegrade c on a.age between c.loage and c.hiage;
注意:计算日期差距的函数 timestampdiff

[28]列出所有地址的详细信息和人数
1.地址人数:
select address, count(*) as num from users group by address;
2.s
[会出现none]
?这里应该也有办法调整的吧?
select a.*,b.num from addr a 
left join (select address, count(*) as num from users group by address) b on a.address=b.address;

[不会出现none的版本,核心在于统计人数而不是统计目录条数]
select a.address,a.anoname,a.value,a.dis,count(b.name) from addr a left join users b on b.address=a.address group by a.address,a.anoname,a.value,a.dis;

##### 0620
[15]列出受雇日期早于其朋友的所有人的姓名,id的地址别名
(内连接外连接本质区别在于,对于未匹配的项,内连接直接丢弃,不管了.外连接会把主表所有为匹配的项也显示出来)
1.受雇日期早于其朋友的(如果有NULL就不管)
select a.name,a.id from  users a join users b on a.friendid=b.id and a.entrydate< b.entrydate;
2.和地址表做外连接查询别名
select a.id,a.name,b.anoname from (select a.name,a.id,a.address from  users a join users b on a.friendid=b.id and a.entrydate< b.entrydate) a left join addr b on a.address=b.address;

[16]列出地址别名和这些地址的员工信息,同时列出没有员工的地址;
1.地址和员工做表连接
select distinct a.anoname, b.* from addr a left join users b on a.address=b.address order by a.anoname desc;

[17]列出至少有5个人员的所有地址
1.统计每个地址人数的表
select address, count(name) from users group by address having count(*)>=5;

[18]列出年龄比linchong大的所有员工信息
1.找出linchong的年龄
select age from users a where a.name='linchong';
2.>上述年龄
select * from users a where a.age > (select age from users a where a.name='linchong');

[19]列出所有男性的姓名,地址名称,地址人数
1.生成部门名称,部门人数表
select address,count(*) as num from users group by address;
2.users 和上述表做表连接;
select a.name,a.address,b.num from users a join (select address,count(*) as num from users group by address) b on a.address=b.address and a.gender='male';

[20]列出最低年龄大于20的各种地址,以及地址人数
1.地址-地址人数-最低年龄表->20
select address,count(*) as num,min(age) as mage from users group by address having min(age)>20;

[21]列出所在地址别名'sds'对人员姓名:
1.查处sds对应的地址名表,
select address from addr where anoname='sds';
2.根据地址名表在users中的筛选
select a.name from users a join (select address from addr where anoname='sds') b on a.address = b.address;


##### 0619
alter user 'root'@'localhost' identified with mysql_native_password by 'qxy123';
过滤:distinct

[06].取得平均年龄最高的地点的别名
1.每个地点的平均年龄
select address, avg(age) as age from users group by address;

2.排序值后取第一个,和addr做内连接
select a.anoname from addr a join (select address, avg(age) as age from users group by address order by age desc limit 1) b on a.address=b.address;

[07]平均年龄的等级最低的地址的地址别名
(这里做的题意不一样,题意是平均年龄的等级,这里是平均的年龄等级)
1.平均年龄等级最低的地址
2.和addr表做表连接
(三表连接)
select c.anoname,avg(b.grade) as grade from users a join agegrade b join addr c where a.age between b.loage and b.hiage and a.address=c.address group by c.anoname order by grade asc limit 1;

(正确理解题意的做法)
1.找到地址的平均薪水的等级表
2.找到平均薪水最低的等级
3. 1\2表连接

[08]取得比没有入职日期的员工最大年龄还大的年龄.
1.没有入职日期的员工的最大年龄 (查询空字符要用is NULL)
select age from users where entrydate is NULL order by age desc limit 1;
2.有入职日期的员工年龄,姓名
select name,age from users where entrydate is not null;
3.1 1.2表连接
select a.name, a.age from (select name,age from users where entrydate is not null) a join (select age from users where entrydate is NULL order by age desc limit 1) b on a.age > b.age;
3.2 1筛选,值大于2
select name,age from users where entrydate is not null and age>(select age from users where entrydate is NULL order by age desc limit 1);

[09]年龄最大的前5名员工
select name,age from users order by age desc limit 0,5;

[10]年龄最大的前6-10名员工
select name,age from users order by age desc limit 5,5;

[11]取得最后入职的5名员工
select name,entrydate from users order by entrydate desc limit 0,5;

[12]取得每个年龄等级的员工数;
1. 获得姓名-年龄等级表
select a.name,b.grade from users a join agegrade b on a.age between b.loage and b.hiage;
2.对该表按年龄等级分组,并count name
select count(a.name) as num,b.grade from users a join agegrade b on a.age between b.loage and b.hiage group by b.grade;  

[13]面试题
有三个表s(学生表),c(课程表),sc(学生选课表)... 跳过了

[14]列出所有人和他朋友的名字;
select a.id as id, a.name as aname,b.name as bname from users a left join users b on a.friendid=b.id order by a.id;
这里有两个点要注意:1.要用左外连接(但不能用右外连接),因为没有朋友的人也要被列出来. 2.内连接可以不用on但外连接一定要有on


##### 0613
[05].取得平均年龄最高的地址的地址别名(两种解决方案)
方案1:
1.取得平均年龄最高的地址(降序排列选第一个)
select address from users group by address order by avg(age) desc limit 1;
2.内连接最好的部门的别名
select a.anoname from addr a join (select address from users group by address order by avg(age) desc limit 1) b on a.address=b.address;

方案2:
(内连接一样,第一步不一样)使用max;
1.1每个部门平均薪水
select address,avg(age) as age from users group by address;
1.2取上述表的最大值
select a.address,a.avg from users a join (select max(age) from (select address,avg(age) as age from users group by address) t) t where a.a;


##### 0612
[03].取得地址中所有人的平均的年龄等级.
1.取得地址中所有人的年龄等级.
select a.address,b.grade from users a join agegrade b on a.age  between b.loage and b.hiage;
2.按地址分组并取平均
select a.address,avg(b.grade) from users a join agegrade b on a.age  between b.loage and b.hiage group by a.address;

[04].不用组函数max取得最高年龄;
方案1:order by 降序取第一个
select age from users order by age desc limit 0,1;
方案2:表的自连接
1.取年龄中比自己小的年龄 复习distinct 和 not in关键字
select distinct b.age from users a join users b on a.age>b.age;
2.把上表做为子表,使用not in 反着取
select age from users where age not in (select distinct b.age from users a join users b on a.age>b.age);

##### 0611
p62-67 p132-133
select后面出现的子查询(不需要掌握,了解即可)
案例:找出每个员工的部门名称,要求显示员工名,部门名?
`select name,(select anoname from addr where users.address=address) as addr from users;`

4 union 合并查询结果集
案例:查询地址是beijing和shanghai的名字
select name,address from users where address='shanghai' or address='beijing';
select name,address from users where address in ('shanghai','beijing');

select name,address from users where address in ('shanghai')
union
select name,address from users where address in ('beijing');

注意:union效率要搞一些,对于表了解来说,每连接一次新表,则匹配的次数满足笛卡尔积,成倍的翻;union可以减少匹配次数,在减少匹配次数的情况下,还可以完成两个结果集的拼接.
union在进行结果集合并的时候,要求两个结果集的**列数**相同(而不是关键字匹配);

5 limit(非常重要)
5.1 limit将查询结果集的一部分取出来,通常使用在分页查询当中.

5.2 limit怎么用?
  按照年龄降序取出前5名的员工.
select name,age from users order by age desc limit 0,5; //从序号0开始,取前5;
用法:
  limit startIndex,length; //statIndex 起始下标,length 长度;
缺省用法:
  limit length;
注意:limit在order by之后执行.
取出年龄排3-5名的员工:
select name,age from users order by age desc limit 3,3;
取出年龄排名在5-9名的员工
select name,age from users order by age desc limit 4,5;

6.DQL语句大总结:
select...from...where...group by...having...order by...limit
执行顺序:
from->where->group by->having->select->order by->limit;

作业题:
[01].获取每个地址最大年龄的人员名称; [Fail]
  step1:找出每个地址最大的年龄
  select address, max(age) from users group by address;
  
  step2:表连接 a.age = b.age and a.ddress = b.address;
  select a.address, a.name from
  users a join
  (select address, max(age) as age from users group by address) b on
  a.age=b.age and a.address=b.address;

[02].哪些人的年龄在地址的平均年龄之上.
step1:部门的平均年龄表:
  select address, avg(age) as age from users group by address;
step2:表连接:a.age>b.age and a.address=b.address
select 
  a.name, a.age
from 
  users a
join
  (select address, avg(age) as age from users group by address) b
on
  a.age>b.age and a.address=b.address;  
注意:括号不能少



##### 0607
p61
SELECT...FROM...where...group by...having...order by...limit...
3.4 from子句中的子查询
注意:from后面的子查询,可以将子查询的查询结果当作一张临时表.
案例:找出每个岗位的平均工资的薪资等级.
step1:找出每个addr的平均age,按照address分组求平均值.
select addr,avg(age) from users group by addr;
step2:克服心理障碍,把以上的查询结果就当作一张真实存在的表t.
表链接,avg(sal) between s.losal and s.hisal;

select
  t.* , s.grade
from 
  (select address,avg(age) as avgage from users group by address) t
join
  agegrade s
on
  t.avgage between s.loage and s.hiage;



##### 0322

P84-95 tar:95-109 123-129
**4.union**
合并查询结果集,将两个查询结果集合并
mysql> select * from users where address='shanghai'
    -> union
    -> select * from users where address='shandong';

union 效率高一些(对于表连接而言).
注意事项:union在进行结果集合并时,要求前后结果集列数要相同. (列数据类型不同,mysql允许但oracle会报错)

**limit**
将查询结果集的一部分取出来,通常使用在分页查询中.

**7.约束** 非常重要五颗星
7.1 什么是约束
  constraint:在创建表的时候,我们可以给表中字段加上一些约束,来保证表中数据完整性,有效性.
  约束的作用:保证表中数据有效.

7.2 约束包括哪些?
  非空约束:not null, 唯一性约束:unique, 主键约束:primary key, 外键约束:foreign key, 检查约束:check (mysql不支持);

**7.3非空约束** not null
非空约束 约束的字段不能为null
not null只有列级约束
```sql
drop table if exists t_vip;
create table t_vip(
  id int,
  name varchar(255) not null
);
insert into t_vip(id,name) values (1,'zhangsan');
insert into t_vip(id,name) values (2,'lisi');
--报错:字段不能为空
insert into t_vip(id) values (3);
```
插曲: XXX.sql被称为sql脚本文件.sql脚本文件中编写了大量sql语句.执行文件时,该文件中所有sql语句会批量全部执行. 通过source语句批量执行vip.sql中的sql代码

**7.4唯一性约束** unique
不能重复,但可以为null(可以有多条数据为null值)
```sql
drop table if exists t_vip;
create table t_vip(
  id int,
  name varchar(255) unique,
  email varchar(255)
);
insert into t_vip(id,name,email) values(1,'zhangsan','zhangsan@123.com');
insert into t_vip(id,name,email) values(2,'lisi','lisi@123.com');
insert into t_vip(id,name,email) values(3,'wangwu','wangwu@123.com');
select * from t_vip;
```
Duplicate entry 'wangwu' for key 'name'

两个字段联合唯一(只要两个字段不完全一致就行)  唯一性约束可以放在列后面,也可以单独加.
```sql
drop table if exists t_vip;
create table t_vip(
  id int,
  name varchar(255),
  email varchar(255),
  unique(name,email)
);
insert into t_vip(id,name,email) values(1,'zhangsan','zhangsan@123.com');
insert into t_vip(id,name,email) values(2,'zhangsan','zhangsan2@123.com');
insert into t_vip(id,name,email) values(3,'wangwu','wangwu@123.com');
select * from t_vip;
```
列级约束:约束直接添加到列后面; 表级约束:没有添加到列后面的约束.

unique 和 not null联合
```sql
drop table if exists t_vip;
create table t_vip(
  id int,
  name varchar(255) not null,
  email varchar(255) not null,
  unique(name)
  -- unique(name,email)
);
insert into t_vip(id,name,email) values(1,'zhangsan','zhangsan@123.com');
insert into t_vip(id,name,email) values(2,'zhangsan','zhangsan2@123.com');
insert into t_vip(id,name,email) values(3,'wangwu','wangwu@123.com');
select * from t_vip;
desc t_vip;
```
注意: 字段被unique和not null联合约束的话,该字段自动变成主键; 如果多个字段均(unique+not null)的话,则靠前的字段变位主键.

**7.5主键约束** 非常重要,五颗星
相关术语: 主键约束:一种约束, 主键字段:添加了主键约束的字段, 主键值:主键字段中的每一个值.
主键:主键值时每一行记录的唯一标识.主键值是每一行记录的身份证号.
任何一张表都应该有主键,没有主键表无效.
主键的特征: not null + unique 主键值不能是NULL,同时也不能重复
主键支持列级约束和表级约束
给一张表添加主键约束:
```sql
drop table if exists t_vip;
create table t_vip(
  id int primary key,
  name varchar(255)
);
insert into t_vip(id,name) values(1,'zhangsan');
insert into t_vip(id,name) values(2,'zhangsan');
insert into t_vip(id,name) values(2,'wangwu');
select * from t_vip;
desc t_vip;
```

联合添加主键约束: id,name联合起来做主键(复合主键); 一个字段做主键:复合主键
```sql
drop table if exists t_vip;
create table t_vip(
  id int,
  name varchar(255),
  primary key (id,name)
);
insert into t_vip(id,name) values(1,'zhangsan');
insert into t_vip(id,name) values(2,'zhangsan');
insert into t_vip(id,name) values(2,'wangwu');
select * from t_vip;
desc t_vip;
```
实际开发不建议使用复合主键,建议使用单一主键.因为主键的意义就是身份证号.但以主键就可以做到.复合主键比较复杂,不建议使用.

一个表中主键约束能加2个吗: 不能!
主键值建议类型:int,bigint,char等类型. 不建议:varchar来做主键. 一般都是数字,一般都是定长的.

除了单一主键,复合主键之外,还可以分成: 自然主键,业务主键
自然主键:主键值是个自然数,和业务没关系
业务主键:主键值和业务紧密关联
实际开发中,自然主键使用比较多.

mysql自动维护主键 (auto_increment)表示从1开始以1递增, auto_increment 必须跟主键关键字.
```sql
drop table if exists t_vip;
create table t_vip(
  id int primary key auto_increment,
  name varchar(255)
);
insert into t_vip(name) values('zhangsan');
insert into t_vip(name) values('zhangsan');
insert into t_vip(name) values('wangwu');
select * from t_vip;
desc t_vip;
```

**7.6外键约束** foreign key(简称fk) 非常重要,五颗星
相关术语:外键约束:一种约束, 外键字段:该字段上添加了外键约束, 外键值:外键字段当中的每一个值

业务背景:
  请设计数据库表,来描述'班级和学生'的信息?
  第一种方案:班级和学生存储在一张表中
no(pk)  name  classno   classname
-------------------------------------
1       jack   100      aoisdoqwejidoiqjodija33(1)
4       hanxi  100      aoisdoqwejidoiqjodija33(1)
5       zs     101      aoisdoqwejidoiqjodija33(2)
8       zl     101      aoisdoqwejidoiqjodija33(2)
9       wq     101      aoisdoqwejidoiqjodija33(2)
浪费空间

  第二种:班级一张,学生一张
t_stu
no(pk)  name    cno
--------------------
1       jack    100
2       lucy    100
3       lilei   100
4       hanxi   100
5       zs      101
6       ls      101
7       ww      101
8       zl      101
9       wq      101

t_class
classno(pk)  classname
------------------------------
100           aoisdoqwejidoiqjodija33(1)
101           aoisdoqwejidoiqjodija33(2)

外键约束:cno字段无约束可能导致数据无效. 设置cno为外键字段,cno中的值是外键值.
注意 t_class 父表, t_stu 子表
删除表顺序:先子后父; 创建:先创建父,再创建子; 删数据: 先子后父; 插入数据:先父后子
```sql
drop table if exists t_student;
drop table if exists t_class;
create table t_class(
  classno int primary key,
  classname varchar(255)
);

create table t_student(
  no int primary key auto_increment,
  name varchar(255),
  cno int,
  foreign key(cno) references t_class(classno);
)
insert into t_class(classno, classname) values(100,'aoisdoqwejidoiqjodija33(1)');
insert into t_class(classno, classname) values(101,'aoisdoqwejidoiqjodija33(2)');

insert into t_student(name,cno) values('jack',100);
insert into t_student(name,cno) values('lucy',100);
insert into t_student(name,cno) values('lilei',100);
insert into t_student(name,cno) values('hanxi',100);
insert into t_student(name,cno) values('zs',101);
insert into t_student(name,cno) values('ls',101);
insert into t_student(name,cno) values('ww',101);
insert into t_student(name,cno) values('zl',101);

select * from t_class;
select * from t_student;
desc t_student;
```
子表引用父表的字段: 至少需要具备unique (也就是说unique和primary key两个约束都可以)
子表的外连接字段可以为null

**8.存储引擎:**(了解内容)
8.1 什么是存储引擎,有什么用呢.
  存储引擎是mysql中特有的一个术语. 是一个表存储/组织数据的方式.不同的存储引擎,表存储数据的方式不同.

8.2 怎么给表指定存储引擎呢?
  show create table t_student;
CREATE TABLE `t_student` (
  `no` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `cno` int(11) DEFAULT NULL,
  PRIMARY KEY (`no`),
  KEY `cno` (`cno`),
  CONSTRAINT `t_student_ibfk_1` FOREIGN KEY (`cno`) REFERENCES `t_class` (`classno`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8
结论: 默认存储引擎InnoDB, 默认字符集是UTF-8

8.3 查看mysql支持的存储引擎
show engines; 
show engines \G;

8.4 关于mysql常用存储引擎: (三个比较常见的,MyISAM, InnoDB, MEMORY)
*MyISAM:*
管理的表具有以下特征:
  使用*三个文件*表示每个表:
      格式文件: 表结构的定义(.frm); 数据文件:表行的内容(.MYD); 索引文件:一本书的目录,提高查询效率的一种方式(.MYI)
      提示:主键或者unique约束字段上会自动创建索引.
  特点:可被转换为压缩,只读,来节省空间. 
      不支持事物机制,安全性低.

*InnoDB*:
mysql默认的存储引擎,重量级存储引擎.InnoDB*支持事物*,支持数据库崩溃后自动恢复机制.
InnoDB最主要的特点是非常安全
  表空间存储数据+索引(表空间是一个逻辑名称.)
  数据表结构存在.frm文件中

特点:支持事物,安全
    效率低,不支持压缩,不能很好的节省空间.

*MEMORY*:
内存存储引擎.数据存储在内存中,且行的长度固定.
  每个表以.frm文件表示. 表的数据以及索引存储在内存中. 不能包含TEXT,BLOB字段.

特点:存储引擎非常快.
    不安全,断电(关机)数据就消失.不支持事物.


**9事物** 必须掌握,必须精通. 非常重要,五颗星

9.1. 什么是事物?
  一个事物就是一个完整的业务逻辑.
  是一个最小的工作单元,不可再分.

  完整业务逻辑: A->B1000: A账户-10000, B账户+10000;
  以上操作是一个最小的工作单元,要么同时成功,要么同时失败,不可再分.

9.2 只有DML才会有事务一说.
  insert, delete, update; 只有以上三个语句和事物有关系.

9.3 本质上,一个事务就是多条DML语句 同时成功 或者 同时失败 .

9.4 事物如何做到多条语句同时成功或者同时失败.
  InnoDB存储引擎:提供一组用来记录事物性活动的日志文件
  每一条DML的操作都会记录到'事务性活动的日志文件'中.
  我们可以提交事物:清空事务性活动的日志文件,将数据全部彻底持久化到数据库表中.标志着事务的结束,并且是一种全部成功的结束.
  也可以回滚事物:将之前所有的DML操作全部撤销.并且将清空事务性活动的日志文件.回滚事务标志着,事务的结束,并且是一种全部失败的结束.

9.5 提交事务,回滚事务.
  事务: transaction;  提交事务: commit;  回滚事务: rollback;
  mysql 默认情况下自动提交事务(每执行一次DML语句就提交一次事务.)
  开启事务(关闭自动提交机制): start transaction;
  关闭事务(开启自动提交机制):set autocommit=1;

9.6 事务包括四个特性
A:原子性 事务是最小工作单元.不可再分 I:隔离性 A事务和B事务之间具有一定的隔离.A在操作一张表时,B也操作会怎样. D:持久性 事务最终结束的一个保障.相当于将没有保存到硬盘上的数据保存到硬板上.  C:一致性 所有事务要求,在同一个是当中,必须同时成功或者同时失败.

9.7 事务隔离性
  读未提交:read uncommitted
    问题: 脏读现象, dirty read
    一般都是理论上的,大多数数据库都是二档起步

  读已提交 read committed
    事务A只能读取到事务B提交之后的数据
    解决了脏读现象
    问题: 不可重复读取数据; 即在事务开启之后,第一次读到数据是3条,当前数据还没有结束,可能第二次读取时候读到了四条.
    这种隔离级别是比较真实的数据,每一次读到的数据是绝对真实.Oracle默认是读已提交

  可重复读 repeatable read:
    事务A开启之后,每一次在事务A中读取到的数据都是一致的.即是事务B将数据已经修改并提交,事务A读取道的数据还是没有发生改变.
    解决了不可重复读的问题.
    问题: 幻影读.每一次读取到的数据都是幻像.不够真实.
    mysql默认隔离级别.

  序列化/串行化 seralized read:
    最高隔离级别,效率最低. 这种隔离级别表示事务排队执行,*不能并发*.

**4.数据库设计三范式:**
数据库表的设计依据.教你怎么进行数据库设计.
  第一范式: 要求任何一张表必须有主键,每一个字段原子性不可再分.
  第二范式: 建立在第一范式基础之上.要求所有非主键字段完全依赖主键,不要产生部分依赖.
  第三范式: 建立在第二范式之上,要求所有非主键字段直接依赖主键,不要产生传递依赖.

4.3. 第一范式
最核心,所有表设计都需要满足.
必须有主键,每一个字段都是原子性不可再分.

4.4. 第二范式
建立在第一范式基础之上.要求所有非主键字段必须完全依赖主键.不要产生部分依赖.
学生老师关系-多对多关系. 张三依赖1001, 王老师依赖001,产生了部分依赖.数据冗余,空间浪费.
为了让以上表满足第二范式,使用三张表来表示多对多关系.1张学生表,1张教师表,1张学生教师关系表.
口诀: 多对多,三张表,关系表两个外键.

4.5 第三范式
  要求所有非主键字段必须直接依赖主键,不要产生传递依赖.
学生编号(PK)  学生姓名  班级编号  班级名称
--------------------------------------
1001         张三     01       一年一班
1002         李四     02       一年二班
1003         王五     03       一年三班
1004         赵六     03       一年三班

班级-学生 一对多(一个教室中有多个学生)
满足第一范式,有主键
满足第二范式,主键不是复合主键,没有产生部分依赖.主键是单一主键
不满足第三范式:班级名称依赖班级编号,班级编号依赖学生编号.产生了传递依赖.产生了数据冗余.
设计一对多: 分成两个表去存. 学生表,班级表.
口诀: 一对多,两张表,多的表加外键.


##### 0320
p51-p60
**连接查询**mysql中最重要内容
2.1从一张表中单独查询,称为单表查询. 从emp表和dept联合查询数据,从emp取员工名字,从dept表中取部门名字,叫跨表查询

2.2分类:年代分类:SQL92,SQL99; 分类方式分类:*内连接*(等值连接,非等值连接,自连接),*外连接*(左外连接/左连接;右外连接/右连接),全连接(不讲)

```sql
创建一个address表
address, anoname, value, dis
beijing, berjier, 95, 50
shanghai, sanghei, 91, 35
shandong, sds, 80, 55
nanjing, jinling, 85, 20
创建一个表:
create table addr(address varchar(20),anoname varchar(20), value int(11), dis int(11));
插入数据:
insert into users values 
  (13,'fangsheng',21,2021,'nanjing','male',13),
  (14,'hudie',18,2021,'beijing','female',14),
  (15,'mubai',46,2021,'shandong','male',15),
  (16,'guli',33,2021,'shandong','female',16);
update users set workno=lpad(workno,5,0);
```

2.3 当两张表进行连接查询是,没有任何条件的限制,会发生什么现象?
A:第一表的每一个数据和第二表的所有数据进行匹配.--笛卡尔积现象:当两张表进行连接查询,没有任何限制的时候,最终查询的结果条数是两张表条数的乘积
select name,anoname from users, addr;

2.4 如何避免笛卡尔积现象: 连接时加条件,满足这个条件的记录被筛选出来.
mysql> select name,anoname from users, addr where users.address=addr.address;
筛选了无效匹配,但在匹配过程中,匹配次数没有减少,执行效率比较低


**内连接之等值连接**
案例:查询每个用户所在地址别名,显示员工名和地址别名;
(废弃)SQL92, 内连接之等值连接 连接条件和过滤条件柔杂在一起,结构不清晰 (几乎不再使用了)
(废弃)select e.name, d.anoname from users e, addr d where e.address = d.address;

SQL99 表连接条件是独立的, 和过滤条件分离, 如果还需进一步筛选,再往后继续添加 join ; on 是连接条件
select e.name, d.anoname from users e join addr d on e.address = d.address;

**内连接之非等值连接** 条件不是一个等量关系,称为非等值连接
mysql> select  e.name, e.age, s.grade from users e join  agegrade s on e.age between s.loage and s.hiage order by s.grade;

**内连接之自连接**: 一张表看作两张表.
select a.name as yg ,b.name as ld from users a join users b on a.friendid=b.id;

**外连接**
右外连接: 又叫右连接. 将join关键字右边的表看成主表,主要将右表的数据全部查询出来,稍带着查询左表; 外连接中,两张表存在主次关系. right 后面有个outer可省略
select e.name, d.anoname from users e right join addr d on e.address=d.address;

左外连接: 又叫左连接. left 后面有个outer 可省略 
mysql> select e.name, d.anoname from users e left join addr d on e.address=d.address;

**2.9三张表连接**
语法:select ... from a join b on a和b的连接条件 join c on a和c的连接条件 join d on a和d的连接条件.
多表连接的原理顺序执行后序语句,每次和下一个join连接的表是上一张连接之后生成的新表.
select a.name,b.value,c.grade from users a join addr b on a.address=b.address join agegrade c on a.age between c.loage and c.hiage order by grade desc ,value asc;

**子查询**
3.1什么是子查询,select语句嵌套select语句,被嵌套的语句称为子查询

where中的子查询:
查询大于平均年龄的员工:
select name, age from users where age>(select avg(age) from users) order by age;


##### 0318
p50
**19.分组查询**非常重要五颗星

GROUP BY; where 分组前过滤; having 分组后过滤;
SELECT gender,count(*) FROM users GROUP BY gender;
SELECT gender,avg(age) FROM users GROUP BY gender;
SELECT address, count(*) FROM users WHERE age <30 GROUP BY address HAVING count(*)>=3;

select ... from ... where ... group by ... order by...
**执行顺序**:from,where,group by, select, order by

select name from users where age>min(age); 错误原因: 分组在where后执行,而min是分组函数,必须要先分组才能执行分组函数. 那为什么 select sum(age) from users;可以用? 因为select在group by之后执行,那时候分组已经结束了.(没有显示的写group by默认分为1组).

19.3:
select address as ads ,sum(age) from users group by address;

select address,max(age) from users group by address;

求每个地址中每个性别的最大年龄; group by 后面可以跟多个字段. 同时select后只能加分组字段+分组函数
select address,gender,max(age) from users group by address,gender;

使用having对分完组之后的数据进一步过滤,having不能代替where,只能联合group by使用. (在where里先过滤效率更高一点),优化策略,where和having有限选择where.where实在完成不了再选择having
select address,max(age) from users group by address having max(age)>20;

只能用having过滤不能用where过滤的例子:
select address,avg(age) from users group by address having avg(age)>20;

**以上都是单表查询,单表查询总结**
select ... from ... where ... group by ... having ... order by ...
执行顺序:
from,where,group by, having, select, order by
*大练习*
select gender,avg(age) from users where address<>'beijing' group by gender having avg(age)>20 order by avg(age) desc;

TCL:transaction control language 事物控制语言: commit,rollback
DCL:data control language 数据控制语言: grant, revoke
is null; is not null; in; not in;

**distinct关键字**
查询结果去除重复记录,原表数据不会被修改; 只能出现在所有字段的最前方,表示后面字段联合起来去除重复记录.
select distinct name,age from users;
select count(distinct age) from users;

**连接查询**mysql中最重要内容
2.1从一张表中单独查询,称为单表查询. 从emp表和dept联合查询数据,从emp取员工名字,从dept表中取部门名字,较跨表查询

2.2分类:年代分类:SQL92,SQL99; 分类方式分类:内连接(等值连接,非等值连接,自连接),外连接(左外连接/左连接;右外连接/右连接),全连接(不讲)







##### 0317
p40
找到了一个17个小时[老杜带你学]的(播放量还更多),讲的应该更精简.从今天开始看那个17小时的.
数据处理函数,又称为单行处理函数:
特点:单个输入对应单个输出.对应:多行处理函数.一次处理多条记录.
特点:多少个输入就有多少个输出,一行一行处理
常见的单行处理函数:

lower转换小写:
  select lower(name) **as ename** from users; 

upper转换大写:
  select upper(name) from users;

substr取子串: substr(name,下标,长度) 起始下标从1开始,没有0.
  select substr(address,1,1) from users;
  select * from users where substr(address,1,1)='b';
  首字母大写: **concat** 字符串拼接
    select concat(upper(substr(name,1,1)),substr(name,2,length(name)-1)) from users;

length 取长度: 'elength'别名(别名前可以加as也可以省略)
  select length(name) elength from users;

trim 去除前后空格:
  select * from users where name=trim('    wang');

str_to_date 将字符串转换成日期

format设置千分位

round四舍五入
  select 字段 from 表名;
  select abc from users; 如果是abc报错
  select 'abc' from users; 如果是'abc'字面值,借助表结构返回
  select 1000 from users; 1000被当作字面值
  select round(1234.567,0) from users; //0表示保留整数位
  select round(age,0) from users;

rand()生成随机数
  select rand() from users;
  select round(rand()*100,0) from users; //100以内随机数

ifnull 可以将null转换成一个具体值
ifnull是空处理函数.在所有数据库中,*只要有null参与数学运算,最终结果是null*
  ifnull(数据,被当作哪个值)
  select id, age+ifnull(entrydate,0) from users;

case...when..then..when..then..else..end: 
**as ...:** 起别名
  select name,address, (case address when 'beijing' then age*1.1 when 'shanghai' then age*1.5 else age end) as newage from users;

**分组函数**
多行处理函数:输入多行,输出一行.有5个函数:count,sum,max,min,avg; 详见0315(聚合函数)
分组函数不能直接使用在where子句中. group by可以解释;
分组函数在使用的时候必须先分组再执行.



##### 0316
**DQL语句**
**排序查询** ORDER BY; DESC, ASC
SELECT * FROM users ORDER BY age ASC;
SELECT * FROM users ORDER BY age DESC;

**分页查询** LIMIT
select * from users limit 4,4;  (起始索引,每页展示记录数)

**案例练习**
显示年龄在(17,24,23)中并且gender是男性的信息
select * from users where age in (17,24,23) and gender='male';
选择年龄在20-40并且gender是男性并且名字是三个字的信息
select * from users where age between 20 and 40 and gender='male' and name like '____';
对60岁以下的用户,按年龄分组统计
select gender,count(*) from users where age<60 group by gender;
select name,age from users where age<=30 order by age asc, entrydate desc;
  limit应该在order之后
select * from users where gender='male' and age>=20 and age<=40 order by age asc, entrydate asc limit 5;

**执行顺序**
编写顺序: SELECT...FROM...where...group by...having...order by...limit...

**DCL语句** data contral language

create,alter,drop 出现在DCL(用户管理),DDL(表/数据库管理中).
语法规则是,create user:创建用户, create database:创建数据库, create table:创建表
insert,update,delete 出现在DML(表中具体数据管理)中.和上面有区分.

**用户管理**
查询用户:
use mysql; select host,user from user;
创建用户:
create user 'itcast'@'localhost' identified by '123456';
create user 'heima'@'%' identified by 1231;
修改密码:
alter user 'itcast'@'localhost' identified with mysql_native_password by '1231';
删除用户:
drop user 'itcast'@'localhost';

**权限控制**
查询权限:
show grants for heima@%;
*查询当前所在数据库名: select database();*
授权:
grant all on itcast.\* to 'heima'@'%';
撤销权限:
revoke all on \*.\* from 'heima'@'%';

**第三章节**
**函数**

**字符串函数** CONCAT, LOWER, UPPER, LPAD, RPAD, TRIM, SUBSTRING
连接: select concat('hello','mysql');
小写: select lower('HELLO');
大写: select upper('hello');
左填充: select lpad('01',5,'-');  5为填充到的长度
右填充: select rpad('01',5,'-');
去除空格: select trim('  hello mysql  ');
截取:select substring('hello MySQL',1,5);  索引从1开始,也就是从h开始截
案例:
update users set workno=lpad(workno,5,0);




##### 0315
p18
**DQL语句**数据查询语言,用来查询数据库中表的记录
SELECT ... FROM ... WHERE ... GROUP BY ... HAVING ... ORDER BY ... LIMIT
SELECT ... FROM
检索(起别名): SELECT id AS idd FROM users;
去重检索: SELECT DINSTINCT id FROM users;

sql语句允许通配符 *

条件检索WHERE; 条件运算符:BETWEEN...AND...; IN(...)

**null**是个关键字,意思是空
条件查询中如果查null,要用is而不能用=
select * from users where entrydate is null;

&&<=>and; ||<=>or; in(18,20,40) 只要在查询列表里就会被检索到

模糊匹配: like XXX; _单个字符 %任意字符
select * from users where address like 's%';

**聚合函数** 分组查询(GROUP BY 会依赖聚合函数) (分组函数)
COUNT 统计数量; MAX 最大值; MIN 最小值; AVG 平均值; SUM 求和;
null 值不参与聚合函数的计算;

SELECT sum(age) from users where address in ('beijing');

**分组查询** GROUP BY; where 分组前过滤; having 分组后过滤;
SELECT gender,count(*) FROM users GROUP BY gender;
SELECT gender,avg(age) FROM users GROUP BY gender;
SELECT address, count(*) FROM users WHERE age <30 GROUP BY address HAVING count(*)>=3;




##### 0314
p13

create table test01(id varchar(20),name varchar(20));
查询当前所在数据库名: select database();
查询建表语句: show create table users;

**DML语句**数据操作语言,对**表中的数据记录**进行增,删,改
增:INSERT 删:DELETE 改:UPDATE
**insert:**
INSERT INTO
**给指定字段添加数据** INSERT INTO users(id,name) VALUES ('3', 'wangw');
**给全部字段添加数据** INSERT INTO users VALUES ('1', 'wang');
**批量添加数据** insert into users(id,name) values('1', 'wang'),('2','lisan');

**update** UPDATE biaoming **SET**
修改满足某一条件的字段: UPDATE users SET name='lihua' WHERE id=5;
修改表中所有字段: UPDATE users SET entrydate='2019-12-12';
update users set workno=id;

**delete**
删除满足某一个条件的字段 DELET FROM users WHERE name='lihua';
删除表中所有字段 delete from users;



##### 0313
p9
ALTER TABLE 表明 ADD 子端明 类型

**alter**:表操作DDL,表结构修改 ADD,CHANGE,DROP,RENAME TO
增加表属性: ALTER TABLE user **ADD** nickname varchar(20);
修改表属性: ALTER TABLE user **CHANGE** uname uname varchar(50);

change 的功能包含 modify
DESC user; //查看表中的信息
删除字段(drop): alter table user **DROP** uname;
修改表名: ALTER TABLE user **RENAME TO** emp;

**default**默认值
alter table user add gender varchar(20) DEFAULT='male';

**表操作,删除**
删除表: drop table if exists emp;
删除并重建: truncate table emp; (数据删除,只有表结构)

##### 0306

从今天开始主要根B栈视频学习mysql

###### MySQL概述

语法(mysql概述,SQL,函数,约束),多表查询,事物
数据库管理系统(DBMS) SQL语句操作关系型数据库(为操作关系数据库提供了统一的标准(不关联于某一特定数据库)) SQL:Structured Query Langurage

**MySQL数据库**
**关系型数据库**(RDBMS) 建立在关系模型基础上,由多张**二维表**组成的数据库.每个表都是一个二维表,二维表之间可以通过某些关键词存在关联.**通过表存储数据的数据库就是关系型数据库**.

###### SQL 

SQL通用语法,SQL分类:1.DDL,DML,DQL,DCL
**SQL通用语法**Mysq数据库的SQL语句不区分大小写,关键字建议大写.
**DDL:** Data Definition Language 数据**定义语言**,定义数据库对象
查询所有的数据库`SHOW DATABASES;`, 创建数据库: `CREATE DATABASE itcast [default charset ];` 
CREATE DATABSE if not exists itcast; 删除 drop database

DML: Data Manipulation Language 数据**操作语言**,对表中的数据进行**增删改**

DQL: Data Query Language 数据**查询语言**,用来查询数据库表中的记录

DCL: Data Control Language 数据控制语言,创建数据库用户,控制数据库访问权限





##### 0228

编译调用了mysql头文件的cpp程序需要添加动态链接库:

`g++ try.cpp -o ./try -lmysqlclient`

启动mysql语句 `mysql -uroot -p`

##### 0206

Mysqyl->database->table

##### bug解决

* 1.执行mysql -u root p时 报错'Access denied for XXX':
  mysql未启动,[重启服务器]或者[启动服务器]

  ```shell
  #重启服务器
  systemctl restart mysql
  #启动服务器
  service mysql start
  ```
* 2.配置版本过高,需要重装版本
  这个问题花费了我半天,期间才了不少坑,甚至删除依赖的时候把设置按钮都搞没了.正确的步骤:
  第一步要'彻底'删除电脑中现存的mysql文件.(但是不是万不得已不要自己去对文件夹执行操作,容易bug).参考[链接](https://blog.csdn.net/qq_35459198/article/details/116448966)

  ```shell
  查看MySQL依赖 ： dpkg --list|grep mysql
  
  卸载： sudo apt-get remove mysql-common
  
  卸载： sudo apt-get autoremove --purge mysql-server-8.0(这里版本对应即可)
  
  清除残留数据: dpkg -l|grep ^rc|awk '{print$2}'|sudo xargs dpkg -P
  
  再次查看MySQL的剩余依赖项: dpkg --list|grep mysql(这里一般就没有输出了，如果有执行下一步)
  
  继续删除剩余依赖项，如：sudo apt-get autoremove --purge mysql-apt-config
  ```

  彻底删除的标准是执行 ``dpkg --list|grep mysql``的时候不再显示有已安装文件.但存在的一个问题是删依赖可能会把设置按钮给删除掉.但我尝试过,直接安装设置按钮又会把某些mysql重新下载回来.所以要**等到需要的版本安装完毕**,最后再执行下面两行命令装设置:

  ```shell
  sudo apt-get install unity-control-center
  sudo apt-get install gnome-control-center
  ```

  第二步:安装指定版本的mysql,我安装的是5.7.29.参考[链接](https://blog.csdn.net/colours_starry_sky/article/details/125392755)
  链接汇总的数据库安装顺序有点问题,正确的如下,但其实不知道顺序也没是,因为装不了它只是会报错安装失败,一个一个试也能试出来.

  ```shell
  dpkg -i mysql-common_5.7.29-1ubuntu18.04_amd64.deb
  
  dpkg -i libmysqlclient20_5.7.29-1ubuntu18.04_amd64.deb
  
  dpkg -i libmysqlclient-dev_5.7.29-1ubuntu18.04_amd64.deb
  
  dpkg -i libmysqld-dev_5.7.29-1ubuntu18.04_amd64.deb
  
  dpkg -i mysql-community-source_5.7.29-1ubuntu18.04_amd64.deb
  
  apt-get install libaio1 libtinfo5
  
  dpkg -i mysql-community-client_5.7.29-1ubuntu18.04_amd64.deb
  
  dpkg -i mysql-client_5.7.29-1ubuntu18.04_amd64.deb
  
  apt-get install libmecab2
  
  dpkg -i mysql-community-server_5.7.29-1ubuntu18.04_amd64.deb
  
  dpkg -i mysql-server_5.7.29-1ubuntu18.04_amd64.deb
  ```
* 3.ERROR1698(28000):Access denied for user root@localhost错误解决方法
  第一次启动mysql,root账户没有密码,也不能通过密码进入.此时只能通过sudo权限进入然后修改密码

---

##### MySql日常操作命令

启动mysql:

```shell
mysql -uroot -p
```

查看数据库:

```shell
show databases;
```

数据库

```shell
创建名为test_db的数据库:
create database test_db;
进入test_db数据库:
use test_db;
查看数据库里有多少张表格:
show tables;
```

数据库中的表

```shell
创建名为test01的表,并创建id,name字段:
create table test01(id varchar(20),name varchar(20));
向表中插入数据:
insert into test01 values ("001","wugk1");
从表中删除数据:

查看test01表数据内容:
select * from test01;

查看建表语句:
show create table test01;
查看表结构中的字段
desc test01;
通过表中的某个字段查询符合该字段值的数据:
    test01中id是"001"的数据:
select * from test01 where id="001";
    test01中id是"001"且name是"hufang"的数据:
select * from test01 where id="001" and name="hufang";
    一些可以通过字面意思读懂的语句:
select * from test01 where name like "%hu%" limit 2;
```

对数据库授权

```shell
#授权关键字有:select,insert,update,delete:
grant all on test01.* to identified by "123456";
#刷新权限:
flush privileges;
#导出数据库: (在命令行中)
mysqldump -uroot -p1231 firstdb > firstdb.sql
#删除数据表:
drop table test01;
#导入数据表/库:
source firstdb.sql
```

```shell
查看版本:
SELECT @@VERSION;
展示有关键字的变量:
SHOW VARIABLES LIKE 'validate_password%';
修改全局参数:
set global validate_password.policy=LOW;
创建用户
create user first@'localhost' identified by "123";
修改密码字段长度(最低为4)
set global validate_password.length=4;
修改用户密码
alter user root@localhost identified WITH mysql_native_password by '1231';
```

##### 使用if条件语句编写MySQL备份脚本

```shell
#检测脚本是否正常
sh -n auto_backup_mysql.sh
#定时运行脚本
crontab -e
```

##### MySQL设置UTF-8终极方法及密码破解

UTF-8:在/etc/my.cnf中添加:

```text
[client]
default-character-set=utf8

[mysql]
default-character-set=utf8

[mysqld]
character-set-server=utf8
```

然后重启mysql,之后建立的database都会支持utf8(之前建立的不被影响)

查看端口

```bash
show global variables like 'port';
```

编译Mysql代码的时候要添加动态链接库 `-l mysqlclient`

统计Mysql某个table中的数据数目 `select count(*) from person;`

删除表中所有数据 `truncate table 表名;`

##### 配置Jsoncpp库的踩坑之路

* 1.使vcpkg无法从github中下载文件,只能找对应的网址分别下载
* 2.如果不将vcpkg的目录注册的话(这个应该可以实现,我还不会),需要将vcpkg `/include`和 `/lib`目录下的对应文件移动到 `/usr/include`和 `/usr/local/lib`之中.

当前配置好之后调用jsoncpp的语句变为 `g++ try.cpp -o try -l jsoncpp`

单例模式:

* 懒汉模式:

  * 1.静态局部变量 2.互斥锁 3. callonece?
* 饿汉模式:

  * 访问时不涉及线程创建,不存在安全问题

---

---

---

---

---

---

---

---

---

---

---

---

---

---

---

---

---

---

---

---

---

---

---

---

---

---

---

---
