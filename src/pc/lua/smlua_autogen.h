#ifndef SMLUA_AUTOGEN_H
#define SMLUA_AUTOGEN_H

//
// Autogen macros
//

// A macro to tell autogen which function parameters are modified during the function call and should be pushed again
// Only works with Vec3, Mat4 and Color types
#define OUT

// A macro to tell autogen this parameter can be omitted and replaced by 'nil' during a function call
// Optional parameters must be contiguous until the last parameter (a mandatory parameter following an optional parameter is not allowed)
#define OPTIONAL

#endif // SMLUA_AUTOGEN_H
