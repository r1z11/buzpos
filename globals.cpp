#include "globals.h"
#include "qstring.h"

Globals * Globals::m_pInstance  = NULL;
Globals * Globals::instance() {
      if (!m_pInstance)
          m_pInstance = new Globals();
      return m_pInstance;
}

Globals::Globals() {
   // whatever initialisation code you need to your global vars
}

QString Globals::getUser() {
   return m_user;
}

void Globals::setUser(const QString & str) {
    m_user = str;
}
