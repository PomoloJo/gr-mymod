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
#include "process_impl.h"
#include "stdio.h"

namespace gr {
  namespace mymod {

    process::sptr
    process::make(const std::string &filename)  // , bool flag_save_data
    {
      return gnuradio::get_initial_sptr
        (new process_impl(filename));  // , flag_save_data
    }

    /*
     * The private constructor
     */
    process_impl::process_impl(const std::string &filename)  // , bool flag_save_data
      : gr::block("process",
              gr::io_signature::make(0,0,0),
              gr::io_signature::make(0,0,0)),
        d_output_file(filename.c_str(), std::ofstream::binary),
        d_arfcn(0),
        d_fn(0),
        d_fn_mod52(0),
        d_ts(0),
        d_block_number(255),
        d_burst_num_in_block(0),
        d_csmode(0)  // , d_flag_save_data(flag_save_data)
    {
      memset(d_block, 0, BLOCK_SIZE);
      
      message_port_register_in(pmt::mp("in")); 
      set_msg_handler(pmt::mp("in"), boost::bind(&process_impl::processData, this, _1));
      message_port_register_out(pmt::mp("out_cs1"));
      message_port_register_out(pmt::mp("out_cs2"));

    }

    /*
     * Our virtual destructor.
     */
    process_impl::~process_impl()
    {
      if (d_output_file.is_open())
        {
            d_output_file.close();
        }
    }

    // int num_bursts = 0;
    void
    process_impl::processData (pmt::pmt_t block_in)
    {
        // std::string s = pmt::serialize_str(burst_in);
        // const char *serialized = s.data();
        // const unsigned char *p_data = (const unsigned char*) serialized;
        // printf("\n");
        // for (int i = 26; i < 174; i++)
        // {
        //     printf("%02x ", p_data[i]);
        // }
        // printf("\n");

        /*get the brock data in int8*/
        pmt::pmt_t block_without_header = pmt::cdr(block_in);
        uint8_t * block_in_int8 = (uint8_t *)pmt::blob_data(block_without_header);

        memcpy(d_block, block_in_int8, 456);
        d_csmode = block_in_int8[456];
        d_block_number = block_in_int8[457];
        d_data_send[31] = block_in_int8[458];
        d_data_send[32] = block_in_int8[459];
        d_data_send[33] = block_in_int8[460];
        d_data_send_cs2[36] = block_in_int8[458];
        d_data_send_cs2[37] = block_in_int8[459];
        d_data_send_cs2[38] = block_in_int8[460];
        d_ts = block_in_int8[461];
        deinterleave();
        switch (d_csmode)
        {
        case 255: // 11111111
            //printf("cs1\n");
            decodeCs1();
            crcCs1();
            ubit2sbitCs1();
            if (d_result_sbit_cs1[0] >= 64 or d_data_send[30] != 0)
            {
              break;
            }
            else if (d_result_sbit_cs1[3] == 21 and d_result_sbit_cs1[4] == 0 and d_result_sbit_cs1[5] == 0)
            {
              break;
            }
            else if (d_result_sbit_cs1[3] == 43 and d_result_sbit_cs1[4] == 43 and d_result_sbit_cs1[5] == 43)
            {
              break;
            }
            sendDataCs1();
            break;

        case 200: // 11001000
            //printf("cs2\n");
            decodeCs2();
            crcCs2();
            ubit2sbitCs2();
            if (d_result_sbit_cs2[0] >= 64 or d_data_send_cs2[35] != 0)
            {
              break;
            }
            else if (d_result_sbit_cs2)
            sendDataCs2();
            break;
        case 33:  // 00100001
            //printf("cs3\n");
            break;
        case 22:  // 00010110
            //printf("cs4\n");
            break;
        // default:
        //     printf("no cs\n");
        }

        d_csmode = 0;
        d_block_number = 255;
        memset(d_block, 0, BLOCK_SIZE);

    }


    void 
    process_impl::sendDataCs1()
    {
      // sent output bursts
      memcpy(d_data_send, d_result_sbit_cs1, 28);
      d_data_send[28] = d_csmode;
      d_data_send[29] = d_block_number;
      // d_data_send[30] in function crcCs1()
      // 31 = 28 + csmode + block_num + crc
      d_data_send[34] = d_ts;
      pmt::pmt_t msg_binary_blob = pmt::make_blob(d_data_send, 35);
      pmt::pmt_t burst_out = pmt::cons(pmt::PMT_NIL, msg_binary_blob);
      message_port_pub(pmt::mp("out_cs1"), burst_out);

      // printf("\n");
      // for(int i=0;i<460;i++){
      //   printf("%2d ", d_block[i]);
      //   if ((i+1)%20==0)
      //     printf("\n");
      // }

      /*!!!!!!!!output file!!!!!!!!!*/
      // if (d_flag_save_data)
      // {
      //   std::string s = pmt::serialize_str(burst_out);
      //   const char *serialized = s.data();
      //   d_output_file.write(serialized, s.length());
      // }
    }

    void 
    process_impl::sendDataCs2()
    {
      // sent output bursts
      memcpy(d_data_send_cs2, d_result_sbit_cs2, 33);
      d_data_send_cs2[33] = d_csmode;
      d_data_send_cs2[34] = d_block_number;
      d_data_send_cs2[39] = d_ts;
      pmt::pmt_t msg_binary_blob = pmt::make_blob(d_data_send_cs2, 40);
      pmt::pmt_t burst_out = pmt::cons(pmt::PMT_NIL, msg_binary_blob);
      message_port_pub(pmt::mp("out_cs2"), burst_out);

      /*!!!!!!!!output file!!!!!!!!!*/
      // if (d_flag_save_data)
      // {
      //   std::string s = pmt::serialize_str(burst_out);
      //   const char *serialized = s.data();
      //   d_output_file.write(serialized, s.length());
      // }
    }


    void
    process_impl::deinterleave()
    {
      int8_t conv_code[456];
      memset(conv_code, 0, 456);
      for(int i = 0; i < 456; i++)
      {
        conv_code[i] = d_block[((i % 8) % 4) * 114 + (2 * ((49 * i) % 57) + (i % 8) / 4)];
      }
      memcpy(d_block, conv_code, 456);
    }

    void
    process_impl::decodeCs1()
    {
      // uint8_t d_g1[5] = { 1,0,0,1,1 };
      // uint8_t d_g2[5] = { 1,1,0,1,1 };
      // uint8_t d_output_table[16][2][2] = 
      // { 
      //     0,0,  1,1,
      //     1,1,  0,0,
      //     1,1,  0,0,
      //     0,0,  1,1,
      //     0,0,  1,1,
      //     1,1,  0,0,
      //     1,1,  0,0,
      //     0,0,  1,1,
      //     0,1,  1,0,
      //     1,0,  0,1,
      //     1,0,  0,1,
      //     0,1,  1,0,
      //     0,1,  1,0,
      //     1,0,  0,1,
      //     1,0,  0,1,
      //     0,1,  1,0
      // };
      // uint8_t d_vtb_result[228];
      memset(d_vtb_result, 0, 228);

      uint8_t decode[16][228];
      uint8_t decode_temp[16][228];
      memset(decode, 0, 16 * 228);
      memset(decode_temp, 0, 16 * 228);

      uint8_t euclidean_sum[16];
      uint8_t euclidean_sum_temp[16];
      memset(euclidean_sum, 0, 16);
      memset(euclidean_sum_temp, 0, 16);

      // vtb decode
      for (int i = 0; i < 228; i++)
      {
          int y, input_bit;
          int euclidean_final_bit0 = 0;
          int euclidean_final_bit1 = 0;
          for (int x = 0; x < 16; x++)
          {
              if(x < 8)
              {
                  y = x;
                  input_bit = 0;
              }
              else
              {
                  y = x - 8;
                  input_bit = 1;
              }
              euclidean_final_bit0 = (d_output_table[2 * y][input_bit][0] ^ d_block[2 * i])
                                  + (d_output_table[2 * y][input_bit][1] ^ d_block[2 * i + 1]);
              euclidean_final_bit1 = (d_output_table[2 * y + 1][input_bit][0] ^ d_block[2 * i]) 
                                  + (d_output_table[2 * y + 1][input_bit][1] ^ d_block[2 * i + 1]);

              if ((euclidean_sum[2 * y] + euclidean_final_bit0) < (euclidean_sum[2 * y + 1] + euclidean_final_bit1))
              {
                  memcpy(decode_temp[x], decode[2 * y], 228);
                  decode_temp[x][i] = input_bit;
                  euclidean_sum_temp[x] = euclidean_sum[2 * y] + euclidean_final_bit0;
              }
              else
              {
                  memcpy(decode_temp[x], decode[2 * y + 1], 228);
                  decode_temp[x][i] = input_bit;
                  euclidean_sum_temp[x] = euclidean_sum[2 * y + 1] + euclidean_final_bit1;
              }
          }
          memcpy(euclidean_sum, euclidean_sum_temp, 16);
          memcpy(decode, decode_temp, 16 * 228);
      }
      int euclidean_min_index = std::min_element(euclidean_sum, euclidean_sum + 16) - euclidean_sum;
      memcpy(d_vtb_result, decode[euclidean_min_index], 228);

      // for (int j = 0; j < 228; j++) 
      // {
      //     printf("%d ", d_vtb_result[j]);
      // }
    }


    void
    process_impl::decodeCs2()
    {
      memset(d_vtb_result_cs2, 0, 294);

      // uint8_t decode[16][294];
      // uint8_t decode_temp[16][294];
      // memset(decode, 0, 16 * 294);
      // memset(decode_temp, 0, 16 * 294);

      // uint8_t euclidean_sum[16];
      // uint8_t euclidean_sum_temp[16];
      // memset(euclidean_sum, 0, 16);
      // memset(euclidean_sum_temp, 0, 16);

      // int temp_decode_data[588];
      // for (int i = 0, j = 0; i < 588; i++)
      // {
      //     if (d_delete_mark_table[i])
      //         temp_decode_data[i] = 0;  // yayuan = 0
      //     else
      //     {
      //         temp_decode_data[i] = d_block[j++];
      //     }
      // }

      int num_states = 16; // 状态数
      int tb_len = 96; // 回溯深度

      // Initialize state metrics
      int state_metric[16] = {0U, 32767U, 32767U, 32767U, 32767U, 32767U, 32767U, 32767U, 32767U, 32767U, 32767U, 32767U, 32767U, 32767U, 32767U, 32767U};

      // Initialize traceback memory
      int tb_idx = 0;
      int tb_input[16][97]; // tb_len + 1  = 97
      memset(tb_input, 0, 16 * 97 * sizeof(int));
      int tb_state[16][97];
      memset(tb_state, 0, 16 * 97 * sizeof(int));

      //vitdecUnQ()核心的解码器函数
      //puncVector是588个1，打孔标0
      int p_pat_len = 588;  //sizeof(puncture) / sizeof(int);
      // 不打孔的位数
      int p_pat_sum = 456;
      // 预解码长度
      int pre_decode_len = 588;
      // 预解码矩阵
      int pre_decode_vec[588];
      memset(pre_decode_vec, 0, 588 * sizeof(int));
      // 有效比特矩阵
      bool valid_bits[588];
      memset(valid_bits, 0, 588 * sizeof(bool));
      

      // Fill in input to the preDecoding vector and expand puncPattern
      for (int i = 0, p = 0; i < pre_decode_len; i++)
      {
          valid_bits[i] = d_puncture_table[i];
          if (d_puncture_table[i])
          {
              pre_decode_vec[i] = d_block[p];
              ++p;
          }
      }

      int block_size = 294;      //  preDecodLen / n  : 588 / 2
      int blk_siz_min_one = 293; // blockSize - 1

      // 最终译码输出的数组
      // uint8_t decoded[294];
      memset(d_vtb_result_cs2, 0, 294 * sizeof(uint8_t));

      int tb_work_last_tb = 0U;
      int min_state_last_tb = 0U;

      int output_idx_offset;
      int input_idx_offset;
      int branch_metric[4];
      memset(branch_metric, 0, 4 * sizeof(int));
      for (int i = 0; i < block_size; i++)
      {
          output_idx_offset = (i - tb_len + block_size) % block_size;
          input_idx_offset = 2 * i;

          // Calculate branch metrics  调用分支度量函数
          QPuncBMC(branch_metric, pre_decode_vec[input_idx_offset], pre_decode_vec[input_idx_offset + 1], valid_bits[input_idx_offset], valid_bits[input_idx_offset + 1]);

          // Update state metrics (ACS)   调用加比选函数
          // output value:
          int min_state = 0;
          ACS(min_state, state_metric, tb_input, tb_state, 
              num_states, branch_metric, tb_idx);

          // Traceback decoding 回溯译码
          int input = 0U;
          int tb_work = tb_idx;

          if (i == blk_siz_min_one)
          {
              // Store starting minState
              min_state_last_tb = min_state; // min_state 在ACS中输出
              // Store starting tbWork
              tb_work_last_tb = tb_work;
          }

          // For TRUNC or TERM mode, dont do traceback for first tblen times
          if (i >= tb_len)
          {
              for (int j = 0; j <= tb_len; j++)
              {
                  input = tb_input[min_state][tb_work]; // min_state在ACS中输出
                  min_state = tb_state[min_state][tb_work];
                  if (tb_work > 0)
                  {
                      --tb_work;
                  }
                  else
                  {
                      tb_work = tb_len;
                  }
              }
              // Set the output decoded value bit by bit from the input associated
              // with the most likely path through the trellis at time tblen prior to
              // the current time
              d_vtb_result_cs2[output_idx_offset] = input & 1;
              input = input >> 1;
          }

          // Increment(mod tblen) the traceback indexand store
          if (tb_idx < tb_len)
          {
              ++tb_idx;
          }
          else
          {
              tb_idx = 0;
          }
      }

      // Truncated or Terminated mode :
      // Fill the last tblen output blocks using the same traceback path,
      // working our way back from the very last block.

      int out_idx_offset;
      int input;
      for (int i = 0; i < tb_len; i++)
      {
          out_idx_offset = blk_siz_min_one - i;
          input = tb_input[min_state_last_tb][tb_work_last_tb];

          d_vtb_result_cs2[out_idx_offset] = input & 1;
          input = input >> 1;

          min_state_last_tb = tb_state[min_state_last_tb][tb_work_last_tb];

          if (tb_work_last_tb > 0)
          {
              --tb_work_last_tb;
          }
          else
          {
              tb_work_last_tb = tb_len;
          }
      }
      /////// 至此vitdecUnQ结束
    }



    // QPuncBMC
    // 实际上被爷写成了分类的嘻嘻嘻
    void 
    process_impl::QPuncBMC(int *branch_metrics, int code_word_0, int code_word_1, int valid_bits_0, int valid_bits_1)
    // param : valid_bits：这个就是588打孔位那个puncture，可以是全局变量，实际上就是每次传进来puncture表中的两个值
    {
        int num_branches = 4;   // 2^n
        memset(branch_metrics, 0, 4 * sizeof(int));
        if (valid_bits_1 == 0)
        {
            if (code_word_0 == 0)
            {
                branch_metrics[0] = 0;
                branch_metrics[1] = 0;
                branch_metrics[2] = 1;
                branch_metrics[3] = 1;
            }
            else
            {
                branch_metrics[0] = 1;
                branch_metrics[1] = 1;
                branch_metrics[2] = 0;
                branch_metrics[3] = 0;
            }
        }
        else
        {
            if (code_word_0 == 0 && code_word_1 == 0)
            {
                branch_metrics[0] = 0;
                branch_metrics[1] = 1;
                branch_metrics[2] = 1;
                branch_metrics[3] = 2;
            }
            else if (code_word_0 == 0 && code_word_1 == 1)
            {
                branch_metrics[0] = 1;
                branch_metrics[1] = 0;
                branch_metrics[2] = 2;
                branch_metrics[3] = 1;
            }
            else if (code_word_0 == 1 && code_word_1 == 0)
            {
                branch_metrics[0] = 1;
                branch_metrics[1] = 2;
                branch_metrics[2] = 0;
                branch_metrics[3] = 1;
            }
            else if (code_word_0 == 1 && code_word_1 == 1)
            {
                branch_metrics[0] = 2;
                branch_metrics[1] = 1;
                branch_metrics[2] = 1;
                branch_metrics[3] = 0;
            }
        }
    }

    // ACS 加比选核心算法
    void 
    process_impl::ACS(int &min_state, int *state_metric, int tb_input[16][97], int tb_state[16][97],
        int num_states, int *branch_metric, int tb_idx)
    {
        int renorm = 32767;
        int temp_metric[16];
        for (int i = 0; i < 16; i++)
        {
            temp_metric[i] = renorm;
        }
        int curr_metric;
        int next_state_idx;
        int curr_met_plus_branch_met;
        for (int state_idx = 0; state_idx < num_states; state_idx++)
        {
            curr_metric = state_metric[state_idx];
            for (int input_idx = 0; input_idx < 2; input_idx++)
            {
                next_state_idx = d_next_states[state_idx][input_idx];
                curr_met_plus_branch_met = curr_metric + branch_metric[d_output_states[state_idx][input_idx]];
                if (curr_met_plus_branch_met < temp_metric[next_state_idx])
                {
                    temp_metric[next_state_idx] = curr_met_plus_branch_met;
                    if (curr_met_plus_branch_met < renorm)
                    {
                        // Update the renorm value (minimum ending state metric)
                        renorm = curr_met_plus_branch_met;
                    }

                    // Precompute tmpIdx (since it is used twice below)
                    tb_state[next_state_idx][tb_idx] = state_idx;
                    tb_input[next_state_idx][tb_idx] = input_idx;
                }
            }
        }

        // Update (and renormalize) state metrics, then find minimum metric state
        // for start of traceback
        min_state = 0U;
        int tmp_val;
        for (int state_idx = 0; state_idx < num_states; state_idx++)
        {
            tmp_val = temp_metric[state_idx] - renorm;
            state_metric[state_idx] = double(tmp_val);
            if (tmp_val == 0)
            {
                min_state = state_idx; // uint32(state_idx)
            }
        }
    }



    void
    process_impl::crcCs1()
    {
      // crc generator polynomial of cs-1 is ( (D23 + 1) * (D17 + D3 +1) )
      uint8_t crc_gen[41] = { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1 };
      uint8_t crc_temp[224];
      memset(crc_temp, 1, 224);
      memcpy(crc_temp, d_vtb_result, 184);
      uint8_t crc_result = 0;

      for (int i = 0; i < 184; i++)
      {
          if (crc_temp[i])
          {
              for (int j = i; j < i + 41; j++) 
              {
                  crc_temp[j] = crc_temp[j] ^ crc_gen[j - i];
              }
          }
      }

      for (int i = 184; i < 224; i++)
      {
          if (crc_temp[i] != d_vtb_result[i])
              ++crc_result;
      }
      d_data_send[30] = crc_result;
      /*if (crc_result == 0)
          printf("cs1 crc pass!\n");
      else
          printf("cs1 crc: %d\n", crc_result);*/
    }


    void 
    process_impl::crcCs2()
    {
        int crc_gen[17] = { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
        int crc_temp[287];

        for (int i = 0; i < 3; i++)
        {
            crc_temp[i] = d_vtb_result_cs2[i];
        }
        for (int i = 3; i < 271; i++)
        {
            crc_temp[i] = d_vtb_result_cs2[i + 3];
        }
        for (int i = 271; i < 287; i++) {
            crc_temp[i] = 1;
        }

        int crc_result = 0;

        for (int i = 0; i < 271; i++)
        {
            if (crc_temp[i])
            {
                for (int j = i; j < i + 17; j++)
                {
                    crc_temp[j] = crc_temp[j] ^ crc_gen[j - i];
                }
            }
        }

        for (int i = 271; i < 287; i++)
        {
            if (crc_temp[i] != d_vtb_result_cs2[i + 3])
                ++crc_result;
        }

        d_data_send_cs2[35] = crc_result;

        // if (crc_result == 0)
        //     printf("cs2 crc pass!\n");
        // else
        //     printf("cs2 crc: %d\n", crc_result);
    }


    void
    process_impl::ubit2sbitCs1()
    {
      memset( d_result_sbit_cs1, 0, 28 );
      for( int i = 0; i < 28; i++ )
      {
        for( int j = 0; j < 8; j++ )
        {
          d_result_sbit_cs1[i] = d_result_sbit_cs1[i] << 1;
          d_result_sbit_cs1[i] += d_vtb_result[ i * 8 + 7 - j ];
        }
      }
    }

    void
    process_impl::ubit2sbitCs2()
    {
      uint8_t vtb_result_cs2_temp[264];
      memset(d_result_sbit_cs2, 0, 33 );
      memcpy(vtb_result_cs2_temp, d_vtb_result_cs2, 3);
      memcpy(vtb_result_cs2_temp + 3, d_vtb_result_cs2 + 6, 261);
      for( int i = 0; i < 33; i++ )
      {
        for( int j = 0; j < 8; j++ )
        {
          d_result_sbit_cs2[i] = d_result_sbit_cs2[i] << 1;
          d_result_sbit_cs2[i] += vtb_result_cs2_temp[ i * 8 + 7 - j ];
        }
      }
    }
    

  } /* namespace mymod */
} /* namespace gr */

