import pytest
import sys

# The PYTHONPATH to compiled pyilm and pybind example is set in bash script run_pytest.sh

def test_pybind():
    import example
    assert example.add(2,3) == 5
    
# def test_module_imports():
#     import imath
    
    
    
