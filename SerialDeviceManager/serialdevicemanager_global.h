#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SERIALDEVICEMANAGER_LIB)
#  define SERIALDEVICEMANAGER_EXPORT Q_DECL_EXPORT
# else
#  define SERIALDEVICEMANAGER_EXPORT Q_DECL_IMPORT
# endif
#else
# define SERIALDEVICEMANAGER_EXPORT
#endif
