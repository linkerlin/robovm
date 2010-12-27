#include <nullvm.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

jint Java_java_lang_System_identityHashCode(JNIEnv* env, jclass clazz, jobject o) {
    return (jint) o;
}

jlong Java_java_lang_System_currentTimeMillis(JNIEnv* env, jclass clazz) {
    struct timeval tv;
    gettimeofday(&tv, (struct timezone *) NULL);
    jlong millis = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
    return millis;
}

jstring Java_java_lang_System_getEncoding(JNIEnv* env, jclass clazz, jint type) {
    if (type == 1) {
        return (*env)->NewStringUTF(env, "UTF-8");
    }
    return NULL;
}

static jboolean setProperty(Env* env, ObjectArray** props, jint index, char* name, char* value) {
    if (*props == NULL || index >= (*props)->length / 2) {
        jint length = *props == NULL ? 10 : (*props)->length * 2;
        ObjectArray* newProps = nvmNewObjectArray(env, length, java_lang_String, NULL, NULL);
        if (!newProps) return FALSE;
        if (*props) {
            jint i;
            for (i = 0; i < (*props)->length; i++) {
                newProps->values[i] = (*props)->values[i];
            }
        }
        *props = newProps;
    }
    Object* n = nvmNewStringUTF(env, name, -1);
    if (!n) return FALSE;
    Object* v = nvmNewStringUTF(env, value, -1);
    if (!v) return FALSE;
    index <<= 1;
    (*props)->values[index++] = n;
    (*props)->values[index++] = v;
    return TRUE;
}

ObjectArray* Java_java_lang_System_getPropertyList(Env* env, Class* clazz) {
    ObjectArray* props = NULL;

    jint i = 0;
    if (!setProperty(env, &props, i++, "java.boot.class.path", "")) return NULL;
    if (!setProperty(env, &props, i++, "java.class.path", "")) return NULL;
    if (!setProperty(env, &props, i++, "java.class.version", "46.0")) return NULL;
    if (!setProperty(env, &props, i++, "java.compiler", "")) return NULL;
    if (!setProperty(env, &props, i++, "java.ext.dirs", "")) return NULL;
    if (!setProperty(env, &props, i++, "java.home", "")) return NULL;
    if (!setProperty(env, &props, i++, "java.io.tmpdir", "/tmp")) return NULL;
    if (getenv("LD_LIBRARY_PATH")) {
        if (!setProperty(env, &props, i++, "java.library.path", getenv("LD_LIBRARY_PATH"))) return NULL;
    } else {
        if (!setProperty(env, &props, i++, "java.library.path", "")) return NULL;
    }

    if (!setProperty(env, &props, i++, "java.net.preferIPv6Addresses", "true")) return NULL;

    if (!setProperty(env, &props, i++, "java.vendor", "NullVM")) return NULL;
    if (!setProperty(env, &props, i++, "java.vendor.url", "http://www.nullvm.org/")) return NULL;
    if (!setProperty(env, &props, i++, "java.version", "0")) return NULL;

    // TODO: Set java.vm.* and java.specification.*

    // TODO: Don't hard code these
    if (!setProperty(env, &props, i++, "os.arch", "amd64")) return NULL;
    if (!setProperty(env, &props, i++, "os.name", "Linux")) return NULL;
    if (!setProperty(env, &props, i++, "os.version", "2.6.32-24-generic")) return NULL;
    if (!setProperty(env, &props, i++, "user.home", getenv("HOME"))) return NULL;
    if (!setProperty(env, &props, i++, "user.name", getenv("USER"))) return NULL;
    char path[PATH_MAX];
    if (!setProperty(env, &props, i++, "user.dir", getcwd(path, sizeof(path)))) return NULL;
    if (!setProperty(env, &props, i++, "file.separator", "/")) return NULL;
    if (!setProperty(env, &props, i++, "line.separator", "\n")) return NULL;
    if (!setProperty(env, &props, i++, "path.separator", ":")) return NULL;
    if (!setProperty(env, &props, i++, "file.encoding", "UTF-8")) return NULL;
    if (!setProperty(env, &props, i++, "user.language", "en")) return NULL;
    if (!setProperty(env, &props, i++, "user.region", "US")) return NULL;
    // TODO: user.timezone

    return props;
}
