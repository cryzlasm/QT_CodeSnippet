> 一个Sqlite的辅助类, 简化数据库操作
``` C++
#include <QSqlDatabase>

#ifndef BOOL
#define BOOL    int
#define TRUE    (1)
#define FALSE   (0)
#endif

class SqliteHelper
{
public:
    // 构造指定 数据库路径
    SqliteHelper(QString db_path)
    {
        this->db_path = db_path;
        this->opencase = false;
        this->conn = QSqlDatabase::addDatabase("QSQLITE");
        this->conn.setDatabaseName(this->db_path);
    }
 
    // 打开数据库, 返回状态
    BOOL open()
    {
        this->opencase = this->conn.open();
        return this->opencase;
    }
 
    QSqlQuery query(QString strSQL)
    {
        QSqlQuery rs(this->conn);
        rs.exec(strSQL);
        return rs;
    }
 
    void execute(QString strSQL)
    {
        QSqlQuery rs;
        rs.exec(strSQL);
    }
 
    QStringList dbTable()
    {
        this->tables = this->conn.tables(QSql::Tables);
        return this->tables;
    }
 
    void close()
    {
        opencase = false;
        this->conn.close();
    }
 
    BOOL getOpenSign()
    {
        if(this->opencase == true)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
 
private:
    BOOL opencase;      // 数据库链接状态
 
    QString db_path;    // 数据库物理地址
    QString strconn;    // 数据库链接字段
 
    QSqlDatabase conn;  // 数据库链接对象
 
    QStringList tables; // 数据库中的表
};
```