import sys
sys.path.insert(0,"../install_dir/lib/python2.7/site-packages")
import imath
import example
example.add(2,3)
print example.vec_test_cpp()
example.test_header()
