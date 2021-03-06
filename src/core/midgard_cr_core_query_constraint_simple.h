/* 
 * Copyright (C) 2010 Piotr Pokora <piotrek.pokora@gmail.com>
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
 */

#ifndef MIDGARD_CR_CORE_QUERY_CONSTRAINT_SIMPLE_H
#define MIDGARD_CR_CORE_QUERY_CONSTRAINT_SIMPLE_H

#include <glib-object.h>

G_BEGIN_DECLS

/* convention macros */
#define MIDGARD_CR_CORE_TYPE_QUERY_CONSTRAINT_SIMPLE (midgard_cr_core_query_constraint_simple_get_type()) 
#define MIDGARD_CR_CORE_QUERY_CONSTRAINT_SIMPLE(object)  (G_TYPE_CHECK_INSTANCE_CAST ((object),MIDGARD_CR_CORE_TYPE_QUERY_CONSTRAINT_SIMPLE, MidgardCRCoreQueryConstraintSimple))
#define MIDGARD_CR_CORE_IS_QUERY_CONSTRAINT_SIMPLE(object) (G_TYPE_CHECK_INSTANCE_TYPE ((object), MIDGARD_CR_CORE_TYPE_QUERY_CONSTRAINT_SIMPLE))
#define MIDGARD_CR_CORE_QUERY_CONSTRAINT_SIMPLE_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), MIDGARD_CR_CORE_TYPE_QUERY_CONSTRAINT_SIMPLE, MidgardCRCoreQueryConstraintSimpleIFace))

typedef struct _MidgardCRCoreQueryConstraintSimple MidgardCRCoreQueryConstraintSimple; /* dummy */
typedef struct _MidgardCRCoreQueryConstraintSimpleIFace MidgardCRCoreQueryConstraintSimpleIFace;
typedef struct _MidgardCRCoreQueryConstraintSimplePrivate MidgardCRCoreQueryConstraintSimplePrivate;

struct _MidgardCRCoreQueryConstraintSimpleIFace {
	GTypeInterface	parent;

	MidgardCRCoreQueryConstraintSimple	**(*list_constraints)	(MidgardCRCoreQueryConstraintSimple *self, guint *n_objects); 
	MidgardCRCoreQueryConstraintSimplePrivate *priv;
};

GType 				midgard_cr_core_query_constraint_simple_get_type		(void);
MidgardCRCoreQueryConstraintSimple	**midgard_cr_core_query_constraint_simple_list_constraints 	(MidgardCRCoreQueryConstraintSimple *self, guint *n_objects);

G_END_DECLS

#endif /* MIDGARD_CR_CORE_QUERY_CONSTRAINT_SIMPLE_H */
