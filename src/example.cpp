#include <pybind11/pybind11.h>

#include <ImathBox.h>
#include <ImfIO.h>
#include <Iex.h>
#include <ImfArray.h>
#include <ImfAttribute.h>
#include <ImfBoxAttribute.h>
#include <ImfChannelList.h>
#include <ImfStandardAttributes.h>
#include <ImfChannelListAttribute.h>
#include <ImfChromaticitiesAttribute.h>
#include <ImfCompressionAttribute.h>
#include <ImfDoubleAttribute.h>
#include <ImfEnvmapAttribute.h>
#include <ImfFloatAttribute.h>
#include <ImfHeader.h>
#include <ImfInputFile.h>
#include <ImfIntAttribute.h>
#include <ImfKeyCodeAttribute.h>
#include <ImfLineOrderAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfOutputFile.h>
#include <ImfPreviewImageAttribute.h>
#include <ImfStringAttribute.h>
#include <ImfTileDescriptionAttribute.h>
#include <ImfTiledOutputFile.h>
#include <ImfTimeCodeAttribute.h>
#include <ImfVecAttribute.h>
#include <ImfFloatVectorAttribute.h>
#include <ImfVersion.h>

#include <ImfRationalAttribute.h>
#include <ImfRational.h>
#include <ImfKeyCodeAttribute.h>
#include <ImfKeyCode.h>
#include <ImfTimeCodeAttribute.h>
#include <ImfTimeCode.h>

#include <iostream>
#include <iomanip>
#include <iostream>
#include <vector>


using namespace std;
using namespace Imf;
using namespace Imath;

namespace py = pybind11;

int add(int i, int j) {
    // Box2i b = Box2i(0,0,1,2);
    // Vec2 v = Vec2(1,2);
    return i + j;
}

V2i vec_test_cpp(){
    return V2i(1,2);
}

/*
take input V2i as input
auto convert to V2i (aaa)
Create a new value using PyIlmbase; 
explicitly convert to V2i and perform operation
return imath.V2i object
*/
V2i vec_test_cpp2(V2i aaa){
  auto b = py::module::import("imath").attr("V2i")(1, 1);
  // Vec2<int> bbb(b.attr("x").cast<int>(), b.attr("y").cast<int>());
  Vec2<int> bbb(b.cast<V2i>());
  cout << aaa + bbb << endl;
  return aaa + bbb;
}

void test_header(){

    // InputFile ii = InputFile("/tmp/ies_A2.exr", 1); // not working
    InputFile ii("/tmp/ies_A2.exr");  // working
    Header h = ii.header();
    cout << h.screenWindowWidth() << endl;

    StringAttribute astr("BB----");
    // astr.set("CC");
    // f.*get(_value) = "CC"

    h.insert("BB", astr);
    StringAttribute *aa = h.findTypedAttribute<StringAttribute>("BB");
    cout << aa->value() << "___" <<endl;


    Header::Iterator it;
    for (it=h.begin(); it!=h.end(); ++it){
        // cout << "attrib: " << it.name() << endl;

        Attribute * bb;
        if (bb=dynamic_cast<StringAttribute *>(h.findTypedAttribute<StringAttribute>(it.name()))){
                cout << "attrib: " << it.name() << " StringAttribute VALUE: " << dynamic_cast<StringAttribute *>(bb)->value() <<endl;
        }
        else if (bb=dynamic_cast<FloatAttribute *>(h.findTypedAttribute<FloatAttribute>(it.name()))){
                // cout << "attrib: " << it.name() << " FloatAttribute VALUE: " << dynamic_cast<FloatAttribute *>(bb)->value() <<endl;
            cout << "attrib: " << it.name() << " FloatAttribute VALUE: " << h.typedAttribute<FloatAttribute>(it.name()).value() <<endl; // alternative option to cast
        }
            else if (h.findTypedAttribute<IntAttribute>(it.name())){
            cout << "attrib: " << it.name() << " IntAttribute VALUE: " << endl;
        }
            else if (h.findTypedAttribute<DoubleAttribute>(it.name())){
            cout << "attrib: " << it.name() << " DoubleAttribute VALUE: " << endl; 
        }
            else if (h.findTypedAttribute<Box2iAttribute>(it.name())){
            cout << "attrib: " << it.name() << " Box2iAttribute VALUE: " << endl; 
        }
            else if (h.findTypedAttribute<Box2fAttribute>(it.name())){
            cout << "attrib: " << it.name() << " Box2fAttribute VALUE: " << endl; 
        }
            else if (h.findTypedAttribute<StringVectorAttribute>(it.name())){
            cout << "attrib: " << it.name() << " StringVectorAttribute VALUE: " << endl; 
        }
            else if (h.findTypedAttribute<V2iAttribute>(it.name())){
            cout << "attrib: " << it.name() << " V2iAttribute VALUE: " << endl;
        }
            else if (h.findTypedAttribute<V2fAttribute>(it.name())){
            cout << "attrib: " << it.name() << " V2fAttribute VALUE: " << endl
        }
                else if (h.findTypedAttribute<V2dAttribute>(it.name())){
            cout << "attrib: " << it.name() << " V2dAttribute VALUE: " << endl;
        }
                else if (h.findTypedAttribute<V3iAttribute>(it.name())){
            cout << "attrib: " << it.name() << " V3iAttribute VALUE: " ;
        }
                else if (h.findTypedAttribute<V3fAttribute>(it.name())){
            cout << "attrib: " << it.name() << " V3fAttribute VALUE: " << endl;
        }
                else if (h.findTypedAttribute<V3dAttribute>(it.name())){
            cout << "attrib: " << it.name() << " V3dAttribute VALUE: " << endl;
        }
                else if (h.findTypedAttribute<ChannelListAttribute>(it.name())){
            cout << "attrib: " << it.name() << " ChannelListAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<M33fAttribute>(it.name())){
            cout << "attrib: " << it.name() << " M33fAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<M33dAttribute>(it.name()))
            cout << "attrib: " << it.name() << " M33dAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<M44fAttribute>(it.name())){
            cout << "attrib: " << it.name() << " M44fAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<M44dAttribute>(it.name())){
            cout << "attrib: " << it.name() << " M44dAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<ChromaticitiesAttribute>(it.name())){
            cout << "attrib: " << it.name() << " ChromaticitiesAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<CompressionAttribute>(it.name())){
            cout << "attrib: " << it.name() << " CompressionAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<DeepImageStateAttribute>(it.name())){
            cout << "attrib: " << it.name() << " DeepImageStateAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<EnvmapAttribute>(it.name())){
            cout << "attrib: " << it.name() << " EnvmapAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<FloatVectorAttribute>(it.name())){
            cout << "attrib: " << it.name() << " FloatVectorAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<KeyCodeAttribute>(it.name())){
            cout << "attrib: " << it.name() << " KeyCodeAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<LineOrderAttribute>(it.name())){
            cout << "attrib: " << it.name() << " LineOrderAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<PreviewImageAttribute>(it.name())){
            cout << "attrib: " << it.name() << " PreviewImageAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<RationalAttribute>(it.name())){
            cout << "attrib: " << it.name() << " RationalAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<TileDescriptionAttribute>(it.name())){
            cout << "attrib: " << it.name() << " TileDescriptionAttribute VALUE: " << endl; 
        }
        else if (h.findTypedAttribute<TimeCodeAttribute>(it.name())){
            cout << "attrib: " << it.name() << " TimeCodeAttribute VALUE: " << endl; 
        }
        // else if (h.findTypedAttribute<OpaqueAttribute>(it.name())){
        //      cout << "attrib: " << it.name() << " OpaqueAttribute VALUE: " << endl; 
        // }
        else {
            cout << "NOTFOUND attrib" << it.name() <<endl;
            // StringAttribute aaa = h.typedAttribute<StringAttribute>(it.name());
        }
    }
}


/// Custom Casters

namespace pybind11 { namespace detail {
    template <>
    struct type_caster<V2i> {
    public:
        PYBIND11_TYPE_CASTER(V2i, _("V2i"));

      // python -> c++
        bool load(handle src, bool) {
                    if (!src) return false;
                    value.x = src.attr("x").cast<int>();
                    value.y = src.attr("y").cast<int>();
                    return true;
        }
        // c++ -> python
        static handle cast(V2i src, return_value_policy /* policy */, handle /* parent */) {
                    // Construct new python obj - V2i Doed not have default constructor - using dummy 3,4
                    py::object tv_py = py::module::import("imath").attr("V2i")(3,4);
                    tv_py.attr("x") = py::cast(src.x);
                    tv_py.attr("y") = py::cast(src.y);
                    return tv_py.release();
        }
    };

    template <>
    struct type_caster<Box2i> {
    public:
        PYBIND11_TYPE_CASTER(Box2i, _("Box2i"));
        bool load(handle src, bool) {
                    if (!src) return false;
                    value.min = src.attr("min").cast<V2i>();
                    value.max = src.attr("max").cast<V2i>();
                    return true;
        }
        static handle cast(Box2i src, return_value_policy /* policy */, handle /* parent */) {
                    py::object bbox = py::module::import("imath").attr("Box2i")(V2i(1,1), V2i(1,1));
                    bbox.attr("min") = py::cast(src.min);
                    bbox.attr("max") = py::cast(src.max);
                    return bbox.release();
        }
    };

/* TODO: add type casters
Box
Box2f
Box2i
Channel
Chromaticities
Compression
LineOrder
PixelType
V2f
V2i
chromaticity
point

        // try to import Imath
        //py::object Imath = py::module::import("Imath");

        // this does not expose anything in python - but may overwrite c++stuff
        // py::object Box = py::module::import("Imath").attr("Box");
        // py::object Box2f = py::module::import("Imath").attr("Box2f");
        // py::object Box2i = py::module::import("Imath").attr("Box2i");
        // py::object Channel = py::module::import("Imath").attr("Channel");
        // // py::object Chromacities = py::module::import("Imath").attr("Chromaticities");
        // py::object Compression = py::module::import("Imath").attr("Compression");
        // py::object LineOrder = py::module::import("Imath").attr("LineOrder");
        // py::object PixelType = py::module::import("Imath").attr("PixelType");
        // py::object PreviewImage = py::module::import("Imath").attr("PreviewImage");
        // py::object V2f = py::module::import("Imath").attr("V2f");
        // py::object V2i = py::module::import("Imath").attr("V2i");

         */
}} // namespace pybind11::detail




py::object getAttribute(Header &self, const char * name){
    cout << name << endl;
    py::object object;
    if (self.findTypedAttribute<StringAttribute>(name)){
        auto val = self.findTypedAttribute<StringAttribute>(name)->value();
        object = py::cast(val);
        return object;
    }
    else if (self.findTypedAttribute<FloatAttribute>(name)){
        auto val = self.findTypedAttribute<FloatAttribute>(name)->value();
        object = py::cast(val);
        return object;
    }
    else if (self.findTypedAttribute<DoubleAttribute>(name)){
        auto val = self.findTypedAttribute<DoubleAttribute>(name)->value();
        object = py::cast(val);
        return object;
    }
    else if (self.findTypedAttribute<Box2iAttribute>(name)){
        Box2i val = self.findTypedAttribute<Box2iAttribute>(name)->value();
        py::object pyval = py::module::import("imath").attr("Box2i")(val.min, val.max); // returns: (0, 0) - (236, 118)
        // py::object pyval = py::module::import("imath").attr("Box2i")(val);           // returns: (0, 0) - (236, 118) - None
        return pyval;
    }
    else{
        object = py::cast("aaa");
        return object;
    }

                //      else if (self.findTypedAttribute<Box2fAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " Box2fAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<StringVectorAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " StringVectorAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<V2iAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " V2iAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<V2fAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " V2fAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<V2dAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " V2dAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<V3iAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " V3iAttribute VALUE: " ;
                //      }
                //      else if (self.findTypedAttribute<V3fAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " V3fAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<V3dAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " V3dAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<ChannelListAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " ChannelListAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<M33fAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " M33fAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<M33dAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " M33dAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<M44fAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " M44fAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<M44dAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " M44dAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<ChromaticitiesAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " ChromaticitiesAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<CompressionAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " CompressionAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<DeepImageStateAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " DeepImageStateAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<EnvmapAttribute>(it.name())){
//          cout << "attrib: " << it.name() << " EnvmapAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<FloatVectorAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " FloatVectorAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<KeyCodeAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " KeyCodeAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<LineOrderAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " LineOrderAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<PreviewImageAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " PreviewImageAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<RationalAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " RationalAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<TileDescriptionAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " TileDescriptionAttribute VALUE: " << endl; 
                //      }
                //      else if (self.findTypedAttribute<TimeCodeAttribute>(it.name())){
                //          cout << "attrib: " << it.name() << " TimeCodeAttribute VALUE: " << endl; 
                //      }
                //      // else if (self.findTypedAttribute<OpaqueAttribute>(it.name())){
                //      //      cout << "attrib: " << it.name() << " OpaqueAttribute VALUE: " << endl; 
                //      // }
                //      else {
                //          cout << "NOTFOUND attrib" << it.name() <<endl;
                //      }
}


PYBIND11_MODULE(example, m) {


    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function which adds two numbers");

        m.attr("FLOAT") = PyLong_FromLong(FLOAT);
        m.attr("HALF") = PyLong_FromLong(HALF);
        m.attr("UINT") = PyLong_FromLong(UINT);
        // m.attr("__version__") = PyString_FromString(VERSION);


        // Option 1 (Better)- if defined custom type_caster
        m.def("vec_test_cpp", &vec_test_cpp);
        m.def("vec_test_cpp2", &vec_test_cpp);


        m.def("test_header", &test_header);

        //////////////////// Define basic types - not neccsary as this should be handled by custom casters
        // py::class_<Box2i>(m, "Box2i", py::dynamic_attr())
        // .def(py::init<>())
        // .def(py::init<Vec2<int>, Vec2<int>>())
        // // Box (const T &point);
    // .def_readwrite("min", &Box2i::min)  // requires to specify py::dynamic_attr()
        // .def_readwrite("max", &Box2i::max);  // requires to specify py::dynamic_attr()

        //////////////////// Define Attriubute types
        /*
            may not be required in pyton as this is a simple mapping from type to attribute
            works more as a wrapper around eache type
            Perhaps better would be to extend and expose just the base classs Attribute 
            and provide conversion in that class only ????
         */
        py::class_<StringAttribute>(m, "_StringAttribute")
            .def(py::init<std::string>())
            // .def_readwrite("_value", &TypedAttribute<string>::_value);  // protectd
            // .def("value", &StringAttribute::value);                     // unresolved overloaded function type> 
            .def("value", [](StringAttribute &self){                       // working
                    return self.value();
                });
        py::class_<FloatAttribute>(m, "_FloatAttribute")
            .def(py::init<float>())
            .def("value", [](FloatAttribute &self){
                    return self.value();
            });
        py::class_<Box2iAttribute>(m, "_Box2i")
            .def(py::init<Box2i>());

        //////////////////// Main OpenEXR classes
        py::class_<Header>(m, "Header")
            .def(py::init<Box2i,Box2i,float,V2f,float,LineOrder>())
            // .def("screenWindowWidth", &Header::screenWindowWidth); // not working:def(const char [18], <unresolved overloaded function type>)’
        .def("screenWindowWidth", [](Header &self){  // working
                    return self.screenWindowWidth();
            })
        .def("getAttrib", &getAttribute)
        .def("iter", [](Header &self){
                Header::Iterator it;
                py::dict header_dict;
                for (it=self.begin(); it!=self.end(); ++it){
                    header_dict[it.name()] = getAttribute(self, it.name());
                }
                return header_dict;
            });

    //https://pybind11.readthedocs.io/en/master/classes.html#creating-bindings-for-a-custom-type
        py::class_<InputFile> input_file(m, "InputFile");
        input_file
            .def(py::init<const char* , int >())
        .def("header", &InputFile::header);
}

