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
#include "bursts_merge_impl.h"
#include "stdio.h"

namespace gr {
  namespace mymod {

    bursts_merge::sptr
    bursts_merge::make()
    {
      return gnuradio::get_initial_sptr
        (new bursts_merge_impl());
    }

    /*
     * The private constructor
     */
    bursts_merge_impl::bursts_merge_impl()
      : gr::block("bursts_merge",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,0,0)),
        d_fn(0),
        d_fn_mod52(0),
        d_burst_ishead(0),
        d_num_bursts(0),
        d_block_number(255),
        d_burst_num_in_block(0),
        d_csmode(0),
        d_ts(8)
    {
      memset(d_block, 0, 458);

      message_port_register_in(pmt::mp("in")); 
      set_msg_handler(pmt::mp("in"), boost::bind(&bursts_merge_impl::snooker, this, _1));
      message_port_register_out(pmt::mp("out"));

    }

    /*
     * Our virtual destructor.
     */
    bursts_merge_impl::~bursts_merge_impl()
    {
    }



    void
    bursts_merge_impl::snooker (pmt::pmt_t burst_in)
    {
      pmt::pmt_t burst_without_header = pmt::cdr(burst_in);
      uint8_t * burst_in_int8 = (uint8_t *)pmt::blob_data(burst_without_header);

      ++d_num_bursts;
      d_fn = (burst_in_int8[8] << 24) ^ (burst_in_int8[9] << 16) ^ (burst_in_int8[10] << 8) ^ burst_in_int8[11];
      d_fn_mod52 = d_fn % 52;
      d_ts = burst_in_int8[3];

      /*judge the fn_mod52 and check continuity*/        
      switch(d_fn_mod52)
      {
        case 0:
        case 4:
        case 8:    
        case 13:              
        case 17:              
        case 21:              
        case 26:              
        case 30:              
        case 34:              
        case 39:              
        case 43:              
        case 47:
            d_burst_ishead = true;
            d_block_number = d_fn_mod52;              
      }
            
      if (!d_burst_ishead)
        return;
      else
      {
          /*save burst data into d_block*/
          uint8_t burst_tmp[114];
          memcpy(burst_tmp, burst_in_int8 + 19, 57);
          memcpy(burst_tmp + 57, burst_in_int8 + 104, 57);
          memcpy(d_block + d_burst_num_in_block * 114, burst_tmp, 114);
          // 76 = 60+16, 103 = 87+16
          d_csmode += (burst_in_int8[76] << 7 - 2 * d_burst_num_in_block) 
                    + (burst_in_int8[103] << 6 - 2 * d_burst_num_in_block);
          ++d_burst_num_in_block;
          d_block[456] = d_csmode;
          d_block[457] = d_block_number;
      }

      if (d_burst_num_in_block == 4)
      {
          d_block[458] = (d_fn >> 16) & 255;
          d_block[459] = (d_fn >> 8) & 255;
          d_block[460] = d_fn & 255;
          d_block[461] = d_ts;

          pmt::pmt_t msg_binary_blob = pmt::make_blob(d_block, 462);
          pmt::pmt_t block_out = pmt::cons(pmt::PMT_NIL, msg_binary_blob);
          message_port_pub(pmt::mp("out"), block_out);

          d_burst_num_in_block = 0;
          d_csmode = 0;
          d_block_number = 255;
          memset(d_block, 0, 462);

          d_burst_ishead = false;
      }
    }

  } /* namespace mymod */
} /* namespace gr */

