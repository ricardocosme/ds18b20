#pragma once

#if (__cplusplus >= 201402L)
#define DS18B20_CONSTEXPR_CTOR constexpr
#else
#define DS18B20_CONSTEXPR_CTOR 
#endif

#define DS18B20_DECLTYPE_AUTO_RETURN(...)                        \
    -> decltype(__VA_ARGS__)                                    \
    { return (__VA_ARGS__); }                                   
    
