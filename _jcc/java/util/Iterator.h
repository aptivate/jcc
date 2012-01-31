/*
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#ifndef _Iterator_H
#define _Iterator_H

#include <Python.h>
#include "JObject.h"

namespace java {
    namespace lang {
        class Class;
        class Object;
    }        
    namespace util {
        using namespace java::lang;

        class Iterator : public JObject {
        public:
            static Class *class$;
            static jmethodID *mids$;
            static jclass initializeClass();

            explicit Iterator(jobject obj) : JObject(obj) {
                initializeClass();
            }

            jboolean hasNext() const;
            Object next() const;
        };

        extern PyTypeObject PY_TYPE(Iterator);

        class t_Iterator {
        public:
            PyObject_HEAD
            Iterator object;
#ifdef _java_generics
            PyTypeObject *parameters[1];
            static PyTypeObject **parameters_(t_Iterator *self)
            {
                return (PyTypeObject **) &(self->parameters);
            }
#endif
            static PyObject *wrap_Object(const Iterator& object);
            static PyObject *wrap_jobject(const jobject& object);
#ifdef _java_generics
            static PyObject *wrap_Object(const Iterator& object,
                                         PyTypeObject *T);
            static PyObject *wrap_jobject(const jobject& object,
                                          PyTypeObject *T);
#endif
        };
    }
}

#endif /* _Iterator_H */
