#include "hls_video.h"
#include "top.h"

void morphological_filter(AXI_STREAM& video_in, AXI_STREAM& video_out, int rows, int cols) {
    //Create AXI streaming interfaces for the core
#pragma HLS INTERFACE axis port=video_in bundle=INPUT_STREAM
#pragma HLS INTERFACE axis port=video_out bundle=OUTPUT_STREAM

#pragma HLS INTERFACE s_axilite port=rows bundle=CONTROL_BUS offset=0x14
#pragma HLS INTERFACE s_axilite port=cols bundle=CONTROL_BUS offset=0x1C
#pragma HLS INTERFACE s_axilite port=return bundle=CONTROL_BUS

#pragma HLS INTERFACE ap_stable port=rows
#pragma HLS INTERFACE ap_stable port=cols

	hls::Window<MORPH_WINDOW_HEIGHT, MORPH_WINDOW_WIDTH, unsigned char> wdw;
	hls::getStructuringElement(hls::MORPH_ELLIPSE, hls::Size(10, 10), hls::Point(-1,-1), wdw);

#pragma HLS dataflow
	GRAY_IMAGE img_0(rows, cols);
	GRAY_IMAGE img_1(rows, cols);
	GRAY_IMAGE img_2(rows, cols);
	GRAY_IMAGE img_3(rows, cols);
	GRAY_IMAGE img_4(rows, cols);
	hls::AXIvideo2Mat(video_in, img_0);
    hls::Erode<hls::MORPH_ELLIPSE, 1, HLS_8UC1, HLS_8UC1, unsigned char, MAX_HEIGHT, MAX_WIDTH, MORPH_WINDOW_HEIGHT, MORPH_WINDOW_WIDTH >(img_0, img_1, wdw);
    hls::Dilate<hls::MORPH_ELLIPSE, 1, HLS_8UC1, HLS_8UC1, unsigned char, MAX_HEIGHT, MAX_WIDTH, MORPH_WINDOW_HEIGHT, MORPH_WINDOW_WIDTH >(img_1, img_2, wdw);
    hls::Dilate<hls::MORPH_ELLIPSE, 1, HLS_8UC1, HLS_8UC1, unsigned char, MAX_HEIGHT, MAX_WIDTH, MORPH_WINDOW_HEIGHT, MORPH_WINDOW_WIDTH >(img_2, img_3, wdw);
    hls::Erode<hls::MORPH_ELLIPSE, 1, HLS_8UC1, HLS_8UC1, unsigned char, MAX_HEIGHT, MAX_WIDTH, MORPH_WINDOW_HEIGHT, MORPH_WINDOW_WIDTH >(img_3, img_4, wdw);
    hls::Mat2AXIvideo(img_4, video_out);
}
