#include "dbus_xml_parse.h"
#include "dbus_log.h"
#include <gio/gio.h>  
#include "list.h"
extern bool redundancy;
void dbus_g_value_variant_get_all(struct dbus_interface *dbus_interface_list, 
					struct dbus_object *dbus_object_list, 
				struct dbus_property * dbus_property_list,GVariant *value)
{
	GVariant *info = NULL;	
	gchar *key = NULL;	
	gchar *str_val = NULL;	
	guint16 uint16_val;
	gint16  int16_val;
	gint32  int32_val;
	guint32 uint32_val;
	gint64  int64_val;
	guint64 uint64_val;	
	gchar   byte_val;
	gdouble double_val;
	gboolean bol_val;

	//dbus_printf("@@ %s,%s\n",dbus_property_list->name,dbus_property_list->type);


	if(! (g_variant_is_of_type (value, G_VARIANT_TYPE(dbus_property_list->type))))
	{
		dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s:%s but not:%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","Failed","Type must be",dbus_property_list->type,g_variant_get_type_string(value),__func__, g_variant_get_type_string(value));
		return;
	}
	if(value !=NULL)
	{
		if(0==g_strcmp0(dbus_property_list->type,"s")){
       			g_variant_get(value, "s", &str_val); 
			//dbus_printf ("property name : %s  , %s\n ",dbus_property_list->name,str_val);
			dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value", __func__,str_val);
			dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value", __func__,str_val);
			//Notes: for special % char
		}
		else if(0==g_strcmp0(dbus_property_list->type,"o")){
			g_variant_get(value, "o", &str_val); 
			//dbus_printf ("property name : %s  , %s\n ",dbus_property_list->name,str_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value",__func__,str_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type,"g")){
		
			g_variant_get(value, "g", &str_val); 
			//dbus_printf ("property name : %s  , %s\n ",dbus_property_list->name,str_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value",__func__,str_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type, "b")){
		
			g_variant_get(value, "b", &byte_val);
			//dbus_printf ("property name : %s  , %d\n ",dbus_property_list->name,byte_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value", __func__,byte_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type, "y")){
	
			g_variant_get(value, "y", &byte_val);
			//dbus_printf ("property name : %s  , %d\n ",dbus_property_list->name,byte_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value",__func__,byte_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type, "n")){
		
			g_variant_get(value, "n", &int16_val);
			//dbus_printf ("property name : %s  , %d\n ",dbus_property_list->name,int16_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value",__func__,int16_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type, "q")){
		
			g_variant_get(value, "q", &uint16_val);
			//dbus_printf ("property name : %s  , %d\n ",dbus_property_list->name,uint16_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value",__func__,uint16_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type, "i")){
		
			g_variant_get(value, "i", &int32_val);
			//dbus_printf ("property name : %s  , %d\n ",dbus_property_list->name,int32_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value",__func__,int32_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type, "u")){
		
			g_variant_get(value, "u", &uint32_val);
			//dbus_printf ("property name : %s  , %d\n ",dbus_property_list->name,uint32_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value",__func__,uint32_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type, "x")){
		
			g_variant_get(value, "x", &int64_val);
			//dbus_printf ("property name : %s  , %ld\n ",dbus_property_list->name,int64_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%lld\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value",__func__,int64_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type, "t")){
	
			g_variant_get(value, "t", &uint64_val);
			//dbus_printf ("property name : %s  , %lld\n ",dbus_property_list->name,uint64_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%llu\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value",__func__,uint64_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type, "h")){
	
			g_variant_get(value, "h", &uint32_val);
			//dbus_printf ("property name : %s  , %d\n ",dbus_property_list->name,uint32_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value",__func__,uint32_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type, "d")){

			g_variant_get(value, "d", &double_val);
			//dbus_printf ("property name : %s  , %lf\n ",dbus_property_list->name,double_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%lf\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value",__func__,double_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type, "as")){
#if 1
		        if(g_variant_is_of_type (value, G_VARIANT_TYPE ("(v)")))   
		        {
		            GVariant * wps_devparse_info = NULL;
		            GVariantIter *iter = NULL;
		            gchar * parse_info = NULL;
		            g_variant_get (value, "(v)", &wps_devparse_info);
		            g_variant_get(wps_devparse_info, "as", &iter);
		            //g_variant_get(value, "s", &iter);
		            //gsize size;
		            //g_variant_get_strv (str_out, &size);
		            dbus_printf("as type data warp with (v)\n");
			    if(iter==NULL)
		                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name,"","","","OK","Get the value  ",__func__,"");
			    else{
		                while (g_variant_iter_next (iter, "s", &parse_info))
		                {
		                    //dbus_printf("   Device Info: %s\n", parse_info);  //add your customizaition code
		                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name,"","","","OK","Get the value  ",__func__,parse_info);
		                    g_free(parse_info);
		                }
		    
		                g_variant_unref(wps_devparse_info);
		                g_variant_iter_free (iter);
		            }
		        }
			else
		        {
		            GVariant * wps_devparse_info = NULL;
		            GVariantIter *iter = NULL;
		            gchar * parse_info = NULL;
		
		            dbus_printf("as type data not warp with (v)\n");
		            //g_variant_get (value, "(v)", &wps_devparse_info);
		            //g_variant_get(wps_devparse_info, "as", &iter);
		            //g_variant_get(value, "s", &iter);
		            g_variant_get(value, "as", &iter);
			    if(iter==NULL)
		                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name,"","","","OK","Get the value  ",__func__,"");
			    else{
		                while (g_variant_iter_next (iter, "s", &parse_info))
		                {
		                    //dbus_printf("   Device Info: %s\n", parse_info);  //add your customizaition code
		                    dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name,"","","","OK","Get the value  ",__func__,parse_info);
		                    g_free(parse_info);
		                }
		    
		                //g_variant_unref(wps_devparse_info);
		                g_variant_iter_free (iter);
		            }
		        }

#endif

#if 0//Pass in Tongwei
		        //if(g_variant_is_of_type (value, G_VARIANT_TYPE ("(v)")))
		        {
		            GVariant * wps_devparse_info = NULL;
		            GVariantIter *iter = NULL;
		            gchar * parse_info = NULL;
		            //g_variant_get (value, "(v)", &wps_devparse_info);
		            //g_variant_get(wps_devparse_info, "as", &iter);
		            g_variant_get(value, "s", &iter);
		            if(iter==NULL)
		                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name,"","","","OK","Get the value  ",__func__,"NULL");
			    else{
	    		            while (g_variant_iter_next (iter, "s", &parse_info))
	    		            {
	    		                //dbus_printf("   Device Info: %s\n", parse_info);  //add your customizaition code
	    		                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name,"","","","OK","Get the value  ",__func__,parse_info);
	    		                g_free(parse_info);
	    		            }
	    		
	    		            g_variant_unref(wps_devparse_info);
	    		            g_variant_iter_free (iter);
                            }
		        }
#endif
	/*		GVariantIter *iter;
			g_variant_get (value, "(as)", &iter);
			while (g_variant_iter_loop (iter, "s", &str_val)){
				//dbus_printf ("property name :string , %s\n ",str_val);
				dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","GetAll the property value",__func__,str_val);
			}
			g_variant_iter_free (iter);*/
		}
		else{
			//g_print ("Result type = %s, %s\n", g_variant_get_type_string(value), g_variant_print (value, TRUE));
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","Failed","Unknown type ..",__func__,"");
			//g_variant_get(result, "s", &str_val);
			//dbus_printf ("type other = %s\n",(gchar *) str_val);
		}
	}
	
}
void *dbus_g_value_variant_get(struct dbus_interface *dbus_interface_list ,
                               struct dbus_object *dbus_object_list,
				struct dbus_property * dbus_property_list,GVariant *value)
{
	GVariant *info = NULL;	
	gchar *key = NULL;	
	gchar *str_val = NULL;	
	guint16 uint16_val;
	gint16  int16_val;
	gint32  int32_val;
	guint32 uint32_val;
	gint64  int64_val;
	guint64 uint64_val;	
	gchar   byte_val;
	gdouble double_val;
	gboolean bol_val;

	//g_print ("Result type = %s, %s\n", g_variant_get_type_string(value), g_variant_print (value, TRUE));

	g_variant_get(value, "(v)", &info);
	if(!g_variant_is_of_type (info, G_VARIANT_TYPE (dbus_property_list->type)))
	{
		dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s:%s but not:%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","Failed","Type must be",dbus_property_list->type,g_variant_get_type_string(info),__func__, g_variant_get_type_string(info));
		return;
	}
	if(value !=NULL)
	{
		if(0==g_strcmp0(dbus_property_list->type,"s")){
			g_variant_get(value, "(v)", &info);
         		g_variant_get(info, "s", &str_val); 
			//dbus_printf ("property name : %s  , %s\n ",dbus_property_list->name,str_val);
			dbus_printf("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","Get value",__func__,str_val);
			dbus_printf_logfile("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","Get value",__func__,str_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type,"o")){
			g_variant_get(value, "(v)", &info);
			g_variant_get(info, "o", &str_val); 
			//dbus_printf ("property name : %s  , %s\n ",dbus_property_list->name,str_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","Get value",__func__,str_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type,"g")){
			g_variant_get(value, "(v)", &info);
			g_variant_get(info, "g", &str_val); 
			//dbus_printf ("property name : %s  , %s\n ",dbus_property_list->name,str_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","Get value",__func__,str_val);
			}
		else if(0==g_strcmp0(dbus_property_list->type, "b")){
			g_variant_get(value, "(v)", &info);
			g_variant_get(info, "b", &byte_val);
			//dbus_printf ("property name : %s  , %d\n ",dbus_property_list->name,byte_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","Get value",__func__,byte_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type, "y")){
			g_variant_get(value, "(v)", &info);
			g_variant_get(info, "y", &byte_val);
			//dbus_printf ("property name : %s  , %d\n ",dbus_property_list->name,byte_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","Get value",__func__,byte_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type, "n")){
			g_variant_get(value, "(v)", &info);
			g_variant_get(info, "n", &int16_val);
			//dbus_printf ("property name : %s  , %d\n ",dbus_property_list->name,int16_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","Get value",__func__,int16_val);
		}
		else if(0==g_strcmp0(dbus_property_list->type, "q")){
			g_variant_get(value, "(v)", &info);
			g_variant_get(info, "q", &uint16_val);
			//dbus_printf ("property name : %s  , %d\n ",dbus_property_list->name,uint16_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","Get value",__func__,uint16_val);
			}
		else if(0==g_strcmp0(dbus_property_list->type, "i")){
			g_variant_get(value, "(v)", &info);
			g_variant_get(info, "i", &int32_val);
			//dbus_printf ("property name : %s  , %d\n ",dbus_property_list->name,int32_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","Get value",__func__,int32_val);
			}
		else if(0==g_strcmp0(dbus_property_list->type, "u")){
			g_variant_get(value, "(v)", &info);
			g_variant_get(info, "u", &uint32_val);
			//dbus_printf ("property name : %s  , %d\n ",dbus_property_list->name,uint32_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","Get value",__func__,uint32_val);
			}
		else if(0==g_strcmp0(dbus_property_list->type, "x")){
			g_variant_get(value, "(v)", &info);
			g_variant_get(info, "x", &int64_val);
			//dbus_printf ("property name : %s  , %ld\n ",dbus_property_list->name,int64_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%ld\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","Get value",__func__,int64_val);
			}
		else if(0==g_strcmp0(dbus_property_list->type, "t")){
			g_variant_get(value, "(v)", &info);
			g_variant_get(info, "t", &uint64_val);
			//dbus_printf ("property name : %s  , %ld\n ",dbus_property_list->name,uint64_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%ld\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","Get value",__func__,uint64_val);
			}
		else if(0==g_strcmp0(dbus_property_list->type, "h")){
			g_variant_get(value, "(v)", &info);
			g_variant_get(info, "h", &uint32_val);
			//dbus_printf ("property name : %s  , %d\n ",dbus_property_list->name,uint32_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","Get value",__func__,uint32_val);
			}
		else if(0==g_strcmp0(dbus_property_list->type, "d")){
			g_variant_get(value, "(v)", &info);
			g_variant_get(info, "d", &double_val);
			//dbus_printf ("property name : %s  , %lf\n ",dbus_property_list->name,double_val);
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%lf\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","Get value",__func__,double_val);
			}
		else if(0==g_strcmp0(dbus_property_list->type, "as")){
#if 1
                        g_variant_get(value, "(v)", &info);
                        g_variant_get(info, "s", &str_val);
			if(str_val==NULL)
			{
				//dbus_printf("NULL....\n");
                        	dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name,"","","","OK","Get value",__func__,"");
				return;
			}
                	GVariantIter *iter;
                	g_variant_get(info, "as", &iter);
                	while (g_variant_iter_loop (iter, "s", &str_val)){
                        	//dbus_printf ("property name :string , %s\n ",str_val);
                        	dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name,"","","","OK","Get value",__func__,str_val);
                	}
                	g_variant_iter_free (iter);

#endif

#if 0
    GVariantIter *array=NULL;
    GVariantIter tuple;
    g_variant_iter_init (&tuple, value);
    g_variant_iter_next (&tuple, "as", &array);

    while (g_variant_iter_loop (array, "s", &str_val))
    {
        dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name, dbus_property_list->name,"","","","OK","",__func__,str_val);
    }
    g_variant_iter_free (array);
#endif
			}
		else if(0==g_strcmp0(dbus_property_list->type, "a{sv}")){
			GVariantIter *iter;
			g_variant_get (value, "a{sv}", &iter);
			while (g_variant_iter_loop (iter, "s", &str_val)){
				//dbus_printf ("property name :string , %s\n ",str_val);
				dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","",__func__,str_val);
			}
			g_variant_iter_free (iter);
				dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","OK","",__func__,"a{sv}value");
			}
		else{
			//g_print ("Result type = %s, %s\n", g_variant_get_type_string(value), g_variant_print (value, TRUE));
			dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%d\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","Failed","Unknown type .",__func__,"");
			//g_variant_get(result, "s", &str_val);
			//dbus_printf ("type other = %s\n",(gchar *) str_val);
		}

		if((dbus_property_list->case_property_has_min)||(dbus_property_list->case_property_has_max))
		{

			if(0==g_strcmp0(dbus_property_list->type, "y")){
				remote_object_property_Lookup_check_range(dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,(int)byte_val);
			}
			else if(0==g_strcmp0(dbus_property_list->type, "u")){
				remote_object_property_Lookup_check_range(dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,(int)uint32_val);
			}
			else if(0==g_strcmp0(dbus_property_list->type, "i")){
				remote_object_property_Lookup_check_range(dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,(int)int32_val);
			}
			else 
			{
				dbus_printf("dbus_g_value_variant_get need parse more type for range check\n");
			}
		}
	}
}

GVariant * dbus_g_variant_test_and_return_new(struct dbus_property *dbus_property_list,gchar value)
//GVariant * dbus_g_variant_test_and_return_new(struct dbus_property *dbus_property_list)
{

	//dbus_printf("@@ dbus_g_variant_new %s, %s\n",dbus_property_list->name,dbus_property_list->type);
	if(dbus_property_list->case_property_has_value==0)
		return NULL;
	if((value==0x01) && !(dbus_property_list->case_property_has_value & 0x01))
	{
		dbus_printf("%s not set test_value in case.xml\n",dbus_property_list->name);
		return NULL;
	}
	if((value==0x02) && !(dbus_property_list->case_property_has_value & 0x02))
	{
		dbus_printf("%s not set test_value2 in case.xml 0x%x\n",dbus_property_list->name,dbus_property_list->case_property_has_value);
		return NULL;
	}
	if(value==0x01)
	{
		switch (*dbus_property_list->type)
		{
			//dbus_printf("@@ %s\n",dbus_property_list->type);
    			case 'b':
      				return g_variant_new_boolean (dbus_property_list->value.bool_v);
    			case 'y':
    				return g_variant_new_byte (dbus_property_list->value.byte_v);
    			case 'n':
     	 			return g_variant_new_int16 (dbus_property_list->value.int16_v);
    			case 'q':
      				return g_variant_new_uint16 (dbus_property_list->value.uint16_v);
    			case 'i':
      				return g_variant_new_int32 (dbus_property_list->value.int32_v);
    			case 'u':
      				return g_variant_new_uint32 (dbus_property_list->value.uint32_v);
    			case 'x':
      				return g_variant_new_int64 (dbus_property_list->value.int64_v);
    			case 't':
      				return g_variant_new_uint64 (dbus_property_list->value.uint64_v);
    			case 'h':
      				return g_variant_new_handle (dbus_property_list->value.handle_v);
    			case 'd':
      				return g_variant_new_double (dbus_property_list->value.double_v);
			case 's':
				return g_variant_new_string(dbus_property_list->value.path_str);
    			default:
      				break;
    		}
		if(strcmp(dbus_property_list->type,"as")==0)
		{

			guint32 count = dbus_property_list->value.str_array.str_count;
                        guint32 useful_count = 0;
			if (count==0)
				return NULL;
			GVariantBuilder *as_builder;
			GVariant *as_value;
			as_builder = g_variant_builder_new (G_VARIANT_TYPE("as"));
			int as_idx=0;
			//while(count>0)
			while(as_idx<count)
			{
				if(strlen(dbus_property_list->value.str_array.str_arry_p[as_idx])>0)
                                {
				    g_variant_builder_add(as_builder, "s", dbus_property_list->value.str_array.str_arry_p[as_idx]);
				    dbus_printf("as %d ##### %s\n", useful_count, dbus_property_list->value.str_array.str_arry_p[as_idx]);
                                    useful_count++;
                                }
				//count--;
				as_idx++;
			}
			as_value = g_variant_builder_end(as_builder);
			dbus_printf("as_value from case.xml.bak is %s, count=%d\n",g_variant_print(as_value, true),useful_count);
			return as_value;
		}
	}
	else if(value==0x02)
	{
		switch (*dbus_property_list->type)
		{
			//dbus_printf("@@ %s\n",dbus_property_list->type);
    			case 'b':
      				return g_variant_new_boolean (dbus_property_list->value2.bool_v);
    			case 'y':
    				return g_variant_new_byte (dbus_property_list->value2.byte_v);
    			case 'n':
     	 			return g_variant_new_int16 (dbus_property_list->value2.int16_v);
    			case 'q':
      				return g_variant_new_uint16 (dbus_property_list->value2.uint16_v);
    			case 'i':
      				return g_variant_new_int32 (dbus_property_list->value2.int32_v);
    			case 'u':
      				return g_variant_new_uint32 (dbus_property_list->value2.uint32_v);
    			case 'x':
      				return g_variant_new_int64 (dbus_property_list->value2.int64_v);
    			case 't':
      				return g_variant_new_uint64 (dbus_property_list->value2.uint64_v);
    			case 'h':
      				return g_variant_new_handle (dbus_property_list->value2.handle_v);
    			case 'd':
      				return g_variant_new_double (dbus_property_list->value2.double_v);
			case 's':
				return g_variant_new_string(dbus_property_list->value2.path_str);
    			default:
      				break;
    		}
		if(strcmp(dbus_property_list->type,"as")==0)
		{

			guint32 count = dbus_property_list->value2.str_array.str_count;
                        guint32 useful_count = 0;
			if (count==0)
				return NULL;
			GVariantBuilder *as_builder;
			GVariant *as_value;
			as_builder = g_variant_builder_new (G_VARIANT_TYPE("as"));
			int as_idx=0;
			//while(count>0)
			while(as_idx<count)
			{
				if(strlen(dbus_property_list->value2.str_array.str_arry_p[as_idx])>0)
                                {
				    g_variant_builder_add(as_builder, "s", dbus_property_list->value2.str_array.str_arry_p[as_idx]);
				    dbus_printf("as %d ##### %s\n", useful_count, dbus_property_list->value2.str_array.str_arry_p[as_idx]);
                                    useful_count++;
                                }
				as_idx++;
			}
			as_value = g_variant_builder_end(as_builder);
			dbus_printf("as_value2 from case.xml.bak is %s, count=%d\n",g_variant_print(as_value, true),useful_count);
			return as_value;
		}

	}
	else
	{
	}
	return NULL;
}




GVariant * dbus_g_variant_new(struct dbus_property *dbus_property_list,gchar onoff)
{
	GVariant *value;

	//dbus_printf("@@ dbus_g_variant_new %s, %s\n",dbus_property_list->name,dbus_property_list->type);
	
	//if(onoff)
	if(1)
	{
		switch (*dbus_property_list->type)
		{
			//dbus_printf("@@ %s\n",dbus_property_list->type);
    			case 'b':
      				return g_variant_new_boolean (dbus_property_list->value.bool_v);
    			case 'y':
    				return g_variant_new_byte (dbus_property_list->value.byte_v);
    			case 'n':
     	 			return g_variant_new_int16 (dbus_property_list->value.int16_v);
    			case 'q':
      				return g_variant_new_uint16 (dbus_property_list->value.uint16_v);
    			case 'i':
      				return g_variant_new_int32 (dbus_property_list->value.int32_v);
    			case 'u':
      				return g_variant_new_uint32 (dbus_property_list->value.uint32_v);
    			case 'x':
      				return g_variant_new_int64 (dbus_property_list->value.int64_v);
    			case 't':
      				return g_variant_new_uint64 (dbus_property_list->value.uint64_v);
    			case 'h':
      				return g_variant_new_handle (dbus_property_list->value.handle_v);
    			case 'd':
      				return g_variant_new_double (dbus_property_list->value.double_v);
			case 's':
				return g_variant_new_string(dbus_property_list->value.path_str);

    			default:
      				break;
    		}
	}
	else
	{
	}
}

void remote_object_igd1_properties_get(struct dbus_property *dbus_property_list, struct dbus_interface *dbus_interface_list ,
                          				struct dbus_object *dbus_object_list)
{
	GDBusConnection  *connection; 
	GError *error = NULL;  
	GVariant* values;
	
	struct timeval start;
	struct timeval end;
	guint elapsed_time = 0;
	
	connection = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, NULL);

	gettimeofday(&start, NULL);
	values = g_dbus_connection_call_sync(connection,	
						"com.ctc.igd1",//"org.freedesktop.UPower",////   
						dbus_object_list->name, //object path
						"com.ctc.igd1.Properties",//"org.freedesktop.DBus.Properties", ////
						"Get",	
						g_variant_new("(ss)", dbus_interface_list->name,dbus_property_list->name),
						G_VARIANT_TYPE("(v)"),
						G_DBUS_CALL_FLAGS_NONE,
						-1,
						NULL,
						&error);
	
	gettimeofday(&end, NULL);
	if(error){
		//dbus_printf("@@ error %s\n",error->message);
		dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"","","","Failed","", __func__,error->message);
		dbus_cts_error_print(error);
		g_variant_unref (values); 
		g_object_unref(connection);
		g_error_free(error);
		error = NULL;
		return ;
	}
	
	elapsed_time = (end.tv_sec - start.tv_sec)*1000000 +
						(end.tv_usec - start.tv_usec);
	//dbus_printf("%s, Time :%d us\n",
	//				(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);
	dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"Get","",elapsed_time,(elapsed_time > 200000)?"Failed":"OK",(elapsed_time > 200000)?"Time out":"",__func__,"");
	if (values != NULL) {
		dbus_g_value_variant_get(dbus_interface_list, dbus_object_list, dbus_property_list,values);
	}

	g_variant_unref (values); 
	g_object_unref(connection);
	
	
}

void remote_object_igd1_properties_get_all( struct dbus_interface *dbus_interface_list ,
                          				struct dbus_object *dbus_object_list)
{
		if(redundancy)
			sleep(1);
	struct listnode *property_list_item_p;
	struct dbus_property *property_p;

	GDBusConnection  *connection;  
	GError *error = NULL;  
	GVariant* values;

	GVariant *info = NULL;	
	gchar *key = NULL;
	
	struct timeval start;
	struct timeval end;
	guint elapsed_time = 0;

	gchar g_property = 0;

	
	connection = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, NULL);

#if 0//It's ok... time too long.....
	gettimeofday(&start, NULL);
	values = g_dbus_connection_call_sync(connection,	
						"com.ctc.igd1",//"org.freedesktop.UPower",//   
						dbus_object_list->name, //object path
						"com.ctc.igd1.Properties",//"org.freedesktop.DBus.Properties", ////
						"GetAll",	
						g_variant_new("(s)", dbus_interface_list->name),
						G_VARIANT_TYPE("(a{sv})"),
						G_DBUS_CALL_FLAGS_NONE,
						-1,
						NULL,
						&error);
#endif
	GDBusProxy  *remote_object;
        remote_object = g_dbus_proxy_new_sync (connection,
                G_DBUS_PROXY_FLAGS_NONE,
                NULL,
                "com.ctc.igd1",
                dbus_object_list->name,
                "com.ctc.igd1.Properties",
                NULL,
                &error);

        //g_assert_no_error(error);
        gettimeofday(&start, NULL);

        values = g_dbus_proxy_call_sync(remote_object,
                "GetAll",
                g_variant_new("(s)", dbus_interface_list->name),//method_input_param,
                G_DBUS_CALL_FLAGS_NONE,
                300000,//-1,
                NULL,
                &error);


	
	gettimeofday(&end, NULL);
	elapsed_time = (end.tv_sec - start.tv_sec)*1000000 +
						(end.tv_usec - start.tv_usec);
	//dbus_printf("%s, Time :%d us\n",
	//				(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);
	dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","GetAll","",elapsed_time,(elapsed_time > 200000)?"Failed":"OK",(elapsed_time > 200000)?"Time out":"",__func__,"get all data");
	if(elapsed_time > 200000){
		dbus_object_list->test_result |= METHOD_CALL_TIMEOUT;
		dbus_interface_list->test_result |= METHOD_CALL_TIMEOUT;
	}
	if (values != NULL) {		
		GVariantIter iter;		
		GVariant *newValue = NULL;
		g_variant_get(values, "(@a{sv})", &newValue);		
		g_variant_iter_init(&iter, newValue);
		
		list_for_each(property_list_item_p, &dbus_interface_list->property_list) {
				property_p = node_to_item(property_list_item_p,
							struct dbus_property, list);
				property_p ->flags = 0;
		}
		while (g_variant_iter_next(&iter, "{sv}", &key, &info)) {
			g_property = 0;
			list_for_each(property_list_item_p, &dbus_interface_list->property_list) {
				property_p = node_to_item(property_list_item_p,
							struct dbus_property, list);
				if(0==g_strcmp0(property_p->name,key))
				{
					property_p ->flags = 1;
					g_property = 1;
					dbus_g_value_variant_get_all(dbus_interface_list, dbus_object_list, property_p,info);
				}
			}
			if(!g_property)
				//dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,property_p->name,"","","","Failed","No property    ",__func__,property_p->name);
				dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,key,"","","","OK","more property    ",__func__,key);
				//Powerlevel /PowerLevel_5G deleted.... can't parse!
		}
		list_for_each(property_list_item_p, &dbus_interface_list->property_list) {
			property_p = node_to_item(property_list_item_p,
							struct dbus_property, list);
			if(!property_p ->flags )
			{
				property_p ->flags = 0;
				//dbus_printf("\t Failed property :%s can't work\n",property_p->name);
				dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,property_p->name,"","","","Failed","Can't getall the value   ",__func__,property_p->name);
				dbus_object_list->test_result |= PROPERTY_CANT_GET_OR_GETALL;
				dbus_interface_list->test_result |= PROPERTY_CANT_GET_OR_GETALL;
			}
		}
	g_variant_unref (values); 
	g_object_unref (G_OBJECT(remote_object));
	}

	g_object_unref(connection);
}

typedef struct {
  GThread *thread;
  GMainLoop *thread_loop;
  guint signal_count;
  struct dbus_property* dbus_property_list;
  struct dbus_interface* dbus_interface_list;
  struct dbus_object *dbus_object_list;
} DeliveryData;

static void
signal_handler (GDBusConnection *connection,
                const gchar      *sender_name,
                const gchar      *object_path,
                const gchar      *interface_name,
                const gchar      *signal_name,
                GVariant         *parameters,
                gpointer         user_data)
{
	DeliveryData *data = user_data;

	const gchar *interface_name_for_signal;
  	GVariant *changed_properties;
 	gchar **invalidated_properties;
  	GVariantIter iter;
  	gchar *key;
  	GVariant *value;

	dbus_printf("@@ signal handle \n");

	if(0==g_strcmp0(data->dbus_object_list->name,object_path) && !g_strcmp0(signal_name,"PropertiesChanged"))
	{
		dbus_printf("Error signal %s\n",signal_name);
		return;
	}

	if (g_variant_is_of_type (parameters, G_VARIANT_TYPE ("(sa{sv}as)"))){	
  	 	g_variant_get (parameters,
                 	"(&s@a{sv}^a&s)",
                	 &interface_name_for_signal,
               	  &changed_properties,
                	 &invalidated_properties);
		
		  g_variant_iter_init (&iter, changed_properties);
 		  while (g_variant_iter_next (&iter, "{sv}", &key, &value)){
		  	 dbus_printf("%s \n",key);
			 //if(g_strcmp0(key,data->dbus_property_list->name) == 0)
			 	//dbus_g_value_variant_get(dbus_interface_list, dbus_object_list, data->dbus_property_list,value);
 		  	}	
		}

  	data->signal_count++;

  g_main_loop_quit (data->thread_loop);
}

void remote_object_igd1_properties_set( struct dbus_property * dbus_property_list,
											struct dbus_interface *dbus_interface_list ,
                          								struct dbus_object *dbus_object_list,gchar onoff)
  //                        								GVariant *value)
{	

	GDBusConnection  *bus; 
	GDBusProxy  *remote_object;
	GVariant* result;
	GError *error = NULL;  
	gint ret = 0;
	GVariant* value;
	
	
	struct timeval start;
	struct timeval end;
	guint elapsed_time = 0;

	struct listnode *property_list_item_p;
	struct dbus_property *property_p;
	struct dbus_interface *interface_p;


	GDBusConnection  *connection;  

	/***signal listen**/
	DeliveryData data;
	GMainLoop *thread_loop;
  	GMainContext *thread_context;
	thread_context = g_main_context_new ();


  	thread_loop = g_main_loop_new (thread_context, FALSE);
	data.thread_loop = thread_loop;	
	data.thread = g_thread_self ();
 	data.signal_count = 0;
	
	data.dbus_object_list   = (struct dbus_object*)malloc(sizeof(struct dbus_object));
	if( !data.dbus_object_list  ) {
			dbus_printf("failed to alloc struct dbus_object memory\n");
			return;
	}
	memset(data.dbus_object_list , 0, sizeof(struct dbus_object));

	
	data.dbus_interface_list   = (struct dbus_interface *)malloc(sizeof(struct dbus_interface));
	if( !data.dbus_interface_list  ) {
			dbus_printf("failed to alloc struct dbus_interface memory\n");
			return;
	}
	memset(data.dbus_interface_list , 0, sizeof(struct dbus_interface));

	data.dbus_property_list   = (struct dbus_property *)malloc(sizeof(struct dbus_property));
	if( !data.dbus_property_list  ) {
			dbus_printf("failed to alloc struct dbus_interface memory\n");
			return;
	}
	
	memset(data.dbus_property_list , 0, sizeof(struct dbus_property));

	
	data.dbus_object_list = dbus_object_list;
	
	data.dbus_interface_list = dbus_interface_list;

	data.dbus_property_list =  dbus_property_list;


	connection = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, &error);	
	//g_assert_no_error(error);
	
	ret = g_dbus_connection_signal_subscribe (connection,			
							NULL,//dbus_interface_list->name,	
							NULL,	
							NULL,
							dbus_object_list->name,
							NULL,
							G_DBUS_SIGNAL_FLAGS_NONE,
							signal_handler,
							&data,
							NULL); 

	/*************************/


	value = dbus_g_variant_new(dbus_property_list,onoff);
	
	bus = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, &error);	
	

	if (!bus){
		dbus_printf ("Couldn't connect to system  bus\n");
	}
	#if 1
	remote_object = g_dbus_proxy_new_sync (bus,	
						G_DBUS_PROXY_FLAGS_NONE,
						NULL, 
						"com.ctc.igd1",//"org.freedesktop.UPower",//	
						dbus_object_list->name,	
						"com.ctc.igd1.Properties",//"org.freedesktop.DBus.Properties",//
						NULL,
						&error);
	
	gettimeofday(&start, NULL);
	result = g_dbus_proxy_call_sync(remote_object,
						"Set",
						g_variant_new("(ssv)", dbus_interface_list->name,dbus_property_list->name,value), 
						G_DBUS_CALL_FLAGS_NONE,
						-1,
						NULL,
						&error);
	#else

	gettimeofday(&start, NULL);
	result = g_dbus_connection_call_sync(connection,	
						"com.ctc.igd1",//"org.freedesktop.UPower",////   
						dbus_object_list->name, //object path
						"com.ctc.igd1.Properties",//"org.freedesktop.DBus.Properties", ////
						"Set",	
						g_variant_new("(ssv)", dbus_interface_list->name,dbus_property_list->name,value),
						NULL,
						G_DBUS_CALL_FLAGS_NONE,
						-1,
						NULL,
						&error);
	
	#endif
       gettimeofday(&end, NULL);

	if(error){
		dbus_cts_error_print(error);
		g_variant_unref (result); 
		g_variant_unref (value); 
		g_object_unref (G_OBJECT (remote_object));
		g_object_unref(bus);
		g_error_free(error);
		error = NULL;
		goto SET_ERROR;
	}
	elapsed_time = (end.tv_sec - start.tv_sec)*1000000 +
						(end.tv_usec - start.tv_usec);
	//dbus_printf("%s, Time :%d us\n",
	//				(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);
	dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"Set","",elapsed_time,(elapsed_time > 200000)?"Failed":"OK",(elapsed_time > 200000)?"Time out":"","remote_object_igd1_properties_set","");

	g_object_unref (G_OBJECT (remote_object));
	g_object_unref(bus);
	 

	//g_main_loop_run (thread_loop);
	SET_ERROR:
	g_object_unref(connection);
	g_main_loop_unref (thread_loop);
	
}


GVariant* dbus_g_variant_new_all(struct dbus_interface *dbus_interface_list ,gchar onoff)
{

}
	
void remote_object_igd1_properties_set_all ( struct dbus_property * dbus_property_list,
											struct dbus_interface *dbus_interface_list ,
                          								struct dbus_object *dbus_object_list,gchar onoff)
  //                        								GVariant *value)
{	

	GDBusConnection  *bus; 
	GDBusProxy  *remote_object;
	GVariant* result;
	GError *error = NULL;  
	gint ret = 0;
	GVariant* value;
	
	
	struct timeval start;
	struct timeval end;
	guint elapsed_time = 0;

	struct listnode *property_list_item_p;
	struct dbus_property *property_p;
	struct dbus_interface *interface_p;


	GDBusConnection  *connection;  

	/***signal listen**/
	DeliveryData data;
	GMainLoop *thread_loop;
  	GMainContext *thread_context;
	thread_context = g_main_context_new ();


  	thread_loop = g_main_loop_new (thread_context, FALSE);
	data.thread_loop = thread_loop;	
	data.thread = g_thread_self ();
 	data.signal_count = 0;
	
	data.dbus_object_list   = (struct dbus_object*)malloc(sizeof(struct dbus_object));
	if( !data.dbus_object_list  ) {
			dbus_printf("failed to alloc struct dbus_object memory\n");
			return;
	}
	memset(data.dbus_object_list , 0, sizeof(struct dbus_object));

	
	data.dbus_interface_list   = (struct dbus_interface *)malloc(sizeof(struct dbus_interface));
	if( !data.dbus_interface_list  ) {
			dbus_printf("failed to alloc struct dbus_interface memory\n");
			return;
	}
	memset(data.dbus_interface_list , 0, sizeof(struct dbus_interface));

	data.dbus_property_list   = (struct dbus_property *)malloc(sizeof(struct dbus_property));
	if( !data.dbus_property_list  ) {
			dbus_printf("failed to alloc struct dbus_interface memory\n");
			return;
	}
	
	memset(data.dbus_property_list , 0, sizeof(struct dbus_property));

	
	data.dbus_object_list = dbus_object_list;
	
	data.dbus_interface_list = dbus_interface_list;

	data.dbus_property_list =  dbus_property_list;


	connection = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, &error);	
	//g_assert_no_error(error);
	
	ret = g_dbus_connection_signal_subscribe (connection,			
						NULL,//dbus_interface_list->name,	
						NULL,	
						NULL,
						dbus_object_list->name,
						NULL,
						G_DBUS_SIGNAL_FLAGS_NONE,
						signal_handler,
						&data,
						NULL); 

	/*************************/


	value = dbus_g_variant_new_all(dbus_interface_list,onoff);
	
	bus = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, &error);	
	

	if (!bus){
		dbus_printf ("Couldn't connect to system  bus\n");
	}
	#if 1
	remote_object = g_dbus_proxy_new_sync (bus,	
						G_DBUS_PROXY_FLAGS_NONE,
						NULL, 
						"com.ctc.igd1",//"org.freedesktop.UPower",//	
						dbus_object_list->name,
						"com.ctc.igd1.Properties",//"org.freedesktop.DBus.Properties",//
						NULL,
						&error);
	
	gettimeofday(&start, NULL);
	result = g_dbus_proxy_call_sync(remote_object,
						"Set",
						g_variant_new("(ssv)", dbus_interface_list->name,dbus_property_list->name,value), 
						G_DBUS_CALL_FLAGS_NONE,
						-1,
						NULL,
						&error);
	#else

	gettimeofday(&start, NULL);
	result = g_dbus_connection_call_sync(connection,	
						"com.ctc.igd1",//"org.freedesktop.UPower",////   
						dbus_object_list->name, //object path
						"com.ctc.igd1.Properties",//"org.freedesktop.DBus.Properties", ////
						"Set",	
						g_variant_new("(ssv)", dbus_interface_list->name,dbus_property_list->name,value),
						NULL,
						G_DBUS_CALL_FLAGS_NONE,
						-1,
						NULL,
						&error);
	
	#endif
       gettimeofday(&end, NULL);

	if(error){
		dbus_cts_error_print(error);
		g_variant_unref (result); 
		g_variant_unref (value); 
		g_object_unref (G_OBJECT (remote_object));
		g_object_unref(bus);
		g_error_free(error);
		error = NULL;
		goto SET_ERROR;
	}
	elapsed_time = (end.tv_sec - start.tv_sec)*1000000 +
						(end.tv_usec - start.tv_usec);
	//dbus_printf("%s, Time :%d us\n",
	//				(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);
	dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,dbus_property_list->name,"SetAll","",elapsed_time,(elapsed_time > 200000)?"Failed":"OK",(elapsed_time > 200000)?"Time out":"","remote_object_igd1_properties_set_all","Set all data");

	g_object_unref (G_OBJECT (remote_object));
	g_object_unref(bus);
	 

	//g_main_loop_run (thread_loop);
	SET_ERROR:
	g_object_unref(connection);
	g_main_loop_unref (thread_loop);
	
}	

void remote_object_igd1_properties( struct dbus_interface *dbus_interface_list ,
                          				struct dbus_object *dbus_object_list)
{
	GDBusConnection  *bus; 
	GDBusProxy  *remote_object;  
	GError *error = NULL;  
	GVariant* result;
	gint ret = 0;
	struct timeval start;
	struct timeval start1;
	struct timeval end;
	guint elapsed_time = 0;
	struct listnode *property_list_item_p;
	struct dbus_property *property_p;

	struct listnode *interface_list_item_p;
	struct dbus_interface *dbus_interface_p;

	GVariant *info = NULL;	
	gchar *key = NULL;	
	gchar *str_val = NULL;	
	guint16 uint16_val;
	gint16  int16_val;
	gint32  int32_val;
	guint32 uint32_val;
	gint64  int64_val;
	guint64 uint64_val;	
	gchar   byte_val;
	gdouble double_val;
	gboolean bol_val;
	struct listnode *method_list_item_p;

        if((!dbus_interface_list->introspect_has_interface))
        {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%s%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","","","","Failed","No interface ",dbus_interface_list->name," from introspect", __func__,"Stop execve");
                return;
        }

	list_for_each(interface_list_item_p, &dbus_object_list->interface_list){
		dbus_interface_p = node_to_item(interface_list_item_p,
						struct dbus_interface, list);
		list_for_each(property_list_item_p, &dbus_interface_p->property_list) {
			property_p = node_to_item(property_list_item_p,
							struct dbus_property, list);
#if 0//simple version
			if(property_p!=NULL)
			{
				if(property_p->introspect_has_property)
					igd1_Get_Set_or_Checksignal(dbus_object_list,dbus_interface_p,property_p);
				else
				
	                                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%s%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","","","","Failed","No property ",property_p->name," from introspect", __func__,"Stop execve");
			}
#endif
#if 1//legcy version
			if((!strncmp(property_p->access,"read",strlen("read")) )|| (!strncmp(property_p->access,"readwrite",strlen("readwrite")) ))
				{
				//dbus_printf("get property\n");

				bus = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, &error);	

				 if (!bus){
	  				dbus_printf ("Couldn't connect to system  bus\n");
					continue;
				 	}

				remote_object = g_dbus_proxy_new_sync (bus,	
									G_DBUS_PROXY_FLAGS_NONE,
									NULL, 
									"com.ctc.igd1",	//"org.freedesktop.UPower",//	
									dbus_object_list->name,
									"com.ctc.igd1.Properties",//"org.freedesktop.DBus.Properties",//////
									NULL,
									&error);
				gettimeofday(&start1, NULL);
				gettimeofday(&start, NULL);
				result = g_dbus_proxy_call_sync(remote_object,
										"Get",
										  g_variant_new("(ss)",
										dbus_interface_p->name,property_p->name), 
										G_DBUS_CALL_FLAGS_NONE,
										-1,
										NULL,
										&error);

				gettimeofday(&end, NULL);

				if(error){
					//dbus_printf("@@ error %s\n",error->message);
					dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name, property_p->name,"","","","Failed","", __func__,error->message);
					//dbus_cts_error_print(error);
					//g_variant_unref (result); 
					g_object_unref (G_OBJECT (remote_object));
					g_object_unref(bus);
					g_error_free(error);
					error = NULL;
					continue;
				}
				
	 			
				if(result != NULL){	
					dbus_g_value_variant_get(dbus_interface_list, dbus_object_list, property_p,result);
				}
				
				g_variant_unref (result); 			
				//elapsed_time = (end.tv_sec - start.tv_sec)*1000000 +
				//		(end.tv_usec - start.tv_usec);
				//dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
				//	dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);
				elapsed_time = (end.tv_sec - start1.tv_sec)*1000000 +
						(end.tv_usec - start1.tv_usec);
				//dbus_printf("[%s]@[%s] property[%s], performace  is %s ,the perform time is %d us\n",
				//	dbus_object_list->name,dbus_object_list->name, property_p->name, (elapsed_time > 200000)?"FAILED":"OK",elapsed_time);
				dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","igd1_properties","",elapsed_time,(elapsed_time > 200000)?"Failed":"OK",(elapsed_time > 200000)?"Time out":"Get single property not time out",__func__,property_p->name);
				g_object_unref (G_OBJECT (remote_object));
				g_object_unref(bus);
			}
#endif
		}

	}
}


void remote_object_igd1_properties_GCS( struct dbus_interface *dbus_interface_list ,
                          				struct dbus_object *dbus_object_list)
{
	GDBusConnection  *bus; 
	GDBusProxy  *remote_object;  
	GError *error = NULL;  
	GVariant* result;
	gint ret = 0;
	struct timeval start;
	struct timeval start1;
	struct timeval end;
	guint elapsed_time = 0;
	struct listnode *property_list_item_p;
	struct dbus_property *property_p;

	struct listnode *interface_list_item_p;
	struct dbus_interface *dbus_interface_p;

	GVariant *info = NULL;	
	gchar *key = NULL;	
	gchar *str_val = NULL;	
	guint16 uint16_val;
	gint16  int16_val;
	gint32  int32_val;
	guint32 uint32_val;
	gint64  int64_val;
	guint64 uint64_val;	
	gchar   byte_val;
	gdouble double_val;
	gboolean bol_val;
	struct listnode *method_list_item_p;

        if((!dbus_interface_list->introspect_has_interface))
        {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%s%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","","","","Failed","No interface ",dbus_interface_list->name," from introspect", __func__,"Stop execve");
                return;
        }

	list_for_each(interface_list_item_p, &dbus_object_list->interface_list){
		dbus_interface_p = node_to_item(interface_list_item_p,
						struct dbus_interface, list);
		list_for_each(property_list_item_p, &dbus_interface_p->property_list) {
			property_p = node_to_item(property_list_item_p,
							struct dbus_property, list);
#if 1//simple version
			if(property_p!=NULL)
			{
				if(property_p->introspect_has_property)
					igd1_Get_Set_or_Checksignal(dbus_object_list,dbus_interface_p,property_p);
				else
				
	                                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%s%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","","","","Failed","No property ",property_p->name," from introspect", __func__,"Stop execve");
			}
#endif
#if 0//legcy version
			if((!strncmp(property_p->access,"read",strlen("read")) )|| (!strncmp(property_p->access,"readwrite",strlen("readwrite")) ))
				{
				//dbus_printf("get property\n");

				bus = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, &error);	

				 if (!bus){
	  				dbus_printf ("Couldn't connect to system  bus\n", error);
					continue;
				 	}

				remote_object = g_dbus_proxy_new_sync (bus,	
									G_DBUS_PROXY_FLAGS_NONE,
									NULL, 
									"com.ctc.igd1",	//"org.freedesktop.UPower",//	
									dbus_object_list->name,
									"com.ctc.igd1.Properties",//"org.freedesktop.DBus.Properties",//////
									NULL,
									&error);
				gettimeofday(&start1, NULL);
				gettimeofday(&start, NULL);
				result = g_dbus_proxy_call_sync(remote_object,
										"Get",
										  g_variant_new("(ss)",
										dbus_interface_p->name,property_p->name), 
										G_DBUS_CALL_FLAGS_NONE,
										-1,
										NULL,
										&error);

				gettimeofday(&end, NULL);

				if(error){
					//dbus_printf("@@ error %s\n",error->message);
					dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_p->name, property_p->name,"","","","Failed","", __func__,error->message);
					//dbus_cts_error_print(error);
					//g_variant_unref (result); 
					g_object_unref (G_OBJECT (remote_object));
					g_object_unref(bus);
					g_error_free(error);
					error = NULL;
					continue;
				}
				
	 			
				if(result != NULL){	
					dbus_g_value_variant_get(dbus_interface_list, dbus_object_list, property_p,result);
				}
				
				g_variant_unref (result); 			
				//elapsed_time = (end.tv_sec - start.tv_sec)*1000000 +
				//		(end.tv_usec - start.tv_usec);
				//dbus_printf("%s, performace  is %s ,the perform time is %d us\n",
				//	dbus_object_list->name,(elapsed_time > 200000)?"FAILED":"OK",elapsed_time);
				elapsed_time = (end.tv_sec - start1.tv_sec)*1000000 +
						(end.tv_usec - start1.tv_usec);
				//dbus_printf("[%s]@[%s] property[%s], performace  is %s ,the perform time is %d us\n",
				//	dbus_object_list->name,dbus_object_list->name, property_p->name, (elapsed_time > 200000)?"FAILED":"OK",elapsed_time);
				dbus_printf_twice("%s,%s,%s,%s,%s,%d(us),%s,%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","igd1_properties","",elapsed_time,(elapsed_time > 200000)?"Failed":"OK",(elapsed_time > 200000)?"Time out":"Get single property not time out",__func__,property_p->name);
				g_object_unref (G_OBJECT (remote_object));
				g_object_unref(bus);
			}
#endif
		}

	}
}




void remote_object_igd1_properties_SCC( struct dbus_interface *dbus_interface_list ,
                          				struct dbus_object *dbus_object_list)
{
	GDBusConnection  *bus; 
	GDBusProxy  *remote_object;  
	GError *error = NULL;  
	GVariant* result;
	gint ret = 0;
	struct timeval start;
	struct timeval start1;
	struct timeval end;
	guint elapsed_time = 0;
	struct listnode *property_list_item_p;
	struct dbus_property *property_p;

	struct listnode *interface_list_item_p;
	struct dbus_interface *dbus_interface_p;

	GVariant *info = NULL;	
	gchar *key = NULL;	
	gchar *str_val = NULL;	
	guint16 uint16_val;
	gint16  int16_val;
	gint32  int32_val;
	guint32 uint32_val;
	gint64  int64_val;
	guint64 uint64_val;	
	gchar   byte_val;
	gdouble double_val;
	gboolean bol_val;
	struct listnode *method_list_item_p;

        if((!dbus_interface_list->introspect_has_interface))
        {
                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%s%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,"","","","","Failed","No interface ",dbus_interface_list->name," from introspect", __func__,"Stop execve");
                return;
        }

	/*list_for_each(interface_list_item_p, &dbus_object_list->interface_list){
		dbus_interface_p = node_to_item(interface_list_item_p,
						struct dbus_interface, list);
		list_for_each(property_list_item_p, &dbus_interface_p->property_list) {*/
		list_for_each(property_list_item_p, &dbus_interface_list->property_list) {
			property_p = node_to_item(property_list_item_p,
							struct dbus_property, list);
			if(property_p!=NULL)
			{
				if(property_p->introspect_has_property)
					igd1_Set_Checksignal_CheckGet(dbus_object_list,dbus_interface_list,property_p,0);
				else
				{
	                                dbus_printf_twice("%s,%s,%s,%s,%s,%s,%s,%s%s%s,%s,%s\n",dbus_object_list->name, dbus_interface_list->name,property_p->name,"","","","Failed","No property ",property_p->name," from introspect", __func__,"Stop execve");

					dbus_object_list->test_result |= NO_PROPERTY;
					property_p->test_result |= NO_PROPERTY;
				}
			}
		}

	//}
}
