//Simple example of a node interface.
//

#include <v8.h>
#include <node.h>

using namespace node;
using namespace v8;

//inherit from ObjectWrap. It apparently
//provides some utility for keeping track
//of shit that one needs to keep track of.
//
class NodeSimple: ObjectWrap
{
  private:
    int m_counter;

  public:

    //Persistent handle definition.  Provides connectivity
    //to a heap-allocated object.
    static Persistent<FunctionTemplate> s_ct;

    //This is how to initialize the simple object onto
    //the target that will be provided by Node.  Note that
    //methods that the object will contain are also declared
    //here.  The target is the module for this - it's where the
    //extension will be loaded into.
    static void Init(Handle<Object> target)
    {
      //Set scope.  See http://code.google.com/apis/v8/embed.html#handles
      //This can only be stack allocated, not heap allocated with new.
      HandleScope scope;

      //Create a function template for the "new" method.
      Local<FunctionTemplate> t = FunctionTemplate::New(New);
      s_ct = Persistent<FunctionTemplate>::New(t);

      //Set it for 1 internal field.
      s_ct->InstanceTemplate()->SetInternalFieldCount(1);

      //Give the class a name
      s_ct->SetClassName(String::NewSymbol("NodeSimple"));

      //This macro is used to bind the add method to this class.
      NODE_SET_PROTOTYPE_METHOD(s_ct, "add", Add);

      //Set this function template on the target.  Assign it to 
      //NodeSimple there, and voila - you're exposed to users.
      target->Set(String::NewSymbol("NodeSimple"),
          s_ct->GetFunction());
    }

    //This is the new method that v8 will call when
    //the class is being created.  Creates a normal c++
    //object, uses wrap from ObjectWrap to store a 
    //reference to teh C++ object inside args.This.
    static Handle<Value> New(const Arguments& args)
    {
      HandleScope scope;
      NodeSimple* ns = new NodeSimple();
      ns->Wrap(args.This());
      return args.This();
    }

    //This is the def for the Add method that was
    //bound in the init function above.  We can extract
    //a pointer to our class.  We compute the result,
    //and then return it while taking care of closing
    //the local scope.
    static Handle<Value> Add(const Arguments& args)
    {
      HandleScope scope;
      NodeSimple* ns = ObjectWrap::Unwrap<NodeSimple>(args.This());
      Local<Integer> result = Integer::New(2 + 3);
      return scope.Close(result);
    }

    NodeSimple() :
      m_counter(0)
    {
    }

    ~NodeSimple()
    {
    }

};

//Node.js can use code loaded from a shared object.
extern "C" {
  static void init (Handle<Object> target)
  {
    NodeSimple::Init(target);
  }

  NODE_MODULE(nodesimple, init);
}
