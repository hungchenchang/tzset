
//#define __NAN__

#ifdef __NAN__

#include <node.h>
#include <v8.h>
#include <time.h>
#include <nan.h>

using namespace v8;
using v8::Date;
using v8::Isolate;


void tzset(const Nan::FunctionCallbackInfo<v8::Value>& args)
{
  //printf("tzset is caled args = %d\n", args.Length());
  Isolate *isolate = Isolate::GetCurrent();
#ifdef _WIN32
  _tzset();
#else
  tzset();
#endif
  Date::DateTimeConfigurationChangeNotification(isolate);
  int result = 0;
  v8::Local<v8::Number> num = Nan::New(result);
  args.GetReturnValue().Set(num);
}

void Init(Handle<Object> exports) {
  exports->Set(Nan::New("tzset").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(tzset)->GetFunction());
}

NODE_MODULE(tzset, Init)

#else

#define NAPI_VERSION 3
#include <node_api.h>
#include <v8.h>
#include <time.h>

using namespace v8;
using v8::Date;
using v8::Isolate;

napi_value tzset(napi_env env, napi_callback_info args)
{
    napi_status status;

    Isolate *isolate = Isolate::GetCurrent();
#ifdef _WIN32
    _tzset();
#else
    tzset();
#endif
    Date::DateTimeConfigurationChangeNotification(isolate);
    int result = 0;
    napi_value retvalue;
    status = napi_create_int64(env, result, &retvalue);
    if (status != napi_ok) return nullptr;
    return retvalue;
}

napi_value Init(napi_env env, napi_value exports) 
{
  napi_status status;
  napi_value fn;

  status = napi_create_function(env, nullptr, 0, tzset, nullptr, &fn);
  if (status != napi_ok) return nullptr;

  status = napi_set_named_property(env, exports, "tzset", fn);
  if (status != napi_ok) return nullptr;
  return exports;
}

NAPI_MODULE(tzset, Init)

#endif
