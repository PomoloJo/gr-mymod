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

#ifndef INCLUDED_MYMOD_BURSTS_MERGE_IMPL_H
#define INCLUDED_MYMOD_BURSTS_MERGE_IMPL_H

#include <mymod/bursts_merge.h>

namespace gr {
  namespace mymod {

    class bursts_merge_impl : public bursts_merge
    {
     private:
      long d_fn;
      uint8_t d_fn_mod52;
      bool d_burst_ishead;
      int d_num_bursts;
      int8_t d_block[462];
      uint8_t d_block_number;
      uint8_t d_burst_num_in_block;
      uint8_t d_csmode;

      uint8_t d_ts;

     public:
      bursts_merge_impl();
      ~bursts_merge_impl();

      void snooker(pmt::pmt_t msg);
    };

  } // namespace mymod
} // namespace gr

#endif /* INCLUDED_MYMOD_BURSTS_MERGE_IMPL_H */

