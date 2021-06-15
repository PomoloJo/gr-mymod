/* -*- c++ -*- */
/* 
 * Copyright 2021 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_MYMOD_FFT2MSG_IMPL_H
#define INCLUDED_MYMOD_FFT2MSG_IMPL_H

#include <mymod/fft2msg.h>

namespace gr {
  namespace mymod {

    class fft2msg_impl : public fft2msg
    {
     private:
        int d_count;
        float d_fft_data[1024];
      // Nothing to declare in this block.

     public:
      fft2msg_impl();
      ~fft2msg_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace mymod
} // namespace gr

#endif /* INCLUDED_MYMOD_FFT2MSG_IMPL_H */

