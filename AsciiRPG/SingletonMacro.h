#ifndef SINGLETON_MACRO_H
#define SINGLETON_MACRO_H

#define SINGLETON(ClassName) \
public: \
    static ClassName& GetInstance() \
    { \
        if(nullptr == instance) \
        { \
            instance = new ClassName(); \
            instance->Init(); \
        } \
        return *instance; \
    } \
private: \
    ClassName() = default; \
    ~ClassName() = default; \
    ClassName(const ClassName&) = delete; \
    ClassName& operator=(const ClassName&) = delete; \
private: \
    static ClassName* instance;


#define SINGLETON_INITIALIZER(ClassName)\
ClassName* ClassName::instance = nullptr;


#endif // !SINGLETON_MACRO_H

