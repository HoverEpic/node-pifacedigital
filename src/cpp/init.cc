#include <node.h>
#include "NPIFaceDigital.h"

using namespace v8;

void Initialize(Local<Object> exports) {
  PIFaceDigital::Init(exports);
}

NODE_MODULE(pifacedigital, Initialize)
