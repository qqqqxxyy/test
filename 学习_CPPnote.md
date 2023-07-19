cpp视频: 42-43,47,50-51,61, 84-85,106-119,126-131,135-140, 167-184
第9周期目标223-243
##### 07_16
复习格式化输入输出：直接读取一行数据：第三题-游游刷题
//这是最常用的情况
复习优先队列自定义变量的写法：
arr={1,5,4,2,7,3,9,3}
[X]1.用一个vector从小到大排序(最基本的)
[X]2.vector进行从大到小排序
greater<int>(); <or> reverse();


3.给定一个node元素，里面有val值，按照val值的从小到大排序
3.1优先队列，再cmp类中重载()
```cpp
class node{
public:
    string name;
    int val;
    node(int v):val(v){}
    node():val(0){}
};
class cmp{
public:
    bool operator()(node&a,node&b){
        return a.val>b.val;
    }
};
int main(){
    vector<node>arr={1,5,4,2,7,3,9,3};
    priority_queue<node,vector<node>,cmp>que;
}
```
3.2优先队列，重载node 比较操作符解
```cpp
class node{
public:
    string name;
    int val;
    node(int v):val(v){}
    node():val(0){}
    bool operator<(const node & a)const{
        return val>a.val;
    }
};
int main(){
    vector<node>arr={1,5,4,2,7,3,9,3};
    priority_queue<node,vector<node>>que;
}
```
3.2.5自定义compare函数
```cpp
priority_queue<node,vector<node>,bool(*)(node& ,node&)>que(cmp);
或者
priority_queue<node,vector<node>,decltype(&node)>que(cmp);
```
本质是先把函数类型传进去，然后再在外面传函数指针
3.3vector，重载node比较操作符 <,(若从大到小,无法再使用greater,只能reverse或者反向定义operater<)(只能定义<才有效)
3.4vector，定义compare函数比较操作符解, bool compare(node & a,node & b){  return a.val<b.val;  }


priority_queue初始化的时候用less<int>初始化，sort进行排序的时候用less<int>()进行排序，一个是类，以格式实例。

##### 07_08
ret.push_back(dp[i] * 1.0 / all); int转double
isalpha(char) ;查看输入的字符数组是不是字母(也就是a-z;A-Z;之间的一个)
##### 07_06
灵活使用一下函数可以应对各种参数读取情景：
1. cin>>；自动跳过' ','\n';如果输入流中没有数据，返回false；
配合while(cin>>m);可以一次读取，把输入数据流都完
2. cin.get()读取下一个字符，不跳过空格和换行
3. getline(cin,line,'\n');一行一行读取数据
配合istringstream()把line转成输入流，可以先一行一行读取，在读取行中的元素。
注意：如果line前面还有数据是通过换行符区分的话，以为换行符没有被读取，当前读会读空。解决方法：先getline一次或者cin.get()一次；
使用情况，每行不知道读取多少个元素的情况。

##### 07_05
**vector从大到小排序**
1.使用内置greater
sort(arr.begin(),arr.end(),greater<int>());
2.自定义compare函数
```cpp
bool compare(int&a,int&b){
    return a>b;
}
int main() {
    vector<int>arr={1,5,3,9,1,9,9,6};
    sort(arr.begin(),arr.end(),compare);}
```
**priority_queue从大到小排序**
vector<int>tmp={1,5,3,9,1,9,9,6};
priority_queue<int,vector<int>,less<int>>arr(tmp.begin(),tmp.end());
priority_queue自定义函数做比较函数比较麻烦，要写类，又因为使用priority往往是自定义类型的场合，所以建议在类中自定义<来作比较



##### 07_02
可以使用n={xxx,yyy}的初始化列表方法对类、结构体赋值

##### 06_24
deque: 没有reserve函数
vector/deque的相关操作:
size(),front(),back(); push_back(),push_fron(),pop_back(),pop_front();
empty();
迭代器:
begin(),end();

对:make_heap; push_heap; pop_heap; pop_back();

两个迭代器拼接:
a.insert(a.end(),b.begin()+3,b.end());
指针和数组的相同和不同:
    我之前一直以为指针和数组完全一样.没想到还是有区别的;
    相同点: 指针和数组都可以通过a[i],访问第i个下标的元素
    不同点: (取地址,大小计算)对数组取地址,得到的是数组首元素地址,对指针取地址,得到的是指针地址.sizeof(数组名)计算的是整个数组大小.而sizeof指针名则得到的是指针大小(8); (初始化),数组可以通过{1,2,3}的方式进行初始化.而指针不行,int指针只能通过一个int元素的地址进行初始化.
int a[100]和vector<int>的不同:
    不同点很多,一个最近才意识到的不同点是,a[100]不支持=赋值,只能一个元素一个元素的改.

##### 06_20
shared_ptr:
指针资源的痛点：1.已释放的内存资源，指针没有改变，后续还在使用。2.已释放的内存资源，因为指针的存在后期又试图再次释放。3.内存不及时释放，但指针被销毁，造成内存泄露
**解决逻辑：**储存动态创建对象的指针，管理动态创建对象的销毁，从而帮助彻底消除内存泄漏和悬空指针的问题。
**基本原理：**记录对象被引用的次数，当引用次数为0的时候，也就是最后一个指向改对象的共享指针析构的时候，共享指针的析构函数就把指向的内存区域释放掉。（自动释放内存）。

重要函数：
=make_shared<T>(value);通过这个方法赋值；
get() 返回当前存储的指针
use_count() 获取当前的引用计数
reset() 重置当前的指针；



##### 06_14
vector返回首元素/末尾元素
vec.front()
vec.back()
指针可以作为cpp unorderedmap的哈希键

##### 06_13
对vector b赋予a的一个子数组的值:(归并排序用到了)
b.assign(a.begin()+2,a.begin()+5);
对b的一个子数组赋予a的值
copy(iterator beg, iterator end, iterator dest);
insert

##### 06_11
字符串操作:
从字符串中取想要的字串
int pos = str.find('@');
//find()返回的不是int类型的变量,但可以用int()进行强制转换,转换后如果找不到会返回为-1;
string subops = str.substr(0,pos);
new 之后返回的是一个地址.

##### 06_06
```cpp
对二维vector的初始化：
vector<vector<int>>b(5,vector<int>(5,0));
```
##### 06_05
vector
vector<int> vec; vector<int> vec={1,2,3}; vec.push_back(8); vec.pop_back(9);
#define vit vector<int>
//对于越界访问,不会报错,但会访问到非法的内存地址.

unordered_map
map.insert({4,5});和map.insert(pari<int,int>{4,5})效果一样,但推荐用前一种,因为前一种可以一次insert多个;
//对于查找元素在不在map中,建议使用count,因为count返回的是数字,更好操作;

迭代器的使用,对于有序容器,可以使用reverse,sort对容器进行排序;

在做这道题的时候:
剑指 Offer 12. 矩阵中的路径;发现用pair不能做哈希的键值,原因也很好理解,pair内容可以修改.而且pair有很多局限性,例如只能接受二元组.
换成tuple
##### 06_04
cpp递归写法技巧：

##### 06_03
vector初始化:
2.初始化开辟一个规模为n每个元为0个vector
`vit arr2(n,0);`
3.用数组arr初始化
`vit arr2=arr1;`

'for(declaration: expression)'
右边是一个可便利对象，可以通过此种方式，进行遍历
push_back,insert的区别，push_back在最后插入，面向有序容器，insert面向无序容器（unordered_set/map）;erase和pop同理

vector
```cpp
/*
声明： vector<int> v;
0.初始化：
v(n,elem);
vector<int>v={1,2,3};
1.预留空间
v.reserve(100000);
2.尾插：
v.push_back(1);
3.尾删
v.pop_back();
4.方问
* `at(int idx); `     //返回索引idx所指的数据
* `operator[]; `       //返回索引idx所指的数据
* `front(); `            //返回容器中第一个数据元素
* `back();`              //返回容器中最后一个数据元素
*/
```
C11哈希表：
unordered_map 
```cpp
/*格式：
构造，支持默认构造和拷贝构造
unordered_map <key-type,value-type>map
插入 map.insert({..,..});
查找：1.操作符[]
['key'],返回该键值所对应的值的引用，如果key不在，则在map中注册key，值设为0;
find 返回一个常量迭代器，如果找不到返回end
删除：map.erase('b');
*/
```


##### 04_25
关联是容器.插入排序.关联式容器.
set 不允许重复, multiset 允许重复
构造:默认,拷贝 赋值:=赋值

**插入**: `insert`
set 特点:所有元素插入时会自动排序.
拷贝构造两种写法:
`set<int>s2=s1;`  `set<int>s2(s1);`
赋值操作:
`s2=s1;`

**大小和交换** size(),empty(),swap()
s1.swap(s2),交换两个容器中的元素.

##### 04_19
[坑].全局变量如果在递归函数中不被初始化的话,可能会产生脏数据问题.
clear()可以用O1的时间初始化.

vector初始化:
2.初始化开辟一个规模为n每个元为0个vector
`vit arr2(n,0);`
3.用数组arr初始化
`vit arr2=arr1;`
4.用数组arr的一个子集初始化
`vit arr2(arr1.begin(),arr1.begin()+2);`
5.在末尾插入一个指定的部分
`arr2.insert(arr2.end(),{7,8,9});`
6.指定部分替换
`copy(arr3.begin(),arr3.end(),arr2.begin()+1);`

vector.reserve() 预留一部分空间, vector.clear()数据清理;
这两个语句配合使用可以解决递归函数中修改同一个数组的时间慢或脏数据问题.
##### 04_18
字符串取子串: s.substr(st,ed)
##### 04_17
[坑].仅限于力扣题目.对力扣来说,似乎在测试用例的时候,定义在全局区的变量有可能不会被释放.也就是如果上一个用例定义了一个数组,下一个用例数组可能不会被重新初始化.这就导致如果要定义数组这种类型,最好还是在类内定义.
[坑].for循环迭代的坑.对于使用for(int i:vec)这种结构迭代,即是在外部预先定义好了i的类型并且类型正确,也会报错.必须要在括号内部重新指定局部变量才可以.

##### 04_16
[坑].vector初始化的坑:对于vector当作数组的声明,最方便的当然是`vector<int> prevec(10000,5);`这种一开始先开辟好并初始化的声明.但是这种声明不能用在类里面,类中分不清这是一个参数声明还是一个函数定义.所以在类中只能使用`vector<int> prevec = vector<int>(10000,5);`这种定义方式.

##### 04_12
引用做函数返回值的时候,不要返回局部变量,因为函数接不会管你的变量还被不被指向都会释放那块内存空间.
如果想左到上述效果,可以在函数内部声明静态变量,静态变量不会随着函数运行结束而释放
##### 04_11
两个指针相等意思是两个指针所储存的地址是相等的;
```cpp
int *a,*b,c;
c=1;a=&c;b=&c;
/*a=b=>a和b指向的同一块地值,而不是a和b的地址一样.其实
逻辑和正常变量一样.两个变量相等指的是两个变量的值相等,而不是两个变量的地址相等.
而指针类型的变量的值,就是其所储存的地址*/
```
和int*指针一样,结构体指针只能指向一个已经声明好了的结构体,不能通过结构体指针构造函数.
\*的优先级要小于.,因此用\*取值的话要加括号.(`(*p).val`)才是取p指针所指向结构体的值,要加星号.
unordered_map
```cpp
//以int,int为例
//声明
unordered_map<int,int>hmap;
//添加元素方式1.insert显示添加
hmap.insert(pair<int,int>(1,0));
//更方便的添方式
hmap[1]=0;
//上面两种方式的是,insert不会刷新,而数组添加的方式会刷新
//键值一样的的话不会出现两个
//查找元素是否存在map中:
hmap.count(1);
```

vector
```cpp
//下列语句可以让迭代器指向想指的位置
vec.begin()+2
//向指定位置插入数据
vec.insert(vec.begin()+2,100 );
//向指定位置删除数据
vec.erase(vec.end()-1);
```
##### 04_10
?:属于3目运算符, 运算符返回的值类型应该一致.
```cpp
/*线段树
意义: 可以以logn的复杂度修改数列,同时以logn的复杂度查询数列中任意长度串的和
sum[]数组代表线段树的数据结构,sum[]数组只存储其段的和,所以每次查找删除都要递归的找
一言以蔽之,线段树算是递归算法应用的大成数据结构
*/
//建树 递归
void build(int k, int l, int r)//k当前节点 ,[l,r]为当前区间
{
    if(l==r){sum[k]=a[l];return;}
    int mid=(l+r)>>1;
    build(k*2,l,mid);
    build(k*2+1,mid+1,r);
    //当前段的值永远可以用左右子树的值之和表达出来
    sum[k]=sum[k*2]+sum[k*2+1];
    return;
}
//单点查询
int find(int k, int l, int r, int x)//k当前节点, [l,r]为当前区间,x为目标节点
{
    if(l==r) return sum[k];
    int mid = (l+r)>>1;
    if (x<=mid) return find(k*2,l,mid,x); //左子树继续找
    else return find(k*2+1,l,mid+1,x);
}
//单点修改
void modified(int k, int l, int r, int x)
{
    sum[k]+=x;
    if (l==r) return;
    int mid = (l+r)>>1;
    if (x<=mid) modifies(k*2,l,mid,x);
    else modifies(k*2+1,mid+1,r,x);
}
//区间查询 
int find(int k,int l,int r, int x,int y)//k当前节点,[l,r]为当前区间,[x,y]为搜索区间
{
    if (l<=x and r>=y) return sum[k];//[这句判断很重要,不然查找会退化成ON]
    int mid = (l+r)>>1;
    int res=0;
    //有在左子树的部分,就从左子树加,因为线段树保证递归搜索不会有重复元
    if (x<=mid) res+=find(k*2,l,mid,x,y);
    if (y>mid) res+=find(k*2+1,l,mid,x,y); 
    return res;
}
```


##### 04_07
多态:
[坑].只有当父类的引用或者指针指向子类对象的时候,多态才会发生; 拷贝构造不会发生多态,父类仍然会调用父类的函数.

```cpp
//优先队列的定义
struct compare{
    bool operator()(const int a,const int b){
        return a<b;}};
void test01(){
    priority_queue<int,vector<int>,compare >q;
    q.push(1);
    q.push(300);
    q.push(20);
    while(q.empty()==false){
        cout<<q.top()<<" ";
        q.pop();
    }cout<<endl;
}

优先队列常用函数:
void pop() //删除队头元素,没有返回值
```
emplace():原地创造一个元素并插入队列;
任务
[X]1.写一个优先队列从小到大输出元素
[X]2.写一个优先队列从大到小输出元素
3.写一个优先队列,直接从一个vector<int>中读入元素,然后从小到大输出元素
4.写一个类,有name,age,写一个优先队列,按照age输出类实例
自定义类的编写:
1.在类外定义struct代替comparsion函数:好处是不局限于自定义类,pari或者int想自定义比较方法都可以
2.在类内定义友元operator <

```cpp
push,pop,size,emplace
empty(): 0非空, 1空
//仅有初始化的时候可以这么做;
priority_queue<int,vector<int>,greater<int> >pq(a.begin(),a.end());
struct cmp1{bool operator()(Person&a, Person&b){return a.age>b.age;}};
```

##### 04_06
对于string类型:
通过,append,+,+=,=,compare,size() 可完全代替👇操作;

这些都是C语言的字符数组操作函数,不能作用在C++ STL的string上,而且比较简陋;
strcpy(char * d,char * c):将c中的字符拷贝到d中; 
strcat(char * d,char * c):将c中字符追加到d的结尾; 
strcmp(char * d,char * c); 比较d,c字典序的大小.
strlen(char * c):统计c中的字符个数,遇到\0返回; 
strstr(char * c, char b):返回c首次出现b之后的字符串


**多态**: *静态多态*:函数重载,运算符重载; *动态多态*(一般所指的多态):派生类和虚函数实现运行时多态
静态多态:编译时确定函数地址, 动态多态:运行时确定函数地址
虚函数 virtual:实现动态多态- *地址晚绑定* 
使用场景: 子类继承父类,调用的时候,希望执行子类的重载函数.父类定义的时候要用虚函数(virtual)
动态多态满足条件:
1.有继承关系; 2.子类*重写*父类的虚函数(重写!=重载,重写函数和原函数(返回值,名称,参数列表)要完全相同);
动态多态的使用场景:
1.**父类的指针或者引用**指向子类的对象
[坑].只有当父类的引用或者指针指向子类对象的时候,多态才会发生; 拷贝构造不会发生多态,父类仍然会调用父类的函数.

**多态底层原理**:
当子类重写父类虚函数的时候: 子类中的虚函数表内部会替换成子类的函数地址;子类的虚函数表内部会变成子类的虚函数地址.
&Animal::speak => &Cat::speak
当父类的指针或者引用指向子类的对象的时候,就发生了多态

对于多态的个人理解:
1.父类引用向子类对象:
  一个更广泛的说法是:基础类的指针指向一个派生类的对象:
    语法逻辑便是:忽略所有派生类中的类型定义/重写,只能访问基础类定义的成员函数和变量
所以虚函数的出现巧妙绕过了这一点.虚函数的地址通过虚函数指针指向虚函数表访问,而子类和父类的虚函数指针名一样,指向的虚函数表可以不一样.所以表面上使用的是父类的指针,但实际上指向了子类的虚函数表. (但正常指针又不会有这种效果,因为指针类变量仍然存在栈空间之中)

---
纯虚函数和抽象类:
纯虚函数: virtual 返回值类型 函数名 (参数列表) = 0;
virtual void func() = 0;//纯虚函数 单纯为了占个名,扩展
抽象类:拥有纯虚函数的类称为抽象类;

对于纯虚函数的继承,子类必须重写纯虚函数,否则无法实例化.

---
**虚析构与纯虚析构**
父类析构函数无法delete在子类中new出来的变量.
纯虚析构:变成抽象类
虚析构:对父类(基类)中析构函数加virtual,析构函数会走子类
纯虚析构:纯虚析构必须有具体实现(函数外)
note:只有要解决多态时子类析构代码调不到的问题才会使用到虚析构.


###### 04_05
vector/deque的相关操作:
size(),front(),back(); push_back(),push_fron(),pop_back(),pop_front();
empty();
迭代器:
begin(),end();

对:make_heap; push_heap; pop_heap; pop_back();

两个迭代器拼接:
a.insert(a.end(),b.begin()+3,b.end());
指针和数组的相同和不同:
    我之前一直以为指针和数组完全一样.没想到还是有区别的;
    相同点: 指针和数组都可以通过a[i],访问第i个下标的元素
    不同点: (取地址,大小计算)对数组取地址,得到的是数组首元素地址,对指针取地址,得到的是指针地址.sizeof(数组名)计算的是整个数组大小.而sizeof指针名则得到的是指针大小(8); (初始化),数组可以通过{1,2,3}的方式进行初始化.而指针不行,int指针只能通过一个int元素的地址进行初始化.
int a[100]和vector<int>的不同:
    不同点很多,一个最近才意识到的不同点是,a[100]不支持=赋值,只能一个元素一个元素的改.


###### 04_04
**算法题相关:**
vector很方便的初始化方式: 
vector< vector<int> > arr={{1,2,3},{4,5,6}};


185-189
目标:hashmap,deque,list,set; undordered map, set...

迭代器: 现在可以当指针来用
[插曲].回调函数和函数指针
函数指针的定义: 返回值类型 * 函数名 (传入参数); 另,和数组一样,函数名也有函数地地址的意义.因此下列语句合法:
int (\*p) (int,int); p = &Max ; 其中max是一个返回值为int的函数; 因此,把函数名传进其他函数中去,实际上传递的就是函数指针了. (也就是说Max和&Max的等效的)
[坑]. 函数指针作为回调函数的时候,编译器会自动把 void handler(void p ())中解释成指针类型,因此如果再加一个\*就是指针的指针了.所以想要加\*的话,括号不能省略. 即void handler(void (\*p) ())<=>void handler(void p ()) 这种写法仅限于函数调用,在程序中声明函数指针的\*不能被省略

> \*cb_func是一个函数指针,这里是定义了一个cb_func的函数指针,指针的地址是函数
> 为的是后面定义某些回调函数的时候,把cb_func作为参数传进去
> 函数回调:在函数中调用函数的做法
> 回调函数:在函数中被调用的函数.在这个定义下,\*cb_func确实是一个回调函数
> 回调函数的实参可以在调用函数外部作为参数传递进去也可以在调用函数内部定义
[插曲].取类构造函数地址报错: &Person("lihua",101); 左值无法取地址.

STL容器之:string
本质:string是C++风格字符串,本质是一个类
string 的构造函数:
const char * p = "hello";
string s1 = p;
string s2;
string s3(10,'a');
string常用的函数:
s1.insert(s1.length(),"1");  s1.length();  s1+="wo"<=>s1.append("wo");  
s1.find("woo")<<\endl;  s1.insert(4,"WWW");  s1.replace(4,1,"MMM");


###### 04_03
早上:
先:根据腾讯面试整理八股;整理八股
后:集中背操作系统的内容(腾讯考了几道基础的都没答上来)
最后:看CPP视频.

类模板成员函数份文件编写:1.直接包含源文件(一般不这么做) 2.第二种解决方式,.h和.cpp写到一起,改为hpp文件

类模板和友元:
[插曲:].友元关键字: friend
全局函数做友元:在类种任意位置以friend关键字声明函数,类允许该函数访问类的时候,访问私有/保护变量.
全局函数可以在类内定义也可以在类外定义,
类做友元:同理; 关键字: friend class XXX(类名);
成员函数做友元: 指定某个类中的特定成员函数是友元.

[插曲:].全局函数. C++没有局部函数这个概念.也不支持函数内定义函数(和python最大的不同). 同时对函数定义对调用有影响.先定义的函数没法调用后定义的函数,除非预先声明.因此'局部函数'是个违命题.除非指的是成员函数.

类内用friend声明的'全局函数',如果没有在类外定义而是在类内定义的话.可见域只有类内.除非传入参数是p(这个时候编译器可能会自动查看类p中的友元函数)
全局函数类外实现比较复杂,首先要让全局函数在类前面,同时又要在函数前面指定模板类(不然函数也识别不了类);较为简单的做法是类内实现;

类模板与继承: 1.继承类模板要指定<参数列表>  2.或者仍然用模板继承,但这样无法访问子类中的成员变量.
[插曲]. 子类和父类拥有同名成员函数,子类会隐藏父类中的所有版本相同的成员函数.在实例化对象中,通过加作用域的父哪个是可以访问户类中的成员函数.

类模板函数的类外实现;

[插曲].new,delete调用;对于指针类型, int * a = new(10); delete a; 对于指针数组类型: int * a = new[10]; delete [] a;
[插曲]. new相比于malloc的优越性: 对于自定义数据类型(自定义的类),new可以调用其构造函数,delete可以调用其析构函数. 而malloc则不行. 注意:new和malloc都可以对模板类进行初始化.因为在程序执行过程,申请内存时,模板类T已经有明确的定义了. 在C++环境中,用new准没错.

[插曲]C++异常退出值令: throw "words";


###### 04_02
上午,继续看函数模板的视频. 看完整理腾讯面试的问题;整理到八股之中; 下午继续看C++的视频; 查资料看各个地方的实习截至日期;
43, 61, 126, 173-179
仿函数: 重载类的'()'运算符,使用起来像一个函数;
lambda表达式: 底层实现是仿函数,但是是匿名的; lambda表达式和仿函数的差异: lambda表达式定义更方便,但不支持模板和重载. 仿函数支持模板和重载.

数组名不可以进行赋值: 数组名理解为指针常量,指针内部的地址值不可以修改.
对类模板重载以应对自定义数据类型之间的比较.
具体化 :template <> 函数名; 具体化的一个模板; 具体化模板优先级比普通函数低(在本案例中功能一样)
模板,可以指定多个不同的变量类型,eg template<typename T1, typename T2>
类模板
[插曲],this指针
用途:this指针指向被调用的成员函数所属的**对象**(指的是类对象),用于使成员函数区分当前调用是哪个对象来进行的.
this指针和静态方法之间的关系:
类中非静态方法默认有this指针.当类成员变量和传入参数重名时,只有用this才能指定修改成员变量.否则默认修改传入参数. 静态方法:实例化和非实例化的类型都可以调用静态方法.但是即使是实例化的类型,也无法在静态方法中使用this指针.静态方法只能访问静态成员函数.

静态成员变量: static int m_A; 静态成员变量必须类内声明类外初始化. 同时可以被 静态 或者 非静态 成员函数访问或者修改.
但静态成员函数,只能访问静态成员变量.
[插曲结束].
类模板:1.参数化列表不能省略.(类模板没有 自动类型推导 的使用方式) 2.类模板可以有默认参数;但即是类模板所有参数都有默认参数,也至少要声明一个空的参数列表.

类模板的成员函数,一开始不会创建,被调用的时候才会被创建.

类模板对象做函数参数.
[插曲] typeid(T1).name() 查看参数T1的数据类型
1.指定传入参数 (普通函数调用类模板); 2.参数模板化(函数模板) 3.整个类模板化(函数模板)



###### 04_01
42,47, 167-172
泛型编程,STL技术
函数模板, 类模板
int & a: 引用.

template<typename T>
void mySwap(T&a, T&b){
    T tmp;
    tmp = a;
    a = b;
    b = tmp;
    return ;
}
/*1.自动类型推导
mySwap(a,b);
2.指定数据类型
mySwap<int>(a,b);
*/

注意事项:
1.自动类型推导,必须推导出一致T数据.
2.模板必须要确定T的数据类型,才可以使用.

数组定义三种方式:
int arr[5];
int arr[5] = {1,2,3,4,5};
int arr[] =  {1,2,3,4,5}
[插曲], char a[5]="abcd"只能输入四个字符,因为最后一个字符会添加上\0;
    这是因为字符串"abcd"会添加一个\0;如果是{'a','b','c','d'}这种赋值则不会出现上述问题.

普通函数和函数模板的区别: 隐式类型转换; 普通函数支持隐士类型转换; 
模板函数,自动类型推导不支持转换,
指定数据类型支持.

1.普通函数和函数模板重名且都可以调用,优先调用普通函数;
2.可以通过 空模板参数列表 强值调用模板函数.
3.函数模板可以重载
4.如果函数可以产生更好的匹配,优先使用函数模板.
