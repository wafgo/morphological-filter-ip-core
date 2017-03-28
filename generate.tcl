#
open_project morphological-filter
set_top morphological_filter
add_files mf.cpp
add_files top.h
add_files -tb image_utils.h
add_files -tb opencv_top.cpp
add_files -tb opencv_top.h
add_files -tb test.cpp
open_solution "solution1"
set_part {xc7z020clg484-1}
create_clock -period 10 -name default

csim_design -clean
csynth_design
cosim_design
export_design -format ip_catalog
