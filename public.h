#ifndef PUBLIC_H
#define PUBLIC_H

namespace Common
{
    enum CLSID_type {
        CLSID_Class1 = 0,
        CLSID_Class2
    };

    class ICommon
    {
    public:
        virtual ~ICommon() {}
    };
}

#endif // PUBLIC_H
