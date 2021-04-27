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
#include "helloworld_impl.h"

namespace gr {
  namespace mymod {

    helloworld::sptr
    helloworld::make()
    {
      return gnuradio::get_initial_sptr
        (new helloworld_impl());
    }

    /*
     * The private constructor
     */
    helloworld_impl::helloworld_impl()
      : gr::sync_block("helloworld",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {}

    /*
     * Our virtual destructor.
     */
    helloworld_impl::~helloworld_impl()
    {
    }

    int
    helloworld_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      // Do <+signal processing+>
      printf("helloworld\n");
      for(int i = 0, j = 16;i < noutput_items; i++)
      {
        printf("%02x ", in[i]);
        if (--j == 0)
        {
        	j = 16;
        	printf("\n");
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mymod */
} /* namespace gr */

