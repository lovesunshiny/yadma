#ifndef __HEX_DUMP_USER__
#define __HEX_DUMP_USER__



#define USER_EMERG	"<0>"	/* system is unusable			*/
#define USER_ALERT	"<1>"	/* action must be taken immediately	*/
#define USER_CRIT	"<2>"	/* critical conditions			*/
#define USER_ERR	"<3>"	/* error conditions			*/
#define USER_WARNING	"<4>"	/* warning conditions			*/
#define USER_NOTICE	"<5>"	/* normal but significant condition	*/
#define USER_INFO	"<6>"	/* informational			*/
#define USER_DEBUG	"<7>"	/* debug-level messages			*/

/* Use the default kernel loglevel */
#define USER_DEFAULT	"<d>"
/*
 * Annotation for a "continued" line of log printout (only done after a
 * line that had no enclosing \n). Only to be used by core/arch code
 * during early bootup (a continued line is not SMP-safe otherwise).
 */
#define USER_CONT	"<c>"


enum {
	DUMP_PREFIX_NONE,
	DUMP_PREFIX_ADDRESS,
	DUMP_PREFIX_OFFSET
};

extern void hex_dump_to_buffer(const void *buf, int len,
			       int rowsize, int groupsize,
			       char *linebuf, int linebuflen, int ascii);

extern void print_hex_dump(const char *level, const char *prefix_str,
			   int prefix_type, int rowsize, int groupsize,
			   const void *buf, int len, int ascii);

extern void print_hex_dump_bytes(const char *prefix_str, int prefix_type,
				 const void *buf, int len);


#endif
