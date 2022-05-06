#pragma once

template <class Z>
class ExtInterface
{
public:
    Z* proxy;
    uintptr_t ext;

    ExtInterface(uintptr_t ext, Z* ExtInterface)
    {
        this->ext = ext;
        this->proxy = ExtInterface;
    }
    
    ExtInterface() {};

    template <typename T>
    T Get(T* var)
    {
        T buffer;

        //resolve offset dynamically
        uintptr_t offset = (uintptr_t)var - (uintptr_t)proxy;

        //add offset to get to member variable
        uintptr_t extAddr = ext + offset;

        //Read it
        ReadProcessMemory(h_process, (void*)extAddr, &buffer, sizeof(buffer), nullptr);

        return buffer;
    }

    template <typename T>
    void Set(T* var, T value)
    {
        T buffer;
        uintptr_t offset = (uintptr_t)var - (uintptr_t)proxy;
        uintptr_t extAddr = ext + offset;
        WriteProcessMemory(h_process, (void*)extAddr, &value, sizeof(buffer), nullptr);
    }
};
