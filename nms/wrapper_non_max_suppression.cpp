//test_class_wrapper.cpp
#include"./non_max_suppression.cpp"
#include <boost/python.hpp>

BOOST_PYTHON_MODULE(test_class)
{
	namespace py = boost::python;
    py::def("nms", &nms);
}
