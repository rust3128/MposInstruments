#ifndef TERMINALS_H
#define TERMINALS_H
#include <QString>

class Terminals
{
public:
    Terminals();
    int colParam() const;
    void setColParam(int colParam);

    int isCheked() const;
    void setIsCheked(int isCheked);


    int terminal() const;
    void setTerminal(int terminal);

    QString name() const;
    void setName(const QString &name);

    QString serverName() const;
    void setServerName(const QString &serverName);

    QString database() const;
    void setDatabase(const QString &database);

    QString password() const;
    void setPassword(const QString &password);

private:
    int m_colParam;
    int m_isCheked;
    int m_terminal;
    QString m_name;
    QString m_serverName;
    QString m_database;
    QString m_password;
};

#endif // TERMINALS_H
