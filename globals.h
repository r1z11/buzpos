#ifndef GLOBALS_H
#define GLOBALS_H
#include "qstring.h"

class Globals {
protected:
    static Globals * m_pInstance;

public:

    //Globals * instance();
    static Globals * instance();

    // your global setters/getter

    QString  getUser();
    void setUser(const QString & str);

protected:

    QString m_user;

private:
    Globals();
};

#endif // GLOBALS_H
