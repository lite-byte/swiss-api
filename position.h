// swe_addon.h
#ifndef SWE_ADDON_H
#define SWE_ADDON_H

#include <string.h>
#include <node.h>
#include <node_object_wrap.h>

namespace SWE {

class Position : public node::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit Position(const std::string& date = "01.01.2023");
  ~Position();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Calc(const v8::FunctionCallbackInfo<v8::Value>& args);

  const std::string date_;
};

}  // namespace SWE

#endif