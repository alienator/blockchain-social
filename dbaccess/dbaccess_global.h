#ifndef DBACCESS_GLOBAL_H
#define DBACCESS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DBACCESS_LIBRARY)
#  define DBACCESSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DBACCESSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DBACCESS_GLOBAL_H
