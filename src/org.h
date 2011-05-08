/* 
 *	geoip.cc - node.JS to C++ glue code for the GeoIP C library
 *	Written by Joe Vennix on March 15, 2011
 *	For the GeoIP C library, go here: http://www.maxmind.com/app/c
 *		./configure && make && sudo make install
 */

#ifndef NODE_GEOIP_ORG_H
#define NODE_GEOIP_ORG_H

#include <v8.h>
#include <node.h>
#include "node_geoip.h"

using namespace v8;
using namespace node;

namespace geoip {
  class Org: ObjectWrap
  {
    private:
      GeoIP *db;

      int db_edition;

      static Persistent<FunctionTemplate> constructor_template;

    protected:
      static Handle<Value> New(const Arguments& args);

    public:
      static void Init(Handle<Object> target);


      static Handle<Value> lookupSync(const Arguments &args);

      static Handle<Value> lookup(const Arguments& args);

      static int EIO_Org(eio_req *req);

      static int EIO_AfterOrg(eio_req *req);

      static Handle<Value> close(const Arguments &args);
  };
}

struct org_baton_t {
  geoip::Org * o;
  char host_cstr[256];
  char *org;
  int increment_by;
  int sleep_for;
  Persistent<Function> cb;
};

#endif /* NODE_GEOIP_ORG_H */