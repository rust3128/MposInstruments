#include "terminals.h"

#define COL_PARAM 6

Terminals::Terminals()
{
    setColParam(COL_PARAM);
}

int Terminals::colParam() const
{
    return m_colParam;
}

void Terminals::setColParam(int colParam)
{
    m_colParam = colParam;
}

int Terminals::isCheked() const
{
    return m_isCheked;
}

void Terminals::setIsCheked(int isCheked)
{
    m_isCheked = isCheked;
}

int Terminals::terminal() const
{
    return m_terminal;
}

void Terminals::setTerminal(int terminal)
{
    m_terminal = terminal;
}

QString Terminals::name() const
{
    return m_name;
}

void Terminals::setName(const QString &name)
{
    m_name = name;
}

QString Terminals::serverName() const
{
    return m_serverName;
}

void Terminals::setServerName(const QString &serverName)
{
    m_serverName = serverName;
}

QString Terminals::database() const
{
    return m_database;
}

void Terminals::setDatabase(const QString &database)
{
    m_database = database;
}

QString Terminals::password() const
{
    return m_password;
}

void Terminals::setPassword(const QString &password)
{
    m_password = password;
}
