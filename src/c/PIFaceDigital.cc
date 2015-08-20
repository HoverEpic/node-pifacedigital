#include "PIFaceDigital.h"

v8::Persistent<FunctionTemplate> PIFaceDigital::constructor;

void PIFaceDigital::Init(Handle<Object> target) {
	NanScope();

	//Class
  Local<FunctionTemplate> ctor = NanNew<FunctionTemplate>(PIFaceDigital::New);
  NanAssignPersistent(constructor, ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(NanNew("PIFaceDigital"));

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(ctor, "get", Get);
  NODE_SET_PROTOTYPE_METHOD(ctor, "set", Set);
	NODE_SET_PROTOTYPE_METHOD(ctor, "open", Open);
	NODE_SET_PROTOTYPE_METHOD(ctor, "close", Close);
}

NAN_METHOD(PIFaceDigital::New) {
  NanScope();
	if (args.This()->InternalFieldCount() == 0){
    NanThrowTypeError("Cannot instantiate without new");
  }
  PIFaceDigital *pifacedigital;
  if (args.Length() == 0){
    pifacedigital = new PIFaceDigital;
  } else if (args.Length() == 1){
    pifacedigital = new PIFaceDigital( args[0]->IntegerValue() );
  }
  pifacedigital->Wrap(args.Holder());
  NanReturnValue(args.Holder());
}

PIFaceDigital::PIFaceDigital(): ObjectWrap() {
	hw_addr = 0;
}


PIFaceDigital::PIFaceDigital(int addr): ObjectWrap() {
  hw_addr = addr;
}

NAN_METHOD(PIFaceDigital::Open){
  SETUP_FUNCTION(PIFaceDigital)
  self->pifacedigital_open(hw_addr);
}

NAN_METHOD(PIFaceDigital::Close){
  SETUP_FUNCTION(PIFaceDigital)
  self->pifacedigital_close(hw_addr);
}

NAN_METHOD(PIFaceDigital::Set){
	SETUP_FUNCTION(PIFaceDigital)

  if(args.Length() == 2) {
  	int i = args[0]->IntegerValue();
  	int j = args[1]->IntegerValue();
    pifacedigital_digital_write(i,j);
  } else {
    NanThrowTypeError( "Invalid number of arguments" );
  }

	NanReturnUndefined();
}

NAN_METHOD(PIFaceDigital::Get){
	SETUP_FUNCTION(PIFaceDigital)
  int res = 0;
  if(args.Length() == 1) {
  	int i = args[0]->IntegerValue();
    res = pifacedigital_digital_read(i);
  } else {
    NanThrowTypeError( "Invalid number of arguments" );
  }

	NanReturnValue(res);
}
