/* ====================================================================
 * Copyright (c) 2000 Gregory Trubetskoy.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution, if
 *    any, must include the following acknowledgment: "This product 
 *    includes software developed by Gregory Trubetskoy."
 *    Alternately, this acknowledgment may appear in the software itself, 
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "mod_python", "modpython" or "Gregory Trubetskoy" must not 
 *    be used to endorse or promote products derived from this software 
 *    without prior written permission. For written permission, please 
 *    contact grisha@modpython.org.
 *
 * 5. Products derived from this software may not be called "mod_python"
 *    or "modpython", nor may "mod_python" or "modpython" appear in their 
 *    names without prior written permission of Gregory Trubetskoy.
 *
 * THIS SOFTWARE IS PROVIDED BY GREGORY TRUBETSKOY ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL GREGORY TRUBETSKOY OR
 * HIS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * util.c 
 *
 * $Id: util.c,v 1.4 2001/11/03 04:24:30 gtrubetskoy Exp $
 *
 * See accompanying documentation and source code comments 
 * for details.
 *
 */

#include "mod_python.h"

/**
 ** tuple_from_array_header
 **
 *   Given an array header return a tuple. The array elements
 *   assumed to be strings.
 */

PyObject * tuple_from_array_header(const apr_array_header_t *ah)
{

    PyObject *t;
    int i;
    char **s;

    if (ah == NULL)
    {
	Py_INCREF(Py_None);
	return Py_None;
    }
    else
    {
	t = PyTuple_New(ah->nelts);

	s = (char **) ah->elts;
	for (i = 0; i < ah->nelts; i++) {
	    PyTuple_SetItem(t, i, PyString_FromString(s[i]));
	}
	return t;
    }
}

/**
 ** tuple_from_method_list
 **
 *   Given an apr_method_list_t return a tuple. 
 */

PyObject * tuple_from_method_list(const ap_method_list_t *l)
{

    PyObject *t;
    int i;
    char **methods;

    if ((l->method_list == NULL) || (l->method_list->nelts == 0)) {
	Py_INCREF(Py_None);
	return Py_None;
    }
    else {
	t = PyTuple_New(l->method_list->nelts);
	
	methods = (char **)l->method_list->elts;
	for (i = 0; i < l->method_list->nelts; ++i) {
	    PyTuple_SetItem(t, i, PyString_FromString(methods[i]));
	}
	return t;
    }
}

/**
 ** python_decref
 ** 
 *   This helper function is used with apr_pool_cleanup_register to destroy
 *   python objects when a certain pool is destroyed.
 */

apr_status_t python_decref(void *object)
{
    Py_XDECREF((PyObject *) object);
    return 0;
}



