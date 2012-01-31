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

#include <jni.h>
#include "JCCEnv.h"
#include "JArray.h"

#include "java/lang/Class.h"
#include "java/lang/Object.h"
#include "java/lang/String.h"
#include "java/lang/reflect/Method.h"
#ifdef _java_generics
#include "java/lang/reflect/Type.h"
#include "java/lang/reflect/TypeVariable.h"
#endif

namespace java {
    namespace lang {
        namespace reflect {

            enum {
                mid_getModifiers,
                mid_getReturnType,
                mid_getName,
                mid_getParameterTypes,
                mid_getExceptionTypes,
                mid_getDeclaringClass,
#ifdef _java_generics
                mid_getTypeParameters,
                mid_getGenericExceptionTypes,
                mid_getGenericParameterTypes,
                mid_getGenericReturnType,
#endif
                max_mid
            };

            Class *Method::class$ = NULL;
            jmethodID *Method::_mids = NULL;

            jclass Method::initializeClass()
            {
                if (!class$)
                {
                    jclass cls = env->findClass("java/lang/reflect/Method");

                    _mids = new jmethodID[max_mid];
                    _mids[mid_getModifiers] =
                        env->getMethodID(cls, "getModifiers",
                                         "()I");
                    _mids[mid_getReturnType] =
                        env->getMethodID(cls, "getReturnType",
                                         "()Ljava/lang/Class;");
                    _mids[mid_getName] =
                        env->getMethodID(cls, "getName",
                                         "()Ljava/lang/String;");

                    _mids[mid_getParameterTypes] =
                        env->getMethodID(cls, "getParameterTypes",
                                         "()[Ljava/lang/Class;");
                    _mids[mid_getExceptionTypes] =
                        env->getMethodID(cls, "getExceptionTypes",
                                         "()[Ljava/lang/Class;");
                    _mids[mid_getDeclaringClass] =
                        env->getMethodID(cls, "getDeclaringClass",
                                         "()Ljava/lang/Class;");
#ifdef _java_generics
                    _mids[mid_getTypeParameters] =
                        env->getMethodID(cls, "getTypeParameters",
                                         "()[Ljava/lang/reflect/TypeVariable;");
                    _mids[mid_getGenericExceptionTypes] =
                        env->getMethodID(cls, "getGenericExceptionTypes",
                                         "()[Ljava/lang/reflect/Type;");
                    _mids[mid_getGenericParameterTypes] =
                        env->getMethodID(cls, "getGenericParameterTypes",
                                         "()[Ljava/lang/reflect/Type;");
                    _mids[mid_getGenericReturnType] =
                        env->getMethodID(cls, "getGenericReturnType",
                                         "()Ljava/lang/reflect/Type;");
#endif

                    class$ = (Class *) new JObject(cls);
                }
                
                return (jclass) class$->this$;
            }

            int Method::getModifiers() const
            {
                return env->callIntMethod(this$, _mids[mid_getModifiers]);
            }

            Class Method::getReturnType() const
            {
                return Class(env->callObjectMethod(this$, _mids[mid_getReturnType]));
            }

            String Method::getName() const
            {
                return String(env->callObjectMethod(this$, _mids[mid_getName]));
            }

            JArray<Class> Method::getParameterTypes() const
            {
                jobjectArray array = (jobjectArray)
                    env->callObjectMethod(this$, _mids[mid_getParameterTypes]);

                return JArray<Class>(array);
            }

            JArray<Class> Method::getExceptionTypes() const
            {
                jobjectArray array = (jobjectArray)
                    env->callObjectMethod(this$, _mids[mid_getExceptionTypes]);

                return JArray<Class>(array);
            }

            Class Method::getDeclaringClass() const
            {
                return Class(env->callObjectMethod(this$, _mids[mid_getDeclaringClass]));
            }

#ifdef _java_generics
            JArray<TypeVariable> Method::getTypeParameters() const
            {
                return JArray<TypeVariable>(env->callObjectMethod(this$, _mids[mid_getTypeParameters]));
            }

            JArray<Type> Method::getGenericExceptionTypes() const
            {
                return JArray<Type>(env->callObjectMethod(this$, _mids[mid_getGenericExceptionTypes]));
            }

            JArray<Type> Method::getGenericParameterTypes() const
            {
                return JArray<Type>(env->callObjectMethod(this$, _mids[mid_getGenericParameterTypes]));
            }

            Type Method::getGenericReturnType() const
            {
                return Type(env->callObjectMethod(this$, _mids[mid_getGenericReturnType]));
            }
#endif
        }
    }
}


#include "structmember.h"
#include "functions.h"
#include "macros.h"

namespace java {
    namespace lang {
        namespace reflect {

            static PyObject *t_Method_cast_(PyTypeObject *type, PyObject *arg);
            static PyObject *t_Method_instance_(PyTypeObject *type, PyObject *arg);
            static PyObject *t_Method_getModifiers(t_Method *self);
            static PyObject *t_Method_getReturnType(t_Method *self);
            static PyObject *t_Method_getName(t_Method *self);
            static PyObject *t_Method_getParameterTypes(t_Method *self);
            static PyObject *t_Method_getExceptionTypes(t_Method *self);
            static PyObject *t_Method_getDeclaringClass(t_Method *self);
#ifdef _java_generics
            static PyObject *t_Method_getTypeParameters(t_Method *self);
            static PyObject *t_Method_getGenericExceptionTypes(t_Method *self);
            static PyObject *t_Method_getGenericParameterTypes(t_Method *self);
            static PyObject *t_Method_getGenericReturnType(t_Method *self);
#endif

            static PyMethodDef t_Method__methods_[] = {
                DECLARE_METHOD(t_Method, cast_, METH_O | METH_CLASS),
                DECLARE_METHOD(t_Method, instance_, METH_O | METH_CLASS),
                DECLARE_METHOD(t_Method, getModifiers, METH_NOARGS),
                DECLARE_METHOD(t_Method, getReturnType, METH_NOARGS),
                DECLARE_METHOD(t_Method, getName, METH_NOARGS),
                DECLARE_METHOD(t_Method, getParameterTypes, METH_NOARGS),
                DECLARE_METHOD(t_Method, getExceptionTypes, METH_NOARGS),
                DECLARE_METHOD(t_Method, getDeclaringClass, METH_NOARGS),
#ifdef _java_generics
                DECLARE_METHOD(t_Method, getTypeParameters, METH_NOARGS),
                DECLARE_METHOD(t_Method, getGenericExceptionTypes, METH_NOARGS),
                DECLARE_METHOD(t_Method, getGenericParameterTypes, METH_NOARGS),
                DECLARE_METHOD(t_Method, getGenericReturnType, METH_NOARGS),
#endif
                { NULL, NULL, 0, NULL }
            };

            DECLARE_TYPE(Method, t_Method, Object, Method,
                         abstract_init, 0, 0, 0, 0, 0);

            static PyObject *t_Method_cast_(PyTypeObject *type, PyObject *arg)
            {
                if (!(arg = castCheck(arg, Method::initializeClass, 1)))
                    return NULL;
                return t_Method::wrap_Object(Method(((t_Method *) arg)->object.this$));
            }

            static PyObject *t_Method_instance_(PyTypeObject *type, PyObject *arg)
            {
                if (!castCheck(arg, Method::initializeClass, 0))
                    Py_RETURN_FALSE;
                Py_RETURN_TRUE;
            }

            static PyObject *t_Method_getModifiers(t_Method *self)
            {
                jint modifiers;

                OBJ_CALL(modifiers = self->object.getModifiers());
                return PyInt_FromLong(modifiers);
            }

            static PyObject *t_Method_getReturnType(t_Method *self)
            {
                Class cls((jobject) NULL);

                OBJ_CALL(cls = self->object.getReturnType());
                return t_Class::wrap_Object(cls);
            }

            static PyObject *t_Method_getName(t_Method *self)
            {
                String name((jobject) NULL);

                OBJ_CALL(name = self->object.getName());
                return j2p(name);
            }

            static PyObject *t_Method_getParameterTypes(t_Method *self)
            {
                JArray<Class> types((jobject) NULL);

                OBJ_CALL(types = self->object.getParameterTypes());
                return types.toSequence(t_Class::wrap_Object);
            }

            static PyObject *t_Method_getExceptionTypes(t_Method *self)
            {
                JArray<Class> types((jobject) NULL);

                OBJ_CALL(types = self->object.getExceptionTypes());
                return types.toSequence(t_Class::wrap_Object);
            }

            static PyObject *t_Method_getDeclaringClass(t_Method *self)
            {
                Class cls((jobject) NULL);

                OBJ_CALL(cls = self->object.getDeclaringClass());
                return t_Class::wrap_Object(cls);
            }

#ifdef _java_generics
            static PyObject *t_Method_getTypeParameters(t_Method *self)
            {
                JArray<TypeVariable> result((jobject) NULL);
                OBJ_CALL(result = self->object.getTypeParameters());

                return result.toSequence(t_TypeVariable::wrap_Object);
            }

            static PyObject *t_Method_getGenericExceptionTypes(t_Method *self)
            {
                JArray<Type> result((jobject) NULL);
                OBJ_CALL(result = self->object.getGenericExceptionTypes());

                return result.toSequence(t_Type::wrap_Object);
            }

            static PyObject *t_Method_getGenericParameterTypes(t_Method *self)
            {
                JArray<Type> result((jobject) NULL);
                OBJ_CALL(result = self->object.getGenericParameterTypes());

                return result.toSequence(t_Type::wrap_Object);
            }

            static PyObject *t_Method_getGenericReturnType(t_Method *self)
            {
                Type result((jobject) NULL);
                OBJ_CALL(result = self->object.getGenericReturnType());

                return t_Type::wrap_Object(result);
            }
#endif
        }
    }
}
