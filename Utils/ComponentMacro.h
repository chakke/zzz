
#ifndef HoverUp_ComponentMacro_h
#define HoverUp_ComponentMacro_h

#define CREATE_FUNC_NAME(__TYPE__) \
static __TYPE__* create(const std::string& name) \
{ \
__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
if (pRet && pRet->init()) \
{ \
pRet->setName(name); \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = NULL; \
return NULL; \
} \
}

#endif
