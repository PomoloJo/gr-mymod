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
      const gr_complex *in_u5 = (const gr_complex *) input_items[5];
      const gr_complex *in_u6 = (const gr_complex *) input_items[6];
      const gr_complex *in_u7 = (const gr_complex *) input_items[7];
      const gr_complex *in_u8 = (const gr_complex *) input_items[8];
      const gr_complex *in_u9 = (const gr_complex *) input_items[9];
      const gr_complex *in_u10 = (const gr_complex *) input_items[10];
      const gr_complex *in_u11 = (const gr_complex *) input_items[11];
      const gr_complex *in_u12 = (const gr_complex *) input_items[12];
      const gr_complex *in_u13 = (const gr_complex *) input_items[13];
      const gr_complex *in_u14 = (const gr_complex *) input_items[14];
      const gr_complex *in_u15 = (const gr_complex *) input_items[15];
      const gr_complex *in_u16 = (const gr_complex *) input_items[16];
      const gr_complex *in_u17 = (const gr_complex *) input_items[17];
      const gr_complex *in_u18 = (const gr_complex *) input_items[18];

      const gr_complex *in_d0 = (const gr_complex *) input_items[19];
      const gr_complex *in_d1 = (const gr_complex *) input_items[20];
      const gr_complex *in_d2 = (const gr_complex *) input_items[21];
      const gr_complex *in_d3 = (const gr_complex *) input_items[22];
      const gr_complex *in_d4 = (const gr_complex *) input_items[23];
      const gr_complex *in_d5 = (const gr_complex *) input_items[24];
      const gr_complex *in_d6 = (const gr_complex *) input_items[25];
      const gr_complex *in_d7 = (const gr_complex *) input_items[26];
      const gr_complex *in_d8 = (const gr_complex *) input_items[27];
      const gr_complex *in_d9 = (const gr_complex *) input_items[28];
      const gr_complex *in_d10 = (const gr_complex *) input_items[29];
      const gr_complex *in_d11 = (const gr_complex *) input_items[30];
      const gr_complex *in_d12 = (const gr_complex *) input_items[31];
      const gr_complex *in_d13 = (const gr_complex *) input_items[32];
      const gr_complex *in_d14 = (const gr_complex *) input_items[33];
      const gr_complex *in_d15 = (const gr_complex *) input_items[34];
      const gr_complex *in_d16 = (const gr_complex *) input_items[35];
      const gr_complex *in_d17 = (const gr_complex *) input_items[36];
      const gr_complex *in_d18 = (const gr_complex *) input_items[37];


      gr_complex *out0 = (gr_complex *) output_items[0];
      gr_complex *out1 = (gr_complex *) output_items[1];

      const gr_complex *in_list_uplink[19] = 
      {in_u0, in_u1, in_u2, in_u3, in_u4, in_u5, in_u6, in_u7, in_u8, in_u9,
        in_u10, in_u11, in_u12, in_u13, in_u14, in_u15, in_u16, in_u17, in_u18};

      const gr_complex *in_list_downlink[19] = 
      {in_d0, in_d1, in_d2, in_d3, in_d4, in_d5, in_d6, in_d7, in_d8, in_d9,
        in_d10, in_d11, in_d12, in_d13, in_d14, in_d15, in_d16, in_d17, in_d18};

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
        printf("current index: %d \n", d_index);
        pmt::pmt_t block_without_header = pmt::cdr(block_in);
        uint8_t * block_in_int8 = (uint8_t *)pmt::blob_data(block_without_header);
        if(block_in_int8[0] > 0)
        {
          if(d_index != block_in_int8[0] - 1)
          {
            d_index = block_in_int8[0] - 1;
            printf("!!! index change: %d \n",d_index);
          }
        } 
    }

  } /* namespace mymod */
} /* namespace gr */

