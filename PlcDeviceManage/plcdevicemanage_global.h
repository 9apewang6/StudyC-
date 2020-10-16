#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PLCDEVICEMANAGE_LIB)
#  define PLCDEVICEMANAGE_EXPORT Q_DECL_EXPORT
# else
#  define PLCDEVICEMANAGE_EXPORT Q_DECL_IMPORT
# endif
#else
# define PLCDEVICEMANAGE_EXPORT
#endif
