/*
    Numdiff - compare putatively similar files,
    ignoring small numeric differences
    Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014,
   2015, 2016, 2017  Ivano Primi  <ivprimi@libero.it>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "numdiff.h"
#include "xalloc.h"

ignorelist ignorelist_new(void) {
  ignorelist list;

  list = (ignorelist)xmalloc(sizeof(ignore_list_node));
  list->regular_expression = NULL;
  list->next = NULL;
  return list;
}

int ignorelist_add(ignorelist *plist, const char *def) {

  ignore_list_node *pnode;

  if (!def || !*def)
    return IGNORELIST_ERROR; /* no input */

  /* If we arrive here we are sure that *def != '\0' ! */
  pnode = (ignore_list_node *)xmalloc(sizeof(ignore_list_node));
  pnode->regular_expression = xstrdup(def);
  pnode->regular_expression[strlen(def)] = '\0';
  pnode->next = *plist;
  *plist = pnode;
  return IGNORELIST_OK;
}

/*
  Dispose the stack pointed to by PLIST (free and clean the memory).
 */

void ignorelist_dispose(ignorelist *plist) {
  ignore_list_node *pnode, *pnext;

  if (plist != NULL) {
    pnode = *plist;
    while (pnode != NULL) {
      pnext = pnode->next;
      if (pnode->regular_expression) {
        free((void *)pnode->regular_expression);
      }
      free((void *)pnode);
      pnode = pnext;
    }
    *plist = NULL;
  }
}
