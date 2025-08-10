#pragma once

#include <vector>
#include <iostream>
#include <stdio.h>

#include "DLL_Build.h"

template <typename returnType, typename... args>
class DelegateBase
{
public:
    DelegateBase() = default;
    ~DelegateBase() = default;
	virtual returnType Invoke(args... parameters) = 0;
};

template<typename classType, typename returnType, typename... args> class Delegate : public DelegateBase<returnType, args...>
{
public:

    //Called as Delegate(ClassInstance, &Class::FuncName, Args...)
    Delegate(classType* classInstance, returnType(classType::* pFunction)(args...))
    {
        this->classInstance = classInstance;
        this->pFunction = pFunction;
    }
    ~Delegate() = default;

    void Invoke(args... parameters) override
    {
        if(pFunction == nullptr)
        {
            LOG_ERROR("pFunction is null");
            return;
        }
        if(classInstance == nullptr)
        {
            LOG_ERROR("classInstance is null");
            return;
        }
        (*classInstance.*pFunction)(parameters...);
    }

    //Should be called before freeing Delegate
    void Destroy()
    {
        delete classInstance;
        delete pFunction;
    }

private:
    classType* classInstance;
    returnType(classType::*pFunction)(args...);
};

//Can hold multiple functions if their return type and arguments match
template <typename returnType, typename... args> class DLL_API Event
{
public:
    Event() = default;
    ~Event()
    {
        for(int i = 0; i < delegates.size(); i++)
        {
            delegates[i].Destroy();
            delete delegates[i];
            delete pFuncs[i];
        }
        classesPtr.clear();
    }

    //Add function pointer to Invoke list
    //Called as AddDelegate(ClassInstance, &Class::FuncName, Args...)
    template<typename classType>
    void AddEvent(classType* classInstance, returnType(classType::*pFunction)(args...))
    {
        auto del = new Delegate<classType, returnType, args...>(classInstance, pFunction);
        auto baseDel = new Delegate<DelegateBase<returnType, args...>, returnType, args...>(del, &DelegateBase<returnType, args...>::Invoke);

        classesPtr.push_back(classInstance);
        //casting function pointer to void* is allowed because its only being used to compare memory addresses later
        pFuncs.push_back(reinterpret_cast<void*>(pFunction));
        delegates.push_back(*baseDel);
    }

    //Will remove function pointer from Invoke list if classInstance and pFunction are found in Event
    template<typename classType>
    void RemoveEvent(classType* classInstance, returnType(classType::*pFunction)(args...))
    {
        for(int i = 0; delegates.size(); i++)
        {
            if(classInstance == classesPtr[i] && reinterpret_cast<void*>(pFunction) == pFuncs[i])
            {
                classesPtr.erase(classesPtr.begin() + i);
                pFuncs.erase(pFuncs.begin() + i);
                delegates.erase(delegates.begin() + i);
                return;
            }
        }
    }

    void Invoke(args... parameters)
    {
        for(int i = 0; i < delegates.size(); i++)
        {
            delegates[i].Invoke(parameters...);
        }
    }

private:
    std::vector<void*> classesPtr;
    std::vector<void*> pFuncs;
    std::vector<Delegate<DelegateBase<returnType, args...>, returnType, args...>> delegates;
};