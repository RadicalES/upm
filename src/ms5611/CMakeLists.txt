set (libname "ms5611")
set (libdescription "Barometric Pressure and Temperature Sensor")
set (module_src ${libname}.cxx)
set (module_hpp ${libname}.hpp)
set (module_iface iPressure.hpp iTemperature.hpp)
upm_module_init(mraa)
