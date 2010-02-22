/* 
 * Copyright (C) 2006 Piotr Pokora <piotrek.pokora@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *   
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *   */

#ifndef MIDGARD_CORE_QUERY_H
#define MIDGARD_CORE_QUERY_H

#include "midgard_connection.h"
#include "midgard_dbobject.h"
#include <libgda/libgda.h>
#include "schema.h"
#include "midgard_query_property.h"
#include "midgard_query_storage.h"
#include "midgard_query_simple_constraint.h"

typedef struct _MidgardDBColumn MidgardDBColumn;
typedef struct _MidgardDBJoin MidgardDBJoin;

struct _MidgardDBColumn {
	const gchar *table_name;
	const gchar *column_name;
	const gchar *column_desc;
	const gchar *dbtype;
	GType gtype;
	gboolean index;
	gboolean unique;
	gboolean autoinc;
	gboolean primary;
	GValue *gvalue;
	const gchar *dvalue;
};

struct _MidgardDBJoin {
	gchar *type;
	guint typeid;
	gchar *table;
	MidgardObjectClass *klass;

	/* pointers references */
	MgdSchemaPropertyAttr *left;
	MgdSchemaPropertyAttr *right;
};

struct MidgardCoreQueryOrder {
	MidgardQueryProperty *property;
	const gchar *type;
};

struct _MidgardQueryExecutorPrivate {
	MidgardConnection *mgd;
	MidgardQueryStorage *storage;
	MidgardQuerySimpleConstraint *constraint;
	GSList *orders;
	GSList *joins;
	guint limit;
	guint offset;
	gpointer resultset;
};

MidgardDBJoin	*midgard_core_dbjoin_new	(void);
void		midgard_core_dbjoin_free	(MidgardDBJoin *mdbj);

#ifdef HAVE_LIBGDA_4
#define midgard_data_model_get_value_at(__model,__col,__row) \
	gda_data_model_get_value_at((__model), (__col), (__row), NULL)
#else
#define midgard_data_model_get_value_at(__model,__col,__row) \
	gda_data_model_get_value_at((__model), (__col), (__row))
#endif

#ifdef HAVE_LIBGDA_4
#define midgard_data_model_get_value_at_col_name(__model,__col,__row) \
	midgard_data_model_get_value_at (__model, gda_data_model_get_column_index (__model, __col), __row);
#else
#define midgard_data_model_get_value_at_col_name(__model,__col,__row) \
	gda_data_model_get_value_at_col_name (__model, __col, __row)
#endif

#define MIDGARD_GET_UINT_FROM_VALUE(__prop, __value) \
	if(G_VALUE_HOLDS_UINT(__value)) { \
		__prop = \
			g_value_get_uint(__value); \
	} \
	if(G_VALUE_HOLDS_INT(__value)) { \
		__prop = \
			(guint)g_value_get_int(__value); \
	} \
	if(G_VALUE_HOLDS_CHAR(__value)) { \
		__prop = \
			(guint)g_value_get_char(__value); \
	}

#define MIDGARD_GET_INT_FROM_VALUE(__prop, __value) \
	if(G_VALUE_HOLDS_UINT(__value)) { \
		__prop = \
			(gint)g_value_get_uint(__value); \
	} \
	if(G_VALUE_HOLDS_INT(__value)) { \
		__prop = \
			g_value_get_int(__value); \
	} \
	if(G_VALUE_HOLDS_CHAR(__value)) { \
		__prop = \
			(gint)g_value_get_char(__value); \
	}

#define MIDGARD_GET_BOOLEAN_FROM_VALUE(__prop, __value) \
	if(G_VALUE_HOLDS_UINT(__value)) { \
		guint __i = g_value_get_uint(__value); \
		if(__i == 1) \
			__prop = TRUE; \
		else if(__i == 0) \
			__prop = FALSE; \
		else \
			g_warning("Midgard failed to convert guint to gboolean"); \
	} \
	else if(G_VALUE_HOLDS_INT(__value)) { \
		gint __i = g_value_get_int(__value); \
		if(__i == 1) \
			__prop = TRUE; \
		else if(__i == 0) \
			__prop = FALSE; \
		else \
	 		g_warning("Midgard failed to convert gint to gboolean"); \
	} \
	else if(G_VALUE_HOLDS_STRING(__value)) { \
		gint __i = atoi(g_value_get_string(__value)); \
		if(__i == 0) \
			__prop = FALSE; \
		else if (__i != 0) \
			__prop = TRUE; \
		else \
	 		g_warning("Midgard failed to convert string to gboolean"); \
	} \
	else if(G_VALUE_HOLDS_CHAR(__value)) { \
		gchar __i = g_value_get_char(__value); \
		if(__i == 1) \
			__prop = TRUE; \
		else if(__i == 0) \
			__prop = FALSE; \
		else \
			g_warning("Midgard failed to convert gchar to gboolean"); \
	} \
	else { \
		g_warning("Can not convert %s to boolean", G_VALUE_TYPE_NAME(__value)); \
	}

MidgardDBColumn *midgard_core_dbcolumn_new(void);

gchar *midgard_core_query_where_guid(
			const gchar *table,
			const gchar *guid);

gint midgard_core_query_execute(
			MidgardConnection *mgd, 
			const gchar *query,
			gboolean ignore_error);

GdaDataModel *midgard_core_query_get_model(
			MidgardConnection *mgd, 
			const gchar *query);

GValue *midgard_core_query_get_field_value(
			MidgardConnection *mgd,
			const gchar *field,
			const gchar *table, 
			const gchar *where);

guint midgard_core_query_get_id(
			MidgardConnection *mgd, 
			const gchar *table,
			const gchar *guid);

gint midgard_core_query_insert_records(
			MidgardConnection *mgd,
			const gchar *table, 
			GList *cols, 
			GList *values, guint query_type, const gchar *where);

gboolean midgard_core_query_update_object_fields(
			MidgardDBObject *object, 
			const gchar *propname, ...);

gboolean midgard_core_query_create_table(
			MidgardConnection *mgd,
			const gchar *descr, 
			const gchar *tablename, 
			const gchar *primary);

gboolean midgard_core_query_add_column(
			MidgardConnection *mgd,
			MidgardDBColumn *mdc);

gboolean midgard_core_query_add_index(
			MidgardConnection *mgd,
			MidgardDBColumn *mdc);

gboolean midgard_core_query_create_metadata_columns(
			MidgardConnection *mgd, 
			const gchar *tablename);

gboolean midgard_core_query_create_basic_db(
			MidgardConnection *mgd);

gboolean midgard_core_query_create_class_storage(
			MidgardConnection *mgd, 
			MidgardDBObjectClass *klass);

gboolean midgard_core_query_update_class_storage(
			MidgardConnection *mgd, 
			MidgardDBObjectClass *klass);

gboolean midgard_core_table_exists(
			MidgardConnection *mgd, 
			const gchar *tablename);

GdaDataModel 		*midgard_core_query_get_dbobject_model 		(MidgardConnection *mgd, MidgardDBObjectClass *klass, guint n_params, const GParameter *parameters);
gboolean		midgard_core_query_create_dbobject_record 	(MidgardDBObject *object);
gboolean		midgard_core_query_update_dbobject_record 	(MidgardDBObject *object);
gchar                   *midgard_core_query_binary_stringify            (GValue *src_value);

#endif /* MIDGARD_CORE_QUERY_H */
