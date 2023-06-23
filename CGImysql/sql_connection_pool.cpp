#include <mysql/mysql.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <list>
#include <pthread.h>
#include <iostream>
#include "sql_connection_pool.h"

using namespace std;

connection_pool::connection_pool()
{
	m_CurConn = 0;
	m_FreeConn = 0;
}

connection_pool* connection_pool::GetInstance()
{
	//调用构造函数
	static connection_pool connPool;
	//每次调用静态函数GetInstance都会返回唯一的线程池地址
	return &connPool;
}

//构造初始化
//初始化线程池
void connection_pool::init(string url, string User, string PassWord, string DBName, int Port, int MaxConn, int close_log)
{
	/*m_url:数据库ip地址,本地为'127.0.0.1'
	m_Port:数据库访问端口,默认为3306
	m_User:数据库登陆名,root
	m_PassWord:数据库访问密码,我设置的为1231
	m_DatabaseName:mysql中具体的database名,我设置的为yourdb
	m_close_log:是否关闭日志,1关闭,0打开,默认值:0,打开*/
	m_url = url;
	m_Port = Port;
	m_User = User;
	m_PassWord = PassWord;
	m_DatabaseName = DBName;
	m_close_log = close_log;

	//初始化的时候创建maxconn那么多个连接
	for (int i = 0; i < MaxConn; i++)
	{
		//创建一个MYSQL类型指针,用于储存建立的mysql连接
		MYSQL *con = NULL;
		//初始化连接环境,将分配,初始化并返回新对象,通过 返回的对象 去连接MySQL服务器
		//其实直接传空指针进去也行,这个函数定义就是要接受一个指针变量,输入遍量没有意义
		con = mysql_init(con);

		if (con == NULL)
		{
			LOG_ERROR("MySQL Error");
			exit(1);
		}
		//该函数通过指定的参数,去连接mysql数据库(tcp连接),返回一个可以操作数据库的指针.
		//传入包括网络地址,用户名,密码,数据库名,端口,后两个不用管
		con = mysql_real_connect(con, url.c_str(), User.c_str(), PassWord.c_str(), DBName.c_str(), Port, NULL, 0);

		if (con == NULL)
		{
			LOG_ERROR("MySQL Error");
			exit(1);
		}
		//STL容器中的列表,定义在sql_connection_pool.h中,列表中元素指定为MYSQL*
		connList.push_back(con);
		++m_FreeConn;//每创建一个数据库连接,空闲连接计数+1
	}

	reserve = sem(m_FreeConn);//设置信号量,保证没有数据库链接的时候会阻塞.

	m_MaxConn = m_FreeConn;//这句话不知道有什么意义.
}


//当有请求时，从数据库连接池中返回一个可用连接，更新使用和空闲连接数
MYSQL *connection_pool::GetConnection()
{
	MYSQL *con = NULL;
	//如果链接池列表中没有链接可以取出了,返回空
	if (0 == connList.size())
		return NULL;
	//链接数-1
	reserve.wait();
	//取链接的时候上锁
	lock.lock();
	//取第一个链接,并且pop掉
	con = connList.front();
	connList.pop_front();
	//空闲链接-1,工作链接+1
	--m_FreeConn;
	++m_CurConn;
	//解锁
	lock.unlock();
	return con;
}

//释放当前使用的连接给连接池
bool connection_pool::ReleaseConnection(MYSQL *con)
{
	if (NULL == con)
		return false;

	lock.lock();
	//把线程链接放回连接池里回收
	connList.push_back(con);
	++m_FreeConn;
	--m_CurConn;

	lock.unlock();
	//信号量+1
	reserve.post();
	return true;
}

//销毁数据库连接池
void connection_pool::DestroyPool()
{

	lock.lock();
	if (connList.size() > 0)
	{
		list<MYSQL *>::iterator it;
		for (it = connList.begin(); it != connList.end(); ++it)
		{
			MYSQL *con = *it;
			mysql_close(con);
		}
		m_CurConn = 0;
		m_FreeConn = 0;
		connList.clear();
	}

	lock.unlock();
}

//当前空闲的连接数
int connection_pool::GetFreeConn()
{
	return this->m_FreeConn;
}

connection_pool::~connection_pool()
{
	DestroyPool();
}

/*SQL一个空的指向MYSQL指针的指针
connPool指向数据库连接池的指针
这个函数的目的是从数据库连接池中取一个链接用SQL指向它,一次来访问数据库
*/
connectionRAII::connectionRAII(MYSQL **SQL, connection_pool *connPool){
	*SQL = connPool->GetConnection();
	//记录当前链接和线程池
	conRAII = *SQL;
	poolRAII = connPool;
}

connectionRAII::~connectionRAII(){
	poolRAII->ReleaseConnection(conRAII);
}