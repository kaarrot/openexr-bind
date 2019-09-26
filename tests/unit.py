import pytest
import sys

sys.path.insert(0,"../install_dir/lib/python2.7/site-packages")

def test_pybind():
    import example
    assert example.add(2,3) == 5
    
def test_module_imports():
    import imath

def test_V2i_return():
    import example, imath
    assert 1 == example.vec_test_cpp().x
    assert 2 == example.vec_test_cpp().y

# def test_example_header():
#     import example
#     example.test_header()

def test_StringAttribute_value():
    import example
    sattr = example._StringAttribute("BB")
    assert sattr.value() == u"BB"


def test_B2i_custom():
    import example, imath
    import pdb
    v1py = imath.V2i(2,3)
    v2 = imath.V2i(3,4)
    b1 = imath.Box2i(v2, v1py)
    # pdb.set_trace()
    # example.box_test_cpp(v1py)
    assert imath.Box2i(imath.V2i(6,7), v1py) == example.box_test_cpp(v1py)

    
# image = example.InputFile("/home/kuba/SRC/openexr-bind/build/openexr_src/IlmImfTest/lineOrder_decreasing.exr", 1)
# header =  image.header()
# print header.iter()
# print header.getAttrib("displayWindow")


# # Box2i
# #aa = example._Box2i(imath.V2i(0,1),imath.V2i(2,3))  # not working 

# def test_imath_Box2i():
#     ''' Test Pyilmbase  Box2iAttribute '''
#     import example, imath
#     v1 = imath.V2i(2,3)
#     v2 = imath.V2i(3,4)
#     aa = imath.Box2i(v1,v2)
#     assert aa.center().x == 2
#     assert aa.center().y == 3

