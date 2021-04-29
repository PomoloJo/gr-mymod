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
#include "data_gate_impl.h"

namespace gr {
  namespace mymod {

    data_gate::sptr
    data_gate::make()
    {
      return gnuradio::get_initial_sptr
        (new data_gate_impl());
    }

    /*
     * The private constructor
     */
    data_gate_impl::data_gate_impl()
      : gr::sync_block("data_gate",
              gr::io_signature::make(1, 10, sizeof(gr_complex)),
              gr::io_signature::make(1, 2, sizeof(gr_complex))),
      d_index(0)
    {
      message_port_register_in(pmt::mp("arfcn")); 
      set_msg_handler(pmt::mp("arfcn"), boost::bind(&data_gate_impl::changeIndex, this, _1));
    }

    /*
     * Our virtual destructor.
     */
    data_gate_impl::~data_gate_impl()
    {
    }

    int
    data_gate_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in_u0 = (const gr_complex *) input_items[0];
      const gr_complex *in_u1 = (const gr_complex *) input_items[1];
      const gr_complex *in_u2 = (const gr_complex *) input_items[2];
      const gr_complex *in_u3 = (const gr_complex *) input_items[3];
      const gr_complex *in_u4 = (const gr_complex *) input_items[4];

      const gr_complex *in_d0 = (const gr_complex *) input_items[5];
      const gr_complex *in_d1 = (const gr_complex *) input_items[6];
      const gr_complex *in_d2 = (const gr_complex *) input_items[7];
      const gr_complex *in_d3 = (const gr_complex *) input_items[8];
      const gr_complex *in_d4 = (const gr_complex *) input_items[9];


      gr_complex *out0 = (gr_complex *) output_items[0];
      gr_complex *out1 = (gr_complex *) output_items[1];

      const gr_complex *in_list_uplink[5] = {in_u0, in_u1, in_u2, in_u3, in_u4};
      const gr_complex *in_list_downlink[5] = {in_d0, in_d1, in_d2, in_d3, in_d4};

      // Do <+signal processing+>
      for (int i = 0; i < noutput_items;i++)
      {
          out0[i] = in_list_uplink[d_index][i];
          out1[i] = in_list_downlink[d_index][i];
      }
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    void
    data_gate_impl::changeIndex (pmt::pmt_t block_in)
    {
        pmt::pmt_t block_without_header = pmt::cdr(block_in);
        uint8_t * block_in_int8 = (uint8_t *)pmt::blob_data(block_without_header);
        d_index = block_in_int8[0] - 1;
        printf("%d \n",d_index);
    }

  } /* namespace mymod */
} /* namespace gr */

