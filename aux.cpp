// --------------------------------------------------------------------------------------------
//  From cppreference: storage and linkage
// --------------------------------------------------------------------------------------------
#if 0
#include <iostream>
using namespace std;

int aux_global_static = 66;
extern int global_extern_static;
extern int global_internal_const;
extern int global_extern_const;
extern int unnamed_namespace_internal;

void aux_foo()
{
    cout << "[aux_foo]: global extern static: " << global_extern_static << endl;
    cout << "[aux_foo]: global extern const: " << global_extern_const << endl;
//    cout << "[aux_foo]: global internal const: " << global_internal_const << endl;
//    cout << "[aux_foo]: unnamed namespace internal: " << unnamed_namespace_internal << endl;
//    cout << "[aux_foo]: global extern enum: " << EXTERN_ENUM_CASE1 << endl;
}
#endif
