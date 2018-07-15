#ifndef CLASS_FACTORY_H
#define CLASS_FACTORY_H

namespace Common
{

template<typename Class, typename Base>
shared_ptr<Base> create_shared()
{
    return dynamic_pointer_cast<Base>(make_shared<Class>());
}

template<typename Interface, typename Base>
shared_ptr<Interface> query_interface(shared_ptr<Base> ptr)
{
    return dynamic_pointer_cast<Interface>(ptr);
}

template <
    typename Class_id,
    typename Base,
    typename Factory_function
>
class Factory
{
public:
    bool register_class(Class_id clsid, Factory_function creator)
    {
        return (associations_.insert({clsid, creator}).second);
    }

    std::shared_ptr<Base> create_object(Class_id clsid)
    {
        auto it = associations_.find(clsid);
        if (it != associations_.end())
            return it->second();
        else
            return nullptr;
    }

    template<typename Interface>
    std::shared_ptr<Interface> create_object(Class_id clsid)
    {
        auto it = associations_.find(clsid);
        if (it != associations_.end())
            return dynamic_pointer_cast<Interface>(it->second());
        else
            return nullptr;
    }

private:
    map<Class_id, Factory_function> associations_;
};

}

#endif // CLASS_FACTORY_H
