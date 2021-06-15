/* -*- c++ -*- */

#define MYMOD_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "mymod_swig_doc.i"

%{
#include "mymod/helloworld.h"
#include "mymod/process.h"
#include "mymod/bursts_merge.h"
#include "mymod/data_extract.h"
#include "mymod/selector_ff.h"
#include "mymod/data_gate.h"
#include "mymod/fft2msg.h"
%}


%include "mymod/helloworld.h"
GR_SWIG_BLOCK_MAGIC2(mymod, helloworld);
%include "mymod/process.h"
GR_SWIG_BLOCK_MAGIC2(mymod, process);


%include "mymod/bursts_merge.h"
GR_SWIG_BLOCK_MAGIC2(mymod, bursts_merge);
%include "mymod/data_extract.h"
GR_SWIG_BLOCK_MAGIC2(mymod, data_extract);
%include "mymod/selector_ff.h"
GR_SWIG_BLOCK_MAGIC2(mymod, selector_ff);
%include "mymod/data_gate.h"
GR_SWIG_BLOCK_MAGIC2(mymod, data_gate);
%include "mymod/fft2msg.h"
GR_SWIG_BLOCK_MAGIC2(mymod, fft2msg);
