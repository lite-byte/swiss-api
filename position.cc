// swe.cc
#include <string.h>
#include "ephm/swephexp.h"
#include "position.h"

namespace SWE {

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::ObjectTemplate;
using v8::String;
using v8::Value;

Position::Position(const std::string& date) : date_(date) {
}

Position::~Position() {
}

void Position::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  Local<ObjectTemplate> addon_data_tpl = ObjectTemplate::New(isolate);
  addon_data_tpl->SetInternalFieldCount(1);  // 1 field for the MyObject::New()
  Local<Object> addon_data =
      addon_data_tpl->NewInstance(context).ToLocalChecked();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New, addon_data);
  tpl->SetClassName(String::NewFromUtf8(isolate, "Position").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "Calc", Calc);

  Local<Function> constructor = tpl->GetFunction(context).ToLocalChecked();
  addon_data->SetInternalField(0, constructor);
  exports->Set(context, String::NewFromUtf8(
      isolate, "Position").ToLocalChecked(),
      constructor).FromJust();
}

void Position::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    const char date = args[0]->IsUndefined() ?
        0 : args[0]->NumberValue(context).FromMaybe(0);
    Position* obj = new Position();
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Function> cons =
        args.Data().As<Object>()->GetInternalField(0)
            .As<Value>().As<Function>();
    Local<Object> result =
        cons->NewInstance(context, argc, argv).ToLocalChecked();
    args.GetReturnValue().Set(result);
  }
}

void Position::Calc(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  Position* obj = ObjectWrap::Unwrap<Position>(args.Holder());
  char *smon[] = {NULL, "January", "February", "March", "April", "May", "June", 
                        "July", "August", "September", "October", "November", "December"};
  char sdate[AS_MAXCH], snam[40], serr[AS_MAXCH];  
  int jday = 1, jmon = 1, jyear = 2022;
  double jut = 0.0;
  double tjd, te, x2[6];
  int32 iflag, iflgret;
  int p;
  swe_set_ephe_path("./ephe");
  iflag = SEFLG_SPEED;
  // parse date string to get day, month, year
  sscanf (obj->date_.c_str(), "%d%*c%d%*c%d", &jday,&jmon,&jyear);
  // we have day, month and year and convert to Julian day number
  if (jmon < 1 || jmon > 12) {
    printf("illegal month %d\n", jmon);
  }
  tjd = swe_julday(jyear,jmon,jday,jut,SE_GREG_CAL);        
  // compute Ephemeris time from Universal time by adding delta_t
  te = tjd + swe_deltat(tjd);
  printf("date: %02d %s %04d at 0:00 Universal time, jd=%.1lf\n", jday, smon[jmon], jyear, tjd);
  printf("planet     \tlongitude\tlatitude\tdistance\tspeed long.\n");
  for (p = SE_SUN; p <= SE_CHIRON; p++) { // a loop over all planets
    if (p == SE_EARTH) continue;
    swe_get_planet_name(p, snam); //  get the name of the planet p
    // do the coordinate calculation for this planet p
    iflgret = swe_calc(te, p, iflag, x2, serr);
    // if there is a problem, a negative value is returned and an error message is in serr.
    if (iflgret < 0) {
	    printf("%10s\terror: %s\n", snam, serr);
	    continue;
    }
    if (iflgret != iflag)
      printf("warning: iflgret != iflag. %s\n", serr);
    // print the coordinates
    printf("%10s\t%11.7f\t%10.7f\t%10.7f\t%10.7f\n",
    snam, x2[0], x2[1], x2[2], x2[3]);
  }
  tjd++;	// if date entry is empty, take next day
  swe_revjul(tjd, SE_GREG_CAL, &jyear, &jmon, &jday, &jut);

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, obj->date_.c_str()).ToLocalChecked());
}

}  // namespace SWE