import sys
sys.path.insert(0,"../install_dir/lib/python2.7/site-packages")
import imath
import example
example.add(2,3)
print example.vec_test_cpp()
example.test_header()

aa = example.InputFile("/home/kuba/PRJ/openexr-pybind/build/openexr_src/IlmImfTest/lineOrder_decreasing.exr", 1)
aa.hh()

bb = example.TypedAttribute("BB")
bb.value()
