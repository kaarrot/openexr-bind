import sys
sys.path.insert(0,"../install_dir/lib/python2.7/site-packages")
import imath
import example
example.add(2,3)
print example.vec_test_cpp()
example.test_header()
image = example.InputFile("/home/kuba/SRC/openexr-bind/build/openexr_src/IlmImfTest/lineOrder_decreasing.exr", 1)
header =  image.header()

bb = example._StringAttribute("BB")
bb.value()

print header.iter()


print header.getAttrib("displayWindow")

# Box2i
#aa = example.Box2i(Imath.V2i(0,1),Imath.V2i(2,3))


## Create Box2iAttribute
v1 = Imath.V2i(2,3)
v2 = Imath.V2i(3,4)
print Imath.Box2i(v1,v2)
# example.Attrib(Box2i ???




'''
 b /home/kuba/SRC/openexr-bind/src/example.cpp:190

    Header header (width, height);
    header.insert ("comments", StringAttribute (comments));
    header.insert ("cameraTransform", M44fAttribute (cameraTransform));
'''
