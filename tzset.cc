#include <nan.h>
#include <node.h>
#include <v8.h>
#include <time.h>

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
