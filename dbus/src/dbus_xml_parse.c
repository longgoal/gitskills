#include <expat.h>
#include <dbus_cts.h>
#include <list.h>
#include <dbus_xml_parse.h>

#ifdef x86
//#define xml_path "/home/public/dbus_cts.xml.bak"  
#else
//#define xml_path "/tmp/dbus_cts.xml.bak"  
#endif
//#define xml_case_bak_path  "/tmp/dbus_cts.case.xml"
#define DEBUG 0
extern char xml_path[100];
extern char noinstance_xml_path[100];
extern char result_file[100];
//extern char xml_case_bak_path[100];
extern char xml_case_bak_path[100];
#define BUF_SIZE 1024

struct listnode dbus_list;
struct listnode dbus_case_list;
struct listnode dbus_result_list;
gint32 init_result = TEST_OK;


static void str_to_variant_value(dbus_variant_val_t * variant_value_p,
		const char * type, const char * value_str)
{
	char * str_p = NULL;
	char * str_tmp_p = NULL;
	char * comma_brace_p = NULL;
	int count;
	int idx = 0;

	/* parse string array and device info struct array */
	if(strcmp(type, "as")==0) {
		variant_value_p->str_array.str_mem_block = malloc(strlen(value_str) + 1);
		str_p = (char *)variant_value_p->str_array.str_mem_block;
		if(str_p == NULL) {
			dbus_printf("%s: failed to alloc memory\n", __func__);
			return;
		}
		strcpy(str_p, value_str);
		str_tmp_p = str_p;


		count = 1;
		while(*str_tmp_p) {
			if( (comma_brace_p = strchr(str_tmp_p, ',')) != NULL ) {
				*comma_brace_p = 0;
				count++;
				str_tmp_p = comma_brace_p + 1;
			//dbus_printf("####s %s\n",str_tmp_p);
			} else {
				break;
			}
		}
		variant_value_p->str_array.str_arry_p = (gchar **)malloc((count + 1) * sizeof(gchar **));
		if(variant_value_p->str_array.str_arry_p == NULL) {
			dbus_printf("%s: failed to alloc memory\n", __func__);
			return;
		}
		memset(variant_value_p->str_array.str_arry_p, 0, (count + 1) * sizeof(gchar **));
		//variant_value_p->str_array.str_count=(count-1);
		variant_value_p->str_array.str_count=count;
                /*    count == 1
                    , count == 2
                    , , count == 3.
                    str_array_str_arry_p[idx] would accept the null point. And it would pick out by dbus_g_variant_test_and_return_new
                    if(strlen(....) >0)
                */

		do {
			variant_value_p->str_array.str_arry_p[idx] = str_p;
			++idx;
			str_p += (strlen(str_p) + 1);
			//dbus_printf("as %s %d %d\n",variant_value_p->str_array.str_arry_p[idx-1], (idx-1),variant_value_p->str_array.str_count);
 
		} while (--count > 0);
		return;
	} else if(strcmp(type, "a{sv}")==0) {
		//Notes...... a{sv}  as s ....
		variant_value_p->path_str = (gchar *)malloc(strlen(value_str) + 1);
		strcpy(variant_value_p->path_str, value_str);

	} else if(strcmp(type, "a(ss)")==0) {
		DevInfo_t * devInfo_p = NULL;

		variant_value_p->devInfo.str_mem_block = malloc(strlen(value_str) + 1);
		str_p = (char *)variant_value_p->devInfo.str_mem_block;
		if(str_p == NULL) {
			dbus_printf("%s: failed to alloc memory\n", __func__);
			return;
		}
		strcpy(str_p, value_str);
		str_tmp_p = str_p;

		count = 0;
		while(*str_tmp_p) {
			if( (comma_brace_p = strchr(str_tmp_p, '{')) != NULL ) {
				count++;
				str_tmp_p = comma_brace_p + 1;
			} else {
				break;
			}
		}
		if(count) {
			devInfo_p = (DevInfo_t *)malloc((count+1) * sizeof(DevInfo_t *));
			if(devInfo_p == NULL) {
				dbus_printf("%s: failed to alloc memory of DevInfo point array\n", __func__);
				return;
			}
			memset(devInfo_p , 0, (count+1) * sizeof(DevInfo_t *));
			variant_value_p->devInfo.devInfo_p = devInfo_p;
		}
		while(count-- > 0) {
			devInfo_p[idx].str1 = strchr(str_p, '{') + 1;
			comma_brace_p = strchr(devInfo_p[idx].str1, ',');
			*comma_brace_p = 0;
			devInfo_p[idx].str2 = comma_brace_p + 1;
			comma_brace_p = strchr(devInfo_p[idx].str2, '}');
			*comma_brace_p = 0;
			idx++;
			str_p = comma_brace_p + 1;
		}

		return;
	}

	switch(*type) {
	case 'y':
		variant_value_p->byte_v = (guchar)(atoi(value_str));
		break;
	case 'b':
		variant_value_p->bool_v = (gboolean)(atoi(value_str));
		break;
	case 'n':
		variant_value_p->int16_v = (gint16)(atoi(value_str));
		break;
	case 'q':
		variant_value_p->uint16_v = (guint16)(strtoul(value_str, NULL, 0));
		break;
	case 'i':
		variant_value_p->int32_v = (gint32)(atol(value_str));
		break;
	case 'u':
		variant_value_p->uint32_v = (guint32)(strtoul(value_str, NULL, 0));
		break;
	case 'x':
		variant_value_p->int64_v = (gint64)(atoll(value_str));
		break;
	case 't':
		variant_value_p->uint64_v = (guint64)(strtoull(value_str, NULL, 0));
		break;
	case 'd':
		variant_value_p->double_v = (gdouble)(strtod(value_str, NULL));
		break;
	case 'h':
		variant_value_p->handle_v = (gint32)(atol(value_str));
		break;
	case 's':
	case 'p':
	case 'o':
		variant_value_p->path_str = (gchar *)malloc(strlen(value_str) + 1);
		strcpy(variant_value_p->path_str, value_str);
		break;
	}
}

static void start_tag(void *data, const XML_Char *tag_name,
                      const XML_Char **attr)
{
	const XML_Char *attr_name = NULL;
	const XML_Char *attr_form_name = NULL;
	const XML_Char *attr_path = NULL;
	const XML_Char *attr_type = NULL;
	const XML_Char *attr_direction = NULL;
	const XML_Char *attr_access = NULL;
	const XML_Char *attr_value = NULL;
	const XML_Char *attr_value_bad = NULL;
	const XML_Char *attr_notification = NULL;
	const XML_Char *attr_min = NULL;
	const XML_Char *attr_max = NULL;
	struct listnode *dbus_list_head_p = (struct listnode*)data;
	struct listnode *dbus_case_list_head_p = (struct listnode*)data;
	static struct dbus_case *current_dbus_case_p = NULL;
	unsigned int i;
	static parse_tag_status_t tag_status = PARSE_TAG_STATUS_NONE;
	static struct dbus_object * current_dbus_object_p = NULL;
	static struct dbus_interface * current_interface_p = NULL;
	static struct dbus_method * current_method_p = NULL;
	static struct dbus_signal * current_signal_p = NULL;

	//debug("tag name:%-20s\ttag attribute name:", tag_name);
	for (i = 0; attr[i]; i += 2) {
		debug("%s ", attr[i]);
		if (strcmp(attr[i], "name") == 0)
			attr_name = attr[i + 1];
		if (strcmp(attr[i], "formname") == 0)
			attr_form_name = attr[i + 1];
		if (strcmp(attr[i], "path") == 0)
			attr_path = attr[i + 1];
		else if (strcmp(attr[i], "type") == 0)
			attr_type = attr[i + 1];
		else if (strcmp(attr[i], "access") == 0)
			attr_access = attr[i + 1];
		else if (strcmp(attr[i], "direction") == 0)
			attr_direction = attr[i + 1]; 
		else if ((strcmp(attr[i], "value") == 0))
			attr_value = attr[i + 1];
		else if (strcmp(attr[i], "value_bad") == 0)
			attr_value_bad = attr[i + 1];
		else if (strcmp(attr[i], "notification") == 0)
			attr_notification = attr[i + 1];
		else if (strcmp(attr[i], "min") == 0)
			attr_min = attr[i + 1];
		else if (strcmp(attr[i], "max") == 0)
			attr_max = attr[i + 1];
	}
	//debug("\n");
	if (strcmp(tag_name, "node") == 0) {
		struct dbus_object *dbus_object_new_p;

		dbus_object_new_p = (struct dbus_object *)malloc(sizeof(struct dbus_object));
		if( !dbus_object_new_p ) {
			dbus_printf("failed to alloc struct dbus_object memory\n");
			return;
		}
		memset(dbus_object_new_p, 0, sizeof(struct dbus_object));
		if(attr_name != NULL) {
			dbus_object_new_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(dbus_object_new_p->name != NULL)
				strcpy(dbus_object_new_p->name, attr_name);
		}
		dbus_object_new_p->form_name = NULL;
		dbus_object_new_p->test_result = init_result;

		list_init(&dbus_object_new_p->interface_list);
		list_add_tail(dbus_list_head_p, &dbus_object_new_p->list);
		tag_status = PARSE_TAG_STATUS_NODE;
		current_dbus_object_p = (void *)dbus_object_new_p;
	}
	else if (strcmp(tag_name, "form_node") == 0) {

		if(PARSE_TAG_STATUS_NONE == tag_status) {
			dbus_printf("Error interface information. Skip!\n");
			return;
		}
		if(attr_form_name != NULL) {
			current_dbus_object_p->form_name = (char *)malloc(strlen(attr_form_name) + 1);
			if(current_dbus_object_p->form_name != NULL)
				strcpy(current_dbus_object_p->form_name, attr_form_name);
		}
	}
	else if (strcmp(tag_name, "interface") == 0) {
		struct dbus_interface *interface_p;

		if(PARSE_TAG_STATUS_NONE == tag_status) {
			dbus_printf("Error interface information. Skip!\n");
			return;
		}
		interface_p = (struct dbus_interface *)malloc(sizeof(struct dbus_interface));
		if( !interface_p ) {
			dbus_printf("failed to alloc struct dbus_interface memory\n");
			return;
		}
		memset(interface_p, 0, sizeof(struct dbus_interface));
		interface_p->introspect_has_interface = true;
		interface_p->test_result = init_result;
		if(attr_name != NULL) {
			interface_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(interface_p->name != NULL)
				strcpy(interface_p->name, attr_name);
		}
		if(attr_path != NULL) {
			interface_p->path = (char *)malloc(strlen(attr_path) + 1);
			if(interface_p->path != NULL)
				strcpy(interface_p->path, attr_path);
		}
		
		list_init(&interface_p->method_list);
		list_init(&interface_p->signal_list);
		list_init(&interface_p->property_list);
		list_add_tail(&current_dbus_object_p->interface_list, &interface_p->list);
		tag_status = PARSE_TAG_STATUS_INTERFACE;
		current_interface_p = interface_p;
	}
	else if(strcmp(tag_name, "method") == 0) {
		struct dbus_method * method_p;

		if(tag_status < PARSE_TAG_STATUS_INTERFACE) {
			dbus_printf("Error method information. Skip!\n");
			return;
		}
		method_p = (struct dbus_method *)malloc(sizeof(struct dbus_method));
		if( !method_p ) {
			dbus_printf("failed to alloc struct dbus_method memory\n");
			return;
		}
		memset(method_p, 0, sizeof(struct dbus_method));
		method_p->introspect_has_method = true;
		method_p->test_result = init_result;
		if(attr_name != NULL) {
			method_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(method_p->name != NULL)
				strcpy(method_p->name, attr_name);
		}

		list_init(&method_p->arg_list);
		list_add_tail(&current_interface_p->method_list, &method_p->list);
		tag_status = PARSE_TAG_STATUS_METHOD;
		current_method_p = method_p;
	}
	else if(strcmp(tag_name, "arg") == 0) {
		union dbus_arg *dbus_arg_p;

		if(tag_status <= PARSE_TAG_STATUS_INTERFACE) {
			dbus_printf("Error arg information. Skip!\n");
			return;
		}
		dbus_arg_p = (union dbus_arg *)malloc(sizeof(union dbus_arg));
		if( !dbus_arg_p ) {
			dbus_printf("failed to alloc union dbus_arg memory\n");
			return;
		}
		memset(dbus_arg_p, 0, sizeof(union dbus_arg));
		switch (tag_status) {
		case PARSE_TAG_STATUS_METHOD:
			dbus_arg_p->method_arg.case_method_arg_has_value=false;
			dbus_arg_p->method_arg.test_result = init_result;
			if(attr_name != NULL) {
				dbus_arg_p->method_arg.name = (char *)malloc(strlen(attr_name) + 1);
				if(dbus_arg_p->method_arg.name != NULL)
					strcpy(dbus_arg_p->method_arg.name, attr_name);
			}
			if( attr_type ) {
				strcpy(dbus_arg_p->method_arg.type, attr_type);
				if(attr_value != NULL && attr_direction != NULL && (g_strcmp0(attr_direction, "in")==0)){
					str_to_variant_value(&dbus_arg_p->method_arg.value, attr_type, attr_value);
					dbus_arg_p->method_arg.case_method_arg_has_value=true;
				}
				if(attr_value_bad != NULL && attr_direction != NULL && (g_strcmp0(attr_direction, "in")==0))
					str_to_variant_value(&dbus_arg_p->method_arg.value_bad, attr_type, attr_value_bad);
			}
			if( attr_direction )
				strcpy(dbus_arg_p->method_arg.direction, attr_direction);

			list_add_tail(&current_method_p->arg_list,
					&(dbus_arg_p->method_arg.list));
			break;
		case PARSE_TAG_STATUS_SIGNAL:
			dbus_arg_p->signal_arg.test_result = init_result;
			if(attr_name != NULL) {
				dbus_arg_p->signal_arg.name = (char *)malloc(strlen(attr_name) + 1);
				if(dbus_arg_p->signal_arg.name != NULL)
					strcpy(dbus_arg_p->signal_arg.name, attr_name);
			}
			if( attr_type )
				strcpy(dbus_arg_p->signal_arg.type, attr_type);
			if( attr_direction )
				strcpy(dbus_arg_p->signal_arg.direction, attr_direction);

			list_add_tail(&current_signal_p->arg_list,
					&(dbus_arg_p->signal_arg.list));
			break;
		default:
			free(dbus_arg_p);
			dbus_printf("Error arg information. Skip!\n");
			return;
		}
	}
	else if(strcmp(tag_name, "signal") == 0){
		struct dbus_signal * signal_p;

		if(tag_status < PARSE_TAG_STATUS_INTERFACE) {
			dbus_printf("Error signal information. Skip!\n");
			return;
		}
		signal_p = (struct dbus_signal *)malloc(sizeof(struct dbus_signal));
		if( !signal_p ) {
			dbus_printf("failed to alloc struct dbus_signal memory\n");
			return;
		}
		memset(signal_p, 0, sizeof(struct dbus_signal));
		signal_p->test_result = init_result;
		if(attr_name != NULL) {
			signal_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(signal_p->name != NULL)
				strcpy(signal_p->name, attr_name);
		}

		list_init(&signal_p->arg_list);
		list_add_tail(&current_interface_p->signal_list, &signal_p->list);
		tag_status = PARSE_TAG_STATUS_SIGNAL;
		current_signal_p = signal_p;
	}
	else if(strcmp(tag_name, "property") == 0){
		struct dbus_property * property_p;

		if(tag_status < PARSE_TAG_STATUS_INTERFACE) {
			dbus_printf("Error property_p information. Skip!\n");
			return;
		}
		property_p = (struct dbus_property *)malloc(sizeof(struct dbus_property));
		if( !property_p ) {
			dbus_printf("failed to alloc struct dbus_property memory\n");
			return;
		}
		property_p->test_result=init_result;
		memset(property_p, 0, sizeof(struct dbus_property));
		property_p->introspect_has_property = false;
		property_p->case_property_has_value = 0x0;//Notes:.... always false in xml
		property_p->notification = false;
		property_p->case_property_has_min=false;
		property_p->case_property_has_max=false;
		if(attr_name != NULL) {
			property_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(property_p->name != NULL)
				strcpy(property_p->name, attr_name);
		}
		if( attr_access )
			strcpy(property_p->access, attr_access);

		if( attr_notification )
			if((g_strcmp0(attr_notification, "y") == 0))
				property_p->notification = true;



		if( attr_type ) {
			strcpy(property_p->type, attr_type);
			if(attr_value != NULL && attr_access != NULL &&
					((g_strcmp0(attr_access, "write") == 0)||(g_strcmp0(attr_access, "readwrite") == 0)))
			{
				str_to_variant_value(&property_p->value, attr_type, attr_value);
			}
			if(attr_value_bad != NULL && attr_access != NULL &&
					((g_strcmp0(attr_access, "write") == 0)||(g_strcmp0(attr_access, "readwrite") == 0)))
				str_to_variant_value(&property_p->value_bad, attr_type, attr_value_bad);
		}

		if( attr_min ) {
			if(attr_type != NULL)
			{
				str_to_variant_value(&property_p->min, attr_type, attr_min);
				property_p->case_property_has_min=true;
			}
		}

		if( attr_max ) {
			if(attr_type != NULL)
			{
				str_to_variant_value(&property_p->max, attr_type, attr_max);
				property_p->case_property_has_max=true;
			}
		}

		list_add_tail(&current_interface_p->property_list, &property_p->list);
		tag_status = PARSE_TAG_STATUS_PROPERTY;
	}
}

static void end_tag(void *data, const XML_Char *tag_name)
{
	data;
	tag_name;
	//debug("************end_tag : tag_name:%s\n", tag_name);
}

int dbus_xml_init( void )
{
	XML_Parser parser;
	FILE *file;
	int bytes_read;
	void *buf;
	int ret = 0;
#if DEBUG
	struct listnode *obj_list_item_p;
	struct listnode *interface_list_item_p;
	struct listnode *method_list_item_p;
	struct listnode *signal_list_item_p;
	struct listnode *property_list_item_p;
	struct listnode *arg_list_item_p;
#endif

	file = fopen(xml_path, "r");
	if (!file) {
		dbus_printf("Failed to open %s\n", xml_path);
		ret = -1;
		return ret;
	}

	parser = XML_ParserCreate(NULL);

	if (!parser) {
		dbus_printf("Failed to create XML parser\n");
		ret = -1;
		goto err_parser_create;
	}
	list_init(&dbus_list);
	XML_SetUserData(parser, &dbus_list);

	//init_result = TEST_OK;
	init_result = UNPASS;
	XML_SetElementHandler(parser, start_tag, end_tag);

	for (;;) {
		buf = XML_GetBuffer(parser, BUF_SIZE);
		if (buf == NULL) {
			dbus_printf("failed to get XML buffer\n");
            ret = -1;
			goto err_parse;
		}

		bytes_read = fread(buf, 1, BUF_SIZE, file);

		if (bytes_read < 0) {
			dbus_printf("failed to read file\n");
            ret = -1;
			goto err_parse;
		}

		if (XML_ParseBuffer(parser, bytes_read,
					bytes_read == 0)== XML_STATUS_ERROR) {
			dbus_printf("Error in xml (%s)\n", xml_path);
            ret = -1;
			goto err_parse;
		}
		if (bytes_read == 0)
			break;
	}

#if DEBUG
	dbus_printf("\n\n");
	list_for_each(obj_list_item_p, &dbus_list) {
		struct dbus_object *dbus_object_p;

		dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
		dbus_printf("###node name: %s\n", dbus_object_p->name);
		list_for_each(interface_list_item_p, &dbus_object_p->interface_list) {
			struct dbus_interface *interface_p =
				node_to_item(interface_list_item_p,
						struct dbus_interface, list);

			dbus_printf("\tinterface name: %s\n", interface_p->name);
			list_for_each(method_list_item_p, &interface_p->method_list) {
				struct dbus_method *method_p =
					node_to_item(method_list_item_p,
							struct dbus_method, list);

				dbus_printf("\t\tmethod name: %s\n", method_p->name);
				list_for_each(arg_list_item_p, &method_p->arg_list) {
					struct dbus_method_arg *arg_item_p =
						node_to_item(arg_list_item_p,
								struct dbus_method_arg, list);

					dbus_printf("\t\t\targ name:%s type:%s direction:%s\n",
					arg_item_p->name, arg_item_p->type, arg_item_p->direction);
				}
			}

			list_for_each(signal_list_item_p, &interface_p->signal_list) {
				struct dbus_signal *signal_p =
					node_to_item(signal_list_item_p,
							struct dbus_signal, list);

				dbus_printf("\t\tsignal name: %s\n", signal_p->name);
				list_for_each(arg_list_item_p, &signal_p->arg_list) {
					struct dbus_signal_arg *arg_item_p =
						node_to_item(arg_list_item_p,
								struct dbus_signal_arg, list);

					dbus_printf("\t\t\targ name:%s type:%s direction:%s\n",
					arg_item_p->name, arg_item_p->type, arg_item_p->direction);
				}
			}

			list_for_each(property_list_item_p, &interface_p->property_list) {
				struct dbus_property *property_p =
					node_to_item(property_list_item_p,
							struct dbus_property, list);

				dbus_printf("\t\tproperty name:%s type:%s access:%s\n",
						property_p->name, property_p->type, property_p->access);
			}
		}
	}
#endif
	err_parse:
		XML_ParserFree(parser);
	err_parser_create:
		fclose(file);
	
	return ret;
}

void dbus_case_start_tag(void *data, const XML_Char *tag_name,
                      const XML_Char **attr)
{
	const XML_Char *attr_name = NULL;
	const XML_Char *attr_path = NULL;
	const XML_Char *attr_type = NULL;
	const XML_Char *attr_direction = NULL;
	const XML_Char *attr_access = NULL;
	const XML_Char *attr_value = NULL;
	const XML_Char *attr_value2 = NULL;
	const XML_Char *attr_value_bad = NULL;

	const XML_Char *attr_notification = NULL;
	const XML_Char *attr_min = NULL;
	const XML_Char *attr_max = NULL;


	struct listnode *dbus_case_list_head_p = (struct listnode*)data;
	unsigned int i;
	static case_parse_tag_status_t tag_status = CASE_PARSE_TAG_STATUS_NONE;
	static struct dbus_case *current_dbus_case_p = NULL;
	static struct dbus_object * current_dbus_object_p = NULL;
	static struct dbus_interface * current_interface_p = NULL;
	static struct dbus_method * current_method_p = NULL;
	static struct dbus_signal * current_signal_p = NULL;

//	dbus_printf("dbus_case_start_tag\n");
//	dbus_printf("tag name:%-20s\ttag attribute name:", tag_name);
	for (i = 0; attr[i]; i += 2) {
		debug("%s ", attr[i]);
#if 0
		if (strcmp(attr[i], "name") == 0)
			attr_name = attr[i + 1];
		/*if (strcmp(attr[i], "path") == 0)
			attr_path = attr[i + 1];*/
		else if (strcmp(attr[i], "type") == 0)
			attr_type = attr[i + 1];
		else if (strcmp(attr[i], "access") == 0)
			attr_access = attr[i + 1];
		else if (strcmp(attr[i], "direction") == 0)
			attr_direction = attr[i + 1];
		else if ((strcmp(attr[i], "value") == 0) || (strcmp(attr[i], "test_value") == 0))
			attr_value = attr[i + 1];
		/*else if (strcmp(attr[i], "value_bad") == 0)
			attr_value_bad = attr[i + 1];*/
#endif
		if (strcmp(attr[i], "name") == 0)
			attr_name = attr[i + 1];
		if (strcmp(attr[i], "path") == 0)
			attr_path = attr[i + 1];
		else if (strcmp(attr[i], "type") == 0)
			attr_type = attr[i + 1];
		else if (strcmp(attr[i], "access") == 0)
			attr_access = attr[i + 1];
		else if (strcmp(attr[i], "direction") == 0)
			attr_direction = attr[i + 1]; 
		else if (((strcmp(attr[i], "value") == 0)) ||(strcmp(attr[i], "test_value") == 0))
			attr_value = attr[i + 1];
		else if (strcmp(attr[i], "test_value2") == 0)
			attr_value2 = attr[i + 1];
		else if (strcmp(attr[i], "value_bad") == 0)
			attr_value_bad = attr[i + 1];
		else if (strcmp(attr[i], "notification") == 0)
			attr_notification = attr[i + 1];
		else if (strcmp(attr[i], "min") == 0)
			attr_min = attr[i + 1];
		else if (strcmp(attr[i], "max") == 0)
			attr_max = attr[i + 1];
	}
	//debug("\n");
	if (g_strcmp0(tag_name, "case") == 0){
		struct dbus_case *dbus_case_new_p;

		dbus_case_new_p = (struct dbus_case *)malloc(sizeof(struct dbus_case));
		if( !dbus_case_new_p ) {
			dbus_printf("failed to alloc struct dbus_object memory\n");
			return;
		}
		memset(dbus_case_new_p, 0, sizeof(struct dbus_case));
		if(attr_name != NULL) {
			dbus_case_new_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(dbus_case_new_p->name != NULL)
				strcpy(dbus_case_new_p->name, attr_name);
		}

		list_init(&dbus_case_new_p->object_list);
		list_add_tail(dbus_case_list_head_p, &dbus_case_new_p->list);
		tag_status = CASE_PARSE_TAG_STATUS_ID;
		current_dbus_case_p = (void *)dbus_case_new_p;
	}
	else if (g_strcmp0(tag_name, "node") == 0) {

		if( tag_status != CASE_PARSE_TAG_STATUS_ID ) {
			dbus_printf("Error object information. Skip!\n");
			return;
		}
		struct dbus_object *dbus_object_new_p;

		dbus_object_new_p = (struct dbus_object *)malloc(sizeof(struct dbus_object));
		if( !dbus_object_new_p ) {
			dbus_printf("failed to alloc struct dbus_object memory\n");
			return;
		}
		memset(dbus_object_new_p, 0, sizeof(struct dbus_object));
		if(attr_name != NULL) {
			dbus_object_new_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(dbus_object_new_p->name != NULL)
				strcpy(dbus_object_new_p->name, attr_name);
		}

		list_init(&dbus_object_new_p->interface_list);
		list_add_tail(&current_dbus_case_p->object_list, &dbus_object_new_p->list);
		tag_status = CASE_PARSE_TAG_STATUS_NODE;
		current_dbus_object_p = (void *)dbus_object_new_p;
	}
#if 0
	else if (g_strcmp0(tag_name, "interface") == 0) {
		struct dbus_interface *interface_p;

		if(tag_status < CASE_PARSE_TAG_STATUS_NODE){
			dbus_printf("Error interface information. Skip!\n");
			return;
		}
		interface_p = (struct dbus_interface *)malloc(sizeof(struct dbus_interface));
		if( !interface_p ) {
			dbus_printf("failed to alloc struct dbus_interface memory\n");
			return;
		}
		memset(interface_p, 0, sizeof(struct dbus_interface));
		if(attr_name != NULL) {
			interface_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(interface_p->name != NULL)
				strcpy(interface_p->name, attr_name);
		}
		
		list_init(&interface_p->method_list);
		list_init(&interface_p->signal_list);
		list_init(&interface_p->property_list);
		list_add_tail(&current_dbus_object_p->interface_list, &interface_p->list);
		tag_status = CASE_PARSE_TAG_STATUS_INTERFACE;
		current_interface_p = interface_p;
	}
	else if(g_strcmp0(tag_name, "method") == 0) {
		struct dbus_method * method_p;

		if(tag_status < CASE_PARSE_TAG_STATUS_INTERFACE) {
			dbus_printf("Error method information. Skip!\n");
			return;
		}
		method_p = (struct dbus_method *)malloc(sizeof(struct dbus_method));
		if( !method_p ) {
			dbus_printf("failed to alloc struct dbus_method memory\n");
			return;
		}
		memset(method_p, 0, sizeof(struct dbus_method));
		if(attr_name != NULL) {
			method_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(method_p->name != NULL)
				strcpy(method_p->name, attr_name);
		}

		list_init(&method_p->arg_list);
		list_add_tail(&current_interface_p->method_list, &method_p->list);
		tag_status = CASE_PARSE_TAG_STATUS_METHOD;
		current_method_p = method_p;
	}
	else if(g_strcmp0(tag_name, "arg") == 0) {
		union dbus_arg *dbus_arg_p;

		if(tag_status < CASE_PARSE_TAG_STATUS_METHOD) {
			dbus_printf("Error arg information. Skip!\n");
			return;
		}
		dbus_arg_p = (union dbus_arg *)malloc(sizeof(union dbus_arg));
		if( !dbus_arg_p ) {
			dbus_printf("failed to alloc union dbus_arg memory\n");
			return;
		}
		memset(dbus_arg_p, 0, sizeof(union dbus_arg));
		dbus_arg_p->method_arg.case_method_arg_has_value=false;

		if(attr_name != NULL) {
			dbus_arg_p->method_arg.name = (char *)malloc(strlen(attr_name) + 1);
			if(dbus_arg_p->method_arg.name != NULL)
				strcpy(dbus_arg_p->method_arg.name, attr_name);
		}
		if( attr_type ) {
			strcpy(dbus_arg_p->method_arg.type, attr_type);
			if(attr_value != NULL )
			{
				str_to_variant_value(&dbus_arg_p->method_arg.value, attr_type, attr_value);
				dbus_arg_p->method_arg.case_method_arg_has_value=true;
			}
		}

		list_add_tail(&current_method_p->arg_list,
				&(dbus_arg_p->method_arg.list));
	}
	else if(g_strcmp0(tag_name, "signal") == 0){
		struct dbus_signal * signal_p;

		if(tag_status < CASE_PARSE_TAG_STATUS_INTERFACE) {
			dbus_printf("Error signal information. Skip!\n");
			return;
		}
		signal_p = (struct dbus_signal *)malloc(sizeof(struct dbus_signal));
		if( !signal_p ) {
			dbus_printf("failed to alloc struct dbus_signal memory\n");
			return;
		}
		memset(signal_p, 0, sizeof(struct dbus_signal));
		if(attr_name != NULL) {
			signal_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(signal_p->name != NULL)
				strcpy(signal_p->name, attr_name);
		}

		list_init(&signal_p->arg_list);
		list_add_tail(&current_interface_p->signal_list, &signal_p->list);
		tag_status = CASE_PARSE_TAG_STATUS_SIGNAL;
		current_signal_p = signal_p;
	}
	else if(g_strcmp0(tag_name, "property") == 0){
		struct dbus_property * property_p;

		if(tag_status < CASE_PARSE_TAG_STATUS_INTERFACE) {
			dbus_printf("Error property_p information. Skip!\n");
			return;
		}
		property_p = (struct dbus_property *)malloc(sizeof(struct dbus_property));
		if( !property_p ) {
			dbus_printf("failed to alloc struct dbus_property memory\n");
			return;
		}
		memset(property_p, 0, sizeof(struct dbus_property));
		property_p->case_property_has_value = 0x0;

		if(attr_name != NULL) {
			property_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(property_p->name != NULL)
				strcpy(property_p->name, attr_name);
		}
		//dbus_printf("name = %s\n",property_p->name);
		if( attr_type ) {
			strcpy(property_p->type, attr_type);
			if(attr_value != NULL)
			{
				str_to_variant_value(&property_p->value, attr_type, attr_value);
				property_p->case_property_has_value |= 0x1;
			}
		}
		list_add_tail(&current_interface_p->property_list, &property_p->list);
		tag_status = PARSE_TAG_STATUS_PROPERTY;
	}
#endif
	else if (strcmp(tag_name, "interface") == 0) {
		struct dbus_interface *interface_p;

		if(PARSE_TAG_STATUS_NONE == tag_status) {
			dbus_printf("Error interface information. Skip!\n");
			return;
		}
		interface_p = (struct dbus_interface *)malloc(sizeof(struct dbus_interface));
		if( !interface_p ) {
			dbus_printf("failed to alloc struct dbus_interface memory\n");
			return;
		}
		memset(interface_p, 0, sizeof(struct dbus_interface));
		
		interface_p->introspect_has_interface = true;
		if(attr_name != NULL) {
			interface_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(interface_p->name != NULL)
				strcpy(interface_p->name, attr_name);
		}
		if(attr_path != NULL) {
			interface_p->path = (char *)malloc(strlen(attr_path) + 1);
			if(interface_p->path != NULL)
				strcpy(interface_p->path, attr_path);
		}
		
		list_init(&interface_p->method_list);
		list_init(&interface_p->signal_list);
		list_init(&interface_p->property_list);
		list_add_tail(&current_dbus_object_p->interface_list, &interface_p->list);
		tag_status = PARSE_TAG_STATUS_INTERFACE;
		current_interface_p = interface_p;
	}
	else if(strcmp(tag_name, "method") == 0) {
		struct dbus_method * method_p;

		if(tag_status < PARSE_TAG_STATUS_INTERFACE) {
			dbus_printf("Error method information. Skip!\n");
			return;
		}
		method_p = (struct dbus_method *)malloc(sizeof(struct dbus_method));
		if( !method_p ) {
			dbus_printf("failed to alloc struct dbus_method memory\n");
			return;
		}
		memset(method_p, 0, sizeof(struct dbus_method));
		method_p->introspect_has_method = true;
		if(attr_name != NULL) {
			method_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(method_p->name != NULL)
				strcpy(method_p->name, attr_name);
		}

		list_init(&method_p->arg_list);
		list_add_tail(&current_interface_p->method_list, &method_p->list);
		tag_status = PARSE_TAG_STATUS_METHOD;
		current_method_p = method_p;
	}
	else if(strcmp(tag_name, "arg") == 0) {

		union dbus_arg *dbus_arg_p;

		if(tag_status <= PARSE_TAG_STATUS_INTERFACE) {
			dbus_printf("Error arg information. Skip!\n");
			return;
		}
		dbus_arg_p = (union dbus_arg *)malloc(sizeof(union dbus_arg));
		if( !dbus_arg_p ) {
			dbus_printf("failed to alloc union dbus_arg memory\n");
			return;
		}
		memset(dbus_arg_p, 0, sizeof(union dbus_arg));
		dbus_arg_p->method_arg.case_method_arg_has_value=false;

		switch (tag_status) {
		case PARSE_TAG_STATUS_METHOD:
			if(attr_name != NULL) {
				dbus_arg_p->method_arg.name = (char *)malloc(strlen(attr_name) + 1);
				if(dbus_arg_p->method_arg.name != NULL)
					strcpy(dbus_arg_p->method_arg.name, attr_name);
			}
			if( attr_type ) {
				strcpy(dbus_arg_p->method_arg.type, attr_type);
				if(attr_value != NULL && attr_direction != NULL && (g_strcmp0(attr_direction, "in")==0)){
					str_to_variant_value(&dbus_arg_p->method_arg.value, attr_type, attr_value);
					dbus_arg_p->method_arg.case_method_arg_has_value=true;
				}
				if(attr_value_bad != NULL && attr_direction != NULL && (g_strcmp0(attr_direction, "in")==0))
					str_to_variant_value(&dbus_arg_p->method_arg.value_bad, attr_type, attr_value_bad);
			}
			if( attr_direction )
				strcpy(dbus_arg_p->method_arg.direction, attr_direction);

			list_add_tail(&current_method_p->arg_list,
					&(dbus_arg_p->method_arg.list));
			break;
		case PARSE_TAG_STATUS_SIGNAL:
			if(attr_name != NULL) {
				dbus_arg_p->signal_arg.name = (char *)malloc(strlen(attr_name) + 1);
				if(dbus_arg_p->signal_arg.name != NULL)
					strcpy(dbus_arg_p->signal_arg.name, attr_name);
			}
			if( attr_type )
				strcpy(dbus_arg_p->signal_arg.type, attr_type);
			if( attr_direction )
				strcpy(dbus_arg_p->signal_arg.direction, attr_direction);

			list_add_tail(&current_signal_p->arg_list,
					&(dbus_arg_p->signal_arg.list));
			break;
		default:
			free(dbus_arg_p);
			dbus_printf("Error arg information. Skip!\n");
			return;
		}
	}
	else if(strcmp(tag_name, "signal") == 0){
		struct dbus_signal * signal_p;

		if(tag_status < PARSE_TAG_STATUS_INTERFACE) {
			dbus_printf("Error signal information. Skip!\n");
			return;
		}
		signal_p = (struct dbus_signal *)malloc(sizeof(struct dbus_signal));
		if( !signal_p ) {
			dbus_printf("failed to alloc struct dbus_signal memory\n");
			return;
		}
		memset(signal_p, 0, sizeof(struct dbus_signal));
		if(attr_name != NULL) {
			signal_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(signal_p->name != NULL)
				strcpy(signal_p->name, attr_name);
		}

		list_init(&signal_p->arg_list);
		list_add_tail(&current_interface_p->signal_list, &signal_p->list);
		tag_status = PARSE_TAG_STATUS_SIGNAL;
		current_signal_p = signal_p;
	}
	else if(strcmp(tag_name, "property") == 0){
		struct dbus_property * property_p;

		if(tag_status < PARSE_TAG_STATUS_INTERFACE) {
			dbus_printf("Error property_p information. Skip!\n");
			return;
		}
		property_p = (struct dbus_property *)malloc(sizeof(struct dbus_property));
		if( !property_p ) {
			dbus_printf("failed to alloc struct dbus_property memory\n");
			return;
		}
		memset(property_p, 0, sizeof(struct dbus_property));
		property_p->introspect_has_property = false;
		property_p->case_property_has_value = 0;//Notes:.... always false in xml
		property_p->case_property_set_value = 0;//Notes:.... always false in xml
		property_p->notification = false;
		property_p->case_property_has_min=false;
		property_p->case_property_has_max=false;
		if(attr_name != NULL) {
			property_p->name = (char *)malloc(strlen(attr_name) + 1);
			if(property_p->name != NULL)
				strcpy(property_p->name, attr_name);
		}
		if( attr_access )
			strcpy(property_p->access, attr_access);

		if( attr_notification )
			if((g_strcmp0(attr_notification, "y") == 0))
				property_p->notification = true;

		if( attr_type ) {
			strcpy(property_p->type, attr_type);
			if(attr_value != NULL && attr_access != NULL &&
					((g_strcmp0(attr_access, "write") == 0)||(g_strcmp0(attr_access, "readwrite") == 0)))
			{
				str_to_variant_value(&property_p->value, attr_type, attr_value);
				property_p->case_property_has_value |= 0x1;
			}
			if(attr_value2 != NULL && attr_access != NULL &&
					((g_strcmp0(attr_access, "write") == 0)||(g_strcmp0(attr_access, "readwrite") == 0)))
			{
				str_to_variant_value(&property_p->value2, attr_type, attr_value2);
				property_p->case_property_has_value |= 0x2;
			}
			if(attr_value_bad != NULL && attr_access != NULL &&
					((g_strcmp0(attr_access, "write") == 0)||(g_strcmp0(attr_access, "readwrite") == 0)))
				str_to_variant_value(&property_p->value_bad, attr_type, attr_value_bad);
		}

		if( attr_min ) {
			if(attr_type != NULL)
			{
				str_to_variant_value(&property_p->min, attr_type, attr_min);
				property_p->case_property_has_min=true;
			}
		}

		if( attr_max ) {
			if(attr_type != NULL)
			{
				str_to_variant_value(&property_p->max, attr_type, attr_max);
				property_p->case_property_has_max=true;
			}
		}

		list_add_tail(&current_interface_p->property_list, &property_p->list);
		tag_status = PARSE_TAG_STATUS_PROPERTY;
	}

}

static void dbus_case_end_tag(void *data, const XML_Char *tag_name)
{
	data;
	tag_name;
}

int  dbus_case_xml_init()
{
	XML_Parser parser;
	FILE *file;
	int bytes_read;
	void *buf;
	int ret = 0;
	dbus_printf("dbus_case_xml_init\n");
	file = fopen(xml_case_bak_path, "r");

	if (!file) {
		dbus_printf("Failed to open %s\n", xml_case_bak_path);
		ret = -1;
		return ret;
	}

	parser = XML_ParserCreate(NULL);

	if (!parser) {
		dbus_printf("Failed to create XML parser\n");
		ret = -1;
		goto err_parser_create;
	}
	list_init(&dbus_case_list);
	XML_SetUserData(parser, &dbus_case_list);
	XML_SetElementHandler(parser, dbus_case_start_tag, dbus_case_end_tag);
	//XML_SetElementHandler(parser, start_tag, dbus_case_end_tag);

	for (;;) {
		buf = XML_GetBuffer(parser, BUF_SIZE);
		if (buf == NULL) {
			dbus_printf("failed to get XML buffer\n");
            ret = -1;
			goto err_parse;
		}

		bytes_read = fread(buf, 1, BUF_SIZE, file);

		if (bytes_read < 0) {
			dbus_printf("failed to read file\n");
            ret = -1;
			goto err_parse;
		}

		if (XML_ParseBuffer(parser, bytes_read,
					bytes_read == 0)== XML_STATUS_ERROR) {
			dbus_printf("Error in xml (%s)\n", xml_case_bak_path);
           		 ret = -1;
			goto err_parse;
		}
		if (bytes_read == 0)
			break;
	}

	
	struct listnode *dbus_case_item_p;
	struct listnode *obj_list_item_p;
	struct listnode *interface_list_item_p;
	struct listnode *method_list_item_p;
	struct listnode *signal_list_item_p;
	struct listnode *property_list_item_p;
	struct listnode *arg_list_item_p;
#if DEBUG
	dbus_printf("\n\n");
	list_for_each(dbus_case_item_p, &dbus_case_list) {
		struct dbus_case *dbus_case_p;
		dbus_case_p = node_to_item(dbus_case_item_p, struct dbus_case, list);
		dbus_printf("case name: %s\n", dbus_case_p->name);
		list_for_each(obj_list_item_p, &dbus_case_p->object_list) {
		struct dbus_object *dbus_object_p;

		dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
		dbus_printf("###node name: %s\n", dbus_object_p->name);
		list_for_each(interface_list_item_p, &dbus_object_p->interface_list) {
			struct dbus_interface *interface_p =
				node_to_item(interface_list_item_p,
						struct dbus_interface, list);

			dbus_printf("\tinterface name: %s\n", interface_p->name);
			list_for_each(method_list_item_p, &interface_p->method_list) {
				struct dbus_method *method_p =
					node_to_item(method_list_item_p,
							struct dbus_method, list);

				dbus_printf("\t\tmethod name: %s\n", method_p->name);
				list_for_each(arg_list_item_p, &method_p->arg_list) {
					struct dbus_method_arg *arg_item_p =
						node_to_item(arg_list_item_p,
								struct dbus_method_arg, list);
					if(g_strcmp0(arg_item_p->type,"s")!=0)
					dbus_printf("\t\t\targ name:%s type:%s value:%d\n",
					arg_item_p->name, arg_item_p->type, arg_item_p->value);
					else
					dbus_printf("\t\t\targ name:%s type:%s value:%s\n",
					arg_item_p->name, arg_item_p->type, arg_item_p->value.path_str);
				}
			}

			list_for_each(signal_list_item_p, &interface_p->signal_list) {
				struct dbus_signal *signal_p =
					node_to_item(signal_list_item_p,
							struct dbus_signal, list);

				dbus_printf("\t\tsignal name: %s\n", signal_p->name);
				list_for_each(arg_list_item_p, &signal_p->arg_list) {
					struct dbus_signal_arg *arg_item_p =
						node_to_item(arg_list_item_p,
								struct dbus_signal_arg, list);

					dbus_printf("\t\t\targ name:%s type:%s direction:%s\n",
					arg_item_p->name, arg_item_p->type, arg_item_p->direction);
				}
			}

			list_for_each(property_list_item_p, &interface_p->property_list) {
				struct dbus_property *property_p =
					node_to_item(property_list_item_p,
							struct dbus_property, list);
				if(g_strcmp0(property_p->type,"s")!=0)
				dbus_printf("\t\tproperty name:%s type:%s value:%d\n",
						property_p->name, property_p->type, property_p->value);
				else
								dbus_printf("\t\tproperty name:%s type:%s value:%s\n",
						property_p->name, property_p->type, property_p->value);
			}
		}
	}
}

       #endif
err_parse:
	XML_ParserFree(parser);
err_parser_create:
	fclose(file);

	return ret;
}

void method_sync(struct dbus_interface *case_interface_p,struct dbus_interface *interface_p)
{
	struct listnode *property_list_item_p;
	struct listnode *method_list_item_p;
	struct listnode *case_method_list_item_p;
	struct listnode *arg_list_item_p;
	struct listnode *case_arg_list_item_p;

	list_for_each(method_list_item_p, &interface_p->method_list) {
		struct dbus_method *method_p =node_to_item(method_list_item_p,	struct dbus_method, list);
		if(method_p==NULL)
			continue;

		list_for_each(case_method_list_item_p, &case_interface_p->method_list) {
			struct dbus_method *case_method_p = node_to_item(case_method_list_item_p, struct dbus_method, list);
			if(g_strcmp0(method_p->name, case_method_p->name)!=0)
				continue;

			//dbus_printf(" sync..... method name: %s\n", method_p->name);

			list_for_each(arg_list_item_p, &method_p->arg_list) {
				struct dbus_method_arg *arg_item_p = node_to_item(arg_list_item_p, struct dbus_method_arg, list);
					
				list_for_each(case_arg_list_item_p, &case_method_p->arg_list) {
					struct dbus_method_arg *case_arg_item_p = node_to_item(case_arg_list_item_p, struct dbus_method_arg, list);
					if(g_strcmp0(arg_item_p->name, case_arg_item_p->name)!=0)
						continue;
					if(case_arg_item_p->case_method_arg_has_value)
					{
						arg_item_p->value=case_arg_item_p->value;
						arg_item_p->value2=case_arg_item_p->value2;
						arg_item_p->case_method_arg_has_value=true;
					}
					/*if(g_strcmp0(arg_item_p->type,"s")!=0)
						dbus_printf("     arg name:%s type:%s value:%d\n",
						arg_item_p->name, arg_item_p->type, arg_item_p->value);
					else
						dbus_printf("      arg name:%s type:%s value:%s\n",
						arg_item_p->name, arg_item_p->type, arg_item_p->value.path_str);*/


				}

			}
		}
	}
}

void interface_delete_property(struct dbus_interface *interface_p, char* property_name)
{
	struct listnode *property_list_item_p;
	struct listnode *case_property_list_item_p;
	struct dbus_property *property_p;
	struct dbus_property *case_property_p;

	if(property_name==NULL)
		return;
	list_for_each(property_list_item_p, &interface_p->property_list) {
		property_p = node_to_item(property_list_item_p, struct dbus_property, list);
		if(property_p==NULL)
			continue;
		/*list_for_each(case_property_list_item_p, &case_interface_p->property_list) {
			case_property_p = node_to_item(case_property_list_item_p, struct dbus_property, list);
			if(case_property_p==NULL)
				continue;*/
			if(strcmp(property_name, property_p->name)==0)
			{
				dbus_printf("   Remove the property %s.%s\n",interface_p->name, property_name);
				list_remove(&property_p->list);
				free(property_p);
				property_p=NULL;
				return;
			}
		//}
	}

}

void object_delete(char* object_name, char* property_name)
{

	struct listnode *obj_list_item_p;
	//struct listnode *case_obj_list_item_p;
	struct listnode *interface_list_item_p;

	//struct dbus_object *case_object_list;
	struct dbus_object *object_list;
	//struct listnode *dbus_case_item_p;
	/*list_for_each(dbus_case_item_p, &dbus_case_list) {
		struct dbus_case *dbus_case_p;
		dbus_case_p = node_to_item(dbus_case_item_p, struct dbus_case, list);
		list_for_each(case_obj_list_item_p, &dbus_case_p->object_list) {
		        case_object_list = node_to_item(case_obj_list_item_p, struct dbus_object, list);
			if(case_object_list == NULL)
				continue;*/
	if(object_name==NULL)
		return;
	if(property_name==NULL)
		return;
		        list_for_each(obj_list_item_p, &dbus_list) {
		                object_list = node_to_item(obj_list_item_p, struct dbus_object, list);
				if(object_list ==NULL)
					continue;
		                if(strcmp(object_list->name, object_name)!=0)
		                {
		                        if(object_list->form_name!=NULL)
		                        {
		                                if(g_strcmp0(object_list->form_name, object_name) == 0)
		                                {
							list_for_each(interface_list_item_p, &object_list->interface_list){
								struct dbus_interface* object_interface_p = node_to_item(interface_list_item_p,
					                                                struct dbus_interface, list);
								if(object_interface_p==NULL)
									continue;
								interface_delete_property(object_interface_p, property_name);
							}

		                                }
		                        }
		                        continue;
		                }
				else
				{

					list_for_each(interface_list_item_p, &object_list->interface_list){
						struct dbus_interface* object_interface_p = node_to_item(interface_list_item_p,
			                                                struct dbus_interface, list);
						if(object_interface_p==NULL)
							continue;
						interface_delete_property(object_interface_p, property_name);
					}

				}
		        }
		        //dbus_printf("can't find the object %s\n",object_name);
	/*	}
	}*/
}

void propertys_sync(struct dbus_interface *case_interface_p,struct dbus_interface *interface_p)
{
	struct listnode *property_list_item_p;
	struct listnode *case_property_list_item_p;
	struct dbus_property *property_p;
	struct dbus_property *case_property_p;

	list_for_each(property_list_item_p, &interface_p->property_list) {
		property_p = node_to_item(property_list_item_p, struct dbus_property, list);
		if(property_p==NULL)
			continue;
		list_for_each(case_property_list_item_p, &case_interface_p->property_list) {
			case_property_p = node_to_item(case_property_list_item_p, struct dbus_property, list);
			if(case_property_p==NULL)
				continue;
			if(strcmp(case_property_p->name, property_p->name)==0)
			{
				property_p->case_property_has_value = case_property_p->case_property_has_value;
				property_p->case_property_set_value = case_property_p->case_property_set_value;
				property_p->value= case_property_p->value;
				property_p->value2= case_property_p->value2;
//dbus_printf("owen ===== 0x%x, 0x%x %s\n", property_p->case_property_has_value,case_property_p->case_property_has_value,case_property_p->name);
			}
		}
	}

}

void interfaces_sync(struct dbus_object* case_object_p, struct dbus_object* object_p)
{
	struct listnode *interface_list_item_p;
	struct listnode *case_interface_list_item_p;

	list_for_each(interface_list_item_p, &object_p->interface_list) {
		struct dbus_interface* object_interface_p = node_to_item(interface_list_item_p,
                                                struct dbus_interface, list);
		if(object_interface_p==NULL)
			continue;
		list_for_each(case_interface_list_item_p, &case_object_p->interface_list){
			struct dbus_interface* object_case_interface_p = node_to_item(case_interface_list_item_p,
                                                struct dbus_interface, list);
			if(object_case_interface_p==NULL)
				continue;
			if(strcmp(object_case_interface_p->name, object_interface_p->name)==0)
			{
				propertys_sync(object_case_interface_p,object_interface_p);
				method_sync(object_case_interface_p,object_interface_p);
			}
		}

	}

}



void object_sync()
{

	struct listnode *obj_list_item_p;
	struct listnode *case_obj_list_item_p;

	struct dbus_object *case_object_list;
	struct dbus_object *object_list;
	struct listnode *dbus_case_item_p;
	list_for_each(dbus_case_item_p, &dbus_case_list) {
		struct dbus_case *dbus_case_p;
		dbus_case_p = node_to_item(dbus_case_item_p, struct dbus_case, list);
		list_for_each(case_obj_list_item_p, &dbus_case_p->object_list) {
		        case_object_list = node_to_item(case_obj_list_item_p, struct dbus_object, list);
			if(case_object_list == NULL)
				continue;
		        list_for_each(obj_list_item_p, &dbus_list) {
		                object_list = node_to_item(obj_list_item_p, struct dbus_object, list);
				if(object_list ==NULL)
					continue;
		                if(strcmp(object_list->name, case_object_list->name)!=0)
		                {
		                        if(object_list->form_name!=NULL)
		                        {
		                                if(g_strcmp0(object_list->form_name, case_object_list->name) == 0)
		                                {
		                                        interfaces_sync(case_object_list, object_list);
		                                }
		                        }
		                        continue;
		                }
		                else
		                        interfaces_sync(case_object_list, object_list);
		        }
		        //dbus_printf("can't find the object %s\n",object_name);
		}
	}
}

static bool bWLAN_Devices_object_sync=false;
void WLAN_Devices_object_sync()
{

	struct listnode *obj_list_item_p;
	struct listnode *case_obj_list_item_p;

	struct dbus_object *case_object_list;
	struct dbus_object *case_object_2_4G_list=NULL;
	struct dbus_object *case_object_5G_list=NULL;
	struct dbus_object *object_list;
	struct listnode *dbus_case_item_p;

	if(bWLAN_Devices_object_sync==false)
	{
		bWLAN_Devices_object_sync=true;
	}
	else 
		return;
	list_for_each(dbus_case_item_p, &dbus_case_list) {
		struct dbus_case *dbus_case_p;
		dbus_case_p = node_to_item(dbus_case_item_p, struct dbus_case, list);
		list_for_each(case_obj_list_item_p, &dbus_case_p->object_list) {
		        case_object_list = node_to_item(case_obj_list_item_p, struct dbus_object, list);
			if(case_object_list == NULL)
				continue;

			if(strcmp("/com/ctc/igd1/Config/WLAN/Devices_2_4G/{i}", case_object_list->name)==0)
			{
				case_object_2_4G_list=case_object_list;
			}
			if(strcmp("/com/ctc/igd1/Config/WLAN/Devices_5G/{i}", case_object_list->name)==0)
			{
				case_object_5G_list=case_object_list;
			}
		        //dbus_printf("can't find the object %s\n",object_name);
		}
	}

	if(case_object_2_4G_list==NULL)
	{
		dbus_printf("/com/ctc/igd1/Config/WLAN/Devices_2_4G/{i} info error\n");
		//exit(0);
		return;
	}
	if(case_object_5G_list==NULL)
	{
		dbus_printf("/com/ctc/igd1/Config/WLAN/Devices_5G/{i} info error\n");
		//exit(0);
		return;
	}
		        list_for_each(obj_list_item_p, &dbus_list) {
		                object_list = node_to_item(obj_list_item_p, struct dbus_object, list);
				if(object_list ==NULL)
					continue;
		                //if(strcmp(object_list->name, case_object_list->name)!=0)
		                {
		                        if(object_list->form_name!=NULL)
		                        {
		                                //if(g_strcmp0(object_list->form_name, case_object_list->name) == 0)
		                                {
		                                        //interfaces_sync(case_object_list, object_list);
							
							if(strcmp("/com/ctc/igd1/Config/WLAN/Devices/{i}", object_list->form_name)==0)
							{

								guint32 u2_4G_or_5G;
								u2_4G_or_5G=igd1_Get_2_4G_or_5G(object_list);
								if(u2_4G_or_5G==1)
								{
									dbus_printf("sync %s with 5G info\n",object_list->name);
									interfaces_sync(case_object_5G_list, object_list);
									object_delete(object_list->name, "Powerlevel");
								}
								else
								{
									dbus_printf("sync %s with 2.4G info\n",object_list->name);
									interfaces_sync(case_object_2_4G_list, object_list);
									object_delete(object_list->name, "PowerLevel_5G");
								}
							}
		                                }
		                        }
		                }
		        }
}









void method_property_signal_result_sync(struct dbus_interface *result_interface_p,struct dbus_interface *interface_p)
{
	struct listnode *property_list_item_p;
	struct listnode *method_list_item_p;
	struct listnode *result_method_list_item_p;
	struct listnode *arg_list_item_p;
	struct listnode *result_arg_list_item_p;

	list_for_each(method_list_item_p, &interface_p->method_list) {
		struct dbus_method *method_p =node_to_item(method_list_item_p,	struct dbus_method, list);
		if(method_p==NULL)
			continue;

		list_for_each(result_method_list_item_p, &result_interface_p->method_list) {
			struct dbus_method *result_method_p = node_to_item(result_method_list_item_p, struct dbus_method, list);
			if(g_strcmp0(method_p->name, result_method_p->name)!=0)
				continue;

			//dbus_printf(" sync..... method name: %s\n", method_p->name);
			result_method_p->test_result= method_p->test_result;
			list_for_each(arg_list_item_p, &method_p->arg_list) {
				struct dbus_method_arg *arg_item_p = node_to_item(arg_list_item_p, struct dbus_method_arg, list);
					
				list_for_each(result_arg_list_item_p, &result_method_p->arg_list) {
					struct dbus_method_arg *result_arg_item_p = node_to_item(result_arg_list_item_p, struct dbus_method_arg, list);
					//if(g_strcmp0(arg_item_p->name, result_arg_item_p->name)!=0)
					if(strstr(result_arg_item_p->name, arg_item_p->name)==NULL)
					{//For |xml_data
						continue;
					}
					result_arg_item_p->test_result= arg_item_p->test_result;
				}

			}
		}
	}

	{
	struct listnode *property_list_item_p;
	struct listnode *result_property_list_item_p;
	struct dbus_property *property_p;
	struct dbus_property *result_property_p;

	list_for_each(property_list_item_p, &interface_p->property_list) {
		property_p = node_to_item(property_list_item_p, struct dbus_property, list);
		if(property_p==NULL)
			continue;
		list_for_each(result_property_list_item_p, &result_interface_p->property_list) {
			result_property_p = node_to_item(result_property_list_item_p, struct dbus_property, list);
			if(result_property_p==NULL)
				continue;

			if(strcmp(result_property_p->name, property_p->name)==0)
			{
				result_property_p->test_result=property_p->test_result;
//dbus_printf("owen ===== 0x%x, 0x%x %s\n", property_p->result_property_has_value,result_property_p->result_property_has_value,result_property_p->name);
			}
		}
	}
	}



{
	struct listnode *property_list_item_p;
	struct listnode *signal_list_item_p;
	struct listnode *result_signal_list_item_p;
	struct listnode *arg_list_item_p;
	struct listnode *result_arg_list_item_p;

	list_for_each(signal_list_item_p, &interface_p->signal_list) {
		struct dbus_signal *signal_p =node_to_item(signal_list_item_p,	struct dbus_signal, list);
		if(signal_p==NULL)
			continue;

		list_for_each(result_signal_list_item_p, &result_interface_p->signal_list) {
			struct dbus_signal *result_signal_p = node_to_item(result_signal_list_item_p, struct dbus_signal, list);
			if(g_strcmp0(signal_p->name, result_signal_p->name)!=0)
				continue;

			//dbus_printf(" sync..... signal name: %s\n", signal_p->name);
			result_signal_p->test_result= signal_p->test_result;
			list_for_each(arg_list_item_p, &signal_p->arg_list) {
				struct dbus_signal_arg *arg_item_p = node_to_item(arg_list_item_p, struct dbus_signal_arg, list);
					
				list_for_each(result_arg_list_item_p, &result_signal_p->arg_list) {
					struct dbus_signal_arg *result_arg_item_p = node_to_item(result_arg_list_item_p, struct dbus_signal_arg, list);
					//if(g_strcmp0(arg_item_p->name, result_arg_item_p->name)!=0)
					if(strstr(result_arg_item_p->name, arg_item_p->name)==NULL)//For |xml_data
						continue;
					result_arg_item_p->test_result= arg_item_p->test_result;
					/*if(g_strcmp0(arg_item_p->type,"s")!=0)
						dbus_printf("     arg name:%s type:%s value:%d\n",
						arg_item_p->name, arg_item_p->type, arg_item_p->value);
					else
						dbus_printf("      arg name:%s type:%s value:%s\n",
						arg_item_p->name, arg_item_p->type, arg_item_p->value.path_str);*/


				}

			}
		}
	}
}



}


void interfaces_result_sync(struct dbus_object* result_object_p, struct dbus_object* object_p)
{
	struct listnode *interface_list_item_p;
	struct listnode *case_interface_list_item_p;
	result_object_p->test_result=object_p->test_result;

	list_for_each(interface_list_item_p, &object_p->interface_list) {
		struct dbus_interface* object_interface_p = node_to_item(interface_list_item_p,
                                                struct dbus_interface, list);
		if(object_interface_p==NULL)
			continue;
		list_for_each(case_interface_list_item_p, &result_object_p->interface_list){
			struct dbus_interface* object_result_interface_p = node_to_item(case_interface_list_item_p,
                                                struct dbus_interface, list);
			if(object_result_interface_p==NULL)
				continue;
			if(strcmp(object_result_interface_p->name, object_interface_p->name)==0)
			{
				//propertys_sync(object_case_interface_p,object_interface_p);
				//method_sync(object_case_interface_p,object_interface_p);
				object_result_interface_p->test_result=object_interface_p->test_result;
				method_property_signal_result_sync(object_result_interface_p,object_interface_p);
			}
		}

	}

}



void object_result_sync()
{

	struct listnode *obj_list_item_p;
	struct listnode *result_obj_list_item_p;

	struct dbus_object *result_object_list;
	struct dbus_object *object_list;
	struct listnode *dbus_case_item_p;
	list_for_each(result_obj_list_item_p, &dbus_result_list) {
	        result_object_list = node_to_item(result_obj_list_item_p, struct dbus_object, list);
		if(result_object_list == NULL)
			continue;
		char*p=result_object_list->name;
		int n;
		bool parent_object=false;
		for(n=0;n<strlen(result_object_list->name);n++)
		{
			if(*p=='{')
			{
				parent_object=true;
			}
			p++;
		}
		dbus_printf("  sync result for %s\n",result_object_list->name);	
		if(parent_object==false)
		{
		        list_for_each(obj_list_item_p, &dbus_list) {
		                object_list = node_to_item(obj_list_item_p, struct dbus_object, list);
				if(object_list ==NULL)
					continue;
		                if(strcmp(object_list->name, result_object_list->name)==0)
		                {
		                        interfaces_result_sync(result_object_list, object_list);
					break;
		                }
		        }
		}
		else{
			bool son_has_error=false;
			struct dbus_object *last_son_object_list=NULL;
		        list_for_each(obj_list_item_p, &dbus_list) {
		                object_list = node_to_item(obj_list_item_p, struct dbus_object, list);
				if(object_list ==NULL)
					continue;
				if(object_list->form_name!=NULL)
				{
		                	if(strcmp(object_list->form_name, result_object_list->name)==0)
		                	{
		                        	//interfaces_result_sync(result_object_list, object_list);
						last_son_object_list=object_list;
						if(object_list->test_result!=TEST_OK)
						{
							son_has_error=true;
							break;
						}
		                	}
				}
		        }

			if(last_son_object_list!=NULL)
			{//for example. some untest ddns...
				interfaces_result_sync(result_object_list, last_son_object_list);
				result_object_list->form_name=malloc(strlen(last_son_object_list->name)+1);
				if(result_object_list->form_name!=NULL)
					strcpy(result_object_list->form_name, last_son_object_list->name);
				//form_name == last_son name!!
			}
		}
	        //dbus_printf("can't find the object %s\n",object_name);
	}
}




int test_num=0;
static int current_test_num=0;
static int error_test_num=0;
static int ok_test_num=0;
void print_result(char* cmd, char* name, char* instance_name,  guint32 result, int space)
{
	int u = space;
	char* p = cmd;
	current_test_num++;
	if(strlen(name)>100)
	{
		dbus_printf("Name is too long!\n");
		sprintf(p," name too long!");	
		strncpy(p,name,80);
		p=cmd+strlen(cmd);
		*p++='\n';
		*p='\0';
		return;
		
	}
	for(u=space;u>0;u--)
	{
		sprintf(p,"   ");
		//p=cmd+strlen(cmd)-1;
		p+=3;
	}
	if(instance_name==NULL)
		sprintf(p,"<%d/%d>%s: %s[0x%x]  ",current_test_num,test_num,name,(result==TEST_OK)?"OK.":"Failed. Reason:",result);
	else
		sprintf(p,"<%d,%d>%s form [%s]: %s[0x%x]  ",current_test_num,test_num,name,instance_name,(result==TEST_OK)?"OK.":"Failed. Reason:",result);
	if(result==TEST_OK)
	{
		ok_test_num++;
	}
	if(result & NO_INTERFACE){
		p=cmd+strlen(cmd);
		sprintf(p," NO_INTERFACE");
	}
	
	if(result & NEW_INTERFACE){
		p=cmd+strlen(cmd);
		sprintf(p," NEW_INTERFACE");
	}

	if(result & NO_PROPERTY){
		p=cmd+strlen(cmd);
		sprintf(p," NO_PROPERTY");
	}
	if(result & PROPERTY_WRONG_TYPE){
		p=cmd+strlen(cmd);
		sprintf(p," PROPERTY_WRONG_TYPE");
	}
	if(result & PROPERTY_WRONG_ACCESS){
		p=cmd+strlen(cmd);
		sprintf(p," PROPERTY_WRONG_ACCESS");
	}

	if(result &  PROPERTY_WRONG_ACCESS){
		p=cmd+strlen(cmd);
		sprintf(p," PROPERTY_WRONG_ACCESS");
	}
	if(result & PROPERTY_WRONG_NOTIFICATION ){
		p=cmd+strlen(cmd);
		sprintf(p," PROPERTY_WRONG_NOTIFICATION");
	}
	if(result & PROPERTY_GET_SET_TIMEOUT){
		p=cmd+strlen(cmd);
		sprintf(p," PROPERTY_TIMEOUT");
	}
	if(result & PROPERTY_CANT_GET_OR_GETALL ){
		p=cmd+strlen(cmd);
		sprintf(p," PROPERTY_CANT_GET_OR_GETALL");
	}
	if(result & PROPERTY_CANT_SET_OR_SETMULTI ){
		p=cmd+strlen(cmd);
		sprintf(p," PROPERTY_CANT_SET_OR_SETMULTI");
	}
	if(result & NULL_OBJECT_BY_METHOD_CALL ){
		p=cmd+strlen(cmd);
		sprintf(p," NULL_OBJECT_BY_METHOD_CALL");
	}

	if(result & PROPERTY_SET_GET_NOT_EQUAL ){
		p=cmd+strlen(cmd);
		sprintf(p," PROPERTY_SET_GET_NOT_EQUAL");
	}

	if(result & PROPERTY_WRONG_NAME){
		p=cmd+strlen(cmd);
		sprintf(p," PROPERTY_WRONG_NAME");
	}


	if(result & NEW_PROPERTY ){
		p=cmd+strlen(cmd);
		sprintf(p," NEW_PROPERTY");
	}

	if(result & NEW_METHOD ){
		p=cmd+strlen(cmd);
		sprintf(p," NEW_METHOD");
	}
	if(result & NO_METHOD ){
		p=cmd+strlen(cmd);
		sprintf(p," NO_METHOD");
	}
	if(result &  NO_METHOD_ARG){
		p=cmd+strlen(cmd);
		sprintf(p," NO_METHOD_ARG");
	}

	if(result & NEW_METHOD_ARG ){
		p=cmd+strlen(cmd);
		sprintf(p," NEW_METHOD_ARG");
	}
	if(result &  METHOD_CANT_CALL){
		p=cmd+strlen(cmd);
		sprintf(p," METHOD_CANT_CALL");
	}
	if(result & NO_SIGNAL_ARG ){
		p=cmd+strlen(cmd);
		sprintf(p," NO_SIGNAL_ARG");
	}
	if(result & NEW_SIGNAL_ARG ){
		p=cmd+strlen(cmd);
		sprintf(p," NEW_SIGNAL_ARG");
	}

	if(result & NO_RECIVE_SIGNAL ){
		p=cmd+strlen(cmd);
		sprintf(p," NO_RECIVE_SIGNAL");
	}
	if(result & NULL_PARAM ){
		p=cmd+strlen(cmd);
		sprintf(p," NULL_PARAM");
	}

	if(result & NO_SIGNAL ){
		p=cmd+strlen(cmd);
		sprintf(p," NO_SIGNAL");
	}
	if(result &  PROPERTY_SETMUL_GETALL_TIMEOUT){
		p=cmd+strlen(cmd);
		sprintf(p," PROPERTY_TIMEOUT");
	}

	if(result &  METHOD_CALL_FAIL){
		p=cmd+strlen(cmd);
		sprintf(p," METHOD_CALL_FAIL");
	}

	if(result & METHOD_CALL_TIMEOUT ){
		p=cmd+strlen(cmd);
		sprintf(p," METHOD_CALL_TIMEOUT");
	}
	if(result &  RANGE_ERROR){
		p=cmd+strlen(cmd);
		sprintf(p," RANGE_ERROR");
	}
	if(result &  METHOD_ARG_NO_VALUE){
		p=cmd+strlen(cmd);
		sprintf(p," METHOD_ARG_NO_VALUE");
	}
	if(result &  PROPERTY_NO_VALUE){
		p=cmd+strlen(cmd);
		sprintf(p," PROPERTY_NO_VALUE");
	}
	if(result &  CONNECTION_CLOSED){
		p=cmd+strlen(cmd);
		sprintf(p," CONNECTION_CLOSED");
	}
	if(result &  CONNECTION_NULL){
		p=cmd+strlen(cmd);
		sprintf(p," CONNECTION_NULL");
	}
	if(result &  UNPASS){
		p=cmd+strlen(cmd);
		sprintf(p," UNPASS");
	}

	//*p++='\n';
	p=cmd+strlen(cmd);
	*p++='\n';
	*p='\0';
	
}	

int dbus_test_result( void )
{
	XML_Parser parser;
	FILE *file;
	int bytes_read;
	void *buf;
	int ret = 0;
#if 1//DEBUG
	struct listnode *obj_list_item_p;
	struct listnode *interface_list_item_p;
	struct listnode *method_list_item_p;
	struct listnode *signal_list_item_p;
	struct listnode *property_list_item_p;
	struct listnode *arg_list_item_p;
#endif

	file = fopen(noinstance_xml_path, "r");
	if (!file) {
		dbus_printf("Failed to open %s\n", noinstance_xml_path);
		ret = -1;
		return ret;
	}

	parser = XML_ParserCreate(NULL);

	if (!parser) {
		dbus_printf("Failed to create XML parser\n");
		ret = -1;
		goto err_parser_create;
	}
	list_init(&dbus_result_list);
	XML_SetUserData(parser, &dbus_result_list);
	init_result = UNPASS;
	XML_SetElementHandler(parser, start_tag, end_tag);

	for (;;) {
		buf = XML_GetBuffer(parser, BUF_SIZE);
		if (buf == NULL) {
			dbus_printf("failed to get XML buffer\n");
            ret = -1;
			goto err_parse;
		}

		bytes_read = fread(buf, 1, BUF_SIZE, file);

		if (bytes_read < 0) {
			dbus_printf("failed to read file\n");
            ret = -1;
			goto err_parse;
		}

		if (XML_ParseBuffer(parser, bytes_read,
					bytes_read == 0)== XML_STATUS_ERROR) {
			dbus_printf("Error in xml (%s)\n", noinstance_xml_path);
            ret = -1;
			goto err_parse;
		}
		if (bytes_read == 0)
			break;
	}

	if(access(result_file,0)==0)
	{
		dbus_printf("\n    Delete the result file %s\n", result_file);
                remove(result_file);
	}
	object_result_sync();

        FILE *fp;
        int rc = 0;
        fp = fopen(result_file, "a+");
	if(fp){

#if 1//DEBUG
	dbus_printf("\n\n");

	int num = 0;
	int o_num = 0;
	list_for_each(obj_list_item_p, &dbus_result_list) {
		struct dbus_object *dbus_object_p;
		num++;

		dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
		test_num++;

		list_for_each(interface_list_item_p, &dbus_object_p->interface_list) {
			struct dbus_interface *interface_p =
				node_to_item(interface_list_item_p,
						struct dbus_interface, list);
			if(interface_p==NULL)
			{
				continue;
			}
			test_num++;
			list_for_each(method_list_item_p, &interface_p->method_list) {
				struct dbus_method *method_p =
					node_to_item(method_list_item_p,
							struct dbus_method, list);
				test_num++;
				list_for_each(arg_list_item_p, &method_p->arg_list) {
					struct dbus_method_arg *arg_item_p =
						node_to_item(arg_list_item_p,
								struct dbus_method_arg, list);
					test_num++;
				}
			}

			list_for_each(signal_list_item_p, &interface_p->signal_list) {
				struct dbus_signal *signal_p =
					node_to_item(signal_list_item_p,
							struct dbus_signal, list);

				test_num++;
	
				list_for_each(arg_list_item_p, &signal_p->arg_list) {
					struct dbus_signal_arg *arg_item_p =
						node_to_item(arg_list_item_p,
								struct dbus_signal_arg, list);
					test_num++;
				}
			}

			list_for_each(property_list_item_p, &interface_p->property_list) {
				struct dbus_property *property_p =
					node_to_item(property_list_item_p,
							struct dbus_property, list);
				test_num++;
			}
		}

	}






	list_for_each(obj_list_item_p, &dbus_result_list) {
		struct dbus_object *dbus_object_p;

		dbus_object_p = node_to_item(obj_list_item_p, struct dbus_object, list);
		if(dbus_object_p==NULL){
			dbus_printf("NULL2222\n");
			continue;
		}
		char obj_num[30]={0};
		o_num++;
		sprintf(obj_num,"\n\n[current obj %d/ sum obj %d]\n",o_num,num);
		fwrite(obj_num, 1, strlen(obj_num), fp);

		char n_cmd[300]={0};
		print_result(n_cmd,dbus_object_p->name,dbus_object_p->form_name, dbus_object_p->test_result,0);
		//dbus_printf("###node name: %s\n", dbus_object_p->name);
		fwrite(n_cmd, 1, strlen(n_cmd), fp);
		list_for_each(interface_list_item_p, &dbus_object_p->interface_list) {
			struct dbus_interface *interface_p =
				node_to_item(interface_list_item_p,
						struct dbus_interface, list);

			//dbus_printf("\tinterface name: %s\n", interface_p->name);
			char i_cmd[300]={0};
			print_result(i_cmd,interface_p->name,NULL, interface_p->test_result,1);
			fwrite(i_cmd, 1, strlen(i_cmd), fp);
			//dbus_printf("\tinterface name: %s\n", i_cmd);
			list_for_each(method_list_item_p, &interface_p->method_list) {
				struct dbus_method *method_p =
					node_to_item(method_list_item_p,
							struct dbus_method, list);

				//dbus_printf("\t\tmethod name: %s\n", method_p->name);
				char m_cmd[300]={0};
				print_result(m_cmd,method_p->name,NULL, method_p->test_result,2);
				fwrite(m_cmd, 1, strlen(m_cmd), fp);
				list_for_each(arg_list_item_p, &method_p->arg_list) {
					struct dbus_method_arg *arg_item_p =
						node_to_item(arg_list_item_p,
								struct dbus_method_arg, list);

					//dbus_printf("\t\t\targ name:%s type:%s direction:%s\n",
					//arg_item_p->name, arg_item_p->type, arg_item_p->direction);
					char ma_cmd[300]={0};
					print_result(ma_cmd,arg_item_p->name,NULL, arg_item_p->test_result,3);
					fwrite(ma_cmd, 1, strlen(ma_cmd), fp);
				}
			}

			list_for_each(signal_list_item_p, &interface_p->signal_list) {
				struct dbus_signal *signal_p =
					node_to_item(signal_list_item_p,
							struct dbus_signal, list);

				//dbus_printf("\t\tsignal name: %s\n", signal_p->name);
				char s_cmd[300]={0};
				print_result(s_cmd,signal_p->name,NULL,signal_p->test_result,2);
				fwrite(s_cmd, 1, strlen(s_cmd), fp);
	
				list_for_each(arg_list_item_p, &signal_p->arg_list) {
					struct dbus_signal_arg *arg_item_p =
						node_to_item(arg_list_item_p,
								struct dbus_signal_arg, list);

					//dbus_printf("\t\t\targ name:%s type:%s direction:%s\n",
					//arg_item_p->name, arg_item_p->type, arg_item_p->direction);
					char sa_cmd[300]={0};
					print_result(sa_cmd,arg_item_p->name,NULL, arg_item_p->test_result,3);
					fwrite(sa_cmd, 1, strlen(sa_cmd), fp);
				}
			}

			list_for_each(property_list_item_p, &interface_p->property_list) {
				struct dbus_property *property_p =
					node_to_item(property_list_item_p,
							struct dbus_property, list);

				//dbus_printf("\t\tproperty name:%s type:%s access:%s\n",
				//		property_p->name, property_p->type, property_p->access);

				char p_cmd[300]={0};
				print_result(p_cmd,property_p->name,NULL,property_p->test_result,2);
				fwrite(p_cmd, 1, strlen(p_cmd), fp);
			}
		}

	}
	char end_result[30]={0};
	sprintf(end_result,"End.\nTest %d , ok %d, failed %d\n#####\n#####\n",test_num,ok_test_num,(test_num-ok_test_num));
	fwrite(end_result, 1, strlen(end_result), fp);


	fclose(fp);
	}
#endif
	err_parse:
		XML_ParserFree(parser);
	err_parser_create:
		fclose(file);
	
	return ret;
}
