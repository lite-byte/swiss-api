// swe.cc
#include <node.h>
#include "position.h"

namespace SWE {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
  Position::Init(exports);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, InitAll)

}  // namespace SWE