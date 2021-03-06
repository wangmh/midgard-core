/* MidgardCore ObjectBuilder routines routines
 *    
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

#ifndef _MIDGARD_CR_CORE_SCHEMA_OBJECT_H_
#define _MIDGARD_CR_CORE_SCHEMA_OBJECT_H_

#include <glib-object.h>
#include "midgardcr.h"
#include "midgard_local.h"
#include "midgard_cr_core_object_builder.h"

GType midgard_cr_core_schema_object_register_type (MgdSchemaTypeAttr *type_data, GType parent_type);

#endif /* _MIDGARD_CR_CORE_SCHEMA_OBJECT_H_ */
