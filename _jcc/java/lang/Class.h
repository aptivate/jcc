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

#ifndef _Class_H
#define _Class_H

#include <Python.h>
#include "JArray.h"
#include "java/lang/Object.h"

namespace java {
    namespace lang {
        namespace reflect {
            class Method;
            class Constructor;
            class Field;
#ifdef _java_generics
            class Type;
            class TypeVariable;
#endif
        }

        using namespace reflect;

        class Class : public Object {
        public:
            static Class *class$;
            static jmethodID *_mids;
            static jclass initializeClass();

            explicit Class(jobject obj) : Object(obj) {
                initializeClass();
            }
            Class(const Class& obj) : Object(obj) {}

            static Class forName(const String& className);
            JArray<Method> getDeclaredMethods() const;
            JArray<Method> getMethods() const;
            Method getMethod(const String &name, const JArray<Class>& params) const;
            Method getDeclaredMethod(const String &name, const JArray<Class>& params) const;
            JArray<Constructor> getDeclaredConstructors() const;
            JArray<Field> getDeclaredFields() const;
            JArray<Class> getDeclaredClasses() const;
            int isArray() const;
            int isPrimitive() const;
            int isInterface() const;
            int isAssignableFrom(const Class& obj) const;
            Class getComponentType() const;
            Class getSuperclass() const;
            Class getDeclaringClass() const;
            Class getEnclosingClass() const;
            JArray<Class> getInterfaces() const;
            String getName() const;
            int getModifiers() const;
            int isInstance(const Object &obj) const;
#ifdef _java_generics
            JArray<TypeVariable> getTypeParameters() const;
            JArray<Type> getGenericInterfaces() const;
            Type getGenericSuperclass() const;
#endif
        };

        extern PyTypeObject PY_TYPE(Class);

        class t_Class {
        public:
            PyObject_HEAD
            Class object;
#ifdef _java_generics
            PyTypeObject *parameters[1];
            static PyTypeObject **parameters_(t_Class *self)
            {
                return (PyTypeObject **) &(self->parameters);
            }
#endif
            static PyObject *wrap_Object(const Class& object);
#ifdef _java_generics
            static PyObject *wrap_Object(const Class& object, PyTypeObject *T);
#endif
            static PyObject *wrap_jobject(const jobject& object);
        };
    }
}

#endif /* _Class_H */
