/* Developped by 
 *	Arthur Carvalho Walraven,
 *	Paulo Bruno de Sousa Serafim,
 *	2014-2015. Used with permission.
 */
 
#ifndef PB_LOG_H
#define PB_LOG_H


#include <iostream>


#define LOGS

#define ERRORS
//#define WARNINGS

#define DEBUG


#ifdef LOGS
    #define SIZE_PATH   0  // Nao exibe os SIZE_PATH primeiros caracteres de __FILE__.

    #define WHERE   &__FILE__[SIZE_PATH] << "->" << __FUNCTION__ << ':' << __LINE__ << " - "

    #define LOG(str)                        \
    {                                       \
        std::cout << WHERE << str << ".\n"; \
    }

	#ifdef ERRORS
		#define LOGerr(str)\
		{                                       				\
		    std::cerr << WHERE << "ERROR:\n " <<str << ".\n\n"; \
		}
	#else
		#define LOGerr(str)
	#endif // ERRORS
    
    #ifdef WARNINGS
		#define LOGwar(str)\
		{														 \
		    std::cerr << WHERE << "WARNING:\n " << str << ".\n\n"; \
		}
	#else
		#define LOGwar(str)
	#endif // WARNINGS

    #ifdef DEBUG
        #define LOGdbg(str) LOG(str)
    #else
        #define LOGdbg(str)
    #endif // DEBUG
#else
    #define LOG(str)
    #define LOGerr(str)
    #define LOGdbg(str)
#endif // LOGS


#endif // PB_LOG_H
