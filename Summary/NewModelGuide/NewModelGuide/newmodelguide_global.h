#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NEWMODELGUIDE_LIB)
#  define NEWMODELGUIDE_API Q_DECL_EXPORT
# else
#  define NEWMODELGUIDE_API Q_DECL_IMPORT
# endif
#else
# define NEWMODELGUIDE_API
#endif

extern "C"
{
    NEWMODELGUIDE_API QWidget* createNewModelGuideWidget();
    
}