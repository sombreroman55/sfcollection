/* assert.h
 *
 * Diagnostics header
 */


#undef assert

#ifdef NDEBUG
    #define assert(ignore) ((void)0)
#else
    void __assert(const char* expression, const char* funcName, const char* filename, unsigned int line);
    #define assert(x) ((x) ? (void)0 : __assert(#x, __func__, __FILE__, __LINE__))
#endif

