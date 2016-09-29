#ifndef _DBUS_XML_PARSE_H_
#define _DBUS_XML_PARSE_H_

#include <glib.h>
#include <list.h>
#include "dbus_log.h"
#include <dbus/dbus.h>
#include <gio/gio.h> 
//#define DEBUG 1

#if DEBUG
#define debug(fmt, args...) printf(fmt, ##args)
#else
#define debug(fmt, args...)
#endif

//#define dbus_printf(fmt, args...) printf(fmt, ##args)
typedef enum {
	TEST_OK 			= 0x00000000,
	NO_INTERFACE 			= 0x00000001,
	NEW_INTERFACE 			= 0x00000002,
	NO_PROPERTY 			= 0x00000004,
	PROPERTY_WRONG_TYPE 		= 0x00000008,
	PROPERTY_WRONG_ACCESS 			= 0x00000010,
	PROPERTY_WRONG_NOTIFICATION 		= 0x00000020,
	PROPERTY_GET_SET_TIMEOUT 		= 0x00000040,
	PROPERTY_CANT_GET_OR_GETALL 		= 0x00000080,
	PROPERTY_CANT_SET_OR_SETMULTI 		= 0x00000100,
	NULL_OBJECT_BY_METHOD_CALL 	= 0x00000200,
	PROPERTY_SET_GET_NOT_EQUAL 	= 0x00000400,
	PROPERTY_WRONG_NAME 		= 0x00000800,
	NEW_PROPERTY 		= 0x00001000,
	NEW_METHOD 		= 0x00002000,
	NO_METHOD 		= 0x00004000,
	NO_METHOD_ARG 		= 0x00008000,
	NEW_METHOD_ARG 			= 0x00010000,
	METHOD_CANT_CALL 		= 0x00020000,
	NO_SIGNAL_ARG 			= 0x00040000,
	NEW_SIGNAL_ARG 			= 0x00080000,

	NO_RECIVE_SIGNAL		= 0x00100000,
	NULL_PARAM	 		= 0x00200000,
	NO_SIGNAL 			= 0x00400000,
	PROPERTY_SETMUL_GETALL_TIMEOUT 	= 0x00800000,

	METHOD_CALL_FAIL 		= 0x01000000,
	METHOD_CALL_TIMEOUT 		= 0x02000000,
	RANGE_ERROR			= 0x04000000,
	METHOD_ARG_NO_VALUE		= 0x08000000,
	PROPERTY_NO_VALUE		= 0x10000000,
	CONNECTION_CLOSED		= 0x20000000,
	CONNECTION_NULL			= 0x40000000,
	UNPASS			=0x80000000
} test_result_status_t;


typedef struct {
	gchar * str1;
	gchar * str2;
}DevInfo_t;

typedef struct {
	void * str_mem_block;
	DevInfo_t *devInfo_p;
}DevInfoarray_t;

typedef struct {
	void * str_mem_block;
	char ** str_arry_p;
	guint32 str_count;
}str_array_t;

typedef union dbus_variant_val {
	gchar * path_str;
	str_array_t str_array;
	DevInfoarray_t devInfo;
	guchar byte_v;
	gboolean bool_v;
	gint16 int16_v;
	guint16 uint16_v;
	gint32 int32_v;
	gint32 handle_v;
	guint32 uint32_v;
	gint64 int64_v;
	guint64 uint64_v;
	gdouble double_v;
} dbus_variant_val_t;


struct dbus_method_arg{
	char *name;
	char  type[16];
	char  direction[4];
	dbus_variant_val_t value;
	dbus_variant_val_t value2;
	dbus_variant_val_t value_bad;
	bool  case_method_arg_has_value;
	struct listnode list;
	gint32 test_result;
};

struct dbus_method{
	char *name;
	struct listnode arg_list;
	struct listnode list;
	bool introspect_has_method:true;
	gint32 test_result;
};

struct dbus_signal_arg{
	char *name;
	char  type[16];
	char  direction[4];
	struct listnode list;
	gint32 test_result;
};

struct dbus_signal{
	char *name;
	struct listnode arg_list;
	struct listnode list;
	gint32 test_result;
};

union dbus_arg {
	struct dbus_method_arg method_arg;
	struct dbus_signal_arg signal_arg;
};

struct dbus_property {
	char *name;
	char  type[16];
	char  access[12];
	dbus_variant_val_t value;
	dbus_variant_val_t value2;
	dbus_variant_val_t value_bad;
	gchar flags;
	gchar  case_property_has_value;
	gchar  case_property_set_value;//0== unset; 1==value; 2==value2;
	bool  notification;
	dbus_variant_val_t min;
	dbus_variant_val_t max;
	bool  case_property_has_min;
	bool  case_property_has_max;//Notes, min/max would be initialed by 0...
	struct listnode list;
	bool introspect_has_property;
	gint32 test_result;
};



struct dbus_interface{
	char *name;
	char *path;
	struct listnode method_list;
	struct listnode signal_list;
	struct listnode property_list;
	struct listnode list;
	bool introspect_has_interface:true;
	gint32 test_result;
};



struct dbus_object {
	char *name;
	char *form_name;//owenlee
	struct listnode interface_list;
	struct listnode list;
	gint32 test_result;
};

struct dbus_case{
	char*name;
	struct listnode object_list;
	struct listnode list;
};

typedef enum {
	PARSE_TAG_STATUS_NONE 		= 0,
	PARSE_TAG_STATUS_NODE 		= 1,
	PARSE_TAG_STATUS_INTERFACE 	= 2,
	PARSE_TAG_STATUS_METHOD 	= 3,
	PARSE_TAG_STATUS_SIGNAL 	= 4,
	PARSE_TAG_STATUS_PROPERTY 	= 5,
	PARSE_TAG_STATUS_ARG		= 6,
} parse_tag_status_t;


typedef enum {
	CASE_PARSE_TAG_STATUS_NONE 		= 0,
	CASE_PARSE_TAG_STATUS_ID         =1,	
	CASE_PARSE_TAG_STATUS_NODE 		= 2,
	CASE_PARSE_TAG_STATUS_INTERFACE 	=3,
	CASE_PARSE_TAG_STATUS_METHOD 	= 4,
	CASE_PARSE_TAG_STATUS_SIGNAL 	= 5,
	CASE_PARSE_TAG_STATUS_PROPERTY 	= 6,
	CASE_PARSE_TAG_STATUS_ARG		= 7,
} case_parse_tag_status_t;
extern struct listnode dbus_list;
extern struct listnode dbus_case_list;

extern int dbus_xml_init( void );

extern bool print_introspect;
#endif /* end of _DBUS_XML_PARSE_H_ */
