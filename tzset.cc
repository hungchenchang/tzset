#include <nan.h>

using namespace v8;

void tzset(const Nan::FunctionCallbackInfo<v8::Value>& args)
{
  //printf("tzset is caled args = %d\n", args.Length());
#ifdef _WIN32
  _tzset();
#else
  tzset();
#endif
  int result = 0;
  v8::Local<v8::Number> num = Nan::New(result);
  args.GetReturnValue().Set(num);
}

void Init(Handle<Object> exports) {
  exports->Set(Nan::New("tzset").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(tzset)->GetFunction());
}

NODE_MODULE(tzset, Init)
