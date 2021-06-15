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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "fft2msg_impl.h"

namespace gr {
  namespace mymod {

    fft2msg::sptr
    fft2msg::make()
    {
      return gnuradio::get_initial_sptr
        (new fft2msg_impl());
    }

    /*
     * The private constructor
     */
    fft2msg_impl::fft2msg_impl()
      : gr::sync_block("fft2msg",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(0, 0, 0)),
      d_count(0)
    {
    	message_port_register_out(pmt::mp("out"));
    }

    /*
     * Our virtual destructor.
     */
    fft2msg_impl::~fft2msg_impl()
    {
    }

    int
    fft2msg_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];

      // Do <+signal processing+>

      for (int i = 0; i < noutput_items; i++)
      {	
		d_fft_data[d_count] = in[i];
		++d_count;
		if (d_count == 1024)
		{
			pmt::pmt_t msg_binary_blob = pmt::make_blob(d_fft_data, 1024 * sizeof(float));
	        pmt::pmt_t data_out = pmt::cons(pmt::PMT_NIL, msg_binary_blob);
	        message_port_pub(pmt::mp("out"), data_out);

	        memset(d_fft_data, 0, sizeof(1024));
	        d_count = 0;
		}
      }
      

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mymod */
} /* namespace gr */

