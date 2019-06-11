// python -c "import OpenEXRA; print OpenEXRA.add(1,2)"

/*
import OpenEXRA
OpenEXRA.add(1,2)
aa = OpenEXRA.InputFile("/tmp/ies_A2.exr", 1)	 # one argument
hh = aa.header()
['channel', 'channels', 'close', 'header', 'isComplete']
>>> cc.header() # dictionary

channels and channel does not work

*/

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

//////////////////////////////////////////////////////// segfaults - cast between V2i - Imath.V2i

// namespace pybind11 { namespace detail {
//     template <> struct type_caster<V2i> {
//     public:
//         /**
//          * This macro establishes the name 'inty' in
//          * function signatures and declares a local variable
//          * 'value' of type inty
//          */
//         PYBIND11_TYPE_CASTER(V2i, _("V2i"));

//         /**
//          * Conversion part 1 (Python->C++): convert a PyObject into a inty
//          * instance or return false upon failure. The second argument
//          * indicates whether implicit conversions should be applied.
//          */
//         bool load(handle src, bool) {
//                                      if (!src) return false;
//                                      // value.some_cpp_member = src.attr("some_python_member").cast<double>();
//                                      value = src.attr("V2i").cast<V2i>(); // this operates on values
//                                      return true;

//         }

//         /**
//          * Conversion part 2 (C++ -> Python): convert an inty instance into
//          * a Python object. The second and third arguments are used to
//          * indicate the return value policy and parent object (for
//          * ``return_value_policy::reference_internal``) and are generally
//          * ignored by implicit casters.
//          */
//         static handle cast(V2i src, return_value_policy /* policy */, handle /* parent */) {
//                                      // Construct new python obj - V2i Doed not have default constructor - using dummy 3,4
//                                      py::object tv_py = py::module::import("imath").attr("V2i")(3,4);
                                     
//                                      tv_py = py::cast((PyObject*)src);
//                                      return tv_py.release();
//         }
//     };
// }} // namespace pybind11::detail

////////////////////////////////////////////////////////


namespace pybind11 { namespace detail {
    template <> struct type_caster<V2i> {
    public:
        PYBIND11_TYPE_CASTER(V2i, _("V2i"));
        bool load(handle src, bool) {
                                        if (!src) return false;
                                        value.x = src.attr("x").cast<int>();
                                        value.y = src.attr("y").cast<int>();
                                        return true;
        }
        static handle cast(V2i src, return_value_policy /* policy */, handle /* parent */) {
                                        // Construct new python obj - V2i Doed not have default constructor - using dummy 3,4
                                        py::object tv_py = py::module::import("imath").attr("V2i")(3,4);
                                        tv_py.attr("x") = py::cast(src.x);
                                        tv_py.attr("y") = py::cast(src.y);
                                        return tv_py.release();
        }
    };
}} // namespace pybind11::detail

int add(int i, int j) {
        // Box2i b = Box2i(0,0,1,2);
        // Vec2 v = Vec2(1,2);
    return i + j;
}

V2i vec_test_cpp(){
        return V2i(1,2);
}


void test_header(){
        // InputFile ii = InputFile("/tmp/ies_A2.exr", 1); // not working
        InputFile ii("/home/kuba/PRJ/openexr-pybind/build/openexr_src/IlmImfTest/lineOrder_decreasing.exr");  // working
        Header h = ii.header();
        cout << h.screenWindowWidth() << endl;

        StringAttribute astr("BB----");
        h.insert("BB", astr);
        StringAttribute *aa = h.findTypedAttribute<StringAttribute>("BB");                                       
        cout << aa->value() << "___" <<endl;


        Header::Iterator it;
        for (it=h.begin(); it!=h.end(); ++it){
                cout << it.name()<<endl;
        }
}

PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

		m.def("test_header", &test_header);
		
    m.def("add", &add, "A function which adds two numbers");

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


                //TODO //['FLOAT', 'HALF', 'Header', 'InputFile', 'OutputFile', 'UINT', '__doc__', '__file__', '__name__', '__package__', '__version__', 'error',

                // Current; ['__doc__', '__file__', '__name__', '__package__', 'add']

                m.attr("FLOAT") = PyLong_FromLong(FLOAT);
                m.attr("HALF") = PyLong_FromLong(HALF);
                m.attr("UINT") = PyLong_FromLong(UINT);
                // m.attr("__version__") = PyString_FromString(VERSION);


    //https://pybind11.readthedocs.io/en/master/classes.html#creating-bindings-for-a-custom-type
                py::class_<InputFile>(m, "InputFile")
                  .def(py::init<const char* , int >())
                  // .def_readonly("header", &InputFile::header)
                  .def("header", &InputFile::header);


                py::class_<Header>(m, "Header");

                // Option 1 (Better)- if defined custom type_caster
                m.def("vec_test_cpp", &vec_test_cpp);

                // Option 2 - no cater required but need to handle conversion per each method
                // m.def("vec_test_cpp", []() {
                //              py::object pyV2i = py::module::import("Imath").attr("V2i");
                //              cout << vec_test_cpp() <<endl;
                //              V2i aaa = vec_test_cpp();
                //              // pyV2i bbb = py::cast(aaa); // not working - Imath.V2i is known at runtime

                //              return pyV2i(aaa.x,aaa.y);  // this is working

                //      });
}
