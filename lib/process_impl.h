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

#ifndef INCLUDED_MYMOD_PROCESS_IMPL_H
#define INCLUDED_MYMOD_PROCESS_IMPL_H

#define BLOCK_SIZE 456

#include <mymod/process.h>
#include <fstream>

namespace gr {
  namespace mymod {

    class process_impl : public process
    {
     private:
      std::ofstream d_output_file;
      int d_arfcn;
      long d_fn;
      uint8_t d_fn_mod52;
      uint8_t d_ts;
      int8_t d_block[BLOCK_SIZE];
      uint8_t d_block_number;
      uint8_t d_burst_num_in_block;
      uint8_t d_csmode;

      uint8_t d_g1[5] = { 1,0,0,1,1 };
      uint8_t d_g2[5] = { 1,1,0,1,1 };
      uint8_t d_output_table[16][2][2] = 
      { 
          {{0,0},  {1,1}},
          {{1,1},  {0,0}},
          {{1,1},  {0,0}},
          {{0,0},  {1,1}},
          {{0,0},  {1,1}},
          {{1,1},  {0,0}},
          {{1,1},  {0,0}},
          {{0,0},  {1,1}},
          {{0,1},  {1,0}},
          {{1,0},  {0,1}},
          {{1,0},  {0,1}},
          {{0,1},  {1,0}},
          {{0,1},  {1,0}},
          {{1,0},  {0,1}},
          {{1,0},  {0,1}},
          {{0,1},  {1,0}}
      };
      uint8_t d_vtb_result[228];
      uint8_t d_data_send[35];  // 28+3+3+1
      uint8_t d_result_sbit_cs1[28];


      uint8_t d_next_states[16][2] =
      {
          {0, 8},
          {0, 8},
          {1, 9},
          {1, 9},
          {2, 10},
          {2, 10},
          {3, 11},
          {3, 11},
          {4, 12},
          {4, 12},
          {5, 13},
          {5, 13},
          {6, 14},
          {6, 14},
          {7, 15},
          {7, 15}
        };

      uint8_t d_output_states[16][2] =
      {
          {0, 3},
          {3, 0},
          {3, 0},
          {0, 3},
          {0, 3},
          {3, 0},
          {3, 0},
          {0, 3},
          {1, 2},
          {2, 1},
          {2, 1},
          {1, 2},
          {1, 2},
          {2, 1},
          {2, 1},
          {1, 2}
        };

      uint8_t d_vtb_result_cs2[294];
      uint8_t d_puncture_table[588] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0};
      uint8_t d_data_send_cs2[40];  // 33+3+3+1
      uint8_t d_result_sbit_cs2[33];

      //bool d_flag_save_data;


      int d_count;
      clock_t d_start;



     public:
      process_impl(const std::string &filename);  // , bool flag_save_data
      ~process_impl();
      void processData (pmt::pmt_t msg);
      void deinterleave();

      void decodeCs1();

      void decodeCs2();
      void QPuncBMC(int* branch_metrics, int code_word_0, int code_word_1, int valid_bits_0, int valid_bits_1);
      void ACS(int &min_state, int* state_metric, int tb_input[16][97], int tb_state[16][97],
        int num_states, int* branch_metric, int tb_idx);


      void crcCs1();
      void crcCs2();

      void ubit2sbitCs1();
      void ubit2sbitCs2();

      void sendDataCs1();
      void sendDataCs2();

    };

  } // namespace mymod
} // namespace gr

#endif /* INCLUDED_MYMOD_PROCESS_IMPL_H */

