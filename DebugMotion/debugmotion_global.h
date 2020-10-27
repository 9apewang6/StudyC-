#pragma once

#include <QtCore/qglobal.h>
#include <QtWidgets/QWidget>
#ifndef BUILD_STATIC
# if defined(DEBUGMOTION_LIB)
#  define DEBUGMOTION_EXPORT Q_DECL_EXPORT
# else
#  define DEBUGMOTION_EXPORT Q_DECL_IMPORT
# endif
#else
# define DEBUGMOTION_EXPORT
#endif
extern "C"
{
    DEBUGMOTION_EXPORT QWidget* createDebugMotionWidget();

}