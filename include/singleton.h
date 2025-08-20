/**
# @File     : singleton.h
# @Author   : jade
# @Date     : 2025/8/18 19:35
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : singleton.h
*/
//

#ifndef SINGLETON_H
#define SINGLETON_H
/**
 * @brief The Singleton class
 */
template <typename T>
class Singleton {
public:
    static T *getInstance();
};

template <typename T>
T *Singleton<T>::getInstance() {
    static T *instance = new T();
    return instance;
}

#define SINGLETON(Class)                                                                           \
private:                                                                                           \
friend class Singleton<Class>;                                                                 \
\
public:                                                                                            \
static Class *getInstance() {                                                                  \
return Singleton<Class>::getInstance();                                                    \
}

#endif //SINGLETON_H
