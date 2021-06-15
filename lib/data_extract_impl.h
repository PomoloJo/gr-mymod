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

#ifndef INCLUDED_MYMOD_DATA_EXTRACT_IMPL_H
#define INCLUDED_MYMOD_DATA_EXTRACT_IMPL_H

#include <mymod/data_extract.h>
#include <vector>

namespace gr {
  namespace mymod {

    class data_extract_impl : public data_extract
    {
     private:
        uint8_t d_block_recv_cs2[40];

        std::vector<std::vector<uint8_t> > d_data_stack_list[32] 
        {
          data_stack_0,
          data_stack_1,
          data_stack_2,
          data_stack_3,
          data_stack_4,
          data_stack_5,
          data_stack_6,
          data_stack_7,
          data_stack_8,
          data_stack_9,
          data_stack_10,
          data_stack_11,
          data_stack_12,
          data_stack_13,
          data_stack_14,
          data_stack_15,
          data_stack_16,
          data_stack_17,
          data_stack_18,
          data_stack_19,
          data_stack_20,
          data_stack_21,
          data_stack_22,
          data_stack_23,
          data_stack_24,
          data_stack_25,
          data_stack_26,
          data_stack_27,
          data_stack_28,
          data_stack_29,
          data_stack_30,
          data_stack_31
        };

        std::vector<std::vector<uint8_t> > data_stack_0;
        std::vector<std::vector<uint8_t> > data_stack_1;
        std::vector<std::vector<uint8_t> > data_stack_2;
        std::vector<std::vector<uint8_t> > data_stack_3;
        std::vector<std::vector<uint8_t> > data_stack_4;
        std::vector<std::vector<uint8_t> > data_stack_5;
        std::vector<std::vector<uint8_t> > data_stack_6;
        std::vector<std::vector<uint8_t> > data_stack_7;
        std::vector<std::vector<uint8_t> > data_stack_8;
        std::vector<std::vector<uint8_t> > data_stack_9;
        std::vector<std::vector<uint8_t> > data_stack_10;
        std::vector<std::vector<uint8_t> > data_stack_11;
        std::vector<std::vector<uint8_t> > data_stack_12;
        std::vector<std::vector<uint8_t> > data_stack_13;
        std::vector<std::vector<uint8_t> > data_stack_14;
        std::vector<std::vector<uint8_t> > data_stack_15;
        std::vector<std::vector<uint8_t> > data_stack_16;
        std::vector<std::vector<uint8_t> > data_stack_17;
        std::vector<std::vector<uint8_t> > data_stack_18;
        std::vector<std::vector<uint8_t> > data_stack_19;
        std::vector<std::vector<uint8_t> > data_stack_20;
        std::vector<std::vector<uint8_t> > data_stack_21;
        std::vector<std::vector<uint8_t> > data_stack_22;
        std::vector<std::vector<uint8_t> > data_stack_23;
        std::vector<std::vector<uint8_t> > data_stack_24;
        std::vector<std::vector<uint8_t> > data_stack_25;
        std::vector<std::vector<uint8_t> > data_stack_26;
        std::vector<std::vector<uint8_t> > data_stack_27;
        std::vector<std::vector<uint8_t> > data_stack_28;
        std::vector<std::vector<uint8_t> > data_stack_29;
        std::vector<std::vector<uint8_t> > data_stack_30;
        std::vector<std::vector<uint8_t> > data_stack_31;

        int d_csmode;
        int d_link_flag;
        int d_arfcn;


        int d_ttl_list[32]
        {
            d_ttl_0,
            d_ttl_1,
            d_ttl_2,
            d_ttl_3,
            d_ttl_4,
            d_ttl_5,
            d_ttl_6,
            d_ttl_7,
            d_ttl_8,
            d_ttl_9,
            d_ttl_10,
            d_ttl_11,
            d_ttl_12,
            d_ttl_13,
            d_ttl_14,
            d_ttl_15,
            d_ttl_16,
            d_ttl_17,
            d_ttl_18,
            d_ttl_19,
            d_ttl_20,
            d_ttl_21,
            d_ttl_22,
            d_ttl_23,
            d_ttl_24,
            d_ttl_25,
            d_ttl_26,
            d_ttl_27,
            d_ttl_28,
            d_ttl_29,
            d_ttl_30,
            d_ttl_31
        };

        int d_ttl_0;
        int d_ttl_1;
        int d_ttl_2;
        int d_ttl_3;
        int d_ttl_4;
        int d_ttl_5;
        int d_ttl_6;
        int d_ttl_7;
        int d_ttl_8;
        int d_ttl_9;
        int d_ttl_10;
        int d_ttl_11;
        int d_ttl_12;
        int d_ttl_13;
        int d_ttl_14;
        int d_ttl_15;
        int d_ttl_16;
        int d_ttl_17;
        int d_ttl_18;
        int d_ttl_19;
        int d_ttl_20;
        int d_ttl_21;
        int d_ttl_22;
        int d_ttl_23;
        int d_ttl_24;
        int d_ttl_25;
        int d_ttl_26;
        int d_ttl_27;
        int d_ttl_28;
        int d_ttl_29;
        int d_ttl_30;
        int d_ttl_31;
   

     public:
      data_extract_impl(const int &cs_mode, const int &link_flag, const int &arfcn);
      ~data_extract_impl();

      void extract (pmt::pmt_t);
      void extractAndSend(int index, uint8_t *data_send);

    };

  } // namespace mymod
} // namespace gr

#endif /* INCLUDED_MYMOD_DATA_EXTRACT_IMPL_H */

